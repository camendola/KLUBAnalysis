import ROOT
import sys
import numpy as np
from array import array

# rew_CV_1_C2V_1_C3_1    - node 1
#  Integrated weight (pb)  :       0.00149992979981

# rew_CV_1_C2V_1_C3_0    - node 2
#  Integrated weight (pb)  :       0.003947772581

# rew_CV_1_C2V_1_C3_2    - node 3
#  Integrated weight (pb)  :       0.0012432333494

# rew_CV_1_C2V_2_C3_1    - node 4
#  Integrated weight (pb)  :       0.0127194756702

# rew_CV_1_5_C2V_1_C3_1  - node 5
#  Integrated weight (pb)  :       0.0579439534956

# rew_CV_0p5_C2V_1_C3_1   - node 6  ---> !! NOT PRODUCED !!

# rew_CV_m2_C2V_0_C3_4   - node 7
#  Integrated weight (pb)  :       0.88272145511

# rew_CV_2_C2V_m1_C3_m1  - node 8
#  Integrated weight (pb)  :       0.799476107975

# rew_CV_m1_C2V_m1_C3_m1 - node 9
#  Integrated weight (pb)  :       0.079882616707

# rew_CV_4_C2V_0_C3_0    - node 10
#  Integrated weight (pb)  :       8.209257197

# rew_CV_1_C2V_1_C3_4    - node 11
#  Integrated weight (pb)  :       0.007305

# rew_CV_1_C2V_1_C3_m2    - node 12
#  Integrated weight (pb)  :       0.01543

# rew_CV_1_C2V_1_C3_m4    - node 13
#  Integrated weight (pb)  :       0.03568

# rew_CV_1_C2V_0_C3_1    - node 14
#  Integrated weight (pb)  :       0.02388

# rew_CV_1_C2V_4_C3_1    - node 15
#  Integrated weight (pb)  :       0.1358

# rew_CV_1_C2V_m2_C3_1   - node 16
#  Integrated weight (pb)  :       0.1692

# rew_CV_1_C2V_0_C3_0    - node 17
#  Integrated weight (pb)  :       0.03209

# rew_CV_0_C2V_1_C3_0    - node 18
#  0p001_1_0p001     --> Integrated weight (pb)  : 0.01677 +- 1.598e-05 pb
#  0p00001_1_0p00001 --> Integrated weight (pb)  : 0.01679 +- 1.435e-05 pb

# rew_CV_1_C2V_0_C3_2    - node 19
#  Integrated weight (pb)  :       0.0178

# rew_CV_2_C2V_1_C3_1          - node 20
#  Integrated weight (pb)  :       0.2918

# rew_CV_3_C2V_2_C3_4          - node 21
#  Integrated weight (pb)  :       1.144

# rew_CV_1p5_C2V_m2p5_C3_m1p5  - node 22
#  Integrated weight (pb)  :       0.6047

# rew_CV_1_C2V_4p5_C3_m2       - node 23
#  Integrated weight (pb)  :       0.1407

# rew_CV_1_C2V_0_C3_2000       - node 24
#  Integrated weight (pb)  :       4368



def CheckBit (number, bitpos):
    res = number & (1 << bitpos)
    if res > 0:
        return 1
    else:
        return 0

# Can retrieve histograms from LLR "big-ntuples"
def make_histogram_from_bigntuples (tIn, hname, maxevts):
    print hname, 'entries:', tIn.GetEntries(), ' - reduced to:', maxevts
    binning_mHH = [ 250,260,270,280,290,300,310,320,330,340,350,360,370,380,390,400,410,420,430,440,450,460,470,480,490,500,510,520,530,540,550,600,610,620,630,640,650,660,670,680,690,700,750,800,850,900,950,1000,1100,1200,1300,1400,1500.,1750,2000]
    hMap1D = ROOT.TH1F('mHH_Map1D','mHH_Map1D',len(binning_mHH)-1,np.asarray(binning_mHH, 'f'))
    for i,evt in enumerate(tIn):
        if i==maxevts: break
        if i%5000 == 0: print ' - Processing entry:', i
        idx1 = -1
        idx2 = -1
        vH1 = ROOT.TLorentzVector()
        vH2 = ROOT.TLorentzVector()
        vSum = ROOT.TLorentzVector()
        for igen in range(int(evt.genpart_px.size())):
            if evt.genpart_pdg.at(igen) == 25:
                isFirst = CheckBit(evt.genpart_flags.at(igen), 12)
                if isFirst:
                    if idx1 >= 0 and idx2 >= 0:
                        print "** ERROR: more than 2 H identified "
                        continue
                    if idx1 == -1:
                        idx1 = igen
                    else:
                        idx2 = igen
            
        if idx1 == -1 or idx2 == -1:
            print "** ERROR: couldn't find 2 H"
            continue
        else:
            vH1.SetPxPyPzE(evt.genpart_px.at(idx1),evt.genpart_py.at(idx1),evt.genpart_pz.at(idx1),evt.genpart_e.at(idx1))
            vH2.SetPxPyPzE(evt.genpart_px.at(idx2),evt.genpart_py.at(idx2),evt.genpart_pz.at(idx2),evt.genpart_e.at(idx2))
            vSum = vH1 + vH2
            mHH = vSum.M()
            hMap1D.Fill(mHH)

    return hMap1D

