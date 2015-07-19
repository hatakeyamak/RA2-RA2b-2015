#!/bin/sh

sample=$1
  submitscript=submitScriptWJet.sh

  mkdir -p qsub

  for WJetStr in 100_200 200_400 400_600 600_inf; do 

    if [ $sample -eq 14 ]; then
      njobs=`ls InputFiles_WJet_${WJetStr}/filelist_WJet_HT_${WJetStr}* | wc -l`
      #njobs=$[$njobs+1]
      echo number of jobs: $njobs
      #for i in `seq 1 $njobs`; do
        for i in `seq 0 $njobs`; do

          export filenum=$i
          export WJetStr=$WJetStr
          echo $filenum
          qsub -N WJet_$WJetStr -o qsub/ -e qsub/ -V $submitscript -q moonshot

          sleep 1

        done
    fi

    if [ $sample -eq 15 ]; then
      njobs=`ls InputFiles_WJet_${WJetStr}/filelist_Spring15_WJet_HT_${WJetStr}* | wc -l`
      #njobs=$[$njobs+1]
      echo number of jobs: $njobs
      #for i in `seq 1 $njobs`; do
        for i in `seq 0 $njobs`; do

          export filenum=$i
          export WJetStr=$WJetStr
          export sample_=$sample
          echo $filenum
          qsub -N WJet_$WJetStr -o qsub/ -e qsub/ -V $submitscript -q moonshot

          sleep 1

        done
    fi



  done


