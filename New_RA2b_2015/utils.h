#include "TH1.h"
#include "TVector2.h"
#include <cstdio>
#include <iostream>
#include "TString.h"
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class Utils{

    int TauResponse_nBins;

public:


    Utils();

    void TauResponse_checkPtBin(unsigned int ptBin);

    TString TauResponse_name(unsigned int ptBin);

    double deltaPhi(double phi1, double phi2);

    double deltaR(double eta1, double eta2, double phi1, double phi2);

    bool findMatchedObject(int &matchedObjIdx,double genTauEta, double genTauPhi, vector<double> PtVec,vector<double> EtaVec, vector<double> PhiVec,double deltaRMax, int ver);

    int TauResponse_nBins_();

    unsigned int TauResponse_ptBin(double pt);

    double getRandom(double muPt_,vector<TH1*> vec_resp);

    double MuActivity(double muEta, double muPhi, vector<double> JetPtVec,vector<double> JetEtaVec, vector<double> JetPhiVec,vector<double> JetChargedEmEnergyFraction, vector<double> JetChargedHadronEnergyFraction);
};

