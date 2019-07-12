#! /usr/bin/env python
import sys, pwd, commands, optparse
import os
import re
import glob

def parseOptions():

    usage = ('usage: %prog [options]\n' + '%prog -h for help')
    parser = optparse.OptionParser(usage)
    
    parser.add_option('-r', '--resonant', dest='RESONANT', type='int', help='1:resonant 0:non-resonant analysis')
    parser.add_option('-s', '--spin'    , dest='SPIN'    , type='int', help='0:Radion, 2:Graviton')

    # store options and arguments as global variables
    global opt, args
    (opt, args) = parser.parse_args()



# Make cards with all vars/selections
print "*** CREATION of CARDS per CHANNEL/CATEGORY/GRIDPOINT ***"

# Parse the arguments
parseOptions()
if (opt.RESONANT == 1):
    if (opt.SPIN == 0) or (opt.SPIN == 2):
        print "Resonant Analysis Selected with Spin Hypothesis:", opt.SPIN
    else:
        print "ERROR!! Invalid spin option selected for resonant analysis (spin: %s), please choose between 0 (Radion) or 2 (Graviton)" % opt.SPIN
        sys.exit()
elif (opt.RESONANT == 0):
    print "Non-Resonant Analysis Selected"
else:
    print "ERROR!! Please provide at least one argument: 0 for Non-Resonant analysis or 1 for Resonant Analysis"
    sys.exit()



### CONFIGURABLES SECTION ###

# Do the combinations or not
doCombination = True

# Select the correct path to the current working directory
SOURCE = "/gwpool/users/brivio/Hhh_1718/syncFeb2018/May2019/CMSSW_9_0_0/src/KLUBAnalysis"

# Working directory for limit calculation
CF = SOURCE + "/combiner/BDTlimits"

# Quantiles for limit calculation
QUANTILES = [0.025, 0.16, 0.5, 0.84, 0.975, -1.0]

# Output directory tag
OUTSTRING = "2019_07_12_Resonant"

# Input directory tag
tag = "19June2019_limits"
nametag = "comb_limits"

# Selections
#SELECTIONS = ["baseline", "s1b1jresolved", "s2b0jresolved", "sboostedLL"]
SELECTIONS = ["s1b1jresolved", "s2b0jresolved", "sboostedLL"]
#SELECTIONS = ["s1b1jresolved"]

# Channels
#CHANNELS = ["MuTau", "ETau", "TauTau"]
CHANNELS=["TauTau"]


# Build the correct variables if doing resonant/non-resonant and create the GridPoints/Hypotheses list
# GridPoints: names for variables and directory creation
# Hypotheses: mass points or lambdas

if (opt.RESONANT == 0):
    VARIABLE = "BDToutSM_kl"
    LAMBDAS = [1] #(0, 1, 2.45, 5, 30)

    HYPOTHESES  = LAMBDAS
    GRIDPOINTS  = [VARIABLE+"_"+str(l) for l in LAMBDAS] # names for the directories
    MHYPOTHESES = ["125" for hypo in HYPOTHESES]         # actual masses (always 125 GeV for non-resonant case)

    NAMESAMPLE = "GGFHH" #"ggHH"
else:
    LM_masses  = [250, 260, 270, 280, 300, 320]
    MM_masses  = [350, 400]
    HM_masses  = [450, 500, 550, 600, 650, 700, 750, 800, 850, 900]
    VHM_masses = [1000, 1250, 1500, 1750, 2000, 2500, 3000] # not used for now

    LM_masses  = [280]
    MM_masses  = [400]
    HM_masses  = [650]

    HYPOTHESES = LM_masses + MM_masses + HM_masses   # names for the directories
    MHYPOTHESES = [str(hypo) for hypo in HYPOTHESES] # actual masses (mass of the resonances for the resonant case)

    GRIDPOINTS = []
    for mass in LM_masses:
        VARIABLE = "BDToutLM_spin_"+str(opt.SPIN)+"_mass_"
        GRIDPOINTS.append(VARIABLE+str(mass))
    for mass in MM_masses:
        VARIABLE = "BDToutMM_spin_"+str(opt.SPIN)+"_mass_"
        GRIDPOINTS.append(VARIABLE+str(mass))
    for mass in HM_masses:
        VARIABLE = "BDToutHM_spin_"+str(opt.SPIN)+"_mass_"
        GRIDPOINTS.append(VARIABLE+str(mass))

    if (opt.SPIN == 0):
        NAMESAMPLE = "GGFHH_Radion"
    else:
        NAMESAMPLE = "GGFHH_Graviton"

# Printing all configurables
print "Channels    : ", CHANNELS
print "Categories  : ", SELECTIONS
print "NameSample  : ", NAMESAMPLE
print "GridPoints  : ", GRIDPOINTS
print "Hypotheses  : ", HYPOTHESES
print "MHypotheses : ", MHYPOTHESES

### END OF CONFIGURABLES SECTION ###

