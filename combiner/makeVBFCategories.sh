#!/bin/bash
# make cards with all vars/selections

export cat="$1"
export prefix="$2"
export DELTAETA="$3" 
export BDTSTRING="$4"
export OUTSTRING="${BDTSTRING}${cat}Scan_newOrder_deltaEta${DELTAETA}_18Jun2018"
export INSTRING="VBF18Jun2018_combine_newOrder_${BDTSTRING}${cat}scan"
export intag="18Jun2018_newOrder_${BDTSTRING}${cat}scan"


#export SELECTION="s2b0jresolvedMcut_noVBFmXXXeta${DELTAETA}"
#export SELECTION="s1b1jresolvedMcut_noVBFmXXXeta${DELTAETA}"
export SELECTION="${prefix}mXXXeta${DELTAETA}"
export NAMESAMPLE="ggHHXS VBFC2V1XS"
export RESONANT=$2
export LEPTONS="TauTau ETau MuTau"
#export LEPTONS="TauTau"

export MASS="300 400 500 600 650 700 750 800 900 1000 1500 2000"
#export MASS="300"

export CF="$CMSSW_BASE/src/KLUBAnalysis/combiner"


export VARIABLE="MT2"
export SELECTIONS=""

for m in $MASS
do
    export SELECTIONS="$SELECTIONS ${SELECTION/XXX/$m}"

done
echo $SELECTIONS
echo $NAMESAMPLE

export QUANTILES="0.025 0.16 0.5 0.84 0.975 -1.0"
export SOURCE="/home/llr/cms/amendola/CMSSW_7_4_7/src/KLUBAnalysis" 

echo "@@@ Creating cards for each signal..."
for sample in $NAMESAMPLE
do
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
		export instring=${INSTRING/${BDTSTRING}/}
		export tag=${intag/${BDTSTRING}/}
            fi
	    echo "$BASE"
	    python chcardMaker.py -f analyzedOutPlotter_${c}_${tag}.root -o "_${OUTSTRING}" -c ${c} -i ${SOURCE}/analysis_${c}_${instring}/mainCfg_VBF_${c}.cfg -y -s ${BASE} ${RESONANT} -u 1 -t -l $sample
	done
    done
done
echo "@@@ Created cards for each signal"
echo ""
echo "@@@ Creating cards with both signals..."
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
	    export instring=${INSTRING/${BDTSTRING}/}
	    export tag=${intag/${BDTSTRING}/}
            fi
	echo "$BASE"
	python chcardMaker_Comb.py -f analyzedOutPlotter_${c}_${tag}.root -o "_${OUTSTRING}" -c ${c} -i ${SOURCE}/analysis_${c}_${instring}/mainCfg_VBF_${c}.cfg -y -s ${BASE} ${RESONANT} -u 1 -t
    done
done
echo "@@@ All cards created"
echo ""

echo "MAKE LIMIT FOR IDIVIDUAL CHANNEL/CATEGORIES"
echo ${sample}
export i=0
for m in $MASS
do
    export ibase="${SELECTION/XXX/$m}"
    for sample in $NAMESAMPLE
    do
	echo $ibase

	for c in $LEPTONS
	do
 	    #if [ -a "hh_3_L${i}_13TeV.txt" ]
 	    #	then
 	    #	combineCards.py -S "hh_3_L${i}_13TeV.txt" >> comb.txt 
 	    #fi
	    if [ "${c}" == "MuTau" ]
	    then
		export chanNum="2"
		echo "${c} ${chanNum}"
		export BASE="$ibase"
	    fi
	    if [ "${c}" == "ETau" ]
	    then
		export chanNum="1"
		echo "${c} ${chanNum}" 
		export BASE="$ibase"
	    fi
	    if [ "${c}" == "TauTau" ]
	    then
		export chanNum="3"
		echo "${c} ${chanNum}" 
		export BASE=${ibase/${STRINGLEPTONS}/}
	    fi
	    echo ${CF}/cards_${c}_$OUTSTRING/$sample${BASE}${VARIABLE}
	    cd ${CF}/cards_${c}_$OUTSTRING/$sample${BASE}${VARIABLE}
	    pwd

	    combineCards.py -S  hh_*.txt >> comb.txt 
	    text2workspace.py -m ${m} comb.txt -o comb.root ;
	    ln -ns ../../prepareHybrid.py .
	    ln -ns ../../prepareGOF.py .
	    ln -ns ../../prepareAsymptotic.py .
	    python prepareAsymptotic.py -m ${m} -n $sample
	    cd ${CF}
	done
    done
done


echo "CATEGORY COMBINATION"
echo $MASS
echo $ibase
echo $SELECTION

export ibase=""

