#include <cstdio>
#include <math>

using namespace std;

//
// newLum: luminosity in fb-1, where we want to project our results
// imode:  0: keep the relative stat uncertainty reflecting full MC stat power
//            i.e. both content and error are scale by lumi
//         1: project the stat uncertainy to the targetted luminosity
//            i.e. content is scale by lumi, while scale the error by sqrt(lumi)

Scale_ByLumi(double newLum=3, int imode=1){   // Scale histogram contents and uncertainty to xxx fb^{-1}

  char tempname[200];
  TH1D * temphist;

  const int sampleSize=11;
  string sample[sampleSize]={"TTbar",
			     "WJet_100_200","WJet_200_400","WJet_400_600","WJet_600_inf",
			     "t_top","tW_top","t_antitop","tW_antitop"};

  /*
  TTbar:            806.1 (pb), 
  Wjets HT=100-200: 1.23 * 1817.0 (pb),
  Wjets HT=200-400: 1.23 * 471.6  (pb),
  Wjets HT=400-600: 1.23 * 55.61  (pb),
  Wjets HT=600-inf: 1.23 * 18.81  (pb),
  Single top T_s:       2   (pb)
  Single top Tbar_s:    1   (pb)
  Single top T_t:     103.4 (pb)
  Single top Tbar_t:   61.6 (pb)
  Single top T_tW:     35   (pb)
  Single top Tbar_tW:  35   (pb)
  */
  
  double sample_xsec[sampleSize]={806.1, 
				  1.23*1817.0, 1.23*471.6, 1.23*55.61, 1.23*18.81,
                                  2.,103.4,35.,1.,61.3,35.};  // in pb
  double sample_nevents[sampleSize]={25348009,
				     5257344,4936077,4640594,4581841,
				     500000,3941400,986100,
				     250000,1999800,971800};  // total number of events in ntuples
  double sample_lumi[sampleSize];

  //
  // Looping over different samples
  //
  for(int filei=0;filei<sampleSize;filei++){

    //#######
    // Prediction 
    //#######

    cout << " \n Working on sample: " << sample[filei] << endl;
    sprintf(tempname,"TauHad2/HadTauEstimation_%s_org.root",sample[filei].c_str());
    TFile * file_in  = new TFile(tempname,"READ");
    if (imode==1)      sprintf(tempname,"TauHad2/HadTauEstimation_%s_LumiScaledTo%.1ffbinv.root",sample[filei].c_str(),newLum);
    else if (imode==0) sprintf(tempname,"TauHad2/HadTauEstimation_%s_%.1ffbinv_OrigRelStatError.root",sample[filei].c_str(),newLum);
    else { printf("This mode is not supported\n"); break; }
    TFile * file_out = new TFile(tempname,"UPDATE");

    //#######
    // QCD_Low
    //#######
   
    temphist = (TH1D*) file_in->Get("QCD_Low")->Clone();

    cout << " QCD_Low: Before fix: \n ############### \n ";
    temphist->GetXaxis()->SetRange(1,1);
    if (filei==0) temphist->Print("all");
    else temphist->Print("range");

    //sprintf(tempname,"allEvents/PreSel/MHT_PreSel_allEvents");
    //double nevents_from_root_file = (* (TH1D*)file_in->Get(tempname)).GetEntries();
    sprintf(tempname,"cutflow_preselection");
    double nevents_from_root_file = (* (TH1D*)file_in->Get(tempname)).GetBinContent(1);
  
    double originalSampleLum = nevents_from_root_file / sample_xsec[filei] / 1000.; // original sample luminosity in terms of fb^{-1}
                                                                                   // 1/1000. to convert pb^{-1} to fb^{-1}
    printf("Sample name = %10s, sample lumi = %8.3f, total events = %8.0f, events from allEvent folder = %8.0f\n",
	   sample[filei].c_str(),originalSampleLum,sample_nevents[filei],nevents_from_root_file
	   );

    for (int ibin=0; ibin<temphist->GetNbinsX()+2; ibin++){ // scan including underflow and overflow bins
      double bin=temphist->GetBinContent(ibin);
      temphist->SetBinContent(ibin, bin*newLum/originalSampleLum );
      double binEr=temphist->GetBinError(ibin);
      if (imode==1)      temphist->SetBinError(ibin,   binEr*sqrt(newLum/originalSampleLum) );
      else if (imode==0) temphist->SetBinError(ibin,   binEr*newLum/originalSampleLum );
    }

    cout << " QCD_Low: After fix: \n ############### \n ";
    if (filei==0) temphist->Print("all");
    else temphist->Print("range");
    temphist->GetXaxis()->SetRange();

    temphist->Write();

    //#######
    // QCD_Up
    //#######

    temphist = (TH1D*) file_in->Get("QCD_Up")->Clone();

    cout << " QCD_Up: Before fix: \n ############### \n ";
    temphist->GetXaxis()->SetRange(1,1);
    temphist->Print("range");

    double originalSampleLum = sample_nevents[filei] / sample_xsec[filei] / 1000.; // original sample luminosity in terms of fb^{-1}

    for (int ibin=0; ibin<temphist->GetNbinsX()+2; ibin++){ // scan including underflow and overflow bins
      double bin=temphist->GetBinContent(ibin);
      temphist->SetBinContent(ibin, bin*newLum/originalSampleLum );
      double binEr=temphist->GetBinError(ibin);
      if (imode==1)      temphist->SetBinError(ibin,   binEr*sqrt(newLum/originalSampleLum) );
      else if (imode==0) temphist->SetBinError(ibin,   binEr*newLum/originalSampleLum );
    }

    cout << " QCD_Up: After fix: \n ############### \n ";
    temphist->Print("range");
    temphist->GetXaxis()->SetRange();

    temphist->Write();

    //#######
    // searchH_b
    //#######

    temphist = (TH1D*) file_in->Get("searchH_b")->Clone();

    cout << " searchH_b: Before fix: \n ############### \n ";
    temphist->GetXaxis()->SetRange(1,1);
    temphist->Print("range");

    double originalSampleLum = sample_nevents[filei] / sample_xsec[filei] / 1000.; // original sample luminosity in terms of fb^{-1}

    for (int ibin=0; ibin<temphist->GetNbinsX()+2; ibin++){ // scan including underflow and overflow bins
      double bin=temphist->GetBinContent(ibin);
      temphist->SetBinContent(ibin, bin*newLum/originalSampleLum );
      double binEr=temphist->GetBinError(ibin);
      if (imode==1)      temphist->SetBinError(ibin,   binEr*sqrt(newLum/originalSampleLum) );
      else if (imode==0) temphist->SetBinError(ibin,   binEr*newLum/originalSampleLum );
    }

    cout << " searchH_b: After fix: \n ############### \n ";
    temphist->Print("range");
    temphist->GetXaxis()->SetRange();

    temphist->Write();

    file_out->Close();

  }

  // Expectation

  for(int filei=0;filei<sampleSize;filei++){

    cout << " \n Working on sample: " << sample[filei] << endl;
    sprintf(tempname,"TauHad/GenInfo_HadTauEstimation_%s_org.root",sample[filei].c_str());
    TFile * file_in = new TFile(tempname,"READ");
    if (imode==1)      sprintf(tempname,"TauHad/GenInfo_HadTauEstimation_%s_LumiScaledTo%.1ffbinv.root",sample[filei].c_str(),newLum);
    else if (imode==0) sprintf(tempname,"TauHad/GenInfo_HadTauEstimation_%s_%.1ffbinv_OrigRelStatError.root",sample[filei].c_str(),newLum);
    
    TFile * file_out = new TFile(tempname,"UPDATE");

    //#######
    // QCD_Low
    //#######
   
    temphist = (TH1D*) file_in->Get("QCD_Low")->Clone();

    cout << " QCD_Low: Before fix: \n ############### \n ";
    temphist->GetXaxis()->SetRange(1,1);
    temphist->Print("range");
    
    sprintf(tempname,"cutflow_preselection");
    double nevents_from_root_file = (* (TH1D*)file_in->Get(tempname)).GetBinContent(1);

   double originalSampleLum = nevents_from_root_file / sample_xsec[filei] / 1000.; // original sample luminosity in terms of fb^{-1}
                                                                                   // 1/1000. to convert pb^{-1} to fb^{-1}
    printf("Sample name = %10s, sample lumi = %8.3f, total events = %8.0f, events from allEvent folder = %8.0f\n",
	   sample[filei].c_str(),originalSampleLum,sample_nevents[filei],nevents_from_root_file
	   );

    for (int ibin=0; ibin<temphist->GetNbinsX()+2; ibin++){ // scan including underflow and overflow bins
      double bin=temphist->GetBinContent(ibin);
      temphist->SetBinContent(ibin, bin*newLum/originalSampleLum );
      double binEr=temphist->GetBinError(ibin);
      if (imode==1)      temphist->SetBinError(ibin,   binEr*sqrt(newLum/originalSampleLum) );
      else if (imode==0) temphist->SetBinError(ibin,   binEr*newLum/originalSampleLum );
    }

    cout << " QCD_Low: After fix: \n ############### \n ";
    temphist->Print("range");
    temphist->GetXaxis()->SetRange();

    temphist->Write();

    //#######
    // QCD_Up
    //#######

    temphist = (TH1D*) file_in->Get("QCD_Up")->Clone();

    cout << " QCD_Up: Before fix: \n ############### \n ";
    temphist->GetXaxis()->SetRange(1,1);
    temphist->Print("range");

   double originalSampleLum = sample_nevents[filei] / sample_xsec[filei] / 1000.; // original sample luminosity in terms of fb^{-1}

    for (int ibin=0; ibin<temphist->GetNbinsX()+2; ibin++){ // scan including underflow and overflow bins
      double bin=temphist->GetBinContent(ibin);
      temphist->SetBinContent(ibin, bin*newLum/originalSampleLum );
      double binEr=temphist->GetBinError(ibin);
      if (imode==1)      temphist->SetBinError(ibin,   binEr*sqrt(newLum/originalSampleLum) );
      else if (imode==0) temphist->SetBinError(ibin,   binEr*newLum/originalSampleLum );
    }

    cout << " QCD_Up: After fix: \n ############### \n ";
    temphist->Print("range");
    temphist->GetXaxis()->SetRange();

    temphist->Write();

    //#######
    // searchH_b
    //#######

    temphist = (TH1D*) file_in->Get("searchH_b")->Clone();

    cout << " searchH_b: Before fix: \n ############### \n ";
    temphist->GetXaxis()->SetRange(1,1);
    temphist->Print("range");

   double originalSampleLum = sample_nevents[filei] / sample_xsec[filei] / 1000.; // original sample luminosity in terms of fb^{-1}

    for (int ibin=0; ibin<temphist->GetNbinsX()+2; ibin++){ // scan including underflow and overflow bins
      double bin=temphist->GetBinContent(ibin);
      temphist->SetBinContent(ibin, bin*newLum/originalSampleLum );
      double binEr=temphist->GetBinError(ibin);
      if (imode==1)      temphist->SetBinError(ibin,   binEr*sqrt(newLum/originalSampleLum) );
      else if (imode==0) temphist->SetBinError(ibin,   binEr*newLum/originalSampleLum );
    }

    cout << " searchH_b: After fix: \n ############### \n ";
    temphist->Print("range");
    temphist->GetXaxis()->SetRange();

    temphist->Write();

    file_out->Close();

  }

}