# Make histogram from LHE ntuples
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

def get_composed_h(hListIn, oname, norm):
    """ hListIn is a iterable of elements (histogram, weight) """
    for idx, el in enumerate(hListIn):
        if idx == 0:
            hout = el[0].Clone(oname)
            hout.Scale(el[1])
        else:
            hout.Add(el[0], el[1])
    hout.SetDirectory(0)
    hout.Scale(norm/hout.Integral())
    return hout


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


############# MAIN #############

ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

silent = False
if len(sys.argv) > 2:
    if int(sys.argv[2]) == 0:
        silent = True
if silent:
    ROOT.gROOT.SetBatch(True)

c1 = ROOT.TCanvas('c1', 'c1', 600, 600)
c1.SetFrameLineWidth(3)

pad1 = None
pad2 = None

makeRatioPlot = False

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


t_1_1_1    = f_1_1_1    .Get('lheTree')
t_1_1_0    = f_1_1_0    .Get('lheTree')
t_1_1_2    = f_1_1_2    .Get('lheTree')
t_1_2_1    = f_1_2_1    .Get('lheTree')
t_1p5_1_1  = f_1p5_1_1  .Get('lheTree')
t_m2_0_4   = f_m2_0_4   .Get('lheTree')
t_2_m1_m1  = f_2_m1_m1  .Get('lheTree')
t_m1_m1_m1 = f_m1_m1_m1 .Get('lheTree')
t_4_0_0    = f_4_0_0    .Get('lheTree')
t_1_1_4    = f_1_1_4    .Get('lheTree')
t_1_1_m2   = f_1_1_m2   .Get('lheTree')
t_1_1_m4   = f_1_1_m4   .Get('lheTree')
t_1_0_1    = f_1_0_1    .Get('lheTree')
t_1_4_1    = f_1_4_1    .Get('lheTree')
t_1_m2_1   = f_1_m2_1   .Get('lheTree')
t_1_0_0    = f_1_0_0    .Get('lheTree')
t_0_1_0    = f_0_1_0    .Get('lheTree')
t_1_0_2    = f_1_0_2    .Get('lheTree')
t_2_1_1         = f_2_1_1        .Get('lheTree')
t_3_2_4         = f_3_2_4        .Get('lheTree')
t_1p5_m2p5_m1p5 = f_1p5_m2p5_m1p5.Get('lheTree')
t_1_4p5_m2      = f_1_4p5_m2     .Get('lheTree')
t_1_0_2000      = f_1_0_2000     .Get('lheTree')


# Get the histograms
bounds = '200, 250, 1250'
expr = 'HH_mass'
h_1_1_1         = make_histogram(t_1_1_1   , expr, '', 'h_1_1_1'   , bounds) # 1
h_1_1_0         = make_histogram(t_1_1_0   , expr, '', 'h_1_1_0'   , bounds) # 2
h_1_1_2         = make_histogram(t_1_1_2   , expr, '', 'h_1_1_2'   , bounds) # 3
h_1_2_1         = make_histogram(t_1_2_1   , expr, '', 'h_1_2_1'   , bounds) # 4
h_1p5_1_1       = make_histogram(t_1p5_1_1 , expr, '', 'h_1p5_1_1' , bounds) # 5
h_m2_0_4        = make_histogram(t_m2_0_4  , expr, '', 'h_m2_0_4'  , bounds) # 7
h_2_m1_m1       = make_histogram(t_2_m1_m1 , expr, '', 'h_2_m1_m1' , bounds) # 8
h_m1_m1_m1      = make_histogram(t_m1_m1_m1, expr, '', 'h_m1_m1_m1', bounds) # 9
h_4_0_0         = make_histogram(t_4_0_0   , expr, '', 'h_4_0_0'   , bounds) # 10
h_1_1_4         = make_histogram(t_1_1_4   , expr, '', 'h_1_1_4'   , bounds) # 11
h_1_1_m2        = make_histogram(t_1_1_m2  , expr, '', 'h_1_1_m2'  , bounds) # 12
h_1_1_m4        = make_histogram(t_1_1_m4  , expr, '', 'h_1_1_m4'  , bounds) # 13
h_1_0_1         = make_histogram(t_1_0_1   , expr, '', 'h_1_0_1'   , bounds) # 14
h_1_4_1         = make_histogram(t_1_4_1   , expr, '', 'h_1_4_1'   , bounds) # 15
h_1_m2_1        = make_histogram(t_1_m2_1  , expr, '', 'h_1_m2_1'  , bounds) # 16
h_1_0_0         = make_histogram(t_1_0_0   , expr, '', 'h_1_0_0'   , bounds) # 17
h_0_1_0         = make_histogram(t_0_1_0   , expr, '', 'h_0_1_0'   , bounds) # 18
h_1_0_2         = make_histogram(t_1_0_2   , expr, '', 'h_1_0_2'   , bounds) # 19
h_2_1_1         = make_histogram(t_2_1_1        , expr, '', 'h_2_1_1'        , bounds) # 20
h_3_2_4         = make_histogram(t_3_2_4        , expr, '', 'h_3_2_4'        , bounds) # 21
h_1p5_m2p5_m1p5 = make_histogram(t_1p5_m2p5_m1p5, expr, '', 'h_1p5_m2p5_m1p5', bounds) # 22
h_1_4p5_m2      = make_histogram(t_1_4p5_m2     , expr, '', 'h_1_4p5_m2'     , bounds) # 23
h_1_0_2000      = make_histogram(t_1_0_2000     , expr, '', 'h_1_0_2000'     , bounds) # 24


