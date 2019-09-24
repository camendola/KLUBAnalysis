from sympy import *
import numpy as np
from sympy import Matrix
from array import array
import ROOT
#import argparse


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
    def __init__(self, val_CV, val_C2V, val_kl, val_xs):
        self.val_CV  = val_CV
        self.val_C2V = val_C2V
        self.val_kl  = val_kl
        self.val_xs  = val_xs

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

# Get the total cross section
def get_total_xs (sample_list, t_CV, t_C2V, t_kl):

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

    return total_xs


######################
######## MAIN ########
######################
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetPaintTextFormat(".4f")

# Samples used to solve the system --> sample(cV, c2V, kl, xs, histo)
# Rewwighting number 9
rew_list = [
    sample(  1, 1, 1, 0.001499), # node 1
    sample(  1, 1, 0, 0.003947), # node 2
    sample(  1, 1, 2, 0.001243), # node 3
    sample(  1, 2, 1, 0.012719), # node 4
    sample(1.5, 1, 1, 0.057943), # node 5
    sample(  1, 0, 2,   0.0178), # node 19
]

######## Scan CV_C2V ########
t_cvs  = np.arange(-3,3.2,0.2)
t_c2vs = np.arange(-8,8.2,0.2)

# TH2D
th2_CV_C2V_scan = ROOT.TH2D("th2_CV_C2V_scan", "CV_C2V scan", len(t_cvs), t_cvs[0]-0.1, t_cvs[-1]+0.1, len(t_c2vs), t_c2vs[0]-0.1, t_c2vs[-1]+0.1)
th2_CV_C2V_scan.GetXaxis().SetTitle("C_{V}")
th2_CV_C2V_scan.GetYaxis().SetTitle("C_{2V}")
th2_CV_C2V_scan.GetZaxis().SetTitle("xs [pb]")
th2_CV_C2V_scan.GetYaxis().SetTitleOffset(0.9)
th2_CV_C2V_scan.GetZaxis().SetTitleOffset(1.)

# Actual scan of the parameters
t_kl  = 1
print "Start scan assuming kl=", t_kl
for i,t_cv in enumerate(t_cvs):
    for j,t_c2v in enumerate(t_c2vs):
    
        if (i%10==0 and j%10==0): print '- Doing t_cv=', t_cv, ' and t_c2v=', t_c2v
    
        tot_sigma = get_total_xs(rew_list, t_cv, t_c2v, t_kl)
        if tot_sigma==0: print 'ZERO XS for (', t_cv, ',', t_c2v,','+t_kl+')'

        ibin = th2_CV_C2V_scan.GetBin(i+1, j+1)
        th2_CV_C2V_scan.SetBinContent(ibin, tot_sigma)

c1 = ROOT.TCanvas()
c1.SetTopMargin(0.07)
c1.SetRightMargin(0.13)
c1.SetLeftMargin(0.09)
th2_CV_C2V_scan.SetTitle("C_{V}-C_{2V} scan - assuming k_{#lambda} = 1")
th2_CV_C2V_scan.Draw("colz text")
c1.Print('sum_scan/2D_CV_C2V_scan_kl_1.pdf','pdf')


t_kl  = 3
print "Start scan assuming kl=", t_kl
for i,t_cv in enumerate(t_cvs):
    for j,t_c2v in enumerate(t_c2vs):
    
        if (i%10==0 and j%10==0): print '- Doing t_cv=', t_cv, ' and t_c2v=', t_c2v
    
        tot_sigma = get_total_xs(rew_list, t_cv, t_c2v, t_kl)
        if tot_sigma==0: print 'ZERO XS for (', t_cv, ',', t_c2v,','+t_kl+')'

        ibin = th2_CV_C2V_scan.GetBin(i+1, j+1)
        th2_CV_C2V_scan.SetBinContent(ibin, tot_sigma)

c1a = ROOT.TCanvas()
c1a.SetTopMargin(0.07)
c1a.SetRightMargin(0.13)
c1a.SetLeftMargin(0.09)
th2_CV_C2V_scan.SetTitle("C_{V}-C_{2V} scan - assuming k_{#lambda} = 3")
th2_CV_C2V_scan.Draw("colz text")
c1a.Print('sum_scan/2D_CV_C2V_scan_kl_3.pdf','pdf')


