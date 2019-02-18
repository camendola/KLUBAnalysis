tag=7Feb2019_decaymodes_noSF
#tag=28Jan2019_decaymodes_bins_DYenriched



### same decay mode
#taking the QCD already computed, without making the fit
python makeCards.py --tag $tag --decay bothDM0 --sel baselineHTauTau_bothDM0_DY --qcd True
python makeCards.py --tag $tag --decay bothDM1 --sel baselineHTauTau_bothDM1_DY --qcd True
python makeCards.py --tag $tag --decay bothDM10 --sel baselineHTauTau_bothDM10_DY --qcd True
### output is dataset_QCD.txt

#computing also the QCD
python makeCards.py --tag $tag --decay bothDM0 --sel baselineHTauTau_bothDM0_DY
python makeCards.py --tag $tag --decay bothDM1 --sel baselineHTauTau_bothDM1_DY
python makeCards.py --tag $tag --decay bothDM10 --sel baselineHTauTau_bothDM10_DY
### output is combined.txt



### different decay modes
#taking the QCD already computed, without making the fit
python makeCards.py --tag $tag --decay cross_DM0_DM1 --sel baselineHTauTau_tau1_DM0_tau2_DM1_DY --qcd True
python makeCards.py --tag $tag --decay cross_DM1_DM0 --sel baselineHTauTau_tau1_DM1_tau2_DM0_DY --qcd True

python makeCards.py --tag $tag --decay cross_DM0_DM10 --sel baselineHTauTau_tau1_DM0_tau2_DM10_DY --qcd True
python makeCards.py --tag $tag --decay cross_DM10_DM0 --sel baselineHTauTau_tau1_DM10_tau2_DM0_DY --qcd True

python makeCards.py --tag $tag --decay cross_DM1_DM10 --sel baselineHTauTau_tau1_DM1_tau2_DM10_DY --qcd True
python makeCards.py --tag $tag --decay cross_DM10_DM1 --sel baselineHTauTau_tau1_DM10_tau2_DM1_DY --qcd True
### output is dataset_QCD.txt

#computing also the QCD
python makeCards.py --tag $tag --decay cross_DM0_DM1 --sel baselineHTauTau_tau1_DM0_tau2_DM1_DY 
python makeCards.py --tag $tag --decay cross_DM1_DM0 --sel baselineHTauTau_tau1_DM1_tau2_DM0_DY 

python makeCards.py --tag $tag --decay cross_DM0_DM10 --sel baselineHTauTau_tau1_DM0_tau2_DM10_DY 
python makeCards.py --tag $tag --decay cross_DM10_DM0 --sel baselineHTauTau_tau1_DM10_tau2_DM0_DY 

python makeCards.py --tag $tag --decay cross_DM1_DM10 --sel baselineHTauTau_tau1_DM1_tau2_DM10_DY 
python makeCards.py --tag $tag --decay cross_DM10_DM1 --sel baselineHTauTau_tau1_DM10_tau2_DM1_DY 
#### output is combined.txt

