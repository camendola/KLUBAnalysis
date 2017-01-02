#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TProfile.h>


#include <iostream>
#include <TLegend.h>
#include <TBranch.h>
#include <TClonesArray.h>
#include <TChain.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TGraphAsymmErrors.h>
#include <TF1.h>
#include "interface/bigTree.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"


#include <vector>
#include <map>



using namespace std;



void convert(int i_split=0, bool isMC=true){

  TString dir_in;
  TString dir_out;
  TString file;    
TString infileName;    

  
  vector<TString> list;
  
  
  file="ntuples_HTauTauAnalysis";
  dir_out="/data_CMS/cms/amendola/TestSelections/ntuples_converted/";
  
  
  dir_in="root://polgrid4.in2p3.fr//dpm/in2p3.fr/home/cms/trivcat/store/user/salerno/HHNtuples/MC_80X_ttbar_07Jul2016/1_TT_TuneCUETP8M1_13TeV-powheg-pythia8__RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0_ext4-v1/TT_TuneCUETP8M1_13TeV-powheg-pythia8/TT_TuneCUETP8M1_13TeV-powheg-pythia8_MC_80X_ttbar_07Jul2016_1/160707_085658/";
  
  int i_dir=i_split/10;
  dir_in+=Form("000%i/",i_dir);
  
  int i_min=i_split*100;
  if(i_split==0) i_min++;
  int i_max=(i_split+1)*100;
  if(i_split==91) i_max=112;
  
    
  for(int i=i_min;i<i_max;i++){
    infileName = dir_in+Form("HTauTauAnalysis_%i.root",i);  
    cout<<infileName<<endl;
    TFile *infile = TFile::Open(Form("%s",infileName.Data()),"read");
    if (infile == NULL) continue;  
    list.push_back(dir_in+Form("HTauTauAnalysis_%i.root",i));
  }
  
  
  

  
  file+=Form("_%i",i_split);
  file+=".root";
  
  
  
   TChain * tree = new TChain("HTauTauTree/HTauTauTree");
  int nFiles = list.size();
 
   for(int i=0;i<nFiles;i++)
     //  for(int i=0;i<10;i++)
    {
      tree->Add(list[i]);
    }
  
  
  
  Long64_t nentries = tree->GetEntries();
  //nentries=100;
  
  
    
  TFile* f_new = TFile::Open(dir_out+file,"RECREATE");
  
  
  
  
  TTree* tree_new=tree->GetTree()->CloneTree(0);
  tree_new=new TTree("HTauTauTree","HTauTauTree");
    
  
  // Declaration of leaf types
   ULong64_t       EventNumber;
   Int_t           RunNumber;
   Int_t           lumi;
   Long64_t        triggerbit;
   Int_t           metfilterbit;
   Float_t         met;
   Float_t         metphi;
   Float_t         PUPPImet;
   Float_t         PUPPImetphi;
   Float_t         PFMETCov00;
   Float_t         PFMETCov01;
   Float_t         PFMETCov10;
   Float_t         PFMETCov11;
   Float_t         PFMETsignif;
   Int_t           npv;
   Float_t         npu;
   Float_t         PUReweight;
   Float_t         rho;
   vector<float>   *mothers_px;
   vector<float>   *mothers_py;
   vector<float>   *mothers_pz;
   vector<float>   *mothers_e;
   vector<float>   *daughters_px;
   vector<float>   *daughters_py;
   vector<float>   *daughters_pz;
   vector<float>   *daughters_e;
   vector<int>     *daughters_charge;
   vector<int>     *daughters_TauUpExists;
   vector<float>   *daughters_px_TauUp;
   vector<float>   *daughters_py_TauUp;
   vector<float>   *daughters_pz_TauUp;
   vector<float>   *daughters_e_TauUp;
   vector<int>     *daughters_TauDownExists;
   vector<float>   *daughters_px_TauDown;
   vector<float>   *daughters_py_TauDown;
   vector<float>   *daughters_pz_TauDown;
   vector<float>   *daughters_e_TauDown;
   Int_t           PUNumInteractions;
   vector<int>     *daughters_genindex;
   Float_t         MC_weight;
   Float_t         lheHt;
   Int_t           lheNOutPartons;
   Int_t           lheNOutB;
   Float_t         aMCatNLOweight;
   vector<float>   *genpart_px;
   vector<float>   *genpart_py;
   vector<float>   *genpart_pz;
   vector<float>   *genpart_e;
   vector<int>     *genpart_pdg;
   vector<int>     *genpart_status;
   vector<int>     *genpart_HMothInd;
   vector<int>     *genpart_MSSMHMothInd;
   vector<int>     *genpart_TopMothInd;
   vector<int>     *genpart_TauMothInd;
   vector<int>     *genpart_ZMothInd;
   vector<int>     *genpart_WMothInd;
   vector<int>     *genpart_bMothInd;
   vector<int>     *genpart_HZDecayMode;
   vector<int>     *genpart_TopDecayMode;
   vector<int>     *genpart_WDecayMode;
   vector<int>     *genpart_TauGenDecayMode;
   vector<int>     *genpart_flags;
   vector<float>   *genjet_px;
   vector<float>   *genjet_py;
   vector<float>   *genjet_pz;
   vector<float>   *genjet_e;
   vector<int>     *genjet_partonFlavour;
   vector<int>     *genjet_hadronFlavour;
   Int_t           NUP;
   vector<float>   *SVfitMass;
   vector<float>   *SVfitMassTauUp;
   vector<float>   *SVfitMassTauDown;
   vector<float>   *SVfitTransverseMass;
   vector<float>   *SVfitTransverseMassTauUp;
   vector<float>   *SVfitTransverseMassTauDown;
   vector<float>   *SVfit_pt;
   vector<float>   *SVfit_ptTauUp;
   vector<float>   *SVfit_ptTauDown;
   vector<float>   *SVfit_ptUnc;
   vector<float>   *SVfit_ptUncTauUp;
   vector<float>   *SVfit_ptUncTauDown;
   vector<float>   *SVfit_eta;
   vector<float>   *SVfit_etaTauUp;
   vector<float>   *SVfit_etaTauDown;
   vector<float>   *SVfit_etaUnc;
   vector<float>   *SVfit_etaUncTauUp;
   vector<float>   *SVfit_etaUncTauDown;
   vector<float>   *SVfit_phi;
   vector<float>   *SVfit_phiTauUp;
   vector<float>   *SVfit_phiTauDown;
   vector<float>   *SVfit_phiUnc;
   vector<float>   *SVfit_phiUncTauUp;
   vector<float>   *SVfit_phiUncTauDown;
   vector<float>   *SVfit_fitMETRho;
   vector<float>   *SVfit_fitMETRhoTauUp;
   vector<float>   *SVfit_fitMETRhoTauDown;
   vector<float>   *SVfit_fitMETPhi;
   vector<float>   *SVfit_fitMETPhiTauUp;
   vector<float>   *SVfit_fitMETPhiTauDown;
   vector<bool>    *isOSCand;
   vector<float>   *METx;
   vector<float>   *METy;
   vector<float>   *uncorrMETx;
   vector<float>   *uncorrMETy;
   vector<float>   *MET_cov00;
   vector<float>   *MET_cov01;
   vector<float>   *MET_cov10;
   vector<float>   *MET_cov11;
   vector<float>   *MET_significance;
   vector<float>   *mT_Dau1;
   vector<float>   *mT_Dau2;
   vector<int>     *PDGIdDaughters;
   vector<int>     *indexDau1;
   vector<int>     *indexDau2;
   vector<int>     *particleType;
   vector<float>   *discriminator;
   vector<int>     *daughters_muonID;
   vector<int>     *daughters_typeOfMuon;
   vector<float>   *dxy;
   vector<float>   *dz;
   vector<float>   *dxy_innerTrack;
   vector<float>   *dz_innerTrack;
   vector<float>   *daughters_rel_error_trackpt;
   vector<float>   *SIP;
   vector<bool>    *daughters_iseleBDT;
   vector<bool>    *daughters_iseleWP80;
   vector<bool>    *daughters_iseleWP90;
   vector<float>   *daughters_eleMVAnt;
   vector<bool>    *daughters_passConversionVeto;
   vector<int>     *daughters_eleMissingHits;
   vector<bool>    *daughters_iseleChargeConsistent;
   vector<int>     *daughters_eleCUTID;
   vector<int>     *decayMode;
   vector<Long64_t> *tauID;
   vector<float>   *combreliso;
   vector<float>   *daughters_IetaIeta;
   vector<float>   *daughters_hOverE;
   vector<float>   *daughters_deltaEtaSuperClusterTrackAtVtx;
   vector<float>   *daughters_deltaPhiSuperClusterTrackAtVtx;
   vector<float>   *daughters_IoEmIoP;
   vector<float>   *daughters_IoEmIoP_ttH;
   vector<float>   *daughters_SCeta;
   vector<float>   *daughters_depositR03_tracker;
   vector<float>   *daughters_depositR03_ecal;
   vector<float>   *daughters_depositR03_hcal;
   vector<int>     *daughters_decayModeFindingOldDMs;
   vector<float>   *againstElectronMVA5category;
   vector<float>   *againstElectronMVA5raw;
   vector<float>   *byPileupWeightedIsolationRaw3Hits;
   vector<float>   *footprintCorrection;
   vector<float>   *neutralIsoPtSumWeight;
   vector<float>   *photonPtSumOutsideSignalCone;
   vector<int>     *daughters_decayModeFindingNewDMs;
   vector<float>   *daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits;
   vector<float>   *daughters_byIsolationMVA3oldDMwoLTraw;
   vector<float>   *daughters_byIsolationMVA3oldDMwLTraw;
   vector<float>   *daughters_byIsolationMVA3newDMwoLTraw;
   vector<float>   *daughters_byIsolationMVA3newDMwLTraw;
   vector<float>   *daughters_chargedIsoPtSum;
   vector<float>   *daughters_neutralIsoPtSum;
   vector<float>   *daughters_puCorrPtSum;
   vector<int>     *daughters_numChargedParticlesSignalCone;
   vector<int>     *daughters_numNeutralHadronsSignalCone;
   vector<int>     *daughters_numPhotonsSignalCone;
   vector<int>     *daughters_daughters_numParticlesSignalCone;
   vector<int>     *daughters_numChargedParticlesIsoCone;
   vector<int>     *daughters_numNeutralHadronsIsoCone;
   vector<int>     *daughters_numPhotonsIsoCone;
   vector<int>     *daughters_numParticlesIsoCone;
   vector<float>   *daughters_leadChargedParticlePt;
   vector<float>   *daughters_trackRefPt;
   vector<int>     *daughters_isLastTriggerObjectforPath;
   vector<Long64_t> *daughters_trgMatched;
   vector<int>     *daughters_isTriggerObjectforPath;
   vector<Long64_t> *daughters_FilterFired;
   vector<Long64_t> *daughters_isGoodTriggerType;
   vector<Long64_t> *daughters_L3FilterFired;
   vector<Long64_t> *daughters_L3FilterFiredLast;
   vector<float>   *daughters_HLTpt;
   vector<bool>    *daughters_isL1IsoTau28Matched;
   vector<int>     *daughters_jetNDauChargedMVASel;
   vector<float>   *daughters_miniRelIsoCharged;
   vector<float>   *daughters_miniRelIsoNeutral;
   vector<float>   *daughters_jetPtRel;
   vector<float>   *daughters_jetPtRatio;
   vector<float>   *daughters_jetBTagCSV;
   vector<float>   *daughters_lepMVA_mvaId;
   Int_t           JetsNumber;
   vector<float>   *jets_px;
   vector<float>   *jets_py;
   vector<float>   *jets_pz;
   vector<float>   *jets_e;
   vector<float>   *jets_rawPt;
   vector<float>   *jets_area;
   vector<float>   *jets_mT;
   vector<int>     *jets_Flavour;
   vector<int>     *jets_HadronFlavour;
   vector<int>     *jets_genjetIndex;
   vector<float>   *jets_PUJetID;
   vector<float>   *jets_PUJetIDupdated;
   vector<float>   *jets_vtxPt;
   vector<float>   *jets_vtxMass;
   vector<float>   *jets_vtx3dL;
   vector<float>   *jets_vtxNtrk;
   vector<float>   *jets_vtx3deL;
   vector<float>   *jets_leadTrackPt;
   vector<float>   *jets_leptonPtRel;
   vector<float>   *jets_leptonPt;
   vector<float>   *jets_leptonDeltaR;
   vector<float>   *jets_chEmEF;
   vector<float>   *jets_chHEF;
   vector<float>   *jets_nEmEF;
   vector<float>   *jets_nHEF;
   vector<int>     *jets_chMult;
   vector<float>   *jets_jecUnc;
   vector<float>   *bDiscriminator;
   vector<float>   *bCSVscore;
   vector<float>   *pfCombinedMVAV2BJetTags;
   vector<int>     *PFjetID;
   vector<float>   *jetRawf;
   vector<float>   *ak8jets_px;
   vector<float>   *ak8jets_py;
   vector<float>   *ak8jets_pz;
   vector<float>   *ak8jets_e;
   vector<float>   *ak8jets_SoftDropMass;
   vector<float>   *ak8jets_PrunedMass;
   vector<float>   *ak8jets_TrimmedMass;
   vector<float>   *ak8jets_FilteredMass;
   vector<float>   *ak8jets_tau1;
   vector<float>   *ak8jets_tau2;
   vector<float>   *ak8jets_tau3;
   vector<float>   *ak8jets_CSV;
   vector<int>     *ak8jets_nsubjets;
   vector<float>   *subjets_px;
   vector<float>   *subjets_py;
   vector<float>   *subjets_pz;
   vector<float>   *subjets_e;
   vector<float>   *subjets_CSV;
   vector<int>     *subjets_ak8MotherIdx;


  
  // List of branches
   TBranch        *b_EventNumber;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_triggerbit;   //!
   TBranch        *b_metfilterbit;   //!
   TBranch        *b_met;   //!
   TBranch        *b_metphi;   //!
   TBranch        *b_PUPPImet;   //!
   TBranch        *b_PUPPImetphi;   //!
   TBranch        *b_PFMETCov00;   //!
   TBranch        *b_PFMETCov01;   //!
   TBranch        *b_PFMETCov10;   //!
   TBranch        *b_PFMETCov11;   //!
   TBranch        *b_PFMETsignif;   //!
   TBranch        *b_npv;   //!
   TBranch        *b_npu;   //!
   TBranch        *b_PUReweight;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_mothers_px;   //!
   TBranch        *b_mothers_py;   //!
   TBranch        *b_mothers_pz;   //!
   TBranch        *b_mothers_e;   //!
   TBranch        *b_daughters_px;   //!
   TBranch        *b_daughters_py;   //!
   TBranch        *b_daughters_pz;   //!
   TBranch        *b_daughters_e;   //!
   TBranch        *b_daughters_charge;   //!
   TBranch        *b_daughters_TauUpExists;   //!
   TBranch        *b_daughters_px_TauUp;   //!
   TBranch        *b_daughters_py_TauUp;   //!
   TBranch        *b_daughters_pz_TauUp;   //!
   TBranch        *b_daughters_e_TauUp;   //!
   TBranch        *b_daughters_TauDownExists;   //!
   TBranch        *b_daughters_px_TauDown;   //!
   TBranch        *b_daughters_py_TauDown;   //!
   TBranch        *b_daughters_pz_TauDown;   //!
   TBranch        *b_daughters_e_TauDown;   //!
   TBranch        *b_PUNumInteractions;   //!
   TBranch        *b_daughters_genindex;   //!
   TBranch        *b_MC_weight;   //!
   TBranch        *b_lheHt;   //!
   TBranch        *b_lheNOutPartons;   //!
   TBranch        *b_lheNOutB;   //!
   TBranch        *b_aMCatNLOweight;   //!
   TBranch        *b_genpart_px;   //!
   TBranch        *b_genpart_py;   //!
   TBranch        *b_genpart_pz;   //!
   TBranch        *b_genpart_e;   //!
   TBranch        *b_genpart_pdg;   //!
   TBranch        *b_genpart_status;   //!
   TBranch        *b_genpart_HMothInd;   //!
   TBranch        *b_genpart_MSSMHMothInd;   //!
   TBranch        *b_genpart_TopMothInd;   //!
   TBranch        *b_genpart_TauMothInd;   //!
   TBranch        *b_genpart_ZMothInd;   //!
   TBranch        *b_genpart_WMothInd;   //!
   TBranch        *b_genpart_bMothInd;   //!
   TBranch        *b_genpart_HZDecayMode;   //!
   TBranch        *b_genpart_TopDecayMode;   //!
   TBranch        *b_genpart_WDecayMode;   //!
   TBranch        *b_genpart_TauGenDecayMode;   //!
   TBranch        *b_genpart_flags;   //!
   TBranch        *b_genjet_px;   //!
   TBranch        *b_genjet_py;   //!
   TBranch        *b_genjet_pz;   //!
   TBranch        *b_genjet_e;   //!
   TBranch        *b_genjet_partonFlavour;   //!
   TBranch        *b_genjet_hadronFlavour;   //!
   TBranch        *b_NUP;   //!
   TBranch        *b_SVfitMass;   //!
   TBranch        *b_SVfitMassTauUp;   //!
   TBranch        *b_SVfitMassTauDown;   //!
   TBranch        *b_SVfitTransverseMass;   //!
   TBranch        *b_SVfitTransverseMassTauUp;   //!
   TBranch        *b_SVfitTransverseMassTauDown;   //!
   TBranch        *b_SVfit_pt;   //!
   TBranch        *b_SVfit_ptTauUp;   //!
   TBranch        *b_SVfit_ptTauDown;   //!
   TBranch        *b_SVfit_ptUnc;   //!
   TBranch        *b_SVfit_ptUncTauUp;   //!
   TBranch        *b_SVfit_ptUncTauDown;   //!
   TBranch        *b_SVfit_eta;   //!
   TBranch        *b_SVfit_etaTauUp;   //!
   TBranch        *b_SVfit_etaTauDown;   //!
   TBranch        *b_SVfit_etaUnc;   //!
   TBranch        *b_SVfit_etaUncTauUp;   //!
   TBranch        *b_SVfit_etaUncTauDown;   //!
   TBranch        *b_SVfit_phi;   //!
   TBranch        *b_SVfit_phiTauUp;   //!
   TBranch        *b_SVfit_phiTauDown;   //!
   TBranch        *b_SVfit_phiUnc;   //!
   TBranch        *b_SVfit_phiUncTauUp;   //!
   TBranch        *b_SVfit_phiUncTauDown;   //!
   TBranch        *b_SVfit_fitMETRho;   //!
   TBranch        *b_SVfit_fitMETRhoTauUp;   //!
   TBranch        *b_SVfit_fitMETRhoTauDown;   //!
   TBranch        *b_SVfit_fitMETPhi;   //!
   TBranch        *b_SVfit_fitMETPhiTauUp;   //!
   TBranch        *b_SVfit_fitMETPhiTauDown;   //!
   TBranch        *b_isOSCand;   //!
   TBranch        *b_METx;   //!
   TBranch        *b_METy;   //!
   TBranch        *b_uncorrMETx;   //!
   TBranch        *b_uncorrMETy;   //!
   TBranch        *b_MET_cov00;   //!
   TBranch        *b_MET_cov01;   //!
   TBranch        *b_MET_cov10;   //!
   TBranch        *b_MET_cov11;   //!
   TBranch        *b_MET_significance;   //!
   TBranch        *b_mT_Dau1;   //!
   TBranch        *b_mT_Dau2;   //!
   TBranch        *b_PDGIdDaughters;   //!
   TBranch        *b_indexDau1;   //!
   TBranch        *b_indexDau2;   //!
   TBranch        *b_particleType;   //!
   TBranch        *b_discriminator;   //!
   TBranch        *b_daughters_muonID;   //!
   TBranch        *b_daughters_typeOfMuon;   //!
   TBranch        *b_dxy;   //!
   TBranch        *b_dz;   //!
   TBranch        *b_dxy_innerTrack;   //!
   TBranch        *b_dz_innerTrack;   //!
   TBranch        *b_daughters_rel_error_trackpt;   //!
   TBranch        *b_SIP;   //!
   TBranch        *b_daughters_iseleBDT;   //!
   TBranch        *b_daughters_iseleWP80;   //!
   TBranch        *b_daughters_iseleWP90;   //!
   TBranch        *b_daughters_eleMVAnt;   //!
   TBranch        *b_daughters_passConversionVeto;   //!
   TBranch        *b_daughters_eleMissingHits;   //!
   TBranch        *b_daughters_iseleChargeConsistent;   //!
   TBranch        *b_daughters_eleCUTID;   //!
   TBranch        *b_decayMode;   //!
   TBranch        *b_tauID;   //!
   TBranch        *b_combreliso;   //!
   TBranch        *b_daughters_IetaIeta;   //!
   TBranch        *b_daughters_hOverE;   //!
   TBranch        *b_daughters_deltaEtaSuperClusterTrackAtVtx;   //!
   TBranch        *b_daughters_deltaPhiSuperClusterTrackAtVtx;   //!
   TBranch        *b_daughters_IoEmIoP;   //!
   TBranch        *b_daughters_IoEmIoP_ttH;   //!
   TBranch        *b_daughters_SCeta;   //!
   TBranch        *b_daughters_depositR03_tracker;   //!
   TBranch        *b_daughters_depositR03_ecal;   //!
   TBranch        *b_daughters_depositR03_hcal;   //!
   TBranch        *b_daughters_decayModeFindingOldDMs;   //!
   TBranch        *b_againstElectronMVA5category;   //!
   TBranch        *b_againstElectronMVA5raw;   //!
   TBranch        *b_byPileupWeightedIsolationRaw3Hits;   //!
   TBranch        *b_footprintCorrection;   //!
   TBranch        *b_neutralIsoPtSumWeight;   //!
   TBranch        *b_photonPtSumOutsideSignalCone;   //!
   TBranch        *b_daughters_decayModeFindingNewDMs;   //!
   TBranch        *b_daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits;   //!
   TBranch        *b_daughters_byIsolationMVA3oldDMwoLTraw;   //!
   TBranch        *b_daughters_byIsolationMVA3oldDMwLTraw;   //!
   TBranch        *b_daughters_byIsolationMVA3newDMwoLTraw;   //!
   TBranch        *b_daughters_byIsolationMVA3newDMwLTraw;   //!
   TBranch        *b_daughters_chargedIsoPtSum;   //!
   TBranch        *b_daughters_neutralIsoPtSum;   //!
   TBranch        *b_daughters_puCorrPtSum;   //!
   TBranch        *b_daughters_numChargedParticlesSignalCone;   //!
   TBranch        *b_daughters_numNeutralHadronsSignalCone;   //!
   TBranch        *b_daughters_numPhotonsSignalCone;   //!
   TBranch        *b_daughters_daughters_numParticlesSignalCone;   //!
   TBranch        *b_daughters_numChargedParticlesIsoCone;   //!
   TBranch        *b_daughters_numNeutralHadronsIsoCone;   //!
   TBranch        *b_daughters_numPhotonsIsoCone;   //!
   TBranch        *b_daughters_numParticlesIsoCone;   //!
   TBranch        *b_daughters_leadChargedParticlePt;   //!
   TBranch        *b_daughters_trackRefPt;   //!
   TBranch        *b_daughters_isLastTriggerObjectforPath;   //!
   TBranch        *b_daughters_trgMatched;   //!
   TBranch        *b_daughters_isTriggerObjectforPath;   //!
   TBranch        *b_daughters_FilterFired;   //!
   TBranch        *b_daughters_isGoodTriggerType;   //!
   TBranch        *b_daughters_L3FilterFired;   //!
   TBranch        *b_daughters_L3FilterFiredLast;   //!
   TBranch        *b_daughters_HLTpt;   //!
   TBranch        *b_daughters_isL1IsoTau28Matched;   //!
   TBranch        *b_daughters_jetNDauChargedMVASel;   //!
   TBranch        *b_daughters_miniRelIsoCharged;   //!
   TBranch        *b_daughters_miniRelIsoNeutral;   //!
   TBranch        *b_daughters_jetPtRel;   //!
   TBranch        *b_daughters_jetPtRatio;   //!
   TBranch        *b_daughters_jetBTagCSV;   //!
   TBranch        *b_daughters_lepMVA_mvaId;   //!
   TBranch        *b_JetsNumber;   //!
   TBranch        *b_jets_px;   //!
   TBranch        *b_jets_py;   //!
   TBranch        *b_jets_pz;   //!
   TBranch        *b_jets_e;   //!
   TBranch        *b_jets_rawPt;   //!
   TBranch        *b_jets_area;   //!
   TBranch        *b_jets_mT;   //!
   TBranch        *b_jets_Flavour;   //!
   TBranch        *b_jets_HadronFlavour;   //!
   TBranch        *b_jets_genjetIndex;   //!
   TBranch        *b_jets_PUJetID;   //!
   TBranch        *b_jets_PUJetIDupdated;   //!
   TBranch        *b_jets_vtxPt;   //!
   TBranch        *b_jets_vtxMass;   //!
   TBranch        *b_jets_vtx3dL;   //!
   TBranch        *b_jets_vtxNtrk;   //!
   TBranch        *b_jets_vtx3deL;   //!
   TBranch        *b_jets_leadTrackPt;   //!
   TBranch        *b_jets_leptonPtRel;   //!
   TBranch        *b_jets_leptonPt;   //!
   TBranch        *b_jets_leptonDeltaR;   //!
   TBranch        *b_jets_chEmEF;   //!
   TBranch        *b_jets_chHEF;   //!
   TBranch        *b_jets_nEmEF;   //!
   TBranch        *b_jets_nHEF;   //!
   TBranch        *b_jets_chMult;   //!
   TBranch        *b_jets_jecUnc;   //!
   TBranch        *b_bDiscriminator;   //!
   TBranch        *b_bCSVscore;   //!
   TBranch        *b_pfCombinedMVAV2BJetTags;   //!
   TBranch        *b_PFjetID;   //!
   TBranch        *b_jetRawf;   //!
   TBranch        *b_ak8jets_px;   //!
   TBranch        *b_ak8jets_py;   //!
   TBranch        *b_ak8jets_pz;   //!
   TBranch        *b_ak8jets_e;   //!
   TBranch        *b_ak8jets_SoftDropMass;   //!
   TBranch        *b_ak8jets_PrunedMass;   //!
   TBranch        *b_ak8jets_TrimmedMass;   //!
   TBranch        *b_ak8jets_FilteredMass;   //!
   TBranch        *b_ak8jets_tau1;   //!
   TBranch        *b_ak8jets_tau2;   //!
   TBranch        *b_ak8jets_tau3;   //!
   TBranch        *b_ak8jets_CSV;   //!
   TBranch        *b_ak8jets_nsubjets;   //!
   TBranch        *b_subjets_px;   //!
   TBranch        *b_subjets_py;   //!
   TBranch        *b_subjets_pz;   //!
   TBranch        *b_subjets_e;   //!
   TBranch        *b_subjets_CSV;   //!
   TBranch        *b_subjets_ak8MotherIdx;   //!

  
     mothers_px = 0;
   mothers_py = 0;
   mothers_pz = 0;
   mothers_e = 0;
   daughters_px = 0;
   daughters_py = 0;
   daughters_pz = 0;
   daughters_e = 0;
   daughters_charge = 0;
   daughters_TauUpExists = 0;
   daughters_px_TauUp = 0;
   daughters_py_TauUp = 0;
   daughters_pz_TauUp = 0;
   daughters_e_TauUp = 0;
   daughters_TauDownExists = 0;
   daughters_px_TauDown = 0;
   daughters_py_TauDown = 0;
   daughters_pz_TauDown = 0;
   daughters_e_TauDown = 0;
   daughters_genindex = 0;
   genpart_px = 0;
   genpart_py = 0;
   genpart_pz = 0;
   genpart_e = 0;
   genpart_pdg = 0;
   genpart_status = 0;
   genpart_HMothInd = 0;
   genpart_MSSMHMothInd = 0;
   genpart_TopMothInd = 0;
   genpart_TauMothInd = 0;
   genpart_ZMothInd = 0;
   genpart_WMothInd = 0;
   genpart_bMothInd = 0;
   genpart_HZDecayMode = 0;
   genpart_TopDecayMode = 0;
   genpart_WDecayMode = 0;
   genpart_TauGenDecayMode = 0;
   genpart_flags = 0;
   genjet_px = 0;
   genjet_py = 0;
   genjet_pz = 0;
   genjet_e = 0;
   genjet_partonFlavour = 0;
   genjet_hadronFlavour = 0;
   SVfitMass = 0;
   SVfitMassTauUp = 0;
   SVfitMassTauDown = 0;
   SVfitTransverseMass = 0;
   SVfitTransverseMassTauUp = 0;
   SVfitTransverseMassTauDown = 0;
   SVfit_pt = 0;
   SVfit_ptTauUp = 0;
   SVfit_ptTauDown = 0;
   SVfit_ptUnc = 0;
   SVfit_ptUncTauUp = 0;
   SVfit_ptUncTauDown = 0;
   SVfit_eta = 0;
   SVfit_etaTauUp = 0;
   SVfit_etaTauDown = 0;
   SVfit_etaUnc = 0;
   SVfit_etaUncTauUp = 0;
   SVfit_etaUncTauDown = 0;
   SVfit_phi = 0;
   SVfit_phiTauUp = 0;
   SVfit_phiTauDown = 0;
   SVfit_phiUnc = 0;
   SVfit_phiUncTauUp = 0;
   SVfit_phiUncTauDown = 0;
   SVfit_fitMETRho = 0;
   SVfit_fitMETRhoTauUp = 0;
   SVfit_fitMETRhoTauDown = 0;
   SVfit_fitMETPhi = 0;
   SVfit_fitMETPhiTauUp = 0;
   SVfit_fitMETPhiTauDown = 0;
   isOSCand = 0;
   METx = 0;
   METy = 0;
   uncorrMETx = 0;
   uncorrMETy = 0;
   MET_cov00 = 0;
   MET_cov01 = 0;
   MET_cov10 = 0;
   MET_cov11 = 0;
   MET_significance = 0;
   mT_Dau1 = 0;
   mT_Dau2 = 0;
   PDGIdDaughters = 0;
   indexDau1 = 0;
   indexDau2 = 0;
   particleType = 0;
   discriminator = 0;
   daughters_muonID = 0;
   daughters_typeOfMuon = 0;
   dxy = 0;
   dz = 0;
   dxy_innerTrack = 0;
   dz_innerTrack = 0;
   daughters_rel_error_trackpt = 0;
   SIP = 0;
   daughters_iseleBDT = 0;
   daughters_iseleWP80 = 0;
   daughters_iseleWP90 = 0;
   daughters_eleMVAnt = 0;
   daughters_passConversionVeto = 0;
   daughters_eleMissingHits = 0;
   daughters_iseleChargeConsistent = 0;
   daughters_eleCUTID = 0;
   decayMode = 0;
   tauID = 0;
   combreliso = 0;
   daughters_IetaIeta = 0;
   daughters_hOverE = 0;
   daughters_deltaEtaSuperClusterTrackAtVtx = 0;
   daughters_deltaPhiSuperClusterTrackAtVtx = 0;
   daughters_IoEmIoP = 0;
   daughters_IoEmIoP_ttH = 0;
   daughters_SCeta = 0;
   daughters_depositR03_tracker = 0;
   daughters_depositR03_ecal = 0;
   daughters_depositR03_hcal = 0;
   daughters_decayModeFindingOldDMs = 0;
   againstElectronMVA5category = 0;
   againstElectronMVA5raw = 0;
   byPileupWeightedIsolationRaw3Hits = 0;
   footprintCorrection = 0;
   neutralIsoPtSumWeight = 0;
   photonPtSumOutsideSignalCone = 0;
   daughters_decayModeFindingNewDMs = 0;
   daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits = 0;
   daughters_byIsolationMVA3oldDMwoLTraw = 0;
   daughters_byIsolationMVA3oldDMwLTraw = 0;
   daughters_byIsolationMVA3newDMwoLTraw = 0;
   daughters_byIsolationMVA3newDMwLTraw = 0;
   daughters_chargedIsoPtSum = 0;
   daughters_neutralIsoPtSum = 0;
   daughters_puCorrPtSum = 0;
   daughters_numChargedParticlesSignalCone = 0;
   daughters_numNeutralHadronsSignalCone = 0;
   daughters_numPhotonsSignalCone = 0;
   daughters_daughters_numParticlesSignalCone = 0;
   daughters_numChargedParticlesIsoCone = 0;
   daughters_numNeutralHadronsIsoCone = 0;
   daughters_numPhotonsIsoCone = 0;
   daughters_numParticlesIsoCone = 0;
   daughters_leadChargedParticlePt = 0;
   daughters_trackRefPt = 0;
   daughters_isLastTriggerObjectforPath = 0;
   daughters_trgMatched = 0;
   daughters_isTriggerObjectforPath = 0;
   daughters_FilterFired = 0;
   daughters_isGoodTriggerType = 0;
   daughters_L3FilterFired = 0;
   daughters_L3FilterFiredLast = 0;
   daughters_HLTpt = 0;
   daughters_isL1IsoTau28Matched = 0;
   daughters_jetNDauChargedMVASel = 0;
   daughters_miniRelIsoCharged = 0;
   daughters_miniRelIsoNeutral = 0;
   daughters_jetPtRel = 0;
   daughters_jetPtRatio = 0;
   daughters_jetBTagCSV = 0;
   daughters_lepMVA_mvaId = 0;
   jets_px = 0;
   jets_py = 0;
   jets_pz = 0;
   jets_e = 0;
   jets_rawPt = 0;
   jets_area = 0;
   jets_mT = 0;
   jets_Flavour = 0;
   jets_HadronFlavour = 0;
   jets_genjetIndex = 0;
   jets_PUJetID = 0;
   jets_PUJetIDupdated = 0;
   jets_vtxPt = 0;
   jets_vtxMass = 0;
   jets_vtx3dL = 0;
   jets_vtxNtrk = 0;
   jets_vtx3deL = 0;
   jets_leadTrackPt = 0;
   jets_leptonPtRel = 0;
   jets_leptonPt = 0;
   jets_leptonDeltaR = 0;
   jets_chEmEF = 0;
   jets_chHEF = 0;
   jets_nEmEF = 0;
   jets_nHEF = 0;
   jets_chMult = 0;
   jets_jecUnc = 0;
   bDiscriminator = 0;
   bCSVscore = 0;
   pfCombinedMVAV2BJetTags = 0;
   PFjetID = 0;
   jetRawf = 0;
   ak8jets_px = 0;
   ak8jets_py = 0;
   ak8jets_pz = 0;
   ak8jets_e = 0;
   ak8jets_SoftDropMass = 0;
   ak8jets_PrunedMass = 0;
   ak8jets_TrimmedMass = 0;
   ak8jets_FilteredMass = 0;
   ak8jets_tau1 = 0;
   ak8jets_tau2 = 0;
   ak8jets_tau3 = 0;
   ak8jets_CSV = 0;
   ak8jets_nsubjets = 0;
   subjets_px = 0;
   subjets_py = 0;
   subjets_pz = 0;
   subjets_e = 0;
   subjets_CSV = 0;
   subjets_ak8MotherIdx = 0;
   // Set branch addresses and branch pointers
   tree->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   tree->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   tree->SetBranchAddress("lumi", &lumi, &b_lumi);
   tree->SetBranchAddress("triggerbit", &triggerbit, &b_triggerbit);
   tree->SetBranchAddress("metfilterbit", &metfilterbit, &b_metfilterbit);
   tree->SetBranchAddress("met", &met, &b_met);
   tree->SetBranchAddress("metphi", &metphi, &b_metphi);
   tree->SetBranchAddress("PUPPImet", &PUPPImet, &b_PUPPImet);
   tree->SetBranchAddress("PUPPImetphi", &PUPPImetphi, &b_PUPPImetphi);
   tree->SetBranchAddress("PFMETCov00", &PFMETCov00, &b_PFMETCov00);
   tree->SetBranchAddress("PFMETCov01", &PFMETCov01, &b_PFMETCov01);
   tree->SetBranchAddress("PFMETCov10", &PFMETCov10, &b_PFMETCov10);
   tree->SetBranchAddress("PFMETCov11", &PFMETCov11, &b_PFMETCov11);
   tree->SetBranchAddress("PFMETsignif", &PFMETsignif, &b_PFMETsignif);
   tree->SetBranchAddress("npv", &npv, &b_npv);
   tree->SetBranchAddress("npu", &npu, &b_npu);
   tree->SetBranchAddress("PUReweight", &PUReweight, &b_PUReweight);
   tree->SetBranchAddress("rho", &rho, &b_rho);
   tree->SetBranchAddress("mothers_px", &mothers_px, &b_mothers_px);
   tree->SetBranchAddress("mothers_py", &mothers_py, &b_mothers_py);
   tree->SetBranchAddress("mothers_pz", &mothers_pz, &b_mothers_pz);
   tree->SetBranchAddress("mothers_e", &mothers_e, &b_mothers_e);
   tree->SetBranchAddress("daughters_px", &daughters_px, &b_daughters_px);
   tree->SetBranchAddress("daughters_py", &daughters_py, &b_daughters_py);
   tree->SetBranchAddress("daughters_pz", &daughters_pz, &b_daughters_pz);
   tree->SetBranchAddress("daughters_e", &daughters_e, &b_daughters_e);
   tree->SetBranchAddress("daughters_charge", &daughters_charge, &b_daughters_charge);
   tree->SetBranchAddress("daughters_TauUpExists", &daughters_TauUpExists, &b_daughters_TauUpExists);
   tree->SetBranchAddress("daughters_px_TauUp", &daughters_px_TauUp, &b_daughters_px_TauUp);
   tree->SetBranchAddress("daughters_py_TauUp", &daughters_py_TauUp, &b_daughters_py_TauUp);
   tree->SetBranchAddress("daughters_pz_TauUp", &daughters_pz_TauUp, &b_daughters_pz_TauUp);
   tree->SetBranchAddress("daughters_e_TauUp", &daughters_e_TauUp, &b_daughters_e_TauUp);
   tree->SetBranchAddress("daughters_TauDownExists", &daughters_TauDownExists, &b_daughters_TauDownExists);
   tree->SetBranchAddress("daughters_px_TauDown", &daughters_px_TauDown, &b_daughters_px_TauDown);
   tree->SetBranchAddress("daughters_py_TauDown", &daughters_py_TauDown, &b_daughters_py_TauDown);
   tree->SetBranchAddress("daughters_pz_TauDown", &daughters_pz_TauDown, &b_daughters_pz_TauDown);
   tree->SetBranchAddress("daughters_e_TauDown", &daughters_e_TauDown, &b_daughters_e_TauDown);
   tree->SetBranchAddress("PUNumInteractions", &PUNumInteractions, &b_PUNumInteractions);
   tree->SetBranchAddress("daughters_genindex", &daughters_genindex, &b_daughters_genindex);
   tree->SetBranchAddress("MC_weight", &MC_weight, &b_MC_weight);
   tree->SetBranchAddress("lheHt", &lheHt, &b_lheHt);
   tree->SetBranchAddress("lheNOutPartons", &lheNOutPartons, &b_lheNOutPartons);
   tree->SetBranchAddress("lheNOutB", &lheNOutB, &b_lheNOutB);
   tree->SetBranchAddress("aMCatNLOweight", &aMCatNLOweight, &b_aMCatNLOweight);
   tree->SetBranchAddress("genpart_px", &genpart_px, &b_genpart_px);
   tree->SetBranchAddress("genpart_py", &genpart_py, &b_genpart_py);
   tree->SetBranchAddress("genpart_pz", &genpart_pz, &b_genpart_pz);
   tree->SetBranchAddress("genpart_e", &genpart_e, &b_genpart_e);
   tree->SetBranchAddress("genpart_pdg", &genpart_pdg, &b_genpart_pdg);
   tree->SetBranchAddress("genpart_status", &genpart_status, &b_genpart_status);
   tree->SetBranchAddress("genpart_HMothInd", &genpart_HMothInd, &b_genpart_HMothInd);
   tree->SetBranchAddress("genpart_MSSMHMothInd", &genpart_MSSMHMothInd, &b_genpart_MSSMHMothInd);
   tree->SetBranchAddress("genpart_TopMothInd", &genpart_TopMothInd, &b_genpart_TopMothInd);
   tree->SetBranchAddress("genpart_TauMothInd", &genpart_TauMothInd, &b_genpart_TauMothInd);
   tree->SetBranchAddress("genpart_ZMothInd", &genpart_ZMothInd, &b_genpart_ZMothInd);
   tree->SetBranchAddress("genpart_WMothInd", &genpart_WMothInd, &b_genpart_WMothInd);
   tree->SetBranchAddress("genpart_bMothInd", &genpart_bMothInd, &b_genpart_bMothInd);
   tree->SetBranchAddress("genpart_HZDecayMode", &genpart_HZDecayMode, &b_genpart_HZDecayMode);
   tree->SetBranchAddress("genpart_TopDecayMode", &genpart_TopDecayMode, &b_genpart_TopDecayMode);
   tree->SetBranchAddress("genpart_WDecayMode", &genpart_WDecayMode, &b_genpart_WDecayMode);
   tree->SetBranchAddress("genpart_TauGenDecayMode", &genpart_TauGenDecayMode, &b_genpart_TauGenDecayMode);
   tree->SetBranchAddress("genpart_flags", &genpart_flags, &b_genpart_flags);
   tree->SetBranchAddress("genjet_px", &genjet_px, &b_genjet_px);
   tree->SetBranchAddress("genjet_py", &genjet_py, &b_genjet_py);
   tree->SetBranchAddress("genjet_pz", &genjet_pz, &b_genjet_pz);
   tree->SetBranchAddress("genjet_e", &genjet_e, &b_genjet_e);
   tree->SetBranchAddress("genjet_partonFlavour", &genjet_partonFlavour, &b_genjet_partonFlavour);
   tree->SetBranchAddress("genjet_hadronFlavour", &genjet_hadronFlavour, &b_genjet_hadronFlavour);
   tree->SetBranchAddress("NUP", &NUP, &b_NUP);
   tree->SetBranchAddress("SVfitMass", &SVfitMass, &b_SVfitMass);
   tree->SetBranchAddress("SVfitMassTauUp", &SVfitMassTauUp, &b_SVfitMassTauUp);
   tree->SetBranchAddress("SVfitMassTauDown", &SVfitMassTauDown, &b_SVfitMassTauDown);
   tree->SetBranchAddress("SVfitTransverseMass", &SVfitTransverseMass, &b_SVfitTransverseMass);
   tree->SetBranchAddress("SVfitTransverseMassTauUp", &SVfitTransverseMassTauUp, &b_SVfitTransverseMassTauUp);
   tree->SetBranchAddress("SVfitTransverseMassTauDown", &SVfitTransverseMassTauDown, &b_SVfitTransverseMassTauDown);
   tree->SetBranchAddress("SVfit_pt", &SVfit_pt, &b_SVfit_pt);
   tree->SetBranchAddress("SVfit_ptTauUp", &SVfit_ptTauUp, &b_SVfit_ptTauUp);
   tree->SetBranchAddress("SVfit_ptTauDown", &SVfit_ptTauDown, &b_SVfit_ptTauDown);
   tree->SetBranchAddress("SVfit_ptUnc", &SVfit_ptUnc, &b_SVfit_ptUnc);
   tree->SetBranchAddress("SVfit_ptUncTauUp", &SVfit_ptUncTauUp, &b_SVfit_ptUncTauUp);
   tree->SetBranchAddress("SVfit_ptUncTauDown", &SVfit_ptUncTauDown, &b_SVfit_ptUncTauDown);
   tree->SetBranchAddress("SVfit_eta", &SVfit_eta, &b_SVfit_eta);
   tree->SetBranchAddress("SVfit_etaTauUp", &SVfit_etaTauUp, &b_SVfit_etaTauUp);
   tree->SetBranchAddress("SVfit_etaTauDown", &SVfit_etaTauDown, &b_SVfit_etaTauDown);
   tree->SetBranchAddress("SVfit_etaUnc", &SVfit_etaUnc, &b_SVfit_etaUnc);
   tree->SetBranchAddress("SVfit_etaUncTauUp", &SVfit_etaUncTauUp, &b_SVfit_etaUncTauUp);
   tree->SetBranchAddress("SVfit_etaUncTauDown", &SVfit_etaUncTauDown, &b_SVfit_etaUncTauDown);
   tree->SetBranchAddress("SVfit_phi", &SVfit_phi, &b_SVfit_phi);
   tree->SetBranchAddress("SVfit_phiTauUp", &SVfit_phiTauUp, &b_SVfit_phiTauUp);
   tree->SetBranchAddress("SVfit_phiTauDown", &SVfit_phiTauDown, &b_SVfit_phiTauDown);
   tree->SetBranchAddress("SVfit_phiUnc", &SVfit_phiUnc, &b_SVfit_phiUnc);
   tree->SetBranchAddress("SVfit_phiUncTauUp", &SVfit_phiUncTauUp, &b_SVfit_phiUncTauUp);
   tree->SetBranchAddress("SVfit_phiUncTauDown", &SVfit_phiUncTauDown, &b_SVfit_phiUncTauDown);
   tree->SetBranchAddress("SVfit_fitMETRho", &SVfit_fitMETRho, &b_SVfit_fitMETRho);
   tree->SetBranchAddress("SVfit_fitMETRhoTauUp", &SVfit_fitMETRhoTauUp, &b_SVfit_fitMETRhoTauUp);
   tree->SetBranchAddress("SVfit_fitMETRhoTauDown", &SVfit_fitMETRhoTauDown, &b_SVfit_fitMETRhoTauDown);
   tree->SetBranchAddress("SVfit_fitMETPhi", &SVfit_fitMETPhi, &b_SVfit_fitMETPhi);
   tree->SetBranchAddress("SVfit_fitMETPhiTauUp", &SVfit_fitMETPhiTauUp, &b_SVfit_fitMETPhiTauUp);
   tree->SetBranchAddress("SVfit_fitMETPhiTauDown", &SVfit_fitMETPhiTauDown, &b_SVfit_fitMETPhiTauDown);
   tree->SetBranchAddress("isOSCand", &isOSCand, &b_isOSCand);
   tree->SetBranchAddress("METx", &METx, &b_METx);
   tree->SetBranchAddress("METy", &METy, &b_METy);
   tree->SetBranchAddress("uncorrMETx", &uncorrMETx, &b_uncorrMETx);
   tree->SetBranchAddress("uncorrMETy", &uncorrMETy, &b_uncorrMETy);
   tree->SetBranchAddress("MET_cov00", &MET_cov00, &b_MET_cov00);
   tree->SetBranchAddress("MET_cov01", &MET_cov01, &b_MET_cov01);
   tree->SetBranchAddress("MET_cov10", &MET_cov10, &b_MET_cov10);
   tree->SetBranchAddress("MET_cov11", &MET_cov11, &b_MET_cov11);
   tree->SetBranchAddress("MET_significance", &MET_significance, &b_MET_significance);
   tree->SetBranchAddress("mT_Dau1", &mT_Dau1, &b_mT_Dau1);
   tree->SetBranchAddress("mT_Dau2", &mT_Dau2, &b_mT_Dau2);
   tree->SetBranchAddress("PDGIdDaughters", &PDGIdDaughters, &b_PDGIdDaughters);
   tree->SetBranchAddress("indexDau1", &indexDau1, &b_indexDau1);
   tree->SetBranchAddress("indexDau2", &indexDau2, &b_indexDau2);
   tree->SetBranchAddress("particleType", &particleType, &b_particleType);
   tree->SetBranchAddress("discriminator", &discriminator, &b_discriminator);
   tree->SetBranchAddress("daughters_muonID", &daughters_muonID, &b_daughters_muonID);
   tree->SetBranchAddress("daughters_typeOfMuon", &daughters_typeOfMuon, &b_daughters_typeOfMuon);
   tree->SetBranchAddress("dxy", &dxy, &b_dxy);
   tree->SetBranchAddress("dz", &dz, &b_dz);
   tree->SetBranchAddress("dxy_innerTrack", &dxy_innerTrack, &b_dxy_innerTrack);
   tree->SetBranchAddress("dz_innerTrack", &dz_innerTrack, &b_dz_innerTrack);
   tree->SetBranchAddress("daughters_rel_error_trackpt", &daughters_rel_error_trackpt, &b_daughters_rel_error_trackpt);
   tree->SetBranchAddress("SIP", &SIP, &b_SIP);
   tree->SetBranchAddress("daughters_iseleBDT", &daughters_iseleBDT, &b_daughters_iseleBDT);
   tree->SetBranchAddress("daughters_iseleWP80", &daughters_iseleWP80, &b_daughters_iseleWP80);
   tree->SetBranchAddress("daughters_iseleWP90", &daughters_iseleWP90, &b_daughters_iseleWP90);
   tree->SetBranchAddress("daughters_eleMVAnt", &daughters_eleMVAnt, &b_daughters_eleMVAnt);
   tree->SetBranchAddress("daughters_passConversionVeto", &daughters_passConversionVeto, &b_daughters_passConversionVeto);
   tree->SetBranchAddress("daughters_eleMissingHits", &daughters_eleMissingHits, &b_daughters_eleMissingHits);
   tree->SetBranchAddress("daughters_iseleChargeConsistent", &daughters_iseleChargeConsistent, &b_daughters_iseleChargeConsistent);
   tree->SetBranchAddress("daughters_eleCUTID", &daughters_eleCUTID, &b_daughters_eleCUTID);
   tree->SetBranchAddress("decayMode", &decayMode, &b_decayMode);
   tree->SetBranchAddress("tauID", &tauID, &b_tauID);
   tree->SetBranchAddress("combreliso", &combreliso, &b_combreliso);
   tree->SetBranchAddress("daughters_IetaIeta", &daughters_IetaIeta, &b_daughters_IetaIeta);
   tree->SetBranchAddress("daughters_hOverE", &daughters_hOverE, &b_daughters_hOverE);
   tree->SetBranchAddress("daughters_deltaEtaSuperClusterTrackAtVtx", &daughters_deltaEtaSuperClusterTrackAtVtx, &b_daughters_deltaEtaSuperClusterTrackAtVtx);
   tree->SetBranchAddress("daughters_deltaPhiSuperClusterTrackAtVtx", &daughters_deltaPhiSuperClusterTrackAtVtx, &b_daughters_deltaPhiSuperClusterTrackAtVtx);
   tree->SetBranchAddress("daughters_IoEmIoP", &daughters_IoEmIoP, &b_daughters_IoEmIoP);
   tree->SetBranchAddress("daughters_IoEmIoP_ttH", &daughters_IoEmIoP_ttH, &b_daughters_IoEmIoP_ttH);
   tree->SetBranchAddress("daughters_SCeta", &daughters_SCeta, &b_daughters_SCeta);
   tree->SetBranchAddress("daughters_depositR03_tracker", &daughters_depositR03_tracker, &b_daughters_depositR03_tracker);
   tree->SetBranchAddress("daughters_depositR03_ecal", &daughters_depositR03_ecal, &b_daughters_depositR03_ecal);
   tree->SetBranchAddress("daughters_depositR03_hcal", &daughters_depositR03_hcal, &b_daughters_depositR03_hcal);
   tree->SetBranchAddress("daughters_decayModeFindingOldDMs", &daughters_decayModeFindingOldDMs, &b_daughters_decayModeFindingOldDMs);
   tree->SetBranchAddress("againstElectronMVA5category", &againstElectronMVA5category, &b_againstElectronMVA5category);
   tree->SetBranchAddress("againstElectronMVA5raw", &againstElectronMVA5raw, &b_againstElectronMVA5raw);
   tree->SetBranchAddress("byPileupWeightedIsolationRaw3Hits", &byPileupWeightedIsolationRaw3Hits, &b_byPileupWeightedIsolationRaw3Hits);
   tree->SetBranchAddress("footprintCorrection", &footprintCorrection, &b_footprintCorrection);
   tree->SetBranchAddress("neutralIsoPtSumWeight", &neutralIsoPtSumWeight, &b_neutralIsoPtSumWeight);
   tree->SetBranchAddress("photonPtSumOutsideSignalCone", &photonPtSumOutsideSignalCone, &b_photonPtSumOutsideSignalCone);
   tree->SetBranchAddress("daughters_decayModeFindingNewDMs", &daughters_decayModeFindingNewDMs, &b_daughters_decayModeFindingNewDMs);
   tree->SetBranchAddress("daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits", &daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits, &b_daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits);
   tree->SetBranchAddress("daughters_byIsolationMVA3oldDMwoLTraw", &daughters_byIsolationMVA3oldDMwoLTraw, &b_daughters_byIsolationMVA3oldDMwoLTraw);
   tree->SetBranchAddress("daughters_byIsolationMVA3oldDMwLTraw", &daughters_byIsolationMVA3oldDMwLTraw, &b_daughters_byIsolationMVA3oldDMwLTraw);
   tree->SetBranchAddress("daughters_byIsolationMVA3newDMwoLTraw", &daughters_byIsolationMVA3newDMwoLTraw, &b_daughters_byIsolationMVA3newDMwoLTraw);
   tree->SetBranchAddress("daughters_byIsolationMVA3newDMwLTraw", &daughters_byIsolationMVA3newDMwLTraw, &b_daughters_byIsolationMVA3newDMwLTraw);
   tree->SetBranchAddress("daughters_chargedIsoPtSum", &daughters_chargedIsoPtSum, &b_daughters_chargedIsoPtSum);
   tree->SetBranchAddress("daughters_neutralIsoPtSum", &daughters_neutralIsoPtSum, &b_daughters_neutralIsoPtSum);
   tree->SetBranchAddress("daughters_puCorrPtSum", &daughters_puCorrPtSum, &b_daughters_puCorrPtSum);
   tree->SetBranchAddress("daughters_numChargedParticlesSignalCone", &daughters_numChargedParticlesSignalCone, &b_daughters_numChargedParticlesSignalCone);
   tree->SetBranchAddress("daughters_numNeutralHadronsSignalCone", &daughters_numNeutralHadronsSignalCone, &b_daughters_numNeutralHadronsSignalCone);
   tree->SetBranchAddress("daughters_numPhotonsSignalCone", &daughters_numPhotonsSignalCone, &b_daughters_numPhotonsSignalCone);
   tree->SetBranchAddress("daughters_daughters_numParticlesSignalCone", &daughters_daughters_numParticlesSignalCone, &b_daughters_daughters_numParticlesSignalCone);
   tree->SetBranchAddress("daughters_numChargedParticlesIsoCone", &daughters_numChargedParticlesIsoCone, &b_daughters_numChargedParticlesIsoCone);
   tree->SetBranchAddress("daughters_numNeutralHadronsIsoCone", &daughters_numNeutralHadronsIsoCone, &b_daughters_numNeutralHadronsIsoCone);
   tree->SetBranchAddress("daughters_numPhotonsIsoCone", &daughters_numPhotonsIsoCone, &b_daughters_numPhotonsIsoCone);
   tree->SetBranchAddress("daughters_numParticlesIsoCone", &daughters_numParticlesIsoCone, &b_daughters_numParticlesIsoCone);
   tree->SetBranchAddress("daughters_leadChargedParticlePt", &daughters_leadChargedParticlePt, &b_daughters_leadChargedParticlePt);
   tree->SetBranchAddress("daughters_trackRefPt", &daughters_trackRefPt, &b_daughters_trackRefPt);
   tree->SetBranchAddress("daughters_isLastTriggerObjectforPath", &daughters_isLastTriggerObjectforPath, &b_daughters_isLastTriggerObjectforPath);
   tree->SetBranchAddress("daughters_trgMatched", &daughters_trgMatched, &b_daughters_trgMatched);
   tree->SetBranchAddress("daughters_isTriggerObjectforPath", &daughters_isTriggerObjectforPath, &b_daughters_isTriggerObjectforPath);
   tree->SetBranchAddress("daughters_FilterFired", &daughters_FilterFired, &b_daughters_FilterFired);
   tree->SetBranchAddress("daughters_isGoodTriggerType", &daughters_isGoodTriggerType, &b_daughters_isGoodTriggerType);
   tree->SetBranchAddress("daughters_L3FilterFired", &daughters_L3FilterFired, &b_daughters_L3FilterFired);
   tree->SetBranchAddress("daughters_L3FilterFiredLast", &daughters_L3FilterFiredLast, &b_daughters_L3FilterFiredLast);
   tree->SetBranchAddress("daughters_HLTpt", &daughters_HLTpt, &b_daughters_HLTpt);
   tree->SetBranchAddress("daughters_isL1IsoTau28Matched", &daughters_isL1IsoTau28Matched, &b_daughters_isL1IsoTau28Matched);
   tree->SetBranchAddress("daughters_jetNDauChargedMVASel", &daughters_jetNDauChargedMVASel, &b_daughters_jetNDauChargedMVASel);
   tree->SetBranchAddress("daughters_miniRelIsoCharged", &daughters_miniRelIsoCharged, &b_daughters_miniRelIsoCharged);
   tree->SetBranchAddress("daughters_miniRelIsoNeutral", &daughters_miniRelIsoNeutral, &b_daughters_miniRelIsoNeutral);
   tree->SetBranchAddress("daughters_jetPtRel", &daughters_jetPtRel, &b_daughters_jetPtRel);
   tree->SetBranchAddress("daughters_jetPtRatio", &daughters_jetPtRatio, &b_daughters_jetPtRatio);
   tree->SetBranchAddress("daughters_jetBTagCSV", &daughters_jetBTagCSV, &b_daughters_jetBTagCSV);
   tree->SetBranchAddress("daughters_lepMVA_mvaId", &daughters_lepMVA_mvaId, &b_daughters_lepMVA_mvaId);
   tree->SetBranchAddress("JetsNumber", &JetsNumber, &b_JetsNumber);
   tree->SetBranchAddress("jets_px", &jets_px, &b_jets_px);
   tree->SetBranchAddress("jets_py", &jets_py, &b_jets_py);
   tree->SetBranchAddress("jets_pz", &jets_pz, &b_jets_pz);
   tree->SetBranchAddress("jets_e", &jets_e, &b_jets_e);
   tree->SetBranchAddress("jets_rawPt", &jets_rawPt, &b_jets_rawPt);
   tree->SetBranchAddress("jets_area", &jets_area, &b_jets_area);
   tree->SetBranchAddress("jets_mT", &jets_mT, &b_jets_mT);
   tree->SetBranchAddress("jets_Flavour", &jets_Flavour, &b_jets_Flavour);
   tree->SetBranchAddress("jets_HadronFlavour", &jets_HadronFlavour, &b_jets_HadronFlavour);
   tree->SetBranchAddress("jets_genjetIndex", &jets_genjetIndex, &b_jets_genjetIndex);
   tree->SetBranchAddress("jets_PUJetID", &jets_PUJetID, &b_jets_PUJetID);
   tree->SetBranchAddress("jets_PUJetIDupdated", &jets_PUJetIDupdated, &b_jets_PUJetIDupdated);
   tree->SetBranchAddress("jets_vtxPt", &jets_vtxPt, &b_jets_vtxPt);
   tree->SetBranchAddress("jets_vtxMass", &jets_vtxMass, &b_jets_vtxMass);
   tree->SetBranchAddress("jets_vtx3dL", &jets_vtx3dL, &b_jets_vtx3dL);
   tree->SetBranchAddress("jets_vtxNtrk", &jets_vtxNtrk, &b_jets_vtxNtrk);
   tree->SetBranchAddress("jets_vtx3deL", &jets_vtx3deL, &b_jets_vtx3deL);
   tree->SetBranchAddress("jets_leadTrackPt", &jets_leadTrackPt, &b_jets_leadTrackPt);
   tree->SetBranchAddress("jets_leptonPtRel", &jets_leptonPtRel, &b_jets_leptonPtRel);
   tree->SetBranchAddress("jets_leptonPt", &jets_leptonPt, &b_jets_leptonPt);
   tree->SetBranchAddress("jets_leptonDeltaR", &jets_leptonDeltaR, &b_jets_leptonDeltaR);
   tree->SetBranchAddress("jets_chEmEF", &jets_chEmEF, &b_jets_chEmEF);
   tree->SetBranchAddress("jets_chHEF", &jets_chHEF, &b_jets_chHEF);
   tree->SetBranchAddress("jets_nEmEF", &jets_nEmEF, &b_jets_nEmEF);
   tree->SetBranchAddress("jets_nHEF", &jets_nHEF, &b_jets_nHEF);
   tree->SetBranchAddress("jets_chMult", &jets_chMult, &b_jets_chMult);
   tree->SetBranchAddress("jets_jecUnc", &jets_jecUnc, &b_jets_jecUnc);
   tree->SetBranchAddress("bDiscriminator", &bDiscriminator, &b_bDiscriminator);
   tree->SetBranchAddress("bCSVscore", &bCSVscore, &b_bCSVscore);
   tree->SetBranchAddress("pfCombinedMVAV2BJetTags", &pfCombinedMVAV2BJetTags, &b_pfCombinedMVAV2BJetTags);
   tree->SetBranchAddress("PFjetID", &PFjetID, &b_PFjetID);
   tree->SetBranchAddress("jetRawf", &jetRawf, &b_jetRawf);
   tree->SetBranchAddress("ak8jets_px", &ak8jets_px, &b_ak8jets_px);
   tree->SetBranchAddress("ak8jets_py", &ak8jets_py, &b_ak8jets_py);
   tree->SetBranchAddress("ak8jets_pz", &ak8jets_pz, &b_ak8jets_pz);
   tree->SetBranchAddress("ak8jets_e", &ak8jets_e, &b_ak8jets_e);
   tree->SetBranchAddress("ak8jets_SoftDropMass", &ak8jets_SoftDropMass, &b_ak8jets_SoftDropMass);
   tree->SetBranchAddress("ak8jets_PrunedMass", &ak8jets_PrunedMass, &b_ak8jets_PrunedMass);
   tree->SetBranchAddress("ak8jets_TrimmedMass", &ak8jets_TrimmedMass, &b_ak8jets_TrimmedMass);
   tree->SetBranchAddress("ak8jets_FilteredMass", &ak8jets_FilteredMass, &b_ak8jets_FilteredMass);
   tree->SetBranchAddress("ak8jets_tau1", &ak8jets_tau1, &b_ak8jets_tau1);
   tree->SetBranchAddress("ak8jets_tau2", &ak8jets_tau2, &b_ak8jets_tau2);
   tree->SetBranchAddress("ak8jets_tau3", &ak8jets_tau3, &b_ak8jets_tau3);
   tree->SetBranchAddress("ak8jets_CSV", &ak8jets_CSV, &b_ak8jets_CSV);
   tree->SetBranchAddress("ak8jets_nsubjets", &ak8jets_nsubjets, &b_ak8jets_nsubjets);
   tree->SetBranchAddress("subjets_px", &subjets_px, &b_subjets_px);
   tree->SetBranchAddress("subjets_py", &subjets_py, &b_subjets_py);
   tree->SetBranchAddress("subjets_pz", &subjets_pz, &b_subjets_pz);
   tree->SetBranchAddress("subjets_e", &subjets_e, &b_subjets_e);
   tree->SetBranchAddress("subjets_CSV", &subjets_CSV, &b_subjets_CSV);
   tree->SetBranchAddress("subjets_ak8MotherIdx", &subjets_ak8MotherIdx, &b_subjets_ak8MotherIdx);

  

  
  for(int i=0; i<nentries; i++){
    if (i%10000 == 0){
      std::cout << ">>> Event # " << i << " / " << nentries << " entries" << std::endl; 
    } 
    tree->GetEntry(i);
    tree_new->Fill();
  }
  f_new->cd();
  tree_new->Write();
  f_new->Close();
  return;
}

