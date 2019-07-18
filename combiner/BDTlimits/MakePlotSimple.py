#!/usr/bin/env python
import re, optparse, sys
import os.path
from math import *
from ROOT import *

def parseOptions():

    usage = ('usage: %prog [options] datasetList\n'
             + '%prog -h for help')
    parser = optparse.OptionParser(usage)
    
    parser.add_option('-x', '--benchmark' , dest='bench'       , type='int'   , default=0  ,  help='0:lambda scan, 1:benchmarks, 999:resonant')
    parser.add_option('-o', '--outName'   , dest='outName'     , type='string', default='' ,  help='outsuffix')
    parser.add_option('-s', '--spin'      , dest='spin'        , type='string', default='' ,  help='spin hypothesis for the resonant analysis')
    parser.add_option('-c', '--categories', action="store_true", dest='cats'  , help='by categories'  )
    parser.add_option('-d', '--draw'      , action="store_true", dest='draw'  , help='draw histos'    )
    parser.add_option('-l', '--log'       , action="store_true", dest='logy'  , help='draw logY scale')
    parser.add_option('-a', '--addObs'    , action="store_true", dest='addobs', help='add observation')

    # store options and arguments as global variables
    global opt, args
    (opt, args) = parser.parse_args()

    if opt.bench == 999 and opt.spin == '':
        print "ERROR!! you chose resonant analysis but didn't provide a valid spin option, please choose between 0 (Radion) or 2 (Graviton)"
        sys.exit()

# Configurables
inputDir = "/gwpool/users/brivio/Hhh_1718/syncFeb2018/May2019/CMSSW_9_0_0/src/KLUBAnalysis/combiner/BDTlimits"

## Parsing Options
parseOptions()

outFormats = [".pdf",".png",".root",".C"]

#benchmark = 999 # -1: 1507 points, 0: lambda, 1: benchmark, 2:300points 2D grid, 999: Risonante, by default we do not plot the 1507 points
benchmark = opt.bench

addObserved = False
if opt.addobs : addObserved = True

if opt.cats : plotByCategory = True
else : plotByCategory = False

#channels = ["ETau","MuTau","TauTau","Combined"] #"Combined"
#channelsName = ["bb e#tau_{h} channel","bb #mu#tau_{h} channel","bb #tau_{h}#tau_{h} channel","bb #mu#tau_{h} + bb e#tau_{h} + bb #tau_{h}#tau_{h}"]
channels = ["MuTau","TauTau","Combined"] #"Combined"
channelsName = ["bb #mu#tau_{h} channel","bb #tau_{h}#tau_{h} channel","bb #mu#tau_{h} + bb #tau_{h}#tau_{h}"]
if plotByCategory : channelsName = ["Combined 2b0j","Combined 1b1j","Combined boosted"]

folder = "2019_07_12_nonResonant"

outString = opt.outName

scale=1000.0 #from pb to fb?

masses = []
if benchmark == 999:

    LM_masses  = [250, 260, 270, 280, 300, 320]
    MM_masses  = [350, 400]
    HM_masses  = [450, 500, 550, 600, 650, 700, 750, 800, 850, 900]
    VHM_masses = [1000, 1250, 1500, 1750, 2000, 2500, 3000] # not used for now

    LM_masses  = [280]
    MM_masses  = [400]
    HM_masses  = [650]
    masses = LM_masses + MM_masses + HM_masses

    defaultNames = []
    for mass in LM_masses:
        defaultVar = "BDToutLM_spin_"+str(opt.spin)+"_mass_"+str(mass)
        defaultNames.append(defaultVar)
    for mass in MM_masses:
        defaultVar = "BDToutMM_spin_"+str(opt.spin)+"_mass_"+str(mass)
        defaultNames.append(defaultVar)
    for mass in HM_masses:
        defaultVar = "BDToutHM_spin_"+str(opt.spin)+"_mass_"+str(mass)
        defaultNames.append(defaultVar)

else:
    defaultVar = "BDToutSM_kl"
    masses    = [0, 1, 5, 30] #(0, 1, 2.45, 5, 30)

    defaultNames = []
    for mass in masses:
        defaultNames.append(defaultVar+"_"+str(mass))

categories = ["s2b0jresolved","s1b1jresolved","sboostedLL"]

pointNumbers=[]

