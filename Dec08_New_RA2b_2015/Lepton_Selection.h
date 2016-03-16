
// Event selection helper functions and cut values.
//
// Author: Matthias Schroeder
//         matthias.schroeder@AT@desy.de
//         November 2013

class Lepton_Selection {
public:
  // Returns result of delta-phi selection
  static bool deltaPhi(double dPhi1, double dPhi2, double dPhi3) {
    return dPhi1 > 0.5 && dPhi2 > 0.3 && dPhi3 > 0.3;
  }

  // Returns result of HT baseline selection
  static bool ht(double ht) { return ht > 500.; }

  // Returns result of MHT baseline selection
  static bool mht(double mht) { return mht > 200.; }

  // Returns result of N(jets) baseline selection
  static bool nJets(unsigned int nJets) { return nJets >= 3; }

  // Returns result of search-bin selection (to be applied on top
  // of baseline selection)
  static unsigned int searchBin(double ht, double mht, unsigned int nJets);

  // Cut values for HT jets
  static float htJetPtMin() { return 50.; }
  static float htJetEtaMax() { return 2.5; }

  // Cut values for MHT jets
  static float mhtJetPtMin() { return 30.; }
  static float mhtJetEtaMax() { return 5.0; }

  // Isolation value for Muon
  static double muIso() { return 0.2; }

};


unsigned int Lepton_Selection::searchBin(double ht, double mht, unsigned int nJets) {
  unsigned int bin = 0;

  if( nJets >= 3 && nJets <= 5 ) {
    
    if( ht > 500 && ht < 800 ) {

      if(      mht > 200 && mht < 300 ) bin = 1;
      else if( mht > 300 && mht < 450 ) bin = 2;
      else if( mht > 450 && mht < 600 ) bin = 3;
      else if( mht > 600              ) bin = 4;

    } else if( ht >  800 && ht < 1000 ) {

      if(      mht > 200 && mht < 300 ) bin = 5;
      else if( mht > 300 && mht < 450 ) bin = 6;
      else if( mht > 450 && mht < 600 ) bin = 7;
      else if( mht > 600              ) bin = 8;

    } else if( ht > 1000 && ht < 1250 ) {

      if(      mht > 200 && mht < 300 ) bin = 9;
      else if( mht > 300 && mht < 450 ) bin = 10;
      else if( mht > 450 && mht < 600 ) bin = 11;
      else if( mht > 600              ) bin = 12;

    } else if( ht > 1250 && ht < 1500 ) {

      if(      mht > 200 && mht < 300 ) bin = 13;
      else if( mht > 300 && mht < 450 ) bin = 14;
      else if( mht > 450              ) bin = 15;

    } else if( ht > 1500 ) {

      if(      mht > 200 && mht < 300 ) bin = 16;
      else if( mht > 300              ) bin = 17;

    }

  } else if( nJets >= 6 && nJets <= 7 ) {
    
    if( ht > 500 && ht < 800 ) {

      if(      mht > 200 && mht < 300 ) bin = 18;
      else if( mht > 300 && mht < 450 ) bin = 19;
      else if( mht > 450              ) bin = 20;

    } else if( ht >  800 && ht < 1000 ) {

      if(      mht > 200 && mht < 300 ) bin = 21;
      else if( mht > 300 && mht < 450 ) bin = 22;
      else if( mht > 450              ) bin = 23;

    } else if( ht > 1000 && ht < 1250 ) {

      if(      mht > 200 && mht < 300 ) bin = 24;
      else if( mht > 300 && mht < 450 ) bin = 25;
      else if( mht > 450              ) bin = 26;

    } else if( ht > 1250 && ht < 1500 ) {

      if(      mht > 200 && mht < 300 ) bin = 27;
      else if( mht > 300 && mht < 450 ) bin = 28;
      else if( mht > 450              ) bin = 29;

    } else if( ht > 1500 ) {

      if(      mht > 200 && mht < 300 ) bin = 30;
      else if( mht > 300              ) bin = 31;

    }

  } else if( nJets >= 8 ) {
    
    if( mht > 200 ) {

      if(      ht >  500 && ht <  800 ) bin = 32;
      else if( ht >  800 && ht < 1000 ) bin = 33;
      else if( ht > 1000 && ht < 1250 ) bin = 34;
      else if( ht > 1250 && ht < 1500 ) bin = 35;
      else if( ht > 1500              ) bin = 36;

    }

  }

  return bin;
}

