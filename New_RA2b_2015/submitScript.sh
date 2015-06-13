#!/bin/sh
cd /home/borzou/CMSSW_7_4_0_pre1/src/RA2-RA2b-2015/New_RA2b_2015
source ~cmssoft/shrc
eval `scramv1 runtime -sh`
#
if [ $filenum -lt 10 ]
then
./run_tauHad2 "InputFiles/filelist_TTJets_PU20bx25_0$filenum" "TTbar_$filenum" "TauHad2Multiple" "00" "0"
else
./run_tauHad2 "InputFiles/filelist_TTJets_PU20bx25_$filenum" "TTbar_$filenum" "TauHad2Multiple" "00" "0"
fi
