#!/usr/bin/env python
import re, optparse
import os.path
from math import *
from ROOT import *
import modules.ConfigReader as cfgr

def parseOptions():

    usage = ('usage: %prog [options] datasetList\n'
             + '%prog -h for help')
    parser = optparse.OptionParser(usage)
    

    parser.add_option('-o', '--outName',   dest='outName',   type='string', default="testApr2018",  help='outsuffix')

    # store options and arguments as global variables
    global opt, args
    (opt, args) = parser.parse_args()


        
    
#gROOT.SetBatch(True)

parseOptions()

drawEY = False

outFormats = [".pdf",".png",".root",".C"]

drawHig2016 = False
drawHig2016VBF = False
drawHig2016Both = False

drawHig2016 = True
#drawHig2016VBF = True
drawHig2016Both = True

channels ="Combined"
channelsName = "bb #mu#tau_{h} + bb e#tau_{h} + bb #tau_{h}#tau_{h}"
#channelsName = "bb #tau_{h}#tau_{h}"

#catName = "VBF_lmr70"
#cat = "lmr70VBF"
#sel = "VBF"

#catName = "only VBF category"
#cat = "VBF"
#sel = "VBF"

#catName = "sboost_noVBF"
#cat = "sboost_noVBF"
#sel = "sboostedLL_noVBF"

#catName = "s1b1j_noVBF"
#sel = "s1b1jresolvedMcut_noVBF"
#cat = "s1b1j_noVBF"

#cat = "s2b0j_noVBF"
#catName = "s2b0j_noVBF"
#sel = "s2b0jresolvedMcut_noVBF"

#catName = "Inclusive (no VBF)"
#cat = "incl_noVBF"
#sel = "incl_noVBF"

catName = "Inclusive (with VBF)"
cat = "incl"
sel = "incl"

plotsFolder ="_newOrder_18Jun2018"

tag=''
#tag = '_onlyVBFsig_lmr70'
#tag = '_onlyGGFsig_lmr70'
#tag = '_onlyVBFsig'
#tag = '_onlyGGFsig'


sig=''
#sig='ggHHXS'
#sig='VBFC2V1XS'

sigName = ''
if 'ggHH' in sig or 'GGF' in tag:
    sigName = "only ggF signal"
elif 'VBF' in sig or 'VBF' in tag:
    sigName = "only VBF signal"
else:
    sigName = "ggF and VBF signals"

    
DeltaEta=["2","3","4"]
#DeltaEta=["2p5","3"]
#DeltaEta=["2"]

mCut=[300,400,500,600,650,700,750,800,900,1000,1500,2000]

def Frame(gPad,width=2):
    gPad.Update()
    gPad.RedrawAxis()
    l = TLine()
    l.SetLineWidth(width)

    lm = gPad.GetLeftMargin();
    rm = 1.-gPad.GetRightMargin();
    tm = 1.-gPad.GetTopMargin();
    bm = gPad.GetBottomMargin();

    
    l.DrawLineNDC(lm,tm,rm,tm);
    #right
    l.DrawLineNDC(rm,bm,rm,tm);
    #bottom
    l.DrawLineNDC(lm,bm,rm,bm);
    #top
    l.DrawLineNDC(lm,bm,lm,tm);
    

def Text(gPad, text, size = 0.03, font=42, align = 13, line = 1):
    x = 0
    y = 0
    #    histoWidth = histo.GetXaxis().GetBinWidth(1)*histo.GetXaxis().GetNbins()
    #    histoHeight = histo.GetMaximum()-histo.GetMinimum()
    t = gPad.GetTopMargin()
    b = gPad.GetBottomMargin()
    l = gPad.GetLeftMargin()
    r = gPad.GetRightMargin()
    if align==13:
        x = l + 0.02
        y = 1 - t - 0.02
    if align==31:
        x = 1 - r
        y = 1 - t + 0.02
    if align==11:
        x = l
        y = 1 - t + 0.02
        
    latex = TLatex()
    latex.SetNDC();
    latex.SetTextSize(size)
    latex.SetTextAlign(align)
    latex.SetTextFont(font)
    latex.DrawLatex(x,y,text)
    return latex
   
