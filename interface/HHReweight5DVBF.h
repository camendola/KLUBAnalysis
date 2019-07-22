/*
** class  : HHReweight5DVBF
** author : L. Cadamuro (University of Florida), F. Brivio (MIB), C. Amendola (LLR)
** date   : July 2019
** brief  : Compute a reweight coefficient to transform an input distribution into a general point in kl, kt plane. 31/05/2017: Updated to 5D reweight
**          22 July 2019: Adapted to VBF signals
*/ 


#ifndef HHREWEIGHTVBF_H
#define HHREWEIGHTVBF_H

#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <utility>

#include "TH1.h"
#include "TH2.h"
#include "TAxis.h"
#include "TFile.h"

#define NCOEFFSAVBF 6

class HHReweight5DVBF{
    
    public:
        HHReweight5DVBF(std::string coeffFile, const TH2* hInput, bool useAbsEta=true);
        ~HHReweight5DVBF();
        double getWeight(double kl, double cV, double c2V, double mhh, double cth);
    
    private:
        void readInputFile(std::string coeffFile);
        double functionGF(double kl, double cV, double c2V, std::array<double, NCOEFFSAVBF> const &A);
        std::vector<std::string> tokenize(std::string input);
        std::pair<int,int> find2DBin(TH2* h, double x, double y);
        
        // adapted from ROOT to check histogram consistency
        bool CheckConsistency(const TH1* h1, const TH1* h2);
        bool CheckAxisLimits(const TAxis *a1, const TAxis *a2 );
        bool CheckBinLimits(const TAxis* a1, const TAxis * a2);
        
        // the coefficients of the reweight - read from the input file
        std::shared_ptr<TH2> h_SM_;
        std::shared_ptr<TH2> h_sumv1_;

        std::array<std::shared_ptr<TH2>, NCOEFFSAVBF> h_A_vec_;

        std::array<double, NCOEFFSAVBF> A_13TeV_;

        // the distribution of the input events
        // must the all the generated events before preselections
        std::shared_ptr<TH2> h_input_;
        bool useAbsEta_;
};

#endif