# this little macro redraws the axis tick marks and the pad border lines.
def redrawBorder():
   gPad.Update();
   gPad.RedrawAxis();
   l = TLine()
   l.SetLineWidth(3)
   l.DrawLine(gPad.GetUxmin(), gPad.GetUymax(), gPad.GetUxmax(), gPad.GetUymax());
   l.DrawLine(gPad.GetUxmax(), gPad.GetUymin(), gPad.GetUxmax(), gPad.GetUymax());
   l.DrawLine(gPad.GetUxmin(), gPad.GetUymin(), gPad.GetUxmin(), gPad.GetUymax());

def getExpValue( kl,  yt): 
	BR =1 
	return (2.09*yt*yt*yt*yt +   0.28*yt*yt*kl*kl  -1.37*yt*yt*yt*kl)*2.44477/BR;

def getExpLine(c,  xmin,  xmax,  yt):
	BR = 1
	myFunc =  TF1("myFunc","(2.09*[0]*[0]*[0]*[0] + 0.28*[0]*[0]*x*x -1.37*[0]*[0]*[0]*x)*2.44185/[1]",xmin,xmax);
	myFunc.SetParameter(0,yt); 
	myFunc.SetParameter(1,BR); 
	graph = TGraph(myFunc);
	ci = TColor.GetColor("#ff0000");
	c.cd();
	graph.SetLineColor(ci);
	graph.SetLineWidth(3);
	graph.Draw("l");
	nP = int((xmax-xmin)*10.0)
	Graph_syst_Scale =  TGraphAsymmErrors(nP)
	for i in range(nP) : 
		Graph_syst_Scale_x=(xmin+(i*1.)/10.)
		Graph_syst_Scale_y=(getExpValue(xmin+(i*1.)/10.,yt)) #; //(2.11+0.29*(-4.+(i*1.)/10.)*(-4.+(i*1.)/10.)-1.40*(-4.+(i*1.)/10.))*2.5039)
		Graph_syst_Scale_x_err=(0)
		Graph_syst_Scale_y_errup=(  (2.09*yt*yt*yt*yt+0.28*yt*yt*(xmin+(i*1.)/10.)*(xmin+(i*1.)/10.)-1.37*yt*yt*yt*(xmin+(i*1.)/10.))*2.44185*0.053/BR)
		Graph_syst_Scale_y_errdown=((2.09*yt*yt*yt*yt+0.28*yt*yt*(xmin+(i*1.)/10.)*(xmin+(i*1.)/10.)-1.37*yt*yt*yt*(xmin+(i*1.)/10.))*2.44185*0.067/BR)
		Graph_syst_Scale.SetPoint(i,Graph_syst_Scale_x,Graph_syst_Scale_y)
		Graph_syst_Scale.SetPointError(i,Graph_syst_Scale_x_err,Graph_syst_Scale_x_err,Graph_syst_Scale_y_errup,Graph_syst_Scale_y_errdown)

	Graph_syst_Scale.SetLineColor(kRed)
	Graph_syst_Scale.SetFillColor(kRed)
	Graph_syst_Scale.SetFillStyle(3001)
	Graph_syst_Scale.DrawClone("e3");

## find maximum of tgraph, including error
def findMaxOfGraph (graph):
    uppers = []
    for i in range (0, graph.GetN()):
        x = Double(0.0)
        y = Double(0.0)
        graph.GetPoint(i, x, y)
        uppers.append (y + graph.GetErrorYhigh(i))
    return max(uppers)


if not opt.draw :
	gROOT.SetBatch(True)

gEtau = TMultiGraph()
gMutau = TMultiGraph()
gTautau = TMultiGraph()
gCombined = TMultiGraph()

mg = [gEtau,gMutau,gTautau,gCombined] 

gtemp = [TGraphAsymmErrors(),TGraphAsymmErrors(),TGraphAsymmErrors(),TGraphAsymmErrors()]
g95 = [TGraphAsymmErrors(),TGraphAsymmErrors(),TGraphAsymmErrors(),TGraphAsymmErrors()]


