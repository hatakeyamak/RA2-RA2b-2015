#!/bin/sh

echo $PBS_O_WORKDIR
cd $PBS_O_WORKDIR
hostname
source ~cmssoft/shrc
eval `scramv1 runtime -sh`
#




    ./run_tauHad2 "InputFiles_Rare/${filename}" "${filename}_${outStr}" "TauHad2Multiple" "00" "0"


