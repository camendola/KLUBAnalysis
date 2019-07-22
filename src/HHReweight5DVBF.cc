#include "HHReweight5DVBF.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>
#include <utility>

#include "TH2D.h"
#include "TMath.h"

using namespace std;

#define DEBUG false

HHReweight5DVBF::HHReweight5DVBF(std::string coeffFile, const TH2* hInput, bool useAbsEta)
{
    readInputFile(coeffFile); // initialize the reweight parameters from the txt input

    // clone the input histogram
    TH2* cloneH = (TH2*) hInput->Clone("h_input");
    if (!CheckConsistency(cloneH, h_A_vec_.at(0).get()))
    {
        cerr << " ** Error : the input histogram to HHReweightVBF is not compatible with the reweight file, did you use the correct binning?" << endl;
        throw std::runtime_error("Histograms inconsistency");
    }
    h_input_.reset(cloneH);

    // set default values
    A_13TeV_ = {1.00000, 1.00000, 1.00000, 1.00000, 1.00000, 1.00000}; // FRA DEBUG: FIXME with correct coeffs for VBF !!

    useAbsEta_ = useAbsEta;
}

HHReweight5DVBF::~HHReweight5DVBF()
{}

// return the weight to be applied for the reweight
// NOTE: normalization is arbitrary you'll have to scale by the sum of weights
double HHReweight5DVBF::getWeight(double kl, double cV, double c2V, double mhh, double cth)
{
    if (useAbsEta_) cth = TMath::Abs(cth);

    pair<int,int> bins = find2DBin(h_input_.get(), mhh, cth);
    double denom = h_input_->GetBinContent(bins.first, bins.second);
    if (denom == 0)
        return 0;

    double nEvSM = h_SM_->GetBinContent(bins.first, bins.second);
    
    std::array<double, NCOEFFSAVBF> Acoeffs;
    for (uint ic = 0; ic < NCOEFFSAVBF; ++ic)
    {
      Acoeffs[ic] = (h_A_vec_.at(ic))->GetBinContent(bins.first, bins.second);
    }
    double effBSM = nEvSM * functionGF(kl,cV,c2V,Acoeffs)/functionGF(kl,cV,c2V,A_13TeV_);

    if (DEBUG && effBSM/denom < 0){
      std::cout << "** HHReweight5DVBF : warning : I am getting a negative weight "
        << "kl, cV, c2V, mhh, cth " << kl << " " << cV << " " << c2V << " " << mhh << " " << cth << " | vals: "
        << nEvSM << " " << functionGF(kl,cV,c2V,Acoeffs) << " " << functionGF(kl,cV,c2V,A_13TeV_) << " " << denom
        << endl;
    }

    if (effBSM/denom < 0) return 0; // sometimes I get negative coeffs.. this should be a temporary fix!
    return (effBSM/denom) ;
}