# XSs and scaling of signals
xs_1_1_1         = 0.00149992979981
xs_1_1_0         = 0.003947772581
xs_1_1_2         = 0.0012432333494
xs_1_2_1         = 0.0127194756702
xs_1p5_1_1       = 0.0579439534956
xs_m2_0_4        = 0.88272145511
xs_2_m1_m1       = 0.799476107975
xs_m1_m1_m1      = 0.079882616707
xs_4_0_0         = 8.209257197
xs_1_1_4         = 0.007305
xs_1_1_m2        = 0.01543
xs_1_1_m4        = 0.03568
xs_1_0_1         = 0.02388
xs_1_4_1         = 0.1358
xs_1_m2_1        = 0.1692
xs_1_0_0         = 0.03209
xs_0_1_0         = 0.01679
xs_1_0_2         = 0.0178
xs_2_1_1         = 0.2918
xs_3_2_4         = 1.144
xs_1p5_m2p5_m1p5 = 0.6047
xs_1_4p5_m2      = 0.1407
xs_1_0_2000      = 4368


h_1_1_1        .Scale ( xs_1_1_1    / h_1_1_1.Integral()    )
h_1_1_0        .Scale ( xs_1_1_0    / h_1_1_0.Integral()    )
h_1_1_2        .Scale ( xs_1_1_2    / h_1_1_2.Integral()    )
h_1_2_1        .Scale ( xs_1_2_1    / h_1_2_1.Integral()    )
h_1p5_1_1      .Scale ( xs_1p5_1_1  / h_1p5_1_1.Integral()  )
h_m2_0_4       .Scale ( xs_m2_0_4   / h_m2_0_4.Integral()   )
h_2_m1_m1      .Scale ( xs_2_m1_m1  / h_2_m1_m1.Integral()  )
h_m1_m1_m1     .Scale ( xs_m1_m1_m1 / h_m1_m1_m1.Integral() )
h_4_0_0        .Scale ( xs_4_0_0    / h_4_0_0.Integral()    )
h_1_1_4        .Scale ( xs_1_1_4    / h_1_1_4.Integral()    )
h_1_1_m2       .Scale ( xs_1_1_m2   / h_1_1_m2.Integral()   )
h_1_1_m4       .Scale ( xs_1_1_m4   / h_1_1_m4.Integral()   )
h_1_0_1        .Scale ( xs_1_0_1    / h_1_0_1.Integral()    )
h_1_4_1        .Scale ( xs_1_4_1    / h_1_4_1.Integral()    )
h_1_m2_1       .Scale ( xs_1_m2_1   / h_1_m2_1.Integral()   )
h_1_0_0        .Scale ( xs_1_0_0    / h_1_0_0.Integral()    )
h_0_1_0        .Scale ( xs_0_1_0    / h_0_1_0.Integral()    )
h_1_0_2        .Scale ( xs_1_0_2    / h_1_0_2.Integral()    )
h_2_1_1        .Scale ( xs_2_1_1         / h_2_1_1.Integral()         )
h_3_2_4        .Scale ( xs_3_2_4         / h_3_2_4.Integral()         )
h_1p5_m2p5_m1p5.Scale ( xs_1p5_m2p5_m1p5 / h_1p5_m2p5_m1p5.Integral() )
h_1_4p5_m2     .Scale ( xs_1_4p5_m2      / h_1_4p5_m2.Integral()      )
h_1_0_2000     .Scale ( xs_1_0_2000      / h_1_0_2000.Integral()      )


################################################

ntest = 999
if len(sys.argv) > 1:
    ntest = int(sys.argv[1])
nRew = 1
if len(sys.argv) > 2:
    nRew = int(sys.argv[2])

# node1 StandardModel
if ntest == 1:
    print '--> TARGET: node 1 cV,c2V,kl=(1,1,1)'
    cv  = 1
    c2v = 1
    kl  = 1
    title = 'full scan - target node 1 cV,c2V,kl=(1,1,1)'
    h_target = h_1_1_1.Clone('h_target')
    xs_target = xs_1_1_1
    oname = 'full_scan_target_node1_rew'+str(nRew)+'.pdf'

# node3 incluso nel sistema
elif ntest == 3:
    print '--> TARGET: node 3 cV,c2V,kl=(1,1,2)'
    cv  = 1
    c2v = 1
    kl  = 2
    title = 'full scan - target node 3 cV,c2V,kl=(1,1,2)'
    h_target = h_1_1_2.Clone('h_target')
    xs_target = xs_1_1_2
    oname = 'full_scan_target_node3_rew'+str(nRew)+'.pdf'

