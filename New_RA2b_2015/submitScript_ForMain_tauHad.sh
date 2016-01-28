#!/bin/sh

echo $PBS_O_WORKDIR
cd $PBS_O_WORKDIR
source ~cmssoft/shrc
eval `scramv1 runtime -sh`
#


./run_tauHad "InputFiles_ForMain/${sample}/${filename}" "${filename}-${outputStr}" "TauHadMultiple" "00" "0"