t_kl  = -2
print "Start scan assuming kl=", t_kl
for i,t_cv in enumerate(t_cvs):
    for j,t_c2v in enumerate(t_c2vs):
    
        if (i%10==0 and j%10==0): print '- Doing t_cv=', t_cv, ' and t_c2v=', t_c2v
    
        tot_sigma = get_total_xs(rew_list, t_cv, t_c2v, t_kl)
        if tot_sigma==0: print 'ZERO XS for (', t_cv, ',', t_c2v,','+t_kl+')'

        ibin = th2_CV_C2V_scan.GetBin(i+1, j+1)
        th2_CV_C2V_scan.SetBinContent(ibin, tot_sigma)

c1b = ROOT.TCanvas()
c1b.SetTopMargin(0.07)
c1b.SetRightMargin(0.13)
c1b.SetLeftMargin(0.09)
th2_CV_C2V_scan.SetTitle("C_{V}-C_{2V} scan - assuming k_{#lambda} = -2")
th2_CV_C2V_scan.Draw("colz text")
c1b.Print('sum_scan/2D_CV_C2V_scan_kl_m2.pdf','pdf')


######## Scan CV_KL ########
t_cvs = np.arange(-6,6.2,0.2)
t_kls = np.arange(-8,8.2,0.2)

# TH2D
th2_CV_KL_scan = ROOT.TH2D("th2_CV_KL_scan", "CV_KL scan", len(t_cvs), t_cvs[0]-0.1, t_cvs[-1]+0.1, len(t_kls), t_kls[0]-0.1, t_kls[-1]+0.1)
th2_CV_KL_scan.GetXaxis().SetTitle("C_{V}")
th2_CV_KL_scan.GetYaxis().SetTitle("K_{#lambda}")
th2_CV_KL_scan.GetZaxis().SetTitle("xs [pb]")
th2_CV_KL_scan.GetYaxis().SetTitleOffset(0.9)
th2_CV_KL_scan.GetZaxis().SetTitleOffset(1.)

# Actual scan of the parameters
t_c2v  = 1
print "Start scan assuming c2v=", t_c2v
for i,t_cv in enumerate(t_cvs):
    for j,t_kl in enumerate(t_kls):
    
        if (i%10==0 and j%10==0): print '- Doing t_cv=', t_cv, ' and t_kl=', t_kl
    
        tot_sigma = get_total_xs(rew_list, t_cv, t_c2v, t_kl)
        if tot_sigma==0: print 'ZERO XS for (', t_cv, ',', t_c2v,','+t_kl+')'

        ibin = th2_CV_KL_scan.GetBin(i+1, j+1)
        th2_CV_KL_scan.SetBinContent(ibin, tot_sigma)

c2 = ROOT.TCanvas()
c2.SetTopMargin(0.07)
c2.SetRightMargin(0.13)
c2.SetLeftMargin(0.09)
th2_CV_KL_scan.SetTitle("C_{V}-K_{#lambda} scan - assuming C_{2V} = 1")
th2_CV_KL_scan.Draw("colz text")
c2.Print('sum_scan/2D_CV_KL_scan_C2V_1.pdf','pdf')


t_c2v  = 3
print "Start scan assuming c2v=", t_c2v
for i,t_cv in enumerate(t_cvs):
    for j,t_kl in enumerate(t_kls):
    
        if (i%10==0 and j%10==0): print '- Doing t_cv=', t_cv, ' and t_kl=', t_kl
    
        tot_sigma = get_total_xs(rew_list, t_cv, t_c2v, t_kl)
        if tot_sigma==0: print 'ZERO XS for (', t_cv, ',', t_c2v,','+t_kl+')'

        ibin = th2_CV_KL_scan.GetBin(i+1, j+1)
        th2_CV_KL_scan.SetBinContent(ibin, tot_sigma)

c2a = ROOT.TCanvas()
c2a.SetTopMargin(0.07)
c2a.SetRightMargin(0.13)
c2a.SetLeftMargin(0.09)
th2_CV_KL_scan.SetTitle("C_{V}-K_{#lambda} scan - assuming C_{2V} = 3")
th2_CV_KL_scan.Draw("colz text")
c2a.Print('sum_scan/2D_CV_KL_scan_C2V_3.pdf','pdf')


