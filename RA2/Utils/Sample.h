#ifndef SAMPLE_H
#define SAMPLE_H

#include <exception>
#include <iostream>

#include "TColor.h"
#include "TString.h"


// Encapsulates sample information. Each sample is
// accessed by its unique id as defined in the table
// on the TWiki.
//
// Author: Matthias Schroeder
//         matthias.schroeder@AT@desy.de
//         November 2013
class Sample {
public:
  // Compact sample name without spaces, i.e. suitable
  // for file names etc.
  static TString toTString(unsigned int id);

  // Ntuple file name
  static TString fileNameFullSample(unsigned int id);

  // Ntuple file name of a small subset of the full sample
  // for quick tests
  static TString fileNameSubSample(unsigned int id);

  // Full-blown sample name including TLatex commands for
  // plot legends etc.
  static TString label(unsigned int id);

  // A color associated with each sample, e.g. for plotting
  static int color(unsigned int id);
  


private:
  static TString path_;

  static void checkId(unsigned int id);
};


// Path to ntuple directory. Adapt for your environment.
TString Sample::path_ = "root://eoscms//eos/cms/store/cmst3/group/das2014/SUSYJetsPlusMHT/ntuple/v4/";

TString Sample::fileNameFullSample(unsigned int id) {
  checkId(id);

  TString name("");
  if(      id ==  1  ) name += "HTMHT-Run2012.root";
  else if( id ==  2  ) name += "MuHad.root";
  else if( id == 11  ) name += "Summer12-WJetsHT400toInf_*.root";
  else if( id == 12  ) name += "Summer12-TTJets-*.root";
  else if( id == 13  ) name += "Summer12-ZJetsHT400toInf.root";
  else if( id == 14  ) name += "Summer12-QCDHT250toInf.root";
  else if( id == 21  ) name += "Summer12-SUSY_LM6.root";
  else if( id == 22  ) name += "Summer12-SUSY_LM9.root";

  return path_+name;
}


TString Sample::fileNameSubSample(unsigned int id) {
  checkId(id);

  TString name("");
  if(      id ==  1  ) name += "HTMHT-Run2012.root";
  else if( id ==  2  ) name += "MuHad.root";
  else if( id == 11  ) name += "Summer12-WJetsHT400toInf_1.root";
  else if( id == 12  ) name += "Summer12-TTJets-SemiLep_1.root";
  else if( id == 13  ) name += "Summer12-ZJetsHT400toInf.root";
  else if( id == 14  ) name += "Summer12-QCDHT250toInf.root";
  else if( id == 21  ) name += "Summer12-SUSY_LM6.root";
  else if( id == 22  ) name += "Summer12-SUSY_LM9.root";

  return path_+name;
}


// Return the label for a given sample
TString Sample::label(unsigned int id) {
  checkId(id);

  TString label("");
  if(      id ==  1  ) label += "Data";
  else if( id ==  2  ) label += "Data";
  else if( id == 11  ) label += "W(l#nu)+Jets";
  else if( id == 12  ) label += "t#bar{t}+Jets";
  else if( id == 13  ) label += "Z(#nu#bar{#nu})+Jets";
  else if( id == 14  ) label += "QCD";
  else if( id == 21  ) label += "LM6";
  else if( id == 22  ) label += "LM9";

  return label;
}


TString Sample::toTString(unsigned int id) {
  checkId(id);

  TString str("");
  if(      id ==  1  ) str += "Data";
  else if( id ==  2  ) str += "Data";
  else if( id == 11  ) str += "WJets";
  else if( id == 12  ) str += "TTJets";
  else if( id == 13  ) str += "ZJets";
  else if( id == 14  ) str += "QCD";
  else if( id == 21  ) str += "LM6";
  else if( id == 22  ) str += "LM9";

  return str;
}


int Sample::color(unsigned int id) {
  checkId(id);

  int color = kBlack;
  if(      id ==  1  ) color = kBlack;
  else if( id ==  1  ) color = kBlack;
  else if( id == 11  ) color = kGreen+1;
  else if( id == 12  ) color = kRed;
  else if( id == 13  ) color = kYellow+2;
  else if( id == 14  ) color = kRed+3;
  else if( id == 21  ) color = kBlue;
  else if( id == 22  ) color = kBlue+3;

  return color;
}
  

void Sample::checkId(unsigned int id) {
  if( id != 1 && id != 2 && !(id >= 11 && id <= 16) && !(id >= 21 && id <= 22) ) {
    std::cerr << "\n\nERROR invalid sample id " << id << std::endl;
    throw std::exception();
  } 
}

#endif
