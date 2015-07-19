#!/bin/sh

sample=$1
submitscript=submitScriptTTbar.sh

if [ $sample -eq 14 ]; then
  njobs=`ls InputFiles_TTbar/filelist_TTJets_PU20bx25_* | wc -l`
fi

if [ $sample -eq 15 ]; then
  njobs=`ls InputFiles_TTbar/filelist_Spring15_TTJets_PU20bx25_* | wc -l`
fi

#njobs=$[$njobs+1]
echo number of jobs: $njobs
mkdir -p qsub
#for i in `seq 1 $njobs`; do
for i in `seq 0 $njobs`; do

export filenum=$i
export sample_=$sample
echo $filenum
echo $code 

qsub -N TTbar -o qsub/ -e qsub/ -V $submitscript -q moonshot

sleep 1

done

