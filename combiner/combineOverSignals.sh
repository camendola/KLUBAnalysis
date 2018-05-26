#!/bin/bash
# make cards with all vars/selections


export STRINGLEPTONS="lmr70"
export OUTSTRING="22MayTest_${STRINGLEPTONS}"

export VARIABLE="MT2"

export CF="$CMSSW_BASE/src/KLUBAnalysis/combiner"
    
mkdir -p cards_Combined_$OUTSTRING/${VARIABLE}
cd cards_Combined_$OUTSTRING/${VARIABLE}
pwd    



combineCards.py -S  ${CF}/cards_Combined_$OUTSTRING/ggHHXS${VARIABLE}/comb.txt ${CF}/cards_Combined_$OUTSTRING/VBFC2V1XS${VARIABLE}/comb.txt >> comb.txt 

text2workspace.py -m 1 comb.txt -o comb.root ;
ln -ns ../../prepareHybrid.py .
ln -ns ../../prepareGOF.py .
ln -ns ../../prepareAsymptotic.py .
ln -ns ../../prepareImpacts.py .
python prepareAsymptotic.py -m 1 -n comb



