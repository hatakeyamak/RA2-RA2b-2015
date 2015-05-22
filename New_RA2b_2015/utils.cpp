#include "utils.h"


using namespace std;

    Utils::Utils(){
    };

    void Utils::TauResponse_checkPtBin(unsigned int ptBin) {
      if( ptBin > 3 ) {
        std::cout << "\n\nERROR in TauResponse: pt bin " << ptBin << " out of binning" << std::endl;
        throw std::exception();
      }
    }

    TString Utils::TauResponse_name(unsigned int ptBin) {
      TauResponse_checkPtBin(ptBin);
      TString name = "hTauResp_";
      name += ptBin;
      return name;
    }

    double Utils::deltaPhi(double phi1, double phi2) {
      return TVector2::Phi_mpi_pi(phi1-phi2);
    }

    double Utils::deltaR(double eta1, double eta2, double phi1, double phi2) {
      double dphi = deltaPhi(phi1,phi2);
      double deta = eta1 - eta2;
      return sqrt( deta*deta + dphi*dphi );
    }

    bool Utils::findMatchedObject(int &matchedObjIdx,double genTauEta, double genTauPhi, vector<double> PtVec,vector<double> EtaVec, vector<double> PhiVec,double deltaRMax, int ver){
      if(PtVec.size() ==0 ) return false;
      
      matchedObjIdx = -1;
      double deltaRMin = 100000.;
      for(int objIdx = 0; objIdx < (int) EtaVec.size(); ++objIdx){
        const double dr = deltaR(genTauEta,EtaVec[objIdx],genTauPhi,PhiVec[objIdx]);
        // printf("genTauEta: %g EtaVec[objIdx]: %g genTauPhi: %g PhiVec[objIdx]: %g dr: %g \n ",genTauEta,EtaVec[objIdx],genTauPhi,PhiVec[objIdx],dr);
        if( dr < deltaRMin ){
          deltaRMin = dr;
          matchedObjIdx = objIdx;
        }
      } // end of loop over vec

      // printf("matchedObjIdx: %d \n ",matchedObjIdx);
      bool match = false;
      if( deltaRMin < deltaRMax ) {
        match = true;
        if(ver!=0)printf("\n Mathed recoJet info: deltaRMin: %g matchedIdx: %d Pt: %g eta: %g phi: %g \n ",deltaRMin,matchedObjIdx,PtVec[matchedObjIdx],EtaVec[matchedObjIdx],PhiVec[matchedObjIdx]);
      } else {
        matchedObjIdx = -1;
      }
      return match;
    }

    int Utils::TauResponse_nBins_(){
      return 4;
    }

    unsigned int Utils::TauResponse_ptBin(double pt) {
      if( pt < 20.) {
        std::cerr << "\n\nERROR in TauResponse::ptBin" << std::endl;
        std::cerr << " No response available for pt = " << pt << " < " << 20 << std::endl;
        throw std::exception();
      }

      unsigned int bin=0;
      if( pt > 30. ) bin = 1;
      if( pt > 50. ) bin = 2;
      if( pt > 100. ) bin = 3;
      return bin;
    }

    double Utils::getRandom(double muPt_,vector<TH1*> vec_resp){
      int bin = TauResponse_ptBin(muPt_);
      return vec_resp[bin]->GetRandom();
    }

    
    // Activity variable. Muon isolation and efficiency depends on muon's pT and activity variable.
    // The latter maens the amount of hadronic activity around the muon. The higher this is, the harder 
    // it is to find the muon. 
    double Utils::MuActivity(double muEta, double muPhi, vector<double> JetPtVec,vector<double> JetEtaVec, vector<double> JetPhiVec,vector<double> JetChargedEmEnergyFraction, vector<double> JetChargedHadronEnergyFraction){
      double result=0.;
      double maxDeltaRMuActivity_ = 1.0; 
      for(int i=0; i<JetPtVec.size();i++){
        if(deltaR(muEta,JetEtaVec[i],muPhi,JetPhiVec[i]) >  maxDeltaRMuActivity_ ) continue;
        result+=JetPtVec[i]*( JetChargedEmEnergyFraction[i] + JetChargedHadronEnergyFraction[i] );
      }
      return result;
    }


