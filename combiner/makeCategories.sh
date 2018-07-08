#!/bin/bash
# make cards with all vars/selections

#export OUTSTRING="2017_02_19_btag_$1"
export OUTSTRING="18Jun2018TestOld_$1"
export STRINGLEPTONS="$1"
#export SELECTIONS="s2b0jresolvedMcut${STRINGLEPTONS} s1b1jresolvedMcut${STRINGLEPTONS} sboostedLLMcut"
#export SELECTIONS="s2b0jresolvedMcut s1b1jresolvedMcut sboostedLLMcut"
#export SELECTIONS="sboostedLLMcut s1b1jresolvedMcut${STRINGLEPTONS} s2b0jresolvedMcut${STRINGLEPTONS}"
export SELECTIONS="sboostedLLMcut s1b1jresolvedMcut${STRINGLEPTONS} s2b0jresolvedMcut${STRINGLEPTONS}"
export NAMESAMPLE="ggHHXS"
#export NAMESAMPLE="VBFC2V1XS"
#"ggHH_bbtt"
export RESONANT=$2
#export LEPTONS="MuTau ETau TauTau"
export LEPTONS="TauTau"

export CF="$CMSSW_BASE/src/KLUBAnalysis/combiner"
if [ "${RESONANT}" != "-r" ]
    then
    export VARIABLE="MT2"
        export LAMBDAS=""
        #export INSELECTIONS="s2b0jresolvedMcutlmr90 s1b1jresolvedMcutlmr90 s2b0jresolvedMcuthmr90 s1b1jresolvedMcuthmr90 sboostedLLMcut s1b1jresolvedMcutlmr70 s2b0jresolvedMcutlmr70 s1b1jresolvedMcutLepTauKine s2b0jresolvedMcutLepTauKine"
	#        for il in {0..51}
	for il in {1..1}
        do 
        export LAMBDAS="$LAMBDAS ${il}"
    done
    else
        export VARIABLE="HHKin_mass_raw"
        export NAMESAMPLE="Radion"
        #export LAMBDAS="Radion250 Radion260 Radion270 Radion280 Radion300 Radion320 Radion340 Radion400 Radion450 Radion500 Radion550 Radion600 Radion650 Radion700 Radion750 Radion800 Radion900"
        #export LAMBDAS="Radion250"
        export LAMBDAS="250 270 280 300 350 400 450 500 550 600 650 750 900"
fi
#export LAMBDAS="21"
#echo "LAMBDAS ======================"
#echo $LAMBDAS
export QUANTILES="0.025 0.16 0.5 0.84 0.975 -1.0"
export SOURCE="/home/llr/cms/amendola/CMSSW_7_4_7/src/KLUBAnalysis" 

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
            echo "$BASE"
        fi
	echo "$BASE"
	#python chcardMaker.py -f analyzedOutPlotter_${c}_18Jun2018Test_old.root -o "_${OUTSTRING}" -c ${c} -i ${SOURCE}/analysis_${c}_VBF18Jun2018_combineTest_old_noMcut/mainCfg_VBF_${c}.cfg -y -s ${BASE} ${RESONANT} -u 1 -t -l ${NAMESAMPLE} 
	python chcardMaker.py -f analyzedOutPlotter_${c}_18Jun2018Test_1jetCat.root -o "_${OUTSTRING}" -c ${c} -i ${SOURCE}/analysis_${c}_VBF18Jun2018_combine_1jetCat/mainCfg_VBF_${c}.cfg -y -s ${BASE} ${RESONANT} -u 1 -t -l ${NAMESAMPLE}
	#done
#for base in $SELECTIONSTAU
#do
    #python cardMaker.py -i ${SOURCE}/analysis_TauTau_26Gen/mainCfg_TauTau.cfg   -f ${SOURCE}/analysis_TauTau_26Gen/analyzedOutPlotter.root -o $BASE -c TauTau --dir "_$OUTSTRING" -t 0 # -r #-S /home/llr/cms/cadamuro/FittedHHKinFit/outPlotter_fit_sigs_TauTau.root
    done
done
echo " "
echo "CREATED ALL CARDS"
for i in $LAMBDAS
do 
#MAKE LIMIT FOR individual CHANNEL/categories [9 x mass points]
    for ibase in $SELECTIONS
    do	
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
		#export BASE="$ibase"
            fi
	    #            cd ${CF}/cards_${c}_$OUTSTRING/${NAMESAMPLE}${i}${BASE}${VARIABLE}
	    cd ${CF}/cards_${c}_$OUTSTRING/${NAMESAMPLE}${BASE}${VARIABLE}
            pwd
 	        #combineCards.py -S hh_${chanNum}_*L${i}_13TeV.txt >> comb.txt 
            combineCards.py -S hh_*.txt >> comb.txt 
            #combineCards.py hh_${chanNum}_C1_L${i}_13TeV.txt hh_${chanNum}_C2_L${i}_13TeV.txt hh_${chanNum}_C3_L${i}_13TeV.txt >> comb.txt
            text2workspace.py -m ${i} comb.txt -o comb.root ;
            ln -ns ../../prepareHybrid.py .
            ln -ns ../../prepareGOF.py .
            ln -ns ../../prepareAsymptotic.py .
            python prepareAsymptotic.py -m ${i} -n ${NAMESAMPLE}
            cd ${CF}
        done
    done
done