# node7 molto diverso da tutto
elif ntest == 7:
    print '--> TARGET: node 7 cV,c2V,kl=(-2,0,4)'
    cv  = -2
    c2v = 0
    kl  = 4
    title = 'full scan - target node 7 cV,c2V,kl=(-2,0,4)'
    h_target = h_m2_0_4.Clone('h_target')
    xs_target = xs_m2_0_4
    oname = 'full_scan_target_node7_rew'+str(nRew)+'.pdf'

# node11 simile al sistema
elif ntest == 11:
    print '--> TARGET: node 11 cV,c2V,kl=(1,1,4)'
    cv  = 1
    c2v = 1
    kl  = 4
    title = 'full scan - target node 11 cV,c2V,kl=(1,1,4)'
    h_target = h_1_1_4.Clone('h_target')
    xs_target = xs_1_1_4
    oname = 'full_scan_target_node11_rew'+str(nRew)+'.pdf'

# node12 simile al sistema
elif ntest == 12:
    print '--> TARGET: node 12 cV,c2V,kl=(1,1,-2)'
    cv  = 1
    c2v = 1
    kl  = -2
    title = 'full scan - target node 12 cV,c2V,kl=(1,1,-2)'
    h_target = h_1_1_m2.Clone('h_target')
    xs_target = xs_1_1_m2
    oname = 'full_scan_target_node12_rew'+str(nRew)+'.pdf'

# node13 simile al sistema
elif ntest == 13:
    print '--> TARGET: node 13 cV,c2V,kl=(1,1,-4)'
    cv  = 1
    c2v = 1
    kl  = -4
    title = 'full scan - target node 13 cV,c2V,kl=(1,1,-4)'
    h_target = h_1_1_m4.Clone('h_target')
    xs_target = xs_1_1_m4
    oname = 'full_scan_target_node13_rew'+str(nRew)+'.pdf'

# node15 ha c2v diverso
elif ntest == 15:
    print '--> TARGET: node 15 cV,c2V,kl=(1,4,1)'
    cv  = 1
    c2v = 4
    kl  = 1
    title = 'full scan - target node 15 cV,c2V,kl=(1,4,1)'
    h_target = h_1_4_1.Clone('h_target')
    xs_target = xs_1_4_1
    oname = 'full_scan_target_node15_rew'+str(nRew)+'.pdf'

# node5 ha cv diverso
elif ntest == 5:
    print '--> TARGET: node 5 cV,c2V,kl=(1.5,1,1)'
    cv  = 1.5
    c2v = 1
    kl  = 1
    title = 'full scan - target node 5 cV,c2V,kl=(1.5,1,1)'
    h_target = h_1p5_1_1.Clone('h_target')
    xs_target = xs_1p5_1_1
    oname = 'full_scan_target_node5_rew'+str(nRew)+'.pdf'

# node9 tutto negativo
elif ntest == 9:
    print '--> TARGET: node 9 cV,c2V,kl=(-1,-1,-1)'
    cv  = -1
    c2v = -1
    kl  = -1
    title = 'full scan - target node 9 cV,c2V,kl=(-1,-1,-1)'
    h_target = h_m1_m1_m1.Clone('h_target')
    xs_target = xs_m1_m1_m1
    oname = 'full_scan_target_node9_rew'+str(nRew)+'.pdf'

# node4 simile al sistema3
elif ntest == 4:
    print '--> TARGET: node 4 cV,c2V,kl=(1,2,1)'
    cv  = 1
    c2v = 2
    kl  = 1
    title = 'full scan - target node 4 cV,c2V,kl=(1,2,1)'
    h_target = h_1_2_1.Clone('h_target')
    xs_target = xs_1_2_1
    oname = 'full_scan_target_node4_rew'+str(nRew)+'.pdf'

# node16 simile al sistema3
elif ntest == 16:
    print '--> TARGET: node 16 cV,c2V,kl=(1,-2,1)'
    cv  = 1
    c2v = -2
    kl  = 1
    title = 'full scan - target node 16 cV,c2V,kl=(1,-2,1)'
    h_target = h_1_m2_1.Clone('h_target')
    xs_target = xs_1_m2_1
    oname = 'full_scan_target_node16_rew'+str(nRew)+'.pdf'


# node 20
elif ntest == 20:
    print '--> TARGET: node 20 cV,c2V,kl=(2,1,1)'
    cv  = 2
    c2v = 1
    kl  = 1
    title = 'full scan - target node 20 cV,c2V,kl=(2,1,1)'
    h_target = h_2_1_1.Clone('h_target')
    xs_target = xs_2_1_1
    oname = 'full_scan_target_node20_rew'+str(nRew)+'.pdf'

# node 21
elif ntest == 21:
    print '--> TARGET: node 21 cV,c2V,kl=(3,2,4)'
    cv  = 3
    c2v = 2
    kl  = 4
    title = 'full scan - target node 21 cV,c2V,kl=(3,2,4)'
    h_target = h_3_2_4.Clone('h_target')
    xs_target = xs_3_2_4
    oname = 'full_scan_target_node21_rew'+str(nRew)+'.pdf'

