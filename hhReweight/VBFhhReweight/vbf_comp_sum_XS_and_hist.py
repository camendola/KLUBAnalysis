from sympy import *
from sympy import Matrix
from array import array
import ROOT
import argparse

parser = argparse.ArgumentParser(description='Target couplings.')
parser.add_argument('--nTarget', type=int, dest= 'nTarget', default = 1, help = 'Target Node number'   )
parser.add_argument('--nRew'   , type=int, dest= 'nRew'   , default = 1, help = 'number of reweighting')

args = parser.parse_args()

## implements the formula of https://indico.cern.ch/event/844260/contributions/3568369/attachments/1909554/3154880/2019_09_17_bbtautau_HHrew.pdf, slide 2
## C -> vector of couplings
## S -> vector of samples (generated xs)
## V -> vector of components (a,b,c,iab,ibc,iac)
## M -> matrix that describes the single samples as sum of components, so that S = M * V
## so that M^-1 * S = V
##
## sigma (CV, C2V, kl) = C^T * V = C^T * M-1 * S


def make_histogram(tIn, expr, cut, hname, bounds):
    hformat = 'h (%s)' % bounds
    tIn.Draw(expr + ' >> ' + hformat, cut) ## note: if using goff, I can't retrieve the histo
    myh = ROOT.gPad.GetPrimitive("h");
    out_h = myh.Clone(hname)
    out_h.SetDirectory(0)
    out_h.Sumw2()
    return out_h

def scaleTo(hIn, xs):
    hIn.Scale(xs/hIn.Integral())


class sample:
    def __init__(self, val_CV, val_C2V, val_kl, val_xs, histo):
        self.val_CV  = val_CV
        self.val_C2V = val_C2V
        self.val_kl  = val_kl
        self.val_xs  = val_xs
        self.histo   = histo

def build_matrix(sample_list):    
    if len(sample_list) != 6:
        print "[ERROR] : expecting 6 samples in input"
        raise RuntimeError("malformed input sample list")

    M_tofill = [
        [None,None,None,None,None,None],
        [None,None,None,None,None,None],
        [None,None,None,None,None,None],
        [None,None,None,None,None,None],
        [None,None,None,None,None,None],
        [None,None,None,None,None,None]
    ]

    for isample, sample in enumerate(sample_list):
        # Implement the 6 scalings
        M_tofill[isample][0] = sample.val_CV**2 * sample.val_kl**2
        M_tofill[isample][1] = sample.val_CV**4
        M_tofill[isample][2] = sample.val_C2V**2
        M_tofill[isample][3] = sample.val_CV**3 * sample.val_kl
        M_tofill[isample][4] = sample.val_CV    * sample.val_C2V    * sample.val_kl
        M_tofill[isample][5] = sample.val_CV**2 * sample.val_C2V
    
    res = Matrix(M_tofill)
    return res


# Get the total cross section and histogram
def get_total_xs_and_histo (sample_list):

    # Automatically build the matrix of the initial 6-equation system given the list of samples
    M = build_matrix(sample_list)
    
    # Declare symbols to be used in the solution of the systems
    CV, C2V, kl, a, b, c, iab, iac, ibc, s1, s2, s3, s4, s5, s6 = symbols('CV C2V kl a b c iab iac ibc s1 s2 s3 s4 s5 s6')

    # Declare the vectors of samples, couplings and components
    # The vector of couplings
    C = Matrix([
        [CV**2 * kl**2] ,
        [CV**4]         ,
        [C2V**2]        ,
        [CV**3 * kl]    ,
        [CV * C2V * kl] ,
        [CV**2 * C2V]   
    ])

    # The vector of components
    V = Matrix([
        [a]   ,
        [b]   ,
        [c]   ,
        [iab] ,
        [iac] ,
        [ibc]  
    ])

    # The vector of samples (i.e. cross sections)
    S = Matrix([
        [s1] ,
        [s2] ,
        [s3] ,
        [s4] ,
        [s5] ,
        [s6] 
    ])

    # Invert the system matrix to get the resolution
    Minv   = M.inv()

    # Multiply the Minv for the couplings to get the coefficients of the six addendums of the final cross sections
    coeffs = C.transpose() * Minv

    # Final cross section from multiplying the coefficients for the samples
    sigma  = coeffs*S

    # Eval the final cross section
    total_xs = sigma[0].evalf(subs={
        CV  : t_CV,
        C2V : t_C2V,
        kl  : t_kl,
        s1  : sample_list[0].val_xs,
        s2  : sample_list[1].val_xs,
        s3  : sample_list[2].val_xs,
        s4  : sample_list[3].val_xs,
        s5  : sample_list[4].val_xs,
        s6  : sample_list[5].val_xs,
    })

    # Eval the single coefficients
    eval_coeffs = []
    for coeff in coeffs:
        eval_coeffs.append(coeff.evalf(subs={CV:t_CV, C2V:t_C2V, kl:t_kl}))

    # Normalize each histo for his coefficient*xs
    for i,sample in enumerate(sample_list):
        scaleTo(sample.histo  , eval_coeffs[i] * sample.val_xs)

    for i,sample in enumerate(sample_list):
        if i == 0:
            tot_histo = sample.histo.Clone('tot_histo')
        else:
            tot_histo.Add(sample.histo)

    return total_xs, tot_histo


