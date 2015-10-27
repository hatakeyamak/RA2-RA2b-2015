/*

  

 */

void HadTauEstimation_output_format(string elogForData="Elog378_",
				    string elogForMC="Elog377_",
				    string elogForSys="",
				    int isys==0){

  char tempname[200];

  //
  // Open data files
  //
  sprintf(tempname,"TauHad2/%sHadTauEstimation_data_SingleMuon_v15cd_.root",elogForData.c_str());
  TFile *DataEstFile = TFile::Open(tempname,"R");

  //
  // Open MC expectation and prediction code for closure systematics
  // 
  string sample="stacked";

  if(sample.find("stack")==string::npos)sprintf(tempname,"TauHad/%sGenInfo_HadTauEstimation_%s.root",elogForMC.c_str(),sample.c_str());
  else sprintf(tempname,"TauHad/Stack/%sGenInfo_HadTauEstimation_%s.root",elogForMC.c_str(),sample.c_str());
  TFile * MCGenFile = new TFile(tempname,"R");
  printf("Opened %s\n",tempname);

  if(sample.find("stack")==string::npos)sprintf(tempname,"TauHad2/%sHadTauEstimation_%s.root",elogForMC.c_str(),sample.c_str());
  else sprintf(tempname,"TauHad2/Stack/%sHadTauEstimation_%s.root",elogForMC.c_str(),sample.c_str());
  TFile * MCEstFile = new TFile(tempname,"R");
  printf("Opened %s\n",tempname);

  //
  // Open MC file including systematics.
  //
  sprintf(tempname,"TauHad2/Elog381_HadTauEstimation_haddedToContainSysErrorFolders_.root",elogForSys.c_str());
  TFile * MCSysFile = new TFile(tempname,"R");
  printf("Opened %s\n",tempname);

  //
  // ----- Normal 72 bin predicitons -----
  //

  // Nominal
  TH1D* searchBin_nominal = (TH1D*)DataEstFile->Get("searchH_b")->Clone("searchBin_nominal");
  TH2D* hWeightForSearchBin = (TH2D*)DataEstFile->Get("hWeight4ForSearchBin")->Clone("hWeightForSearchBin");
  for (int ibin=0; ibin<searchBin_nominal->GetNbinsX(); ibin++){
    searchBin_nominal->SetBinError(ibin+1,pow(pow(searchBin_nominal->GetBinError(ibin+1),2)+pow(0.275,2),0.5));
  }

  // Jack's inclusive binning
  TH1D* hPredHTMHT0b_nominal_ABbins = (TH1D*)DataEstFile->Get("hPredHTMHT0b")->Clone("hPredHTMHT0b_nominal_ABbins");
  TH1D* hPredHTMHTwb_nominal_ABbins = (TH1D*)DataEstFile->Get("hPredHTMHTwb")->Clone("hPredHTMHTwb_nominal_ABbins");
  TH1D* hPredNJetBins_nominal = (TH1D*)DataEstFile->Get("hPredNJetBins")->Clone("hPredNJetBins_nominal");
  TH1D* hPredNbBins_nominal = (TH1D*)DataEstFile->Get("hPredNbBins")->Clone("hPredNbBins_nominal");
  
  TH1D* hPredHTMHT0b_nominal = new TH1D("hPredHTMHT0b_nominal", ";HTMHT Box;Events / Bin", 6, 0.5, 6.5);
  TH1D* hPredHTMHTwb_nominal = new TH1D("hPredHTMHTwb_nominal", ";HTMHT Box;Events / Bin", 6, 0.5, 6.5);
  for (int ibin=0;ibin<6;ibin++){
    hPredHTMHT0b_nominal->SetBinContent(ibin+1,hPredHTMHT0b_nominal_ABbins->GetBinContent(ibin+1));
    hPredHTMHT0b_nominal->SetBinError(ibin+1,pow(pow(hPredHTMHT0b_nominal_ABbins->GetBinError(ibin+1),2)+pow(0.275,2),0.5));
    hPredHTMHTwb_nominal->SetBinContent(ibin+1,hPredHTMHTwb_nominal_ABbins->GetBinContent(ibin+1));
    hPredHTMHTwb_nominal->SetBinError(ibin+1,pow(pow(hPredHTMHTwb_nominal_ABbins->GetBinError(ibin+1),2)+pow(0.275,2),0.5));
  }
  for (int ibin=0; ibin<hPredNJetBins_nominal->GetNbinsX(); ibin++){
    hPredNJetBins_nominal->SetBinError(ibin+1,pow(pow(hPredNJetBins_nominal->GetBinError(ibin+1),2)+pow(0.275,2),0.5));
  }
  for (int ibin=0; ibin<hPredNbBins_nominal->GetNbinsX(); ibin++){
    hPredNbBins_nominal->SetBinError(ibin+1,pow(pow(hPredNbBins_nominal->GetBinError(ibin+1),2)+pow(0.275,2),0.5));
  }

  // 
  // From MC sys file
  //
  string histname="searchH_b_";
  string cutname="delphi";
  sprintf(tempname,"allEvents/%s/%s",cutname.c_str(),histname.c_str());
  TH1D * searchBin_default = (TH1D*)MCSysFile->Get(tempname)->Clone();

  sprintf(tempname,"BMistagPlus/%s/%s",cutname.c_str(),histname.c_str());  
  TH1D* searchBin_BMistagUp = (TH1D*)MCSysFile->Get(tempname)->Clone("searchBin_BMistagUp");
  sprintf(tempname,"BMistagMinus/%s/%s",cutname.c_str(),histname.c_str());
  TH1D* searchBin_BMistagDn = (TH1D*)MCSysFile->Get(tempname)->Clone("searchBin_BMistagDn");
  searchBin_BMistagUp->Add(searchBin_default,-1.); searchBin_BMistagUp->Divide(searchBin_default);
  searchBin_BMistagDn->Add(searchBin_default,-1.); searchBin_BMistagDn->Divide(searchBin_default);
  
  searchBin_BMistagUp->Print("all");
  searchBin_BMistagDn->Print("all");

  sprintf(tempname,"RecoIsoSysPlus/%s/%s",cutname.c_str(),histname.c_str());  
  TH1D* searchBin_MuRecoIsoSysUp = (TH1D*)MCSysFile->Get(tempname)->Clone("searchBin_MuRecoIsoSysUp");
  sprintf(tempname,"RecoIsoSysMinus/%s/%s",cutname.c_str(),histname.c_str());
  TH1D* searchBin_MuRecoIsoSysDn = (TH1D*)MCSysFile->Get(tempname)->Clone("searchBin_MuRecoIsoSysDn");
  searchBin_MuRecoIsoSysUp->Add(searchBin_default,-1.); searchBin_MuRecoIsoSysUp->Divide(searchBin_default);
  searchBin_MuRecoIsoSysDn->Add(searchBin_default,-1.); searchBin_MuRecoIsoSysDn->Divide(searchBin_default);

  searchBin_MuRecoIsoSysUp->Print("all");
  searchBin_MuRecoIsoSysDn->Print("all");
  
  //
  // From MC file
  //
  TH1D * GenHist, * EstHist,* thist;
  TH1D * histTemplate;
  THStack *tempstack;
  
  // For closure systematics
  string histname="searchH_b";
  sprintf(tempname,"%s",histname.c_str());
  tempstack=(THStack*)MCEstFile->Get(tempname)->Clone();
  EstHist=(TH1D*) tempstack->GetStack()->Last();
  tempstack=(THStack*)MCGenFile->Get(tempname)->Clone();   
  GenHist=(TH1D*) tempstack->GetStack()->Last();
  
  //
  // Preparing ratio histograms: Expectation/Prediction for closure uncertainty
  //
  TH1D * searchBin_closureUncertainty = static_cast<TH1D*>(GenHist->Clone("searchBin_closureUncertainty"));
  searchBin_closureUncertainty->Reset();

  TH1D * closureRatio= static_cast<TH1D*>(GenHist->Clone("closureRatio"));
  TH1D * numerator   = static_cast<TH1D*>(GenHist->Clone("numerator"));

  TH1D * GenHist_Clone = static_cast<TH1D*>(GenHist->Clone("GenHist_Clone"));
  TH1D * EstHist_Clone = static_cast<TH1D*>(EstHist->Clone("EstHist_Clone"));
  closureRatio->Divide(GenHist_Clone,EstHist_Clone,1,1,"");  // Expectation/Prediction-1 - Non closure

  double searchBin_closure_stat_uncertainty_fractional[73];
  int n10percent=0;
  int n30percent=0;
  double avenj1;
  double avenj1nb01;
  double avenj1nb23;
  double avenj2;
  double avenj3;
  for (int ibin=1;ibin<=72;ibin++){
    // Stat uncertainty
    searchBin_closure_stat_uncertainty_fractional[ibin]=0.;
    if (numerator->GetBinContent(ibin)!=0.){
      searchBin_closure_stat_uncertainty_fractional[ibin] = closureRatio->GetBinError(ibin)/closureRatio->GetBinContent(ibin);
    }
    double Unc;
    Unc = TMath::Max(fabs(closureRatio->GetBinContent(ibin)-1.),searchBin_closure_stat_uncertainty_fractional[ibin]);
    if (Unc>1.) Unc=1.;
    searchBin_closureUncertainty->SetBinContent(ibin,Unc);    
    printf("%5d, %8.2f\n",ibin,Unc);
    if (Unc<0.1) n10percent++;
    if (Unc<0.3) n30percent++;
    if (ibin>=1 &&ibin<=24) avenj1+=Unc/24.;
    if (ibin>=1 &&ibin<=12) avenj1nb01+=Unc/12.;
    if (ibin>=13&&ibin<=24) avenj1nb23+=Unc/12.;
    if (ibin>=25&&ibin<=48) avenj2+=Unc/24.;
    if (ibin>=49&&ibin<=72) avenj3+=Unc/24.;
  }
  printf("10percent %5d\n",n10percent);
  printf("30precent %5d\n",n30percent);
  printf("nj1 average=%8.2f\n",avenj1);
  printf("nj1nb01 average=%8.2f\n",avenj1nb01);
  printf("nj1nb23 average=%8.2f\n",avenj1nb23);
  printf("nj2 average=%8.2f\n",avenj2);
  printf("nj3 average=%8.2f\n",avenj3);
  searchBin_closureUncertainty->Print("all");



  
  if (isys==1){
  // Stat uncertainty of search-bin-based correction factors
  TH1D* searchBin_AccUp = (TH1D*)DataEstFile->Get("AccMinus/delphi/searchH_b_")->Clone("searchBin_AccUp");
  TH1D* searchBin_AccDn = (TH1D*)DataEstFile->Get("AccPlus/delphi/searchH_b_")->Clone("searchBin_AccDn");
  TH1D* searchBin_IsoUp = (TH1D*)DataEstFile->Get("IsoPlus/delphi/searchH_b_")->Clone("searchBin_IsoUp");
  TH1D* searchBin_IsoDn = (TH1D*)DataEstFile->Get("IsoMinus/delphi/searchH_b_")->Clone("searchBin_IsoDn");
  TH1D* searchBin_MTUp = (TH1D*)DataEstFile->Get("MTMinus/delphi/searchH_b_")->Clone("searchBin_MTUp");
  TH1D* searchBin_MTDn = (TH1D*)DataEstFile->Get("MTPlus/delphi/searchH_b_")->Clone("searchBin_MTDn");
  TH1D* searchBin_MuFromTauUp = (TH1D*)DataEstFile->Get("MuFromTauMinus/delphi/searchH_b_")->Clone("searchBin_MuFromTauUp");
  TH1D* searchBin_MuFromTauDn = (TH1D*)DataEstFile->Get("MuFromTauPlus/delphi/searchH_b_")->Clone("searchBin_MuFromTauDn");
  
  searchBin_AccUp->Add(searchBin_nominal,-1.); searchBin_AccUp->Divide(searchBin_nominal);
  searchBin_AccDn->Add(searchBin_nominal,-1.); searchBin_AccDn->Divide(searchBin_nominal);
  searchBin_IsoUp->Add(searchBin_nominal,-1.); searchBin_IsoUp->Divide(searchBin_nominal);
  searchBin_IsoDn->Add(searchBin_nominal,-1.); searchBin_IsoDn->Divide(searchBin_nominal);
  searchBin_MTUp->Add(searchBin_nominal,-1.); searchBin_MTUp->Divide(searchBin_nominal);
  searchBin_MTDn->Add(searchBin_nominal,-1.); searchBin_MTDn->Divide(searchBin_nominal);
  searchBin_MuFromTauUp->Add(searchBin_nominal,-1.); searchBin_MuFromTauUp->Divide(searchBin_nominal);
  searchBin_MuFromTauDn->Add(searchBin_nominal,-1.); searchBin_MuFromTauDn->Divide(searchBin_nominal);

  // BMistag
  TH1D* searchBin_BMistagUp = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/searchH_b_")->Clone("searchBin_BMistagUp");
  TH1D* searchBin_BMistagDn = (TH1D*)DataEstFile->Get("BMistagMinus/delphi/searchH_b_")->Clone("searchBin_BMistagDn");
  searchBin_BMistagUp->Add(searchBin_nominal,-1.); searchBin_BMistagUp->Divide(searchBin_nominal);
  searchBin_BMistagDn->Add(searchBin_nominal,-1.); searchBin_BMistagDn->Divide(searchBin_nominal);

  //
  // Closure: 
  // Njets=4-6: 20%
  // Njets=7-8: 40%
  // Njets=9- : 60%
  // MHT2 for Wjets-dominated region: 20%
  // MHT3 for Wjets-dominated region: 40%
  // MHT2 for ttbar-dominated region: 20%
  // MHT3 for ttbar-dominated region: 40%
  double SearchBin_ClosureMHT2Wjets[72]    = {
    -999.,-999.,-999.,  0.2,  0.2,-999., // Njets=4-6
    -999.,-999.,-999.,  0.2,  0.2,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,  0.2,  0.2,-999., // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999., // Njets=9-
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.
  };
  double SearchBin_ClosureMHT3Wjets[72]    = {
    -999.,-999.,-999.,-999.,-999.,  0.4, // Njets=4-6
    -999.,-999.,-999.,-999.,-999.,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,  0.4, // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999., // Njets=9-
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.
  };
  double SearchBin_ClosureMHT2TTbar[72]    = {
    -999.,-999.,-999.,-999.,-999.,-999., // Njets=4-6
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,  0.2,  0.2,-999., 
    -999.,-999.,-999.,  0.2,  0.2,-999.,
    -999.,-999.,-999.,-999.,-999.,-999., // Njets=7-8
    -999.,-999.,-999.,  0.2,  0.2,-999., 
    -999.,-999.,-999.,  0.2,  0.2,-999., 
    -999.,-999.,-999.,  0.2,  0.2,-999., 
    -999.,-999.,-999.,  0.2,  0.2,-999., // Njets=9-
    -999.,-999.,-999.,  0.2,  0.2,-999., 
    -999.,-999.,-999.,  0.2,  0.2,-999., 
    -999.,-999.,-999.,  0.2,  0.2,-999.
  };
  double SearchBin_ClosureMHT3TTbar[72]    = {
    -999.,-999.,-999.,-999.,-999.,-999., // Njets=4-6
    -999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,  0.4,
    -999.,-999.,-999.,-999.,-999.,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999., // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,  0.4,
    -999.,-999.,-999.,-999.,-999.,  0.4,
    -999.,-999.,-999.,-999.,-999.,  0.4,
    -999.,-999.,-999.,-999.,-999.,  0.4, // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,  0.4,
    -999.,-999.,-999.,-999.,-999.,  0.4,
    -999.,-999.,-999.,-999.,-999.,  0.4
  };

  //
  TH1D* searchBin_ClosureNj46 = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/searchH_b_")->Clone("searchBin_ClosureNj46");
  TH1D* searchBin_ClosureNj78 = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/searchH_b_")->Clone("searchBin_ClosureNj78");
  TH1D* searchBin_ClosureNj9  = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/searchH_b_")->Clone("searchBin_ClosureNj9");
  TH1D* searchBin_ClosureMHT2Wjets = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/searchH_b_")->Clone("searchBin_ClosureMHT2Wjets");
  TH1D* searchBin_ClosureMHT3Wjets = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/searchH_b_")->Clone("searchBin_ClosureMHT3Wjets");
  TH1D* searchBin_ClosureMHT2TTbar = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/searchH_b_")->Clone("searchBin_ClosureMHT2TTbar");
  TH1D* searchBin_ClosureMHT3TTbar = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/searchH_b_")->Clone("searchBin_ClosureMHT3TTbar");
  TH1D* searchBin_ClosureTotal = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/searchH_b_")->Clone("searchBin_ClosureTotal");
  searchBin_ClosureNj46->Reset();
  for (int ibin=1;  ibin<=72; ibin++) searchBin_ClosureNj46->SetBinContent(ibin,-999.); // -999. for non-applicable bins
  for (int ibin=1;  ibin<=24; ibin++) searchBin_ClosureNj46->SetBinContent(ibin,0.20);
  searchBin_ClosureNj78->Reset();
  for (int ibin=1;  ibin<=72; ibin++) searchBin_ClosureNj78->SetBinContent(ibin,-999.); // -999. for non-applicable bins
  for (int ibin=25; ibin<=48; ibin++) searchBin_ClosureNj78->SetBinContent(ibin,0.40);
  searchBin_ClosureNj9->Reset();
  for (int ibin=1;  ibin<=72; ibin++) searchBin_ClosureNj9->SetBinContent(ibin,-999.); // -999. for non-applicable bins
  for (int ibin=49; ibin<=72; ibin++) searchBin_ClosureNj9->SetBinContent(ibin,0.60);
  searchBin_ClosureMHT2Wjets->Reset();
  for (int ibin=1;  ibin<=72; ibin++) searchBin_ClosureMHT2Wjets->SetBinContent(ibin,SearchBin_ClosureMHT2Wjets[ibin-1]); // -999. for non-applicable bins
  searchBin_ClosureMHT3Wjets->Reset();
  for (int ibin=1;  ibin<=72; ibin++) searchBin_ClosureMHT3Wjets->SetBinContent(ibin,SearchBin_ClosureMHT3Wjets[ibin-1]); // -999. for non-applicable bins
  searchBin_ClosureMHT2TTbar->Reset();
  for (int ibin=1;  ibin<=72; ibin++) searchBin_ClosureMHT2TTbar->SetBinContent(ibin,SearchBin_ClosureMHT2TTbar[ibin-1]); // -999. for non-applicable bins
  searchBin_ClosureMHT3TTbar->Reset();
  for (int ibin=1;  ibin<=72; ibin++) searchBin_ClosureMHT3TTbar->SetBinContent(ibin,SearchBin_ClosureMHT3TTbar[ibin-1]); // -999. for non-applicable bins

  searchBin_ClosureTotal->Reset();
  for (int ibin=1;  ibin<=72; ibin++){
    //-----
    if (searchBin_ClosureNj46->GetBinContent(ibin)>0.)
      searchBin_ClosureTotal->SetBinContent(ibin,
					    pow(pow(searchBin_ClosureNj46->GetBinContent(ibin),2)+pow(searchBin_ClosureTotal->GetBinContent(ibin),2),0.5)); 
    if (searchBin_ClosureNj78->GetBinContent(ibin)>0.)
      searchBin_ClosureTotal->SetBinContent(ibin,
					    pow(pow(searchBin_ClosureNj78->GetBinContent(ibin),2)+pow(searchBin_ClosureTotal->GetBinContent(ibin),2),0.5)); 
    if (searchBin_ClosureNj9->GetBinContent(ibin)>0.)
      searchBin_ClosureTotal->SetBinContent(ibin,
					    pow(pow(searchBin_ClosureNj9->GetBinContent(ibin),2)+pow(searchBin_ClosureTotal->GetBinContent(ibin),2),0.5)); 
    //-----
    if (searchBin_ClosureMHT2Wjets->GetBinContent(ibin)>0.)
      searchBin_ClosureTotal->SetBinContent(ibin,
					    pow(pow(searchBin_ClosureMHT2Wjets->GetBinContent(ibin),2)+pow(searchBin_ClosureTotal->GetBinContent(ibin),2),0.5)); 
    if (searchBin_ClosureMHT3Wjets->GetBinContent(ibin)>0.)
      searchBin_ClosureTotal->SetBinContent(ibin,
					    pow(pow(searchBin_ClosureMHT3Wjets->GetBinContent(ibin),2)+pow(searchBin_ClosureTotal->GetBinContent(ibin),2),0.5)); 
    if (searchBin_ClosureMHT2TTbar->GetBinContent(ibin)>0.)
      searchBin_ClosureTotal->SetBinContent(ibin,
					    pow(pow(searchBin_ClosureMHT2TTbar->GetBinContent(ibin),2)+pow(searchBin_ClosureTotal->GetBinContent(ibin),2),0.5)); 
    if (searchBin_ClosureMHT3TTbar->GetBinContent(ibin)>0.)
      searchBin_ClosureTotal->SetBinContent(ibin,
					    pow(pow(searchBin_ClosureMHT3TTbar->GetBinContent(ibin),2)+pow(searchBin_ClosureTotal->GetBinContent(ibin),2),0.5)); 
  }

  // Creating template for uncertainty due to correction statistics
  TH1D* searchBin_UncertaintyCorrectionStats = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/searchH_b_")->Clone("searchBin_UncertaintyCorrectionStats");
  searchBin_UncertaintyCorrectionStats->Reset();

  } // isys

  // Some additional variables
  double searchBin_stat_uncertainty_fractional[73];
  double searchBin_uncertainty_correction_stats_up[73];
  double searchBin_uncertainty_correction_stats_dn[73];
  double searchBin_uncertainty_correction_stats[73];

  TH1D* searchBin_StatUncertainties = (TH1D*)DataEstFile->Get("searchH_b")->Clone("searchBin_StatUncertainties");
  searchBin_StatUncertainties->Reset();

  //
  // ----- QCD bin predicitons -----
  //
  TH1D* QCDBin_HiDphi_nominal  = (TH1D*)DataEstFile->Get("QCD_Up")->Clone("QCDBin_HiDphi_nominal");
  //TH1D* QCDBin_LowDphi_nominal = (TH1D*)DataEstFile->Get("QCD_Low")->Clone("QCDBin_LowDPhi_nominal");
  for (int ibin=0; ibin<QCDBin_HiDphi_nominal->GetNbinsX(); ibin++){
    QCDBin_HiDphi_nominal->SetBinError(ibin+1,pow(pow(QCDBin_HiDphi_nominal->GetBinError(ibin+1),2)+pow(0.275,2),0.5));
  }

  searchBin_closureUncertainty->Print("all");

  // For closure systematics
  histname="QCD_Up";
  sprintf(tempname,"%s",histname.c_str());
  tempstack=(THStack*)MCEstFile->Get(tempname)->Clone();
  EstHist=(TH1D*) tempstack->GetStack()->Last();
  tempstack=(THStack*)MCGenFile->Get(tempname)->Clone();   
  GenHist=(TH1D*) tempstack->GetStack()->Last();

  //
  // Preparing ratio histograms: Expectation/Prediction for closure uncertainty
  //
  TH1D * QCDBin_HiDphi_closureUncertainty = static_cast<TH1D*>(GenHist->Clone("QCDBin_HiDphi_closureUncertainty"));
  QCDBin_HiDphi_closureUncertainty->Reset();

  TH1D * QCDBin_HiDphi_closureRatio= static_cast<TH1D*>(GenHist->Clone("QCDBin_HiDphi_closureRatio"));
  TH1D * QCDBin_HiDphi_numerator   = static_cast<TH1D*>(GenHist->Clone("QCDBin_HiDphi_numerator"));

  TH1D * QCDBin_HiDphi_GenHist_Clone = static_cast<TH1D*>(GenHist->Clone("QCDBin_HiDphi_GenHist_Clone"));
  TH1D * QCDBin_HiDphi_EstHist_Clone = static_cast<TH1D*>(EstHist->Clone("QCDBin_HiDphi_EstHist_Clone"));
  QCDBin_HiDphi_closureRatio->Divide(QCDBin_HiDphi_GenHist_Clone,QCDBin_HiDphi_EstHist_Clone,1,1,"");  
  // Expectation/Prediction-1 - Non closure

  double QCDBin_HiDphi_closure_stat_uncertainty_fractional[221];
  for (int ibin=1;ibin<=220;ibin++){
    // Stat uncertainty
    QCDBin_HiDphi_closure_stat_uncertainty_fractional[ibin]=0.;
    if (QCDBin_HiDphi_closureRatio->GetBinContent(ibin)!=0.){
      QCDBin_HiDphi_closure_stat_uncertainty_fractional[ibin] = QCDBin_HiDphi_closureRatio->GetBinError(ibin)/QCDBin_HiDphi_closureRatio->GetBinContent(ibin);
    }
    std::cout << ibin << " "
	      << QCDBin_HiDphi_closureRatio->GetBinContent(ibin)-1. << " "
	      << QCDBin_HiDphi_closure_stat_uncertainty_fractional[ibin] << std::endl;
    double Unc;
    Unc = TMath::Max(fabs(QCDBin_HiDphi_closureRatio->GetBinContent(ibin)-1.),QCDBin_HiDphi_closure_stat_uncertainty_fractional[ibin]);
    if (Unc>1.) Unc=1.;
    QCDBin_HiDphi_closureUncertainty->SetBinContent(ibin,Unc);    
  }
  QCDBin_HiDphi_closureUncertainty->Print("all");


  if (isys==1) {
  // Stat uncertainty of search-bin-based correction factors
  TH1D* QCDBin_HiDphi_AccUp = (TH1D*)DataEstFile->Get("AccMinus/delphi/QCD_")->Clone("QCDBin_HiDphi_AccUp");
  TH1D* QCDBin_HiDphi_AccDn = (TH1D*)DataEstFile->Get("AccPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_AccDn");
  TH1D* QCDBin_HiDphi_IsoUp = (TH1D*)DataEstFile->Get("IsoPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_IsoUp");
  TH1D* QCDBin_HiDphi_IsoDn = (TH1D*)DataEstFile->Get("IsoMinus/delphi/QCD_")->Clone("QCDBin_HiDphi_IsoDn");
  TH1D* QCDBin_HiDphi_MTUp = (TH1D*)DataEstFile->Get("MTMinus/delphi/QCD_")->Clone("QCDBin_HiDphi_MTUp");
  TH1D* QCDBin_HiDphi_MTDn = (TH1D*)DataEstFile->Get("MTPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_MTDn");
  TH1D* QCDBin_HiDphi_MuFromTauUp = (TH1D*)DataEstFile->Get("MuFromTauMinus/delphi/QCD_")->Clone("QCDBin_HiDphi_MuFromTauUp");
  TH1D* QCDBin_HiDphi_MuFromTauDn = (TH1D*)DataEstFile->Get("MuFromTauPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_MuFromTauDn");
  
  QCDBin_HiDphi_AccUp->Add(QCDBin_HiDphi_nominal,-1.); QCDBin_HiDphi_AccUp->Divide(QCDBin_HiDphi_nominal);
  QCDBin_HiDphi_AccDn->Add(QCDBin_HiDphi_nominal,-1.); QCDBin_HiDphi_AccDn->Divide(QCDBin_HiDphi_nominal);
  QCDBin_HiDphi_IsoUp->Add(QCDBin_HiDphi_nominal,-1.); QCDBin_HiDphi_IsoUp->Divide(QCDBin_HiDphi_nominal);
  QCDBin_HiDphi_IsoDn->Add(QCDBin_HiDphi_nominal,-1.); QCDBin_HiDphi_IsoDn->Divide(QCDBin_HiDphi_nominal);
  QCDBin_HiDphi_MTUp->Add(QCDBin_HiDphi_nominal,-1.); QCDBin_HiDphi_MTUp->Divide(QCDBin_HiDphi_nominal);
  QCDBin_HiDphi_MTDn->Add(QCDBin_HiDphi_nominal,-1.); QCDBin_HiDphi_MTDn->Divide(QCDBin_HiDphi_nominal);
  QCDBin_HiDphi_MuFromTauUp->Add(QCDBin_HiDphi_nominal,-1.); QCDBin_HiDphi_MuFromTauUp->Divide(QCDBin_HiDphi_nominal);
  QCDBin_HiDphi_MuFromTauDn->Add(QCDBin_HiDphi_nominal,-1.); QCDBin_HiDphi_MuFromTauDn->Divide(QCDBin_HiDphi_nominal);

  // BMistag
  TH1D* QCDBin_HiDphi_BMistagUp = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_BMistagUp");
  TH1D* QCDBin_HiDphi_BMistagDn = (TH1D*)DataEstFile->Get("BMistagMinus/delphi/QCD_")->Clone("QCDBin_HiDphi_BMistagDn");
  QCDBin_HiDphi_BMistagUp->Add(QCDBin_HiDphi_nominal,-1.); QCDBin_HiDphi_BMistagUp->Divide(QCDBin_HiDphi_nominal);
  QCDBin_HiDphi_BMistagDn->Add(QCDBin_HiDphi_nominal,-1.); QCDBin_HiDphi_BMistagDn->Divide(QCDBin_HiDphi_nominal);

  //
  // Closure: 
  // Njets=4  : 20%
  // Njets=5  : 20%
  // Njets=6  : 20%
  // Njets=7-8: 40%
  // Njets=9- : 60%
  // MHT2 for Wjets-dominated region: 20%
  // MHT3 for Wjets-dominated region: 30%
  // MHT4 for Wjets-dominated region: 40%
  // MHT2 for ttbar-dominated region: 20%
  // MHT3 for ttbar-dominated region: 30%
  // MHT3 for ttbar-dominated region: 40%
  double QCDBinHiDphi_ClosureMHT2Wjets[220]    = {
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., // Njets=4
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., // Njets=5
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., // Njets=6
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=9-
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
  };
  double QCDBinHiDphi_ClosureMHT3Wjets[220]    = {
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., // Njets=4
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., // Njets=5
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., // Njets=6
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=9-
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
  };
  double QCDBinHiDphi_ClosureMHT4Wjets[220]    = {
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4, // Njets=4
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4, // Njets=5
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4, // Njets=6
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4, // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=9-
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
  };
  double QCDBinHiDphi_ClosureMHT2TTbar[220]    = {
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=4
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=5
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=6
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=7-8
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., // Njets=9-
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999.
  };
  double QCDBinHiDphi_ClosureMHT3TTbar[220]    = {
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=4
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=5
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=6
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., // Njets=9-
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999.
  };
  double QCDBinHiDphi_ClosureMHT4TTbar[220]    = {
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=4
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=5
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=6
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4, // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4
  };

  //
  TH1D* QCDBin_HiDphi_ClosureNj4  = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_ClosureNj4");
  TH1D* QCDBin_HiDphi_ClosureNj5  = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_ClosureNj4");
  TH1D* QCDBin_HiDphi_ClosureNj6  = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_ClosureNj4");
  TH1D* QCDBin_HiDphi_ClosureNj78 = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_ClosureNj78");
  TH1D* QCDBin_HiDphi_ClosureNj9  = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_ClosureNj9");
  TH1D* QCDBin_HiDphi_ClosureMHT2Wjets = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_ClosureMHT2Wjets");
  TH1D* QCDBin_HiDphi_ClosureMHT3Wjets = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_ClosureMHT3Wjets");
  TH1D* QCDBin_HiDphi_ClosureMHT4Wjets = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_ClosureMHT4Wjets");
  TH1D* QCDBin_HiDphi_ClosureMHT2TTbar = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_ClosureMHT2TTbar");
  TH1D* QCDBin_HiDphi_ClosureMHT3TTbar = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_ClosureMHT3TTbar");
  TH1D* QCDBin_HiDphi_ClosureMHT4TTbar = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/QCD_")->Clone("QCDBin_HiDphi_ClosureMHT4TTbar");
  QCDBin_HiDphi_ClosureNj4->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_HiDphi_ClosureNj4->SetBinContent(ibin,-999.); // -999. for non-applicable bins
  for (int ibin=1;  ibin<=44; ibin++)  QCDBin_HiDphi_ClosureNj4->SetBinContent(ibin,0.30);
  QCDBin_HiDphi_ClosureNj5->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_HiDphi_ClosureNj5->SetBinContent(ibin,-999.); // -999. for non-applicable bins
  for (int ibin=45; ibin<=88; ibin++)  QCDBin_HiDphi_ClosureNj5->SetBinContent(ibin,0.30);
  QCDBin_HiDphi_ClosureNj6->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_HiDphi_ClosureNj6->SetBinContent(ibin,-999.); // -999. for non-applicable bins
  for (int ibin=89; ibin<=132; ibin++) QCDBin_HiDphi_ClosureNj6->SetBinContent(ibin,0.30);
  QCDBin_HiDphi_ClosureNj78->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_HiDphi_ClosureNj78->SetBinContent(ibin,-999.); // -999. for non-applicable bins
  for (int ibin=133;ibin<=176; ibin++)  QCDBin_HiDphi_ClosureNj78->SetBinContent(ibin,0.40);
  QCDBin_HiDphi_ClosureNj9->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_HiDphi_ClosureNj9->SetBinContent(ibin,-999.); // -999. for non-applicable bins
  for (int ibin=177;ibin<=220; ibin++) QCDBin_HiDphi_ClosureNj9->SetBinContent(ibin,0.60);

  QCDBin_HiDphi_ClosureMHT2Wjets->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_HiDphi_ClosureMHT2Wjets->SetBinContent(ibin,QCDBinHiDphi_ClosureMHT2Wjets[ibin-1]); // -999. for non-applicable bins
  QCDBin_HiDphi_ClosureMHT3Wjets->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_HiDphi_ClosureMHT3Wjets->SetBinContent(ibin,QCDBinHiDphi_ClosureMHT3Wjets[ibin-1]); // -999. for non-applicable bins
  QCDBin_HiDphi_ClosureMHT4Wjets->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_HiDphi_ClosureMHT4Wjets->SetBinContent(ibin,QCDBinHiDphi_ClosureMHT4Wjets[ibin-1]); // -999. for non-applicable bins
  QCDBin_HiDphi_ClosureMHT2TTbar->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_HiDphi_ClosureMHT2TTbar->SetBinContent(ibin,QCDBinHiDphi_ClosureMHT2TTbar[ibin-1]); // -999. for non-applicable bins
  QCDBin_HiDphi_ClosureMHT3TTbar->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_HiDphi_ClosureMHT3TTbar->SetBinContent(ibin,QCDBinHiDphi_ClosureMHT3TTbar[ibin-1]); // -999. for non-applicable bins
  QCDBin_HiDphi_ClosureMHT4TTbar->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_HiDphi_ClosureMHT4TTbar->SetBinContent(ibin,QCDBinHiDphi_ClosureMHT4TTbar[ibin-1]); // -999. for non-applicable bins
  
  // Creating template for uncertainty due to correction statistics
  TH1D* QCDBin_HiDphi_UncertaintyCorrectionStats = (TH1D*)DataEstFile->Get("BMistagPlus/delphi/QCD_")->Clone("QCDBinHiDphi_UncertaintyCorrectionStats");
  QCDBin_HiDphi_UncertaintyCorrectionStats->Reset();

  } // isys==1

  // Some additional variables
  double QCDBinHiDphi_stat_uncertainty_fractional[221];
  double QCDBinHiDphi_uncertainty_correction_stats_up[221];
  double QCDBinHiDphi_uncertainty_correction_stats_dn[221];
  double QCDBinHiDphi_uncertainty_correction_stats[221];

  //
  // ----- QCD bin predicitons -----
  //
  TH1D* QCDBin_LowDphi_nominal = (TH1D*)DataEstFile->Get("QCD_Low")->Clone("QCDBin_LowDPhi_nominal");
  for (int ibin=0; ibin<QCDBin_LowDphi_nominal->GetNbinsX(); ibin++){
    QCDBin_LowDphi_nominal->SetBinError(ibin+1,pow(pow(QCDBin_LowDphi_nominal->GetBinError(ibin+1),2)+pow(0.275,2),0.5));
  }

  // For closure systematics
  histname="QCD_Low";
  sprintf(tempname,"%s",histname.c_str());
  tempstack=(THStack*)MCEstFile->Get(tempname)->Clone();
  EstHist=(TH1D*) tempstack->GetStack()->Last();
  tempstack=(THStack*)MCGenFile->Get(tempname)->Clone();   
  GenHist=(TH1D*) tempstack->GetStack()->Last();

  //
  // Preparing ratio histograms: Expectation/Prediction for closure uncertainty
  //
  TH1D * QCDBin_LowDphi_closureUncertainty = static_cast<TH1D*>(GenHist->Clone("QCDBin_LowDphi_closureUncertainty"));
  QCDBin_LowDphi_closureUncertainty->Reset();

  TH1D * QCDBin_LowDphi_closureRatio= static_cast<TH1D*>(GenHist->Clone("QCDBin_LowDphi_closureRatio"));
  TH1D * QCDBin_LowDphi_numerator   = static_cast<TH1D*>(GenHist->Clone("QCDBin_LowDphi_numerator"));

  TH1D * QCDBin_LowDphi_GenHist_Clone = static_cast<TH1D*>(GenHist->Clone("QCDBin_LowDphi_GenHist_Clone"));
  TH1D * QCDBin_LowDphi_EstHist_Clone = static_cast<TH1D*>(EstHist->Clone("QCDBin_LowDphi_EstHist_Clone"));
  QCDBin_LowDphi_closureRatio->Divide(QCDBin_LowDphi_GenHist_Clone,QCDBin_LowDphi_EstHist_Clone,1,1,"");  
  // Expectation/Prediction-1 - Non closure

  double QCDBin_LowDphi_closure_stat_uncertainty_fractional[221];
  for (int ibin=1;ibin<=220;ibin++){
    // Stat uncertainty
    QCDBin_LowDphi_closure_stat_uncertainty_fractional[ibin]=0.;
    if (QCDBin_LowDphi_closureRatio->GetBinContent(ibin)!=0.){
      QCDBin_LowDphi_closure_stat_uncertainty_fractional[ibin] = QCDBin_LowDphi_closureRatio->GetBinError(ibin)/QCDBin_LowDphi_closureRatio->GetBinContent(ibin);
    }
    std::cout << ibin << " "
	      << QCDBin_LowDphi_closureRatio->GetBinContent(ibin)-1. << " "
	      << QCDBin_LowDphi_closure_stat_uncertainty_fractional[ibin] << std::endl;
    double Unc;
    Unc = TMath::Max(fabs(QCDBin_LowDphi_closureRatio->GetBinContent(ibin)-1.),QCDBin_LowDphi_closure_stat_uncertainty_fractional[ibin]);
    if (Unc>1.) Unc=1.;
    QCDBin_LowDphi_closureUncertainty->SetBinContent(ibin,Unc);    
  }
  QCDBin_LowDphi_closureUncertainty->Print("all");

  if (isys==1){
  // Stat uncertainty of search-bin-based correction factors
  TH1D* QCDBin_LowDphi_AccUp = (TH1D*)DataEstFile->Get("AccMinus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_AccUp");
  TH1D* QCDBin_LowDphi_AccDn = (TH1D*)DataEstFile->Get("AccPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_AccDn");
  TH1D* QCDBin_LowDphi_IsoUp = (TH1D*)DataEstFile->Get("IsoPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_IsoUp");
  TH1D* QCDBin_LowDphi_IsoDn = (TH1D*)DataEstFile->Get("IsoMinus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_IsoDn");
  TH1D* QCDBin_LowDphi_MTUp = (TH1D*)DataEstFile->Get("MTMinus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_MTUp");
  TH1D* QCDBin_LowDphi_MTDn = (TH1D*)DataEstFile->Get("MTPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_MTDn");
  TH1D* QCDBin_LowDphi_MuFromTauUp = (TH1D*)DataEstFile->Get("MuFromTauMinus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_MuFromTauUp");
  TH1D* QCDBin_LowDphi_MuFromTauDn = (TH1D*)DataEstFile->Get("MuFromTauPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_MuFromTauDn");
  
  QCDBin_LowDphi_AccUp->Add(QCDBin_LowDphi_nominal,-1.); QCDBin_LowDphi_AccUp->Divide(QCDBin_LowDphi_nominal);
  QCDBin_LowDphi_AccDn->Add(QCDBin_LowDphi_nominal,-1.); QCDBin_LowDphi_AccDn->Divide(QCDBin_LowDphi_nominal);
  QCDBin_LowDphi_IsoUp->Add(QCDBin_LowDphi_nominal,-1.); QCDBin_LowDphi_IsoUp->Divide(QCDBin_LowDphi_nominal);
  QCDBin_LowDphi_IsoDn->Add(QCDBin_LowDphi_nominal,-1.); QCDBin_LowDphi_IsoDn->Divide(QCDBin_LowDphi_nominal);
  QCDBin_LowDphi_MTUp->Add(QCDBin_LowDphi_nominal,-1.); QCDBin_LowDphi_MTUp->Divide(QCDBin_LowDphi_nominal);
  QCDBin_LowDphi_MTDn->Add(QCDBin_LowDphi_nominal,-1.); QCDBin_LowDphi_MTDn->Divide(QCDBin_LowDphi_nominal);
  QCDBin_LowDphi_MuFromTauUp->Add(QCDBin_LowDphi_nominal,-1.); QCDBin_LowDphi_MuFromTauUp->Divide(QCDBin_LowDphi_nominal);
  QCDBin_LowDphi_MuFromTauDn->Add(QCDBin_LowDphi_nominal,-1.); QCDBin_LowDphi_MuFromTauDn->Divide(QCDBin_LowDphi_nominal);

  // BMistag
  TH1D* QCDBin_LowDphi_BMistagUp = (TH1D*)DataEstFile->Get("BMistagPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_BMistagUp");
  TH1D* QCDBin_LowDphi_BMistagDn = (TH1D*)DataEstFile->Get("BMistagMinus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_BMistagDn");
  QCDBin_LowDphi_BMistagUp->Add(QCDBin_LowDphi_nominal,-1.); QCDBin_LowDphi_BMistagUp->Divide(QCDBin_LowDphi_nominal);
  QCDBin_LowDphi_BMistagDn->Add(QCDBin_LowDphi_nominal,-1.); QCDBin_LowDphi_BMistagDn->Divide(QCDBin_LowDphi_nominal);

  //
  // Closure: 
  // Njets=4  : 20%
  // Njets=5  : 20%
  // Njets=6  : 20%
  // Njets=7-8: 40%
  // Njets=9- : 60%
  // MHT2 for Wjets-dominated region: 20%
  // MHT3 for Wjets-dominated region: 30%
  // MHT4 for Wjets-dominated region: 40%
  // MHT2 for ttbar-dominated region: 20%
  // MHT3 for ttbar-dominated region: 30%
  // MHT3 for ttbar-dominated region: 40%
  double QCDBinLowDphi_ClosureMHT2Wjets[220]    = {
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., // Njets=4
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., // Njets=5
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., // Njets=6
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=9-
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
  };
  double QCDBinLowDphi_ClosureMHT3Wjets[220]    = {
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., // Njets=4
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., // Njets=5
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., // Njets=6
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=9-
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
  };
  double QCDBinLowDphi_ClosureMHT4Wjets[220]    = {
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4, // Njets=4
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4, // Njets=5
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4, // Njets=6
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4, // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=9-
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
  };
  double QCDBinLowDphi_ClosureMHT2TTbar[220]    = {
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=4
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=5
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=6
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=7-8
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., // Njets=9-
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999., 
    -999.,-999.,-999.,  0.2,  0.2,  0.2,-999.,-999.,-999.,-999.,-999.
  };
  double QCDBinLowDphi_ClosureMHT3TTbar[220]    = {
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=4
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=5
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=6
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., // Njets=9-
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999., 
    -999.,-999.,-999.,-999.,-999.,-999.,  0.3,  0.3,  0.3,-999.,-999.
  };
  double QCDBinLowDphi_ClosureMHT4TTbar[220]    = {
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=4
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=5
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=6
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999., // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4, // Njets=7-8
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4,
    -999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,-999.,  0.4,  0.4
  };

  //
  TH1D* QCDBin_LowDphi_ClosureNj4  = (TH1D*)DataEstFile->Get("BMistagPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_ClosureNj4");
  TH1D* QCDBin_LowDphi_ClosureNj5  = (TH1D*)DataEstFile->Get("BMistagPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_ClosureNj4");
  TH1D* QCDBin_LowDphi_ClosureNj6  = (TH1D*)DataEstFile->Get("BMistagPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_ClosureNj4");
  TH1D* QCDBin_LowDphi_ClosureNj78 = (TH1D*)DataEstFile->Get("BMistagPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_ClosureNj78");
  TH1D* QCDBin_LowDphi_ClosureNj9  = (TH1D*)DataEstFile->Get("BMistagPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_ClosureNj9");
  TH1D* QCDBin_LowDphi_ClosureMHT2Wjets = (TH1D*)DataEstFile->Get("BMistagPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_ClosureMHT2Wjets");
  TH1D* QCDBin_LowDphi_ClosureMHT3Wjets = (TH1D*)DataEstFile->Get("BMistagPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_ClosureMHT3Wjets");
  TH1D* QCDBin_LowDphi_ClosureMHT4Wjets = (TH1D*)DataEstFile->Get("BMistagPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_ClosureMHT4Wjets");
  TH1D* QCDBin_LowDphi_ClosureMHT2TTbar = (TH1D*)DataEstFile->Get("BMistagPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_ClosureMHT2TTbar");
  TH1D* QCDBin_LowDphi_ClosureMHT3TTbar = (TH1D*)DataEstFile->Get("BMistagPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_ClosureMHT3TTbar");
  TH1D* QCDBin_LowDphi_ClosureMHT4TTbar = (TH1D*)DataEstFile->Get("BMistagPlus/low_Dphi/QCD_")->Clone("QCDBin_LowDphi_ClosureMHT4TTbar");
  QCDBin_LowDphi_ClosureNj4->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_LowDphi_ClosureNj4->SetBinContent(ibin,-999.); // -999. for non-applicable bins
  for (int ibin=1;  ibin<=44; ibin++)  QCDBin_LowDphi_ClosureNj4->SetBinContent(ibin,0.30);
  QCDBin_LowDphi_ClosureNj5->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_LowDphi_ClosureNj5->SetBinContent(ibin,-999.); // -999. for non-applicable bins
  for (int ibin=45; ibin<=88; ibin++)  QCDBin_LowDphi_ClosureNj5->SetBinContent(ibin,0.30);
  QCDBin_LowDphi_ClosureNj6->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_LowDphi_ClosureNj6->SetBinContent(ibin,-999.); // -999. for non-applicable bins
  for (int ibin=89; ibin<=132; ibin++) QCDBin_LowDphi_ClosureNj6->SetBinContent(ibin,0.30);
  QCDBin_LowDphi_ClosureNj78->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_LowDphi_ClosureNj78->SetBinContent(ibin,-999.); // -999. for non-applicable bins
  for (int ibin=133;ibin<=176; ibin++)  QCDBin_LowDphi_ClosureNj78->SetBinContent(ibin,0.40);
  QCDBin_LowDphi_ClosureNj9->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_LowDphi_ClosureNj9->SetBinContent(ibin,-999.); // -999. for non-applicable bins
  for (int ibin=177;ibin<=220; ibin++) QCDBin_LowDphi_ClosureNj9->SetBinContent(ibin,0.60);

  QCDBin_LowDphi_ClosureMHT2Wjets->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_LowDphi_ClosureMHT2Wjets->SetBinContent(ibin,QCDBinLowDphi_ClosureMHT2Wjets[ibin-1]); // -999. for non-applicable bins
  QCDBin_LowDphi_ClosureMHT3Wjets->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_LowDphi_ClosureMHT3Wjets->SetBinContent(ibin,QCDBinLowDphi_ClosureMHT3Wjets[ibin-1]); // -999. for non-applicable bins
  QCDBin_LowDphi_ClosureMHT4Wjets->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_LowDphi_ClosureMHT4Wjets->SetBinContent(ibin,QCDBinLowDphi_ClosureMHT4Wjets[ibin-1]); // -999. for non-applicable bins
  QCDBin_LowDphi_ClosureMHT2TTbar->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_LowDphi_ClosureMHT2TTbar->SetBinContent(ibin,QCDBinLowDphi_ClosureMHT2TTbar[ibin-1]); // -999. for non-applicable bins
  QCDBin_LowDphi_ClosureMHT3TTbar->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_LowDphi_ClosureMHT3TTbar->SetBinContent(ibin,QCDBinLowDphi_ClosureMHT3TTbar[ibin-1]); // -999. for non-applicable bins
  QCDBin_LowDphi_ClosureMHT4TTbar->Reset();
  for (int ibin=1;  ibin<=220; ibin++) QCDBin_LowDphi_ClosureMHT4TTbar->SetBinContent(ibin,QCDBinLowDphi_ClosureMHT4TTbar[ibin-1]); // -999. for non-applicable bins

  // Creating template for uncertainty due to correction statistics
  TH1D* QCDBin_LowDphi_UncertaintyCorrectionStats = (TH1D*)DataEstFile->Get("BMistagPlus/low_Dphi/QCD_")->Clone("QCDBinLowDphi_UncertaintyCorrectionStats");
  QCDBin_LowDphi_UncertaintyCorrectionStats->Reset();

  } // isys==1
  
  // Some additional variables
  double QCDBinLowDphi_stat_uncertainty_fractional[221];
  double QCDBinLowDphi_uncertainty_correction_stats_up[221];
  double QCDBinLowDphi_uncertainty_correction_stats_dn[221];
  double QCDBinLowDphi_uncertainty_correction_stats[221];

  for (int ibin=1;ibin<=72;ibin++){
    // Stat uncertainty
    searchBin_stat_uncertainty_fractional[ibin]=0.;
    if (searchBin_nominal->GetBinContent(ibin)!=0.){
      searchBin_stat_uncertainty_fractional[ibin] = searchBin_nominal->GetBinError(ibin)/searchBin_nominal->GetBinContent(ibin);
      searchBin_StatUncertainties->SetBinContent(ibin,searchBin_stat_uncertainty_fractional[ibin]);
    }
  }

  for (int ibin=1;ibin<=220;ibin++){
    //
    // Stat uncertainty
    QCDBinHiDphi_stat_uncertainty_fractional[ibin]=0.;
    if (QCDBin_HiDphi_nominal->GetBinContent(ibin)!=0.)
      QCDBinHiDphi_stat_uncertainty_fractional[ibin] = QCDBin_HiDphi_nominal->GetBinError(ibin)/QCDBin_HiDphi_nominal->GetBinContent(ibin);    
    //
    // Stat uncertainty
    QCDBinLowDphi_stat_uncertainty_fractional[ibin]=0.;
    if (QCDBin_LowDphi_nominal->GetBinContent(ibin)!=0.)
      QCDBinLowDphi_stat_uncertainty_fractional[ibin] = QCDBin_LowDphi_nominal->GetBinError(ibin)/QCDBin_LowDphi_nominal->GetBinContent(ibin);
  }

  if (isys==1){
  //-----------------------------------------------------------------------------------------------------------------------------------------------------
  //
  // Check Individual Components - regular search bins
  // 
  printf("\n");
  printf("------------------------------------------------------------------------------------------------------------------------\n");
  printf("Search bin");
  printf("------------------------------------------------------------------------------------------------------------------------\n");
  printf("bin#: Prediction:Stat(Frac): Acc Up/Dn  : Iso Up/Dn     : MT Up/Dn      : Mu Up/Dn    : Total from Correction Stats\n");
  for (int ibin=1;ibin<=72;ibin++){
    if (ibin==1 || ibin==25 || ibin==49) 
      printf("------------------------------------------------------------------------------------------------------------------------\n");
    //
    // Uncertainty from correction statistics
    searchBin_uncertainty_correction_stats_up[ibin]=pow(pow(searchBin_AccUp->GetBinContent(ibin),2)
					      +pow(searchBin_IsoUp->GetBinContent(ibin),2)
					      +pow(searchBin_MTUp->GetBinContent(ibin),2)
					      +pow(searchBin_MuFromTauUp->GetBinContent(ibin),2)
					     ,0.5);
    searchBin_uncertainty_correction_stats_dn[ibin]=pow(pow(searchBin_AccUp->GetBinContent(ibin),2)
					      +pow(searchBin_IsoUp->GetBinContent(ibin),2)
					      +pow(searchBin_MTUp->GetBinContent(ibin),2)
					      +pow(searchBin_MuFromTauUp->GetBinContent(ibin),2)
					     ,0.5);
    searchBin_uncertainty_correction_stats[ibin]=(searchBin_uncertainty_correction_stats_up[ibin]+searchBin_uncertainty_correction_stats_dn[ibin])/2.;
    searchBin_UncertaintyCorrectionStats->SetBinContent(ibin,searchBin_uncertainty_correction_stats[ibin]);
    //
    printf("%4d: %10.3f: %6.3f: %6.3f, %6.3f: %6.3f, %6.3f: %6.3f, %6.3f: %6.3f, %6.3f: %8.3f\n",
	   ibin,
	   searchBin_nominal->GetBinContent(ibin),
	   searchBin_stat_uncertainty_fractional[ibin],
	   searchBin_AccUp->GetBinContent(ibin),
	   searchBin_AccDn->GetBinContent(ibin),
	   searchBin_IsoUp->GetBinContent(ibin),
	   searchBin_IsoDn->GetBinContent(ibin),
	   searchBin_MTUp->GetBinContent(ibin),
	   searchBin_MTDn->GetBinContent(ibin),
	   searchBin_MuFromTauUp->GetBinContent(ibin),
	   searchBin_MuFromTauDn->GetBinContent(ibin),
	   searchBin_UncertaintyCorrectionStats->GetBinContent(ibin)
	   );
  }
  printf("------------------------------------------------------------------------------------------------------------------------\n");

  //
  // After some grouping
  // 
  printf("\n");
  printf("------------------------------------------------------------------------------------------------------------------------\n");
  printf("bin#: Prediction:Stat(Frac):BMistag Up/Dn: From Corr Stats: Closure Njets=4-6,7-8,9-,MHT2Wjets,MHT3Wjets,MHT2TTbar,MHT3TTbar\n");
  for (int ibin=1;ibin<=72;ibin++){
    if (ibin==1 || ibin==25 || ibin==49) 
      printf("------------------------------------------------------------------------------------------------------------------------\n");
    //
    printf("%4d: %10.3f: %6.3f:  %6.3f, %6.3f: %8.3f: %8.3f, %8.3f, %8.3f, %8.3f, %8.3f, %8.3f, %8.3f\n",
	   ibin,
	   searchBin_nominal->GetBinContent(ibin),
	   searchBin_stat_uncertainty_fractional[ibin],
	   searchBin_BMistagUp->GetBinContent(ibin),
	   searchBin_BMistagDn->GetBinContent(ibin),
	   searchBin_UncertaintyCorrectionStats->GetBinContent(ibin),
	   searchBin_ClosureNj46->GetBinContent(ibin),
	   searchBin_ClosureNj78->GetBinContent(ibin),
	   searchBin_ClosureNj9->GetBinContent(ibin),
	   searchBin_ClosureMHT2Wjets->GetBinContent(ibin),
	   searchBin_ClosureMHT3Wjets->GetBinContent(ibin),
	   searchBin_ClosureMHT2TTbar->GetBinContent(ibin),
	   searchBin_ClosureMHT3TTbar->GetBinContent(ibin)
	   );
  }
  printf("------------------------------------------------------------------------------------------------------------------------\n");

  //-----------------------------------------------------------------------------------------------------------------------------------------------------
  // 
  // Displaying errors
  //
  TCanvas *tc1 = new TCanvas("searchBin_UncertaintySummary","searchBin_UncertaintySummary",1200,600);
  searchBin_StatUncertainties->SetMaximum(1.5);
  searchBin_StatUncertainties->SetMinimum(-0.5);
  searchBin_StatUncertainties->SetStats(false);
  searchBin_StatUncertainties->SetTitle("Uncertainties versus search bins");
  searchBin_StatUncertainties->GetXaxis()->SetTitle("Search bin");
  searchBin_StatUncertainties->GetYaxis()->SetTitle("Fractional uncertainties");
  searchBin_StatUncertainties->SetLineColor(1);
  searchBin_StatUncertainties->Draw();
  searchBin_StatUncertainties->SetFillColor(21);
  
  searchBin_ClosureTotal->SetLineColor(6);
  searchBin_ClosureTotal->SetLineWidth(2);
  searchBin_ClosureTotal->Draw("same");

  searchBin_BMistagUp->SetLineColor(2);
  searchBin_BMistagUp->SetLineWidth(2);
  searchBin_BMistagUp->Draw("hist,same");

  searchBin_UncertaintyCorrectionStats->SetLineColor(4);
  searchBin_UncertaintyCorrectionStats->SetLineWidth(2);
  searchBin_UncertaintyCorrectionStats->Draw("same");

  //
  // Drawing lines
  TLine *tlzero = new TLine(1.,0.,73.,0.);
  tlzero->SetLineStyle(2);
  tlzero->SetLineColor(4);
  tlzero->Draw();

  float ymax_bottom = 1.4;
  float ymax2_bottom = 1.3;
  float ymax3_bottom = 1.3;
  float ymax4_bottom = 1.3;
  float ymin_bottom = -0.5;

  TLine *tline_bottom_1 = new TLine(25.,ymin_bottom,25.,ymax_bottom);
  tline_bottom_1->SetLineStyle(2);
  tline_bottom_1->Draw();
  
  TLine *tline_bottom_2 = new TLine(49.,ymin_bottom,49.,ymax_bottom);
  tline_bottom_2->SetLineStyle(2);
  tline_bottom_2->Draw();

  TLine *tline_bottom_1a = new TLine(7.,ymin_bottom,7.,ymax2_bottom);
  tline_bottom_1a->SetLineStyle(3);
  tline_bottom_1a->Draw();
  TLine *tline_bottom_1b = new TLine(13.,ymin_bottom,13.,ymax2_bottom);
  tline_bottom_1b->SetLineStyle(3);
  tline_bottom_1b->Draw();
  TLine *tline_bottom_1c = new TLine(19.,ymin_bottom,19.,ymax2_bottom);
  tline_bottom_1c->SetLineStyle(3);
  tline_bottom_1c->Draw();

  TLine *tline_bottom_2a = new TLine(31.,ymin_bottom,31.,ymax3_bottom);
  tline_bottom_2a->SetLineStyle(3);
  tline_bottom_2a->Draw();
  TLine *tline_bottom_2b = new TLine(37.,ymin_bottom,37.,ymax3_bottom);
  tline_bottom_2b->SetLineStyle(3);
  tline_bottom_2b->Draw();
  TLine *tline_bottom_2c = new TLine(43.,ymin_bottom,43.,ymax3_bottom);
  tline_bottom_2c->SetLineStyle(3);
  tline_bottom_2c->Draw();
      
  TLine *tline_bottom_3a = new TLine(55.,ymin_bottom,55.,ymax4_bottom);
  tline_bottom_3a->SetLineStyle(3);
  tline_bottom_3a->Draw();
  TLine *tline_bottom_3b = new TLine(61.,ymin_bottom,61.,ymax4_bottom);
  tline_bottom_3b->SetLineStyle(3);
  tline_bottom_3b->Draw();
  TLine *tline_bottom_3c = new TLine(67.,ymin_bottom,67.,ymax4_bottom);
  tline_bottom_3c->SetLineStyle(3);
  tline_bottom_3c->Draw();

  //
  // Legend & texts
  TLatex * ttext1 = new TLatex(13. , ymax_bottom , "4 #leq N_{jets} #leq 6");
  ttext1->SetTextFont(42);
  ttext1->SetTextSize(0.04);
  ttext1->SetTextAlign(22);
  ttext1->Draw();

  TLatex * ttext2 = new TLatex(37. , ymax_bottom , "7 #leq N_{jets} #leq 8");
  ttext2->SetTextFont(42);
  ttext2->SetTextSize(0.04);
  ttext2->SetTextAlign(22);
  ttext2->Draw();

  TLatex * ttext3 = new TLatex(61. , ymax_bottom , "N_{jets} #geq 9");
  ttext3->SetTextFont(42);
  ttext3->SetTextSize(0.04);
  ttext3->SetTextAlign(22);
  ttext3->Draw();

  TLatex * ttext1a = new TLatex(4. , ymax2_bottom-0.1 , "N_{b} = 0");
  ttext1a->SetTextFont(42);
  ttext1a->SetTextSize(0.04);
  ttext1a->SetTextAlign(22);
  ttext1a->Draw();
  
  TLatex * ttext1b = new TLatex(10. , ymax2_bottom-0.1 , "N_{b} = 1");
  ttext1b->SetTextFont(42);
  ttext1b->SetTextSize(0.04);
  ttext1b->SetTextAlign(22);
  ttext1b->Draw();
  
  TLatex * ttext1c = new TLatex(16. , ymax2_bottom-0.1 , "N_{b} = 2");
  ttext1c->SetTextFont(42);
  ttext1c->SetTextSize(0.04);
  ttext1c->SetTextAlign(22);
  ttext1c->Draw();
  
  TLatex * ttext1d = new TLatex(22. , ymax2_bottom-0.1 , "N_{b} #geq 3");
  ttext1d->SetTextFont(42);
  ttext1d->SetTextSize(0.04);
  ttext1d->SetTextAlign(22);
  ttext1d->Draw();

  //
  //
  //
  Float_t legendX1 = .25; //.50;
  Float_t legendX2 = .45; //.70;
  Float_t legendY1 = .13; //.65;
  Float_t legendY2 = .28; //

  TLegend* catLeg1 = new TLegend(legendX1,legendY1,legendX2,legendY2);
  catLeg1->SetTextSize(0.032);
  catLeg1->SetTextFont(42);
  catLeg1->SetFillColor(0);
  catLeg1->SetLineColor(0);
  catLeg1->SetBorderSize(0);

  sprintf(tempname,"Data stat uncertainties");
  catLeg1->AddEntry(searchBin_StatUncertainties,tempname);
  sprintf(tempname,"MC stat uncertainties on corrections");
  catLeg1->AddEntry(searchBin_UncertaintyCorrectionStats,tempname);
  sprintf(tempname,"B-tag mistag modeling uncertainties");
  catLeg1->AddEntry(searchBin_BMistagUp,tempname);
  sprintf(tempname,"Total non-closure uncertainties (tentative)");
  catLeg1->AddEntry(searchBin_ClosureTotal,tempname);
  catLeg1->Draw();

  sprintf(tempname,"searchBin_UncertaintySummary.png");
  sprintf(tempname,"searchBin_UncertaintySummary.pdf");
  

  //-----------------------------------------------------------------------------------------------------------------------------------------------------
  //
  // QCD HiDphi -
  // 
  printf("\n");
  printf("------------------------------------------------------------------------------------------------------------------------\n");
  printf("QCD bin HiDphi");
  printf("------------------------------------------------------------------------------------------------------------------------\n");
  printf("bin#: Prediction:Stat(Frac): Acc Up/Dn  : Iso Up/Dn     : MT Up/Dn      : Mu Up/Dn    : Total from Correction Stats\n");
  for (int ibin=1;ibin<=220;ibin++){
    if (ibin==1 || ibin==45 || ibin==89 || ibin==133 || ibin==177) 
      printf("------------------------------------------------------------------------------------------------------------------------\n");
    //
    // Uncertainty from correction statistics
    QCDBinHiDphi_uncertainty_correction_stats_up[ibin]=pow(pow(QCDBin_HiDphi_AccUp->GetBinContent(ibin),2)
					      +pow(QCDBin_HiDphi_IsoUp->GetBinContent(ibin),2)
					      +pow(QCDBin_HiDphi_MTUp->GetBinContent(ibin),2)
					      +pow(QCDBin_HiDphi_MuFromTauUp->GetBinContent(ibin),2)
					     ,0.5);
    QCDBinHiDphi_uncertainty_correction_stats_dn[ibin]=pow(pow(QCDBin_HiDphi_AccUp->GetBinContent(ibin),2)
					      +pow(QCDBin_HiDphi_IsoUp->GetBinContent(ibin),2)
					      +pow(QCDBin_HiDphi_MTUp->GetBinContent(ibin),2)
					      +pow(QCDBin_HiDphi_MuFromTauUp->GetBinContent(ibin),2)
					     ,0.5);
    QCDBinHiDphi_uncertainty_correction_stats[ibin]=(QCDBinHiDphi_uncertainty_correction_stats_up[ibin]+QCDBinHiDphi_uncertainty_correction_stats_dn[ibin])/2.;
    QCDBin_HiDphi_UncertaintyCorrectionStats->SetBinContent(ibin,QCDBinHiDphi_uncertainty_correction_stats[ibin]);
    //
    printf("%4d: %10.3f: %6.3f: %6.3f, %6.3f: %6.3f, %6.3f: %6.3f, %6.3f: %6.3f, %6.3f: %8.3f\n",
	   ibin,
	   QCDBin_HiDphi_nominal->GetBinContent(ibin),
	   QCDBinHiDphi_stat_uncertainty_fractional[ibin],
	   QCDBin_HiDphi_AccUp->GetBinContent(ibin),
	   QCDBin_HiDphi_AccDn->GetBinContent(ibin),
	   QCDBin_HiDphi_IsoUp->GetBinContent(ibin),
	   QCDBin_HiDphi_IsoDn->GetBinContent(ibin),
	   QCDBin_HiDphi_MTUp->GetBinContent(ibin),
	   QCDBin_HiDphi_MTDn->GetBinContent(ibin),
	   QCDBin_HiDphi_MuFromTauUp->GetBinContent(ibin),
	   QCDBin_HiDphi_MuFromTauDn->GetBinContent(ibin),
	   QCDBin_HiDphi_UncertaintyCorrectionStats->GetBinContent(ibin)
	   );
  }
  printf("------------------------------------------------------------------------------------------------------------------------\n");

  //
  // After some grouping
  // 
  printf("\n");
  printf("------------------------------------------------------------------------------------------------------------------------\n");
  printf("bin#: Prediction:Stat(Frac):BMistag Up/Dn: From Corr Stats: Closure Njets=4,5,6,7-8,9-,MHT2Wjets,MHT3Wjets,MHT2TTbar,MHT3TTbar\n");
  for (int ibin=1;ibin<=220;ibin++){
    if (ibin==1 || ibin==45 || ibin==89 || ibin==133 || ibin==177) 
      printf("------------------------------------------------------------------------------------------------------------------------\n");
    //
    printf("%4d: %10.3f: %6.3f:  %6.3f, %6.3f: %8.3f: %8.3f, %8.3f, %8.3f, %8.3f, %8.3f, %8.3f, %8.3f, %8.3f, %8.3f, %8.3f, %8.3f\n",
	   ibin,
	   QCDBin_HiDphi_nominal->GetBinContent(ibin),
	   QCDBinHiDphi_stat_uncertainty_fractional[ibin],
	   QCDBin_HiDphi_BMistagUp->GetBinContent(ibin),
	   QCDBin_HiDphi_BMistagDn->GetBinContent(ibin),
	   QCDBin_HiDphi_UncertaintyCorrectionStats->GetBinContent(ibin),
	   QCDBin_HiDphi_ClosureNj4->GetBinContent(ibin),
	   QCDBin_HiDphi_ClosureNj5->GetBinContent(ibin),
	   QCDBin_HiDphi_ClosureNj6->GetBinContent(ibin),
	   QCDBin_HiDphi_ClosureNj78->GetBinContent(ibin),
	   QCDBin_HiDphi_ClosureNj9->GetBinContent(ibin),
	   QCDBin_HiDphi_ClosureMHT2Wjets->GetBinContent(ibin),
	   QCDBin_HiDphi_ClosureMHT3Wjets->GetBinContent(ibin),
	   QCDBin_HiDphi_ClosureMHT4Wjets->GetBinContent(ibin),
	   QCDBin_HiDphi_ClosureMHT2TTbar->GetBinContent(ibin),
	   QCDBin_HiDphi_ClosureMHT3TTbar->GetBinContent(ibin),
	   QCDBin_HiDphi_ClosureMHT4TTbar->GetBinContent(ibin)
	   );
  }
  printf("------------------------------------------------------------------------------------------------------------------------\n");
 
  //-----------------------------------------------------------------------------------------------------------------------------------------------------
  //
  // QCD LowDphi -
  // 
  printf("\n");
  printf("------------------------------------------------------------------------------------------------------------------------\n");
  printf("QCD bin LowDphi");
  printf("------------------------------------------------------------------------------------------------------------------------\n");
  printf("bin#: Prediction:Stat(Frac): Acc Up/Dn  : Iso Up/Dn     : MT Up/Dn      : Mu Up/Dn    : Total from Correction Stats\n");
  for (int ibin=1;ibin<=220;ibin++){
    if (ibin==1 || ibin==45 || ibin==89 || ibin==133 || ibin==177) 
      printf("------------------------------------------------------------------------------------------------------------------------\n");
    //
    // Uncertainty from correction statistics
    QCDBinLowDphi_uncertainty_correction_stats_up[ibin]=pow(pow(QCDBin_LowDphi_AccUp->GetBinContent(ibin),2)
					      +pow(QCDBin_LowDphi_IsoUp->GetBinContent(ibin),2)
					      +pow(QCDBin_LowDphi_MTUp->GetBinContent(ibin),2)
					      +pow(QCDBin_LowDphi_MuFromTauUp->GetBinContent(ibin),2)
					     ,0.5);
    QCDBinLowDphi_uncertainty_correction_stats_dn[ibin]=pow(pow(QCDBin_LowDphi_AccUp->GetBinContent(ibin),2)
					      +pow(QCDBin_LowDphi_IsoUp->GetBinContent(ibin),2)
					      +pow(QCDBin_LowDphi_MTUp->GetBinContent(ibin),2)
					      +pow(QCDBin_LowDphi_MuFromTauUp->GetBinContent(ibin),2)
					     ,0.5);
    QCDBinLowDphi_uncertainty_correction_stats[ibin]=(QCDBinLowDphi_uncertainty_correction_stats_up[ibin]+QCDBinLowDphi_uncertainty_correction_stats_dn[ibin])/2.;
    QCDBin_LowDphi_UncertaintyCorrectionStats->SetBinContent(ibin,QCDBinLowDphi_uncertainty_correction_stats[ibin]);
    //
    printf("%4d: %10.3f: %6.3f: %6.3f, %6.3f: %6.3f, %6.3f: %6.3f, %6.3f: %6.3f, %6.3f: %8.3f\n",
	   ibin,
	   QCDBin_LowDphi_nominal->GetBinContent(ibin),
	   QCDBinLowDphi_stat_uncertainty_fractional[ibin],
	   QCDBin_LowDphi_AccUp->GetBinContent(ibin),
	   QCDBin_LowDphi_AccDn->GetBinContent(ibin),
	   QCDBin_LowDphi_IsoUp->GetBinContent(ibin),
	   QCDBin_LowDphi_IsoDn->GetBinContent(ibin),
	   QCDBin_LowDphi_MTUp->GetBinContent(ibin),
	   QCDBin_LowDphi_MTDn->GetBinContent(ibin),
	   QCDBin_LowDphi_MuFromTauUp->GetBinContent(ibin),
	   QCDBin_LowDphi_MuFromTauDn->GetBinContent(ibin),
	   QCDBin_LowDphi_UncertaintyCorrectionStats->GetBinContent(ibin)
	   );
  }
  printf("------------------------------------------------------------------------------------------------------------------------\n");

  //
  // After some grouping
  // 
  printf("\n");
  printf("------------------------------------------------------------------------------------------------------------------------\n");
  printf("bin#: Prediction:Stat(Frac):BMistag Up/Dn: From Corr Stats: Closure Njets=4,5,6,7-8,9-,MHT2Wjets,MHT3Wjets,MHT2TTbar,MHT3TTbar\n");
  for (int ibin=1;ibin<=220;ibin++){
    if (ibin==1 || ibin==45 || ibin==89 || ibin==133 || ibin==177) 
      printf("------------------------------------------------------------------------------------------------------------------------\n");
    //
    printf("%4d: %10.3f: %6.3f:  %6.3f, %6.3f: %8.3f: %8.3f, %8.3f, %8.3f, %8.3f, %8.3f, %8.3f, %8.3f, %8.3f, %8.3f, %8.3f, %8.3f\n",
	   ibin,
	   QCDBin_LowDphi_nominal->GetBinContent(ibin),
	   QCDBinLowDphi_stat_uncertainty_fractional[ibin],
	   QCDBin_LowDphi_BMistagUp->GetBinContent(ibin),
	   QCDBin_LowDphi_BMistagDn->GetBinContent(ibin),
	   QCDBin_LowDphi_UncertaintyCorrectionStats->GetBinContent(ibin),
	   QCDBin_LowDphi_ClosureNj4->GetBinContent(ibin),
	   QCDBin_LowDphi_ClosureNj5->GetBinContent(ibin),
	   QCDBin_LowDphi_ClosureNj6->GetBinContent(ibin),
	   QCDBin_LowDphi_ClosureNj78->GetBinContent(ibin),
	   QCDBin_LowDphi_ClosureNj9->GetBinContent(ibin),
	   QCDBin_LowDphi_ClosureMHT2Wjets->GetBinContent(ibin),
	   QCDBin_LowDphi_ClosureMHT3Wjets->GetBinContent(ibin),
	   QCDBin_LowDphi_ClosureMHT4Wjets->GetBinContent(ibin),
	   QCDBin_LowDphi_ClosureMHT2TTbar->GetBinContent(ibin),
	   QCDBin_LowDphi_ClosureMHT3TTbar->GetBinContent(ibin),
	   QCDBin_LowDphi_ClosureMHT4TTbar->GetBinContent(ibin)
	   );
  }
  printf("------------------------------------------------------------------------------------------------------------------------\n");
  }
 
  //
  // Store outputs
  //
  sprintf(tempname,"HadTauEstimation_data_formatted.root");
  TFile HadTauEstimation_OutputFile(tempname,"RECREATE");

  searchBin_nominal->Write();
  searchBin_closureUncertainty->Write();
  if (isys==1){
  searchBin_UncertaintyCorrectionStats->Write();
  searchBin_BMistagUp->Write();
  searchBin_BMistagDn->Write();
  searchBin_ClosureNj46->Write();
  searchBin_ClosureNj78->Write();
  searchBin_ClosureNj9->Write();
  searchBin_ClosureMHT2Wjets->Write();
  searchBin_ClosureMHT3Wjets->Write();
  searchBin_ClosureMHT2TTbar->Write();
  searchBin_ClosureMHT3TTbar->Write();
  hWeightForSearchBin->Write();
  }

  hPredHTMHT0b_nominal->Write();
  hPredHTMHTwb_nominal->Write();
  hPredNJetBins_nominal->Write();
  hPredNbBins_nominal->Write();

  QCDBin_HiDphi_nominal->Write();
  QCDBin_HiDphi_closureUncertainty->Write();
  if (isys==1){
  QCDBin_HiDphi_UncertaintyCorrectionStats->Write();
  QCDBin_HiDphi_BMistagUp->Write();
  QCDBin_HiDphi_BMistagDn->Write();
  QCDBin_HiDphi_ClosureNj4->Write();
  QCDBin_HiDphi_ClosureNj5->Write();
  QCDBin_HiDphi_ClosureNj6->Write();
  QCDBin_HiDphi_ClosureNj78->Write();
  QCDBin_HiDphi_ClosureNj9->Write();
  QCDBin_HiDphi_ClosureMHT2Wjets->Write();
  QCDBin_HiDphi_ClosureMHT3Wjets->Write();
  QCDBin_HiDphi_ClosureMHT4Wjets->Write();
  QCDBin_HiDphi_ClosureMHT2TTbar->Write();
  QCDBin_HiDphi_ClosureMHT3TTbar->Write();
  QCDBin_HiDphi_ClosureMHT4TTbar->Write();
  }

  QCDBin_LowDphi_nominal->Write();
  QCDBin_LowDphi_closureUncertainty->Write();
  if (isys==1){
  QCDBin_LowDphi_UncertaintyCorrectionStats->Write();
  QCDBin_LowDphi_BMistagUp->Write();
  QCDBin_LowDphi_BMistagDn->Write();
  QCDBin_LowDphi_ClosureNj4->Write();
  QCDBin_LowDphi_ClosureNj5->Write();
  QCDBin_LowDphi_ClosureNj6->Write();
  QCDBin_LowDphi_ClosureNj78->Write();
  QCDBin_LowDphi_ClosureNj9->Write();
  QCDBin_LowDphi_ClosureMHT2Wjets->Write();
  QCDBin_LowDphi_ClosureMHT3Wjets->Write();
  QCDBin_LowDphi_ClosureMHT4Wjets->Write();
  QCDBin_LowDphi_ClosureMHT2TTbar->Write();
  QCDBin_LowDphi_ClosureMHT3TTbar->Write();
  QCDBin_LowDphi_ClosureMHT4TTbar->Write();
  }

  HadTauEstimation_OutputFile.Close();

}
