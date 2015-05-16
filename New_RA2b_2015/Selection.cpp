#include "Selection.h"  


  // Constructor
  Selection::Selection(){
    //initialize a map between string=cutnames and histvecs. copy one histvec into all of them. The histograms, though, will be filled differently.
    cutname[0]="nocut";cutname[1]="Njet_4";cutname[2]="ht_500";
    cutname[3]="mht_200";cutname[4]="nolep";
    cutname[5]="isoMu";cutname[6]="isoElec";cutname[7]="isoPion";
    cutname[8]="delphi";cutname[9]="CSVM_0";
    cutname[10]="CSVM_1";cutname[11]="CSVM_2";cutname[12]="CSVM_3";
  }

  ///apply the cuts here
  bool Selection::checkcut(string ss,double ht_,double mht_,double minDeltaPhiN_,int nJets_,int nBtags_,int nLeptons_,int nElecIso_,int nMuIso_,int nPionIso_){

    if(ss == cutname[0])return true;
    if(ss== cutname[1]){if(Njet_4(nJets_))return true;}
    if(ss== cutname[2]){if(Njet_4(nJets_) && ht_500(ht_))return true;}
    if(ss== cutname[3]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_))return true;}
    if(ss== cutname[4]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_))return true;}
    if(ss== cutname[5]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_))return true;}
    if(ss== cutname[6]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_))return true;}
    if(ss== cutname[7]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_))return true;}
    if(ss== cutname[8]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( minDeltaPhiN_))return true;}
    if(ss== cutname[9]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( minDeltaPhiN_)&&btag_0( nBtags_))return true;}
    if(ss== cutname[10]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( minDeltaPhiN_)&&btag_1( nBtags_))return true;}
    if(ss== cutname[11]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( minDeltaPhiN_)&&btag_2( nBtags_))return true;}
    if(ss== cutname[12]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( minDeltaPhiN_)&&btag_3( nBtags_))return true;}

  return false;
  }

  bool Selection::checkcut_HadTau(string ss,double ht_,double mht_,double minDeltaPhiN_,int nJets_,int nBtags_,int nLeptons_,int nElecIso_,int nMuIso_,int nPionIso_){

    if(ss == cutname[0])return true;
    if(ss== cutname[1]){if(Njet_4(nJets_))return true;}
    if(ss== cutname[2]){if(Njet_4(nJets_) && ht_500(ht_))return true;}
    if(ss== cutname[3]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_))return true;}
    if(ss== cutname[4]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_))return true;}
    if(ss== cutname[5]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_))return true;}
    if(ss== cutname[6]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_))return true;}
    if(ss== cutname[7]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_))return true;}
    if(ss== cutname[8]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( minDeltaPhiN_))return true;}
    if(ss== cutname[9]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( minDeltaPhiN_)&&btag_0( nBtags_))return true;}
    if(ss== cutname[10]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( minDeltaPhiN_)&&btag_1( nBtags_))return true;}
    if(ss== cutname[11]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( minDeltaPhiN_)&&btag_2( nBtags_))return true;}
    if(ss== cutname[12]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( minDeltaPhiN_)&&btag_3( nBtags_))return true;}

  return false;
  }


  map<int, string> Selection::cutName() const {return cutname;}
 