# node 22
elif ntest == 22:
    print '--> TARGET: node 22 cV,c2V,kl=(1.5,-2.5,-1.5)'
    cv  = 1.5
    c2v = -2.5
    kl  =-1.5
    title = 'full scan - target node 22 cV,c2V,kl=(1.5,-2.5,-1.5)'
    h_target = h_1p5_m2p5_m1p5.Clone('h_target')
    xs_target = xs_1p5_m2p5_m1p5
    oname = 'full_scan_target_node22_rew'+str(nRew)+'.pdf'

# node 23
elif ntest == 23:
    print '--> TARGET: node 23 cV,c2V,kl=(1,4.5,-2)'
    cv  = 1
    c2v = 4.5
    kl  = -2
    title = 'full scan - target node 23 cV,c2V,kl=(1,4.5,-2)'
    h_target = h_1_4p5_m2.Clone('h_target')
    xs_target = xs_1_4p5_m2
    oname = 'full_scan_target_node23_rew'+str(nRew)+'.pdf'

else:
    print "... please set a meaningful target test number"
    sys.exit()

print 'target cv  : ', cv
print 'target c2v : ', c2v
print 'target kl  : ', kl

###############################################

drawCompts = True

################################################

if nRew == 1:
    print '--> REWIGHTING: 1 - nodes 1,2,3,4,14,17'
    #              xs node1         xs node2         xs node3         xs node4         xs node14       xs node17
    xs_a   = -1. * xs_1_1_1 + 0.5 * xs_1_1_0 + 0.5 * xs_1_1_2
    xs_b   =                                                                                      1. * xs_1_0_0
    xs_c   = -1. * xs_1_1_1                                   + 0.5 * xs_1_2_1 + 0.5 * xs_1_0_1
    xs_iab =  1. * xs_1_1_1 - 0.5 * xs_1_1_0 - 0.5 * xs_1_1_2                  +  1. * xs_1_0_1 - 1. * xs_1_0_0
    xs_iac =  1. * xs_1_1_1 -  1. * xs_1_1_0                                   -  1. * xs_1_0_1 + 1. * xs_1_0_0
    xs_ibc =  1. * xs_1_1_1 +  1. * xs_1_1_0                  - 0.5 * xs_1_2_1 - 0.5 * xs_1_0_1 - 1. * xs_1_0_0

if nRew == 2:
    print '--> REWIGHTING: 2 - nodes 1,2,7,9,14,17'
    #              xs node1        xs node2              xs node7         xs node9               xs node14            xs node17
    xs_a   =                                  (1./96.) * xs_m2_0_4                    + (1./3.) * xs_1_0_1 + (1./6.) * xs_1_0_0
    xs_b   =                                                                                                    + 1. * xs_1_0_0
    xs_c   =  1. * xs_1_1_1                                        + 1. * xs_m1_m1_m1      - 2. * xs_1_0_1
    xs_iab =                                - (1./96.) * xs_m2_0_4                    + (2./3.) * xs_1_0_1 - (7./6.) * xs_1_0_0
    xs_iac =  1. * xs_1_1_1 - 1. * xs_1_1_0                                                 -1. * xs_1_0_1      + 1. * xs_1_0_0
    xs_ibc = -1. * xs_1_1_1 + 1. * xs_1_1_0                        - 1. * xs_m1_m1_m1      + 2. * xs_1_0_1      - 1. * xs_1_0_0

if nRew == 3:
    print '--> REWIGHTING: 3 - nodes 1,2,14,17,18,19 (LUCA)'
    #              xs node1       xs node2         xs node14            xs node17        xs node18          xs node19
    xs_a   =                                - 1. * xs_1_0_1     + 0.5 * xs_1_0_0                    + 0.5 * xs_1_0_2
    xs_b   =                                                       1. * xs_1_0_0
    xs_c   =                                                                        1. * xs_0_1_0
    xs_iab =                                  2. * xs_1_0_1 - (3./2.) * xs_1_0_0                    - 0.5 * xs_1_0_2
    xs_iac = 1. * xs_1_1_1 - 1. * xs_1_1_0  - 1. * xs_1_0_1      + 1. * xs_1_0_0
    xs_ibc =                 1. * xs_1_1_0                       - 1. * xs_1_0_0  - 1. * xs_0_1_0

if nRew == 4:
    print '--> REWIGHTING: 4 - same as 3 but different'
    xs_b   = xs_1_0_0
    xs_c   = xs_0_1_0
    xs_ibc = xs_1_1_0 - xs_b - xs_c
    xs_iac = xs_1_1_1 - xs_1_1_0 - xs_1_0_1 + xs_b
    xs_iab = 2. * xs_1_0_1 -1.5 * xs_b -0.5 * xs_1_0_2
    xs_a   = 0.5 * xs_b - xs_1_0_1 +0.5 * xs_1_0_2