# Create all the cards 3 categories x 3 channels x n GridPoints
for BASE in SELECTIONS:
    print "- Doing selection:", BASE
    
    for c in CHANNELS:
        print "    Doing channel:", c

        for i,GRIDPOINT in enumerate(GRIDPOINTS):
            print "      Doing gridpoint:", GRIDPOINT

            # -- with CHCARDMAKER.PY --
            #command_mkcard = 'python chcardMaker.py -f '+SOURCE+'/analysis_'+c+'_'+tag+'/wrapped/analyzedOutPlotter_'+c+'_'+nametag+'.root -o _'+OUTSTRING+' -c '+c+' -i '+SOURCE+'/analysis_'+c+'_'+tag+'/mainCfg_'+c+'.cfg -s '+BASE+' -r '+str(opt.RESONANT)+' -u 0 -t 1 --lambda '+NAMESAMPLE+' -g '+GRIDPOINT+' -m '+MHYPOTHESES[i]

            # -- with CARDMAKER.PY / no QCD plots --
            #command_mkcard = 'python cardMaker.py -f '+SOURCE+'/analysis_'+c+'_'+tag+'/outPlotter.root -q _'+OUTSTRING+' -c '+c+' -i '+SOURCE+'/analysis_'+c+'_'+tag+'/mainCfg_'+c+'.cfg -o '+BASE+' -r '+str(opt.RESONANT)+' -u 0 -t 1 -a --lambda '+NAMESAMPLE+' -g '+GRIDPOINT+' -m '+MHYPOTHESES[i]

            # -- with CARDMAKER.PY / with QCD plots and BBBuncertainties --
            command_mkcard = 'python cardMaker.py -f '+SOURCE+'/analysis_'+c+'_'+tag+'/analyzedOutPlotter.root -q _'+OUTSTRING+' -c '+c+' -i '+SOURCE+'/analysis_'+c+'_'+tag+'/mainCfg_'+c+'.cfg -o '+BASE+' -r '+str(opt.RESONANT)+' -u 0 -t 1 -a -y --lambda '+NAMESAMPLE+' -g '+GRIDPOINT+' -m '+MHYPOTHESES[i]

            os.system(command_mkcard)

print " "
print "- - - - CREATED ALL CARDS - - - -"
print " "
print "* * * * START LIMIT CALCULATION per CHANNEL/CATEGORY/HYPOTHESES * * * *"
print " "

# Compute limits for all the cards 3 categories x 3 channels x n GridPoints/hypotesis
for BASE in SELECTIONS:
    print "- Doing selection:", BASE
    
    for c in CHANNELS:
        print "    Doing channel:", c

        for j,GRIDPOINT in enumerate(GRIDPOINTS):
            print "      Doing gridpoint:", GRIDPOINT, " - Hypotesis:", str(HYPOTHESES[j])

            command_cd = CF+'/cards_'+c+'_'+OUTSTRING+'/'+NAMESAMPLE+BASE+GRIDPOINT
            os.chdir(command_cd)
            os.system('pwd')

            command_combineCards = 'combineCards.py -S hh_*.txt >> comb.txt'
            os.system(command_combineCards)

            command_text2Workspace = 'text2workspace.py -m '+MHYPOTHESES[j]+' comb.txt -o comb.root'
            os.system(command_text2Workspace)

            os.system('ln -ns ../../prepareHybrid.py .')
            os.system('ln -ns ../../prepareGOF.py .')
            os.system('ln -ns ../../prepareAsymptotic.py .')

            command_prepareAsymp = 'python prepareAsymptotic.py -m '+MHYPOTHESES[j]+' -n '+NAMESAMPLE+'_'+str(HYPOTHESES[j])
            os.system(command_prepareAsymp)

            os.chdir(CF)

print " "
print "- - - - COMPUTED LIMITS FOR SINGLE HYPOTHESES - - - -"
print " "

if not doCombination:
    sys.exit()

