//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jan 17 15:33:34 2017 by ROOT version 6.02/05
// from TTree HTauTauTree/small tree for HH analysis
// found on file: /data_CMS/cms/cadamuro/test_submit_to_tier3/Skims2017_10Gen/SKIM_TT_fullyHad/output_0.root
//////////////////////////////////////////////////////////

#ifndef newClass_h
#define newClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"
#include "vector"

class newClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         MC_weight;
   Float_t         PUReweight;
   Float_t         bTagweightL;
   Float_t         bTagweightM;
   Float_t         bTagweightT;
   Float_t         TTtopPtreweight;
   Float_t         TTtopPtreweight_up;
   Float_t         TTtopPtreweight_down;
   Float_t         turnOnreweight;
   Float_t         turnOnreweight_tauup;
   Float_t         turnOnreweight_taudown;
   Float_t         trigSF;
   Float_t         IdAndIsoSF;
   Float_t         DYscale_LL;
   Float_t         DYscale_MM;
   Int_t           nBhadrons;
   Int_t           lheNOutPartons;
   Int_t           lheNOutB;
   Int_t           EventNumber;
   Int_t           RunNumber;
   Int_t           isBoosted;
   Int_t           genDecMode1;
   Int_t           genDecMode2;
   Int_t           npv;
   Float_t         npu;
   Int_t           lumi;
   Long64_t        triggerbit;
   Int_t           L3filter1;
   Int_t           L3filterlast1;
   Int_t           L3filter2;
   Int_t           L3filterlast2;
   Float_t         rho;
   Int_t           pairType;
   Int_t           isMC;
   Int_t           isOS;
   Float_t         met_phi;
   Float_t         met_et;
   Float_t         met_et_corr;
   Float_t         met_cov00;
   Float_t         met_cov01;
   Float_t         met_cov10;
   Float_t         met_cov11;
   Float_t         mT1;
   Float_t         mT2;
   Float_t         dau1_iso;
   Int_t           dau1_MVAiso;
   Int_t           dau1_CUTiso;
   Int_t           dau1_antiele;
   Int_t           dau1_antimu;
   Float_t         dau1_photonPtSumOutsideSignalCone;
   Bool_t          dau1_byLooseCombinedIsolationDeltaBetaCorr3Hits;
   Bool_t          dau1_byMediumCombinedIsolationDeltaBetaCorr3Hits;
   Bool_t          dau1_byTightCombinedIsolationDeltaBetaCorr3Hits;
   Float_t         dau1_pt;
   Float_t         dau1_eta;
   Float_t         dau1_phi;
   Float_t         dau1_e;
   Float_t         dau1_flav;
   Float_t         genmatched1_pt;
   Float_t         genmatched1_eta;
   Float_t         genmatched1_phi;
   Float_t         genmatched1_e;
   Float_t         genmatched2_pt;
   Float_t         genmatched2_eta;
   Float_t         genmatched2_phi;
   Float_t         genmatched2_e;
   Bool_t          hasgenmatch1;
   Bool_t          hasgenmatch2;
   Float_t         dau2_iso;
   Int_t           dau2_MVAiso;
   Int_t           dau2_CUTiso;
   Int_t           dau2_antiele;
   Int_t           dau2_antimu;
   Float_t         dau2_photonPtSumOutsideSignalCone;
   Bool_t          dau2_byLooseCombinedIsolationDeltaBetaCorr3Hits;
   Bool_t          dau2_byMediumCombinedIsolationDeltaBetaCorr3Hits;
   Bool_t          dau2_byTightCombinedIsolationDeltaBetaCorr3Hits;
   Float_t         dau2_pt;
   Float_t         dau2_eta;
   Float_t         dau2_phi;
   Float_t         dau2_e;
   Float_t         dau2_flav;
   Float_t         bjet1_pt;
   Float_t         bjet1_eta;
   Float_t         bjet1_phi;
   Float_t         bjet1_e;
   Float_t         bjet1_bID;
   Int_t           bjet1_flav;
   Float_t         bjet1_pt_raw;
   Bool_t          bjet1_hasgenjet;
   Float_t         bjet2_pt;
   Float_t         bjet2_eta;
   Float_t         bjet2_phi;
   Float_t         bjet2_e;
   Float_t         bjet2_bID;
   Int_t           bjet2_flav;
   Float_t         bjet2_pt_raw;
   Bool_t          bjet2_hasgenjet;
   Int_t           nfatjets;
   Float_t         fatjet_pt;
   Float_t         fatjet_eta;
   Float_t         fatjet_phi;
   Float_t         fatjet_e;
   Float_t         fatjet_bID;
   Float_t         fatjet_filteredMass;
   Float_t         fatjet_prunedMass;
   Float_t         fatjet_trimmedMass;
   Float_t         fatjet_softdropMass;
   Float_t         fatjet_tau1;
   Float_t         fatjet_tau2;
   Float_t         fatjet_tau3;
   Int_t           fatjet_nsubjets;
   Float_t         dR_subj1_subj2;
   Float_t         subjetjet1_pt;
   Float_t         subjetjet1_eta;
   Float_t         subjetjet1_phi;
   Float_t         subjetjet1_e;
   Float_t         subjetjet1_bID;
   Float_t         subjetjet2_pt;
   Float_t         subjetjet2_eta;
   Float_t         subjetjet2_phi;
   Float_t         subjetjet2_e;
   Float_t         subjetjet2_bID;
   Float_t         genjet1_pt;
   Float_t         genjet1_eta;
   Float_t         genjet1_phi;
   Float_t         genjet1_e;
   Float_t         genjet2_pt;
   Float_t         genjet2_eta;
   Float_t         genjet2_phi;
   Float_t         genjet2_e;
   Float_t         tauH_pt;
   Float_t         tauH_eta;
   Float_t         tauH_phi;
   Float_t         tauH_e;
   Float_t         tauH_mass;
   Float_t         tauH_SVFIT_mass;
   Float_t         tauH_SVFIT_pt;
   Float_t         tauH_SVFIT_eta;
   Float_t         tauH_SVFIT_phi;
   Float_t         tauH_SVFIT_METphi;
   Float_t         tauH_SVFIT_METrho;
   Float_t         tauH_SVFIT_mass_up;
   Float_t         tauH_SVFIT_mass_down;
   Float_t         bH_pt;
   Float_t         bH_eta;
   Float_t         bH_phi;
   Float_t         bH_e;
   Float_t         bH_mass;
   Float_t         HHsvfit_pt;
   Float_t         HHsvfit_eta;
   Float_t         HHsvfit_phi;
   Float_t         HHsvfit_e;
   Float_t         HHsvfit_mass;
   Float_t         HH_pt;
   Float_t         HH_eta;
   Float_t         HH_phi;
   Float_t         HH_e;
   Float_t         HH_mass;
   Float_t         HH_mass_raw;
   Float_t         HH_mass_raw_tauup;
   Float_t         HH_mass_raw_taudown;
   Float_t         HHKin_mass;
   Float_t         HHKin_chi2;
   Float_t         HH_deltaPhi;
   Float_t         HHsvfit_deltaPhi;
   Float_t         tauHMet_deltaPhi;
   Float_t         tauHsvfitMet_deltaPhi;
   Float_t         bHMet_deltaPhi;
   Float_t         ditau_deltaPhi;
   Float_t         dib_deltaPhi;
   Float_t         ditau_deltaR;
   Float_t         dib_deltaR;
   Float_t         btau_deltaRmin;
   Float_t         btau_deltaRmax;
   Float_t         dau1MET_deltaphi;
   Float_t         dau2MET_deltaphi;
   Float_t         HT20;
   Float_t         HT50;
   Float_t         HT20Full;
   Float_t         jet20centrality;
   vector<float>   *jets_pt;
   vector<float>   *jets_eta;
   vector<float>   *jets_phi;
   vector<float>   *jets_e;
   vector<float>   *jets_btag;
   vector<int>     *jets_flav;
   vector<int>     *jets_isH;
   vector<bool>    *jets_hasgenjet;
   Int_t           njets;
   Int_t           njets20;
   Int_t           njets50;
   Int_t           nbjetscand;
   Int_t           njetsBHadFlav;
   Int_t           njetsCHadFlav;
   vector<float>   *jets_jecUnc;
   Float_t         dau1_jecUnc;
   Float_t         dau2_jecUnc;
   Float_t         bjet1_jecUnc;
   Float_t         bjet2_jecUnc;
   vector<float>   *leps_pt;
   vector<float>   *leps_eta;
   vector<float>   *leps_phi;
   vector<float>   *leps_e;
   vector<int>     *leps_flav;
   Int_t           nleps;
   Float_t         HHkinsvfit_bHmass;
   Float_t         HHkinsvfit_pt;
   Float_t         HHkinsvfit_eta;
   Float_t         HHkinsvfit_phi;
   Float_t         HHkinsvfit_e;
   Float_t         HHkinsvfit_m;
   Float_t         MT2;
   Float_t         bH_mass_raw;
   Float_t         HHKin_mass_raw;
   Float_t         HHKin_mass_raw_tauup;
   Float_t         HHKin_mass_raw_taudown;
   Float_t         HHKin_mass_raw_chi2;
   Int_t           HHKin_mass_raw_convergence;
   Float_t         HHKin_mass_raw_prob;
   Float_t         HHKin_mass_raw_copy;
   Float_t         lheht;
   Float_t         topReweight;
   Float_t         MuTauKine;
   Float_t         ETauKine;
   Float_t         LepTauKine;
   Float_t         BDTResonant;

   // List of branches
   TBranch        *b_MC_weight;   //!
   TBranch        *b_PUReweight;   //!
   TBranch        *b_bTagweightL;   //!
   TBranch        *b_bTagweightM;   //!
   TBranch        *b_bTagweightT;   //!
   TBranch        *b_TTtopPtreweight;   //!
   TBranch        *b_TTtopPtreweight_up;   //!
   TBranch        *b_TTtopPtreweight_down;   //!
   TBranch        *b_turnOnreweight;   //!
   TBranch        *b_turnOnreweight_tauup;   //!
   TBranch        *b_turnOnreweight_taudown;   //!
   TBranch        *b_trigSF;   //!
   TBranch        *b_IdAndIsoSF;   //!
   TBranch        *b_DYscale_LL;   //!
   TBranch        *b_DYscale_MM;   //!
   TBranch        *b_nBhadrons;   //!
   TBranch        *b_lheNOutPartons;   //!
   TBranch        *b_lheNOutB;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_isBoosted;   //!
   TBranch        *b_genDecMode1;   //!
   TBranch        *b_genDecMode2;   //!
   TBranch        *b_npv;   //!
   TBranch        *b_npu;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_triggerbit;   //!
   TBranch        *b_L3filter1;   //!
   TBranch        *b_L3filterlast1;   //!
   TBranch        *b_L3filter2;   //!
   TBranch        *b_L3filterlast2;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_isMC;   //!
   TBranch        *b_isOS;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_met_et;   //!
   TBranch        *b_met_et_corr;   //!
   TBranch        *b_met_cov00;   //!
   TBranch        *b_met_cov01;   //!
   TBranch        *b_met_cov10;   //!
   TBranch        *b_met_cov11;   //!
   TBranch        *b_mT1;   //!
   TBranch        *b_mT2;   //!
   TBranch        *b_dau1_iso;   //!
   TBranch        *b_dau1_MVAiso;   //!
   TBranch        *b_dau1_CUTiso;   //!
   TBranch        *b_dau1_antiele;   //!
   TBranch        *b_dau1_antimu;   //!
   TBranch        *b_dau1_photonPtSumOutsideSignalCone;   //!
   TBranch        *b_dau1_byLooseCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_dau1_byMediumCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_dau1_byTightCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_dau1_pt;   //!
   TBranch        *b_dau1_eta;   //!
   TBranch        *b_dau1_phi;   //!
   TBranch        *b_dau1_e;   //!
   TBranch        *b_dau1_flav;   //!
   TBranch        *b_genmatched1_pt;   //!
   TBranch        *b_genmatched1_eta;   //!
   TBranch        *b_genmatched1_phi;   //!
   TBranch        *b_genmatched1_e;   //!
   TBranch        *b_genmatched2_pt;   //!
   TBranch        *b_genmatched2_eta;   //!
   TBranch        *b_genmatched2_phi;   //!
   TBranch        *b_genmatched2_e;   //!
   TBranch        *b_hasgenmatch1;   //!
   TBranch        *b_hasgenmatch2;   //!
   TBranch        *b_dau2_iso;   //!
   TBranch        *b_dau2_MVAiso;   //!
   TBranch        *b_dau2_CUTiso;   //!
   TBranch        *b_dau2_antiele;   //!
   TBranch        *b_dau2_antimu;   //!
   TBranch        *b_dau2_photonPtSumOutsideSignalCone;   //!
   TBranch        *b_dau2_byLooseCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_dau2_byMediumCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_dau2_byTightCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_dau2_pt;   //!
   TBranch        *b_dau2_eta;   //!
   TBranch        *b_dau2_phi;   //!
   TBranch        *b_dau2_e;   //!
   TBranch        *b_dau2_flav;   //!
   TBranch        *b_bjet1_pt;   //!
   TBranch        *b_bjet1_eta;   //!
   TBranch        *b_bjet1_phi;   //!
   TBranch        *b_bjet1_e;   //!
   TBranch        *b_bjet1_bID;   //!
   TBranch        *b_bjet1_flav;   //!
   TBranch        *b_bjet1_pt_raw;   //!
   TBranch        *b_bjet1_hasgenjet;   //!
   TBranch        *b_bjet2_pt;   //!
   TBranch        *b_bjet2_eta;   //!
   TBranch        *b_bjet2_phi;   //!
   TBranch        *b_bjet2_e;   //!
   TBranch        *b_bjet2m_bID;   //!
   TBranch        *b_bjet2_flav;   //!
   TBranch        *b_bjet2_pt_raw;   //!
   TBranch        *b_bjet2_hasgenjet;   //!
   TBranch        *b_nfatjets;   //!
   TBranch        *b_fatjet_pt;   //!
   TBranch        *b_fatjet_eta;   //!
   TBranch        *b_fatjet_phi;   //!
   TBranch        *b_fatjet_e;   //!
   TBranch        *b_fatjet_bID;   //!
   TBranch        *b_fatjet_filteredMass;   //!
   TBranch        *b_fatjet_prunedMass;   //!
   TBranch        *b_fatjet_trimmedMass;   //!
   TBranch        *b_fatjet_softdropMass;   //!
   TBranch        *b_fatjet_tau1;   //!
   TBranch        *b_fatjet_tau2;   //!
   TBranch        *b_fatjet_tau3;   //!
   TBranch        *b_fatjet_nsubjets;   //!
   TBranch        *b_dR_subj1_subj2;   //!
   TBranch        *b_subjetjet1_pt;   //!
   TBranch        *b_subjetjet1_eta;   //!
   TBranch        *b_subjetjet1_phi;   //!
   TBranch        *b_subjetjet1_e;   //!
   TBranch        *b_subjetjet1_bID;   //!
   TBranch        *b_subjetjet2_pt;   //!
   TBranch        *b_subjetjet2_eta;   //!
   TBranch        *b_subjetjet2_phi;   //!
   TBranch        *b_subjetjet2_e;   //!
   TBranch        *b_subjetjet2_bID;   //!
   TBranch        *b_genjet1_pt;   //!
   TBranch        *b_genjet1_eta;   //!
   TBranch        *b_genjet1_phi;   //!
   TBranch        *b_genjet1_e;   //!
   TBranch        *b_genjet2_pt;   //!
   TBranch        *b_genjet2_eta;   //!
   TBranch        *b_genjet2_phi;   //!
   TBranch        *b_genjet2_e;   //!
   TBranch        *b_tauH_pt;   //!
   TBranch        *b_tauH_eta;   //!
   TBranch        *b_tauH_phi;   //!
   TBranch        *b_tauH_e;   //!
   TBranch        *b_tauH_mass;   //!
   TBranch        *b_tauH_SVFIT_mass;   //!
   TBranch        *b_tauH_SVFIT_pt;   //!
   TBranch        *b_tauH_SVFIT_eta;   //!
   TBranch        *b_tauH_SVFIT_phi;   //!
   TBranch        *b_tauH_SVFIT_METphi;   //!
   TBranch        *b_tauH_SVFIT_METrho;   //!
   TBranch        *b_tauH_SVFIT_mass_up;   //!
   TBranch        *b_tauH_SVFIT_mass_down;   //!
   TBranch        *b_bH_pt;   //!
   TBranch        *b_bH_eta;   //!
   TBranch        *b_bH_phi;   //!
   TBranch        *b_bH_e;   //!
   TBranch        *b_bH_mass;   //!
   TBranch        *b_HHsvfit_pt;   //!
   TBranch        *b_HHsvfit_eta;   //!
   TBranch        *b_HHsvfit_phi;   //!
   TBranch        *b_HHsvfit_e;   //!
   TBranch        *b_HHsvfit_mass;   //!
   TBranch        *b_HH_pt;   //!
   TBranch        *b_HH_eta;   //!
   TBranch        *b_HH_phi;   //!
   TBranch        *b_HH_e;   //!
   TBranch        *b_HH_mass;   //!
   TBranch        *b_HH_mass_raw;   //!
   TBranch        *b_HH_mass_raw_tauup;   //!
   TBranch        *b_HH_mass_raw_taudown;   //!
   TBranch        *b_HHKin_mass;   //!
   TBranch        *b_HHKin_chi2;   //!
   TBranch        *b_HH_deltaPhi;   //!
   TBranch        *b_HHsvfit_deltaPhi;   //!
   TBranch        *b_tauHMet_deltaPhi;   //!
   TBranch        *b_tauHsvfitMet_deltaPhi;   //!
   TBranch        *b_bHMet_deltaPhi;   //!
   TBranch        *b_ditau_deltaPhi;   //!
   TBranch        *b_dib_deltaPhi;   //!
   TBranch        *b_ditau_deltaR;   //!
   TBranch        *b_dib_deltaR;   //!
   TBranch        *b_btau_deltaRmin;   //!
   TBranch        *b_btau_deltaRmax;   //!
   TBranch        *b_dau1MET_deltaphi;   //!
   TBranch        *b_dau2MET_deltaphi;   //!
   TBranch        *b_HT20;   //!
   TBranch        *b_HT50;   //!
   TBranch        *b_HT20Full;   //!
   TBranch        *b_jet20centrality;   //!
   TBranch        *b_jets_pt;   //!
   TBranch        *b_jets_eta;   //!
   TBranch        *b_jets_phi;   //!
   TBranch        *b_jets_e;   //!
   TBranch        *b_jets_btag;   //!
   TBranch        *b_jets_flav;   //!
   TBranch        *b_jets_isH;   //!
   TBranch        *b_jets_hasgenjet;   //!
   TBranch        *b_njets;   //!
   TBranch        *b_njets20;   //!
   TBranch        *b_njets50;   //!
   TBranch        *b_nbjetscand;   //!
   TBranch        *b_njetsBHadFlav;   //!
   TBranch        *b_njetsCHadFlav;   //!
   TBranch        *b_jets_jecUnc;   //!
   TBranch        *b_dau1_jecUnc;   //!
   TBranch        *b_dau2_jecUnc;   //!
   TBranch        *b_bjet1_jecUnc;   //!
   TBranch        *b_bjet2_jecUnc;   //!
   TBranch        *b_leps_pt;   //!
   TBranch        *b_leps_eta;   //!
   TBranch        *b_leps_phi;   //!
   TBranch        *b_leps_e;   //!
   TBranch        *b_leps_flav;   //!
   TBranch        *b_nleps;   //!
   TBranch        *b_HHkinsvfit_bHmass;   //!
   TBranch        *b_HHkinsvfit_pt;   //!
   TBranch        *b_HHkinsvfit_eta;   //!
   TBranch        *b_HHkinsvfit_phi;   //!
   TBranch        *b_HHkinsvfit_e;   //!
   TBranch        *b_HHkinsvfit_m;   //!
   TBranch        *b_MT2;   //!
   TBranch        *b_bH_mass_raw;   //!
   TBranch        *b_HHKin_mass_raw;   //!
   TBranch        *b_HHKin_mass_raw_tauup;   //!
   TBranch        *b_HHKin_mass_raw_taudown;   //!
   TBranch        *b_HHKin_mass_raw_chi2;   //!
   TBranch        *b_HHKin_mass_raw_convergence;   //!
   TBranch        *b_HHKin_mass_raw_prob;   //!
   TBranch        *b_HHKin_mass_raw_copy;   //!
   TBranch        *b_lheht;   //!
   TBranch        *b_topReweight;   //!
   TBranch        *b_MuTauKine;   //!
   TBranch        *b_ETauKine;   //!
   TBranch        *b_LepTauKine;   //!
   TBranch        *b_BDTResonant;   //!

   newClass(TTree *tree=0);
   virtual ~newClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   //   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef newClass_cxx
