#!/bin/bash
# make cards with all vars/selections

export cat="$1"
export prefix="$2"
export DELTAETA="$3" 
export OUTSTRING="${cat}Scan_newOrder_deltaEta${DELTAETA}_22May2018"
export INSTRING="VBF22May2018_combine_newOrder_${cat}scan"
export intag="newOrder_22May2018_${cat}scan"


#export SELECTION="s2b0jresolvedMcut_noVBFmXXXeta${DELTAETA}"
#export SELECTION="s1b1jresolvedMcut_noVBFmXXXeta${DELTAETA}"
export SELECTION="${prefix}mXXXeta${DELTAETA}"
export NAMESAMPLE="ggHHXS VBFC2V1XS"
export RESONANT=$2
export LEPTONS="TauTau ETau MuTau"

export MASS="300 400 500 600 650 700 750 800 900 1000"

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

#create all the cards 3 categories x 3 channels
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
		echo "$BASE"
            fi
	    echo "$BASE"
	    python chcardMaker.py -f analyzedOutPlotter_${c}_${intag}.root -o "_${OUTSTRING}" -c ${c} -i ${SOURCE}/analysis_${c}_${INSTRING}/mainCfg_VBF_${c}.cfg -y -s ${BASE} ${RESONANT} -u 1 -t -l $sample 
	done
    done
done
echo $SELECTIONS
echo $MASS
echo " "
echo "CREATED ALL CARDS"

#MAKE LIMIT FOR individual CHANNEL/categories [9 x mass points]
#for sample in $NAMESAMPLE

#do
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

	    combineCards.py -S hh_*.txt >> comb.txt 

	    text2workspace.py -m ${m} comb.txt -o comb.root ;
	    ln -ns ../../prepareHybrid.py .
	    ln -ns ../../prepareGOF.py .
	    ln -ns ../../prepareAsymptotic.py .
	    python prepareAsymptotic.py -m ${m} -n $sample
	    cd ${CF}
	done
    done
done



echo "OK fino a qua"

echo "inizio combinazione"
echo $MASS
echo $ibase
echo $SELECTION
#CATEGORY COMBINATION
export ibase=""

for m in $MASS
do
    
    export ibase="${SELECTION/XXX/$m}"
    for sample in $NAMESAMPLE
    do
	echo $ibase
	cd ${CF}
	mkdir -p cards_Combined_$OUTSTRING/$sample${VARIABLE}
	#MAKE COMBINATION FOR CATEGORY [3 x mass point]
	#    for ibase in $SELECTIONS

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


echo "OK fino a qua 2"

#MAKE COMBINATION OF SIGNALS
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
	    for sample in $NAMESAMPLE
	    do
		cp cards_${c}_$OUTSTRING/${sample}${BASE}${VARIABLE}/hh_*.* cards_Combined_$OUTSTRING/${ibase}${VARIABLE}/.
		cp cards_${c}_$OUTSTRING/${sample}${BASE}${VARIABLE}/hh_*.* cards_Combined_$OUTSTRING/${VARIABLE}/.
		cp cards_${c}_$OUTSTRING/${sample}${BASE}${VARIABLE}/hh_*.* cards_${c}_$OUTSTRING/${VARIABLE}/.
            done
	done
        cd cards_Combined_$OUTSTRING/${ibase}${VARIABLE}
        pwd
	if [ -a "hh_3_C0_L${sample}_13TeV.txt" ] #category 0 (VBF)
        then
	    combineCards.py -S hh_*_C0_L*_13Te*.txt  >> comb.txt
        fi
        if [ -a "hh_3_C1_L${sample}_13TeV.txt" ] #category 1 
        then
	    combineCards.py -S hh_*_C1_L*_13Te*.txt  >> comb.txt
        fi
        if [ -a "hh_3_C2_L${sample}_13TeV.txt" ] #category 2
        then
	    combineCards.py -S hh_*_C2_L*_13Te*.txt >> comb.txt
        fi
        if [ -a "hh_3_C3_L${sample}_13TeV.txt" ] #category 3
	then
	    echo "copying to comb.txt in Combined folder"
	    combineCards.py -S hh_*_C3_L*_13Te*.txt >> comb.txt
        fi
	
        text2workspace.py -m ${m} comb.txt -o comb.root ;
        ln -ns ../../prepareHybrid.py .
        ln -ns ../../prepareGOF.py .
        ln -ns ../../prepareAsymptotic.py .
        python prepareAsymptotic.py -m ${m} -n SM_HHbbtt
	
        cd ${CF}
    done


    echo "OK fino a qua 3"
    #MAKE BIG COMBINATION [1 x mass point]
    #    cd cards_Combined_$OUTSTRING/${NAMESAMPLE}${VARIABLE}
    #    pwd
    #    rm comb.*
    #    combineCards.py -S hh_*_C1_L${NAMESAMPLE}_13Te*.txt hh_*_C2_L${NAMESAMPLE}_13Te*.txt hh_*_C3_L${NAMESAMPLE}_13Te*.txt >> comb.txt #ah ma allora le wildcard funzionano?

    #    text2workspace.py -m ${i} comb.txt -o comb.root ;
    #    ln -ns ../../prepareHybrid.py .
    #    ln -ns ../../prepareGOF.py .
    #    ln -ns ../../prepareAsymptotic.py .
    #    ln -ns ../../prepareImpacts.py .
    #    python prepareAsymptotic.py -m ${i} -n ${NAMESAMPLE}

    # cd ${CF}

    #MAKE COMBINATION FOR CHANNEL [3 x mass point]
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