if nRew == 5:
    print '--> REWIGHTING: 5 - exactly as luca'
    xs_b   = xs_1_0_0
    xs_c   = xs_0_1_0
    xs_a   = 0.5 * (xs_1_0_2 - 2.*xs_1_0_1 + xs_1_0_0)
    xs_iab = xs_1_0_1 - xs_a - xs_b
    xs_ibc = xs_1_1_0 - xs_b - xs_c
    xs_iac = xs_1_1_1 - xs_a - xs_b - xs_c - xs_iab - xs_ibc

if nRew == 6:
    print '--> REWIGHTING: 6 - nodes 1,2,14,17,18,19 (LUCA)'
    #              xs node1       xs node2         xs node14            xs node17        xs node18          xs node19
    xs_a   =                                - 1. * xs_1_0_1     + 0.5 * xs_1_0_0                    + 0.5 * xs_1_0_2
    xs_b   =                                                       1. * xs_1_0_0
    xs_c   =                                                                        1. * xs_0_1_0
    xs_iab =                                  2. * xs_1_0_1 - (3./2.) * xs_1_0_0                    - 0.5 * xs_1_0_2
    xs_iac = 1. * xs_1_1_1 - 1. * xs_1_1_0  - 1. * xs_1_0_1      + 1. * xs_1_0_0
    xs_ibc =                 1. * xs_1_1_0                       - 1. * xs_1_0_0  - 1. * xs_0_1_0



################################################

# scale xs by enhancement
xs_A   = (cv**2) * (kl**2) * xs_a
xs_B   = (cv**4) * xs_b
xs_C   = (c2v**2) * xs_c
xs_Iab = (cv**3) * (kl) * xs_iab
xs_Iac = (cv) * (c2v) * (kl) * xs_iac
xs_Ibc = (cv**2) * (c2v) * xs_ibc

'''
print 'xs_a', xs_a
print 'xs_b', xs_b
print 'xs_c', xs_c
print 'xs_iab', xs_iab
print 'xs_iac', xs_iac
print 'xs_ibc', xs_ibc
print 'xs_A', xs_A
print 'xs_B', xs_B
print 'xs_C', xs_C
print 'xs_Iab', xs_Iab
print 'xs_Iac', xs_Iac
print 'xs_Ibc', xs_Ibc
'''

################################################

if nRew == 1:
    #                      xs node1         xs node2         xs node3         xs node4         xs node14       xs node17
    h_a   = get_composed_h([(h_1_1_1, -1.), (h_1_1_0,  0.5), (h_1_1_2,  0.5), (h_1_2_1,   0.), (h_1_0_1,   0.), (h_1_0_0,  0.)], 'h_a'  , xs_a)
    h_b   = get_composed_h([(h_1_1_1,  0.), (h_1_1_0,   0.), (h_1_1_2,   0.), (h_1_2_1,   0.), (h_1_0_1,   0.), (h_1_0_0,  1.)], 'h_b'  , xs_b)
    h_c   = get_composed_h([(h_1_1_1, -1.), (h_1_1_0,   0.), (h_1_1_2,   0.), (h_1_2_1,  0.5), (h_1_0_1,  0.5), (h_1_0_0,  0.)], 'h_c'  , xs_c)
    h_iab = get_composed_h([(h_1_1_1,  1.), (h_1_1_0, -0.5), (h_1_1_2, -0.5), (h_1_2_1,   0.), (h_1_0_1,   1.), (h_1_0_0, -1.)], 'h_iab', xs_iab)
    h_iac = get_composed_h([(h_1_1_1,  1.), (h_1_1_0,  -1.), (h_1_1_2,   0.), (h_1_2_1,   0.), (h_1_0_1,  -1.), (h_1_0_0,  1.)], 'h_iac', xs_iac)
    h_ibc = get_composed_h([(h_1_1_1,  1.), (h_1_1_0,   1.), (h_1_1_2,   0.), (h_1_2_1, -0.5), (h_1_0_1, -0.5), (h_1_0_0, -1.)], 'h_ibc', xs_ibc)

if nRew == 2:
    #                      xs node1         xs node2         xs node7             xs node9           xs node14           xs node17
    h_a   = get_composed_h([(h_1_1_1,  0.), (h_1_1_0,  0.), (h_m2_0_4,  (1./96)), (h_m1_m1_m1,  0.), (h_1_0_1, (1./3.)), (h_1_0_0,  (1./6.))], 'h_a'  , xs_a)
    h_b   = get_composed_h([(h_1_1_1,  0.), (h_1_1_0,  0.), (h_m2_0_4,       0.), (h_m1_m1_m1,  0.), (h_1_0_1,      0.), (h_1_0_0,       1.)], 'h_b'  , xs_b)
    h_c   = get_composed_h([(h_1_1_1,  1.), (h_1_1_0,  0.), (h_m2_0_4,       0.), (h_m1_m1_m1,  1.), (h_1_0_1,     -2.), (h_1_0_0,       0.)], 'h_c'  , xs_c)
    h_iab = get_composed_h([(h_1_1_1,  0.), (h_1_1_0,  0.), (h_m2_0_4, -(1./96)), (h_m1_m1_m1,  0.), (h_1_0_1, (2./3.)), (h_1_0_0, -(7./6.))], 'h_iab', xs_iab)
    h_iac = get_composed_h([(h_1_1_1,  1.), (h_1_1_0, -1.), (h_m2_0_4,       0.), (h_m1_m1_m1,  0.), (h_1_0_1,     -1.), (h_1_0_0,       1.)], 'h_iac', xs_iac)
    h_ibc = get_composed_h([(h_1_1_1, -1.), (h_1_1_0,  1.), (h_m2_0_4,       0.), (h_m1_m1_m1, -1.), (h_1_0_1,      2.), (h_1_0_0,      -1.)], 'h_ibc', xs_ibc)

