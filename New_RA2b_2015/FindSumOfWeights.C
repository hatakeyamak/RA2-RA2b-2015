#include <vector>
#include <cstdio>
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string

using namespace std;

FindSumOfWeights(){

string type[]={"DYJetsToLL_M-50_HT","GJets_HT","ZJetsToNuNu_HT","ST_s","ttHJetTobb","TTWJetsToQQ","TTZToLLNuNu_M-10","TTZToQQ","TTTT","WH_HToBB_WToLNu_M125","ZH_HToBB","WWTo1L1Nu2Q","WWTo2L2Nu","WZTo1L1Nu2Q","WWZ"};

char tempname[200];

for(int i=0; i < sizeof(type)/sizeof(type[0]); i++){
sprintf(tempname,"TauHad2/HadTauEstimation_%s_.root",type[i].c_str());

cout << tempname << endl;
TFile * infile = new TFile(tempname,"R");
TH1D * hist = (TH1D*) infile->Get("searchH_b")->Clone();
//hist->Print();
cout << " events in 3/fb: " << hist->GetSumOfWeights()*3000. << endl;
printf(" percent: %3.2f \n",(hist->GetSumOfWeights()*3000.)/(58.6)*100); // total rare processes contribution is 81.54 events
cout << " ########## \n " ;

infile->Close();

}








}