defaultVar = "MT2"
scale=1.0
scaleOld=1.0
#scale=1000.0/100.0 #/37.9/0.073
#scale=1000.0 #from pb to fb?
#DeltaEta=["2","2p5","3"]

gCombined = TMultiGraph()

gEYTauTau = TMultiGraph()
gEYTauTau.SetTitle(";m_{jj} cut [GeV]; Event Yield")

gEYMuTau = TMultiGraph()
gEYMuTau.SetTitle(";m_{jj} cut [GeV]; Event Yield")

gEYETau = TMultiGraph()
gEYETau.SetTitle(";m_{jj} cut [GeV]; Event Yield")


gCombined.SetTitle(";m_{jj} cut [GeV];Exp CLs/#sigma_{SM}#times#Beta(HH#rightarrow bb#tau#tau)")

colors = [kBlue, kMagenta, kRed]
EYcolors = [kBlue+1, kCyan+3, kCyan+1, kRed+2, kOrange+10, kOrange-2, kGreen, kGreen+2, kGreen+4]

yleg = 0.7
if drawHig2016Both: yleg = 0.6

if cat is 'VBF':
    #legend = TLegend(0.6, 0.11, 0.89,0.3)
    legend = TLegend(0.5, 0.7, 0.89,0.89)
else:
    legend = TLegend(0.5, yleg, 0.89,0.89)


scaleVBF = 1
scaleGGF = 10
if sel is not ("VBF"):
    legEY = TLegend(0.5, 0.11, 0.89,0.25)
    legEY.SetNColumns(2)
    scaleVBF =100  

else:
    legEY = TLegend(0.5, 0.75, 0.89,0.89)
    legEY.SetNColumns(2)
    scaleVBF =10  


legEY.SetFillColor(0)
legEY.SetBorderSize(0)
    
if not "incl" in cat:
    fileHistosTauTau = "/home/llr/cms/amendola/CMSSW_7_4_7/src/KLUBAnalysis/combiner/analyzedOutPlotter_TauTau_18Jun2018_newOrder_"+cat.replace('lmr70','')+"scan.root"
    fileHistosMuTau = "/home/llr/cms/amendola/CMSSW_7_4_7/src/KLUBAnalysis/combiner/analyzedOutPlotter_MuTau_18Jun2018_newOrder_"+cat+"scan.root"
    fileHistosETau = "/home/llr/cms/amendola/CMSSW_7_4_7/src/KLUBAnalysis/combiner/analyzedOutPlotter_ETau_18Jun2018_newOrder_"+cat+"scan.root"
    print fileHistosTauTau
    if not os.path.isfile(fileHistosTauTau) : 
        print "FILE HISTOS NOT FOUND: " , fileHistosTauTau

    if not os.path.isfile(fileHistosMuTau) : 
        print "FILE HISTOS NOT FOUND: " , fileHistosMuTau

    if not os.path.isfile(fileHistosETau) : 
        print "FILE HISTOS NOT FOUND: " , fileHistosETau

    fInTauTau = TFile.Open(fileHistosTauTau)
    fInMuTau = TFile.Open(fileHistosMuTau)
    fInETau = TFile.Open(fileHistosETau)



