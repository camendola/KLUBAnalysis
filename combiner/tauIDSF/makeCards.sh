#taking the QCD already computed, without making the fit
#python makeCards.py --tag 7Feb2019_decaymodes_noSF --decay both1Pr --sel baselineHTauTau_both1Pr_DY --qcd True
#python makeCards.py --tag 7Feb2019_decaymodes_noSF --decay both1PrPi0 --sel baselineHTauTau_both1PrPi0_DY --qcd True
#python makeCards.py --tag 7Feb2019_decaymodes_noSF --decay both3Pr --sel baselineHTauTau_both3Pr_DY --qcd True
### output is dataset_QCD.txt



#computing also the QCD
#python makeCards.py --tag 7Feb2019_decaymodes_noSF --decay both1Pr --sel baselineHTauTau_both1Pr_DY
#python makeCards.py --tag 7Feb2019_decaymodes_noSF --decay both1PrPi0 --sel baselineHTauTau_both1PrPi0_DY
python makeCards.py --tag 7Feb2019_decaymodes_noSF --decay both3Pr --sel baselineHTauTau_both3Pr_DY
### output is combined.txt

