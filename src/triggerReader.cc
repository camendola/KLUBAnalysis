#include "triggerReader.h"
#include "OfflineProducerHelper.h"

using namespace std;

triggerReader::triggerReader (TH1F* inputHisto)
{
    _allTriggers.clear();
    int nbins = inputHisto->GetNbinsX();
    int binstoskip = 3; // skip fist bintoskip bins as they don;t contain trigger info but other stuff
    for (int ibin = binstoskip+1; ibin <= nbins; ++ibin)
    {
        string thisName = string(inputHisto->GetXaxis()->GetBinLabel(ibin));
        _allTriggers.push_back(thisName);
    }
    return;
}

triggerReader::~triggerReader()
{}

void triggerReader::addTauTauTrigs (vector<string> list)
{
    for (unsigned int i = 0; i < list.size(); i++)
    {
        auto it = find (_allTriggers.begin(), _allTriggers.end(), list.at(i));
        if (it != _allTriggers.end()) _ttTriggers.push_back (it - _allTriggers.begin());
        else cout << " ** WARNING triggerReader : trigger name " << list.at(i) << " not in input histogram" << endl;
    }
    return;
}

void triggerReader::addMuTauTrigs (vector<string> list)
{
    for (unsigned int i = 0; i < list.size(); i++)
    {
        auto it = find (_allTriggers.begin(), _allTriggers.end(), list.at(i));
        if (it != _allTriggers.end()) _mtTriggers.push_back (it - _allTriggers.begin());
        else cout << " ** WARNING triggerReader : trigger name " << list.at(i) << " not in input histogram" << endl;
    }
    return;
}

void triggerReader::addEleTauTrigs (vector<string> list)
{
    for (unsigned int i = 0; i < list.size(); i++)
    {
        auto it = find (_allTriggers.begin(), _allTriggers.end(), list.at(i));
        if (it != _allTriggers.end()) _etTriggers.push_back (it - _allTriggers.begin());
        else cout << " ** WARNING triggerReader : trigger name " << list.at(i) << " not in input histogram" << endl;
    }
    return;
}

void triggerReader::addMuEleTrigs (vector<string> list)
{
    for (unsigned int i = 0; i < list.size(); i++)
    {
        auto it = find (_allTriggers.begin(), _allTriggers.end(), list.at(i));
        if (it != _allTriggers.end()) _emTriggers.push_back (it - _allTriggers.begin());
        else cout << " ** WARNING triggerReader : trigger name " << list.at(i) << " not in input histogram" << endl;
    }
    return;
}
void triggerReader::addEleEleTrigs (vector<string> list)
{
    for (unsigned int i = 0; i < list.size(); i++)
    {
        auto it = find (_allTriggers.begin(), _allTriggers.end(), list.at(i));
        if (it != _allTriggers.end()) _eeTriggers.push_back (it - _allTriggers.begin());
        else cout << " ** WARNING triggerReader : trigger name " << list.at(i) << " not in input histogram" << endl;
    }
    return;
}
void triggerReader::addMuMuTrigs (vector<string> list)
{
    for (unsigned int i = 0; i < list.size(); i++)
    {
        auto it = find (_allTriggers.begin(), _allTriggers.end(), list.at(i));
        if (it != _allTriggers.end()) _mmTriggers.push_back (it - _allTriggers.begin());
        else cout << " ** WARNING triggerReader : trigger name " << list.at(i) << " not in input histogram" << endl;
    }
    return;
}

void triggerReader::addBBresTrigs (vector<string> list)
{
    for (unsigned int i = 0; i < list.size(); i++)
    {
        auto it = find (_allTriggers.begin(), _allTriggers.end(), list.at(i));
        if (it != _allTriggers.end()) _bbresTriggers.push_back (it - _allTriggers.begin());
        else cout << " ** WARNING triggerReader : trigger name " << list.at(i) << " not in input histogram" << endl;
    }
    return;
}
void triggerReader::addBBnonresTrigs (vector<string> list)
{
    for (unsigned int i = 0; i < list.size(); i++)
    {
        auto it = find (_allTriggers.begin(), _allTriggers.end(), list.at(i));
        if (it != _allTriggers.end()) _bbnonresTriggers.push_back (it - _allTriggers.begin());
        else cout << " ** WARNING triggerReader : trigger name " << list.at(i) << " not in input histogram" << endl;
    }
    return;
}
void triggerReader::addGGTrigs (vector<string> list)
{
    for (unsigned int i = 0; i < list.size(); i++)
    {
        auto it = find (_allTriggers.begin(), _allTriggers.end(), list.at(i));
        if (it != _allTriggers.end()) _ggTriggers.push_back (it - _allTriggers.begin());
        else cout << " ** WARNING triggerReader : trigger name " << list.at(i) << " not in input histogram" << endl;
    }
    return;
}

