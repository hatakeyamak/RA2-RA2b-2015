#! /bin/bash

cd TauHad2Multiple

#
# Hadd multiple job outpus
# ++++++++++++++++++++++++
# for W+jets
#
for i in 100_200 200_400 400_600 600_inf; do 

  hadd -f HadTauEstimation_WJet_${i}_.root  `ls HadTauEstimation_WJet_${i}_*00.root `  
  cp HadTauEstimation_WJet_${i}_.root ../TauHad2

done 

#
# for Single top
#
for i in s t u ; do

  hadd -f HadTauEstimation_T_${i}_.root  `ls HadTauEstimation_T_${i}_*00.root `
  cp HadTauEstimation_T_${i}_.root ../TauHad2

  hadd -f HadTauEstimation_Tbar_${i}_.root  `ls HadTauEstimation_Tbar_${i}_*00.root `
  cp HadTauEstimation_Tbar_${i}_.root ../TauHad2

done

#
# for ttbar
#
hadd -f HadTauEstimation_TTbar_.root  `ls HadTauEstimation_TTbar_*00.root `
cp HadTauEstimation_TTbar_.root ../TauHad2

cd ..

#####
#exit
#####

#
# Do the following manually
#

#
# Preserve original inputs
# ++++++++++++++++++++++++

cp -p TauHad/GenInfo_HadTauEstimation_TTbar_.root	  TauHad/GenInfo_HadTauEstimation_TTbar_org.root	    
cp -p TauHad/GenInfo_HadTauEstimation_WJet_100_200_.root  TauHad/GenInfo_HadTauEstimation_WJet_100_200_org.root  
cp -p TauHad/GenInfo_HadTauEstimation_WJet_200_400_.root  TauHad/GenInfo_HadTauEstimation_WJet_200_400_org.root  
cp -p TauHad/GenInfo_HadTauEstimation_WJet_400_600_.root  TauHad/GenInfo_HadTauEstimation_WJet_400_600_org.root  
cp -p TauHad/GenInfo_HadTauEstimation_WJet_600_inf_.root  TauHad/GenInfo_HadTauEstimation_WJet_600_inf_org.root  
cp -p TauHad/GenInfo_HadTauEstimation_T_s_.root	          TauHad/GenInfo_HadTauEstimation_T_s_org.root	    
cp -p TauHad/GenInfo_HadTauEstimation_T_t_.root	          TauHad/GenInfo_HadTauEstimation_T_t_org.root	    
cp -p TauHad/GenInfo_HadTauEstimation_T_u_.root	          TauHad/GenInfo_HadTauEstimation_T_u_org.root	    
cp -p TauHad/GenInfo_HadTauEstimation_Tbar_s_.root        TauHad/GenInfo_HadTauEstimation_Tbar_s_org.root        
cp -p TauHad/GenInfo_HadTauEstimation_Tbar_t_.root	  TauHad/GenInfo_HadTauEstimation_Tbar_t_org.root	    
cp -p TauHad/GenInfo_HadTauEstimation_Tbar_u_.root	  TauHad/GenInfo_HadTauEstimation_Tbar_u_org.root	    

cp -p TauHad2/HadTauEstimation_TTbar_.root         TauHad2/HadTauEstimation_TTbar_org.root         
cp -p TauHad2/HadTauEstimation_WJet_100_200_.root  TauHad2/HadTauEstimation_WJet_100_200_org.root  
cp -p TauHad2/HadTauEstimation_WJet_200_400_.root  TauHad2/HadTauEstimation_WJet_200_400_org.root  
cp -p TauHad2/HadTauEstimation_WJet_400_600_.root  TauHad2/HadTauEstimation_WJet_400_600_org.root  
cp -p TauHad2/HadTauEstimation_WJet_600_inf_.root  TauHad2/HadTauEstimation_WJet_600_inf_org.root  
cp -p TauHad2/HadTauEstimation_T_s_.root	   TauHad2/HadTauEstimation_T_s_org.root	   
cp -p TauHad2/HadTauEstimation_T_t_.root	   TauHad2/HadTauEstimation_T_t_org.root	   
cp -p TauHad2/HadTauEstimation_T_u_.root	   TauHad2/HadTauEstimation_T_u_org.root	   
cp -p TauHad2/HadTauEstimation_Tbar_s_.root	   TauHad2/HadTauEstimation_Tbar_s_org.root	   
cp -p TauHad2/HadTauEstimation_Tbar_t_.root	   TauHad2/HadTauEstimation_Tbar_t_org.root	   
cp -p TauHad2/HadTauEstimation_Tbar_u_.root        TauHad2/HadTauEstimation_Tbar_u_org.root        

#
# Project the error to the targetted Luminosity
# ++++++++++++++++++++++++