#CATEGORY COMBINATION
for i in $LAMBDAS
do
    cd ${CF}
	mkdir -p cards_Combined_$OUTSTRING/${NAMESAMPLE}${VARIABLE}
    #MAKE COMBINATION FOR CATEGORY [3 x mass point]
    for ibase in $SELECTIONS
    do
        mkdir -p cards_Combined_$OUTSTRING/${NAMESAMPLE}${ibase}${VARIABLE}
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
	    mkdir -p cards_${c}_$OUTSTRING/${NAMESAMPLE}${VARIABLE}
	    cp cards_${c}_$OUTSTRING/${NAMESAMPLE}${BASE}${VARIABLE}/hh_*.* cards_Combined_$OUTSTRING/${NAMESAMPLE}${ibase}${VARIABLE}/.
            cp cards_${c}_$OUTSTRING/${NAMESAMPLE}${BASE}${VARIABLE}/hh_*.* cards_Combined_$OUTSTRING/${NAMESAMPLE}${VARIABLE}/.
            cp cards_${c}_$OUTSTRING/${NAMESAMPLE}${BASE}${VARIABLE}/hh_*.* cards_${c}_$OUTSTRING/${NAMESAMPLE}${VARIABLE}/.
        done
        cd cards_Combined_$OUTSTRING/${NAMESAMPLE}${ibase}${VARIABLE}
        pwd
        if [ -a "hh_3_C1_L${NAMESAMPLE}_13TeV.txt" ] #category 1
            then
            combineCards.py -S hh_*_C1_L${NAMESAMPLE}_13Te*.txt  >> comb.txt
        fi
        if [ -a "hh_3_C2_L${NAMESAMPLE}_13TeV.txt" ]
            then
            combineCards.py -S hh_*_C2_L${NAMESAMPLE}_13Te*.txt >> comb.txt
        fi
        if [ -a "hh_3_C3_L${NAMESAMPLE}_13TeV.txt" ]
	then
	    echo "copying to comb.txt in Combined folder"
         	combineCards.py -S hh_*_C3_L${NAMESAMPLE}_13Te*.txt >> comb.txt
        fi
#        if [ -a "hh_1_C999_L${i}_13TeV.txt" ]
#           then
#           combineCards.py -S hh_1_C999_L_13TeV.txt hh_2_C999_L_13TeV.txt hh_3_C999_L_13TeV.txt >> comb.txt
#        fi
         text2workspace.py -m ${i} comb.txt -o comb.root ;
         ln -ns ../../prepareHybrid.py .
         ln -ns ../../prepareGOF.py .
         ln -ns ../../prepareAsymptotic.py .
         python prepareAsymptotic.py -m ${i} -n ${NAMESAMPLE}

        cd ${CF}
    done

	#MAKE BIG COMBINATION [1 x mass point]
    cd cards_Combined_$OUTSTRING/${NAMESAMPLE}${VARIABLE}
    pwd
    rm comb.*
    combineCards.py -S hh_*_C1_L${NAMESAMPLE}_13Te*.txt hh_*_C2_L${NAMESAMPLE}_13Te*.txt hh_*_C3_L${NAMESAMPLE}_13Te*.txt >> comb.txt #ah ma allora le wildcard funzionano?
    #combineCards.py -S hh_*_C2_L${i}_13TeV.txt hh_*_C3_L${i}_13TeV.txt >> comb.txt
    text2workspace.py -m ${i} comb.txt -o comb.root ;
    ln -ns ../../prepareHybrid.py .
    ln -ns ../../prepareGOF.py .
    ln -ns ../../prepareAsymptotic.py .
    ln -ns ../../prepareImpacts.py .
    python prepareAsymptotic.py -m ${i} -n ${NAMESAMPLE}
#    if [ $i == "21" ]
#    	then
##    	ln -ns ../../prepareImpacts.py .
##        python prepareImpacts.py -n $i -e 0
##        python prepareImpacts.py -n $i -e 1
##        for g in {0..20}
##        do
##           python prepareGOF.py -n $g 
#    #       done
#    for q in $QUANTILES
#    do
#       python prepareHybrid.py -n $q
#   done
# fi
 cd ${CF}

    #MAKE COMBINATION FOR CHANNEL [3 x mass point]
	for c in $LEPTONS 
	do
#		for base in $SELECTIONS
#		do
#			cp cards_${c}_$OUTSTRING/${i}${base}${VARIABLE}/hh_*C*.* cards_${c}_$OUTSTRING/${i}${VARIABLE}/.
	    #		done
	        cd cards_${c}_$OUTSTRING/${NAMESAMPLE}${VARIABLE}
		pwd
		rm comb.*
		combineCards.py -S hh_*_C1_L${NAMESAMPLE}_13Te*.txt hh_*_C2_L${NAMESAMPLE}_13Te*.txt hh_*_C3_L${NAMESAMPLE}_13Te*.txt >> comb.txt
		#combineCards.py -S  hh_*_C2_L${i}_13TeV.txt hh_*_C3_L${i}_13TeV.txt >> comb.txt
		text2workspace.py -m ${i} comb.txt -o comb.root ;
		ln -ns ../../prepareHybrid.py .
		ln -ns ../../prepareGOF.py .
		ln -ns ../../prepareAsymptotic.py .
		python prepareAsymptotic.py -m ${i} -n ${NAMESAMPLE}
#         if [ $i == "21" ]
#            then
#            for g in {0..20}
#            do
#               python prepareGOF.py -n $g 
#           done
#       fi
		cd ${CF}
    done


done



