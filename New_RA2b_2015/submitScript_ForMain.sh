#!/bin/sh

echo $PBS_O_WORKDIR
cd $PBS_O_WORKDIR
source ~cmssoft/shrc
eval `scramv1 runtime -sh`
#


./run "InputFiles_ForMain/${sample}/${filename}" "${filename}-${outputStr}" "MainMultiple" "00" "0"