def makeDataOverMCRatioPlot (hData, hMC, newName, horErrs=False):
    nPoints = hData.GetNbinsX()
    fX       = []
    fY       = []
    feYUp    = []
    feYDown  = []
    feXRight = []
    feXLeft  = []

    for ibin in range (1, nPoints+1):
        num = hData.GetBinContent(ibin)
        den = hMC.GetBinContent(ibin)
        if den != 0:
            # Y
            fY.append(num/den)
            feYUp.append(hData.GetBinErrorUp(ibin) / den)
            feYDown.append(hData.GetBinErrorLow(ibin) / den)

            # X
            fX.append (hData.GetBinCenter(ibin))
            if horErrs:
                feXRight.append(hData.GetBinLowEdge(ibin+1) - hData.GetBinCenter(ibin))
                feXLeft.append(hData.GetBinCenter(ibin) - hData.GetBinLowEdge(ibin))
            else:
                feXLeft.append(0.0)
                feXRight.append(0.0)

    afX       = array ("d", fX      )
    afY       = array ("d", fY      )
    afeYUp    = array ("d", feYUp   )
    afeYDown  = array ("d", feYDown )
    afeXRight = array ("d", feXRight)
    afeXLeft  = array ("d", feXLeft )
    gRatio = ROOT.TGraphAsymmErrors (len(afX), afX, afY, afeXLeft, afeXRight, afeYDown, afeYUp);
    
    gRatio.SetMarkerStyle(8);
    gRatio.SetMarkerSize(1.);
    gRatio.SetMarkerColor(ROOT.kBlack);
    gRatio.SetLineColor(ROOT.kBlack);
    gRatio.SetName(newName)

    return gRatio;


######################
######## MAIN ########
######################

ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

c1 = ROOT.TCanvas('c1', 'c1', 600, 600)
c1.SetFrameLineWidth(3)

pad1 = None
pad2 = None

makeRatioPlot = True
drawCompts = True

if makeRatioPlot:
    pad1 = ROOT.TPad ("pad1", "pad1", 0, 0.25, 1, 1.0)
    pad1.SetFrameLineWidth(3)
    pad1.SetLeftMargin(0.12);
    pad1.SetBottomMargin(0.02);
    pad1.SetTopMargin(0.065);
    pad1.SetGridy(True);
    pad1.Draw()
else:
    pad1 = ROOT.TPad ("pad1", "pad1", 0, 0.0, 1.0, 1.0)
    pad1.SetFrameLineWidth(3)
    pad1.SetLeftMargin(0.12);
    pad1.SetBottomMargin(0.12);
    pad1.SetTopMargin(0.065);
    pad1.Draw()

pad1.cd()

# File FRA
f_1_1_1         = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1_C2V_1_C3_1.root')
f_1_1_0         = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1_C2V_1_C3_0.root')
f_1_1_2         = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1_C2V_1_C3_2.root')
f_1_2_1         = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1_C2V_2_C3_1.root')
f_1p5_1_1       = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1_5_C2V_1_C3_1.root')
f_m2_0_4        = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_m2_C2V_0_C3_4.root')
f_2_m1_m1       = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_2_C2V_m1_C3_m1.root')
f_m1_m1_m1      = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_m1_C2V_m1_C3_m1.root')
f_4_0_0         = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_4_C2V_0_C3_0.root')
f_1_1_4         = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1_C2V_1_C3_4.root')
f_1_1_m2        = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1_C2V_1_C3_m2.root')
f_1_1_m4        = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1_C2V_1_C3_m4.root')
f_1_0_1         = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1_C2V_0_C3_1.root')
f_1_4_1         = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1_C2V_4_C3_1.root')
f_1_m2_1        = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1_C2V_m2_C3_1.root')
f_1_0_0         = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1_C2V_0_C3_0.root')
f_0_1_0         = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_0p00001_C2V_1_C3_0p00001.root')
f_1_0_2         = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1_C2V_0_C3_2.root')
f_2_1_1         = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_2_C2V_1_C3_1.root')
f_3_2_4         = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_3_C2V_2_C3_4.root')
f_1p5_m2p5_m1p5 = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1p5_C2V_m2p5_C3_m1p5.root')
f_1_4p5_m2      = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1_C2V_4p5_C3_m2.root')
f_1_0_2000      = ROOT.TFile('/gwpool/users/brivio/HH_PRODUCTION/CMSSW_8_0_26_patch1/src/LHEparser/VBF_HH_CV_1_C2V_0_C3_2000.root')


