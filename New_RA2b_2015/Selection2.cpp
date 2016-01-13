#include "Selection2.h"  


  // Constructor
  Selection2::Selection2(){

    applyIsoTrk = true;

    //initialize a map between string=cutnames and histvecs. copy one histvec into all of them. The histograms, though, will be filled differently.
    cutname[0]="PreSel";cutname[1]="nolep";cutname[2]="Njet_4";cutname[3]="ht_500";
    cutname[4]="mht_200";cutname[5]="isoMu";cutname[6]="isoElec";cutname[7]="delphi"; 
    cutname[8]="isoPion";
    cutname[9]="tauId346";
    cutname[10]="tauId3469";
    cutname[11]="tauId257";
    cutname[12]="tauId25710";
    cutname[13]="tauId258";
    cutname[14]="tauId25811";

  }

  bool Selection2::ElecIsoTrk(int nElecIso_){
    if(!applyIsoTrk) return true;
    else if(nElecIso_ ==0)return true; return false;
  }


  bool Selection2::MuIsoTrk(int nMuIso_){
    if(!applyIsoTrk) return true;
    else if(nMuIso_ ==0)return true; return false;
  }


  bool Selection2::PionIsoTrk(int nPionIso_){
    if(!applyIsoTrk) return true;
    else if(nPionIso_ ==0)return true; return false;
  }




  ///apply the cuts here


  bool Selection2::checkcut(string ss,double ht_,double mht_,double dphi0,double dphi1,double dphi2,double dphi3,int nJets_,int nBtags_,int nLeptons_,int nElecIso_,int nMuIso_,int nPionIso_,int nTaus_346, int nTaus_3469,int nTaus_257, int nTaus_25710, int nTaus_258, int nTaus_25811){

    if(ss == cutname[0])return true;
    if(ss== cutname[1]){if(nolep( nLeptons_))return true;}
    if(ss== cutname[2]){if(nolep( nLeptons_)&&Njet_4(nJets_))return true;}
    if(ss== cutname[3]){if(nolep( nLeptons_)&&Njet_4(nJets_) && ht_500(ht_))return true;}
    if(ss== cutname[4]){if(nolep( nLeptons_)&&Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_))return true;}
    if(ss== cutname[5]){if(nolep( nLeptons_)&&Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_))return true;}
    if(ss== cutname[6]){if(nolep( nLeptons_)&&Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_))return true;}
    if(ss== cutname[7]){if(nolep( nLeptons_)&&Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&dphi( dphi0,dphi1,dphi2,dphi3))return true;}
    if(ss== cutname[8]){if(nolep( nLeptons_)&&Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&dphi( dphi0,dphi1,dphi2,dphi3)&&PionIsoTrk(nPionIso_))return true;}
    if(ss== cutname[9]){if(nolep( nLeptons_)&&Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&dphi( dphi0,dphi1,dphi2,dphi3)&&notau(nTaus_346))return true;}
    if(ss== cutname[10]){if(nolep( nLeptons_)&&Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&dphi( dphi0,dphi1,dphi2,dphi3)&&notau(nTaus_3469))return true;}
    if(ss== cutname[11]){if(nolep( nLeptons_)&&Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&dphi( dphi0,dphi1,dphi2,dphi3)&&notau(nTaus_257))return true;}
    if(ss== cutname[12]){if(nolep( nLeptons_)&&Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&dphi( dphi0,dphi1,dphi2,dphi3)&&notau(nTaus_25710))return true;}
    if(ss== cutname[13]){if(nolep( nLeptons_)&&Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&dphi( dphi0,dphi1,dphi2,dphi3)&&notau(nTaus_258))return true;}
    if(ss== cutname[14]){if(nolep( nLeptons_)&&Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&dphi( dphi0,dphi1,dphi2,dphi3)&&notau(nTaus_25811))return true;}
    return false;
  }



  map<int, string> Selection2::cutName() const {return cutname;}
 
