#!/usr/bin/env python
import re, optparse
import os.path
from math import *
from ROOT import *

def parseOptions():

    usage = ('usage: %prog [options] datasetList\n'
             + '%prog -h for help')
    parser = optparse.OptionParser(usage)
    

    parser.add_option('-o', '--outName',   dest='outName',   type='string', default="testApr2018",  help='outsuffix')

    # store options and arguments as global variables
    global opt, args
    (opt, args) = parser.parse_args()

# cards_Combined_2016_07_26



parseOptions()


outFormats = [".pdf",".png",".root",".C"]

drawHig2016 = True

channels ="Combined"
channelsName = "bb #mu#tau_{h} + bb e#tau_{h} + bb #tau_{h}#tau_{h}"
#channelsName = "bb #tau_{h}#tau_{h}"
#catName = "VBF"
#catName = "sboost_noVBF"
#catName = "s1b1j_noVBF"
#catName = "s2b0j_noVBF"
#catName = "Inclusive (noVBF)"
catName = "Inclusive"
#folder = "2017_03_07_2D_{0}".format(bdtstring) #bis = 3cat, ter = 2cat

#outString = "2017_02_12_{0}_resonant".format(bdtstring)
outString = opt.outName 
#cat = "VBF"
#cat = "sboost_noVBF"
#cat = "s1b1j_noVBF"
#cat = "s2b0j_noVBF"
#cat = "incl_noVBF"
cat = "incl"
#sel = "VBF"
#sel = "sboostedLL_noVBF"
#sel = "s1b1jresolvedMcut_noVBF"
#sel = "s2b0jresolvedMcut_noVBF"
#sel = "incl_noVBF"
sel = "incl"

DeltaEta=["2","2p5","3"]

mCut=[300,350,400,450,500,550,600,650,700]

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
scale=1000/((37.9+2)*0.073)
scaleOld=1000/((37.9)*0.073)
#scale=1000.0/100.0 #/37.9/0.073
#scale=1000.0 #from pb to fb?
#DeltaEta=["2","2p5","3"]

gCombined = TMultiGraph()
gCombined.SetTitle(";m_{jj} cut [GeV];Exp CLs/#sigma_{SM}#times#Beta(HH#rightarrow bb#tau#tau)")
colors = [kBlue, kMagenta, kRed]
legend = TLegend(0.6, 0.7, 0.89,0.89)
for k,deltaEta in enumerate(DeltaEta):
    folder ="{0}Scan_oldOrder_deltaEta{1}".format(cat,deltaEta)



    
    npoints = len(mCut)
    gExp = TGraph()
    for i,m in enumerate(mCut) : 
        
        fileLocation = "/home/llr/cms/amendola/CMSSW_7_4_7/src/KLUBAnalysis/combiner/cards_"+channels+"_"+folder+"/"+sel+"m"+str(m)+"eta"+str(deltaEta)+"MT2/higgsCombineSM_HHbbtt_forLim_noTH.Asymptotic.mH"+str(m)+".root"
        print fileLocation
        if not os.path.isfile(fileLocation) : 
	    print "FILE NOT FOUND: " , fileLocation
	    continue
        
        
        fin = TFile.Open(fileLocation)
        tree = fin.Get("limit")
    
    
        for entry in tree :
	    if tree.quantileExpected == 0.5 :
                
                limit = tree.limit*scale
                
	        if limit>0 : #and limit < 50 : 
                    print i, float(m), float(limit)

                    gExp.SetPoint(i,float(m),float(limit))
                    
    gExp.SetLineColor(colors[k])
    gExp.SetLineWidth(2)
    gExp.SetLineStyle(2)
    gExp.Print()
    gCombined.Add(gExp,"l")
    legend.AddEntry(gExp, "#Delta#eta > "+deltaEta.replace("p","."), "l")
if drawHig2016:
    l2016 = TGraph()
    for i,m in enumerate(mCut):
       l2016.SetPoint(i,m,0.0513*scaleOld)

    print 0.0513*scaleOld
    l2016.SetLineStyle(10)
    l2016.SetLineWidth(2)
    l2016.SetLineColor(kRed)
    gCombined.Add(l2016,"l")
    legend.AddEntry(l2016,"HIG-17-002","l")                    
canvas = TCanvas("cCombined", "cCombined", 650,600)    

canvas.Draw()        
canvas.cd()

gCombined.Draw("a")
catLabel = Text(gPad, catName, size = 0.05,align = 11)

channelsLabel = Text(gPad, channelsName, 0.05, align = 31)


    
legend.Draw("same")
Frame(gPad)
canvas.Update()
canvas.Modified()
raw_input()
