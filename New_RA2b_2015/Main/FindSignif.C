#include <cstdio>
#include <map>
#include <cstdio>


using namespace std;

double zbi(double n_on, double mu_b_hat, double sigma_b){

  //double n_on     = 140.;                         // total events in signal region (S+B)
  //double mu_b_hat = 83.33;                        // mean num of BG events expected in sig. region
  //double sigma_b  = 8.333;                        // uncertainty of mu_b_hat

  double tau      = mu_b_hat / (sigma_b*sigma_b); // scale factor to corresp. Noff/Non              
  double n_off    = tau*mu_b_hat;
  double P_Bi     = TMath::BetaIncomplete(1./(1.+tau), n_on, n_off+1);
  double Z_Bi     = sqrt(2.)*TMath::ErfInverse(1 - 2.*P_Bi);
/*
  cout  <<"  total events in signal region (S+B)               - n_on     " <<n_on      <<endl
        <<"  mean num of BG events expected in sig. region     - mu_b_hat " <<mu_b_hat  <<endl
        <<"  uncertainty of mu_b_hat                           - sigma_b  " <<sigma_b   <<endl
        <<"  scale factor to corresp. Noff/Non                 - tau      " <<tau       <<endl
        <<"  tau*mu_b_hat                                      - n_off    " <<n_off     <<endl
        <<"  TMath::BetaIncomplete(1./(1.+tau), n_on, n_off+1) - P_Bi     " <<P_Bi      <<endl
        <<"  sqrt(2.)*TMath::ErfInverse(1 - 2.*P_Bi)           - Z_Bi     " <<Z_Bi      <<endl;
*/
  return Z_Bi;
}

void Order_the_Vec(vector<double> inQvec_, vector<string> inIdvec_, vector<double> &Qvec, vector<string> &Idvec){
  vector<double> inQvec=inQvec_;
  vector<string> inIdvec=inIdvec_;
  int key=1;
  while(key!=0){
    key=0;
    for(int iv=0; iv<((int)inQvec.size()-1);iv++){
      if(inQvec[iv]<inQvec[iv+1]){
        swap(inQvec[iv],inQvec[iv+1]);
        swap(inIdvec[iv],inIdvec[iv+1]);
        key+=1;
      }
    }
  }
  Qvec=inQvec;
  Idvec=inIdvec;
}



void FindSignif(string signalName="T1bbbb_1000_900",string histName="yield_tauId_trk"){

  char tempname[200];

  map <int,string> idMap;
  int IdNum_=0;
  for(int iPile=0;iPile<4;iPile++){
    for(int iIso=0;iIso<4;iIso++){
      for(int iMu=0;iMu<3;iMu++){
        for(int iElec=0;iElec<4;iElec++){
          IdNum_++;
          ostringstream binS_;
          binS_ << (1+iPile)+10*(1+iIso)+100*(1+iMu)+1000*(1+iElec);
          idMap[IdNum_]=binS_.str();
        }
      }
    }
  } 


  TFile * bgFile = new TFile("results_filelist_Spring15_totalBG_.root","R");
  sprintf(tempname,"results_filelist_Spring15_%s_.root",signalName.c_str());
  TFile * sigFile = new TFile(tempname,"R");

  sprintf(tempname,"%s",histName.c_str());
  TH1D * bgHist = (TH1D*)bgFile->Get(tempname)->Clone("bg");
  TH1D * sigHist= (TH1D*)sigFile->Get(tempname)->Clone("sig");


  vector<double> Qvec, inQvec_;
  vector<string> Idvec, inIdvec_;
  map<string,double> bgmap,signalmap,signifmap,zbiimap;
  for (int ibin=1; ibin<=192; ibin++){
    double bg = bgHist->GetBinContent(ibin);
    double signal = sigHist->GetBinContent(ibin);
    double signif = signal/sqrt(bg+0.1*bg);
    double zbii=zbi(signal+bg,bg,0.1*bg);
    double Qmetric=2 * (sqrt(signal+bg) - sqrt(bg) );    
    bgmap[idMap[ibin]]=bg;
    signalmap[idMap[ibin]]=signal;
    signifmap[idMap[ibin]]=signif;
    zbiimap[idMap[ibin]]=zbii;
    inQvec_.push_back(Qmetric);  
    inIdvec_.push_back(idMap[ibin]);
    printf(" ibin %d -> Id: %s => BG: %g Signal: %g significance: %g zbi: %g Qmetric: %g \n ",ibin,idMap[ibin].c_str(),bg,signal,signif,zbii,Qmetric);
  }

  TH1D * pionbgHis = (TH1D*)bgFile->Get("allEvents/isoPion/HT_isoPion_allEvents")->Clone("pionbg");
  TH1D * pionsigHist = (TH1D*)sigFile->Get("allEvents/isoPion/HT_isoPion_allEvents")->Clone("pionsig");
  double pionBG = pionbgHis->GetSumOfWeights();
  double pionSig = pionsigHist->GetSumOfWeights();
  printf("Pion IsoTrk => BG: %g Signal: %g Significance: %g Qmetric: %g \n ",pionBG,pionSig,pionSig/sqrt(1.1*pionBG),2*(sqrt(pionSig+pionBG) - sqrt(pionBG) ));

  Order_the_Vec(inQvec_, inIdvec_, Qvec, Idvec);
  
  for (int ibin=0; ibin<192; ibin++){
    printf(" %s, %1.2f, %1.2f, %7.0f, %7.0f, \n ",Idvec[ibin].c_str(),Qvec[ibin],signifmap[Idvec[ibin]],signalmap[Idvec[ibin]],bgmap[Idvec[ibin]]);
    //printf("Id: %s => Qmetric: %g Significance: %g zbi: %g Signal: %g BG: %g \n ",Idvec[ibin].c_str(),Qvec[ibin],signifmap[Idvec[ibin]],zbiimap[Idvec[ibin]],signalmap[Idvec[ibin]],bgmap[Idvec[ibin]]);
  }

}
