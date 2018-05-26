#!/bin/bash
# make cards with all vars/selections
export out="incl_noVBF"
#export out="incl"
export CATEGORIES="sboost_noVBF s1b1j_noVBF s2b0j_noVBF"
#export CATEGORIES="VBF sboost_noVBF s1b1j_noVBF s2b0j_noVBF"
export DELTAETA="2" 
#export sel="VBF sboostedLL_noVBF s1b1jresolvedMcut_noVBF s2b0jresolvedMcut_noVBF"
export sel="sboostedLL_noVBF s1b1jresolvedMcut_noVBF s2b0jresolvedMcut_noVBF" 

export OUTSTRING="${out}Scan_oldOrder_deltaEta${DELTAETA}_22May2018_onlyGGFsig"
export INSTRING="XXXScan_oldOrder_deltaEta${DELTAETA}_22May2018"

export STRINGLEPTONS="$1"

export SELECTION="mXXXeta${DELTAETA}"
#export NAMESAMPLE="" #empty: both signals
export NAMESAMPLE="ggHHXS"
#export NAMESAMPLE="VBFC2V1XS"

export LEPTONS="TauTau ETau MuTau"

export MASS="300 400 500 600 650 700 750 800 900 1000"
export CF="$CMSSW_BASE/src/KLUBAnalysis/combiner"


export VARIABLE="MT2"
export SELECTIONS=""
export FOLDER=""

for cat in $CATEGORIES
do
    export FOLDER="$FOLDER ${INSTRING/XXX/$cat}"
done

for m in $MASS
do
    export SELECTIONS="$SELECTIONS ${SELECTION/XXX/$m}"

done
echo $SELECTIONS
echo $NAMESAMPLE
echo $FOLDER
export QUANTILES="0.025 0.16 0.5 0.84 0.975 -1.0"
export SOURCE="/home/llr/cms/amendola/CMSSW_7_4_7/src/KLUBAnalysis" 


mkdir cards_Combined_$OUTSTRING


for m in $MASS
do
    
    export S="${SELECTION/XXX/$m}"
    mkdir cards_Combined_$OUTSTRING/${out}${S}${VARIABLE}
    for s in $sel
    do

	
	if [[ $s = *"s1b1j"* ]]
	   then
	       cp cards_Combined_${INSTRING/XXX/s1b1j_noVBF}/${NAMESAMPLE}${s}${S}${VARIABLE}/hh*.* cards_Combined_$OUTSTRING/${out}${S}${VARIABLE}
	fi
	if [[ $s = *"s2b0j"* ]]
	then
	    cp cards_Combined_${INSTRING/XXX/s2b0j_noVBF}/${NAMESAMPLE}${s}${S}${VARIABLE}/hh*.* cards_Combined_$OUTSTRING/${out}${S}${VARIABLE}
	fi

		if [[ $s = *"sboost"* ]]
	then
	    cp cards_Combined_${INSTRING/XXX/sboost_noVBF}/${NAMESAMPLE}${s}${S}${VARIABLE}/hh*.* cards_Combined_$OUTSTRING/${out}${S}${VARIABLE}
	fi

	if [[ $s = *"VBF"* ]]
	then
	    if [[ $s != *"noVBF"* ]]
	       then
	    cp cards_Combined_${INSTRING/XXX/VBF}/${NAMESAMPLE}${s}${S}${VARIABLE}/hh*.* cards_Combined_$OUTSTRING/${out}${S}${VARIABLE}
	    fi
	    fi
    done
    
    export toCombine=""
    if [[ $out != *"noVBF"* ]]
    then
	export toCombine="$toCombine hh_*_C0_*_13Te*.txt"
    fi
    if [[ $sel = *"s1b1j"* ]]
    then 
	export toCombine="$toCombine hh_*_C1_*_13Te*.txt"
    fi
    if [[ $sel = *"s2b0j"* ]]
    then 
	export toCombine="$toCombine hh_*_C2_*_13Te*.txt"
    fi
    if [[ $sel = *"sboost"* ]]
    then 
	export toCombine="$toCombine hh_*_C3_*_13Te*.txt"
    fi
    cd cards_Combined_$OUTSTRING/${out}${S}${VARIABLE}
    pwd
    combineCards.py -S $toCombine >> comb.txt
    
    text2workspace.py -m ${m} comb.txt -o comb.root ;
    ln -ns ../../prepareHybrid.py .
    ln -ns ../../prepareGOF.py .
    ln -ns ../../prepareAsymptotic.py .
    python prepareAsymptotic.py -m ${m} -n SM_HHbbtt
    cd ${CF}
done
    #
#text2workspace.py -m ${i} comb.txt -o comb.root ;
#ln -ns ../../prepareHybrid.py .
#ln -ns ../../prepareGOF.py .
#ln -ns ../../prepareAsymptotic.py .
#python prepareAsymptotic.py -m ${i} -n ${NAMESAMPLE}
#
#cd ${CF}

#
#    text2workspace.py -m ${i} comb.txt -o comb.root ;
#    ln -ns ../../prepareHybrid.py .
#    ln -ns ../../prepareGOF.py .
#    ln -ns ../../prepareAsymptotic.py .
#    ln -ns ../../prepareImpacts.py .
#    python prepareAsymptotic.py -m ${i} -n ${NAMESAMPLE}
#
# cd ${CF}
#
##MAKE COMBINATION FOR CHANNEL [3 x mass point]
#	for c in $LEPTONS 
#	do
#
#	        cd cards_${c}_$OUTSTRING/${NAMESAMPLE}${VARIABLE}
#		pwd
#		rm comb.*
#		combineCards.py -S hh_*_C1_L${NAMESAMPLE}_13Te*.txt hh_*_C2_L${NAMESAMPLE}_13Te*.txt hh_*_C3_L${NAMESAMPLE}_13Te*.txt >> comb.txt
#
#		text2workspace.py -m ${i} comb.txt -o comb.root ;
#		ln -ns ../../prepareHybrid.py .
#		ln -ns ../../prepareGOF.py .
#		ln -ns ../../prepareAsymptotic.py .
#		python prepareAsymptotic.py -m ${i} -n ${NAMESAMPLE}
#
#		cd ${CF}
#   done
#
#
#done
#


