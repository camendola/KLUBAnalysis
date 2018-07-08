from ROOT import *

bkgList = ["DY",
           "TT",
           "WJets",
           "VVJJ",
           "singleT",
           "VBFC2V1XS",
           "ggHHXS"]

channel = 'TauTau'
var = 'MT2' ## oops! forgot mt2 here
#prefix = 's2b0jresolvedMcut_noVBF'
#prefix = 's1b1jresolvedMcut_noVBF'
prefix = 'sboostedLL_noVBF'
#prefix = 'VBF'
#prefix = 'sboostedLL_noVBF'
# channel = 'ETau'
# var = 'ditau_deltaR' ## oops! forgot mt2 here
# # list without the nominal
#inputFile = '/home/llr/cms/amendola/CMSSW_7_4_7/src/KLUBAnalysis/analysis_%s_VBF18Jun2018_combine_newOrder_sboost_noVBFscan/analyzedOutPlotter.root' % channel
inputFile = '/home/llr/cms/amendola/CMSSW_7_4_7/src/KLUBAnalysis/analysis_%s_VBF18Jun2018_combineTest_new_noMcut/analyzedOutPlotter.root' % channel


#selections=['sboostedLLMcut','s2b0jresolvedMcutlmr70','s1b1jresolvedMcutlmr70']
#selections=['sboostedLLMcut','s2b0jresolvedMcut','s1b1jresolvedMcut']
selections=['sboostedLL','s2b0jresolved','s1b1jresolved']


#selections = [prefix+'m300eta2',
#              prefix+'m400eta2',
#              prefix+'m500eta2',
#              prefix+'m600eta2',
#              prefix+'m650eta2',
#              prefix+'m700eta2',
#              prefix+'m750eta2',
#              prefix+'m800eta2',
#              prefix+'m900eta2',
#              prefix+'m1000eta2',
#              prefix+'m1500eta2',
#              prefix+'m2000eta2',
#              prefix+'m300eta3',
#              prefix+'m400eta3',
#              prefix+'m500eta3',
#              prefix+'m600eta3',
#              prefix+'m650eta3',
#              prefix+'m700eta3',
#              prefix+'m750eta3',
#              prefix+'m800eta3',
#              prefix+'m900eta3',
#              prefix+'m1000eta3',
#              prefix+'m1500eta3',
#              prefix+'m2000eta3',
#              prefix+'m300eta4',
#              prefix+'m400eta4',
#              prefix+'m500eta4',
#              prefix+'m600eta4',
#              prefix+'m650eta4',
#              prefix+'m700eta4',
#              prefix+'m750eta4',
#              prefix+'m800eta4',
#              prefix+'m900eta4',
#              prefix+'m1000eta4',
#              prefix+'m1500eta4',
#              prefix+'m2000eta4'
#]
              


print "doing channel: ", channel

#################


toscan = {'tes':'tau', 'jes':'jet'} ## will append "Up/Down"

print inputFile

fIn = TFile.Open(inputFile)

# DY0b_s2b0jresolvedMcutlmr70_tesDown_SR_MT2
## retrieve histograms
for sel in selections:
    for scale,obj in toscan.items():
        histos_nominal = {}
        histos_up      = {}
        histos_down    = {}
        
        for bkg in bkgList:
            hname_nominal = bkg + '_' + sel + '_SR_' + var 
            hname_up      = bkg + '_' + sel +'_SR_' + var + '_'+ obj + 'up'  
            hname_down    = bkg + '_' + sel +'_SR_' + var + '_'+ obj + 'down' 

            histos_nominal[bkg] = fIn.Get(hname_nominal)
            histos_up[bkg]      = fIn.Get(hname_up)
            histos_down[bkg]    = fIn.Get(hname_down)

        ## print this to a file
        fout = open (channel + '_' + sel + '_' + scale + '.txt', 'w')
        for bkg in bkgList:
            print sel, bkg, var
            ynom  = histos_nominal[bkg].Integral()
            yup   = histos_up[bkg].Integral()
            ydown = histos_down[bkg].Integral()

            shiftUp   = 1.0
            shiftDown = 1.0
            if ynom > 0 and histos_nominal[bkg].GetEntries() > 10:
                shiftUp = 1.*yup/ynom
                shiftDown = 1.*ydown/ynom
#            print bkg, shiftUp, shiftDown
                
            fout.write('%20s     ' % bkg)
            fout.write('%.3f     ' % shiftUp)
            fout.write('%.3f'      % shiftDown)
            fout.write('\n')
        fout.close()
