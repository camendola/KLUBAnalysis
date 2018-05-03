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



channels ="Combined" #"Combined"
channelsName = ["bb #mu#tau_{h} + bb e#tau_{h} + bb #tau_{h}#tau_{h}"]


#folder = "2017_03_07_2D_{0}".format(bdtstring) #bis = 3cat, ter = 2cat

#outString = "2017_02_12_{0}_resonant".format(bdtstring)
outString = opt.outName 
#cat = "VBF"
cat = "sboost_noVBF"
#sel = "VBF"
sel = "sboostedLL_noVBF"

def redrawBorder():
   # this little macro redraws the axis tick marks and the pad border lines.
   gPad.Update();
   gPad.RedrawAxis();
   l = TLine()
   l.SetLineWidth(2)
   l.DrawLine(gPad.GetUxmin(), gPad.GetUymax(), gPad.GetUxmax(), gPad.GetUymax());
   l.DrawLine(gPad.GetUxmax(), gPad.GetUymin(), gPad.GetUxmax(), gPad.GetUymax());
   l.DrawLine(gPad.GetUxmin(), gPad.GetUymin(), gPad.GetUxmin(), gPad.GetUymax());
   #l.DrawLine(gPad.GetUxmin(), gPad.GetUymin(), gPad.GetUxmax(), gPad.GetUymin());

defaultVar = "MT2"
scale=1000/((37.9+2)*0.073)
#scale=1000.0/100.0 #/37.9/0.073
#scale=1000.0 #from pb to fb?
#DeltaEta=["2","2p5","3"]
DeltaEta=["2"]

mCut=[300,350,400,450,500,550,600,650,700]
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
                    
canvas = TCanvas("cCombined", "cCombined", 650, 500)    

canvas.Draw()        
canvas.cd()

gCombined.Draw("a")
legend.Draw("same")
canvas.Update()
canvas.Modified()
raw_input()