t_1_1_1         = f_1_1_1    .Get('lheTree')
t_1_1_0         = f_1_1_0    .Get('lheTree')
t_1_1_2         = f_1_1_2    .Get('lheTree')
t_1_2_1         = f_1_2_1    .Get('lheTree')
t_1p5_1_1       = f_1p5_1_1  .Get('lheTree')
t_m2_0_4        = f_m2_0_4   .Get('lheTree')
t_2_m1_m1       = f_2_m1_m1  .Get('lheTree')
t_m1_m1_m1      = f_m1_m1_m1 .Get('lheTree')
t_4_0_0         = f_4_0_0    .Get('lheTree')
t_1_1_4         = f_1_1_4    .Get('lheTree')
t_1_1_m2        = f_1_1_m2   .Get('lheTree')
t_1_1_m4        = f_1_1_m4   .Get('lheTree')
t_1_0_1         = f_1_0_1    .Get('lheTree')
t_1_4_1         = f_1_4_1    .Get('lheTree')
t_1_m2_1        = f_1_m2_1   .Get('lheTree')
t_1_0_0         = f_1_0_0    .Get('lheTree')
t_0_1_0         = f_0_1_0    .Get('lheTree')
t_1_0_2         = f_1_0_2    .Get('lheTree')
t_2_1_1         = f_2_1_1        .Get('lheTree')
t_3_2_4         = f_3_2_4        .Get('lheTree')
t_1p5_m2p5_m1p5 = f_1p5_m2p5_m1p5.Get('lheTree')
t_1_4p5_m2      = f_1_4p5_m2     .Get('lheTree')
t_1_0_2000      = f_1_0_2000     .Get('lheTree')


# Get the histograms
bounds = '200, 250, 1250'
expr = 'HH_mass'

# Samples used to solve the system --> sample(cV, c2V, kl, xs, histo)
nRew = args.nRew
if nRew == 1:
    rew_list = [
        sample(1,1,1, 0.001499, make_histogram(t_1_1_1, expr, '', 'h_1_1_1', bounds) ),  # node 1
        sample(1,1,0, 0.003947, make_histogram(t_1_1_0, expr, '', 'h_1_1_0', bounds) ),  # node 2
        sample(1,1,2, 0.001243, make_histogram(t_1_1_2, expr, '', 'h_1_1_2', bounds) ),  # node 3
        sample(1,2,1, 0.012719, make_histogram(t_1_2_1, expr, '', 'h_1_2_1', bounds) ),  # node 4
        sample(1,0,1,  0.02388, make_histogram(t_1_0_1, expr, '', 'h_1_0_1', bounds) ),  # node 14
        sample(1,0,0,  0.03209, make_histogram(t_1_0_0, expr, '', 'h_1_0_0', bounds) )   # node 17
    ]

elif nRew == 2:
    rew_list = [
        sample( 1,  1,  1, 0.001499, make_histogram(t_1_1_1   , expr, '', 'h_1_1_1'   , bounds) ),  # node 1
        sample( 1,  1,  0, 0.003947, make_histogram(t_1_1_0   , expr, '', 'h_1_1_0'   , bounds) ),  # node 2
        sample(-2,  0,  4, 0.882721, make_histogram(t_m2_0_4  , expr, '', 'h_m2_0_4'  , bounds) ),  # node 7
        sample(-1, -1, -1, 0.079882, make_histogram(t_m1_m1_m1, expr, '', 'h_m1_m1_m1', bounds) ),  # node 9
        sample( 1,  0,  1,  0.02388, make_histogram(t_1_0_1   , expr, '', 'h_1_0_1'   , bounds) ),  # node 14
        sample( 1,  0,  0,  0.03209, make_histogram(t_1_0_0   , expr, '', 'h_1_0_0'   , bounds) )   # node 17
    ]

elif nRew == 3:
    rew_list = [
        sample(1,1,1, 0.001499, make_histogram(t_1_1_1, expr, '', 'h_1_1_1', bounds) ), # node 1
        sample(1,1,0, 0.003947, make_histogram(t_1_1_0, expr, '', 'h_1_1_0', bounds) ), # node 2
        sample(1,0,1,  0.02388, make_histogram(t_1_0_1, expr, '', 'h_1_0_1', bounds) ), # node 14
        sample(1,0,0,  0.03209, make_histogram(t_1_0_0, expr, '', 'h_1_0_0', bounds) ), # node 17
        sample(0,1,0,  0.01679, make_histogram(t_0_1_0, expr, '', 'h_0_1_0', bounds) ), # node 18
        sample(1,0,2,   0.0178, make_histogram(t_1_0_2, expr, '', 'h_1_0_2', bounds) ), # node 19
    ]

