#!/bin/sh

echo $PBS_O_WORKDIR
cd $PBS_O_WORKDIR
source ~cmssoft/shrc
eval `scramv1 runtime -sh`
#


./run_tauHad2 "InputFiles_Signal/${filename}" "${filename}-${outputStr}" "TauHad2Multiple" "00" "0"

