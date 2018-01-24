#define selEvents_cxx
//#define myclass_cxx
#define newClass_cxx
//#include "myclass.h"
#include "newClass.h"
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TMath.h>
#include <sstream>
#include <fstream>
#include <map>
#include <iostream>
#include "TChain.h"


void appendFromFileList (TChain* chain, TString filename)
{

  std::ifstream infile(filename.Data());
  std::string line;
  while (std::getline(infile, line))
    {
      line = line.substr(0, line.find("#", 0)); // remove comments introduced by #
	while (line.find(" ") != std::string::npos) line = line.erase(line.find(" "), 1); // remove white spaces
	while (line.find("\n") != std::string::npos) line = line.erase(line.find("\n"), 1); // remove new line characters
	while (line.find("\r") != std::string::npos) line = line.erase(line.find("\r"), 1); // remove carriage return characters
	if (!line.empty()) {// skip empty lines
	  cout<<line.c_str()<<endl;
	  chain->Add(line.c_str());

	}
    }
    return;
}
  


void selEvents(){



  TString dir_in="./comb_test/";
  TString dir_out="./comb_test/";

  
  
  TString fileList;    
  TString outfilename;
  //   TString process = "GluGluToHHTo2B2Tau_node_SM";
  TString process = "GluGluToRadionToHHTo2B2Tau_M-750";    
  
  fileList=dir_in+"SKIM_"+process+".txt";
  
  cout<<fileList<<endl;
  //  TFile *file = TFile::Open(Form("%s",filename.Data()),"read");
  
  
  TChain * tree;
  tree = new TChain ("HTauTauTree");
  appendFromFileList(tree, fileList);

  //TTree *tree = (TTree*) file->Get("HTauTauTree");
  //tree->ls();  
  //myclass theTree(tree); 
  newClass theTree(tree); 
  outfilename = dir_out+Form("output_%s_sel",process.Data());
  TFile *fileNew = TFile::Open(Form("%s.root",outfilename.Data()),"recreate");
  TTree *treeNew = new TTree ("HTauTauTreeSelections","HTauTauTreeSelections");

  
  //  unsigned int nentries = tree->GetEntries(); 
  
  Int_t           EventNumber;
  Int_t           RunNumber;
  Int_t           lumi;
  Int_t           nbjetscand;

  
  
  Bool_t passTrgBBres;
  Bool_t passTrgBBnonres;
  Bool_t passTrgGG;
  
  TBranch        *b_EventNumber;   //!
  TBranch        *b_RunNumber;   //!
  TBranch        *b_lumi;   //!
  TBranch        *b_nbjetscand;   //!



  
  TBranch *b_passTrgBBres;
  TBranch *b_passTrgBBnonres;
  TBranch *b_passTrgGG;
  
  tree->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
  tree->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
  tree->SetBranchAddress("lumi", &lumi, &b_lumi);
  tree->SetBranchAddress("nbjetscand", &nbjetscand, &b_nbjetscand);
  
  
  tree->SetBranchAddress("passTrgBBres",&passTrgBBres,&b_passTrgBBres);
  tree->SetBranchAddress("passTrgBBnonres",&passTrgBBnonres,&b_passTrgBBnonres);
  tree->SetBranchAddress("passTrgGG",&passTrgGG,&b_passTrgBBres);
  
  
  treeNew->Branch("EventNumber", &EventNumber, "EventNumber/I");
  treeNew->Branch("RunNumber", &RunNumber, "RunNumber/I");
  treeNew->Branch("lumi", &lumi, "lumi/I");


  treeNew->Branch("passTrgBBres",&passTrgBBres,"passTrgBBres/O");
  treeNew->Branch("passTrgBBnonres",&passTrgBBnonres,"passTrgBBnonres/O");
  treeNew->Branch("passTrgGG",&passTrgGG,"passTrgGG/O");




  
  ////summer 2017
  Bool_t tautau_1b1jresolvedMcut_SR;
  Bool_t tautau_2b0jresolvedMcut_SR;
  Bool_t tautau_boostedLLMcut_SR;

  Bool_t mutau_1b1jresolvedMcut_SR;
  Bool_t mutau_2b0jresolvedMcut_SR;
  Bool_t mutau_boostedLLMcut_SR;

  Bool_t etau_1b1jresolvedMcut_SR;
  Bool_t etau_2b0jresolvedMcut_SR;
  Bool_t etau_boostedLLMcut_SR;

  //counters
  Int_t tot_tautau_1b1jresolvedMcut_SR=0;
  Int_t tot_tautau_2b0jresolvedMcut_SR=0;
  Int_t tot_tautau_boostedLLMcut_SR=0;

  Int_t tot_mutau_1b1jresolvedMcut_SR=0;
  Int_t tot_mutau_2b0jresolvedMcut_SR=0;
  Int_t tot_mutau_boostedLLMcut_SR=0;

  Int_t tot_etau_1b1jresolvedMcut_SR=0;
  Int_t tot_etau_2b0jresolvedMcut_SR=0;
  Int_t tot_etau_boostedLLMcut_SR=0;

  /////////additional bjets
  Int_t bjetscand3_tautau_1b1jresolvedMcut_SR=0;
  Int_t bjetscand3_tautau_2b0jresolvedMcut_SR=0;
  Int_t bjetscand3_tautau_boostedLLMcut_SR=0;

  Int_t bjetscand3_mutau_1b1jresolvedMcut_SR=0;
  Int_t bjetscand3_mutau_2b0jresolvedMcut_SR=0;
  Int_t bjetscand3_mutau_boostedLLMcut_SR=0;
  
  Int_t bjetscand3_etau_1b1jresolvedMcut_SR=0;
  Int_t bjetscand3_etau_2b0jresolvedMcut_SR=0;
  Int_t bjetscand3_etau_boostedLLMcut_SR=0;


  Int_t BBandbjetscand3_tautau_1b1jresolvedMcut_SR=0;
  Int_t BBandbjetscand3_tautau_2b0jresolvedMcut_SR=0;
  Int_t BBandbjetscand3_tautau_boostedLLMcut_SR=0;

  Int_t BBandbjetscand3_mutau_1b1jresolvedMcut_SR=0;
  Int_t BBandbjetscand3_mutau_2b0jresolvedMcut_SR=0;
  Int_t BBandbjetscand3_mutau_boostedLLMcut_SR=0;

  Int_t BBandbjetscand3_etau_1b1jresolvedMcut_SR=0;
  Int_t BBandbjetscand3_etau_2b0jresolvedMcut_SR=0;
  Int_t BBandbjetscand3_etau_boostedLLMcut_SR=0;



  Int_t GGandbjetscand3_tautau_1b1jresolvedMcut_SR=0;
  Int_t GGandbjetscand3_tautau_2b0jresolvedMcut_SR=0;
  Int_t GGandbjetscand3_tautau_boostedLLMcut_SR=0;

  Int_t GGandbjetscand3_mutau_1b1jresolvedMcut_SR=0;
  Int_t GGandbjetscand3_mutau_2b0jresolvedMcut_SR=0;
  Int_t GGandbjetscand3_mutau_boostedLLMcut_SR=0;

  Int_t GGandbjetscand3_etau_1b1jresolvedMcut_SR=0;
  Int_t GGandbjetscand3_etau_2b0jresolvedMcut_SR=0;
  Int_t GGandbjetscand3_etau_boostedLLMcut_SR=0;

  //////////taus with high CSV score
  Int_t leps2bjets_tautau_1b1jresolvedMcut_SR=0;
  Int_t leps2bjets_tautau_2b0jresolvedMcut_SR=0;
  Int_t leps2bjets_tautau_boostedLLMcut_SR=0;

  Int_t leps2bjets_mutau_1b1jresolvedMcut_SR=0;
  Int_t leps2bjets_mutau_2b0jresolvedMcut_SR=0;
  Int_t leps2bjets_mutau_boostedLLMcut_SR=0;
  
  Int_t leps2bjets_etau_1b1jresolvedMcut_SR=0;
  Int_t leps2bjets_etau_2b0jresolvedMcut_SR=0;
  Int_t leps2bjets_etau_boostedLLMcut_SR=0;


  Int_t BBandleps2bjets_tautau_1b1jresolvedMcut_SR=0;
  Int_t BBandleps2bjets_tautau_2b0jresolvedMcut_SR=0;
  Int_t BBandleps2bjets_tautau_boostedLLMcut_SR=0;

  Int_t BBandleps2bjets_mutau_1b1jresolvedMcut_SR=0;
  Int_t BBandleps2bjets_mutau_2b0jresolvedMcut_SR=0;
  Int_t BBandleps2bjets_mutau_boostedLLMcut_SR=0;

  Int_t BBandleps2bjets_etau_1b1jresolvedMcut_SR=0;
  Int_t BBandleps2bjets_etau_2b0jresolvedMcut_SR=0;
  Int_t BBandleps2bjets_etau_boostedLLMcut_SR=0;



  Int_t GGandleps2bjets_tautau_1b1jresolvedMcut_SR=0;
  Int_t GGandleps2bjets_tautau_2b0jresolvedMcut_SR=0;
  Int_t GGandleps2bjets_tautau_boostedLLMcut_SR=0;

  Int_t GGandleps2bjets_mutau_1b1jresolvedMcut_SR=0;
  Int_t GGandleps2bjets_mutau_2b0jresolvedMcut_SR=0;
  Int_t GGandleps2bjets_mutau_boostedLLMcut_SR=0;

  Int_t GGandleps2bjets_etau_1b1jresolvedMcut_SR=0;
  Int_t GGandleps2bjets_etau_2b0jresolvedMcut_SR=0;
  Int_t GGandleps2bjets_etau_boostedLLMcut_SR=0;

  
  

  Int_t passTrgBBnonres_tautau_1b1jresolvedMcut_SR=0;
  Int_t passTrgBBnonres_tautau_2b0jresolvedMcut_SR=0;
  Int_t passTrgBBnonres_tautau_boostedLLMcut_SR=0;
		 
  Int_t passTrgBBnonres_mutau_1b1jresolvedMcut_SR=0;
  Int_t passTrgBBnonres_mutau_2b0jresolvedMcut_SR=0;
  Int_t passTrgBBnonres_mutau_boostedLLMcut_SR=0;
		 
  Int_t passTrgBBnonres_etau_1b1jresolvedMcut_SR=0;
  Int_t passTrgBBnonres_etau_2b0jresolvedMcut_SR=0;
  Int_t passTrgBBnonres_etau_boostedLLMcut_SR=0;
  
  Int_t passTrgBBres_tautau_1b1jresolvedMcut_SR=0;
  Int_t passTrgBBres_tautau_2b0jresolvedMcut_SR=0;
  Int_t passTrgBBres_tautau_boostedLLMcut_SR=0;

  Int_t passTrgBBres_mutau_1b1jresolvedMcut_SR=0;
  Int_t passTrgBBres_mutau_2b0jresolvedMcut_SR=0;
  Int_t passTrgBBres_mutau_boostedLLMcut_SR=0;

  Int_t passTrgBBres_etau_1b1jresolvedMcut_SR=0;
  Int_t passTrgBBres_etau_2b0jresolvedMcut_SR=0;
  Int_t passTrgBBres_etau_boostedLLMcut_SR=0;


  Int_t passTrgGG_tautau_1b1jresolvedMcut_SR=0;
  Int_t passTrgGG_tautau_2b0jresolvedMcut_SR=0;
  Int_t passTrgGG_tautau_boostedLLMcut_SR=0;

  Int_t passTrgGG_mutau_1b1jresolvedMcut_SR=0;
  Int_t passTrgGG_mutau_2b0jresolvedMcut_SR=0;
  Int_t passTrgGG_mutau_boostedLLMcut_SR=0;

  Int_t passTrgGG_etau_1b1jresolvedMcut_SR=0;
  Int_t passTrgGG_etau_2b0jresolvedMcut_SR=0;
  Int_t passTrgGG_etau_boostedLLMcut_SR=0;


  
  treeNew->SetAutoSave(-99999999999);
  treeNew->SetAutoFlush(-99999999999);

  
  
  treeNew->Branch("tautau_1b1jresolvedMcut_SR",&tautau_1b1jresolvedMcut_SR,"tautau_1b1jresolvedMcut_SR/O");
  treeNew->Branch("tautau_2b0jresolvedMcut_SR",&tautau_2b0jresolvedMcut_SR,"tautau_2b0jresolvedMcut_SR/O");
  treeNew->Branch("tautau_boostedLLMcut_SR",&tautau_boostedLLMcut_SR,"tautau_boostedLLMcut_SR/O");

  treeNew->Branch("mutau_1b1jresolvedMcut_SR",&mutau_1b1jresolvedMcut_SR,"mutau_1b1jresolvedMcut_SR/O");
  treeNew->Branch("mutau_2b0jresolvedMcut_SR",&mutau_2b0jresolvedMcut_SR,"mutau_2b0jresolvedMcut_SR/O");
  treeNew->Branch("mutau_boostedLLMcut_SR",&mutau_boostedLLMcut_SR,"mutau_boostedLLMcut_SR/O");

  treeNew->Branch("etau_1b1jresolvedMcut_SR",&etau_1b1jresolvedMcut_SR,"etau_1b1jresolvedMcut_SR/O");
  treeNew->Branch("etau_2b0jresolvedMcut_SR",&etau_2b0jresolvedMcut_SR,"etau_2b0jresolvedMcut_SR/O");
  treeNew->Branch("etau_boostedLLMcut_SR",&etau_boostedLLMcut_SR,"etau_boostedLLMcut_SR/O");

  

  for (Long64_t i =0 ;true; ++i){

    int got = 0;
    got = theTree.GetEntry(i);
    if (got == 0) break;
    //  for(unsigned int i=0; i<nentries; i++) {
    // theTree.GetEntry(i);    
    int isOS = theTree.isOS;
    int pairType = theTree.pairType;
    int isBoosted = theTree.isBoosted;
    int nleps = theTree.nleps;
    float dau1_pt = theTree.dau1_pt;
    float dau2_pt = theTree.dau2_pt;
    float dau1_eta = theTree.dau1_eta;
    float dau2_eta = theTree.dau2_eta;
    float  bjet1_bID = theTree.bjet1_bID;
    float  bjet2_bID = theTree.bjet2_bID;
    float tauH_SVFIT_mass = theTree.tauH_SVFIT_mass;
    float bH_mass_raw = theTree.bH_mass_raw;
    float HH_mass_raw = theTree.HH_mass_raw;
    float fatjet_softdropMass = theTree.fatjet_softdropMass;
    float bTagweightL =  theTree.bTagweightL;
    float bTagweightM =  theTree.bTagweightM;
    float LepTauKine =  theTree.LepTauKine;
    int dau1_MVAiso = theTree.dau1_MVAiso;
    float dau1_iso = theTree.dau1_iso;
    int dau2_MVAiso = theTree.dau2_MVAiso;
    float bjet1_pt_raw = theTree.bjet1_pt_raw;
    float bjet2_pt_raw = theTree.bjet2_pt_raw;
    vector<float> *jets_btag=theTree.jets_btag;
    vector<float> *jets_eta=theTree.jets_eta;

    float lep1_btag = theTree.lep1_btag;
    float lep2_btag = theTree.lep2_btag;
	

    
    int nbjetscand3 = 0;

    int nleps2bjets = 0;

    for (unsigned int bjet = 0; bjet<jets_btag->size(); bjet++){
        if (jets_btag->at(bjet) > 0.8484 && fabs(jets_eta->at(bjet))<2.4) nbjetscand3 +=1;
      
    }

  
            
    
    if (i%10000 == 0){
          std::cout << ">>> Event # " << i  << std::endl; 
    }

    
    //basic selections from selectionCfg_TauTau.cfg

    bool tautau_baseline = pairType == 2 && dau1_pt > 45 && abs (dau1_eta) < 2.1 && dau2_pt > 45 && abs (dau2_eta) < 2.1 && nleps == 0;
    bool mutau_baseline= pairType == 0 && dau1_pt > 23 && abs (dau1_eta) < 2.1 && dau2_pt > 20 && abs (dau2_eta) < 2.3 && nleps == 0;
    bool etau_baseline = pairType == 1 && dau1_pt > 27 && abs(dau1_eta) < 2.1 && dau2_pt > 20 && abs(dau2_eta) < 2.3 && nleps == 0;

    // btag
    bool btagM = bjet1_bID > 0.8484 && bjet2_bID < 0.8484;
    bool btagMM = bjet1_bID > 0.8484 && bjet2_bID > 0.8484;
    bool btagLL = bjet1_bID > 0.5426 && bjet2_bID > 0.5426;

    // mass
    bool circMassCut = TMath::Sqrt((tauH_SVFIT_mass-116.)*(tauH_SVFIT_mass-116.) + (bH_mass_raw-111.)*(bH_mass_raw-111.)) < 40.0;
    bool ellypsMassCut = ((tauH_SVFIT_mass-116.)*(tauH_SVFIT_mass-116.))/(35.*35.) + ((bH_mass_raw-111.)*(bH_mass_raw-111.))/(45.*45.) < 1.0;
    bool boostMassCut = tauH_SVFIT_mass > 79.5 && tauH_SVFIT_mass < 152.5 && fatjet_softdropMass > 90 && fatjet_softdropMass < 160;
															  
    //bdt
    bool nonresBDTCut = LepTauKine > -0.134;

    //region
    bool tautau_SR = isOS != 0 && dau1_MVAiso >= 3 && dau2_MVAiso >= 3;
    bool mutau_SR = isOS != 0 && dau1_iso < 0.15 && dau2_MVAiso >= 3;
    bool etau_SR = isOS != 0 && dau1_iso < 0.1 && dau2_MVAiso >= 3;


    //b mistag
    bool lep1b = lep1_btag>0.8484;
    bool lep2b = lep2_btag>0.8484;


    //FIXME  a una certa fai un bell'array
    //-------- TauTau selections--------// 
    
    //comb selections from selectionCfg_TauTau.cfg
    
    tautau_1b1jresolvedMcut_SR = tautau_baseline && btagM && tautau_SR && isBoosted!=1 && ellypsMassCut;
    tautau_2b0jresolvedMcut_SR = tautau_baseline && btagMM && tautau_SR && isBoosted!=1 && ellypsMassCut;
    tautau_boostedLLMcut_SR = tautau_baseline && btagLL && tautau_SR && isBoosted==1 && boostMassCut;

    if(pairType == 2 && lep1b && lep2b) nleps2bjets+=1; 
    
    if(tautau_1b1jresolvedMcut_SR ) tot_tautau_1b1jresolvedMcut_SR+=1;
    if(tautau_2b0jresolvedMcut_SR)  tot_tautau_2b0jresolvedMcut_SR+=1;
    if(tautau_boostedLLMcut_SR)     tot_tautau_boostedLLMcut_SR+=1;

    if(tautau_1b1jresolvedMcut_SR &&passTrgBBnonres)   passTrgBBnonres_tautau_1b1jresolvedMcut_SR+=1;
    if(tautau_2b0jresolvedMcut_SR &&passTrgBBnonres)   passTrgBBnonres_tautau_2b0jresolvedMcut_SR+=1;
    if(tautau_boostedLLMcut_SR &&passTrgBBnonres)      passTrgBBnonres_tautau_boostedLLMcut_SR+=1;

    if(tautau_1b1jresolvedMcut_SR &&passTrgBBres)   passTrgBBres_tautau_1b1jresolvedMcut_SR+=1;
    if(tautau_2b0jresolvedMcut_SR &&passTrgBBres)   passTrgBBres_tautau_2b0jresolvedMcut_SR+=1;
    if(tautau_boostedLLMcut_SR &&passTrgBBres)      passTrgBBres_tautau_boostedLLMcut_SR+=1;

    if(tautau_1b1jresolvedMcut_SR &&passTrgGG)   passTrgGG_tautau_1b1jresolvedMcut_SR+=1;
    if(tautau_2b0jresolvedMcut_SR &&passTrgGG)   passTrgGG_tautau_2b0jresolvedMcut_SR+=1;
    if(tautau_boostedLLMcut_SR &&passTrgGG)      passTrgGG_tautau_boostedLLMcut_SR+=1;
    
    if(tautau_1b1jresolvedMcut_SR && nbjetscand3>2 )  bjetscand3_tautau_1b1jresolvedMcut_SR+=1;
    if(tautau_2b0jresolvedMcut_SR && nbjetscand3>2 )  bjetscand3_tautau_2b0jresolvedMcut_SR+=1;
    if(tautau_boostedLLMcut_SR && nbjetscand3>2 )     bjetscand3_tautau_boostedLLMcut_SR+=1;

    if(tautau_1b1jresolvedMcut_SR && nbjetscand3>2 &&passTrgBBnonres)  BBandbjetscand3_tautau_1b1jresolvedMcut_SR+=1;
    if(tautau_2b0jresolvedMcut_SR && nbjetscand3>2 &&passTrgBBnonres)  BBandbjetscand3_tautau_2b0jresolvedMcut_SR+=1;
    if(tautau_boostedLLMcut_SR && nbjetscand3>2    &&passTrgBBnonres)  BBandbjetscand3_tautau_boostedLLMcut_SR+=1;
    
    if(tautau_1b1jresolvedMcut_SR && nbjetscand3>2 &&passTrgGG)  GGandbjetscand3_tautau_1b1jresolvedMcut_SR+=1;
    if(tautau_2b0jresolvedMcut_SR && nbjetscand3>2 &&passTrgGG)  GGandbjetscand3_tautau_2b0jresolvedMcut_SR+=1;
    if(tautau_boostedLLMcut_SR && nbjetscand3>2    &&passTrgGG)  GGandbjetscand3_tautau_boostedLLMcut_SR+=1;
    
    if(tautau_1b1jresolvedMcut_SR && nleps2bjets )  leps2bjets_tautau_1b1jresolvedMcut_SR+=1;
    if(tautau_2b0jresolvedMcut_SR && nleps2bjets )  leps2bjets_tautau_2b0jresolvedMcut_SR+=1;
    if(tautau_boostedLLMcut_SR && nleps2bjets )     leps2bjets_tautau_boostedLLMcut_SR+=1;
    
    if(tautau_1b1jresolvedMcut_SR && nleps2bjets &&passTrgBBnonres)  BBandleps2bjets_tautau_1b1jresolvedMcut_SR+=1;
    if(tautau_2b0jresolvedMcut_SR && nleps2bjets &&passTrgBBnonres)  BBandleps2bjets_tautau_2b0jresolvedMcut_SR+=1;
    if(tautau_boostedLLMcut_SR && nleps2bjets    &&passTrgBBnonres)  BBandleps2bjets_tautau_boostedLLMcut_SR+=1;
    
    if(tautau_1b1jresolvedMcut_SR && nleps2bjets &&passTrgGG)  GGandleps2bjets_tautau_1b1jresolvedMcut_SR+=1;
    if(tautau_2b0jresolvedMcut_SR && nleps2bjets &&passTrgGG)  GGandleps2bjets_tautau_2b0jresolvedMcut_SR+=1;
    if(tautau_boostedLLMcut_SR && nleps2bjets    &&passTrgGG)  GGandleps2bjets_tautau_boostedLLMcut_SR+=1;
    
    //-----------Tautau selections------------//
    //comb selections from selectionCfg_MuTau.cfg
    
    mutau_1b1jresolvedMcut_SR = mutau_baseline && btagM && mutau_SR && isBoosted!=1 && ellypsMassCut;
    mutau_2b0jresolvedMcut_SR = mutau_baseline && btagMM && mutau_SR && isBoosted!=1 && ellypsMassCut;
    mutau_boostedLLMcut_SR = mutau_baseline && btagLL && mutau_SR && isBoosted==1 && boostMassCut;

    if(pairType == 0 && lep1b && lep2b) nleps2bjets+=1; 
    
    if(mutau_1b1jresolvedMcut_SR ) tot_mutau_1b1jresolvedMcut_SR+=1;
    if(mutau_2b0jresolvedMcut_SR)  tot_mutau_2b0jresolvedMcut_SR+=1;
    if(mutau_boostedLLMcut_SR)     tot_mutau_boostedLLMcut_SR+=1;

    if(mutau_1b1jresolvedMcut_SR &&passTrgBBnonres)   passTrgBBnonres_mutau_1b1jresolvedMcut_SR+=1;
    if(mutau_2b0jresolvedMcut_SR &&passTrgBBnonres)   passTrgBBnonres_mutau_2b0jresolvedMcut_SR+=1;
    if(mutau_boostedLLMcut_SR &&passTrgBBnonres)      passTrgBBnonres_mutau_boostedLLMcut_SR+=1;

    if(mutau_1b1jresolvedMcut_SR &&passTrgBBres)   passTrgBBres_mutau_1b1jresolvedMcut_SR+=1;
    if(mutau_2b0jresolvedMcut_SR &&passTrgBBres)   passTrgBBres_mutau_2b0jresolvedMcut_SR+=1;
    if(mutau_boostedLLMcut_SR &&passTrgBBres)      passTrgBBres_mutau_boostedLLMcut_SR+=1;

    if(mutau_1b1jresolvedMcut_SR &&passTrgGG)   passTrgGG_mutau_1b1jresolvedMcut_SR+=1;
    if(mutau_2b0jresolvedMcut_SR &&passTrgGG)   passTrgGG_mutau_2b0jresolvedMcut_SR+=1;
    if(mutau_boostedLLMcut_SR &&passTrgGG)      passTrgGG_mutau_boostedLLMcut_SR+=1;

    if(mutau_1b1jresolvedMcut_SR && nbjetscand3>2)  bjetscand3_mutau_1b1jresolvedMcut_SR+=1;
    if(mutau_2b0jresolvedMcut_SR && nbjetscand3>2 )  bjetscand3_mutau_2b0jresolvedMcut_SR+=1;
    if(mutau_boostedLLMcut_SR && nbjetscand3>2 )     bjetscand3_mutau_boostedLLMcut_SR+=1;

    if(mutau_1b1jresolvedMcut_SR && nbjetscand3>2 &&passTrgBBnonres)  BBandbjetscand3_mutau_1b1jresolvedMcut_SR+=1;
    if(mutau_2b0jresolvedMcut_SR && nbjetscand3>2 &&passTrgBBnonres)  BBandbjetscand3_mutau_2b0jresolvedMcut_SR+=1;
    if(mutau_boostedLLMcut_SR && nbjetscand3>2    &&passTrgBBnonres)  BBandbjetscand3_mutau_boostedLLMcut_SR+=1;

    if(mutau_1b1jresolvedMcut_SR && nbjetscand3>2 &&passTrgGG)  GGandbjetscand3_mutau_1b1jresolvedMcut_SR+=1;
    if(mutau_2b0jresolvedMcut_SR && nbjetscand3>2 &&passTrgGG)  GGandbjetscand3_mutau_2b0jresolvedMcut_SR+=1;
    if(mutau_boostedLLMcut_SR && nbjetscand3>2    &&passTrgGG)  GGandbjetscand3_mutau_boostedLLMcut_SR+=1;


        if(mutau_1b1jresolvedMcut_SR && nleps2bjets)  leps2bjets_mutau_1b1jresolvedMcut_SR+=1;
    if(mutau_2b0jresolvedMcut_SR && nleps2bjets )  leps2bjets_mutau_2b0jresolvedMcut_SR+=1;
    if(mutau_boostedLLMcut_SR && nleps2bjets )     leps2bjets_mutau_boostedLLMcut_SR+=1;

    if(mutau_1b1jresolvedMcut_SR && nleps2bjets &&passTrgBBnonres)  BBandleps2bjets_mutau_1b1jresolvedMcut_SR+=1;
    if(mutau_2b0jresolvedMcut_SR && nleps2bjets &&passTrgBBnonres)  BBandleps2bjets_mutau_2b0jresolvedMcut_SR+=1;
    if(mutau_boostedLLMcut_SR && nleps2bjets    &&passTrgBBnonres)  BBandleps2bjets_mutau_boostedLLMcut_SR+=1;

    if(mutau_1b1jresolvedMcut_SR && nleps2bjets &&passTrgGG)  GGandleps2bjets_mutau_1b1jresolvedMcut_SR+=1;
    if(mutau_2b0jresolvedMcut_SR && nleps2bjets &&passTrgGG)  GGandleps2bjets_mutau_2b0jresolvedMcut_SR+=1;
    if(mutau_boostedLLMcut_SR && nleps2bjets    &&passTrgGG)  GGandleps2bjets_mutau_boostedLLMcut_SR+=1;

    //-----------ETau selections---------------//

    //comb selections from selectionCfg_Etau.cfg
    etau_1b1jresolvedMcut_SR = etau_baseline && btagM && etau_SR && isBoosted!=1 && ellypsMassCut;
    etau_2b0jresolvedMcut_SR = etau_baseline && btagMM && etau_SR && isBoosted!=1 && ellypsMassCut;
    etau_boostedLLMcut_SR = etau_baseline && btagLL && etau_SR && isBoosted==1 && boostMassCut;

    if(pairType == 1 && lep1b && lep2b) nleps2bjets+=1; 
    
    if(etau_1b1jresolvedMcut_SR ) tot_etau_1b1jresolvedMcut_SR+=1;
    if(etau_2b0jresolvedMcut_SR)  tot_etau_2b0jresolvedMcut_SR+=1;
    if(etau_boostedLLMcut_SR)     tot_etau_boostedLLMcut_SR+=1;



    
    if(etau_1b1jresolvedMcut_SR &&passTrgBBnonres)   passTrgBBnonres_etau_1b1jresolvedMcut_SR+=1;
    if(etau_2b0jresolvedMcut_SR &&passTrgBBnonres)   passTrgBBnonres_etau_2b0jresolvedMcut_SR+=1;
    if(etau_boostedLLMcut_SR &&passTrgBBnonres)      passTrgBBnonres_etau_boostedLLMcut_SR+=1;

    if(etau_1b1jresolvedMcut_SR &&passTrgBBres)   passTrgBBres_etau_1b1jresolvedMcut_SR+=1;
    if(etau_2b0jresolvedMcut_SR &&passTrgBBres)   passTrgBBres_etau_2b0jresolvedMcut_SR+=1;
    if(etau_boostedLLMcut_SR &&passTrgBBres)      passTrgBBres_etau_boostedLLMcut_SR+=1;

    if(etau_1b1jresolvedMcut_SR && passTrgGG)   passTrgGG_etau_1b1jresolvedMcut_SR+=1;
    if(etau_2b0jresolvedMcut_SR && passTrgGG)   passTrgGG_etau_2b0jresolvedMcut_SR+=1;
    if(etau_boostedLLMcut_SR && passTrgGG)      passTrgGG_etau_boostedLLMcut_SR+=1;


    if(etau_1b1jresolvedMcut_SR && nbjetscand3>2 )  bjetscand3_etau_1b1jresolvedMcut_SR+=1;
    if(etau_2b0jresolvedMcut_SR && nbjetscand3>2 )  bjetscand3_etau_2b0jresolvedMcut_SR+=1;
    if(etau_boostedLLMcut_SR && nbjetscand3>2 )     bjetscand3_etau_boostedLLMcut_SR+=1;

    if(etau_1b1jresolvedMcut_SR && nbjetscand3>2 &&passTrgBBnonres)  BBandbjetscand3_etau_1b1jresolvedMcut_SR+=1;
    if(etau_2b0jresolvedMcut_SR && nbjetscand3>2 &&passTrgBBnonres)  BBandbjetscand3_etau_2b0jresolvedMcut_SR+=1;
    if(etau_boostedLLMcut_SR && nbjetscand3>2    &&passTrgBBnonres)  BBandbjetscand3_etau_boostedLLMcut_SR+=1;
    
    if(etau_1b1jresolvedMcut_SR && nbjetscand3>2 &&passTrgGG)  GGandbjetscand3_etau_1b1jresolvedMcut_SR+=1;
    if(etau_2b0jresolvedMcut_SR && nbjetscand3>2 &&passTrgGG)  GGandbjetscand3_etau_2b0jresolvedMcut_SR+=1;
    if(etau_boostedLLMcut_SR && nbjetscand3>2    &&passTrgGG)  GGandbjetscand3_etau_boostedLLMcut_SR+=1;

    if(etau_1b1jresolvedMcut_SR && nleps2bjets )  leps2bjets_etau_1b1jresolvedMcut_SR+=1;
    if(etau_2b0jresolvedMcut_SR && nleps2bjets )  leps2bjets_etau_2b0jresolvedMcut_SR+=1;
    if(etau_boostedLLMcut_SR && nleps2bjets )     leps2bjets_etau_boostedLLMcut_SR+=1;

    if(etau_1b1jresolvedMcut_SR && nleps2bjets &&passTrgBBnonres)  BBandleps2bjets_etau_1b1jresolvedMcut_SR+=1;
    if(etau_2b0jresolvedMcut_SR && nleps2bjets &&passTrgBBnonres)  BBandleps2bjets_etau_2b0jresolvedMcut_SR+=1;
    if(etau_boostedLLMcut_SR && nleps2bjets    &&passTrgBBnonres)  BBandleps2bjets_etau_boostedLLMcut_SR+=1;
    
    if(etau_1b1jresolvedMcut_SR && nleps2bjets &&passTrgGG)  GGandleps2bjets_etau_1b1jresolvedMcut_SR+=1;
    if(etau_2b0jresolvedMcut_SR && nleps2bjets &&passTrgGG)  GGandleps2bjets_etau_2b0jresolvedMcut_SR+=1;
    if(etau_boostedLLMcut_SR && nleps2bjets    &&passTrgGG)  GGandleps2bjets_etau_boostedLLMcut_SR+=1;
    treeNew->Fill();  
    
  }
  fileNew->cd();
  treeNew->Write();
  fileNew->Close();



  cout<<" tot_tautau_1b1jresolvedMcut_SR "		<<   tot_tautau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<" tot_tautau_2b0jresolvedMcut_SR "		<<   tot_tautau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<" tot_tautau_boostedLLMcut_SR "			<<   tot_tautau_boostedLLMcut_SR		<<endl;

  cout<<endl;
  cout<<" tot_mutau_1b1jresolvedMcut_SR "			<<   tot_mutau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<" tot_mutau_2b0jresolvedMcut_SR "			<<   tot_mutau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<" tot_mutau_boostedLLMcut_SR "			<<   tot_mutau_boostedLLMcut_SR			<<endl;  
  cout<<endl;
  cout<<" tot_etau_1b1jresolvedMcut_SR "			<<   tot_etau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<" tot_etau_2b0jresolvedMcut_SR "			<<   tot_etau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<" tot_etau_boostedLLMcut_SR "			<<   tot_etau_boostedLLMcut_SR			<<endl;

  cout<<endl;
  
  cout<<" passTrgBBnonres_tautau_1b1jresolvedMcut_SR "	<<   passTrgBBnonres_tautau_1b1jresolvedMcut_SR	  <<endl;
  cout<<" passTrgBBnonres_tautau_2b0jresolvedMcut_SR "	<<   passTrgBBnonres_tautau_2b0jresolvedMcut_SR	  <<endl;
  cout<<" passTrgBBnonres_tautau_boostedLLMcut_SR "	<<   passTrgBBnonres_tautau_boostedLLMcut_SR	  <<endl;
  cout<<endl;
  cout<<" passTrgBBnonres_mutau_1b1jresolvedMcut_SR "	<<   passTrgBBnonres_mutau_1b1jresolvedMcut_SR	  <<endl;
  cout<<" passTrgBBnonres_mutau_2b0jresolvedMcut_SR "	<<   passTrgBBnonres_mutau_2b0jresolvedMcut_SR	  <<endl;
  cout<<" passTrgBBnonres_mutau_boostedLLMcut_SR "	<<   passTrgBBnonres_mutau_boostedLLMcut_SR       <<endl;		  
  cout<<endl;  
  cout<<" passTrgBBnonres_etau_1b1jresolvedMcut_SR "	<<   passTrgBBnonres_etau_1b1jresolvedMcut_SR	  <<endl;
  cout<<" passTrgBBnonres_etau_2b0jresolvedMcut_SR "	<<   passTrgBBnonres_etau_2b0jresolvedMcut_SR	  <<endl;
  cout<<" passTrgBBnonres_etau_boostedLLMcut_SR "		<<   passTrgBBnonres_etau_boostedLLMcut_SR	  <<endl;	  
  cout<<endl;
  cout<<" passTrgBBres_tautau_1b1jresolvedMcut_SR "	<<   passTrgBBres_tautau_1b1jresolvedMcut_SR	  <<endl;
  cout<<" passTrgBBres_tautau_2b0jresolvedMcut_SR "	<<   passTrgBBres_tautau_2b0jresolvedMcut_SR	  <<endl;
  cout<<" passTrgBBres_tautau_boostedLLMcut_SR "		<<   passTrgBBres_tautau_boostedLLMcut_SR	  <<endl;	  
  cout<<endl;
  cout<<" passTrgBBres_mutau_1b1jresolvedMcut_SR "	<<   passTrgBBres_mutau_1b1jresolvedMcut_SR       <<endl;		  
  cout<<" passTrgBBres_mutau_2b0jresolvedMcut_SR "	<<   passTrgBBres_mutau_2b0jresolvedMcut_SR       <<endl;		  
  cout<<" passTrgBBres_mutau_boostedLLMcut_SR "		<<   passTrgBBres_mutau_boostedLLMcut_SR	  <<endl;	  
  cout<<endl;
  cout<<" passTrgBBres_etau_1b1jresolvedMcut_SR "		<<   passTrgBBres_etau_1b1jresolvedMcut_SR	  <<endl;	  
  cout<<" passTrgBBres_etau_2b0jresolvedMcut_SR "		<<   passTrgBBres_etau_2b0jresolvedMcut_SR	  <<endl;	  
  cout<<" passTrgBBres_etau_boostedLLMcut_SR "		<<   passTrgBBres_etau_boostedLLMcut_SR		  <<endl;
  cout<<endl;
  cout<<" passTrgGG_tautau_1b1jresolvedMcut_SR "		<<   passTrgGG_tautau_1b1jresolvedMcut_SR	  <<endl;	  
  cout<<" passTrgGG_tautau_2b0jresolvedMcut_SR "		<<   passTrgGG_tautau_2b0jresolvedMcut_SR	  <<endl;	  
  cout<<" passTrgGG_tautau_boostedLLMcut_SR "		<<   passTrgGG_tautau_boostedLLMcut_SR		  <<endl;
  cout<<endl;
  cout<<" passTrgGG_mutau_1b1jresolvedMcut_SR "		<<   passTrgGG_mutau_1b1jresolvedMcut_SR	  <<endl;	  
  cout<<" passTrgGG_mutau_2b0jresolvedMcut_SR "		<<   passTrgGG_mutau_2b0jresolvedMcut_SR	  <<endl;	  
  cout<<" passTrgGG_mutau_boostedLLMcut_SR "		<<   passTrgGG_mutau_boostedLLMcut_SR		  <<endl;
  cout<<endl;
  cout<<" passTrgGG_etau_1b1jresolvedMcut_SR "		<<   passTrgGG_etau_1b1jresolvedMcut_SR		  <<endl;
  cout<<" passTrgGG_etau_2b0jresolvedMcut_SR "		<<   passTrgGG_etau_2b0jresolvedMcut_SR		  <<endl;
  cout<<" passTrgGG_etau_boostedLLMcut_SR "        	<<   passTrgGG_etau_boostedLLMcut_SR              <<endl;
  cout<<""<<endl;

  cout<<"\tnbjetscand3_tautau_1b1jresolvedMcut_SR "	<<   bjetscand3_tautau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnbjetscand3_tautau_2b0jresolvedMcut_SR "	<<   bjetscand3_tautau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnbjetscand3_tautau_boostedLLMcut_SR "		<<   bjetscand3_tautau_boostedLLMcut_SR			<<endl;  
  cout<<endl;
  cout<<"\tnbjetscand3_mutau_1b1jresolvedMcut_SR "	<<   bjetscand3_mutau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnbjetscand3_mutau_2b0jresolvedMcut_SR "	<<   bjetscand3_mutau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnbjetscand3_mutau_boostedLLMcut_SR "		<<   bjetscand3_mutau_boostedLLMcut_SR			<<endl;  
  cout<<endl;
  cout<<"\tnbjetscand3_etau_1b1jresolvedMcut_SR "	<<   bjetscand3_etau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnbjetscand3_etau_2b0jresolvedMcut_SR "	<<   bjetscand3_etau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnbjetscand3_etau_boostedLLMcut_SR "		<<   bjetscand3_etau_boostedLLMcut_SR			<<endl;
  cout<<endl;
    cout<<endl;

  cout<<"\tnBBandbjetscand3_tautau_1b1jresolvedMcut_SR "	<<   BBandbjetscand3_tautau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnBBandbjetscand3_tautau_2b0jresolvedMcut_SR "	<<   BBandbjetscand3_tautau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnBBandbjetscand3_tautau_boostedLLMcut_SR "		<<   BBandbjetscand3_tautau_boostedLLMcut_SR			<<endl;  
  cout<<endl;
  cout<<"\tnBBandbjetscand3_mutau_1b1jresolvedMcut_SR "	<<   BBandbjetscand3_mutau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnBBandbjetscand3_mutau_2b0jresolvedMcut_SR "	<<   BBandbjetscand3_mutau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnBBandbjetscand3_mutau_boostedLLMcut_SR "		<<   BBandbjetscand3_mutau_boostedLLMcut_SR			<<endl;  
  cout<<endl;
  cout<<"\tnBBandbjetscand3_etau_1b1jresolvedMcut_SR "	<<   BBandbjetscand3_etau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnBBandbjetscand3_etau_2b0jresolvedMcut_SR "	<<   BBandbjetscand3_etau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnBBandbjetscand3_etau_boostedLLMcut_SR "		<<   BBandbjetscand3_etau_boostedLLMcut_SR			<<endl;
  cout<<endl;
    cout<<endl;
    cout<<"\tnGGandbjetscand3_tautau_1b1jresolvedMcut_SR "	<<   GGandbjetscand3_tautau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnGGandbjetscand3_tautau_2b0jresolvedMcut_SR "	<<   GGandbjetscand3_tautau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnGGandbjetscand3_tautau_boostedLLMcut_SR "		<<   GGandbjetscand3_tautau_boostedLLMcut_SR			<<endl;  
  cout<<endl;
  cout<<"\tnGGandbjetscand3_mutau_1b1jresolvedMcut_SR "	<<   GGandbjetscand3_mutau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnGGandbjetscand3_mutau_2b0jresolvedMcut_SR "	<<   GGandbjetscand3_mutau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnGGandbjetscand3_mutau_boostedLLMcut_SR "		<<   GGandbjetscand3_mutau_boostedLLMcut_SR			<<endl;  
  cout<<endl;
  cout<<"\tnGGandbjetscand3_etau_1b1jresolvedMcut_SR "	<<   GGandbjetscand3_etau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnGGandbjetscand3_etau_2b0jresolvedMcut_SR "	<<   GGandbjetscand3_etau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnGGandbjetscand3_etau_boostedLLMcut_SR "		<<   GGandbjetscand3_etau_boostedLLMcut_SR			<<endl;



    cout<<"\tnleps2bjets_tautau_1b1jresolvedMcut_SR "	<<   leps2bjets_tautau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnleps2bjets_tautau_2b0jresolvedMcut_SR "	<<   leps2bjets_tautau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnleps2bjets_tautau_boostedLLMcut_SR "		<<   leps2bjets_tautau_boostedLLMcut_SR			<<endl;  
  cout<<endl;
  cout<<"\tnleps2bjets_mutau_1b1jresolvedMcut_SR "	<<   leps2bjets_mutau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnleps2bjets_mutau_2b0jresolvedMcut_SR "	<<   leps2bjets_mutau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnleps2bjets_mutau_boostedLLMcut_SR "		<<   leps2bjets_mutau_boostedLLMcut_SR			<<endl;  
  cout<<endl;
  cout<<"\tnleps2bjets_etau_1b1jresolvedMcut_SR "	<<   leps2bjets_etau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnleps2bjets_etau_2b0jresolvedMcut_SR "	<<   leps2bjets_etau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnleps2bjets_etau_boostedLLMcut_SR "		<<   leps2bjets_etau_boostedLLMcut_SR			<<endl;
  cout<<endl;
    cout<<endl;

  cout<<"\tnBBandleps2bjets_tautau_1b1jresolvedMcut_SR "	<<   BBandleps2bjets_tautau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnBBandleps2bjets_tautau_2b0jresolvedMcut_SR "	<<   BBandleps2bjets_tautau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnBBandleps2bjets_tautau_boostedLLMcut_SR "		<<   BBandleps2bjets_tautau_boostedLLMcut_SR			<<endl;  
  cout<<endl;
  cout<<"\tnBBandleps2bjets_mutau_1b1jresolvedMcut_SR "	<<   BBandleps2bjets_mutau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnBBandleps2bjets_mutau_2b0jresolvedMcut_SR "	<<   BBandleps2bjets_mutau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnBBandleps2bjets_mutau_boostedLLMcut_SR "		<<   BBandleps2bjets_mutau_boostedLLMcut_SR			<<endl;  
  cout<<endl;
  cout<<"\tnBBandleps2bjets_etau_1b1jresolvedMcut_SR "	<<   BBandleps2bjets_etau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnBBandleps2bjets_etau_2b0jresolvedMcut_SR "	<<   BBandleps2bjets_etau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnBBandleps2bjets_etau_boostedLLMcut_SR "		<<   BBandleps2bjets_etau_boostedLLMcut_SR			<<endl;
  cout<<endl;
    cout<<endl;
    cout<<"\tnGGandleps2bjets_tautau_1b1jresolvedMcut_SR "	<<   GGandleps2bjets_tautau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnGGandleps2bjets_tautau_2b0jresolvedMcut_SR "	<<   GGandleps2bjets_tautau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnGGandleps2bjets_tautau_boostedLLMcut_SR "		<<   GGandleps2bjets_tautau_boostedLLMcut_SR			<<endl;  
  cout<<endl;
  cout<<"\tnGGandleps2bjets_mutau_1b1jresolvedMcut_SR "	<<   GGandleps2bjets_mutau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnGGandleps2bjets_mutau_2b0jresolvedMcut_SR "	<<   GGandleps2bjets_mutau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnGGandleps2bjets_mutau_boostedLLMcut_SR "		<<   GGandleps2bjets_mutau_boostedLLMcut_SR			<<endl;  
  cout<<endl;
  cout<<"\tnGGandleps2bjets_etau_1b1jresolvedMcut_SR "	<<   GGandleps2bjets_etau_1b1jresolvedMcut_SR		<<endl;	  
  cout<<"\tnGGandleps2bjets_etau_2b0jresolvedMcut_SR "	<<   GGandleps2bjets_etau_2b0jresolvedMcut_SR		<<endl;	  
  cout<<"\tnGGandleps2bjets_etau_boostedLLMcut_SR "		<<   GGandleps2bjets_etau_boostedLLMcut_SR			<<endl;
  
}