elif nRew == 4:
    rew_list = [
        sample(  1, 1, 1, 0.001499, make_histogram(t_1_1_1  , expr, '', 'h_1_1_1'  , bounds) ), # node 1
        sample(  1, 1, 0, 0.003947, make_histogram(t_1_1_0  , expr, '', 'h_1_1_0'  , bounds) ), # node 2
        sample(  1, 1, 2, 0.001243, make_histogram(t_1_1_2  , expr, '', 'h_1_1_2'  , bounds) ), # node 3
        sample(  1, 2, 1, 0.012719, make_histogram(t_1_2_1  , expr, '', 'h_1_2_1'  , bounds) ), # node 4
        sample(1.5, 1, 1, 0.057943, make_histogram(t_1p5_1_1, expr, '', 'h_1p5_1_1', bounds) ), # node 5
        sample(  1, 1, 4, 0.007305, make_histogram(t_1_1_4  , expr, '', 'h_1_1_4'  , bounds) ), # node 11
    ]

elif nRew == 5:
    rew_list = [
        sample(  1, 1, 1, 0.001499, make_histogram(t_1_1_1  , expr, '', 'h_1_1_1'  , bounds) ), # node 1
        sample(  1, 1, 0, 0.003947, make_histogram(t_1_1_0  , expr, '', 'h_1_1_0'  , bounds) ), # node 2
        sample(  1, 1, 2, 0.001243, make_histogram(t_1_1_2  , expr, '', 'h_1_1_2'  , bounds) ), # node 3
        sample(  1, 2, 1, 0.012719, make_histogram(t_1_2_1  , expr, '', 'h_1_2_1'  , bounds) ), # node 4
        sample(1.5, 1, 1, 0.057943, make_histogram(t_1p5_1_1, expr, '', 'h_1p5_1_1', bounds) ), # node 5
        sample(  1, 1,-2,  0.01543, make_histogram(t_1_1_m2 , expr, '', 'h_1_1_m2' , bounds) ), # node 12
    ]

elif nRew == 6:
    rew_list = [
        sample(  1, 1, 1, 0.001499, make_histogram(t_1_1_1  , expr, '', 'h_1_1_1'  , bounds) ), # node 1
        sample(  1, 1, 0, 0.003947, make_histogram(t_1_1_0  , expr, '', 'h_1_1_0'  , bounds) ), # node 2
        sample(  1, 1, 2, 0.001243, make_histogram(t_1_1_2  , expr, '', 'h_1_1_2'  , bounds) ), # node 3
        sample(  1, 2, 1, 0.012719, make_histogram(t_1_2_1  , expr, '', 'h_1_2_1'  , bounds) ), # node 4
        sample(1.5, 1, 1, 0.057943, make_histogram(t_1p5_1_1, expr, '', 'h_1p5_1_1', bounds) ), # node 5
        sample(  1, 1,-4,  0.03568, make_histogram(t_1_1_m4 , expr, '', 'h_1_1_m4' , bounds) ), # node 13
    ]

elif nRew == 7:
    rew_list = [
        sample(  1, 1, 1, 0.001499, make_histogram(t_1_1_1  , expr, '', 'h_1_1_1'  , bounds) ), # node 1
        sample(  1, 1, 0, 0.003947, make_histogram(t_1_1_0  , expr, '', 'h_1_1_0'  , bounds) ), # node 2
        sample(  1, 1, 2, 0.001243, make_histogram(t_1_1_2  , expr, '', 'h_1_1_2'  , bounds) ), # node 3
        sample(  1, 2, 1, 0.012719, make_histogram(t_1_2_1  , expr, '', 'h_1_2_1'  , bounds) ), # node 4
        sample(1.5, 1, 1, 0.057943, make_histogram(t_1p5_1_1, expr, '', 'h_1p5_1_1', bounds) ), # node 5
        sample(  1, 0, 0,  0.03209, make_histogram(t_1_0_0  , expr, '', 'h_1_0_0'  , bounds) ), # node 17
    ]

elif nRew == 8:
    rew_list = [
        sample(  1, 1, 1, 0.001499, make_histogram(t_1_1_1  , expr, '', 'h_1_1_1'  , bounds) ), # node 1
        sample(  1, 1, 0, 0.003947, make_histogram(t_1_1_0  , expr, '', 'h_1_1_0'  , bounds) ), # node 2
        sample(  1, 1, 2, 0.001243, make_histogram(t_1_1_2  , expr, '', 'h_1_1_2'  , bounds) ), # node 3
        sample(  1, 2, 1, 0.012719, make_histogram(t_1_2_1  , expr, '', 'h_1_2_1'  , bounds) ), # node 4
        sample(1.5, 1, 1, 0.057943, make_histogram(t_1p5_1_1, expr, '', 'h_1p5_1_1', bounds) ), # node 5
        sample(  0, 1, 0,  0.01679, make_histogram(t_0_1_0  , expr, '', 'h_0_1_0'  , bounds) ), # node 18
    ]