tooLopOn = channels
if plotByCategory: tooLopOn = categories
for c in range(len(tooLopOn)) :
    gAll = TGraphAsymmErrors()
    gAll.SetTitle("Combined categories")
    gAll.SetName("Combined categories")
    gAll.SetFillStyle(0)
    gObs = TGraph()
    gObs.SetTitle("Observed")
    gObs.SetName("Observed")
    gObs.SetLineColor(1)
    gObs.SetMarkerColor(1)
    gObs.SetMarkerStyle(20)
    gObs.SetFillStyle(0)
    #masses = []
    catstring = categories[c]
    if benchmark == 2 :
        npoints = 2673
        app = "ggHH_bbtt"
        #for m in range(0,npoints) : masses.append(m)
    elif benchmark == 1 :
        npoints = len(masses)
        app = "GGFHH" #"benchrew"
        #for m in range(0,npoints) : masses.append(m)
    elif benchmark == 0 :
        npoints = len(masses)
        app = "GGFHH" #"ggHH_bbtt"
        #for m in range(0,npoints) : masses.append(m)
    elif benchmark < 0:
        npoints = 1507
        app = "5Dplane"
        #for m in range(0,npoints) : masses.append(m)
    else :
        app = "GGFHH_Radion"
        npoints = len(masses)
        #for m in range(0,npoints) : masses.append(massesResonant[m])

    offsetX = 20
    if benchmark == 999 or benchmark == 2 or benchmark == 0:
        offsetX =0
    for i,m in enumerate(masses):
        if benchmark == 999:
            fileLocation = inputDir+"/cards_"+channels[c]+"_"+folder+"/"+app+catstring+defaultNames[i]+"/higgsCombine"+app+"_"+str(m)+"_forLim.AsymptoticLimits.mH"+str(m)+".root"
        else:
            fileLocation = inputDir+"/cards_"+channels[c]+"_"+folder+"/"+app+catstring+defaultNames[i]+"/higgsCombine"+app+"_"+str(m)+"_forLim.AsymptoticLimits.mH125.root"
        if plotByCategory :
            if benchmark == 999:
                fileLocation = inputDir+"/cards_Combined_"+folder+"/"+app+catstring+defaultNames[i]+"/higgsCombine"+app+"_"+str(m)+"_forLim.AsymptoticLimits.mH"+str(m)+".root"
            else:
                fileLocation = inputDir+"/cards_Combined_"+folder+"/"+app+catstring+defaultNames[i]+"/higgsCombine"+app+"_"+str(m)+"_forLim.AsymptoticLimits.mH125.root"
        print '--> INPUTFILE:', fileLocation
        if not os.path.isfile(fileLocation) :
            print "FILE NOT FOUND: " , fileLocation
            continue
        if benchmark<0 : pointNumbers.append(m)
        fin = TFile.Open(fileLocation)
        tree = fin.Get("limit")
        if not tree :
            print "MALEDETTO TREE", fileLocation, fin, tree
            gAll.SetPoint(gAll.GetN(),m-offsetX,-1)
            g95[c].SetPoint(g95[c].GetN(),m-offsetX,-1)
            gObs.SetPoint(gObs.GetN(),m-offsetX,-1)
            continue

        high=0
        low=0
        limit = 0
        obs = 0
        errX = 0.3
        if benchmark == 1:
            offsetX = -1
            errX = 0.15
        for entry in tree:
            if tree.quantileExpected < 0:
                obs = tree.limit*scale
            elif tree.quantileExpected == 0.5:
                limit = tree.limit*scale
            elif tree.quantileExpected > 0.83 and tree.quantileExpected < 0.85:
                high = tree.limit*scale
            elif tree.quantileExpected > 0.15 and tree.quantileExpected < 0.17:
                low = tree.limit*scale
            elif tree.quantileExpected > 0.024 and tree.quantileExpected < 0.026:
                low95 = tree.limit*scale
            elif tree.quantileExpected > 0.974 and tree.quantileExpected < 0.976:
                high95 = tree.limit*scale

        if limit>0 : #and limit < 50 :
            if m == 750 and limit > 900 :
                limit = limit/100
                obs = obs/100
                high = high/100
                high95=high95/100
                low = low/100
                low95=low95/100
            #import pdb; pdb.set_trace()
            gAll.SetPoint     (gAll.GetN()  , m-offsetX, limit)
            gAll.SetPointError(gAll.GetN()-1, 0+errX, 0+errX, limit-low, high-limit)

            g95[c].SetPoint     (g95[c].GetN()  , m-offsetX, limit)
            g95[c].SetPointError(g95[c].GetN()-1, 0+errX, 0+errX, limit-low95, high95-limit)

            gObs.SetPoint(gObs.GetN(), m-offsetX, obs)

            # print "OBS: " , m-offsetX,obs
            # print "  - EXP: " , m-offsetX,limit
            # print "\n"
            #if benchmark < 0:
            #	observed2d[c].append(obs)
            #	expected2d[c].append(limit)
            #g95[c].SetPoint(g95[c].GetN(),m,limit-low95)
            #g95[c].SetPoint(g95[c].GetN(),m,high95-limit)
            #g68[c].SetPoint(g68[c].GetN(),m,limit-low)
            #g68[c].SetPoint(g68[c].GetN(),m,high-limit)
    print "adding gall", gAll.GetN()
    mg[c].Add(gAll)
    mg[c].Add(gtemp[c])
    mg[c].Add(gObs)
    gAll.Print()


