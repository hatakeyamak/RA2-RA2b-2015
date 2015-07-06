
namespace utils2{


  // Determine which model to work with
    // 0: The most simple model
    // 1: 0 but muon's mother ( W or tau ) is determined using hists not generator info.
    // 2: 1 but for veto(in the prediction code) reco objects are used and not gen ones 
    // 3: 2 but in prediction everything reco. Efficiency used
    // 4: 3 but Acceptance added
    int TauHadModel=4;

  // Do the bootstrapping?
  bool bootstrap = true;

  bool applyMT = true;
  // We calculate MTEff in the same code where it is alos being used. 
  // So, it doesn't make sense to apply MT weight when calculating it.
  // To calc. MT eff. first turn off applyMT and applyIsoTrk but turn on bootstrap and 
  // CalcMT. Save the search bin histogram. Next turn on applyMT and run again. Divide 
  // the two search bin histograms, after and before applyMT. 
  // At the end, turn off CalcMT.
  bool CalcMT =false;

  bool applyIsoTrk = true;


//###############################################################################################################
// Full 72 search bins
//

  // find appropriate bin number for the given (Njet,Nbtag,ht,mht)
      std::string findBin(int njet,int nbtag,double ht,double mht){

        std::ostringstream binS;
        int bNjet, bNbtag, bHtMht;
        if(njet >= 4 && njet <=6)bNjet=1;else if(njet >= 7 && njet <=8)bNjet=2;else if(njet >= 9)bNjet=3;else bNjet=9;
        if(nbtag == 0)bNbtag=1;else if(nbtag==1)bNbtag=2;else if(nbtag == 2)bNbtag=3;else if(nbtag >= 3)bNbtag=4;else bNbtag=9;
        if(ht >= 500 && ht <800 && mht>=200 && mht<500)bHtMht=1;else if(ht >= 800 && ht <1200 && mht>=200 && mht<500)bHtMht=2;else if(ht >= 1200 && mht>=200 && mht<500)bHtMht=3;
        else if(ht >= 500 && ht <1200 && mht>=500 && mht<750)bHtMht=4;else if(ht >=1200 && mht>=500 && mht<750)bHtMht=5;else if(ht >=800 && mht>=750)bHtMht=6; else bHtMht=9;
        binS << 100*bNjet+10*bNbtag+bHtMht ;

        return binS.str();
      }

  // A map is needed between strings like "132" or "2143" that specify the searc bins
  // (see findBin fundtion above) and an integer that can take from 1 to 108 (# of search bins)
  std::map <std::string,int> BinMap(){
      int binN=0;
      std::map <std::string , int> binMap;
      for(int bNjet=1; bNjet<=3;  bNjet++){
        for(int bNbtag=1; bNbtag<=4; bNbtag++){
          for(int bHtMht=1; bHtMht<=6; bHtMht++){
              std::ostringstream binS;
              binS << 100*bNjet+10*bNbtag+bHtMht;
              binN++;
              binMap[binS.str()]=binN;
              std::cout << "binString: " << binS.str() << " corresponing with binNumber: " <<binN << std::endl;
          }
        }
      }
    return binMap;
  }


//############################################################################################
// Search bins integrated over nbtags
//

  // find appropriate bin number for the given (Njet,ht,mht) (and no Btag)

      std::string findBin_NoB(int njet,double ht,double mht){
        std::ostringstream binS;
        int bNjet, bHtMht;
        if(njet >= 4 && njet <=6)bNjet=1;else if(njet >= 7 && njet <=8)bNjet=2;else if(njet >= 9)bNjet=3;else bNjet=9;
        if(ht >= 500 && ht <800 && mht>=200 && mht<500)bHtMht=1;else if(ht >= 800 && ht <1200 && mht>=200 && mht<500)bHtMht=2;else if(ht >= 1200 && mht>=200 && mht<500)bHtMht=3;
        else if(ht >= 500 && ht <1200 && mht>=500 && mht<750)bHtMht=4;else if(ht >=1200 && mht>=500 && mht<750)bHtMht=5;else if(ht >=800 && mht>=750)bHtMht=6; else bHtMht=9;
        binS << 10*bNjet+bHtMht;

        return binS.str();
      }


  // A map is needed between strings like "15" or "24" that specify the search bins ( without Btag)
  // (see findBin fundtion above) and an integer that can take from 1 to 108 (# of search bins)
  std::map <std::string,int> BinMap_NoB(){
      int binN=0;
      std::map <std::string , int> binMap_NoB;
      for(int bNjet=1; bNjet<=3;  bNjet++){
          for(int bHtMht=1; bHtMht<=6; bHtMht++){
              std::ostringstream binS;
              binS << 10*bNjet+bHtMht;
              binN++;
              binMap_NoB[binS.str()]=binN;
              std::cout << "binString: " << binS.str() << " corresponing with binNumber: " <<binN << std::endl;
          }
      }
    return binMap_NoB;
  }


//############################################################################################
// Bins defined by Njet and mht only
//

  // find appropriate bin number for the given (Njet,mht) (and no Btag)

      std::string findBin_mht_nj(int njet,double mht){
        std::ostringstream binS;
        int bNjet, bMht;
        if(njet >= 4 && njet <=6)bNjet=1;else if(njet >= 7 && njet <=8)bNjet=2;else if(njet >= 9)bNjet=3;else bNjet=9;
        if(mht>=200 && mht<500)bMht=1;else if(mht>=500 && mht<750)bMht=2;else if(mht>=750)bMht=3; else bMht=9;
        binS << 10*bNjet+bMht;

        return binS.str();
      }


