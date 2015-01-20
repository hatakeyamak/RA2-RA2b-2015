void scan_highMet(){

  for (int i=1; i<=107; i++){

    if (i==26 || i==59 || i==95 || i==104 ||i==108 ) i++; // PHY14 set of ntuples are missing these


    char filename[500];

    // PHY14 PHYS14_720_Dec23_2014 set
    //sprintf (filename, "/data3/store/user/lpcsusyhad/PHYS14_720_Dec23_2014/lhx/PU20bx25_TTJets_MSDecaysCKM_madgraph-tauola/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/PHYS14_PU20bx25_PHYS14_25_V1-FLAT/141224_052628/0000/stopFlatNtuples_%d.root",i);

    // PHY14 set
    sprintf (filename, "/home/borzou/NtupleStorage/PU20bx25_TTJets_MSDecaysCKM_madgraph-tauola/TTJets_MSDecaysCKM_central_Tune4C_13TeV-madgraph-tauola/PHYS14_PU20bx25_PHYS14_25_V1-FLAT/141215_031040/0000/stopFlatNtuples_%d.root",i);

    TFile *_file0 = TFile::Open(filename);

    _file0->cd("stopTreeMaker");

    printf("%s\n",filename);
    //AUX->Scan();
    //AUX->Scan("run,lumi,event,mht,mhtphi");
    //AUX->Scan("run:lumi:event:mht:mhtphi");
    //AUX->Scan("run:lumi:event:mht:mhtphi:ht:met:metphi");
    AUX->Scan("run:lumi:event:mht:mhtphi:ht:met:metphi","event==1744747 || met>5000.");
    //AUX->Draw("met");

  }

}