elif nRew == 9:
    rew_list = [
        sample(  1, 1, 1, 0.001499, make_histogram(t_1_1_1  , expr, '', 'h_1_1_1'  , bounds) ), # node 1
        sample(  1, 1, 0, 0.003947, make_histogram(t_1_1_0  , expr, '', 'h_1_1_0'  , bounds) ), # node 2
        sample(  1, 1, 2, 0.001243, make_histogram(t_1_1_2  , expr, '', 'h_1_1_2'  , bounds) ), # node 3
        sample(  1, 2, 1, 0.012719, make_histogram(t_1_2_1  , expr, '', 'h_1_2_1'  , bounds) ), # node 4
        sample(1.5, 1, 1, 0.057943, make_histogram(t_1p5_1_1, expr, '', 'h_1p5_1_1', bounds) ), # node 5
        sample(  1, 0, 2,   0.0178, make_histogram(t_1_0_2  , expr, '', 'h_1_0_2'  , bounds) ), # node 19
    ]

elif nRew == 10:
    rew_list = [
        sample(  1, 1, 1, 0.001499, make_histogram(t_1_1_1  , expr, '', 'h_1_1_1'  , bounds) ), # node 1
        sample(  1, 1, 0, 0.003947, make_histogram(t_1_1_0  , expr, '', 'h_1_1_0'  , bounds) ), # node 2
        sample(  1, 1, 2, 0.001243, make_histogram(t_1_1_2  , expr, '', 'h_1_1_2'  , bounds) ), # node 3
        sample(  1, 2, 1, 0.012719, make_histogram(t_1_2_1  , expr, '', 'h_1_2_1'  , bounds) ), # node 4
        sample(1.5, 1, 1, 0.057943, make_histogram(t_1p5_1_1, expr, '', 'h_1p5_1_1', bounds) ), # node 5
        sample(  2, 1, 1,   0.2918, make_histogram(t_2_1_1  , expr, '', 'h_2_1_1'  , bounds) ), # node 20
    ]

elif nRew == 11:
    rew_list = [
        sample(  1, 1, 1, 0.001499, make_histogram(t_1_1_1  , expr, '', 'h_1_1_1'  , bounds) ), # node 1
        sample(  1, 1, 0, 0.003947, make_histogram(t_1_1_0  , expr, '', 'h_1_1_0'  , bounds) ), # node 2
        sample(  1, 1, 2, 0.001243, make_histogram(t_1_1_2  , expr, '', 'h_1_1_2'  , bounds) ), # node 3
        sample(  1, 2, 1, 0.012719, make_histogram(t_1_2_1  , expr, '', 'h_1_2_1'  , bounds) ), # node 4
        sample(1.5, 1, 1, 0.057943, make_histogram(t_1p5_1_1, expr, '', 'h_1p5_1_1', bounds) ), # node 5
        sample(  3, 2, 4,    1.144, make_histogram(t_3_2_4  , expr, '', 'h_3_2_4'  , bounds) ), # node 21
    ]

elif nRew == 12:
    rew_list = [
        sample(  1,    1,    1, 0.001499, make_histogram(t_1_1_1        , expr, '', 'h_1_1_1'        , bounds) ), # node 1
        sample(  1,    1,    0, 0.003947, make_histogram(t_1_1_0        , expr, '', 'h_1_1_0'        , bounds) ), # node 2
        sample(  1,    1,    2, 0.001243, make_histogram(t_1_1_2        , expr, '', 'h_1_1_2'        , bounds) ), # node 3
        sample(  1,    2,    1, 0.012719, make_histogram(t_1_2_1        , expr, '', 'h_1_2_1'        , bounds) ), # node 4
        sample(1.5,    1,    1, 0.057943, make_histogram(t_1p5_1_1      , expr, '', 'h_1p5_1_1'      , bounds) ), # node 5
        sample(1.5, -2.5, -1.5,   0.6047, make_histogram(t_1p5_m2p5_m1p5, expr, '', 'h_1p5_m2p5_m1p5', bounds) ), # node 22
    ]

elif nRew == 13:
    rew_list = [
        sample(  1,   1,  1, 0.001499, make_histogram(t_1_1_1   , expr, '', 'h_1_1_1'   , bounds) ), # node 1
        sample(  1,   1,  0, 0.003947, make_histogram(t_1_1_0   , expr, '', 'h_1_1_0'   , bounds) ), # node 2
        sample(  1,   1,  2, 0.001243, make_histogram(t_1_1_2   , expr, '', 'h_1_1_2'   , bounds) ), # node 3
        sample(  1,   2,  1, 0.012719, make_histogram(t_1_2_1   , expr, '', 'h_1_2_1'   , bounds) ), # node 4
        sample(1.5,   1,  1, 0.057943, make_histogram(t_1p5_1_1 , expr, '', 'h_1p5_1_1' , bounds) ), # node 5
        sample(  1, 4.5, -2,   0.1407, make_histogram(t_1_4p5_m2, expr, '', 'h_1_4p5_m2', bounds) ), # node 23
    ]


