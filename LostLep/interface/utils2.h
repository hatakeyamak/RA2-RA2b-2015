
namespace utils2{
  // find appropriate bin number for the given (Njet,Nbtag,ht,mht)
      std::string findBin(int njet,int nbtag,double ht,double mht){

        std::ostringstream binS;
        int bNjet, bNbtag, bHt, bMht;
        if(njet >= 4 && njet <=6)bNjet=1;else if(njet >= 7 && njet <=8)bNjet=2;else if(njet >= 9)bNjet=3;else bNjet=9;
        if(nbtag == 0)bNbtag=1;else if(nbtag==1)bNbtag=2;else if(nbtag == 2)bNbtag=3;else if(nbtag >= 3)bNbtag=4;else bNbtag=9;
        if(ht >= 500 && ht <800)bHt=1;else if(ht >= 800 && ht <1200)bHt=2;else if(ht >= 1200)bHt=3;else bHt=9;
        if(mht >= 200 && mht <500)bMht=1;else if(mht >= 500 && mht <750)bMht=2;else if(mht >= 750)bMht=3;else bMht=9;
        binS << 1000*bNjet+100*bNbtag+10*bHt+bMht ;

        return binS.str();
      }

  // A map is needed between strings like "1232" or "2143" that specify the searc bins
  // (see findBin fundtion above) and an integer that can take from 1 to 108 (# of search bins)
  std::map <std::string,int> BinMap(){
      int binN=0;
      std::map <std::string , int> binMap;
      for(int bNjet=1; bNjet<=3;  bNjet++){
        for(int bNbtag=1; bNbtag<=4; bNbtag++){
          for(int bHt=1; bHt<=3; bHt++){
            for(int bMht=1;bMht<=3;bMht++){
              std::ostringstream binS;
              binS << 1000*bNjet+100*bNbtag+10*bHt+bMht ;
              binN++;
              binMap[binS.str()]=binN;
              std::cout << "binString: " << binS.str() << " corresponing with binNumber: " <<binN << std::endl;
            }
          }
        }
      }
    return binMap;
  }






}
