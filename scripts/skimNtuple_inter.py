#!/usr/bin/env python

import os,sys
import optparse
import fileinput
import commands
import time
import glob
import subprocess
from os.path import basename
import ROOT


def isGoodFile (fileName) :
    ff = ROOT.TFile (fname)
    if ff.IsZombie() : return False
    if ff.TestBit(ROOT.TFile.kRecovered) : return False
    return True
    

# ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


if __name__ == "__main__":

    usage = 'usage: %prog [options]'
    parser = optparse.OptionParser(usage)
    parser.add_option ('-i', '--input'     , dest='input'     , help='input file'                          , default='none')
    parser.add_option ('-x', '--xs'        , dest='xs'        , help='sample xs'                             , default='1.')
    parser.add_option ('-f', '--force'     , dest='force'     , help='replace existing reduced ntuples'      , default=False)
    parser.add_option ('-o', '--output'    , dest='output'    , help='output folder'                         , default='none')
    parser.add_option ('-r', '--resub'     , dest='resub'     , help='resubmit failed jobs'                  , default='none')
    parser.add_option ('-v', '--verb'      , dest='verb'      , help='verbose'                               , default=False)
    parser.add_option ('-s', '--sleep'     , dest='sleep'     , help='sleep in submission'                   , default=False)
    parser.add_option ('-d', '--isdata'    , dest='isdata'    , help='data flag'                             , default=False)
    parser.add_option ('-c', '--config'    , dest='config'    , help='skim config file'                      , default='none')
    parser.add_option ('-n', '--njobs'     , dest='njobs'     , help='number of skim jobs'                   , default=100, type = int)
    parser.add_option ('-k', '--kinfit'    , dest='dokinfit'  , help='run HH kin fitter'                     , default=False)
    parser.add_option ('-m', '--mt2'       , dest='domt2'     , help='run stransverse mass calculation'      , default=True)
    parser.add_option ('-y', '--xsscale'   , dest='xsscale'   , help='scale to apply on XS for stitching'    , default='1.0')
    parser.add_option ('-Z', '--htcutlow'  , dest='htcutlow'  , help='HT low cut for stitching on inclusive' , default='-999.0')
    parser.add_option ('-z', '--htcut'     , dest='htcut'     , help='HT cut for stitching on inclusive'     , default='-999.0')
    parser.add_option ('-e', '--njets'     , dest='njets'     , help='njets required for stitching on inclusive'     , default='-999')
    parser.add_option ('-t', '--toprew'    , dest='toprew'    , help='is TT bar sample to compute reweight?' , default=False)
    parser.add_option ('-b', '--topstitch' , dest='topstitch' , help='type of TT gen level decay pruning for stitch'        , default='0')
    parser.add_option ('-g', '--genjets'   , dest='genjets'   , help='loop on genjets to determine the number of b hadrons' , default=False)
    parser.add_option ('-w', '--weight'    , dest='weightHH'  , help='histo map for hh reweight'             , default='0')
    parser.add_option ('-a', '--ishhsignal', dest='ishhsignal', help='isHHsignal'                            , default=False)
    parser.add_option ('--kl',               dest='klreweight', help='kl for dynamic reweight'              , default='-999.0')
    parser.add_option ('--kt',               dest='ktreweight', help='kt for dynamic reweight'              , default='-999.0')
    parser.add_option ('--c2',               dest='c2reweight', help='c2 for dynamic reweight'              , default='-999.0')
    parser.add_option ('--cg',               dest='cgreweight', help='cg for dynamic reweight'              , default='-999.0')
    parser.add_option ('--c2g',              dest='c2greweight', help='c2g for dynamic reweight'            , default='-999.0')
    parser.add_option ('--susy',             dest='susyModel' , help='name of susy model to select'         , default='NOTSUSY')
    parser.add_option ('--pu',               dest='PUweights' , help='external PUweights file'              , default='none')
    parser.add_option ('--nj',               dest='DY_nJets'  , help='number of gen Jets for DY bins'       , default='-1')
    parser.add_option ('--nb',               dest='DY_nBJets' , help='number of gen BJets for DY bins'      , default='-1')
    parser.add_option ('--DY',               dest='DY'        , help='if it is a DY sample'                 , default=False)
    
    (opt, args) = parser.parse_args()

    currFolder = os.getcwd ()


    # verify the result of the process
    # ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


    # submit the jobs
    # ---- ---- ---- ---- ---- ---- ---- ---- ---- ----


    skimmer = './bin/skimNtuple.exe'


    if opt.config == 'none' :
        print 'config file missing, exiting'
        sys.exit (1)

    if opt.input[-1] == '/' : opt.input = opt.input[:-1]
    if opt.output == 'none' : opt.output = opt.input + '_SKIM'
   
    if not os.path.exists (opt.input) :
        print 'input folder', opt.input, 'not existing, exiting'
        sys.exit (1)
        

    inputfile = opt.input

    jobsDir = currFolder + '/SKIM_' + basename (opt.input)
    jobsDir = jobsDir.rstrip (".txt")

    if os.path.exists (jobsDir) : os.system ('rm -f ' + jobsDir + '/*')
    else                        : os.system ('mkdir ' + jobsDir)
    
    os.system('echo '+ inputfile +' > '+ jobsDir +'/filelist.txt')


    os.system ('source scripts/setup.sh')
    command = skimmer + ' ' + jobsDir+"/filelist.txt" + ' ' + opt.output + ' ' + opt.xs
    if opt.isdata :  command += ' 1 '
    else          :  command += ' 0 '    
    command += ' ' + opt.config + ' '
    if opt.dokinfit=="True" : command += " 1 "
    else                    : command += " 0 "
    command += " " + opt.xsscale
    command += " " + opt.htcut
    command += " " + opt.htcutlow
    if opt.toprew=="True" : command += " 1 "
    else                  : command += " 0 "   
    if opt.genjets=="True": command += " 1 "
    else                  : command += " 0 "   
    command += (" " + opt.weightHH)
    command += " " + opt.topstitch
    if opt.domt2          : command += " 1 " ## inspiegabilmente questo e' un bool
    else                  : command += " 0 "
    if opt.ishhsignal     : command += " 1 "
    else                  : command += " 0 "
    command += (" " + opt.njets)
    command += (" " + opt.klreweight + " " + opt.ktreweight + " " + opt.c2reweight + " " + opt.cgreweight + " " + opt.c2greweight)
    command += (" " + opt.susyModel)
    command += (" " + opt.PUweights)
    command += (" " + opt.DY_nJets)
    command += (" " + opt.DY_nBJets)
    if opt.DY             : command += " 1 "
    else                  : command += " 0 "

        
    os.system (command)


    