elif nRew == 14:
    rew_list = [
        sample(  1, 1, 1, 0.001499, make_histogram(t_1_1_1  , expr, '', 'h_1_1_1'  , bounds) ), # node 1
        sample(  1, 1, 0, 0.003947, make_histogram(t_1_1_0  , expr, '', 'h_1_1_0'  , bounds) ), # node 2
        sample(  1, 1, 2, 0.001243, make_histogram(t_1_1_2  , expr, '', 'h_1_1_2'  , bounds) ), # node 3
        sample(  1, 2, 1, 0.012719, make_histogram(t_1_2_1  , expr, '', 'h_1_2_1'  , bounds) ), # node 4
        sample(1.5, 1, 1, 0.057943, make_histogram(t_1p5_1_1, expr, '', 'h_1p5_1_1', bounds) ), # node 5
        sample( -2, 0, 4, 0.882721, make_histogram(t_m2_0_4 , expr, '', 'h_m2_0_4' , bounds) ), # node 7
    ]

elif nRew == 15:
    rew_list = [
        sample(  1, 1, 1, 0.001499, make_histogram(t_1_1_1  , expr, '', 'h_1_1_1'  , bounds) ), # node 1
        sample(  1, 1, 0, 0.003947, make_histogram(t_1_1_0  , expr, '', 'h_1_1_0'  , bounds) ), # node 2
        sample(  1, 1, 2, 0.001243, make_histogram(t_1_1_2  , expr, '', 'h_1_1_2'  , bounds) ), # node 3
        sample(  1, 2, 1, 0.012719, make_histogram(t_1_2_1  , expr, '', 'h_1_2_1'  , bounds) ), # node 4
        sample(1.5, 1, 1, 0.057943, make_histogram(t_1p5_1_1, expr, '', 'h_1p5_1_1', bounds) ), # node 5
        sample(  2,-1,-1, 0.799476, make_histogram(t_2_m1_m1, expr, '', 'h_2_m1_,1', bounds) ), # node 8
    ]

elif nRew == 16:
    rew_list = [
        sample(  1,  1,  1, 0.001499, make_histogram(t_1_1_1   , expr, '', 'h_1_1_1'   , bounds) ), # node 1
        sample(  1,  1,  0, 0.003947, make_histogram(t_1_1_0   , expr, '', 'h_1_1_0'   , bounds) ), # node 2
        sample(  1,  1,  2, 0.001243, make_histogram(t_1_1_2   , expr, '', 'h_1_1_2'   , bounds) ), # node 3
        sample(  1,  2,  1, 0.012719, make_histogram(t_1_2_1   , expr, '', 'h_1_2_1'   , bounds) ), # node 4
        sample(1.5,  1,  1, 0.057943, make_histogram(t_1p5_1_1 , expr, '', 'h_1p5_1_1' , bounds) ), # node 5
        sample( -1, -1, -1, 0.079882, make_histogram(t_m1_m1_m1, expr, '', 'h_m1_m1_m1', bounds) ), # node 9
    ]

elif nRew == 17:
    rew_list = [
        sample(  1, 1, 1, 0.001499, make_histogram(t_1_1_1  , expr, '', 'h_1_1_1'  , bounds) ), # node 1
        sample(  1, 1, 0, 0.003947, make_histogram(t_1_1_0  , expr, '', 'h_1_1_0'  , bounds) ), # node 2
        sample(  1, 1, 2, 0.001243, make_histogram(t_1_1_2  , expr, '', 'h_1_1_2'  , bounds) ), # node 3
        sample(  1, 2, 1, 0.012719, make_histogram(t_1_2_1  , expr, '', 'h_1_2_1'  , bounds) ), # node 4
        sample(1.5, 1, 1, 0.057943, make_histogram(t_1p5_1_1, expr, '', 'h_1p5_1_1', bounds) ), # node 5
        sample(  4, 0, 0, 8.209257, make_histogram(t_4_0_0  , expr, '', 'h_4_0_0'  , bounds) ), # node 10
    ]

#---------