void HHReweight5DVBF::readInputFile(std::string coeffFile)
{
    if (DEBUG) cout << " -- Reading input file" << coeffFile << endl;

    // create histograms to be filled from file
    // this is the binning of input file histogram
    // NOTE: code can be made more flexible to have binning inferred directly from the input file
    // double binning_mHH   [14] = {250.,270.,300.,330.,360.,390., 420.,450.,500.,550.,600.,700.,800.,1000.} ;
    // double binning_cth    [4] = {-1., -0.55,0.55,1. } ;
    double binning_mHH [56] = { 250,260,270,280,290,300,310,320,330,340,
                                350,360,370,380,390,400,410,420,430,440, 
                                450,460,470,480,490,
                                500,510,520,530,540,550,600,610,620,630,
                                640,650,660,670,680,690,700,750,800,850,
                                900,950,1000,1100,1200,1300,1400,1500.,1750,2000,50000};
    double binning_cth [5]  = {0.0, 0.4, 0.6, 0.8, 1.0} ;

    // int nbins_mHH = 13; // size of arrays - 1
    // int nbins_cth = 3;  // size of arrays - 1
    int nbins_mHH = 55; // size of arrays - 1
    int nbins_cth = 4;  // size of arrays - 1

    for (uint ic = 0; ic < NCOEFFSAVBF; ++ic)
    {
      string name = "h_A" + std::to_string(ic);
      h_A_vec_.at(ic) = std::make_shared<TH2D> (name.c_str(), name.c_str(), nbins_mHH, binning_mHH, nbins_cth, binning_cth );
    }

    h_SM_    = std::make_shared<TH2D> ("h_SM", "h_SM",       nbins_mHH, binning_mHH, nbins_cth, binning_cth );
    h_sumv1_ = std::make_shared<TH2D> ("h_sumv1", "h_sumv1", nbins_mHH, binning_mHH, nbins_cth, binning_cth );

    if (DEBUG) cout << " -- Histograms done" << endl;


    // read and fill from the file
    std::ifstream infile;
    infile.open(coeffFile);
    if (!infile.is_open())
        throw std::runtime_error("Could not open input file");

    std::string line;
    while (std::getline(infile, line))
    {
        if (DEBUG) cout << " -- Reading line " << line << endl;
        line = line.substr(0, line.find("#", 0)); // remove comments introduced by #
        if (!line.empty())
        {
            vector<string> tokens = tokenize(line);
            if (tokens.size() != 35)
            {
                cerr << " ** Error in reading input file: cannot interpret line: " << line << endl;
                throw std::runtime_error("Cannot parse input file");
            }
            //The columns are respectively: nbins GenMhh GenCostStar NenventsSM NenventsSumV1 A1 A3 A7 errorA1 errorA3 errorA7
            double mHH = std::stod(tokens.at(1));
            double cth = std::stod(tokens.at(2));
            int ibin = h_A_vec_.at(0)->FindBin(mHH, cth);

            h_SM_->SetBinContent(ibin, std::stod(tokens.at(3)));
            h_sumv1_->SetBinContent(ibin, std::stod(tokens.at(4)));

            for (uint ic = 0; ic < NCOEFFSAVBF; ++ic)
            {
              (h_A_vec_.at(ic))->SetBinContent(ibin, std::stod(tokens.at(ic+5)) );
              (h_A_vec_.at(ic))->SetBinError(ibin, std::stod(tokens.at(ic+5+15)) );
            }            

            if (DEBUG)
            {
                cout << " -- I'll store a file with the histograms" << endl;
                TFile* fOut = TFile::Open("HHReweight_histograms.root", "recreate");
                fOut->cd();
                for (uint ic = 0; ic < NCOEFFSAVBF; ++ic)
                {
                  (h_A_vec_.at(ic))->Write();
                }
                // h_A1_->Write();
                // h_A3_->Write();
                // h_A7_->Write();
                h_SM_->Write();
                h_sumv1_->Write();
                fOut->Close();
            }
        }
    }
}

// split a string on whitespaces, return elements
vector<std::string> HHReweight5DVBF::tokenize(std::string input)
{    
    if (DEBUG) cout << " -- Tokenizing input " << input << endl;

    std::istringstream buffer(input);
    std::vector<std::string> ret((std::istream_iterator<std::string>(buffer)), std::istream_iterator<std::string>());

    if (DEBUG){
        cout << "I got " << ret.size() << " tokens" << endl;
        cout << "     --> " ;
        for (string x : ret) cout << ":" << x << ": ";
        cout << endl;
    }

    return ret;
}

// return bin in 2D isto wihtout under/over flow (e.g. if ibin > ibinmax , ibin = ibinmax)
pair<int,int> HHReweight5DVBF::find2DBin(TH2* h, double x, double y)
{
    int ibinx = h->GetXaxis()->FindBin(x);
    int ibiny = h->GetYaxis()->FindBin(y);

    if (ibinx <= 0) ibinx = 1;
    if (ibinx > h->GetNbinsX()) ibinx = h->GetNbinsX();

    if (ibiny <= 0) ibiny = 1;
    if (ibiny > h->GetNbinsY()) ibiny = h->GetNbinsY();

    return make_pair(ibinx, ibiny);

}

