#!/bin/bash
# make cards with all vars/selections

export OUTSTRING="2019_06_04"

export STRINGLEPTONS="$1"

export tag="18Dec2018_limits"

#export SELECTIONS="s2b0jresolvedMcut${STRINGLEPTONS} s1b1jresolvedMcut${STRINGLEPTONS} sboostedLLMcut"
#export SELECTIONS="s2b0jresolvedMcut s1b1jresolvedMcut sboostedLLMcut"
#export SELECTIONS="VBFeta_1b1j VBFeta_2b0j VBFeta_High_Eta_1bM VBFeta_Low_Eta_1bM VBFmjj_1b1j VBFmjj_2b0j VBFmjj_High_Eta_1bM VBFmjj_Low_Eta_1bM"
export SELECTIONS="baseline s1b1jresolved s2b0jresolved"
#export SELECTIONS="baseline"

export NAMESAMPLE="ggHH"

export RESONANT=$2

#export LEPTONS="MuTau ETau TauTau"
#export LEPTONS="ETau"
export LEPTONS="TauTau"

export CF="$CMSSW_BASE/src/KLUBAnalysis/combiner"

if [ "${RESONANT}" != "-r" ]
    then
    #export VARIABLE="MT2"
    export VARIABLE="BDToutSM_kl"
    #export LAMBDAS=""
    #export INSELECTIONS="s2b0jresolvedMcutlmr90 s1b1jresolvedMcutlmr90 s2b0jresolvedMcuthmr90 s1b1jresolvedMcuthmr90 sboostedLLMcut s1b1jresolvedMcutlmr70 s2b0jresolvedMcutlmr70 s1b1jresolvedMcutLepTauKine s2b0jresolvedMcutLepTauKine"
    #for il in {0..51}
    #for il in {0..1}
    #    do
    #    export LAMBDAS="$LAMBDAS ${il}"
    #done
    export GRIDPOINTS="0 1"
else
    export VARIABLE="HHKin_mass_raw"
    export NAMESAMPLE="Radion"
    #export LAMBDAS="Radion250 Radion260 Radion270 Radion280 Radion300 Radion320 Radion340 Radion400 Radion450 Radion500 Radion550 Radion600 Radion650 Radion700 Radion750 Radion800 Radion900"
    #export LAMBDAS="Radion250"
    #export LAMBDAS="250 270 280 300 350 400 450 500 550 600 650 750 900"
    export GRIDPOINTS="300"
fi

export QUANTILES="0.025 0.16 0.5 0.84 0.975 -1.0"
export SOURCE="/gwpool/users/brivio/Hhh_1718/syncFeb2018/May2019/CMSSW_9_0_0/src/KLUBAnalysis"

#create all the cards 3 categories x 3 channels
for ibase in $SELECTIONS
do
    for c in $LEPTONS
    do
        if [ "${c}" == "MuTau" ]
            then
            export BASE="$ibase"
        fi
        if [ "${c}" == "ETau" ]
            then
            export BASE="$ibase"
        fi
        if [ "${c}" == "TauTau" ]
            then
            export BASE=${ibase/${STRINGLEPTONS}/}
        fi
        echo "-- Doing selection: $BASE"

        for GRIDPOINT in $GRIDPOINTS
        do
            echo "--- Doing gridpoint: ${GRIDPOINT}"


        #echo "-f: ${SOURCE}/analysis_${c}_${tag}/analyzedOutPlotter.root"
        #echo "-o: _${OUTSTRING}"
        #echo "-c: ${c}"
        #echo "-i: ${SOURCE}/analysis_${c}_${tag}/mainCfg_${c}.cfg"
        #echo "-s: ${BASE}"
        #echo "-r: ${RESONANT}"
        #echo "-selection: $ibase"
        #echo "lambdas: ${LAMBDAS}"

        #python cardMaker.py -i ${SOURCE}/analysis_${c}_1Feb_lims/mainCfg_${c}.cfg -f ${SOURCE}/analysis_${c}_1Feb_lims/analyzedOutPlotter.root   -o $BASE -c ${c}   --dir "_$OUTSTRING" -t 0 ${RESONANT} 
        #python chcardMaker.py -f ${SOURCE}/analysis_${c}_19Feb/analyzedOutPlotter.root -o ${OUTSTRING} -c ${c} -i ${SOURCE}/analysis_${c}_19Feb/mainCfg_TauTau.cfg -y -s ${BASE} ${RESONANT} -u 0
        #python chcardMaker.py -f analyzedOutPlotter_01Mar_2D_${c}.root -o "_${OUTSTRING}" -c ${c} -i ${SOURCE}/analysis_${c}_1Mar_lims_2dscan/mainCfg_${c}.cfg -y -s ${BASE} ${RESONANT} -u 1 -t 
        #python chcardMaker.py -f analyzedOutPlotter_2017_03_10_${c}.root -o "_${OUTSTRING}" -c ${c} -i ${SOURCE}/analysis_${c}_10Mar_lims/mainCfg_${c}.cfg -y -s ${BASE} ${RESONANT} -u 1 -t
        #python chcardMaker.py -f ${SOURCE}/testPlot_TauTau_VBF/VBF_TauTau_11Gen18_2/analyzedOutPlotter.root -o "_${OUTSTRING}" -c ${c} -i ${SOURCE}/config/mainCfg_VBF_${c}.cfg -s ${BASE} ${RESONANT} -u 0 -t --lambda "VBFC2V1" --selection $ibase

        python chcardMaker.py -f ${SOURCE}/analysis_${c}_${tag}/wrapped/analyzedOutPlotter_TauTau_BDTtest.root -o "_${OUTSTRING}" -c ${c} -i ${SOURCE}/analysis_${c}_${tag}/mainCfg_${c}.cfg -s ${BASE} -r ${RESONANT} -u 0 -t 0 --lambda "ggHH" --selection $ibase -v ${VARIABLE} -g ${GRIDPOINT}

#done
#for base in $SELECTIONSTAU
#do
    #python cardMaker.py -i ${SOURCE}/analysis_TauTau_26Gen/mainCfg_TauTau.cfg   -f ${SOURCE}/analysis_TauTau_26Gen/analyzedOutPlotter.root -o $BASE -c TauTau --dir "_$OUTSTRING" -t 0 # -r #-S /home/llr/cms/cadamuro/FittedHHKinFit/outPlotter_fit_sigs_TauTau.root

        done # close GRIPOINTS  loop
    done     # close LEPTONS    loop
done         # close SELECTIONS loop

echo " "
echo "CREATED ALL CARDS"