newClass::newClass(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/data_CMS/cms/cadamuro/test_submit_to_tier3/Skims2017_10Gen/SKIM_TT_fullyHad/output_0.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/data_CMS/cms/cadamuro/test_submit_to_tier3/Skims2017_10Gen/SKIM_TT_fullyHad/output_0.root");
      }
      f->GetObject("HTauTauTree",tree);

   }
   Init(tree);
}

newClass::~newClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t newClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t newClass::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void newClass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jets_pt = 0;
   jets_eta = 0;
   jets_phi = 0;
   jets_e = 0;
   jets_btag = 0;
   jets_flav = 0;
   jets_isH = 0;
   jets_hasgenjet = 0;
   jets_jecUnc = 0;
   leps_pt = 0;
   leps_eta = 0;
   leps_phi = 0;
   leps_e = 0;
   leps_flav = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("MC_weight", &MC_weight, &b_MC_weight);
   fChain->SetBranchAddress("PUReweight", &PUReweight, &b_PUReweight);
   fChain->SetBranchAddress("bTagweightL", &bTagweightL, &b_bTagweightL);
   fChain->SetBranchAddress("bTagweightM", &bTagweightM, &b_bTagweightM);
   fChain->SetBranchAddress("bTagweightT", &bTagweightT, &b_bTagweightT);
   fChain->SetBranchAddress("TTtopPtreweight", &TTtopPtreweight, &b_TTtopPtreweight);
   fChain->SetBranchAddress("TTtopPtreweight_up", &TTtopPtreweight_up, &b_TTtopPtreweight_up);
   fChain->SetBranchAddress("TTtopPtreweight_down", &TTtopPtreweight_down, &b_TTtopPtreweight_down);
   fChain->SetBranchAddress("turnOnreweight", &turnOnreweight, &b_turnOnreweight);
   fChain->SetBranchAddress("turnOnreweight_tauup", &turnOnreweight_tauup, &b_turnOnreweight_tauup);
   fChain->SetBranchAddress("turnOnreweight_taudown", &turnOnreweight_taudown, &b_turnOnreweight_taudown);
   fChain->SetBranchAddress("trigSF", &trigSF, &b_trigSF);
   fChain->SetBranchAddress("IdAndIsoSF", &IdAndIsoSF, &b_IdAndIsoSF);
   fChain->SetBranchAddress("DYscale_LL", &DYscale_LL, &b_DYscale_LL);
   fChain->SetBranchAddress("DYscale_MM", &DYscale_MM, &b_DYscale_MM);
   fChain->SetBranchAddress("nBhadrons", &nBhadrons, &b_nBhadrons);
   fChain->SetBranchAddress("lheNOutPartons", &lheNOutPartons, &b_lheNOutPartons);
   fChain->SetBranchAddress("lheNOutB", &lheNOutB, &b_lheNOutB);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("isBoosted", &isBoosted, &b_isBoosted);
   fChain->SetBranchAddress("genDecMode1", &genDecMode1, &b_genDecMode1);
   fChain->SetBranchAddress("genDecMode2", &genDecMode2, &b_genDecMode2);
   fChain->SetBranchAddress("npv", &npv, &b_npv);
   fChain->SetBranchAddress("npu", &npu, &b_npu);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("triggerbit", &triggerbit, &b_triggerbit);
   fChain->SetBranchAddress("L3filter1", &L3filter1, &b_L3filter1);
   fChain->SetBranchAddress("L3filterlast1", &L3filterlast1, &b_L3filterlast1);
   fChain->SetBranchAddress("L3filter2", &L3filter2, &b_L3filter2);
   fChain->SetBranchAddress("L3filterlast2", &L3filterlast2, &b_L3filterlast2);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("pairType", &pairType, &b_rho);
   fChain->SetBranchAddress("isMC", &isMC, &b_isMC);
   fChain->SetBranchAddress("isOS", &isOS, &b_isOS);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("met_et", &met_et, &b_met_et);
   fChain->SetBranchAddress("met_et_corr", &met_et_corr, &b_met_et_corr);
   fChain->SetBranchAddress("met_cov00", &met_cov00, &b_met_cov00);
   fChain->SetBranchAddress("met_cov01", &met_cov01, &b_met_cov01);
   fChain->SetBranchAddress("met_cov10", &met_cov10, &b_met_cov10);
   fChain->SetBranchAddress("met_cov11", &met_cov11, &b_met_cov11);
   fChain->SetBranchAddress("mT1", &mT1, &b_mT1);
   fChain->SetBranchAddress("mT2", &mT2, &b_mT2);
   fChain->SetBranchAddress("dau1_iso", &dau1_iso, &b_dau1_iso);
   fChain->SetBranchAddress("dau1_MVAiso", &dau1_MVAiso, &b_dau1_MVAiso);
   fChain->SetBranchAddress("dau1_CUTiso", &dau1_CUTiso, &b_dau1_CUTiso);
   fChain->SetBranchAddress("dau1_antiele", &dau1_antiele, &b_dau1_antiele);
   fChain->SetBranchAddress("dau1_antimu", &dau1_antimu, &b_dau1_antimu);
   fChain->SetBranchAddress("dau1_photonPtSumOutsideSignalCone", &dau1_photonPtSumOutsideSignalCone, &b_dau1_photonPtSumOutsideSignalCone);
   fChain->SetBranchAddress("dau1_byLooseCombinedIsolationDeltaBetaCorr3Hits", &dau1_byLooseCombinedIsolationDeltaBetaCorr3Hits, &b_dau1_byLooseCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("dau1_byMediumCombinedIsolationDeltaBetaCorr3Hits", &dau1_byMediumCombinedIsolationDeltaBetaCorr3Hits, &b_dau1_byMediumCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("dau1_byTightCombinedIsolationDeltaBetaCorr3Hits", &dau1_byTightCombinedIsolationDeltaBetaCorr3Hits, &b_dau1_byTightCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("dau1_pt", &dau1_pt, &b_dau1_pt);
   fChain->SetBranchAddress("dau1_eta", &dau1_eta, &b_dau1_eta);
   fChain->SetBranchAddress("dau1_phi", &dau1_phi, &b_dau1_phi);
   fChain->SetBranchAddress("dau1_e", &dau1_e, &b_dau1_e);
   fChain->SetBranchAddress("dau1_flav", &dau1_flav, &b_dau1_flav);
   fChain->SetBranchAddress("genmatched1_pt", &genmatched1_pt, &b_genmatched1_pt);
   fChain->SetBranchAddress("genmatched1_eta", &genmatched1_eta, &b_genmatched1_eta);
   fChain->SetBranchAddress("genmatched1_phi", &genmatched1_phi, &b_genmatched1_phi);
   fChain->SetBranchAddress("genmatched1_e", &genmatched1_e, &b_genmatched1_e);
   fChain->SetBranchAddress("genmatched2_pt", &genmatched2_pt, &b_genmatched2_pt);
   fChain->SetBranchAddress("genmatched2_eta", &genmatched2_eta, &b_genmatched2_eta);
   fChain->SetBranchAddress("genmatched2_phi", &genmatched2_phi, &b_genmatched2_phi);
   fChain->SetBranchAddress("genmatched2_e", &genmatched2_e, &b_genmatched2_e);
   fChain->SetBranchAddress("hasgenmatch1", &hasgenmatch1, &b_hasgenmatch1);
   fChain->SetBranchAddress("hasgenmatch2", &hasgenmatch2, &b_hasgenmatch2);
   fChain->SetBranchAddress("dau2_iso", &dau2_iso, &b_dau2_iso);
   fChain->SetBranchAddress("dau2_MVAiso", &dau2_MVAiso, &b_dau2_MVAiso);
   fChain->SetBranchAddress("dau2_CUTiso", &dau2_CUTiso, &b_dau2_CUTiso);
   fChain->SetBranchAddress("dau2_antiele", &dau2_antiele, &b_dau2_antiele);
   fChain->SetBranchAddress("dau2_antimu", &dau2_antimu, &b_dau2_antimu);
   fChain->SetBranchAddress("dau2_photonPtSumOutsideSignalCone", &dau2_photonPtSumOutsideSignalCone, &b_dau2_photonPtSumOutsideSignalCone);
   fChain->SetBranchAddress("dau2_byLooseCombinedIsolationDeltaBetaCorr3Hits", &dau2_byLooseCombinedIsolationDeltaBetaCorr3Hits, &b_dau2_byLooseCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("dau2_byMediumCombinedIsolationDeltaBetaCorr3Hits", &dau2_byMediumCombinedIsolationDeltaBetaCorr3Hits, &b_dau2_byMediumCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("dau2_byTightCombinedIsolationDeltaBetaCorr3Hits", &dau2_byTightCombinedIsolationDeltaBetaCorr3Hits, &b_dau2_byTightCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("dau2_pt", &dau2_pt, &b_dau2_pt);
   fChain->SetBranchAddress("dau2_eta", &dau2_eta, &b_dau2_eta);
   fChain->SetBranchAddress("dau2_phi", &dau2_phi, &b_dau2_phi);
   fChain->SetBranchAddress("dau2_e", &dau2_e, &b_dau2_e);
   fChain->SetBranchAddress("dau2_flav", &dau2_flav, &b_dau2_flav);
   fChain->SetBranchAddress("bjet1_pt", &bjet1_pt, &b_bjet1_pt);
   fChain->SetBranchAddress("bjet1_eta", &bjet1_eta, &b_bjet1_eta);
   fChain->SetBranchAddress("bjet1_phi", &bjet1_phi, &b_bjet1_phi);
   fChain->SetBranchAddress("bjet1_e", &bjet1_e, &b_bjet1_e);
   fChain->SetBranchAddress("bjet1_bID", &bjet1_bID, &b_bjet1_bID);
   fChain->SetBranchAddress("bjet1_flav", &bjet1_flav, &b_bjet1_flav);
   fChain->SetBranchAddress("bjet1_pt_raw", &bjet1_pt_raw, &b_bjet1_pt_raw);
   fChain->SetBranchAddress("bjet1_hasgenjet", &bjet1_hasgenjet, &b_bjet1_hasgenjet);
   fChain->SetBranchAddress("bjet2_pt", &bjet2_pt, &b_bjet2_pt);
   fChain->SetBranchAddress("bjet2_eta", &bjet2_eta, &b_bjet2_eta);
   fChain->SetBranchAddress("bjet2_phi", &bjet2_phi, &b_bjet2_phi);
   fChain->SetBranchAddress("bjet2_e", &bjet2_e, &b_bjet2_e);
   fChain->SetBranchAddress("bjet2_bID", &bjet2_bID, &b_bjet2m_bID);
   fChain->SetBranchAddress("bjet2_flav", &bjet2_flav, &b_bjet2_flav);
   fChain->SetBranchAddress("bjet2_pt_raw", &bjet2_pt_raw, &b_bjet2_pt_raw);
   fChain->SetBranchAddress("bjet2_hasgenjet", &bjet2_hasgenjet, &b_bjet2_hasgenjet);
   fChain->SetBranchAddress("nfatjets", &nfatjets, &b_nfatjets);
   fChain->SetBranchAddress("fatjet_pt", &fatjet_pt, &b_fatjet_pt);
   fChain->SetBranchAddress("fatjet_eta", &fatjet_eta, &b_fatjet_eta);
   fChain->SetBranchAddress("fatjet_phi", &fatjet_phi, &b_fatjet_phi);
   fChain->SetBranchAddress("fatjet_e", &fatjet_e, &b_fatjet_e);
   fChain->SetBranchAddress("fatjet_bID", &fatjet_bID, &b_fatjet_bID);
   fChain->SetBranchAddress("fatjet_filteredMass", &fatjet_filteredMass, &b_fatjet_filteredMass);
   fChain->SetBranchAddress("fatjet_prunedMass", &fatjet_prunedMass, &b_fatjet_prunedMass);
   fChain->SetBranchAddress("fatjet_trimmedMass", &fatjet_trimmedMass, &b_fatjet_trimmedMass);
   fChain->SetBranchAddress("fatjet_softdropMass", &fatjet_softdropMass, &b_fatjet_softdropMass);
   fChain->SetBranchAddress("fatjet_tau1", &fatjet_tau1, &b_fatjet_tau1);
   fChain->SetBranchAddress("fatjet_tau2", &fatjet_tau2, &b_fatjet_tau2);
   fChain->SetBranchAddress("fatjet_tau3", &fatjet_tau3, &b_fatjet_tau3);
   fChain->SetBranchAddress("fatjet_nsubjets", &fatjet_nsubjets, &b_fatjet_nsubjets);
   fChain->SetBranchAddress("dR_subj1_subj2", &dR_subj1_subj2, &b_dR_subj1_subj2);
   fChain->SetBranchAddress("subjetjet1_pt", &subjetjet1_pt, &b_subjetjet1_pt);
   fChain->SetBranchAddress("subjetjet1_eta", &subjetjet1_eta, &b_subjetjet1_eta);
   fChain->SetBranchAddress("subjetjet1_phi", &subjetjet1_phi, &b_subjetjet1_phi);
   fChain->SetBranchAddress("subjetjet1_e", &subjetjet1_e, &b_subjetjet1_e);
   fChain->SetBranchAddress("subjetjet1_bID", &subjetjet1_bID, &b_subjetjet1_bID);
   fChain->SetBranchAddress("subjetjet2_pt", &subjetjet2_pt, &b_subjetjet2_pt);
   fChain->SetBranchAddress("subjetjet2_eta", &subjetjet2_eta, &b_subjetjet2_eta);
   fChain->SetBranchAddress("subjetjet2_phi", &subjetjet2_phi, &b_subjetjet2_phi);
   fChain->SetBranchAddress("subjetjet2_e", &subjetjet2_e, &b_subjetjet2_e);
   fChain->SetBranchAddress("subjetjet2_bID", &subjetjet2_bID, &b_subjetjet2_bID);
   fChain->SetBranchAddress("genjet1_pt", &genjet1_pt, &b_genjet1_pt);
   fChain->SetBranchAddress("genjet1_eta", &genjet1_eta, &b_genjet1_eta);
   fChain->SetBranchAddress("genjet1_phi", &genjet1_phi, &b_genjet1_phi);
   fChain->SetBranchAddress("genjet1_e", &genjet1_e, &b_genjet1_e);
   fChain->SetBranchAddress("genjet2_pt", &genjet2_pt, &b_genjet2_pt);
   fChain->SetBranchAddress("genjet2_eta", &genjet2_eta, &b_genjet2_eta);
   fChain->SetBranchAddress("genjet2_phi", &genjet2_phi, &b_genjet2_phi);
   fChain->SetBranchAddress("genjet2_e", &genjet2_e, &b_genjet2_e);
   fChain->SetBranchAddress("tauH_pt", &tauH_pt, &b_tauH_pt);
   fChain->SetBranchAddress("tauH_eta", &tauH_eta, &b_tauH_eta);
   fChain->SetBranchAddress("tauH_phi", &tauH_phi, &b_tauH_phi);
   fChain->SetBranchAddress("tauH_e", &tauH_e, &b_tauH_e);
   fChain->SetBranchAddress("tauH_mass", &tauH_mass, &b_tauH_mass);
   fChain->SetBranchAddress("tauH_SVFIT_mass", &tauH_SVFIT_mass, &b_tauH_SVFIT_mass);
   fChain->SetBranchAddress("tauH_SVFIT_pt", &tauH_SVFIT_pt, &b_tauH_SVFIT_pt);
   fChain->SetBranchAddress("tauH_SVFIT_eta", &tauH_SVFIT_eta, &b_tauH_SVFIT_eta);
   fChain->SetBranchAddress("tauH_SVFIT_phi", &tauH_SVFIT_phi, &b_tauH_SVFIT_phi);
   fChain->SetBranchAddress("tauH_SVFIT_METphi", &tauH_SVFIT_METphi, &b_tauH_SVFIT_METphi);
   fChain->SetBranchAddress("tauH_SVFIT_METrho", &tauH_SVFIT_METrho, &b_tauH_SVFIT_METrho);
   fChain->SetBranchAddress("tauH_SVFIT_mass_up", &tauH_SVFIT_mass_up, &b_tauH_SVFIT_mass_up);
   fChain->SetBranchAddress("tauH_SVFIT_mass_down", &tauH_SVFIT_mass_down, &b_tauH_SVFIT_mass_down);
   fChain->SetBranchAddress("bH_pt", &bH_pt, &b_bH_pt);
   fChain->SetBranchAddress("bH_eta", &bH_eta, &b_bH_eta);
   fChain->SetBranchAddress("bH_phi", &bH_phi, &b_bH_phi);
   fChain->SetBranchAddress("bH_e", &bH_e, &b_bH_e);
   fChain->SetBranchAddress("bH_mass", &bH_mass, &b_bH_mass);
   fChain->SetBranchAddress("HHsvfit_pt", &HHsvfit_pt, &b_HHsvfit_pt);
   fChain->SetBranchAddress("HHsvfit_eta", &HHsvfit_eta, &b_HHsvfit_eta);
   fChain->SetBranchAddress("HHsvfit_phi", &HHsvfit_phi, &b_HHsvfit_phi);
   fChain->SetBranchAddress("HHsvfit_e", &HHsvfit_e, &b_HHsvfit_e);
   fChain->SetBranchAddress("HHsvfit_mass", &HHsvfit_mass, &b_HHsvfit_mass);
   fChain->SetBranchAddress("HH_pt", &HH_pt, &b_HH_pt);
   fChain->SetBranchAddress("HH_eta", &HH_eta, &b_HH_eta);
   fChain->SetBranchAddress("HH_phi", &HH_phi, &b_HH_phi);
   fChain->SetBranchAddress("HH_e", &HH_e, &b_HH_e);
   fChain->SetBranchAddress("HH_mass", &HH_mass, &b_HH_mass);
   fChain->SetBranchAddress("HH_mass_raw", &HH_mass_raw, &b_HH_mass_raw);
   fChain->SetBranchAddress("HH_mass_raw_tauup", &HH_mass_raw_tauup, &b_HH_mass_raw_tauup);
   fChain->SetBranchAddress("HH_mass_raw_taudown", &HH_mass_raw_taudown, &b_HH_mass_raw_taudown);
   fChain->SetBranchAddress("HHKin_mass", &HHKin_mass, &b_HHKin_mass);
   fChain->SetBranchAddress("HHKin_chi2", &HHKin_chi2, &b_HHKin_chi2);
   fChain->SetBranchAddress("HH_deltaPhi", &HH_deltaPhi, &b_HH_deltaPhi);
   fChain->SetBranchAddress("HHsvfit_deltaPhi", &HHsvfit_deltaPhi, &b_HHsvfit_deltaPhi);
   fChain->SetBranchAddress("tauHMet_deltaPhi", &tauHMet_deltaPhi, &b_tauHMet_deltaPhi);
   fChain->SetBranchAddress("tauHsvfitMet_deltaPhi", &tauHsvfitMet_deltaPhi, &b_tauHsvfitMet_deltaPhi);
   fChain->SetBranchAddress("bHMet_deltaPhi", &bHMet_deltaPhi, &b_bHMet_deltaPhi);
   fChain->SetBranchAddress("ditau_deltaPhi", &ditau_deltaPhi, &b_ditau_deltaPhi);
   fChain->SetBranchAddress("dib_deltaPhi", &dib_deltaPhi, &b_dib_deltaPhi);
   fChain->SetBranchAddress("ditau_deltaR", &ditau_deltaR, &b_ditau_deltaR);
   fChain->SetBranchAddress("dib_deltaR", &dib_deltaR, &b_dib_deltaR);
   fChain->SetBranchAddress("btau_deltaRmin", &btau_deltaRmin, &b_btau_deltaRmin);
   fChain->SetBranchAddress("btau_deltaRmax", &btau_deltaRmax, &b_btau_deltaRmax);
   fChain->SetBranchAddress("dau1MET_deltaphi", &dau1MET_deltaphi, &b_dau1MET_deltaphi);
   fChain->SetBranchAddress("dau2MET_deltaphi", &dau2MET_deltaphi, &b_dau2MET_deltaphi);
   fChain->SetBranchAddress("HT20", &HT20, &b_HT20);
   fChain->SetBranchAddress("HT50", &HT50, &b_HT50);
   fChain->SetBranchAddress("HT20Full", &HT20Full, &b_HT20Full);
   fChain->SetBranchAddress("jet20centrality", &jet20centrality, &b_jet20centrality);
   fChain->SetBranchAddress("jets_pt", &jets_pt, &b_jets_pt);
   fChain->SetBranchAddress("jets_eta", &jets_eta, &b_jets_eta);
   fChain->SetBranchAddress("jets_phi", &jets_phi, &b_jets_phi);
   fChain->SetBranchAddress("jets_e", &jets_e, &b_jets_e);
   fChain->SetBranchAddress("jets_btag", &jets_btag, &b_jets_btag);
   fChain->SetBranchAddress("jets_flav", &jets_flav, &b_jets_flav);
   fChain->SetBranchAddress("jets_isH", &jets_isH, &b_jets_isH);
   fChain->SetBranchAddress("jets_hasgenjet", &jets_hasgenjet, &b_jets_hasgenjet);
   fChain->SetBranchAddress("njets", &njets, &b_njets);
   fChain->SetBranchAddress("njets20", &njets20, &b_njets20);
   fChain->SetBranchAddress("njets50", &njets50, &b_njets50);
   fChain->SetBranchAddress("nbjetscand", &nbjetscand, &b_nbjetscand);
   fChain->SetBranchAddress("njetsBHadFlav", &njetsBHadFlav, &b_njetsBHadFlav);
   fChain->SetBranchAddress("njetsCHadFlav", &njetsCHadFlav, &b_njetsCHadFlav);
   fChain->SetBranchAddress("jets_jecUnc", &jets_jecUnc, &b_jets_jecUnc);
   fChain->SetBranchAddress("dau1_jecUnc", &dau1_jecUnc, &b_dau1_jecUnc);
   fChain->SetBranchAddress("dau2_jecUnc", &dau2_jecUnc, &b_dau2_jecUnc);
   fChain->SetBranchAddress("bjet1_jecUnc", &bjet1_jecUnc, &b_bjet1_jecUnc);
   fChain->SetBranchAddress("bjet2_jecUnc", &bjet2_jecUnc, &b_bjet2_jecUnc);
   fChain->SetBranchAddress("leps_pt", &leps_pt, &b_leps_pt);
   fChain->SetBranchAddress("leps_eta", &leps_eta, &b_leps_eta);
   fChain->SetBranchAddress("leps_phi", &leps_phi, &b_leps_phi);
   fChain->SetBranchAddress("leps_e", &leps_e, &b_leps_e);
   fChain->SetBranchAddress("leps_flav", &leps_flav, &b_leps_flav);
   fChain->SetBranchAddress("nleps", &nleps, &b_nleps);
   fChain->SetBranchAddress("HHkinsvfit_bHmass", &HHkinsvfit_bHmass, &b_HHkinsvfit_bHmass);
   fChain->SetBranchAddress("HHkinsvfit_pt", &HHkinsvfit_pt, &b_HHkinsvfit_pt);
   fChain->SetBranchAddress("HHkinsvfit_eta", &HHkinsvfit_eta, &b_HHkinsvfit_eta);
   fChain->SetBranchAddress("HHkinsvfit_phi", &HHkinsvfit_phi, &b_HHkinsvfit_phi);
   fChain->SetBranchAddress("HHkinsvfit_e", &HHkinsvfit_e, &b_HHkinsvfit_e);
   fChain->SetBranchAddress("HHkinsvfit_m", &HHkinsvfit_m, &b_HHkinsvfit_m);
   fChain->SetBranchAddress("MT2", &MT2, &b_MT2);
   fChain->SetBranchAddress("bH_mass_raw", &bH_mass_raw, &b_bH_mass_raw);
   fChain->SetBranchAddress("HHKin_mass_raw", &HHKin_mass_raw, &b_HHKin_mass_raw);
   fChain->SetBranchAddress("HHKin_mass_raw_tauup", &HHKin_mass_raw_tauup, &b_HHKin_mass_raw_tauup);
   fChain->SetBranchAddress("HHKin_mass_raw_taudown", &HHKin_mass_raw_taudown, &b_HHKin_mass_raw_taudown);
   fChain->SetBranchAddress("HHKin_mass_raw_chi2", &HHKin_mass_raw_chi2, &b_HHKin_mass_raw_chi2);
   fChain->SetBranchAddress("HHKin_mass_raw_convergence", &HHKin_mass_raw_convergence, &b_HHKin_mass_raw_convergence);
   fChain->SetBranchAddress("HHKin_mass_raw_prob", &HHKin_mass_raw_prob, &b_HHKin_mass_raw_prob);
   fChain->SetBranchAddress("HHKin_mass_raw_copy", &HHKin_mass_raw_copy, &b_HHKin_mass_raw_copy);
   fChain->SetBranchAddress("lheht", &lheht, &b_lheht);
   fChain->SetBranchAddress("topReweight", &topReweight, &b_topReweight);
   fChain->SetBranchAddress("MuTauKine", &MuTauKine, &b_MuTauKine);
   fChain->SetBranchAddress("ETauKine", &ETauKine, &b_ETauKine);
   fChain->SetBranchAddress("LepTauKine", &LepTauKine, &b_LepTauKine);
   fChain->SetBranchAddress("BDTResonant", &BDTResonant, &b_BDTResonant);
   Notify();
}

Bool_t newClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void newClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t newClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef newClass_cxx