for k,deltaEta in enumerate(DeltaEta):
    folder ="{0}Scan_newOrder_deltaEta{1}_18Jun2018{2}".format(cat,deltaEta, tag)
    npoints = len(mCut)
    gExp = TGraph()
    if drawEY and not "incl" in cat:
        gTauTau_ggF = TGraph()
        gMuTau_ggF = TGraph()
        gETau_ggF = TGraph()
        gTauTau_VBF = TGraph()
        gMuTau_VBF = TGraph()
        gETau_VBF = TGraph()
        
        

    for i,m in enumerate(mCut) : 
        if drawEY and not "incl" in cat:

            hname = "ggHHXS_"+sel+"m"+str(m)+"eta"+str(deltaEta)+"_SR_HH_mass"
            histoTauTau = fInTauTau.Get(hname)
            integralTauTau = histoTauTau.Integral(1,histoTauTau.GetNbinsX()+1)
            gTauTau_ggF.SetPoint(i,float(m),float(integralTauTau))
            gTauTau_ggF.SetLineColor(EYcolors[k])
            gTauTau_ggF.SetLineWidth(2)
            
            
            
            histoMuTau = fInMuTau.Get(hname)
            integralMuTau = histoMuTau.Integral(1,histoMuTau.GetNbinsX()+1)
            gMuTau_ggF.SetPoint(i,float(m),float(integralMuTau))
            gMuTau_ggF.SetLineColor(EYcolors[k])
            gMuTau_ggF.SetLineWidth(2)
        
            
            
            histoETau = fInETau.Get(hname)
            integralETau = histoETau.Integral(1,histoETau.GetNbinsX()+1)
            gETau_ggF.SetPoint(i,float(m),float(integralETau))
            gETau_ggF.SetLineColor(EYcolors[k])
            gETau_ggF.SetLineWidth(2)
            


            hname = "VBFC2V1XS_"+sel+"m"+str(m)+"eta"+str(deltaEta)+"_SR_HH_mass"
            histoTauTau = fInTauTau.Get(hname)
            integralTauTau = histoTauTau.Integral(1,histoTauTau.GetNbinsX()+1)
            gTauTau_VBF.SetPoint(i,float(m),float(integralTauTau*scaleVBF))
            gTauTau_VBF.SetLineColor(EYcolors[k+3])
            gTauTau_VBF.SetLineWidth(2)
            
            

            histoMuTau = fInMuTau.Get(hname)
            integralMuTau = histoMuTau.Integral(1,histoMuTau.GetNbinsX()+1)
            gMuTau_VBF.SetPoint(i,float(m),float(integralMuTau*scaleVBF))
            gMuTau_VBF.SetLineColor(EYcolors[k+3])
            gMuTau_VBF.SetLineWidth(2)
            
            

            histoETau = fInETau.Get(hname)
            integralETau = histoETau.Integral(1,histoETau.GetNbinsX()+1)
            gETau_VBF.SetPoint(i,float(m),float(integralETau*scaleVBF))
            gETau_VBF.SetLineColor(EYcolors[k+3])
            gETau_VBF.SetLineWidth(2)
            
        
        if not sig:
            sigtag="SM_HHbbtt"
        else:
            sigtag=sig
        
        fileLocation = "/home/llr/cms/amendola/CMSSW_7_4_7/src/KLUBAnalysis/combiner/cards_"+channels+"_"+folder+"/"+sig+sel+"m"+str(m)+"eta"+str(deltaEta)+"MT2/higgsCombine"+sigtag+"_forLim_noTH.Asymptotic.mH"+str(m)+".root"
        print fileLocation
        if not os.path.isfile(fileLocation) : 
	    print "FILE LIMITS NOT FOUND: " , fileLocation
	    continue
        
        fin = TFile.Open(fileLocation)
        tree = fin.Get("limit")
        

        for entry in tree :
	    if tree.quantileExpected == 0.5 :
                
                limit = tree.limit*scale
                
	        if limit>0 : #and limit < 50 : 
                  

                    gExp.SetPoint(i,float(m),float(limit))
                    
    gExp.SetLineColor(colors[k])
    gExp.SetLineWidth(2)
    gExp.SetLineStyle(2)
    #gExp.Print()
    gCombined.Add(gExp,"l")
    legend.AddEntry(gExp, "#Delta#eta > "+deltaEta.replace("p","."), "l")

    if drawEY and not "incl" in cat:
        gEYETau.Add(gETau_VBF)
        gEYTauTau.Add(gTauTau_ggF)
        gEYMuTau.Add(gMuTau_ggF)
        gEYETau.Add(gETau_ggF)
        gEYTauTau.Add(gTauTau_VBF)
        gEYMuTau.Add(gMuTau_VBF)

        
        legEY.AddEntry(gTauTau_VBF,"VBF x"+str(scaleVBF), "l")
        legEY.AddEntry(gTauTau_ggF,"ggF  #Delta#eta > "+deltaEta.replace("p","."), "l")
        

        

        

        
