
namespace utils2{
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


  // find appropriate bin number for the given (Njet,ht,mht) (and no Btag)

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










}
