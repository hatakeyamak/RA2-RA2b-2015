#!/bin/sh

echo $PBS_O_WORKDIR
cd $PBS_O_WORKDIR
source ~cmssoft/shrc
eval `scramv1 runtime -sh`
#


if [ $sample_ -eq 8 ]; then

  if [ $filenum -lt 10 ]
  then
    ./run_tauHad2 "InputFiles_Data_v08/filelist_data_SingleMuon_v08_0$filenum" "Data_$filenum" "TauHad2Multiple" "00" "0"
    else
    ./run_tauHad2 "InputFiles_Data_v08/filelist_data_SingleMuon_v08_$filenum" "Data_$filenum" "TauHad2Multiple" "00" "0"
  fi

fi