print "* * * * START LIMIT CALCULATION per COMBINATIONS * * * *"
print " "
# CATEGORY COMBINATION
for k,GRIDPOINT in enumerate(GRIDPOINTS):
    print "- Doing gridpoint:", GRIDPOINT, " - Hypotesis:", str(HYPOTHESES[k]), " - Mass:", MHYPOTHESES[k]

    os.chdir(CF)
    command_mkdir = 'mkdir -p cards_Combined_'+OUTSTRING+'/'+NAMESAMPLE+GRIDPOINT
    os.system(command_mkdir)

    for BASE in SELECTIONS:
        print "    Doing selection:", BASE
        
        command_mkdir2 = 'mkdir -p cards_Combined_'+OUTSTRING+'/'+NAMESAMPLE+BASE+GRIDPOINT
        os.system(command_mkdir2)

        for c in CHANNELS:
            print "      Doing channel:", c

            command_mkdir3 = 'mkdir -p cards_'+c+'_'+OUTSTRING+'/'+NAMESAMPLE+GRIDPOINT
            os.system(command_mkdir3)

            command_cp1 = 'cp cards_'+c+'_'+OUTSTRING+'/'+NAMESAMPLE+BASE+GRIDPOINT+'/hh_*.* cards_Combined_'+OUTSTRING+'/'+NAMESAMPLE+BASE+GRIDPOINT+'/.'
            command_cp2 = 'cp cards_'+c+'_'+OUTSTRING+'/'+NAMESAMPLE+BASE+GRIDPOINT+'/hh_*.* cards_Combined_'+OUTSTRING+'/'+NAMESAMPLE+GRIDPOINT+'/.'
            command_cp3 = 'cp cards_'+c+'_'+OUTSTRING+'/'+NAMESAMPLE+BASE+GRIDPOINT+'/hh_*.* cards_'+c+'_'+OUTSTRING+'/'+NAMESAMPLE+GRIDPOINT+'/.'
            os.system(command_cp1)
            os.system(command_cp2)
            os.system(command_cp3)

            command_cp1_temp2 = 'cp cards_'+c+'_'+OUTSTRING+'/'+NAMESAMPLE+BASE+GRIDPOINT+'/temp2_*.* cards_Combined_'+OUTSTRING+'/'+NAMESAMPLE+BASE+GRIDPOINT+'/.'
            command_cp2_temp2 = 'cp cards_'+c+'_'+OUTSTRING+'/'+NAMESAMPLE+BASE+GRIDPOINT+'/temp2_*.* cards_Combined_'+OUTSTRING+'/'+NAMESAMPLE+GRIDPOINT+'/.'
            command_cp3_temp2 = 'cp cards_'+c+'_'+OUTSTRING+'/'+NAMESAMPLE+BASE+GRIDPOINT+'/temp2_*.* cards_'+c+'_'+OUTSTRING+'/'+NAMESAMPLE+GRIDPOINT+'/.'
            os.system(command_cp1_temp2)
            os.system(command_cp2_temp2)
            os.system(command_cp3_temp2)


        os.chdir('cards_Combined_'+OUTSTRING+'/'+NAMESAMPLE+BASE+GRIDPOINT)

        if (glob.glob('hh_*_C1_*_13TeV.txt')):
            os.system('combineCards.py -S hh_*_C1_*_13Te*.txt >> comb.txt')

        if (glob.glob('hh_*_C2_*_13TeV.txt')):
            os.system('combineCards.py -S hh_*_C2_*_13Te*.txt >> comb.txt')

        if (glob.glob('hh_*_C3_*_13TeV.txt')):
            os.system('combineCards.py -S hh_*_C3_*_13Te*.txt >> comb.txt')

        command_text2workspace2 = 'text2workspace.py -m '+MHYPOTHESES[k]+' comb.txt -o comb.root'
        os.system(command_text2workspace2)

        os.system('ln -ns ../../prepareHybrid.py .')
        os.system('ln -ns ../../prepareGOF.py .')
        os.system('ln -ns ../../prepareAsymptotic.py .')

        command_prepareAsymp = 'python prepareAsymptotic.py -m '+MHYPOTHESES[k]+' -n '+NAMESAMPLE+'_'+str(HYPOTHESES[k])
        os.system(command_prepareAsymp)

        os.chdir(CF)

    # limit on the combination of the categories
    os.chdir('cards_Combined_'+OUTSTRING+'/'+NAMESAMPLE+GRIDPOINT)
    os.system('rm comb.*')

    command_combineCards2 = 'combineCards.py -S hh_*_C*_*_13Te*.txt >> comb.txt'
    os.system(command_combineCards2)

    command_text2workspace3 = 'text2workspace.py -m '+MHYPOTHESES[k]+' comb.txt -o comb.root'
    os.system(command_text2workspace3)

    os.system('ln -ns ../../prepareHybrid.py .')
    os.system('ln -ns ../../prepareGOF.py .')
    os.system('ln -ns ../../prepareAsymptotic.py .')
    os.system('ln -ns ../../prepareImpacts.py .')
    
    command_prepareAsymp2 = 'python prepareAsymptotic.py -m '+MHYPOTHESES[k]+' -n '+NAMESAMPLE+'_'+str(HYPOTHESES[k])
    os.system(command_prepareAsymp2)

    os.chdir(CF)


    #MAKE COMBINATION FOR CHANNEL [3 x mass point]
    for c in CHANNELS:
        os.chdir('cards_'+c+'_'+OUTSTRING+'/'+NAMESAMPLE+GRIDPOINT)
        os.system('rm comb.*')

        command_combineCards3 = 'combineCards.py -S hh_*_C*_*_13Te*.txt >> comb.txt'
        os.system(command_combineCards3)

        command_text2workspace4 = 'text2workspace.py -m '+MHYPOTHESES[k]+' comb.txt -o comb.root'
        os.system(command_text2workspace4)

        os.system('ln -ns ../../prepareHybrid.py .')
        os.system('ln -ns ../../prepareGOF.py .')
        os.system('ln -ns ../../prepareAsymptotic.py .')
        
        command_prepareAsymp3 = 'python prepareAsymptotic.py -m '+MHYPOTHESES[k]+' -n '+NAMESAMPLE+'_'+str(HYPOTHESES[k])
        os.system(command_prepareAsymp3)

        os.chdir(CF)








