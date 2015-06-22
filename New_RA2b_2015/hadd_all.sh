#! /bin/bash

cd TauHad2Multiple

for i in 100_200 200_400 400_600 600_inf; do 

  hadd HadTauEstimation_WJet_${i}_.root  `ls HadTauEstimation_WJet_${i}_*00.root `
  
  cp HadTauEstimation_WJet_${i}_.root ../TauHad2

done 


hadd HadTauEstimation_TTbar_.root  `ls HadTauEstimation_TTbar_*00.root `

cp HadTauEstimation_TTbar_.root ../TauHad2

echo " hadd done. Stacking... " 

cd ../TauHad2/Stack/

./Stack "10000"

cd ../../TauHad/Stack/

./Stack "10000"

cd ../..

echo " Making the plots \n\n\n" 
./makeplots.sh 1 1 1 


