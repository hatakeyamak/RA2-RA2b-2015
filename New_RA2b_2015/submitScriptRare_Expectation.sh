#!/bin/sh

echo $PBS_O_WORKDIR
cd $PBS_O_WORKDIR
hostname
source ~cmssoft/shrc
eval `scramv1 runtime -sh`
#


    ./run_tauHad "InputFiles_Rare/${filename}" "${filename}_${outStr}" "TauHadMultiple" "00" "0"


