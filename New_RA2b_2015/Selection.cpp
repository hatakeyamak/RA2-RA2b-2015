#include "Selection.h"  


  // Constructor
  Selection::Selection(){
    //initialize a map between string=cutnames and histvecs. copy one histvec into all of them. The histograms, though, will be filled differently.
    cutname[0]="nocut";cutname[1]="Njet_4";cutname[2]="ht_500";
    cutname[3]="mht_200";cutname[4]="nolep";
    cutname[5]="isoMu";cutname[6]="isoElec";cutname[7]="isoPion";
    cutname[8]="delphi";cutname[9]="CSVM_0";
    cutname[10]="CSVM_1";cutname[11]="CSVM_2";cutname[12]="CSVM_3";

    // search regions
    cutname[13]="search1";cutname[14]="search2";cutname[15]="search3";
    cutname[16]="search1";cutname[17]="search2";cutname[18]="search3";
    cutname[19]="search1";cutname[20]="search2";cutname[21]="search3";
    cutname[22]="search1";cutname[23]="search2";cutname[24]="search3";
    cutname[25]="search1";cutname[26]="search2";cutname[27]="search3";
    cutname[28]="search1";cutname[29]="search2";cutname[30]="search3";


  }

  ///apply the cuts here

/*
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
*/

  bool Selection::checkcut(string ss,double ht_,double mht_,double dphi0,double dphi1,double dphi2,int nJets_,int nBtags_,int nLeptons_,int nElecIso_,int nMuIso_,int nPionIso_){

    if(ss == cutname[0])return true;
    if(ss== cutname[1]){if(Njet_4(nJets_))return true;}
    if(ss== cutname[2]){if(Njet_4(nJets_) && ht_500(ht_))return true;}
    if(ss== cutname[3]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_))return true;}
    if(ss== cutname[4]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_))return true;}
    if(ss== cutname[5]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_))return true;}
    if(ss== cutname[6]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_))return true;}
    if(ss== cutname[7]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_))return true;}
    if(ss== cutname[8]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2))return true;}
    if(ss== cutname[9]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&btag_0( nBtags_))return true;}
    if(ss== cutname[10]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&btag_1( nBtags_))return true;}
    if(ss== cutname[11]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&btag_2( nBtags_))return true;}
    if(ss== cutname[12]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&btag_3( nBtags_))return true;}


    // search cuts
    if(ss== cutname[13]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_4_6(nJets_)&&ht_500_800(ht_)&&mht_200_500(mht_))return true;}
    if(ss== cutname[14]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_4_6(nJets_)&&ht_800_1200(ht_)&&mht_200_500(mht_))return true;}
    if(ss== cutname[15]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_4_6(nJets_)&&ht_1200(ht_)&&mht_200_500(mht_))return true;}

    if(ss== cutname[16]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_4_6(nJets_)&&ht_500_1200(ht_)&&mht_500_750(mht_))return true;}
    if(ss== cutname[17]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_4_6(nJets_)&&ht_1200(ht_)&&mht_500_750(mht_))return true;}
    if(ss== cutname[18]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_4_6(nJets_)&&ht_800(ht_)&&mht_750(mht_))return true;}

    if(ss== cutname[19]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_7_8(nJets_)&&ht_500_800(ht_)&&mht_200_500(mht_))return true;}
    if(ss== cutname[20]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_7_8(nJets_)&&ht_800_1200(ht_)&&mht_200_500(mht_))return true;}
    if(ss== cutname[21]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_7_8(nJets_)&&ht_1200(ht_)&&mht_200_500(mht_))return true;}

    if(ss== cutname[22]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_7_8(nJets_)&&ht_500_1200(ht_)&&mht_500_750(mht_))return true;}
    if(ss== cutname[23]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_7_8(nJets_)&&ht_1200(ht_)&&mht_500_750(mht_))return true;}
    if(ss== cutname[24]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_7_8(nJets_)&&ht_800(ht_)&&mht_750(mht_))return true;}

    if(ss== cutname[25]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_9(nJets_)&&ht_500_800(ht_)&&mht_200_500(mht_))return true;}
    if(ss== cutname[26]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_9(nJets_)&&ht_800_1200(ht_)&&mht_200_500(mht_))return true;}
    if(ss== cutname[27]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_9(nJets_)&&ht_1200(ht_)&&mht_200_500(mht_))return true;}

    if(ss== cutname[28]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_9(nJets_)&&ht_500_1200(ht_)&&mht_500_750(mht_))return true;}
    if(ss== cutname[29]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_9(nJets_)&&ht_1200(ht_)&&mht_500_750(mht_))return true;}
    if(ss== cutname[30]){if(nolep( nLeptons_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_9(nJets_)&&ht_800(ht_)&&mht_750(mht_))return true;}

  return false;
  }

  bool Selection::checkcut_HadTau(string ss,double ht_,double mht_,double dphi0,double dphi1,double dphi2,int nJets_,int nBtags_,int nLeptons_,int nElecIso_,int nMuIso_,int nPionIso_){

    if(ss == cutname[0])return true;
    if(ss== cutname[1]){if(Njet_4(nJets_))return true;}
    if(ss== cutname[2]){if(Njet_4(nJets_) && ht_500(ht_))return true;}
    if(ss== cutname[3]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_))return true;}
    if(ss== cutname[4]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_))return true;}
    if(ss== cutname[5]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_))return true;}
    if(ss== cutname[6]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_))return true;}
    if(ss== cutname[7]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_))return true;}
    if(ss== cutname[8]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2))return true;}
    if(ss== cutname[9]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&btag_0( nBtags_))return true;}
    if(ss== cutname[10]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&btag_1( nBtags_))return true;}
    if(ss== cutname[11]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&btag_2( nBtags_))return true;}
    if(ss== cutname[12]){if(Njet_4( nJets_)&&ht_500( ht_)&&mht_200( mht_)&&MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&btag_3( nBtags_))return true;}

    // search cuts
    if(ss== cutname[13]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_4_6(nJets_)&&ht_500_800(ht_)&&mht_200_500(mht_))return true;}
    if(ss== cutname[14]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_4_6(nJets_)&&ht_800_1200(ht_)&&mht_200_500(mht_))return true;}
    if(ss== cutname[15]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_4_6(nJets_)&&ht_1200(ht_)&&mht_200_500(mht_))return true;}

    if(ss== cutname[16]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_4_6(nJets_)&&ht_500_1200(ht_)&&mht_500_750(mht_))return true;}
    if(ss== cutname[17]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_4_6(nJets_)&&ht_1200(ht_)&&mht_500_750(mht_))return true;}
    if(ss== cutname[18]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_4_6(nJets_)&&ht_800(ht_)&&mht_750(mht_))return true;}

    if(ss== cutname[19]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_7_8(nJets_)&&ht_500_800(ht_)&&mht_200_500(mht_))return true;}
    if(ss== cutname[20]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_7_8(nJets_)&&ht_800_1200(ht_)&&mht_200_500(mht_))return true;}
    if(ss== cutname[21]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_7_8(nJets_)&&ht_1200(ht_)&&mht_200_500(mht_))return true;}

    if(ss== cutname[22]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_7_8(nJets_)&&ht_500_1200(ht_)&&mht_500_750(mht_))return true;}
    if(ss== cutname[23]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_7_8(nJets_)&&ht_1200(ht_)&&mht_500_750(mht_))return true;}
    if(ss== cutname[24]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_7_8(nJets_)&&ht_800(ht_)&&mht_750(mht_))return true;}

    if(ss== cutname[25]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_9(nJets_)&&ht_500_800(ht_)&&mht_200_500(mht_))return true;}
    if(ss== cutname[26]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_9(nJets_)&&ht_800_1200(ht_)&&mht_200_500(mht_))return true;}
    if(ss== cutname[27]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_9(nJets_)&&ht_1200(ht_)&&mht_200_500(mht_))return true;}

    if(ss== cutname[28]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_9(nJets_)&&ht_500_1200(ht_)&&mht_500_750(mht_))return true;}
    if(ss== cutname[29]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_9(nJets_)&&ht_1200(ht_)&&mht_500_750(mht_))return true;}
    if(ss== cutname[30]){if(MuIsoTrk( nMuIso_)&&ElecIsoTrk(nElecIso_)&&PionIsoTrk(nPionIso_)&&dphi( dphi0,dphi1,dphi2)&&Njet_9(nJets_)&&ht_800(ht_)&&mht_750(mht_))return true;}


  return false;
  }


  map<int, string> Selection::cutName() const {return cutname;}
 

