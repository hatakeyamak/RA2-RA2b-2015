#!/bin/sh

echo $PBS_O_WORKDIR
cd $PBS_O_WORKDIR
source ~cmssoft/shrc
eval `scramv1 runtime -sh`
#

if [ $sample_ -eq 14 ]; then

  if [ $filenum -lt 10 ]
  then
    ./run_tauHad2 "InputFiles_TTbar/filelist_TTJets_PU20bx25_0$filenum" "TTbar_${outStr}_$filenum" "TauHad2Multiple" "00" "0"
    else
    ./run_tauHad2 "InputFiles_TTbar/filelist_TTJets_PU20bx25_$filenum" "TTbar_${outStr}_$filenum" "TauHad2Multiple" "00" "0"
  fi

fi

if [ $sample_ -eq 15 ]; then

  if [ $filenum -lt 10 ]
  then
    ./run_tauHad2 "InputFiles_TTbar/filelist_Spring15_TTJets_PU20bx25_0$filenum" "TTbar_${outStr}_$filenum" "TauHad2Multiple" "00" "0"
    else
    ./run_tauHad2 "InputFiles_TTbar/filelist_Spring15_TTJets_PU20bx25_$filenum" "TTbar_${outStr}_$filenum" "TauHad2Multiple" "00" "0"
  fi

fi

