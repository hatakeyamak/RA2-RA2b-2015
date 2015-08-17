#!/bin/sh

echo $PBS_O_WORKDIR
cd $PBS_O_WORKDIR
source ~cmssoft/shrc
eval `scramv1 runtime -sh`
#


if [ $filenum -lt 10 ]
then
  ./run_tauHad2 "InputFiles_Data/filelist_data_SingleMuon_${sample}_0$filenum" "Data_$filenum" "TauHad2Multiple" "00" "0"
  else
  ./run_tauHad2 "InputFiles_Data/filelist_data_SingleMuon_${sample}_$filenum" "Data_$filenum" "TauHad2Multiple" "00" "0"
fi


