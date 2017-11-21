using namespace std;

#define syncNtuples_cxx
#define oldTree_cxx
#include "../interface/oldTree.h"
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TMath.h>
#include <sstream>
#include <fstream>
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "TChain.h"
#include "TString.h"



#include <boost/algorithm/string/replace.hpp>

void appendFromFileList (TChain* chain, TString filename)
{
  //cout << "=== inizio parser ===" << endl;
  std::ifstream infile(filename.Data());
  std::string line;
  while (std::getline(infile, line))
    {
      line = line.substr(0, line.find("#", 0)); // remove comments introduced by #
      while (line.find(" ") != std::string::npos) line = line.erase(line.find(" "), 1); // remove white spaces
      while (line.find("\n") != std::string::npos) line = line.erase(line.find("\n"), 1); // remove new line characters
      while (line.find("\r") != std::string::npos) line = line.erase(line.find("\r"), 1); // remove carriage return characters
      if (!line.empty()) // skip empty lines
	chain->Add(line.c_str());
    }
  return;
}

int main (int argc, char** argv){

  TString inputFile = argv[1] ;
  TString outputFile = argv[2] ;
  cout << "** INFO: inputFile  : " << inputFile << endl;
  cout << "** INFO: outputFile : " << outputFile << endl;
  
  TChain * oldTreeC = new TChain ("HTauTauTree");
  appendFromFileList(oldTreeC, inputFile);
  oldTree theOldTree(oldTreeC);
  
  TFile *fileNew = new TFile(outputFile,"recreate");
  TChain *newchain = (TChain*)oldTreeC->CloneTree(0); 
  TTree *newTree = newchain->GetTree();
  
  Int_t           datasetID;
  
  // 0 TT_TuneCUETP8M2T4
  // 1 TT_TuneCUETP8M2T4_backup
  // 2 TTTo2L2Nu_TuneCUETP8M2_ttHtranche3
  // 3 TTToSemilepton_TuneCUETP8M2_ttHtranche3
    
  TBranch        *b_datasetID;   //!
    
  newTree->SetBranchAddress("datasetID", &datasetID, &b_datasetID);

  for (Long64_t i =0 ;true; ++i){

    int got = 0;
    got = theOldTree.GetEntry(i);
    if (got == 0) break;
    //  for(unsigned int i=0; i<nentries; i++) {
    // theOldTree.GetEntry(i);    
    int isOS = theOldTree.isOS;
    int pairType = theOldTree.pairType;
    int isBoosted = theOldTree.isBoosted;
    int nleps = theOldTree.nleps;
    float dau1_pt = theOldTree.dau1_pt;
    float dau2_pt = theOldTree.dau2_pt;
    float dau1_eta = theOldTree.dau1_eta;
    float dau2_eta = theOldTree.dau2_eta;
    float  bjet1_bID = theOldTree.bjet1_bID;
    float  bjet2_bID = theOldTree.bjet2_bID;
    float tauH_SVFIT_mass = theOldTree.tauH_SVFIT_mass;
    float bH_mass_raw = theOldTree.bH_mass_raw;
    float HH_mass_raw = theOldTree.HH_mass_raw;
    float fatjet_softdropMass = theOldTree.fatjet_softdropMass;
    float bTagweightL =  theOldTree.bTagweightL;
    float bTagweightM =  theOldTree.bTagweightM;
    float LepTauKine =  theOldTree.LepTauKine;
    int dau1_MVAiso = theOldTree.dau1_MVAiso;
    float dau1_iso = theOldTree.dau1_iso;
    int dau2_MVAiso = theOldTree.dau2_MVAiso;
    float bjet1_pt_raw = theOldTree.bjet1_pt_raw;
    float bjet2_pt_raw = theOldTree.bjet2_pt_raw;
    vector<float> *jets_btag=theOldTree.jets_btag;
    vector<float> *jets_eta=theOldTree.jets_eta;


    	
    datasetID = 1;
    

  
            
    
    if (i%10000 == 0){
          std::cout << ">>> Event # " << i  << std::endl; 
    }

    
    //basic selections from selectionCfg_TauTau.cfg

    bool baseline = pairType == 2 && dau1_pt > 45 && abs (dau1_eta) < 2.1 && dau2_pt > 45 && abs (dau2_eta) < 2.1 && nleps == 0;
  
  

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
    
    bool s1b1jresolvedMcut = baseline && btagM && isBoosted != 1 && ellypsMassCut;
    
    if (s1b1jresolvedMcut){
      newTree->Fill();
    }
    
  }
  fileNew->cd();

  fileNew->Close();

  return 0;
}

