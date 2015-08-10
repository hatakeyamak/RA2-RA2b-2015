#!/bin/sh

  submitscript=submitScriptT.sh

  mkdir -p qsub

  for TStr in t_top tW_top; do 

    njobs=`ls InputFiles_T/filelist_Spring15_ST_${TStr}_v1.4b_* | wc -l`
    #njobs=$[$njobs+1]
    echo number of jobs: $njobs
    #for i in `seq 1 $njobs`; do
      for i in `seq 0 $njobs`; do

        export filenum=$i
        export TStr=$TStr
        echo $filenum
        qsub -N $TStr -o qsub/ -e qsub/ -V $submitscript -q moonshot

        sleep 1

      done

  done


  submitscript=submitScriptT.sh

  for TStr in t_antitop tW_antitop ; do                          

    njobs=`ls InputFiles_T/filelist_Spring15_ST_${TStr}_v1.4b_* | wc -l`
    #njobs=$[$njobs+1]
    echo number of jobs: $njobs
    #for i in `seq 1 $njobs`; do
      for i in `seq 0 $njobs`; do

        export filenum=$i
        export TStr=$TStr
        echo $filenum
        qsub -N $TStr -o qsub/ -e qsub/ -V $submitscript -q moonshot

        sleep 1

      done

  done



