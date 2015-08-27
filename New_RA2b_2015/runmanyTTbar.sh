#!/bin/sh

sample=$1
type=$2 # 0 prediction, 1 expectation
outStr=$3
submitscript=submitScriptTTbar.sh
submitscript1=submitScriptTTbar_Expectation.sh

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
export outStr=$outStr
echo $filenum
echo $code 

if [ $type -eq 0 ]; then
  qsub -N TTbar -o qsub/ -e qsub/ -V $submitscript -q moonshot
fi

if [ $type -eq 1 ]; then
  qsub -N TTbar -o qsub/ -e qsub/ -V $submitscript1 -q moonshot
fi

sleep 1

done