if not benchmark == 2 :
	cNice = [
	TCanvas("c"+tooLopOn[0], "c"+tooLopOn[0], 650, 500),
	TCanvas("c"+tooLopOn[1], "c"+tooLopOn[1], 650, 500),
	#TCanvas("c"+tooLopOn[2], "c"+tooLopOn[2], 650, 500),
	TCanvas("cCombined", "cCombined", 650, 500)
	]
else :
	cNice = [
	TCanvas("cCombined", "cCombined", 650, 500)
	]

for ic in range(len(tooLopOn)):
    print "DOING CHANNEL", tooLopOn[ic]
    cNice[ic].cd()
    cNice[ic].SetFrameLineWidth(3)
    cNice[ic].SetBottomMargin (0.15)
    cNice[ic].SetRightMargin (0.05)
    cNice[ic].SetLeftMargin (0.15)

    gexp = mg[ic].GetListOfGraphs().FindObject("Combined categories").Clone()
    gexp.SetTitle("Expected CLs")
    gexp.SetMarkerStyle(24)
    gexp.SetMarkerColor(4)
    gexp.SetMarkerSize(0.8)
    gexp.SetLineColor(4)
    gexp.SetLineStyle(2)
    gexp.SetFillColor(0)
    g68 = mg[ic].GetListOfGraphs().FindObject("Combined categories").Clone()
    g68.SetTitle("Expected #pm 1#sigma")
    g68.SetMarkerStyle(0)
    g68.SetMarkerColor(3)
    g68.SetFillColor(TColor.GetColor(0, 220, 60))
    g68.SetLineColor(TColor.GetColor(0, 220, 60))
    g68.SetFillStyle(1001)
    g95[ic].SetTitle("Expected #pm 2#sigma")
    g95[ic].SetName(tooLopOn[ic])
    g95[ic].SetMarkerStyle(0)
    g95[ic].SetMarkerColor(5)
    g95[ic].SetFillColor(TColor.GetColor(254, 234, 0))
    g95[ic].SetLineColor(TColor.GetColor(254, 234, 0))
    g95[ic].SetFillStyle(1001)
    g95[ic].GetYaxis().SetRangeUser(1,100000)
    if not opt.logy:
        if "Combined" in tooLopOn[ic]:
            g95[ic].GetYaxis().SetRangeUser(1,1000)
        elif "TauTau" in tooLopOn[ic]:
            g95[ic].GetYaxis().SetRangeUser(1,2000)
        elif "MuTau" in tooLopOn[ic]:
            g95[ic].GetYaxis().SetRangeUser(1,2000)
        elif "ETau" in tooLopOn[ic]:
            g95[ic].GetYaxis().SetRangeUser(1,3500)
    gObs = mg[ic].GetListOfGraphs().FindObject("Observed").Clone()

    g95[ic].GetYaxis().SetTitleSize(0.047)
    g95[ic].GetXaxis().SetTitleSize(0.055)
    g95[ic].GetYaxis().SetLabelSize(0.045)
    g95[ic].GetXaxis().SetLabelSize(0.045)
    g95[ic].GetXaxis().SetLabelOffset(0.012)

    g95[ic].GetYaxis().SetTitleOffset(1.15)
    if not opt.logy : g95[ic].GetYaxis().SetTitleOffset(1.2)
    g95[ic].GetXaxis().SetTitleOffset(1.1)
    gxmin = -21
    gxmax = 32
    if benchmark == 999:
        gxmin = 240
        gxmax = 1000
    #plot in the format to be passed to the 2D Xanda's macro
    if benchmark < 0:
        print " "
        ipoint = 0
        for point in range(1507):
            if point in pointNumbers:
                o1, o2, e = Double(0), Double(0), Double(0)
                gObs.GetPoint(ipoint,Double(0),o2)
                gexp.GetPoint(ipoint,Double(0),e)
                print point+1, "{0:.4f}".format(o2), "{0:.4f}".format(o2), 0, 0, 0, 0
                #print point, "{0:.4f}".format(observed2d[ic][ipoint]), "{0:.4f}".format(expected2d[ic][ipoint]), 0, 0, 0, 0
                ipoint = ipoint +1
            else :
                print point+1, 9999, 9999, 0, 0, 0, 0

    if benchmark == 1:
        g95[ic].GetYaxis().SetRangeUser(1,100000)
        g95[ic].GetXaxis().SetRangeUser(-0.49+1.,11.49+1.)
    else :
        gymax = findMaxOfGraph(g95[ic])
        g95[ic].GetXaxis().SetRangeUser(gxmin,gxmax)
        g95[ic].GetYaxis().SetRangeUser(1,gymax*2)

    g95[ic].GetYaxis().SetTitle("95% CL on #sigma #times #bf{#it{#Beta}}(HH#rightarrow bb#tau#tau) [fb]")
    if benchmark == 1:
        g95[ic].GetXaxis().SetTitle("Benchmark number")
        g95[ic].GetXaxis().SetNdivisions(13)
    elif benchmark == 999:
        g95[ic].GetXaxis().SetTitle("M_H [GeV]")
    else:
        g95[ic].GetXaxis().SetTitle("k_{#lambda}/k_{t}")

    gStyle.SetOptTitle(0)
    if benchmark == 1:
        g95[ic].Draw("A2")
        g68.Draw("2SAME")
        gexp.Draw("PXSAME")
    elif benchmark == 0:
        g95[ic].Draw("A2")
        g68.Draw("2SAME")
        gexp.Draw("PXSAME")
    elif benchmark == 999:
        g95[ic].Draw("A3")
        g68.Draw("3SAME")
        gexp.Draw("PLXSAME")
    if addObserved:
        if benchmark>-1 and benchmark < 999:
            gObs.Draw("PSAME")
        else :
            gObs.Draw("PLSAME")
    legend = TLegend()
    legend.SetFillStyle(0)
    legend.SetBorderSize(0)
    legend.SetX1(0.630)
    legend.SetY1(0.699) #(0.171)
    legend.SetX2(0.974) #(1.026)
    legend.SetY2(0.89)  #(0.362)
    #elif not opt.logy :
        #legend.SetX1(0.15)
        #legend.SetY1(0.5)
        #legend.SetX2(0.546)
        #legend.SetY2(0.362-0.171+0.5)

    if addObserved : legend.AddEntry(gObs,"Observed","PL")
    legend.AddEntry(gexp, gexp.GetTitle(), "lp")
    legend.AddEntry(g68, g68.GetTitle(), "f")
    legend.AddEntry(g95[ic], g95[ic].GetTitle(), "f")

    # fakePlot = TGraphAsymmErrors ("fakePlot", "fakePlot", 100, 0, 100);
    fakePlot = TGraphAsymmErrors()
    fakePlot.SetFillColor(kRed)
    fakePlot.SetFillStyle(3001)
    fakePlot.SetLineColor(kRed)
    fakePlot.SetLineWidth(3)
    fakePlot2 = TGraphAsymmErrors()
    #fakePlot2.SetFillColor(kGray+1)
    #fakePlot2.SetLineColor(kGray+3)
    fakePlot2.SetFillColor(kRed+2)
    fakePlot2.SetLineColor(kRed+1)
    fakePlot2.SetFillStyle(3001)
    fakePlot2.SetLineWidth(3)
    if benchmark == 0:
        #legend.AddEntry(fakePlot, "Theory prediction, k_{t}=1", "lf")
        #legend.AddEntry(fakePlot, "Theory prediction, k_{t}=1", "lf")
        legend.AddEntry(fakePlot2, "Theory prediction", "lf")
        xmin=-20.4
        xmax=31.4
        if benchmark == 999 :
            print "new axis"
            xmin=240
            xmax=1000
        yt=1
        BR = 1
        myFunc =  TF1("myFunc","(2.09*[0]*[0]*[0]*[0] + 0.28*[0]*[0]*x*[0]*x*[0] -1.37*[0]*[0]*[0]*x*[0])*2.44185/[1]",xmin,xmax);
        myFunc.SetParameter(0,yt);
        myFunc.SetParameter(1,BR);
        #myFunc.SetParameter(2,yt);
        graph = TGraph(myFunc);
        ci = TColor.GetColor("#ff0000");
        cNice[ic].cd();
        graph.SetLineColor(ci);
        graph.SetLineWidth(2);
        graph.Draw("l");
        nP = int((xmax-xmin)*10.0)
        Graph_syst_Scale =  TGraphAsymmErrors()
        for i in range(nP):
            Graph_syst_Scale_x=(xmin+(i*1.)/10.)
            Graph_syst_Scale_y=(getExpValue(xmin+(i*1.)/10.,yt))
            #if Graph_syst_Scale_y > 800 and not opt.logy and  "Combined" in tooLopOn[ic] : continue
            Graph_syst_Scale_x_err=(0)
            Graph_syst_Scale_y_errup=(  (2.09*yt*yt*yt*yt+0.28*yt*yt*(xmin+(i*1.)/10.)*(xmin+(i*1.)/10.)-1.37*yt*yt*yt*(xmin+(i*1.)/10.))*2.44185*0.053/BR)
            Graph_syst_Scale_y_errdown=((2.09*yt*yt*yt*yt+0.28*yt*yt*(xmin+(i*1.)/10.)*(xmin+(i*1.)/10.)-1.37*yt*yt*yt*(xmin+(i*1.)/10.))*2.44185*0.067/BR)
            #Graph_syst_Scale.SetPoint(Graph_syst_Scale.GetN(),Graph_syst_Scale_x,Graph_syst_Scale_y)
            #Graph_syst_Scale.SetPointError(Graph_syst_Scale.GetN(),Graph_syst_Scale_x_err,Graph_syst_Scale_x_err,Graph_syst_Scale_y_errup,Graph_syst_Scale_y_errdown)
            Graph_syst_Scale.SetPoint(i,Graph_syst_Scale_x,Graph_syst_Scale_y)
            Graph_syst_Scale.SetPointError(i,Graph_syst_Scale_x_err,Graph_syst_Scale_x_err,Graph_syst_Scale_y_errup,Graph_syst_Scale_y_errdown)
        Graph_syst_Scale.SetLineColor(kRed)
        Graph_syst_Scale.SetFillColor(kRed)
        Graph_syst_Scale.SetFillStyle(3001)

        ytbis = 2
        Graph_syst_Scale2 =  TGraphAsymmErrors()
        for i in range(nP):
            Graph_syst_Scale2_x=(xmin+(i*1.)/10.)
            Graph_syst_Scale2_y=(getExpValue(2*(xmin+(i*1.)/10.),ytbis))
            #if Graph_syst_Scale2_y > 800 and not opt.logy and  "Combined" in tooLopOn[ic] : continue
            Graph_syst_Scale2_x_err=(0)
            Graph_syst_Scale2_y_errup=(  (2.09*ytbis*ytbis*ytbis*ytbis+0.28*ytbis*ytbis*2*(xmin+(i*1.)/10.)*2*(xmin+(i*1.)/10.)-1.37*ytbis*ytbis*ytbis*2*(xmin+(i*1.)/10.))*2.44185*0.053/BR)
            Graph_syst_Scale2_y_errdown=((2.09*ytbis*ytbis*ytbis*ytbis+0.28*ytbis*ytbis*2*(xmin+(i*1.)/10.)*2*(xmin+(i*1.)/10.)-1.37*ytbis*ytbis*ytbis*2*(xmin+(i*1.)/10.))*2.44185*0.067/BR)
            #Graph_syst_Scale2.SetPoint(Graph_syst_Scale2.GetN(),Graph_syst_Scale2_x,Graph_syst_Scale2_y)
            #Graph_syst_Scale2.SetPointError(Graph_syst_Scale2.GetN(),Graph_syst_Scale2_x_err,Graph_syst_Scale2_x_err,Graph_syst_Scale2_y_errup,Graph_syst_Scale2_y_errdown)
            Graph_syst_Scale2.SetPoint(i,Graph_syst_Scale2_x,Graph_syst_Scale2_y)
            Graph_syst_Scale2.SetPointError(i,Graph_syst_Scale2_x_err,Graph_syst_Scale2_x_err,Graph_syst_Scale2_y_errup,Graph_syst_Scale2_y_errdown)
        Graph_syst_Scale2.SetLineColor(kRed+1)
        Graph_syst_Scale2.SetFillColor(kRed+2)
        Graph_syst_Scale2.SetFillStyle(3001)
        myFunc.SetParameter(0,ytbis);
        myFunc.SetParameter(1,BR);
        graph2 = TGraph(myFunc);
        graph2.SetLineColor(kRed+1);
        graph2.SetLineWidth(2);
        graph2.Draw("l")
        Graph_syst_Scale.Draw("e3");
        Graph_syst_Scale2.Draw("e3");

        ##### labels for xs
        txt_kt1 = TLatex(30.5, 590.3, "k_{t} = 1")
        txt_kt1.SetTextAngle(48)
        txt_kt1.SetTextAlign(31)
        txt_kt1.SetTextSize(0.03)
        txt_kt1.SetTextFont(42)
        txt_kt1.SetTextColor(kRed+1) #kGray+3
        txt_kt1.Draw()

        txt_kt2 = TLatex(12.3, 750, "k_{t} = 2")
        txt_kt2.SetTextAngle(80)
        txt_kt2.SetTextAlign(31)
        txt_kt2.SetTextSize(0.03)
        txt_kt2.SetTextFont(42)
        txt_kt2.SetTextColor(kRed+2) #kGray+3
        txt_kt2.Draw()

    if benchmark > -1:
        legend.Draw()
    if opt.logy:
        cNice[ic].SetLogy()
    cNice[ic].SetGridy(1)
    cNice[ic].SetGridx(1)

    #pt = TPaveText(0.1663218,0.7966102,0.3045977,0.8898305,"brNDC")
    #pt.SetBorderSize(0)
    #pt.SetTextAlign(12)
    #pt.SetTextFont(62)
    #pt.SetTextSize(0.05)
    #pt.SetFillColor(0)
    #pt.SetFillStyle(0)
    #pt.AddText("CMS" )
    #pt.AddText("#font[52]{preliminary}")
    pt = TPaveText(0.2003218,0.9066667,0.3045977,0.957037,"brNDC")
    pt.SetBorderSize(0)
    pt.SetFillColor(0)
    pt.SetTextSize(0.040)
    pt.SetTextFont(42)
    pt.SetFillStyle(0)
    pt.AddText("#bf{CMS} #font[52]{preliminary}")
    pt2 = TPaveText(0.79,0.9066667,0.8997773,0.957037,"brNDC")
    pt2.SetBorderSize(0)
    pt2.SetFillColor(0)
    pt2.SetTextSize(0.040)
    pt2.SetTextFont(42)
    pt2.SetFillStyle(0)
    pt2.AddText("41.6 fb^{-1} (13 TeV)")

    pt4 = TPaveText(0.01,0.7780357,0.6192951,0.8675595,"brNDC")
    pt4.SetFillColor(0)
    pt4.SetFillStyle(0)
    pt4.SetTextFont(42)
    pt4.SetTextSize(0.05)
    pt4.SetBorderSize(0)
    pt4.AddText(channelsName[ic])
    if ic == 3 : pt4.AddText("#scale[0.8]{Combined channels}")
    if benchmark > -1:
        pt.Draw()
        pt2.Draw()
        pt4.Draw()

    app2=""
    if not opt.logy:
        app2 = "_lin_"
    if addObserved:
        app2 = app2 + "obs_"
    if benchmark == 0:
        app2 = app2 + "LambdaScan"
    elif benchmark == 1:
        app2 = app2 + "Benchmark"
    elif benchmark == 999:
        app2 = app2 + "Resonant"

    if not opt.logy:
        redrawBorder()

    if benchmark == 999:
        for ext in outFormats : cNice[ic].SaveAs("plots/2017stat/resonant/limit"+app2+"_"+tooLopOn[ic]+"_"+outString+ext)
        print "SAVED IN plots/2017stat/resonant"
    elif benchmark == 0:
        for ext in outFormats : cNice[ic].SaveAs("plots/2017stat/lambda_scan/limit"+app2+"_"+tooLopOn[ic]+"_"+outString+ext)
        print "SAVED IN plots/2017stat/lambda_scan"
    elif benchmark == 1:
        for ext in outFormats : cNice[ic].SaveAs("plots/2017stat/benchmarks/limit"+app2+"_"+tooLopOn[ic]+"_"+outString+ext)
        print "SAVED IN plots/2017stat/benchmarks"
    else:
        print "Plots NOT SAVED: no valid option provided!!"