double HHReweight5DVBF::functionGF(double kl, double cV, double c2V, std::array<double, NCOEFFSAVBF> const &A)
{
    // FRA DEBUG: double check the formula
    return ( A[0]*pow(kl,2)*pow(cV,2) + A[1]*pow(cV,4) + A[2]*pow(c2V,2) + A[3]*pow(cV,3)*kl + A[4]*cV*c2V*kl + A[5]*pow(cV,2)*c2V );
}


//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
// the following is adapted from ROOT source - because yeah, they are protected TH1 members...


bool HHReweight5DVBF::CheckConsistency(const TH1* h1, const TH1* h2)
{
   if (h1 == h2) return true;

   if (h1->GetDimension() != h2->GetDimension() ) {
      // throw DifferentDimension();
      return false;
   }
   Int_t dim = h1->GetDimension();

   // returns kTRUE if number of bins and bin limits are identical
   Int_t nbinsx = h1->GetNbinsX();
   Int_t nbinsy = h1->GetNbinsY();
   Int_t nbinsz = h1->GetNbinsZ();

   // Check whether the histograms have the same number of bins.
   if (nbinsx != h2->GetNbinsX() ||
       (dim > 1 && nbinsy != h2->GetNbinsY())  ||
       (dim > 2 && nbinsz != h2->GetNbinsZ()) ) {
      // throw DifferentNumberOfBins();
      return false;
   }

   bool ret = true;

   // check axis limits
   ret &= CheckAxisLimits(h1->GetXaxis(), h2->GetXaxis());
   if (dim > 1) ret &= CheckAxisLimits(h1->GetYaxis(), h2->GetYaxis());
   if (dim > 2) ret &= CheckAxisLimits(h1->GetZaxis(), h2->GetZaxis());

   // check bin limits
   ret &= CheckBinLimits(h1->GetXaxis(), h2->GetXaxis());
   if (dim > 1) ret &= CheckBinLimits(h1->GetYaxis(), h2->GetYaxis());
   if (dim > 2) ret &= CheckBinLimits(h1->GetZaxis(), h2->GetZaxis());

   // check labels if histograms are both not empty
   // if ( (h1->fTsumw != 0 || h1->GetEntries() != 0) &&
   //      (h2->fTsumw != 0 || h2->GetEntries() != 0) ) {
   //    ret &= CheckBinLabels(h1->GetXaxis(), h2->GetXaxis());
   //    if (dim > 1) ret &= CheckBinLabels(h1->GetYaxis(), h2->GetYaxis());
   //    if (dim > 2) ret &= CheckBinLabels(h1->GetZaxis(), h2->GetZaxis());
   // }

   return ret;
}

bool HHReweight5DVBF::CheckAxisLimits(const TAxis *a1, const TAxis *a2 )
{
   if ( ! TMath::AreEqualRel(a1->GetXmin(), a2->GetXmin(),1.E-12) ||
        ! TMath::AreEqualRel(a1->GetXmax(), a2->GetXmax(),1.E-12) ) {
      // throw DifferentAxisLimits();
      return false;
   }
   return true;
}

bool HHReweight5DVBF::CheckBinLimits(const TAxis* a1, const TAxis * a2)
{
   const TArrayD * h1Array = a1->GetXbins();
   const TArrayD * h2Array = a2->GetXbins();
   Int_t fN = h1Array->fN;
   if ( fN != 0 ) {
      if ( h2Array->fN != fN ) {
         // throw DifferentBinLimits();
         return false;
      }
      else {
         for ( int i = 0; i < fN; ++i ) {
            if ( ! TMath::AreEqualRel( h1Array->GetAt(i), h2Array->GetAt(i), 1E-10 ) ) {
               // throw DifferentBinLimits();
               return false;
            }
         }
      }
   }

   return true;
}