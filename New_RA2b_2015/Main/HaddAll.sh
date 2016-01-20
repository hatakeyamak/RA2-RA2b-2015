#!/bin/bash

str=$1

for i in `ls ../InputFiles_ForMain/All`; do 

  file=`echo $i | sed s/.txt//g |sed s/^/results_/g `
  echo $file
  ls ../MainMultiple/${file}_*${str}*00.root 

  hadd ${file}_.root `ls ../MainMultiple/${file}_*${str}*00.root`

 done
