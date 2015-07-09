#!/bin/sh

  submitscript=submitScriptT.sh

  mkdir -p qsub

  for TStr in s t u; do 

    njobs=`ls InputFiles_T/filelist_TToLeptons_${TStr}* | wc -l`
    #njobs=$[$njobs+1]
    echo number of jobs: $njobs
    #for i in `seq 1 $njobs`; do
      for i in `seq 0 $njobs`; do

        export filenum=$i
        export TStr=$TStr
        echo $filenum
        qsub -N T_$TStr -o qsub/ -e qsub/ -V $submitscript -q moonshot

        sleep 1

      done

  done


  submitscript=submitScriptTbar.sh

  for TStr in s t u; do                          

    njobs=`ls InputFiles_T/filelist_TBarToLeptons_${TStr}* | wc -l`
    #njobs=$[$njobs+1]
    echo number of jobs: $njobs
    #for i in `seq 1 $njobs`; do
      for i in `seq 0 $njobs`; do

        export filenum=$i
        export TStr=$TStr
        echo $filenum
        qsub -N Tbar_$TStr -o qsub/ -e qsub/ -V $submitscript -q moonshot

        sleep 1

      done

  done



