#!/usr/bin/python

from ROOT import *
from array import *



DIR = '/data_CMS/cms/amendola/TestSelections/TT_background/'

#CATEGORIES = ['fullyHad', 'fullyLep', 'semiLep']
#CATEGORIES = ['fullyHad']
CATEGORIES = ['fullyLep','semiLep']
pairType = ['tautau','mutau','etau']
base = ['1b1jMcut','2b0jMcut']
region = ['SR','SStight']
selection= {} 

for pair in pairType:         
          if pair == 'tautau':
               for y in region: 
                    for x in base:     
                        # selection.append(pair+'_'+x+'_'+y)
                        selection[pair+'_'+x+'_'+y]= 0
          else:
               for x in base:     
                    #selection.append(pair+'_'+x+'_SR')
                    #selection.append(pair+'_'+x+'BDT_SR')
                    selection[pair+'_'+x+'_SR'] = 0
                    selection[pair+'_'+x+'BDT_SR'] = 0
for x in selection:
    print x

#gROOT.ProcessLine("struct _values{")
#for x in selection:
#     line = 'int '+x+';'
#     gROOT.ProcessLine(line)
#gROOT.ProcessLine("}")

for cat in CATEGORIES:
     
     fIn   = TFile.Open(DIR+cat+'/final_sel.root')
     print DIR+cat+'/final_sel.root'
     tIn   = fIn.Get('HTauTauTreeSelections')
#     values = _values()
#     value = defineArray('d', 15)
#     tIn.SetBranchAddress("EventNumber",value)
#     tIn.SetBranchAddress("RunNumber",value)
#     tIn.SetBranchAddress("lumi",lumi)
#     for x in selection:      
#          tIn.SetBranchAddress(x,selection[x])
     
     nEvt  = tIn.GetEntries()    
     fOut  = open(DIR+cat+"/"+cat+"_SelectedEvents_unsorted.txt","w")
     fOutSort  = open(DIR+cat+"/"+cat+"_SelectedEvents.txt","w")
     fOut.write("EventNumber\tRunNumber\tlumi")
     for x in selection:
          fOut.write("\t"+x)
     fOut.write("\n")



     for evt in range(0,nEvt):
          if (evt%1000 == 0): print ('Event {0} / {1}'.format(evt,nEvt))
         # load = tIn.LoadTree(evt)
         # entry = tIn.GetEntry(evt)
          tIn.GetEntry(evt)
          EventNumber = str(tIn.EventNumber)
          RunNumber = str(tIn.RunNumber)
          lumi = str(tIn.lumi)
          #print tIn.EventNumber
          #print tIn.RunNumber
          #print tIn.lumi
          #print ('event {0} lumi {1}  Run {2}'.format(EventNumber,lumi, RunNumber))
          #print 'event '+EventNumber+'Run '+RunNumber+'lumi '  
          for x in selection:
               execline= 'selection[x] = tIn.'+x 
               exec(execline)   
          doWrite = 0
          for x in selection:
               if selection[x] == 1:
                    doWrite = 1
          if doWrite == 1:
             #  print '+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++'
               fOut.write(EventNumber+'\t'+RunNumber+'\t'+lumi+'\t')
               for x in selection:
                    string = str(selection[x])
                    fOut.write(string+'\t')
               fOut.write('\n')
     fIn.Close()
     fOut.close()

     toSort = open(DIR+cat+"/"+cat+"_SelectedEvents_unsorted.txt","r")

     all_lines = toSort.readlines()
     
     head = [line for line in all_lines if line.startswith("E")]
     print head
     some_lines = [line for line in all_lines if not line.startswith("E")]
     def get_nEvent(line):
          numbers = [int(s) for s in line.split() if s.isdigit()]
          event = numbers[0]
          return int(event)     
     some_lines = sorted(some_lines, key=get_nEvent)
     for line in head:
          fOutSort.write(line)
     for line in some_lines:
          #print line
          fOutSort.write(line)

     toSort.close()
     fOutSort.close()


