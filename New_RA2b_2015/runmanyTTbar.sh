#!/bin/sh
submitscript=submitScriptTTbar.sh
njobs=`ls InputFiles_TTbar/filelist_TTJets_PU20bx25_* | wc -l`
#njobs=$[$njobs+1]
echo number of jobs: $njobs
mkdir -p qsub
#for i in `seq 1 $njobs`; do
for i in `seq 0 $njobs`; do

export filenum=$i
echo $filenum
echo $code 

qsub -N TTbar -o qsub/ -e qsub/ -V $submitscript -q moonshot

sleep 1

done