for m in $MASS
do
    
    export ibase="${SELECTION/XXX/$m}"
    for sample in $NAMESAMPLE
    do
	echo $ibase
	cd ${CF}
	mkdir -p cards_Combined_$OUTSTRING/$sample${VARIABLE}

	mkdir -p cards_Combined_$OUTSTRING/$sample${ibase}${VARIABLE}
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
	    mkdir -p cards_${c}_$OUTSTRING/$sample${VARIABLE}
	    cp cards_${c}_$OUTSTRING/$sample${BASE}${VARIABLE}/hh_*.* cards_Combined_$OUTSTRING/$sample${ibase}${VARIABLE}/.
	    cp cards_${c}_$OUTSTRING/$sample${BASE}${VARIABLE}/hh_*.* cards_Combined_$OUTSTRING/$sample${VARIABLE}/.
	    cp cards_${c}_$OUTSTRING/$sample${BASE}${VARIABLE}/hh_*.* cards_${c}_$OUTSTRING/$sample${VARIABLE}/.
	done
	cd cards_Combined_$OUTSTRING/$sample${ibase}${VARIABLE}
	pwd
	if [ -a "hh_3_C0_L${sample}_13TeV.txt" ] #category 0 (VBF)
	then
	    echo "copy to COMB.TXT"
	    combineCards.py -S hh_*_C0_L${sample}_13Te*.txt  >> comb.txt
	fi
	if [ -a "hh_3_C1_L${sample}_13TeV.txt" ] #category 1 
	then
	    combineCards.py -S hh_*_C1_L${sample}_13Te*.txt  >> comb.txt
	fi
	if [ -a "hh_3_C2_L${sample}_13TeV.txt" ] #category 2
	then
	    combineCards.py -S hh_*_C2_L${sample}_13Te*.txt >> comb.txt
	fi
	if [ -a "hh_3_C3_L${sample}_13TeV.txt" ] #category 3
	then
	    echo "copying to comb.txt in Combined folder"
            combineCards.py -S hh_*_C3_L${sample}_13Te*.txt >> comb.txt
	fi
	
	text2workspace.py -m ${m} comb.txt -o comb.root ;
	ln -ns ../../prepareHybrid.py .
	ln -ns ../../prepareGOF.py .
	ln -ns ../../prepareAsymptotic.py .
	python prepareAsymptotic.py -m ${m} -n $sample
	
	cd ${CF}
    done
done

echo "MAKE COMBINATION OF SIGNALS"
for m in $MASS
do

	cd ${CF}
	mkdir -p cards_Combined_$OUTSTRING/${VARIABLE}
	#MAKE COMBINATION FOR CATEGORY [3 x mass point]
	#for ibase in $SELECTIONS
	#do 
	export ibase="${SELECTION/XXX/$m}"
	
	mkdir -p cards_Combined_$OUTSTRING/${ibase}${VARIABLE}
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
	    mkdir -p cards_${c}_$OUTSTRING/${VARIABLE}
	    samples=($NAMESAMPLE)
	    sample=${samples[0]}
	    #for sample in $NAMESAMPLE
	    #do
	    cp cards_${c}_$OUTSTRING/${BASE}${VARIABLE}/hh_*.* cards_Combined_$OUTSTRING/${ibase}${VARIABLE}/.
	    cp cards_${c}_$OUTSTRING/${BASE}${VARIABLE}/hh_*.* cards_Combined_$OUTSTRING/${VARIABLE}/.
	    cp cards_${c}_$OUTSTRING/${BASE}${VARIABLE}/hh_*.* cards_${c}_$OUTSTRING/${VARIABLE}/.
            #done
	done
        cd cards_Combined_$OUTSTRING/${ibase}${VARIABLE}
        pwd
	if [ -a "hh_3_C0_13TeV.txt" ] #category 0 (VBF)
        then
	    combineCards.py -S hh_*_C0_13Te*.txt  >> comb.txt
        fi
        if [ -a "hh_3_C1_13TeV.txt" ] #category 1 
        then
	    combineCards.py -S hh_*_C1_13Te*.txt  >> comb.txt
        fi
        if [ -a "hh_3_C2_13TeV.txt" ] #category 2
        then
	    combineCards.py -S hh_*_C2_13Te*.txt >> comb.txt
        fi
        if [ -a "hh_3_C3_13TeV.txt" ] #category 3
	then
	    echo "copying to comb.txt in Combined folder"
	    combineCards.py -S hh_*_C3_13Te*.txt >> comb.txt
        fi
	
        text2workspace.py -m ${m} comb.txt -o comb.root ;
        ln -ns ../../prepareHybrid.py .
        ln -ns ../../prepareGOF.py .
        ln -ns ../../prepareAsymptotic.py .
        python prepareAsymptotic.py -m ${m} -n SM_HHbbtt
	
        cd ${CF}
    done