if addObserved:
	print "table format "
	expE, obsE, massE = Double(0), Double(0), Double(0)
	expM, obsM, massM = Double(0), Double(0), Double(0)
	expT, obsT, massT = Double(0), Double(0), Double(0)
	expC, obsC, massC = Double(0), Double(0), Double(0)
	indexB = 0
	if not benchmark == 2:
		gexpE = mg[0].GetListOfGraphs().FindObject("Combined categories").Clone()
		gObsE = mg[0].GetListOfGraphs().FindObject("Observed").Clone()
		gexpM = mg[1].GetListOfGraphs().FindObject("Combined categories").Clone()
		gObsM = mg[1].GetListOfGraphs().FindObject("Observed").Clone()
		gexpT = mg[2].GetListOfGraphs().FindObject("Combined categories").Clone()
		gObsT = mg[2].GetListOfGraphs().FindObject("Observed").Clone()
		indexB = 3
	gexpC = mg[indexB].GetListOfGraphs().FindObject("Combined categories").Clone()
	gObsC = mg[indexB].GetListOfGraphs().FindObject("Observed").Clone()
	if not benchmark == 2:
		print "mass etau_obs etau_exp [-1sigma +1sigma] {-2sigma +2sigma} mutau_obs mutau_exp [-1sigma +1sigma] {-2sigma +2sigma} tautau_obs tautau_exp [-1sigma +1sigma] {-2sigma +2sigma} comb_obs comb_exp [-1sigma +1sigma] {-2sigma +2sigma} "
	else :
		print "mass comb_obs comb_exp [-1sigma +1sigma] {-2sigma +2sigma} "
	for point in range(gexp.GetN()):
		if not benchmark == 2 :
			gexpE.GetPoint(point,massE,expE)
			gObsE.GetPoint(point,massE,obsE)
			gexpM.GetPoint(point,massM,expM)
			gObsM.GetPoint(point,massM,obsM)
			gexpT.GetPoint(point,massT,expT)
			gObsT.GetPoint(point,massT,obsT)
		gexpC.GetPoint(point,massC,expC)
		gObsC.GetPoint(point,massC,obsC)
		if not benchmark == 2 : 
			if benchmark == 999 :
				print "%d & %.1f & (%.1f) & %.1f & (%.1f) & %.1f & (%.1f) & %.1f & (%.1f) \\ " % (massC,obsM,expM,obsE,expE,obsT,expT,obsC,expC)
			else : print "%d %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f " % (massE,obsE,expE,gexpE.GetErrorYlow(point),gexpE.GetErrorYhigh(point),g95[0].GetErrorYlow(point),g95[0].GetErrorYhigh(point),obsM,expM,gexpM.GetErrorYlow(point),gexpM.GetErrorYhigh(point),g95[1].GetErrorYlow(point),g95[1].GetErrorYhigh(point),obsT,expT,gexpT.GetErrorYlow(point),gexpT.GetErrorYhigh(point),g95[2].GetErrorYlow(point),g95[2].GetErrorYhigh(point),obsC,expC,gexpC.GetErrorYlow(point),gexpC.GetErrorYhigh(point),g95[3].GetErrorYlow(point),g95[3].GetErrorYhigh(point))
		else : 
			print "%d %.3f %.3f %.3f %.3f %.3f %.3f " % (massC,obsC,expC,gexpC.GetErrorYlow(point),gexpC.GetErrorYhigh(point),g95[0].GetErrorYlow(point),g95[0].GetErrorYhigh(point))	


#if not opt.draw : raw_input()

