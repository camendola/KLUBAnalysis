#define selEvents_cxx
#define myclass_cxx
#include "myclass.h"

#include <TFile.h>
#include <TTree.h>
#include <TMath.h>

#include <iostream>
#include <fstream>
#include <iomanip>



void selEvents(int i_split ){
  TString dir_in;
  TString dir_out;
  TString filename;    
  TString infileName;    
  vector<TString> list;

  
  dir_in="/data_CMS/cms/amendola/TestSelections/skimmed/";
  filename=dir_in+Form("output_%i",i_split);
  TFile *file = TFile::Open(Form("%s.root",filename.Data()));
  TTree *tree = (TTree *) file->Get("HTauTauTree");
  tree->ls();  
  myclass theTree(tree); 
  TFile *fileNew = TFile::Open(Form("%s_sel.root",filename.Data()),"recreate");
  TTree *treeNew = new TTree ("HTauTauTreeSelections","HTauTauTreeSelections");
  unsigned int nentries = tree->GetEntries(); 
  //original tree 
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
  
  treeNew->SetAutoSave(-99999999999);
  treeNew->SetAutoFlush(-99999999999);
  treeNew->Branch("tautau_resolved_2b0j",&tautau_resolved_2b0j,"tautau_resolved_2b0j/I");
  treeNew->Branch("tautau_resolved_1b1j",&tautau_resolved_1b1j,"tautau_resolved_1b1j/I");
  treeNew->Branch("tautau_resolved_2b0j_Mcut",&tautau_resolved_2b0j_Mcut,"tautau_resolved_2b0j_Mcut/I");
  treeNew->Branch("tautau_resolved_1b1j_Mcut",&tautau_resolved_1b1j_Mcut,"tautau_resolved_1b1j_Mcut/I");
  treeNew->Branch("tautau_boosted",&tautau_boosted,"tautau_boosted/I");
  treeNew->Branch("tautau_boosted_Mcut",&tautau_boosted_Mcut,"tautau_boosted_Mcut/I");
  treeNew->Branch("tautau_defaultBtagLLNoIsoBBTTCut450tag",&tautau_defaultBtagLLNoIsoBBTTCut450tag,"tautau_defaultBtagLLNoIsoBBTTCut450tag/I");
  treeNew->Branch("tautau_defaultBtagLLNoIsoBBTTCut451tag",&tautau_defaultBtagLLNoIsoBBTTCut451tag,"tautau_defaultBtagLLNoIsoBBTTCut451tag/I");
  treeNew->Branch("tautau_defaultBtagLLNoIsoBBTTCut45",&tautau_defaultBtagLLNoIsoBBTTCut45,"tautau_defaultBtagLLNoIsoBBTTCut45/I");
  treeNew->Branch("tautau_defaultBtagLLNoIso45",&tautau_defaultBtagLLNoIso45,"tautau_defaultBtagLLNoIso45/I");


   
  for(unsigned int i=0; i<nentries; i++) {
    
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
    file->cd();
    tree->ls();
    theTree.GetEntry(i);
    tree->GetEntry(i);      
    dau1_pt = theTree.dau1_pt;
    
    if (i%10000 == 0){
      cout<<theTree.dau1_pt<<endl;    
      cout<<dau1_pt<<endl;
      cout<<EventNumber<<endl;
      
      std::cout << ">>> Event # " << i << " / " << nentries << " entries" << std::endl; 
    }
    
    // TauTau selections 
    bool istautau_resolved_2b0j = isOS == 1 && pairType == 2 && dau1_pt > 45 && abs(dau1_eta) < 2.1 && dau2_pt > 45 && abs(dau2_eta) < 2.1 && nleps == 0 && bjet1_bID > 0.460 && bjet2_bID > 0.460 && isBoosted != 1 && bTagweightL > -999; 
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
    treeNew->Fill();  

}
  fileNew->cd();
  treeNew->Write();
  fileNew->Close();

  file->cd();
  file->Close();
}
