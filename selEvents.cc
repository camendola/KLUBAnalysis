#define selEvents_cxx
//#define myclass_cxx
#define newClass_cxx
//#include "myclass.h"
#include "newClass.h"
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>

#include <iostream>
#include <fstream>
#include <iomanip>



void selEvents(int num){
  //TString dir_in="/data_CMS/cms/cadamuro/test_submit_to_tier3/Skims2017_10Gen/SKIM_TT_fullyHad/";
  // TString dir_out="/data_CMS/cms/amendola/TestSelections/TT_background/fullyHad/";


  //  TString dir_in="/data_CMS/cms/cadamuro/test_submit_to_tier3/Skims2017_10Gen/SKIM_TT_semiLep/";
  //TString dir_out="/data_CMS/cms/amendola/TestSelections/TT_background/semiLep/";

  TString dir_in="/data_CMS/cms/cadamuro/test_submit_to_tier3/Skims2017_10Gen/SKIM_TT_fullyLep/";
  TString dir_out="/data_CMS/cms/amendola/TestSelections/TT_background/fullyLep/";

  TString filename;    
  TString outfilename;    

  filename=dir_in+Form("output_%i.root",num);
  cout<<filename<<endl;
  TFile *file = TFile::Open(Form("%s",filename.Data()),"read");
  
  TTree *tree = (TTree*) file->Get("HTauTauTree");
  tree->ls();  
  //myclass theTree(tree); 
  newClass theTree(tree); 
  outfilename = dir_out+Form("output_%d_sel",num);
  TFile *fileNew = TFile::Open(Form("%s.root",outfilename.Data()),"recreate");
  TTree *treeNew = new TTree ("HTauTauTreeSelections","HTauTauTreeSelections");


  unsigned int nentries = tree->GetEntries(); 

  Int_t           EventNumber;
  Int_t           RunNumber;
  Int_t           lumi;
  
  TBranch        *b_EventNumber;   //!
  TBranch        *b_RunNumber;   //!
  TBranch        *b_lumi;   //!  
  
  tree->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
  tree->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
  tree->SetBranchAddress("lumi", &lumi, &b_lumi);
  
  treeNew->Branch("EventNumber", &EventNumber, "EventNumber/I");
  treeNew->Branch("RunNumber", &RunNumber, "RunNumber/I");
  treeNew->Branch("lumi", &lumi, "lumi/I");






  //selections
  Int_t tautau_1b1jMcut_SR;
  Int_t tautau_2b0jMcut_SR;
  Int_t tautau_1b1jMcut_SStight;
  Int_t tautau_2b0jMcut_SStight;

  Int_t mutau_1b1jMcut_SR;
  Int_t mutau_2b0jMcut_SR;
  Int_t mutau_1b1jMcutBDT_SR;
  Int_t mutau_2b0jMcutBDT_SR;

  Int_t etau_1b1jMcut_SR;
  Int_t etau_2b0jMcut_SR;
  Int_t etau_1b1jMcutBDT_SR;
  Int_t etau_2b0jMcutBDT_SR;


  Int_t tautau_resolved_2b0j;
  Int_t tautau_resolved_1b1j;
  Int_t tautau_resolved_2b0j_Mcut;
  Int_t tautau_resolved_1b1j_Mcut;
  Int_t tautau_resolved_2b0j_McutCirc;
  Int_t tautau_resolved_1b1j_McutCirc;
  Int_t tautau_boosted;
  Int_t tautau_boosted_Mcut;
  Int_t tautau_defaultBtagLLNoIsoBBTTCut450tag;
  Int_t tautau_defaultBtagLLNoIsoBBTTCut451tag;
  Int_t tautau_defaultBtagLLNoIsoBBTTCut45;
  Int_t tautau_defaultBtagLLNoIso45;

  Int_t mutau_resolved_2b0j;
  Int_t mutau_resolved_1b1j;
  Int_t mutau_resolved_2b0j_Mcut;
  Int_t mutau_resolved_1b1j_Mcut;
  Int_t mutau_boosted;
  Int_t mutau_boosted_Mcut;
  Int_t mutau_defaultBtagMMNoIsoBBTTCut;
  Int_t mutau_defaultBtagLLNoIso;
  Int_t mutau_defaultBtagLLNoIsoBBTTCut;
  Int_t mutau_defaultBtagLLNoIsoBBTTCutKine80;
  Int_t mutau_defaultBtagLLNoIsoBBTTCutKine801tag;

  Int_t etau_resolved_2b0j;
  Int_t etau_resolved_1b1j;
  Int_t etau_resolved_2b0j_Mcut;
  Int_t etau_resolved_1b1j_Mcut;
  Int_t etau_boosted;
  Int_t etau_boosted_Mcut;
  Int_t etau_defaultBtagMMNoIsoBBTTCut;
  Int_t etau_defaultBtagLLNoIso;
  Int_t etau_defaultBtagLLNoIsoBBTTCut;
  Int_t etau_defaultBtagLLNoIsoBBTTCutKine80;
  Int_t etau_defaultBtagLLNoIsoBBTTCutKine801tag;
  
  treeNew->SetAutoSave(-99999999999);
  treeNew->SetAutoFlush(-99999999999);

  treeNew->Branch("tautau_1b1jMcut_SR",&tautau_1b1jMcut_SR,"tautau_1b1jMcut_SR/I");
  treeNew->Branch("tautau_2b0jMcut_SR",&tautau_2b0jMcut_SR,"tautau_2b0jMcut_SR/I");
  treeNew->Branch("tautau_1b1jMcut_SStight",&tautau_1b1jMcut_SStight,"tautau_1b1jMcut_SStight/I");
  treeNew->Branch("tautau_2b0jMcut_SStight",&tautau_2b0jMcut_SStight,"tautau_2b0jMcut_SStight/I");

  treeNew->Branch("mutau_1b1jMcut_SR",&mutau_1b1jMcut_SR,"mutau_1b1jMcut_SR/I");
  treeNew->Branch("mutau_2b0jMcut_SR",&mutau_2b0jMcut_SR,"mutau_2b0jMcut_SR/I");
  treeNew->Branch("mutau_1b1jMcutBDT_SR",&mutau_1b1jMcutBDT_SR,"mutau_1b1jMcutBDT_SR/I");
  treeNew->Branch("mutau_2b0jMcutBDT_SR",&mutau_2b0jMcutBDT_SR,"mutau_2b0jMcutBDT_SR/I");

  treeNew->Branch("etau_1b1jMcut_SR",&etau_1b1jMcut_SR,"etau_1b1jMcut_SR/I");
  treeNew->Branch("etau_2b0jMcut_SR",&etau_2b0jMcut_SR,"etau_2b0jMcut_SR/I");
  treeNew->Branch("etau_1b1jMcutBDT_SR",&etau_1b1jMcutBDT_SR,"etau_1b1jMcutBDT_SR/I");
  treeNew->Branch("etau_2b0jMcutBDT_SR",&etau_2b0jMcutBDT_SR,"etau_2b0jMcutBDT_SR/I");



  /*  treeNew->Branch("tautau_resolved_2b0j",&tautau_resolved_2b0j,"tautau_resolved_2b0j/I");
  treeNew->Branch("tautau_resolved_1b1j",&tautau_resolved_1b1j,"tautau_resolved_1b1j/I");
  treeNew->Branch("tautau_resolved_2b0j_Mcut",&tautau_resolved_2b0j_Mcut,"tautau_resolved_2b0j_Mcut/I");
  treeNew->Branch("tautau_resolved_1b1j_Mcut",&tautau_resolved_1b1j_Mcut,"tautau_resolved_1b1j_Mcut/I");
  treeNew->Branch("tautau_resolved_2b0j_McutCirc",&tautau_resolved_2b0j_McutCirc,"tautau_resolved_2b0j_McutCirc/I");
  treeNew->Branch("tautau_resolved_1b1j_McutCirc",&tautau_resolved_1b1j_McutCirc,"tautau_resolved_1b1j_McutCirc/I");
  treeNew->Branch("tautau_boosted",&tautau_boosted,"tautau_boosted/I");
  treeNew->Branch("tautau_boosted_Mcut",&tautau_boosted_Mcut,"tautau_boosted_Mcut/I");
  treeNew->Branch("tautau_defaultBtagLLNoIsoBBTTCut450tag",&tautau_defaultBtagLLNoIsoBBTTCut450tag,"tautau_defaultBtagLLNoIsoBBTTCut450tag/I");
  treeNew->Branch("tautau_defaultBtagLLNoIsoBBTTCut451tag",&tautau_defaultBtagLLNoIsoBBTTCut451tag,"tautau_defaultBtagLLNoIsoBBTTCut451tag/I");
  treeNew->Branch("tautau_defaultBtagLLNoIsoBBTTCut45",&tautau_defaultBtagLLNoIsoBBTTCut45,"tautau_defaultBtagLLNoIsoBBTTCut45/I");
  treeNew->Branch("tautau_defaultBtagLLNoIso45",&tautau_defaultBtagLLNoIso45,"tautau_defaultBtagLLNoIso45/I");

  treeNew->Branch("mutau_resolved_2b0j",&mutau_resolved_2b0j,"mutau_resolved_2b0j/I");
  treeNew->Branch("mutau_resolved_1b1j",&mutau_resolved_1b1j,"mutau_resolved_1b1j/I");
  treeNew->Branch("mutau_resolved_2b0j_Mcut",&mutau_resolved_2b0j_Mcut,"mutau_resolved_2b0j_Mcut/I");
  treeNew->Branch("mutau_resolved_1b1j_Mcut",&mutau_resolved_1b1j_Mcut,"mutau_resolved_1b1j_Mcut/I");
  treeNew->Branch("mutau_boosted",&mutau_boosted,"mutau_boosted/I");
  treeNew->Branch("mutau_boosted_Mcut",&mutau_boosted_Mcut,"mutau_boosted_Mcut/I");
  treeNew->Branch("mutau_defaultBtagMMNoIsoBBTTCut",&mutau_defaultBtagMMNoIsoBBTTCut,"mutau_defaultBtagMMNoIsoBBTTCut/I");
  treeNew->Branch("mutau_defaultBtagLLNoIso",&mutau_defaultBtagLLNoIso,"mutau_defaultBtagLLNoIso/I");
  treeNew->Branch("mutau_defaultBtagLLNoIsoBBTTCut",&mutau_defaultBtagLLNoIsoBBTTCut,"mutau_defaultBtagLLNoIsoBBTTCut/I");
  treeNew->Branch("mutau_defaultBtagLLNoIsoBBTTCutKine80",&mutau_defaultBtagLLNoIsoBBTTCutKine80,"mutau_defaultBtagLLNoIsoBBTTCutKine80/I");
  treeNew->Branch("mutau_defaultBtagLLNoIsoBBTTCutKine801tag",&mutau_defaultBtagLLNoIsoBBTTCutKine801tag,"mutau_defaultBtagLLNoIsoBBTTCutKine801tag/I");

  treeNew->Branch("etau_resolved_2b0j",&etau_resolved_2b0j,"etau_resolved_2b0j/I");
  treeNew->Branch("etau_resolved_1b1j",&etau_resolved_1b1j,"etau_resolved_1b1j/I");
  treeNew->Branch("etau_resolved_2b0j_Mcut",&etau_resolved_2b0j_Mcut,"etau_resolved_2b0j_Mcut/I");
  treeNew->Branch("etau_resolved_1b1j_Mcut",&etau_resolved_1b1j_Mcut,"etau_resolved_1b1j_Mcut/I");
  treeNew->Branch("etau_boosted",&etau_boosted,"etau_boosted/I");
  treeNew->Branch("etau_boosted_Mcut",&etau_boosted_Mcut,"etau_boosted_Mcut/I");
  treeNew->Branch("etau_defaultBtagMMNoIsoBBTTCut",&etau_defaultBtagMMNoIsoBBTTCut,"etau_defaultBtagMMNoIsoBBTTCut/I");
  treeNew->Branch("etau_defaultBtagLLNoIso",&etau_defaultBtagLLNoIso,"etau_defaultBtagLLNoIso/I");
  treeNew->Branch("etau_defaultBtagLLNoIsoBBTTCut",&etau_defaultBtagLLNoIsoBBTTCut,"etau_defaultBtagLLNoIsoBBTTCut/I");
  treeNew->Branch("etau_defaultBtagLLNoIsoBBTTCutKine80",&etau_defaultBtagLLNoIsoBBTTCutKine80,"etau_defaultBtagLLNoIsoBBTTCutKine80/I");
  treeNew->Branch("etau_defaultBtagLLNoIsoBBTTCutKine801tag",&etau_defaultBtagLLNoIsoBBTTCutKine801tag,"etau_defaultBtagLLNoIsoBBTTCutKine801tag/I");
  */
  for(unsigned int i=0; i<nentries; i++) {
    theTree.GetEntry(i);    
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
    
    tree->ls();

    tree->GetEntry(i);      
    
    
    if (i%10000 == 0){
          std::cout << ">>> Event # " << i << " / " << nentries << " entries" << std::endl; 
    }

    
    //basic selections from selectionCfg_TauTau.cfg

    bool tautau_baseline = pairType == 2 && dau1_pt > 45 && abs (dau1_eta) < 2.1 && dau2_pt > 45 && abs (dau2_eta) < 2.1 && nleps == 0;
    bool mutau_baseline= pairType == 0 && dau1_pt > 23 && abs (dau1_eta) < 2.1 && dau2_pt > 20 && abs (dau2_eta) < 2.3 && nleps == 0;
    bool etau_baseline = pairType == 1 && dau1_pt > 27 && abs(dau1_eta) < 2.1 && dau2_pt > 20 && abs(dau2_eta) < 2.3 && nleps == 0;
    bool btagM = bjet1_bID > 0.800 && bjet2_bID < 0.800;
    bool btagMM = bjet1_bID > 0.800 && bjet2_bID > 0.800;
    bool circMassCut = TMath::Sqrt((tauH_SVFIT_mass-116.)*(tauH_SVFIT_mass-116.) + (bH_mass_raw-111.)*(bH_mass_raw-111.)) < 40.0;
    bool nonresBDTCut = LepTauKine > -0.134;
      
    bool tautau_SR = isOS != 0 && dau1_MVAiso >= 3 && dau2_MVAiso >= 3;
    bool mutau_SR = isOS != 0 && dau1_iso < 0.15 && dau2_MVAiso >= 3;
    bool etau_SR = isOS != 0 && dau1_iso < 0.1 && dau2_MVAiso >= 3;
    bool tautau_SStight = isOS == 0 && dau1_MVAiso >= 3 && dau2_MVAiso >= 3;


    //FIXME  a una certa fai un bell'array
    //-------- TauTau selections--------// 
    
    //comb selections from selectionCfg_TauTau.cfg
    bool istautau_1b1jMcut_SR = tautau_baseline && btagM && tautau_SR;
    bool istautau_2b0jMcut_SR = tautau_baseline && btagMM && circMassCut && tautau_SR;
    bool istautau_1b1jMcut_SStight = tautau_baseline && btagM && tautau_SStight;
    bool istautau_2b0jMcut_SStight = tautau_baseline && btagMM && circMassCut && tautau_SStight;
    
    
    //selections from analysis_2016.cfg
    /*    bool istautau_resolved_2b0j = isOS == 1 && pairType == 2 && dau1_pt > 45 && abs(dau1_eta) < 2.1 && dau2_pt > 45 && abs(dau2_eta) < 2.1 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && isBoosted != 1 && bTagweightL > -999; 
    bool istautau_resolved_1b1j = isOS == 1 && pairType == 2 && dau1_pt > 45 && abs(dau1_eta) < 2.1 && dau2_pt > 45 && abs(dau2_eta) < 2.1 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID < 0.460 && isBoosted != 1 ;
    bool istautau_resolved_2b0j_Mcut = isOS == 1 && pairType == 2 && dau1_pt > 45 && abs(dau1_eta) < 2.1 && dau2_pt > 45 && abs(dau2_eta) < 2.1 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && isBoosted != 1 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && bH_mass_raw > 80 && bH_mass_raw < 160 && bTagweightL > -999 ;
    bool istautau_resolved_1b1j_Mcut = isOS == 1 && pairType == 2 && dau1_pt > 45 && abs(dau1_eta) < 2.1 && dau2_pt > 45 && abs(dau2_eta) < 2.1 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID < 0.460 && isBoosted != 1 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && bH_mass_raw > 80 && bH_mass_raw < 160; 
    
    bool istautau_resolved_2b0j_McutCirc = isOS == 1 && pairType == 2 && dau1_pt > 45 && abs(dau1_eta) < 2.1 && dau2_pt > 45 && abs(dau2_eta) < 2.1 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && isBoosted != 1 && TMath::Sqrt((tauH_SVFIT_mass-111)*(tauH_SVFIT_mass-111) + (bH_mass_raw-120)*(bH_mass_raw-120)) < 35 && bTagweightL > -999 ;
    bool istautau_resolved_1b1j_McutCirc = isOS == 1 && pairType == 2 && dau1_pt > 45 && abs(dau1_eta) < 2.1 && dau2_pt > 45 && abs(dau2_eta) < 2.1 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID < 0.460 && isBoosted != 1 && TMath::Sqrt((tauH_SVFIT_mass-111)*(tauH_SVFIT_mass-111) + (bH_mass_raw-120)*(bH_mass_raw-120)) < 35 ;
    
    
    bool istautau_boosted = isOS == 1 && pairType == 2 && dau1_pt > 45 && abs(dau1_eta) < 2.1 && dau2_pt > 45 && abs(dau2_eta) < 2.1 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && isBoosted == 1; 
    bool istautau_boosted_Mcut  = isOS == 1 && pairType == 2 && dau1_pt > 45 && abs(dau1_eta) < 2.1 && dau2_pt > 45 && abs(dau2_eta) < 2.1 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && isBoosted == 1 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && fatjet_softdropMass > 90 && fatjet_softdropMass < 160; 
    
    bool istautau_defaultBtagLLNoIsoBBTTCut450tag = isOS == 1 && pairType == 2 && dau1_pt > 45 && abs (dau1_eta) < 2.1 && dau2_pt > 45 && abs (dau2_eta) < 2.1 && nleps == 0 && bjet1_bID < 0.460 && bjet2_bID < 0.460 && bH_mass_raw > 80 && bH_mass_raw < 160 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && HH_mass_raw > 200 && bTagweightL > -999;
    bool istautau_defaultBtagLLNoIsoBBTTCut451tag = isOS == 1 && pairType == 2 && dau1_pt > 45 && abs (dau1_eta) < 2.1 && dau2_pt > 45 && abs (dau2_eta) < 2.1 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID < 0.460 && bH_mass_raw > 80 && bH_mass_raw < 160 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && HH_mass_raw > 200 && bTagweightL > -999;
    bool istautau_defaultBtagLLNoIsoBBTTCut45 = isOS == 1 && pairType == 2 && dau1_pt > 45 && abs (dau1_eta) < 2.1 && dau2_pt > 45 && abs (dau2_eta) < 2.1 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && bH_mass_raw > 80 && bH_mass_raw < 160 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && HH_mass_raw > 200 && bTagweightL > -999;
    bool istautau_defaultBtagLLNoIso45 = isOS == 1 && pairType == 2 && dau1_pt > 45 && abs (dau1_eta) < 2.1 && dau2_pt > 45 && abs (dau2_eta) < 2.1 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && HH_mass_raw > 200 && bTagweightL > -999;    
    */
    //-----------MuTau selections------------//
    //comb selections from selectionCfg_MuTau.cfg
    bool ismutau_1b1jMcut_SR = mutau_baseline && btagM && mutau_SR;
    bool ismutau_2b0jMcut_SR = mutau_baseline && btagMM && circMassCut && mutau_SR;
    bool ismutau_1b1jMcutBDT_SR = mutau_baseline && btagM && mutau_SR && nonresBDTCut;
    bool ismutau_2b0jMcutBDT_SR = mutau_baseline && btagMM && circMassCut && mutau_SR && nonresBDTCut;
   

    //selections from analysis_2016.cfg
    /* bool ismutau_resolved_2b0j = isOS == 1 && pairType == 0 && dau1_pt > 23 && abs(dau1_eta) < 2.1 && dau2_pt > 20 && abs(dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.800 && bjet2_bID > 0.800 && isBoosted != 1 && bTagweightM > -999 ;
    bool ismutau_resolved_1b1j = isOS == 1 && pairType == 0 && dau1_pt > 23 && abs(dau1_eta) < 2.1 && dau2_pt > 20 && abs(dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.800 && bjet2_bID < 0.800 && isBoosted != 1 ;
    bool ismutau_resolved_2b0j_Mcut = isOS == 1 && pairType == 0 && dau1_pt > 23 && abs(dau1_eta) < 2.1 && dau2_pt > 20 && abs(dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.800 && bjet2_bID > 0.800 && isBoosted != 1 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && bH_mass_raw > 80 && bH_mass_raw < 160 && bTagweightM > -999;
    bool ismutau_resolved_1b1j_Mcut = isOS == 1 && pairType == 0 && dau1_pt > 23 && abs(dau1_eta) < 2.1 && dau2_pt > 20 && abs(dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.800 && bjet2_bID < 0.800 && isBoosted != 1 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && bH_mass_raw > 80 && bH_mass_raw < 160 && bTagweightM > -999;
    bool ismutau_boosted  = isOS == 1 && pairType == 0 && dau1_pt > 23 && abs(dau1_eta) < 2.1 && dau2_pt > 20 && abs(dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && isBoosted == 1 ;
    bool ismutau_boosted_Mcut = isOS == 1 && pairType == 0 && dau1_pt > 23 && abs(dau1_eta) < 2.1 && dau2_pt > 20 && abs(dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && isBoosted == 1 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && fatjet_softdropMass > 90 && fatjet_softdropMass < 160 ;
    
    bool ismutau_defaultBtagMMNoIsoBBTTCut = isOS == 1 && pairType == 0 && dau1_pt > 23 && abs (dau1_eta) < 2.1 && dau2_pt > 20 && abs (dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.800 && bjet2_bID > 0.800 && bH_mass_raw > 80 && bH_mass_raw < 160 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && bTagweightM > -999;
    bool ismutau_defaultBtagLLNoIso = isOS == 1 && pairType == 0 && dau1_pt > 23 && abs (dau1_eta) < 2.1 && dau2_pt > 20 && abs (dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && HH_mass_raw > 200 && bTagweightL > -999;
    bool ismutau_defaultBtagLLNoIsoBBTTCut = isOS == 1 && pairType == 0 && dau1_pt > 23 && abs (dau1_eta) < 2.1 && dau2_pt > 20 && abs (dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && bH_mass_raw > 80 && bH_mass_raw < 160 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && HH_mass_raw > 200 && bTagweightL > -999;
    bool ismutau_defaultBtagLLNoIsoBBTTCutKine80 = isOS == 1 && pairType == 0 && dau1_pt > 23 && abs (dau1_eta) < 2.1 && dau2_pt > 20 && abs (dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && bH_mass_raw > 80 && bH_mass_raw < 160 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && LepTauKine > -0.134 && HH_mass_raw > 200 && bTagweightL > -999;
    bool ismutau_defaultBtagLLNoIsoBBTTCutKine801tag = isOS == 1 && pairType == 0 && dau1_pt > 23 && abs (dau1_eta) < 2.1 && dau2_pt > 20 && abs (dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID < 0.460 && bH_mass_raw > 80 && bH_mass_raw < 160 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && LepTauKine > -0.134 && HH_mass_raw > 200 && bTagweightL > -999;
    */
    //-----------ETau selections---------------//

    //comb selections from selectionCfg_Etau.cfg
    bool isetau_1b1jMcut_SR = etau_baseline && btagM && etau_SR;
    bool isetau_2b0jMcut_SR = etau_baseline && btagMM && circMassCut && etau_SR;
    bool isetau_1b1jMcutBDT_SR = etau_baseline && btagM && etau_SR && nonresBDTCut;
    bool isetau_2b0jMcutBDT_SR = etau_baseline && btagMM && circMassCut && etau_SR && nonresBDTCut;
   

    //selections from analysis_2016.cfg
    /*bool isetau_resolved_2b0j = isOS == 1 && pairType == 1 && dau1_pt > 27 && abs(dau1_eta) < 2.1 && dau2_pt > 20 && abs(dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.800 && bjet2_bID > 0.800 && isBoosted != 1 && bTagweightM > -999;
      bool isetau_resolved_1b1j = isOS == 1 && pairType == 1 && dau1_pt > 27 && abs(dau1_eta) < 2.1 && dau2_pt > 20 && abs(dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.800 && bjet2_bID < 0.800 && isBoosted != 1 ;
    bool isetau_resolved_2b0j_Mcut = isOS == 1 && pairType == 1 && dau1_pt > 27 && abs(dau1_eta) < 2.1 && dau2_pt > 20 && abs(dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.800 && bjet2_bID > 0.800 && isBoosted != 1 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && bH_mass_raw > 80 && bH_mass_raw < 160 && bTagweightM > -999;
    bool isetau_resolved_1b1j_Mcut = isOS == 1 && pairType == 1 && dau1_pt > 27 && abs(dau1_eta) < 2.1 && dau2_pt > 20 && abs(dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.800 && bjet2_bID < 0.800 && isBoosted != 1 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && bH_mass_raw > 80 && bH_mass_raw < 160 && bTagweightM > -999;
    bool isetau_boosted  = isOS == 1 && pairType == 1 && dau1_pt > 27 && abs(dau1_eta) < 2.1 && dau2_pt > 20 && abs(dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && isBoosted == 1 ;
    bool isetau_boosted_Mcut = isOS == 1 && pairType == 1 && dau1_pt > 27 && abs(dau1_eta) < 2.1 && dau2_pt > 20 && abs(dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && isBoosted == 1 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && fatjet_softdropMass > 90 && fatjet_softdropMass < 160 ;
    
    bool isetau_defaultBtagLLNoIso = isOS == 1 && pairType == 1 && dau1_pt > 27 && abs (dau1_eta) < 2.1 && dau2_pt > 20 && abs (dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && HH_mass_raw > 200 && bTagweightL > -999;
    bool isetau_defaultBtagLLNoIsoBBTTCut = isOS == 1 && pairType == 1 && dau1_pt > 27 && abs (dau1_eta) < 2.1 && dau2_pt > 20 && abs (dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && bH_mass_raw > 80 && bH_mass_raw < 160 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && HH_mass_raw > 200 && bTagweightL > -999;
    bool isetau_defaultBtagMMNoIsoBBTTCut = isOS == 1 && pairType == 1 && dau1_pt > 27 && abs (dau1_eta) < 2.1 && dau2_pt > 20 && abs (dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.800 && bjet2_bID > 0.800 && bH_mass_raw > 80 && bH_mass_raw < 160 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && bTagweightM > -999;
    bool isetau_defaultBtagLLNoIsoBBTTCutKine80 = isOS == 1 && pairType == 1 && dau1_pt > 27 && abs (dau1_eta) < 2.1 && dau2_pt > 20 && abs (dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && bH_mass_raw > 80 && bH_mass_raw < 160 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && LepTauKine > -0.134 && HH_mass_raw > 200 && bTagweightL > -999;
    bool isetau_defaultBtagLLNoIsoBBTTCutKine801tag = isOS == 1 && pairType == 1 && dau1_pt > 27 && abs (dau1_eta) < 2.1 && dau2_pt > 20 && abs (dau2_eta) < 2.3 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID < 0.460 && bH_mass_raw > 80 && bH_mass_raw < 160 && tauH_SVFIT_mass > 80 && tauH_SVFIT_mass < 160 && LepTauKine > -0.134 && HH_mass_raw > 200 && bTagweightL > -999;
    */


   tautau_1b1jMcut_SR = 0;
   tautau_2b0jMcut_SR = 0;
   tautau_1b1jMcut_SStight = 0;
   tautau_2b0jMcut_SStight = 0;

   mutau_1b1jMcut_SR = 0;
   mutau_2b0jMcut_SR = 0;
   mutau_1b1jMcutBDT_SR = 0;
   mutau_2b0jMcutBDT_SR = 0;

   etau_1b1jMcut_SR = 0;
   etau_2b0jMcut_SR = 0;
   etau_1b1jMcutBDT_SR = 0;
   etau_2b0jMcutBDT_SR = 0;



   if(istautau_1b1jMcut_SR) tautau_1b1jMcut_SR = 1;
   if(istautau_2b0jMcut_SR) tautau_2b0jMcut_SR = 1;
   if(istautau_1b1jMcut_SStight) tautau_1b1jMcut_SStight = 1;
   if(istautau_2b0jMcut_SStight) tautau_2b0jMcut_SStight = 1;

   if(ismutau_1b1jMcut_SR) mutau_1b1jMcut_SR = 1;
   if(ismutau_2b0jMcut_SR) mutau_2b0jMcut_SR = 1;
   if(ismutau_1b1jMcutBDT_SR) mutau_1b1jMcutBDT_SR = 1;
   if(ismutau_2b0jMcutBDT_SR) mutau_2b0jMcutBDT_SR = 1;

   if(isetau_1b1jMcut_SR) etau_1b1jMcut_SR = 1;
   if(isetau_2b0jMcut_SR) etau_2b0jMcut_SR = 1;
   if(isetau_1b1jMcutBDT_SR) etau_1b1jMcutBDT_SR = 1;
   if(isetau_2b0jMcutBDT_SR) etau_2b0jMcutBDT_SR = 1;


   /*
    tautau_resolved_2b0j = 0;
    tautau_resolved_1b1j = 0;
    tautau_resolved_2b0j_Mcut = 0;
    tautau_resolved_1b1j_Mcut = 0;
    tautau_resolved_2b0j_McutCirc = 0;
    tautau_resolved_1b1j_McutCirc = 0;
    tautau_boosted = 0;
    tautau_boosted_Mcut = 0;
    tautau_defaultBtagLLNoIsoBBTTCut450tag = 0;
    tautau_defaultBtagLLNoIsoBBTTCut451tag = 0;
    tautau_defaultBtagLLNoIsoBBTTCut45 = 0;
    tautau_defaultBtagLLNoIso45 = 0;
    
    mutau_resolved_2b0j = 0;
    mutau_resolved_1b1j = 0;
    mutau_resolved_2b0j_Mcut = 0;
    mutau_resolved_1b1j_Mcut = 0;
    mutau_boosted = 0;
    mutau_boosted_Mcut = 0;
    mutau_defaultBtagMMNoIsoBBTTCut = 0;
    mutau_defaultBtagLLNoIso = 0;
    mutau_defaultBtagLLNoIsoBBTTCut = 0;
    mutau_defaultBtagLLNoIsoBBTTCutKine80 = 0;
    mutau_defaultBtagLLNoIsoBBTTCutKine801tag = 0;

    etau_resolved_2b0j = 0;
    etau_resolved_1b1j = 0;
    etau_resolved_2b0j_Mcut = 0;
    etau_resolved_1b1j_Mcut = 0;
    etau_boosted = 0;
    etau_boosted_Mcut = 0;
    etau_defaultBtagMMNoIsoBBTTCut = 0;
    etau_defaultBtagLLNoIso = 0;
    etau_defaultBtagLLNoIsoBBTTCut = 0;
    etau_defaultBtagLLNoIsoBBTTCutKine80 = 0;
    etau_defaultBtagLLNoIsoBBTTCutKine801tag = 0;
  
    if(istautau_resolved_2b0j)   tautau_resolved_2b0j = 1;
    if(istautau_resolved_1b1j)   tautau_resolved_1b1j = 1;
    if(istautau_resolved_2b0j_Mcut)   tautau_resolved_2b0j_Mcut = 1;
    if(istautau_resolved_1b1j_Mcut)   tautau_resolved_1b1j_Mcut = 1;
    if(istautau_resolved_2b0j_McutCirc)   tautau_resolved_2b0j_McutCirc = 1;
    if(istautau_resolved_1b1j_McutCirc)   tautau_resolved_1b1j_McutCirc = 1;
    if(istautau_boosted)   tautau_boosted = 1;
    if(istautau_boosted_Mcut)   tautau_boosted_Mcut = 1;
    if(istautau_defaultBtagLLNoIsoBBTTCut450tag)   tautau_defaultBtagLLNoIsoBBTTCut450tag = 1;
    if(istautau_defaultBtagLLNoIsoBBTTCut451tag)   tautau_defaultBtagLLNoIsoBBTTCut451tag = 1;
    if(istautau_defaultBtagLLNoIsoBBTTCut45)   tautau_defaultBtagLLNoIsoBBTTCut45 = 1;
    if(istautau_defaultBtagLLNoIso45)   tautau_defaultBtagLLNoIso45 = 1;
   
    if(ismutau_resolved_2b0j) mutau_resolved_2b0j = 1;
    if(ismutau_resolved_1b1j) mutau_resolved_1b1j = 1;
    if(ismutau_resolved_2b0j_Mcut) mutau_resolved_2b0j_Mcut = 1;
    if(ismutau_resolved_1b1j_Mcut) mutau_resolved_1b1j_Mcut = 1;
    if(ismutau_boosted) mutau_boosted = 1;
    if(ismutau_boosted_Mcut) mutau_boosted_Mcut = 1;
    if(ismutau_defaultBtagMMNoIsoBBTTCut) mutau_defaultBtagMMNoIsoBBTTCut = 1;
    if(ismutau_defaultBtagLLNoIso) mutau_defaultBtagLLNoIso = 1;
    if(ismutau_defaultBtagLLNoIsoBBTTCut) mutau_defaultBtagLLNoIsoBBTTCut = 1;
    if(ismutau_defaultBtagLLNoIsoBBTTCutKine80) mutau_defaultBtagLLNoIsoBBTTCutKine80 = 1;
    if(ismutau_defaultBtagLLNoIsoBBTTCutKine801tag) mutau_defaultBtagLLNoIsoBBTTCutKine801tag = 1;

    if(isetau_resolved_2b0j) etau_resolved_2b0j = 1;
    if(isetau_resolved_1b1j) etau_resolved_1b1j = 1;
    if(isetau_resolved_2b0j_Mcut) etau_resolved_2b0j_Mcut = 1;
    if(isetau_resolved_1b1j_Mcut) etau_resolved_1b1j_Mcut = 1;
    if(isetau_boosted) etau_boosted = 1;
    if(isetau_boosted_Mcut) etau_boosted_Mcut = 1;
    if(isetau_defaultBtagMMNoIsoBBTTCut) etau_defaultBtagMMNoIsoBBTTCut = 1;
    if(isetau_defaultBtagLLNoIso) etau_defaultBtagLLNoIso = 1;
    if(isetau_defaultBtagLLNoIsoBBTTCut) etau_defaultBtagLLNoIsoBBTTCut = 1;
    if(isetau_defaultBtagLLNoIsoBBTTCutKine80) etau_defaultBtagLLNoIsoBBTTCutKine80 = 1;
    if(isetau_defaultBtagLLNoIsoBBTTCutKine801tag) etau_defaultBtagLLNoIsoBBTTCutKine801tag = 1;
   */   
 treeNew->Fill();  
    
  }
  fileNew->cd();
  treeNew->Write();
  fileNew->Close();
  

}