elif nRew == 18:
    rew_list = [
        sample(  1, 1, 1, 0.001499, make_histogram(t_1_1_1  , expr, '', 'h_1_1_1'  , bounds) ), # node 1
        sample(  1, 1, 0, 0.003947, make_histogram(t_1_1_0  , expr, '', 'h_1_1_0'  , bounds) ), # node 2
        sample(  1, 1, 2, 0.001243, make_histogram(t_1_1_2  , expr, '', 'h_1_1_2'  , bounds) ), # node 3
        sample(  1, 2, 1, 0.012719, make_histogram(t_1_2_1  , expr, '', 'h_1_2_1'  , bounds) ), # node 4
        sample(1.5, 1, 1, 0.057943, make_histogram(t_1p5_1_1, expr, '', 'h_1p5_1_1', bounds) ), # node 5
        sample(  1, 0, 1,  0.02388, make_histogram(t_1_0_1  , expr, '', 'h_1_0_1'  , bounds) ),  # node 14
    ]

elif nRew == 19:
    rew_list = [
        sample(  1, 1, 1, 0.001499, make_histogram(t_1_1_1  , expr, '', 'h_1_1_1'  , bounds) ), # node 1
        sample(  1, 1, 0, 0.003947, make_histogram(t_1_1_0  , expr, '', 'h_1_1_0'  , bounds) ), # node 2
        sample(  1, 1, 2, 0.001243, make_histogram(t_1_1_2  , expr, '', 'h_1_1_2'  , bounds) ), # node 3
        sample(  1, 2, 1, 0.012719, make_histogram(t_1_2_1  , expr, '', 'h_1_2_1'  , bounds) ), # node 4
        sample(1.5, 1, 1, 0.057943, make_histogram(t_1p5_1_1, expr, '', 'h_1p5_1_1', bounds) ), # node 5
        sample(  1, 4, 1,   0.1358, make_histogram(t_1_4_1  , expr, '', 'h_1_4_1'  , bounds) ), # node 15
    ]

elif nRew == 20:
    rew_list = [
        sample(  1,  1, 1, 0.001499, make_histogram(t_1_1_1  , expr, '', 'h_1_1_1'  , bounds) ), # node 1
        sample(  1,  1, 0, 0.003947, make_histogram(t_1_1_0  , expr, '', 'h_1_1_0'  , bounds) ), # node 2
        sample(  1,  1, 2, 0.001243, make_histogram(t_1_1_2  , expr, '', 'h_1_1_2'  , bounds) ), # node 3
        sample(  1,  2, 1, 0.012719, make_histogram(t_1_2_1  , expr, '', 'h_1_2_1'  , bounds) ), # node 4
        sample(1.5,  1, 1, 0.057943, make_histogram(t_1p5_1_1, expr, '', 'h_1p5_1_1', bounds) ), # node 5
        sample(  1, -2, 1,   0.1692, make_histogram(t_1_m2_1 , expr, '', 'h_1_m2_1' , bounds) ), # node 16
    ]


# Target sample
nTarget = args.nTarget
if  nTarget == 1:
    h_target = make_histogram(t_1_1_1, expr, '', 'h_1_1_1', bounds)
    xs_target = 0.001499
    t_CV  = 1
    t_C2V = 1
    t_kl  = 1
    title = 'sumRew - target node1: cV,c2V,kl=(1,1,1)'

elif nTarget == 21:
    h_target = make_histogram(t_3_2_4, expr, '', 'h_3_2_4', bounds)
    xs_target = 1.144
    t_CV  = 3
    t_C2V = 2
    t_kl  = 4
    title = 'nRew: '+str(nRew)+' - target node21: cV,c2V,kl=(3,2,4)'


print '-------------------------'
print "Using reweighting number :", nRew

#Print target coefficients and xs
scaleTo(h_target, xs_target)
print "Target sigma        : ", xs_target
print "Target couplings: CV = ", t_CV, " C2V =  ", t_C2V, " kl = ", t_kl

# Get final cross section and modelled histogram
tot_sigma, h_total = get_total_xs_and_histo(rew_list)

print "Final modeled sigma :", tot_sigma
print "Modelled integral   :", h_total.Integral()
print "Target integral     :", h_target.Integral()

# Get the components histograms
h_0 = rew_list[0].histo
h_1 = rew_list[1].histo
h_2 = rew_list[2].histo
h_3 = rew_list[3].histo
h_4 = rew_list[4].histo
h_5 = rew_list[5].histo

# Drawing section
h_total.SetLineColor(ROOT.kRed)
h_total.SetFillColor(ROOT.kRed)
h_total.SetFillStyle(3002)
h_target.SetLineColor(ROOT.kBlack)
h_target.SetLineWidth(2)
h_target.SetMarkerStyle(8)
h_target.SetMarkerSize(0.4)

if not drawCompts:
    mmin = min(h_total.GetMinimum(), h_target.GetMinimum())
    mmax = max(h_total.GetMaximum(), h_target.GetMaximum())