  // A map is needed between strings like "15" or "24" that specify the search bins ( without Btag)
  // (see findBin fundtion above) and an integer that can take from 1 to 108 (# of search bins)
  std::map <std::string,int> BinMap_mht_nj(){
      int binN=0;
      std::map <std::string , int> binMap_mht_nj;
      for(int bNjet=1; bNjet<=3;  bNjet++){
          for(int bMht=1; bMht<=3; bMht++){
              std::ostringstream binS;
              binS << 10*bNjet+bMht;
              binN++;
              binMap_mht_nj[binS.str()]=binN;
              std::cout << "binString: " << binS.str() << " corresponing with binNumber: " <<binN << std::endl;
          }
      }
    return binMap_mht_nj;
  }



//############################################################################################
// Bins defined by Njet, HT, MHT (no b-tag) used for Iso-track veto parametrization
//

  // find appropriate bin number for the given (Njet,ht,mht) (and no Btag)

      std::string findBin_ForIso(int njet,double ht,double mht){
        std::ostringstream binS;
        int bNjet, bHtMht;
        if(njet >= 4 && njet <=6)bNjet=1;else if(njet >= 7)bNjet=2;else bNjet=9;
        if(ht >= 500 && ht <800 && mht>=200 && mht<500)bHtMht=1;else if(ht >= 800 && ht <1200 && mht>=200 && mht<500)bHtMht=2;else if(ht >= 1200 && mht>=200 && mht<500)bHtMht=3;
        else if(ht >= 500 && mht>=500 )bHtMht=4; else bHtMht=9;
        binS << 10*bNjet+bHtMht;

        return binS.str();
      }


  // A map is needed between strings like "15" or "24" that specify the search bins ( without Btag)
  // (see findBin fundtion above) and an integer that can take from 1 to 108 (# of search bins)
  std::map <std::string,int> BinMap_ForIso(){
      int binN=0;
      std::map <std::string , int> binMap_NoB;
      for(int bNjet=1; bNjet<=2;  bNjet++){
          for(int bHtMht=1; bHtMht<=4; bHtMht++){
              std::ostringstream binS;
              binS << 10*bNjet+bHtMht;
              binN++;
              binMap_NoB[binS.str()]=binN;
              std::cout << "binString: " << binS.str() << " corresponing with binNumber: " <<binN << std::endl;
          }
      }
    return binMap_NoB;
  }


//############################################################################################
// QCD binnings
//

  // find appropriate bin number for the given (Njet,Nbtag,ht,mht)
      std::string findBin_QCD(int njet,int nbtag,double ht,double mht){

        std::ostringstream binS;
        int bNjet, bNbtag, bHtMht;

        if(njet == 4)bNjet=1; else if(njet==5)bNjet=2; else if(njet==6)bNjet=3; else if(njet >= 7 && njet <=8)bNjet=4;else if(njet >= 9)bNjet=5;
        else bNjet=9;

        if(nbtag == 0)bNbtag=1;else if(nbtag==1)bNbtag=2;else if(nbtag == 2)bNbtag=3;else if(nbtag >= 3)bNbtag=4;else bNbtag=9;

        if     (ht >=  500 && ht < 800 && mht>=200 && mht<300) bHtMht=1;
	else if(ht >=  800 && ht <1200 && mht>=200 && mht<300) bHtMht=2;
        else if(ht >= 1200             && mht>=200 && mht<300) bHtMht=3; 
        else if(ht >=  500 && ht < 800 && mht>=300 && mht<500) bHtMht=4;
        else if(ht >=  800 && ht <1200 && mht>=300 && mht<500) bHtMht=5;
        else if(ht >= 1200             && mht>=300 && mht<500) bHtMht=6;
        else if(ht >=  500 && ht <800  && mht>=500 && mht<750) bHtMht=7;
        else if(ht >=  800 && ht <1200 && mht>=500 && mht<750) bHtMht=8;
        else if(ht >= 1200             && mht>=500 && mht<750) bHtMht=9;
        else if(ht >=  800 && ht<1200  && mht>=750)            bHtMht=10;
        else if(ht >= 1200             && mht>=750)            bHtMht=11;
        else bHtMht=19;
        binS << 1000*bNjet+100*bNbtag+bHtMht ;

	//std::cout << ht << " " << mht << " " << njet << " " << nbtag << std::endl;
	//std::cout << bHtMht << " " << bNjet << " " << bNbtag << std::endl;

        return binS.str();
      }

  // A map is needed between strings like "132" or "2143" that specify the searc bins
  // (see findBin fundtion above) and an integer that can take from 1 to 108 (# of search bins)
  std::map <std::string,int> BinMap_QCD(){
      int binN=0;
      std::map <std::string , int> binMap;
      for(int bNjet=1; bNjet<=5;  bNjet++){
        for(int bNbtag=1; bNbtag<=4; bNbtag++){
          for(int bHtMht=1; bHtMht<=11; bHtMht++){
              std::ostringstream binS;
              binS << 1000*bNjet+100*bNbtag+bHtMht;
              binN++;
              binMap[binS.str()]=binN;
              std::cout << "binString: " << binS.str() << " corresponing with binNumber: " <<binN << std::endl;
          }
        }
      }
    return binMap;
  }









}