if nRew == 3:
    #                       xs node1       xs node2        xs node14       xs node17            xs node18       xs node19
    h_a   = get_composed_h([(h_1_1_1, 0.), (h_1_1_0,  0.), (h_1_0_1, -1.), (h_1_0_0,      0.5), (h_0_1_0,  0.), (h_1_0_2,  0.5)], 'h_a'  , xs_a)
    h_b   = get_composed_h([(h_1_1_1, 0.), (h_1_1_0,  0.), (h_1_0_1,  0.), (h_1_0_0,       1.), (h_0_1_0,  0.), (h_1_0_2,   0.)], 'h_b'  , xs_b)
    h_c   = get_composed_h([(h_1_1_1, 0.), (h_1_1_0,  0.), (h_1_0_1,  0.), (h_1_0_0,       0.), (h_0_1_0,  1.), (h_1_0_2,   0.)], 'h_c'  , xs_c)
    h_iab = get_composed_h([(h_1_1_1, 0.), (h_1_1_0,  0.), (h_1_0_1,  2.), (h_1_0_0, -(3./2.)), (h_0_1_0,  0.), (h_1_0_2, -0.5)], 'h_iab', xs_iab)
    h_iac = get_composed_h([(h_1_1_1, 1.), (h_1_1_0, -1.), (h_1_0_1, -1.), (h_1_0_0,       1.), (h_0_1_0,  0.), (h_1_0_2,   0.)], 'h_iac', xs_iac)
    h_ibc = get_composed_h([(h_1_1_1, 0.), (h_1_1_0,  1.), (h_1_0_1,  0.), (h_1_0_0,      -1.), (h_0_1_0, -1.), (h_1_0_2,   0.)], 'h_ibc', xs_ibc)

if nRew == 4:
    h_b   = get_composed_h([(h_1_0_0, 1.0)], 'h_b', xs_b)
    h_c   = get_composed_h([(h_0_1_0, 1.0)], 'h_c', xs_c)
    h_ibc = get_composed_h([(h_1_1_0, 1.0), (h_b, -1.0), (h_c, -1.0)], 'h_ibc', xs_ibc)
    h_iac = get_composed_h([(h_1_1_1, 1.0), (h_1_1_0, -1.0), (h_1_0_1, -1.0), (h_b, 1.0)], 'h_iac', xs_iac)
    h_iab = get_composed_h([(h_1_0_1, 2.0), (h_b, -1.5), (h_1_0_2, -0.5)], 'h_iab', xs_iab)
    h_a   = get_composed_h([(h_b, 0.5), (h_1_0_1, -1.0), (h_1_0_2, 0.5)], 'h_a'  , xs_a)


if nRew == 5:
    h_b   = get_composed_h([(h_1_0_0, 1.0)], 'h_b', xs_b)
    h_c   = get_composed_h([(h_0_1_0, 1.0)], 'h_c', xs_c)
    h_a   = get_composed_h([(h_1_0_2, 0.5), (h_1_0_1, -1.0), (h_1_0_0, 0.5)], 'h_a' , xs_a) # last could be h_b
    h_iab = get_composed_h([(h_1_0_1, 1.0), (h_a, -1.0), (h_b, -1.0)], 'h_ibc' , xs_ibc)
    h_ibc = get_composed_h([(h_1_1_0, 1.0), (h_b, -1.0), (h_c, -1.0)], 'h_iac' , xs_iac)
    h_iac = get_composed_h([(h_1_1_1, 1.0), (h_a, -1.0), (h_b, -1.0), (h_c, -1.0), (h_iab, -1.0), (h_ibc, -1.0)], 'h_iab' , xs_iab)

if nRew == 6:
    #                       xs node1       xs node2        xs node14       xs node17            xs node18       xs node19
    h_a   = get_composed_h([(h_1_1_1, 0.), (h_1_1_0,  0.), (h_1_0_1, -1.), (h_1_0_0,      0.5), (h_0_1_0,  0.), (h_1_0_2,  0.5)], 'h_a'  , xs_a)
    h_b   = get_composed_h([(h_1_1_1, 0.), (h_1_1_0,  0.), (h_1_0_1,  0.), (h_1_0_0,       1.), (h_0_1_0,  0.), (h_1_0_2,   0.)], 'h_b'  , xs_b)
    h_c   = get_composed_h([(h_1_1_1, 0.), (h_1_1_0,  0.), (h_1_0_1,  0.), (h_1_0_0,       0.), (h_0_1_0,  1.), (h_1_0_2,   0.)], 'h_c'  , xs_c)
    h_iab = get_composed_h([(h_1_1_1, 0.), (h_1_1_0,  0.), (h_1_0_1,  2.), (h_1_0_0, -(3./2.)), (h_0_1_0,  0.), (h_1_0_2, -0.5)], 'h_iab', xs_iab)
    h_iac = get_composed_h([(h_1_1_1, 1.), (h_1_1_0, -1.), (h_1_0_1, -1.), (h_1_0_0,       1.), (h_0_1_0,  0.), (h_1_0_2,   0.)], 'h_iac', xs_iac)
    h_ibc = get_composed_h([(h_1_1_1, 0.), (h_1_1_0,  1.), (h_1_0_1,  0.), (h_1_0_0,      -1.), (h_0_1_0, -1.), (h_1_0_2,   0.)], 'h_ibc', xs_ibc)


