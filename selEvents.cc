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


  //TString dir_in="/data_CMS/cms/cadamuro/test_submit_to_tier3/Skims2017_10Gen/SKIM_TT_fullyHad/";
  // TString dir_out="/data_CMS/cms/amendola/TestSelections/TT_background/fullyHad/";


  //  TString dir_in="/data_CMS/cms/cadamuro/test_submit_to_tier3/Skims2017_10Gen/SKIM_TT_semiLep/";
  //TString dir_out="/data_CMS/cms/amendola/TestSelections/TT_background/semiLep/";

  TString dir_in="./comb_test/";
  TString dir_out="./comb_test/";

  
  
  TString fileList;    
  TString outfilename;
  //  TString process = "GluGluToHHTo2B2Tau_node_SM";
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

  Bool_t passTrgBBres;
  Bool_t passTrgBBnonres;
  Bool_t passTrgGG;
  
  TBranch        *b_EventNumber;   //!
  TBranch        *b_RunNumber;   //!
  TBranch        *b_lumi;   //!  

  TBranch *b_passTrgBBres;
  TBranch *b_passTrgBBnonres;
  TBranch *b_passTrgGG;
  
  tree->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
  tree->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
  tree->SetBranchAddress("lumi", &lumi, &b_lumi);

  tree->SetBranchAddress("passTrgBBres",&passTrgBBres,&b_passTrgBBres);
  tree->SetBranchAddress("passTrgBBnonres",&passTrgBBnonres,&b_passTrgBBnonres);
  tree->SetBranchAddress("passTrgGG",&passTrgGG,&b_passTrgBBres);

  
  treeNew->Branch("EventNumber", &EventNumber, "EventNumber/I");
  treeNew->Branch("RunNumber", &RunNumber, "RunNumber/I");
  treeNew->Branch("lumi", &lumi, "lumi/I");


  treeNew->Branch("passTrgBBres",&passTrgBBres,"passTrgBBres/O");
  treeNew->Branch("passTrgBBnonres",&passTrgBBnonres,"passTrgBBnonres/O");
  treeNew->Branch("passTrgGG",&passTrgGG,"passTrgGG/O");



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
    //    tree->ls();



    
    

    //    tree->GetEntry(i);      
    
    
    if (i%10000 == 0){
          std::cout << ">>> Event # " << i  << std::endl; 
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
    
    


    //-----------MuTau selections------------//
    //comb selections from selectionCfg_MuTau.cfg
    bool ismutau_1b1jMcut_SR = mutau_baseline && btagM && mutau_SR;
    bool ismutau_2b0jMcut_SR = mutau_baseline && btagMM && circMassCut && mutau_SR;
    bool ismutau_1b1jMcutBDT_SR = mutau_baseline && btagM && mutau_SR && nonresBDTCut;
    bool ismutau_2b0jMcutBDT_SR = mutau_baseline && btagMM && circMassCut && mutau_SR && nonresBDTCut;
   


    //-----------ETau selections---------------//

    //comb selections from selectionCfg_Etau.cfg
    bool isetau_1b1jMcut_SR = etau_baseline && btagM && etau_SR;
    bool isetau_2b0jMcut_SR = etau_baseline && btagMM && circMassCut && etau_SR;
    bool isetau_1b1jMcutBDT_SR = etau_baseline && btagM && etau_SR && nonresBDTCut;
    bool isetau_2b0jMcutBDT_SR = etau_baseline && btagMM && circMassCut && etau_SR && nonresBDTCut;
   




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


 treeNew->Fill();  
    
  }
  fileNew->cd();
  treeNew->Write();
  fileNew->Close();
  

}

