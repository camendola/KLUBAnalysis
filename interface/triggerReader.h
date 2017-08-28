// class to read the trigger histogram in the files produced in the LLR framework
// and retrieve useful information depending on the pair

// using string everywhere!

#include "TH1F.h"
#include <string>
#include <vector>

class triggerReader
{
    public:
        triggerReader (TH1F* inputHisto);
        ~triggerReader ();
        void addTauTauTrigs (std::vector<std::string> list);
        void addMuTauTrigs  (std::vector<std::string> list);
        void addEleTauTrigs (std::vector<std::string> list);
        void addMuEleTrigs  (std::vector<std::string> list);
        void addMuMuTrigs  (std::vector<std::string> list);
        void addEleEleTrigs  (std::vector<std::string> list);
	void addBBresTrigs  (std::vector<std::string> list);
	void addBBnonresTrigs  (std::vector<std::string> list);
	void addGGTrigs  (std::vector<std::string> list);
        
        bool checkORTauTau  (Long64_t triggerbit);
        bool checkORMuTau   (Long64_t triggerbit);
        bool checkOREleTau  (Long64_t triggerbit);
        bool checkORMuEle   (Long64_t triggerbit);
        bool checkORMuMu   (Long64_t triggerbit);
        bool checkOREleEle   (Long64_t triggerbit);
	bool checkORBBnonres   (Long64_t triggerbit);
	bool checkORBBres   (Long64_t triggerbit);
	bool checkORGG   (Long64_t triggerbit);

        bool CheckBit (Long64_t number, int bitpos);

        bool checkOR (int pairType, Long64_t triggerbit);
	bool checkORcomb (int analysis, Long64_t triggerbit);
    private:
        std::vector<std::string> _allTriggers; // all trigger names
        // --- these index the corresponding bits in the std::vector _allTriggers
        std::vector<Long64_t> _ttTriggers; // tau tau
        std::vector<Long64_t> _mtTriggers; // mu tau
        std::vector<Long64_t> _etTriggers; // e tau
        std::vector<Long64_t> _emTriggers; // e mu
        std::vector<Long64_t> _mmTriggers; // mu mu
        std::vector<Long64_t> _eeTriggers; // e e
	std::vector<Long64_t> _bbresTriggers; 
	std::vector<Long64_t> _bbnonresTriggers; 
	std::vector<Long64_t> _ggTriggers; 
	
};
