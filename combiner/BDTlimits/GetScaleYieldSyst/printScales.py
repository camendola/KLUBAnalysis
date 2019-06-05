# Original script in: KLUBAnalysis/studies/GetScaleYieldSyst/printScales.py

from ROOT import *

# list of processes
bkgList = ["DY", "TT", "WJets", "singleT", "EWKW", "SM", "VVV", "TTV", "TTVV", "VV", 'ggHH', 'VBFSM']

# channel, variable and selections
channel = 'TauTau'
var = 'BDToutSM_kl_1'
selections = ['baseline', 's1b1jresolved', 's2b0jresolved']

print "doing channel: ", channel

#################

inputFile = '/gwpool/users/brivio/Hhh_1718/syncFeb2018/May2019/CMSSW_9_0_0/src/KLUBAnalysis/analysis_%s_18Dec2018_limits/outPlotter.root' % channel
toscan = [''] #['tes', 'jes'] ## will append "Up/Down"

print "input file: ", inputFile

fIn = TFile.Open(inputFile)

# DY0b_s2b0jresolvedMcutlmr70_tesDown_SR_MT2
# DY_baseline_SR_BDToutSM_kl_1
## retrieve histograms
for sel in selections:
    for scale in toscan:
        histos_nominal = {}
        histos_up      = {}
        histos_down    = {}
        
        for bkg in bkgList:
            #hname_nominal = bkg + '_' + sel + '_nominal_SR_' + var
            #hname_up      = bkg + '_' + sel + '_' + scale + 'Up_SR_'   + var
            #hname_down    = bkg + '_' + sel + '_' + scale + 'Down_SR_' + var
            hname_nominal = bkg + '_' + sel + '_SR_' + var           # for now no up/down variations
            hname_up      = bkg + '_' + sel + '_SR_' + var           # for now no up/down variations
            hname_down    = bkg + '_' + sel + '_SR_' + var           # for now no up/down variations

            histos_nominal[bkg] = fIn.Get(hname_nominal)
            histos_up[bkg]      = fIn.Get(hname_up)
            histos_down[bkg]    = fIn.Get(hname_down)

        ## print this to a file
        fout = open (channel + '_' + sel + '_' + scale + '.txt', 'w')
        for bkg in bkgList:
            # print sel, var, bkg
            ynom  = histos_nominal[bkg].Integral()
            yup   = histos_up[bkg].Integral()
            ydown = histos_down[bkg].Integral()

            shiftUp   = 1.0
            shiftDown = 1.0
            if ynom > 0 and histos_nominal[bkg].GetEntries() > 10:
                shiftUp = 1.*yup/ynom
                shiftDown = 1.*ydown/ynom

            fout.write('%20s     ' % bkg)
            fout.write('%.3f     ' % shiftUp)
            fout.write('%.3f'      % shiftDown)
            fout.write('\n')
        fout.close()