bool triggerReader::checkORTauTau  (Long64_t triggerbit)
{
    bool OR = false;
    for (unsigned int i = 0; i < _ttTriggers.size(); i++)
    {
        OR = CheckBit (triggerbit, _ttTriggers.at(i));
        if (OR) break;
    }
    return OR;
}

bool triggerReader::checkORMuTau  (Long64_t triggerbit)
{
    bool OR = false;
    for (unsigned int i = 0; i < _mtTriggers.size(); i++)
    {
        OR = CheckBit (triggerbit, _mtTriggers.at(i));
        if (OR) break;
    }
    return OR;
}

bool triggerReader::checkOREleTau  (Long64_t triggerbit)
{
    bool OR = false;
    for (unsigned int i = 0; i < _etTriggers.size(); i++)
    {
        OR = CheckBit (triggerbit, _etTriggers.at(i));
        if (OR) break;
    }
    return OR;
}

bool triggerReader::checkORMuEle  (Long64_t triggerbit)
{
    bool OR = false;
    for (unsigned int i = 0; i < _emTriggers.size(); i++)
    {
        OR = CheckBit (triggerbit, _emTriggers.at(i));
        if (OR) break;
    }
    return OR;
}
bool triggerReader::checkOREleEle  (Long64_t triggerbit)
{
    bool OR = false;
    for (unsigned int i = 0; i < _eeTriggers.size(); i++)
    {
        OR = CheckBit (triggerbit, _eeTriggers.at(i));
        if (OR) break;
    }
    return OR;
}
bool triggerReader::checkORMuMu  (Long64_t triggerbit)
{
    bool OR = false;
    for (unsigned int i = 0; i < _mmTriggers.size(); i++)
    {
        OR = CheckBit (triggerbit, _mmTriggers.at(i));
        if (OR) break;
    }
    return OR;
}

bool triggerReader::checkORBBnonres  (Long64_t triggerbit)
{
    bool OR = false;
    for (unsigned int i = 0; i < _bbnonresTriggers.size(); i++)
    {
        OR = CheckBit (triggerbit, _bbnonresTriggers.at(i));
        if (OR) break;
    }
    return OR;
}

bool triggerReader::checkORBBres  (Long64_t triggerbit)
{
    bool OR = false;
    for (unsigned int i = 0; i < _bbresTriggers.size(); i++)
    {
        OR = CheckBit (triggerbit, _bbresTriggers.at(i));
        if (OR) break;
    }
    return OR;
}

bool triggerReader::checkORGG  (Long64_t triggerbit)
{
    bool OR = false;
    for (unsigned int i = 0; i < _ggTriggers.size(); i++)
    {
        OR = CheckBit (triggerbit, _ggTriggers.at(i));
        if (OR) break;
    }
    return OR;
}

bool triggerReader::CheckBit (Long64_t number, int bitpos)
{
  Long64_t bit = 1;
  bool res = number & (bit << bitpos);
  return res;
}

bool triggerReader::checkOR (int pairType, Long64_t triggerbit)
{
    if (pairType == ((int) OfflineProducerHelper::MuHad) )      return checkORMuTau(triggerbit);
    else if (pairType == ((int) OfflineProducerHelper::EHad) )   return checkOREleTau(triggerbit);
    else if (pairType == ((int) OfflineProducerHelper::HadHad) ) return checkORTauTau(triggerbit);
    else if (pairType == ((int) OfflineProducerHelper::EMu) )    return checkORMuEle(triggerbit);
    else if (pairType == ((int) OfflineProducerHelper::EE) )    return checkOREleEle(triggerbit);
    else if (pairType == ((int) OfflineProducerHelper::MuMu) )    return checkORMuMu(triggerbit);
    else
    {
        cout << " ** WARNING!! Pair type " << pairType << " not implemented for trigger" << endl;
        return false;
    }
}


bool triggerReader::checkORcomb (int analysis, Long64_t triggerbit)
{
    
  if (analysis == 1 )   return checkORBBres(triggerbit);
    else if (analysis == 2 ) return checkORBBnonres(triggerbit);
    else if (analysis == 3 )    return checkORGG(triggerbit);
    else
    {
        cout << " ** WARNING!! analysis " << analysis << " not implemented for trigger" << endl;
        return false;
    }
}
