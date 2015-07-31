#!/usr/bin/python
import os
import re
import math
import collections
from ROOT import *
from array import array

## ---------------------------------------------------------------
## card reader class
## ---------------------------------------------------------------

class configReader:

    def __init__(self, inputTextFile):

        if not os.path.exists(inputTextFile):
            raise RuntimeError, "File {0} does not exist!!!".format(inputTextFile)
        
        # input file
        self.theInput = inputTextFile
        # lumi
        self.lumi = -999.9
        # sqrts
        #self.sqrts = -999.9
        # channels
        self.signals=[]
        self.background=[]
        self.datasamples=[]
        #self.all_chan = False
        #self.Lambda1_chan = False
        #self.Lambda20_chan = False
#
        #self.DY_chan = False
        #self.TT_chan = False
        #self.TWtop_chan = False
        #self.TWantitop_chan = False
        #self.Tt_chan = False
        #self.WW2l2v_chan = True
        #self.WWlvqq_chan = True
        #self.WWinc_chan = True
        #self.WZinc_chan = True
        #self.WJet_chan = True

        # Variables
        self.AllVars = []
        self.AllBins = []
        self.AllvarX = []
        self.AllvarY = []
        self.varX = -999
        self.varY = -999
        self.selectionLevel = ""
        self.dimensions = -999
 
        # systematics 
        self.lumiUnc = -999.9

        self.CMS_zz4l_mean_m_sig = -999.9
        self.CMS_zz4l_sigma_m_sig = -999.9
        self.CMS_zz4l_mean_e_sig = -999.9
        self.CMS_zz4l_sigma_e_sig = -999.9

        self.useLumiUnc = False
        self.useCMS_zz4l_mean = False
        self.useCMS_zz4l_sigma = False


    def goodEntry(self,variable):
        if variable == -999.9:
            return False
        else:
            return True


    def parseBoolString(self,theString):

        return theString[0].upper()=='T'


    def readInputs(self):
        print "reading inputs"
        section = ""
        varXname = ""
        varYname = ""
        varnames = []
        for line in open(self.theInput,'r'):
            f = line.split()

            if len(f) < 1: continue
            if f[0].startswith("#"): continue

            if f[0].startswith('['):
                #print f
                f = re.split('\W+',line)
                #print f
                section = f[1]
                print section
		continue
            if section is not "histos":
                if section is not "cardmaker" : f = re.split('\W+',line)
            #f = re.split('\W+',line)
            if section == "general":
                #f = re.split('\W+',line)
                if f[0] == 'signals' : 
                    for sample in range(1,len(f)): self.signals.append(f[sample])
                elif f[0] == "backgrounds": 
                    for sample in range(1,len(f)): self.background.append(f[sample])
                elif f[0] == "data": 
                    for sample in range(1,len(f)): self.datasamples.append(f[sample])

 #               for chan in f:
 #                   if chan == f[0]: continue
 #                   if chan.lower().startswith("ggh"):     self.ggH_chan = True
 #                   elif chan.lower().startswith("qqh"):   self.qqH_chan = True
 #                   elif chan.lower().startswith("wh"):    self.WH_chan = True
 #                   elif chan.lower().startswith("zh"):    self.ZH_chan = True
 #                   elif chan.lower().startswith("tth"):   self.ttH_chan = True
 #                   elif chan.lower().startswith("qqzz"):  self.qqZZ_chan = True
 #                   elif chan.lower().startswith("ggzz"):  self.ggZZ_chan = True
 #                   elif chan.lower().startswith("zjets"): self.zjets_chan = True
 #                   elif chan.lower().startswith("ttbar"): self.ttbar_chan = True
 #                   elif chan.lower().startswith("zbb"):   self.zbb_chan = True
 #                   elif chan.lower().startswith("all"):   self.all_chan = True
 #                   else : raise RuntimeError, "Unknown channel {0}, choices are ggH, qqH, WH, ZH, ttH, qqZZ, ggZZ, zjets".format(chan)
  	        #continue

            if section == "systematics": #devo capire che formato sare    
                continue
            #print f        
            if f[0] == "lumi" :
                self.lumi = float(f[1])
                print "lumi ", self.lumi
            #print section
            if section == "histos":
                self.AllVars.append(f[0]) #f[1]="="
                self.AllBins.append(re.sub(',', '', f[1]))
                self.AllvarX.append(re.sub(',', '', f[2]))
                self.AllvarY.append(re.sub(',', '', f[3]))
                
            if f[0] == "cardsvariables":
                #print f
                varnames.append(f[1])
                varnames.append(f[2])
                print varnames
                #varXname = f[2]
                #print self.varX
                if len(f)>3 : 
                    #varYname = f[3]
                    self.dimensions = 2
                else :  self.dimensions = 1 
           
            if f[0] == "cardsselection":
                self.selectionLevel = f[1]

        for iname in range(len(self.AllVars)):
            #print self.AllVars[iname]#, varXname
            #varnames = f[2].split(':')
            #print varnames
            if self.AllVars[iname] == re.sub('_','',varnames[0]):
                    print "GOTCHA"
                    self.varX = iname
                    self.AllVars[iname] = varnames[0]
            elif self.dimensions>1:
                    if self.AllVars[iname] == re.sub('_','',varnames[1]):
                        self.varY = iname
                        self.AllVars[iname] = varnames[1]

    
    def getInputs(self):

        dict = {}

        ## check settings ##
        
        if self.varX == "":
            print "Variable X is not set. Using {0} for X.".format("HHKinMass")
            self.varX = "HHKinMass"
        if self.cardsselection == "":
            print "Selection level not set. Using all instead"
            self.selectionLevel = "all"

      ## Set dictionary entries to be passed to datacard class ##
        
        dict['lumi'] = float(self.lumi)
        dict['varX'] = self.varX
#        dict['signals'] = self.signals

#        dict['all'] = self.all_chan
#        dict['ggH'] = self.ggH_chan
#        dict['qqH'] = self.qqH_chan
#        dict['WH'] = self.WH_chan
#        dict['ZH'] = self.ZH_chan
#        dict['ttH'] = self.ttH_chan
#        dict['ggH_SM'] = self.ggH_chan
#        dict['qqH_SM'] = self.qqH_chan
#        dict['WH_SM'] = self.WH_chan
#        dict['ZH_SM'] = self.ZH_chan
#        dict['ttH_SM'] = self.ttH_chan
#        dict['qqZZ'] = self.qqZZ_chan
#        dict['ggZZ'] = self.ggZZ_chan

        return dict