t_c2v  = -2
print "Start scan assuming c2v=", t_c2v
for i,t_cv in enumerate(t_cvs):
    for j,t_kl in enumerate(t_kls):
    
        if (i%10==0 and j%10==0): print '- Doing t_cv=', t_cv, ' and t_kl=', t_kl
    
        tot_sigma = get_total_xs(rew_list, t_cv, t_c2v, t_kl)
        if tot_sigma==0: print 'ZERO XS for (', t_cv, ',', t_c2v,','+t_kl+')'

        ibin = th2_CV_KL_scan.GetBin(i+1, j+1)
        th2_CV_KL_scan.SetBinContent(ibin, tot_sigma)

c2b = ROOT.TCanvas()
c2b.SetTopMargin(0.07)
c2b.SetRightMargin(0.13)
c2b.SetLeftMargin(0.09)
th2_CV_KL_scan.SetTitle("C_{V}-K_{#lambda} scan - assuming C_{2V} = -2")
th2_CV_KL_scan.Draw("colz text")
c2b.Print('sum_scan/2D_CV_KL_scan_C2V_m2.pdf','pdf')


######## Scan C2V_KL ########
ROOT.gStyle.SetPaintTextFormat(".3f")
t_c2vs = np.arange(-8,8.2,0.2)
t_kls = np.arange(-8,8.2,0.2)


# TH2D
th2_C2V_KL_scan = ROOT.TH2D("th2_C2V_KL_scan", "C2V_KL scan", len(t_c2vs), t_c2vs[0]-0.1, t_c2vs[-1]+0.1, len(t_kls), t_kls[0]-0.1, t_kls[-1]+0.1)
th2_C2V_KL_scan.GetXaxis().SetTitle("C_{2V}")
th2_C2V_KL_scan.GetYaxis().SetTitle("K_{#lambda}")
th2_C2V_KL_scan.GetZaxis().SetTitle("xs [pb]")
th2_C2V_KL_scan.GetYaxis().SetTitleOffset(0.9)
th2_C2V_KL_scan.GetZaxis().SetTitleOffset(1.)

# Actual scan of the parameters
t_cv  = 1
print "Start scan assuming cv=", t_cv
for i,t_c2v in enumerate(t_c2vs):
    for j,t_kl in enumerate(t_kls):
    
        if (i%10==0 and j%10==0): print '- Doing t_c2v=', t_c2v, ' and t_kl=', t_kl
    
        tot_sigma = get_total_xs(rew_list, t_cv, t_c2v, t_kl)
        if tot_sigma==0: print 'ZERO XS for (', t_cv, ',', t_c2v,','+t_kl+')'

        ibin = th2_C2V_KL_scan.GetBin(i+1, j+1)
        th2_C2V_KL_scan.SetBinContent(ibin, tot_sigma)

c3 = ROOT.TCanvas()
c3.SetTopMargin(0.07)
c3.SetRightMargin(0.13)
c3.SetLeftMargin(0.09)
th2_C2V_KL_scan.SetTitle("C_{2V}-K_{#lambda} scan - assuming C_{V} = 1")
th2_C2V_KL_scan.Draw("colz text")
c3.Print('sum_scan/2D_C2V_KL_scan_CV_1.pdf','pdf')


# Actual scan of the parameters
t_cv  = 3
print "Start scan assuming cv=", t_cv
for i,t_c2v in enumerate(t_c2vs):
    for j,t_kl in enumerate(t_kls):
    
        if (i%10==0 and j%10==0): print '- Doing t_c2v=', t_c2v, ' and t_kl=', t_kl
    
        tot_sigma = get_total_xs(rew_list, t_cv, t_c2v, t_kl)
        if tot_sigma==0: print 'ZERO XS for (', t_cv, ',', t_c2v,','+t_kl+')'

        ibin = th2_C2V_KL_scan.GetBin(i+1, j+1)
        th2_C2V_KL_scan.SetBinContent(ibin, tot_sigma)

