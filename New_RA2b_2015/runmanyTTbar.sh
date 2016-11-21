#!/bin/sh

type=$1 # 0 prediction, 1 expectation
outStr=$2
submitscript=submitScriptTTbar.sh
submitscript1=submitScriptTTbar_Expectation.sh


for TTbarStr in DiLept HT_1200_2500 HT_600_800 HT_800_1200 HT_2500_Inf Inclusive T_SingleLep Tbar_SingleLep; do

#for TTbarStr in T_SingleLep Tbar_SingleLep; do
  njobs=`ls InputFiles_TTbar/filelist_Spring15_TTJets_${TTbarStr}_* | wc -l`

  #njobs=$[$njobs+1]
  echo number of jobs: $njobs
  mkdir -p qsub
  #for i in `seq 1 $njobs`; do
  for i in `seq 0 $njobs`; do

    export filenum=$i
    export outStr=$outStr
    echo $filenum
    echo $code 
    export TTbarStr=$TTbarStr

    if [ $type -eq 0 ]; then
	echo $filenum
	if [ -e TauHad2Multiple/HadTauEstimation_TTbar_${TTbarStr}_${outStr}_${i}_00.root ]; then
        echo warning !
        echo exist TauHad2Multiple/HadTauEstimation_TTbar_${TTbarStr}_${outStr}_${i}_00.root
      else
        echo submitting TauHad2Multiple/HadTauEstimation_TTbar_${TTbarStr}_${outStr}_${i}_00.root
        qsub -l walltime=12:00:00 -N TTbar_$TTbarStr_$outStr -o qsub/ -e qsub/ -V $submitscript  
      fi

    fi

    if [ $type -eq 1 ]; then
	echo $filenum
      if [ -e TauHadMultiple/GenInfo_HadTauEstimation_TTbar_${TTbarStr}_${outStr}_${i}_00.root ]; then
        echo warning !
        echo exist TauHadMultiple/GenInfo_HadTauEstimation_TTbar_${TTbarStr}_${outStr}_${i}_00.root
      else
        echo submitting TauHadMultiple/GenInfo_HadTauEstimation_TTbar_${TTbarStr}_${outStr}_${i}_00.root
        qsub -l walltime=12:00:00 -N TTbar_$TTbarStr_$outStr -o qsub/ -e qsub/ -V $submitscript1  
      fi

    fi

    sleep 1

  done


done

