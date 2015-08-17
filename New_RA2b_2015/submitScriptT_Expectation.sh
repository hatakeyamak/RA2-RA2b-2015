#!/bin/sh
#cd /home/borzou/CMSSW_7_4_0_pre1/src/RA2-RA2b-2015/New_RA2b_2015
cd $PBS_O_WORKDIR
source ~cmssoft/shrc
eval `scramv1 runtime -sh`
#
if [ $filenum -lt 10 ]
then
./run_tauHad "InputFiles_T/filelist_Spring15_ST_${TStr}_v1.4g3_0$filenum" "${TStr}_$filenum" "TauHadMultiple" "00" "0"
else
./run_tauHad "InputFiles_T/filelist_Spring15_ST_${TStr}_v1.4g3_$filenum" "${TStr}_$filenum" "TauHadMultiple" "00" "0"
fi