c3a = ROOT.TCanvas()
c3a.SetTopMargin(0.07)
c3a.SetRightMargin(0.13)
c3a.SetLeftMargin(0.09)
th2_C2V_KL_scan.SetTitle("C_{2V}-K_{#lambda} scan - assuming C_{V} = 3")
th2_C2V_KL_scan.Draw("colz text")
c3a.Print('sum_scan/2D_C2V_KL_scan_CV_3.pdf','pdf')


# Actual scan of the parameters
t_cv  = -2
print "Start scan assuming cv=", t_cv
for i,t_c2v in enumerate(t_c2vs):
    for j,t_kl in enumerate(t_kls):
    
        if (i%10==0 and j%10==0): print '- Doing t_c2v=', t_c2v, ' and t_kl=', t_kl
    
        tot_sigma = get_total_xs(rew_list, t_cv, t_c2v, t_kl)
        if tot_sigma==0: print 'ZERO XS for (', t_cv, ',', t_c2v,','+t_kl+')'

        ibin = th2_C2V_KL_scan.GetBin(i+1, j+1)
        th2_C2V_KL_scan.SetBinContent(ibin, tot_sigma)

c3b = ROOT.TCanvas()
c3b.SetTopMargin(0.07)
c3b.SetRightMargin(0.13)
c3b.SetLeftMargin(0.09)
th2_C2V_KL_scan.SetTitle("C_{2V}-K_{#lambda} scan - assuming C_{V} = -2")
th2_C2V_KL_scan.Draw("colz text")
c3b.Print('sum_scan/2D_C2V_KL_scan_CV_m2.pdf','pdf')



######## Full 3D scan CV_C2V_KL ########
#t_cvs  = np.arange(-10,10.,1.0)
#t_c2vs = np.arange(-10,10.,1.0)
#t_kls  = np.arange(-10,10.,1.0)
t_cvs  = np.arange(-2,2.,1.0)
t_c2vs = np.arange(-2,2.,1.0)
t_kls  = np.arange(-2,2.,1.0)

# TH3D
th3_CV_C2V_KL_scan = ROOT.TH3D("th2_CV_C2V_KL_scan", "CV_C2V_KL scan", len(t_cvs), t_cvs[0]-0.5, t_cvs[-1]+0.5, len(t_c2vs), t_c2vs[0]-0.5, t_c2vs[-1]+0.5, len(t_kls), t_kls[0]-0.5, t_kls[-1]+0.5)
th3_CV_C2V_KL_scan.GetXaxis().SetTitle("C_{V}")
th3_CV_C2V_KL_scan.GetYaxis().SetTitle("C_{2V}")
th3_CV_C2V_KL_scan.GetZaxis().SetTitle("K_{#lambda}")
th3_CV_C2V_KL_scan.GetYaxis().SetTitleOffset(0.9)
th3_CV_C2V_KL_scan.GetZaxis().SetTitleOffset(1.)
th3_CV_C2V_KL_scan.SetTitle("C_{V}-C_{2V}-K_{#lambda} scan")

# Actual scan of the parameters

for i,t_cv in enumerate(t_cvs):
    for j,t_c2v in enumerate(t_c2vs):
        for k,t_kl in enumerate(t_kls):
        
            if (i%10==0 and j%10==0 and k%10==0): print '- Doing t_cv=', t_cv, ' and t_c2v=', t_c2v, ' and t_kl=', t_kl
        
            tot_sigma = get_total_xs(rew_list, t_cv, t_c2v, t_kl)
            if tot_sigma==0: print 'ZERO XS for (', t_cv, ',', t_c2v,','+t_kl+')'

            ibin = th3_CV_C2V_KL_scan.GetBin(i+1, j+1, k+1)
            th3_CV_C2V_KL_scan.SetBinContent(ibin, tot_sigma)


c4 = ROOT.TCanvas()
c4.SetTopMargin(0.07)
c4.SetRightMargin(0.13)
c4.SetLeftMargin(0.09)
th3_CV_C2V_KL_scan.Draw("BOX2Z")
c4.Print('sum_scan/3D_CV_C2V_KL_scan_BOX2Z.pdf','pdf')


fOut = ROOT.TFile('sum_scan/VBF_XS_scans.root', 'recreate')
fOut.cd()
th2_CV_KL_scan.Write()
th2_CV_C2V_scan.Write()
th2_C2V_KL_scan.Write()
th3_CV_C2V_KL_scan.Write()
fOut.Close()

