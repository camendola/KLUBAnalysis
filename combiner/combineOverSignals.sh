#!/bin/bash
# make cards with all vars/selections


export STRINGLEPTONS="lmr70"
export OUTSTRING="22MayTest_${STRINGLEPTONS}"
export outSTRING="22MayTest_${STRINGLEPTONS}_14Jun"

export VARIABLE="MT2"

export CF="$CMSSW_BASE/src/KLUBAnalysis/combiner"
    
mkdir -p cards_Combined_$outSTRING/${VARIABLE}
cd cards_Combined_$outSTRING/${VARIABLE}
pwd    

cp ${CF}/cards_Combined_$OUTSTRING/ggHHXS${VARIABLE}/hh*.* .
cp ${CF}/cards_Combined_$OUTSTRING/VBFC2V1XS${VARIABLE}/hh*.* .


export CAT="1 2 3"
export PAIR="1 2 3"
export cards=""

for cat in $CAT
do
    for pair in $PAIR
    do
	export SR="ch${pair}_C${cat}=hh_${pair}_C${cat}_LVBFC2V1XS_13TeV.txt ch${pair}_C${cat}=hh_${pair}_C${cat}_LggHHXS_13TeV.txt"
	if cat!=2
	   then
	export regB="ch${pair}_C${cat}_regB=hh_${pair}_C${cat}_LVBFC2V1XS_13TeV_regB.txt ch${pair}_C${cat}_regB=hh_${pair}_C${cat}_LggHHXS_13TeV_regB.txt"
	export regC="ch${pair}_C${cat}_regC=hh_${pair}_C${cat}_LVBFC2V1XS_13TeV_regC.txt ch${pair}_C${cat}_regC=hh_${pair}_C${cat}_LggHHXS_13TeV_regC.txt"
	export regD="ch${pair}_C${cat}_regD=hh_${pair}_C${cat}_LVBFC2V1XS_13TeV_regD.txt ch${pair}_C${cat}_regD=hh_${pair}_C${cat}_LggHHXS_13TeV_regD.txt"
	fi
	
	export cards="${cards} ${SR} ${regB} ${regC} ${regD}"
	#export cards="${cards} hh_${pair}_C${cat}_*.txt"
    done
done

echo $cards
   
combineCards.py -S $cards >> comb.txt

text2workspace.py -m 1 comb.txt -o comb.root ;
ln -ns ../../prepareHybrid.py .
ln -ns ../../prepareGOF.py .
ln -ns ../../prepareAsymptotic.py .
ln -ns ../../prepareImpacts.py .
python prepareAsymptotic.py -m 1 -n comb