if nRew == 6:
    scaleTo(h_a  , 1./h_a.Integral())
    scaleTo(h_b  , 1./h_b.Integral())
    scaleTo(h_b  , 1./h_c.Integral())
    scaleTo(h_iab, 1./h_iab.Integral())
    scaleTo(h_iac, 1./h_iac.Integral())
    scaleTo(h_ibc, 1./h_ibc.Integral())
else:
    scaleTo(h_a  , xs_A)
    scaleTo(h_b  , xs_B)
    scaleTo(h_b  , xs_C)
    scaleTo(h_iab, xs_Iab)
    scaleTo(h_iac, xs_Iac)
    scaleTo(h_ibc, xs_Ibc)

################################################

xs_TOT = xs_A + xs_B + xs_C + xs_Iab + xs_Iac + xs_Ibc
print 'xs_TOT', xs_TOT
print 'xs_target', xs_target
h_total = get_composed_h([(h_a, 1.0), (h_b, 1.0), (h_c, 1.0), (h_iab, 1.0), (h_iac, 1.0), (h_ibc, 1.0)], 'h_total', xs_TOT)


h_total.SetLineColor(ROOT.kRed)
h_target.SetLineColor(ROOT.kBlack)

if not drawCompts:
    mmin = min(h_total.GetMinimum(), h_target.GetMinimum())
    mmax = max(h_total.GetMaximum(), h_target.GetMaximum())
else:
    mmin = min(h_total.GetMinimum(), h_target.GetMinimum(), h_a.GetMinimum(), h_b.GetMinimum(), h_c.GetMinimum(), h_iab.GetMinimum(), h_iac.GetMinimum(), h_ibc.GetMinimum())
    mmax = max(h_total.GetMaximum(), h_target.GetMaximum(), h_a.GetMaximum(), h_b.GetMaximum(), h_c.GetMaximum(), h_iab.GetMaximum(), h_iac.GetMaximum(), h_ibc.GetMaximum())

h_total.SetMaximum(1.15*mmax)
h_total.SetMinimum(0 if mmin > 0 else 1.15*mmin)

h_target.Scale(xs_TOT / h_target.Integral())

h_total.SetTitle(title)
h_total.SetTitleSize(0.1,'z')
h_total.Draw('pe')
h_target.Draw('pe same')

print 'h_total : ', h_total.Integral()
print 'h_target : ', h_target.Integral()

###### draw the individual components

h_a   .SetLineColor(ROOT.kBlue)
h_b   .SetLineColor(ROOT.kOrange)
h_c   .SetLineColor(ROOT.kGreen+1)
h_iab .SetLineColor(ROOT.kViolet)
h_iac .SetLineColor(ROOT.kMagenta)
h_ibc .SetLineColor(ROOT.kCyan)

h_a   .SetLineWidth(2)
h_b   .SetLineWidth(2)
h_c   .SetLineWidth(2)
h_iab .SetLineWidth(2)
h_iac .SetLineWidth(2)
h_ibc .SetLineWidth(2)
h_total  .SetLineWidth(2)
h_target .SetLineWidth(2)

if drawCompts:
    h_a  .Draw('same')
    h_b  .Draw('same')
    h_c  .Draw('same')
    h_iab.Draw('same')
    h_iac.Draw('same')
    h_ibc.Draw('same')

leg = ROOT.TLegend(0.55, 0.65, 0.88, 0.90)
leg.SetFillStyle(0)
leg.SetBorderSize(0)
leg.SetNColumns(2)
if drawCompts:
    leg.AddEntry(h_a  , 'a'     , 'lp')
    leg.AddEntry(h_b  , 'b'     , 'lp')
    leg.AddEntry(h_c  , 'c'     , 'lp')
    leg.AddEntry(h_iab, 'i_{ab}', 'lp')
    leg.AddEntry(h_iac, 'i_{ac}', 'lp')
    leg.AddEntry(h_ibc, 'i_{bc}', 'lp')

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
    hRatio.GetYaxis().SetTitle ("total/target")
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

oname = 'full_scan/'+oname

if not drawCompts:
    oname = oname.replace('.pdf', '_nocompts.pdf')
if not makeRatioPlot:
    oname = oname.replace('.pdf', '_noratio.pdf')
c1.Print(oname, 'pdf')
print '... done'