if drawHig2016:
    l2016 = TGraph()
    for i,m in enumerate(mCut):
       l2016.SetPoint(i,m,19.81)

    
    l2016.SetLineStyle(10)
    l2016.SetLineWidth(2)
    l2016.SetLineColor(kRed)
    gCombined.Add(l2016,"l")
    legend.AddEntry(l2016,"HIG-17-002 (ggF)","l")                    

if drawHig2016VBF:
    l2016VBF = TGraph()
    for i,m in enumerate(mCut):
       l2016VBF.SetPoint(i,m,1301.0)

    
    l2016VBF.SetLineStyle(10)
    l2016VBF.SetLineWidth(2)
    l2016VBF.SetLineColor(kRed)
    gCombined.Add(l2016VBF,"l")
    legend.AddEntry(l2016VBF,"HIG-17-002 (VBF)","l")


if drawHig2016Both:
    l2016both = TGraph()
    for i,m in enumerate(mCut):
       l2016both.SetPoint(i,m,19.44)

    
    l2016both.SetLineStyle(10)
    l2016both.SetLineWidth(2)
    l2016both.SetLineColor(kBlue)
    gCombined.Add(l2016both,"l")
    legend.AddEntry(l2016both,"HIG-17-002 (ggF+VBF)","l")                    


    
#canvas limits
canvas = TCanvas("cCombined", "cCombined", 650,600)    

canvas.Draw()        
canvas.cd()

gCombined.Draw("a")
gCombined.GetYaxis().SetTitleOffset(1.5)
catLabel = Text(gPad, catName, size = 0.05,align = 11)
sigLabel = Text(gPad, sigName, size = 0.03,align = 13)
channelsLabel = Text(gPad, channelsName, 0.03, align = 31)


legend.SetFillColor(0)
legend.SetBorderSize(0)
legend.Draw("same")
Frame(gPad)
canvas.Update()
canvas.Modified()
raw_input()
canvas.SaveAs("plots"+plotsFolder+"/limits_"+cat+"_"+channels+tag+sig+".pdf")
if drawEY and not "incl" in cat:
    #canvas event yelds
    canvasTauTau = TCanvas("canvasTauTau", "canvasTauTau", 650,600)    
    canvasTauTau.Draw()        
    canvasTauTau.cd()
    gEYTauTau.Draw("a")
    gEYTauTau.GetYaxis().SetTitleOffset(1.5)
    catLabel = Text(gPad, catName, size = 0.05,align = 11)
    channelsLabel = Text(gPad, "bb #tau_{h}#tau_{h}", 0.05, align = 31)
    legEY.Draw("same")
    Frame(gPad)
    canvasTauTau.Update()
    canvasTauTau.Modified()
    #raw_input()
    canvasTauTau.SaveAs("plots"+plotsFolder+"/EY_"+cat+"_"+"TauTau.pdf")
    canvasMuTau = TCanvas("canvasMuTau", "canvasMuTau", 650,600)    
    canvasMuTau.Draw()        
    canvasMuTau.cd()
    gEYMuTau.Draw("a")
    gEYMuTau.GetYaxis().SetTitleOffset(1.5)
    catLabel = Text(gPad, catName, size = 0.05,align = 11)
    channelsLabel = Text(gPad, "bb #tau_{#mu}#tau_{h}", 0.05, align = 31)
    legEY.Draw("same")
    Frame(gPad)
    canvasMuTau.Update()
    canvasMuTau.Modified()
    #raw_input()
    canvasMuTau.SaveAs("plots"+plotsFolder+"/EY_"+cat+"_"+"MuTau.pdf")

    canvasETau = TCanvas("canvasETau", "canvasETau", 650,600)    
    canvasETau.Draw()        
    canvasETau.cd()
    gEYETau.Draw("a")
    gEYETau.GetYaxis().SetTitleOffset(1.5)
    catLabel = Text(gPad, catName, size = 0.05,align = 11)
    channelsLabel = Text(gPad, "bb #tau_{e}#tau_{h}", 0.05, align = 31)
    legEY.Draw("same")
    Frame(gPad)
    canvasETau.Update()
    canvasETau.Modified()
    #raw_input()
    canvasETau.SaveAs("plots"+plotsFolder+"/EY_"+cat+"_"+"ETau.pdf")




    