else:
    mmin = min(h_total.GetMinimum(), h_target.GetMinimum(), h_0.GetMinimum(), h_1.GetMinimum(), h_2.GetMinimum(), h_3.GetMinimum(), h_4.GetMinimum(), h_5.GetMinimum())
    mmax = max(h_total.GetMaximum(), h_target.GetMaximum(), h_0.GetMaximum(), h_1.GetMaximum(), h_2.GetMaximum(), h_3.GetMaximum(), h_4.GetMaximum(), h_5.GetMaximum())


h_total.SetMaximum(1.15*mmax)
h_total.SetMinimum(0 if mmin > 0 else 1.15*mmin)

h_total.SetTitle(title)
h_total.SetTitleSize(0.1,'z')
h_total.Draw('hist')
h_target.Draw('pe same')

h_0.SetLineColor(ROOT.kBlue)
h_1.SetLineColor(ROOT.kGreen+1)
h_2.SetLineColor(ROOT.kOrange)
h_3.SetLineColor(ROOT.kViolet)
h_4.SetLineColor(ROOT.kCyan)
h_5.SetLineColor(ROOT.kMagenta)

h_0.SetLineWidth(2)
h_1.SetLineWidth(2)
h_2.SetLineWidth(2)
h_3.SetLineWidth(2)
h_4.SetLineWidth(2)
h_5.SetLineWidth(2)

if drawCompts:
    h_0.Draw('same')
    h_1.Draw('same')
    h_2.Draw('same')
    h_3.Draw('same')
    h_4.Draw('same')
    h_5.Draw('same')


leg = ROOT.TLegend(0.55, 0.70, 0.88, 0.90)
leg.SetFillStyle(0)
leg.SetBorderSize(0)
leg.SetNColumns(2)
if drawCompts:
    leg.AddEntry(h_0, h_0.GetName(), 'lp')
    leg.AddEntry(h_1, h_1.GetName(), 'lp')
    leg.AddEntry(h_2, h_2.GetName(), 'lp')
    leg.AddEntry(h_3, h_3.GetName(), 'lp')
    leg.AddEntry(h_4, h_4.GetName(), 'lp')
    leg.AddEntry(h_4, h_5.GetName(), 'lp')

leg.AddEntry(h_total, 'Modelling', 'lp')
leg.AddEntry(None, '', '')
leg.AddEntry(h_target, 'Sample', 'lp')
leg.AddEntry(None, '', '')

leg.Draw()
c1.Update()

if makeRatioPlot:

    h_total.GetXaxis().SetTitleSize(0.00);
    h_total.GetXaxis().SetLabelSize(0.00);

    c1.cd()
    pad2 = ROOT.TPad ("pad2", "pad2", 0, 0.0, 1, 0.2496)
    pad2.SetLeftMargin(0.12);
    pad2.SetTopMargin(0.02);
    pad2.SetBottomMargin(0.3);
    pad2.SetGridy(True);
    pad2.SetFrameLineWidth(3)
    #pad2.SetGridx(True);
    pad2.Draw()
    pad2.cd()

    ratioPlot = makeDataOverMCRatioPlot (h_total, h_target, "grRatio", horErrs=False)
    
    titleSize = 18
    labelSize = 16

    hRatio = h_total.Clone("hRatioAxis") # for ranges only
    hRatio.GetXaxis().SetTitleFont(43) # so that size is in pixels
    hRatio.GetYaxis().SetTitleFont(43) # so that size is in pixels
    hRatio.GetXaxis().SetLabelFont(43) # so that size is in pixels
    hRatio.GetYaxis().SetLabelFont(43) # so that size is in pixels
    hRatio.GetYaxis().SetNdivisions(505)
    hRatio.SetTitle("")
    #hRatio.GetYaxis().SetTitle ("total/target")
    hRatio.GetYaxis().SetTitle ("modelling/sample")
    hRatio.GetXaxis().SetTitle ("mHH [GeV]")
    hRatio.GetXaxis().SetTitleOffset(3.9)
    hRatio.GetYaxis().SetTitleOffset(1.2)

    hRatio.GetXaxis().SetTitleSize(titleSize);
    hRatio.GetXaxis().SetLabelSize(labelSize);
    hRatio.GetYaxis().SetTitleSize(titleSize);
    hRatio.GetYaxis().SetLabelSize(labelSize);

    hRatio.GetXaxis().SetTickSize(0.10)
    hRatio.GetYaxis().SetTickSize(0.05)
    hRatio.SetStats(0)
    hRatio.SetMinimum(0.0) #default value
    hRatio.SetMaximum(+2.) #default value

    hRatio.Draw("axis")
    ratioPlot.Draw("P Z same")

    pad2.RedrawAxis();
    pad2.RedrawAxis("g"); #otherwise no grid..

    c1.Update()

c1.Print('sum_scan/sumRew_node'+str(nTarget)+'_rew'+str(nRew)+'.pdf','pdf')
print '-------------------------'