# Prepare the output files skeltons
# We scale and write only limited numbers of histograms, but stack code right now assumes more histograms to be present
# so it's important to prepare the skeltons

#####
cp -p TauHad/GenInfo_HadTauEstimation_TTbar_org.root	    TauHad/GenInfo_HadTauEstimation_TTbar_LumiScaledTo10.0fbinv.root         
cp -p TauHad/GenInfo_HadTauEstimation_WJet_100_200_org.root TauHad/GenInfo_HadTauEstimation_WJet_100_200_LumiScaledTo10.0fbinv.root 
cp -p TauHad/GenInfo_HadTauEstimation_WJet_200_400_org.root TauHad/GenInfo_HadTauEstimation_WJet_200_400_LumiScaledTo10.0fbinv.root  
cp -p TauHad/GenInfo_HadTauEstimation_WJet_400_600_org.root TauHad/GenInfo_HadTauEstimation_WJet_400_600_LumiScaledTo10.0fbinv.root  
cp -p TauHad/GenInfo_HadTauEstimation_WJet_600_inf_org.root TauHad/GenInfo_HadTauEstimation_WJet_600_inf_LumiScaledTo10.0fbinv.root  
cp -p TauHad/GenInfo_HadTauEstimation_T_s_org.root          TauHad/GenInfo_HadTauEstimation_T_s_LumiScaledTo10.0fbinv.root	        
cp -p TauHad/GenInfo_HadTauEstimation_T_t_org.root	    TauHad/GenInfo_HadTauEstimation_T_t_LumiScaledTo10.0fbinv.root	       
cp -p TauHad/GenInfo_HadTauEstimation_T_u_org.root	    TauHad/GenInfo_HadTauEstimation_T_u_LumiScaledTo10.0fbinv.root	         
cp -p TauHad/GenInfo_HadTauEstimation_Tbar_s_org.root       TauHad/GenInfo_HadTauEstimation_Tbar_s_LumiScaledTo10.0fbinv.root 
cp -p TauHad/GenInfo_HadTauEstimation_Tbar_t_org.root	    TauHad/GenInfo_HadTauEstimation_Tbar_t_LumiScaledTo10.0fbinv.root    
cp -p TauHad/GenInfo_HadTauEstimation_Tbar_u_org.root	    TauHad/GenInfo_HadTauEstimation_Tbar_u_LumiScaledTo10.0fbinv.root    

cp -p TauHad2/HadTauEstimation_TTbar_org.root        TauHad2/HadTauEstimation_TTbar_LumiScaledTo10.0fbinv.root         
cp -p TauHad2/HadTauEstimation_WJet_100_200_org.root TauHad2/HadTauEstimation_WJet_100_200_LumiScaledTo10.0fbinv.root	
cp -p TauHad2/HadTauEstimation_WJet_200_400_org.root TauHad2/HadTauEstimation_WJet_200_400_LumiScaledTo10.0fbinv.root	
cp -p TauHad2/HadTauEstimation_WJet_400_600_org.root TauHad2/HadTauEstimation_WJet_400_600_LumiScaledTo10.0fbinv.root	
cp -p TauHad2/HadTauEstimation_WJet_600_inf_org.root TauHad2/HadTauEstimation_WJet_600_inf_LumiScaledTo10.0fbinv.root	
cp -p TauHad2/HadTauEstimation_T_s_org.root	  TauHad2/HadTauEstimation_T_s_LumiScaledTo10.0fbinv.root		
cp -p TauHad2/HadTauEstimation_T_t_org.root	  TauHad2/HadTauEstimation_T_t_LumiScaledTo10.0fbinv.root		
cp -p TauHad2/HadTauEstimation_T_u_org.root	  TauHad2/HadTauEstimation_T_u_LumiScaledTo10.0fbinv.root		
cp -p TauHad2/HadTauEstimation_Tbar_s_org.root	  TauHad2/HadTauEstimation_Tbar_s_LumiScaledTo10.0fbinv.root 	
cp -p TauHad2/HadTauEstimation_Tbar_t_org.root	  TauHad2/HadTauEstimation_Tbar_t_LumiScaledTo10.0fbinv.root	
cp -p TauHad2/HadTauEstimation_Tbar_u_org.root       TauHad2/HadTauEstimation_Tbar_u_LumiScaledTo10.0fbinv.root	

#####
root -l -b -q Scale_ByLumi.C

#
# Now, copy output files to those which Stack reads in
#

