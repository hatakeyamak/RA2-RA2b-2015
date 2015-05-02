#!/bin/sh
cd /home/borzou/CMSSW_7_4_0_pre1/src/RA2-RA2b-2015
source ~cmssoft/shrc
eval `scramv1 runtime -sh`
#
if [ $filenum -lt 10 ]
then
./main "FileList/filelist_TTJets_PU20bx25_0$filenum" "TTJets_PU20bx25_0$filenum" "Results" "00" "0"
else
./main "FileList/filelist_TTJets_PU20bx25_$filenum" "TTJets_PU20bx25_$filenum" "Results" "00" "0"
fi
