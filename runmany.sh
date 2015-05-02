#!/bin/sh
submitscript=submitScript.sh
njobs=`ls FileList/filelist_TTJets_PU20bx25_* | wc -l`
#njobs=$[$njobs+1]
echo number of jobs: $njobs
#for i in `seq 1 $njobs`; do
for i in `seq 0 $njobs`; do

export filenum=$i
echo $filenum
qsub -N TTbar -V $submitscript

sleep 10

done

