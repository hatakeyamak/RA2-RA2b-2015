#!/bin/sh

echo $PBS_O_WORKDIR
cd $PBS_O_WORKDIR
source ~cmssoft/shrc
eval `scramv1 runtime -sh`
#


if [ $filenum -lt 10 ]
then
  ./run_tauHad2 "InputFiles_QCD/filelist_Spring15_QCD_0$filenum" "QCD_${outputStr}_$filenum" "TauHad2Multiple" "00" "0"
  else
  ./run_tauHad2 "InputFiles_QCD/filelist_Spring15_QCD_$filenum" "QCD_${outputStr}_$filenum" "TauHad2Multiple" "00" "0"
fi