#####
cp -p TauHad/GenInfo_HadTauEstimation_TTbar_LumiScaledTo10.0fbinv.root         TauHad/GenInfo_HadTauEstimation_TTbar_.root	
cp -p TauHad/GenInfo_HadTauEstimation_WJet_100_200_LumiScaledTo10.0fbinv.root  TauHad/GenInfo_HadTauEstimation_WJet_100_200_.root
cp -p TauHad/GenInfo_HadTauEstimation_WJet_200_400_LumiScaledTo10.0fbinv.root  TauHad/GenInfo_HadTauEstimation_WJet_200_400_.root
cp -p TauHad/GenInfo_HadTauEstimation_WJet_400_600_LumiScaledTo10.0fbinv.root  TauHad/GenInfo_HadTauEstimation_WJet_400_600_.root
cp -p TauHad/GenInfo_HadTauEstimation_WJet_600_inf_LumiScaledTo10.0fbinv.root  TauHad/GenInfo_HadTauEstimation_WJet_600_inf_.root
cp -p TauHad/GenInfo_HadTauEstimation_T_s_LumiScaledTo10.0fbinv.root	       TauHad/GenInfo_HadTauEstimation_T_s_.root          
cp -p TauHad/GenInfo_HadTauEstimation_T_t_LumiScaledTo10.0fbinv.root	       TauHad/GenInfo_HadTauEstimation_T_t_.root	 
cp -p TauHad/GenInfo_HadTauEstimation_T_u_LumiScaledTo10.0fbinv.root	       TauHad/GenInfo_HadTauEstimation_T_u_.root	   
cp -p TauHad/GenInfo_HadTauEstimation_Tbar_s_LumiScaledTo10.0fbinv.root	       TauHad/GenInfo_HadTauEstimation_Tbar_s_.root      
cp -p TauHad/GenInfo_HadTauEstimation_Tbar_t_LumiScaledTo10.0fbinv.root	       TauHad/GenInfo_HadTauEstimation_Tbar_t_.root	
cp -p TauHad/GenInfo_HadTauEstimation_Tbar_u_LumiScaledTo10.0fbinv.root	       TauHad/GenInfo_HadTauEstimation_Tbar_u_.root	

cp -p TauHad2/HadTauEstimation_TTbar_LumiScaledTo10.0fbinv.root         TauHad2/HadTauEstimation_TTbar_.root        
cp -p TauHad2/HadTauEstimation_WJet_100_200_LumiScaledTo10.0fbinv.root	TauHad2/HadTauEstimation_WJet_100_200_.root 
cp -p TauHad2/HadTauEstimation_WJet_200_400_LumiScaledTo10.0fbinv.root	TauHad2/HadTauEstimation_WJet_200_400_.root 
cp -p TauHad2/HadTauEstimation_WJet_400_600_LumiScaledTo10.0fbinv.root	TauHad2/HadTauEstimation_WJet_400_600_.root 
cp -p TauHad2/HadTauEstimation_WJet_600_inf_LumiScaledTo10.0fbinv.root	TauHad2/HadTauEstimation_WJet_600_inf_.root 
cp -p TauHad2/HadTauEstimation_T_s_LumiScaledTo10.0fbinv.root		TauHad2/HadTauEstimation_T_s_.root	  
cp -p TauHad2/HadTauEstimation_T_t_LumiScaledTo10.0fbinv.root		TauHad2/HadTauEstimation_T_t_.root	  
cp -p TauHad2/HadTauEstimation_T_u_LumiScaledTo10.0fbinv.root		TauHad2/HadTauEstimation_T_u_.root	  
cp -p TauHad2/HadTauEstimation_Tbar_s_LumiScaledTo10.0fbinv.root 	TauHad2/HadTauEstimation_Tbar_s_.root	  
cp -p TauHad2/HadTauEstimation_Tbar_t_LumiScaledTo10.0fbinv.root	TauHad2/HadTauEstimation_Tbar_t_.root	  
cp -p TauHad2/HadTauEstimation_Tbar_u_LumiScaledTo10.0fbinv.root	TauHad2/HadTauEstimation_Tbar_u_.root       

#
# Stacking histograms/root files
# ++++++++++++++++++++++++

echo " hadd done. Stacking... " 

cd TauHad2/Stack/

./Stack "-1"

cd ../../TauHad/Stack/

./Stack "-1"

cd ../..

cp -p TauHad/Stack/GenInfo_HadTauEstimation_stacked.root TauHad/Stack/GenInfo_HadTauEstimation_stacked_LumiScaledTo10.0fbinv.root
cp -p TauHad2/Stack/HadTauEstimation_stacked.root        TauHad2/Stack/HadTauEstimation_stacked_LumiScaledTo10.0fbinv.root

#
# Plotting
# ++++++++

echo " Making the plots \n\n\n" 
#./makeplots.sh 1 1 1 

root.exe -b -q 'Plot_searchBin_full.C("stacked","searchH_b")'
root.exe -b -q 'Plot_searchBin_full.C("stacked","QCD_Low")'
root.exe -b -q 'Plot_searchBin_full.C("stacked","QCD_Up")'

