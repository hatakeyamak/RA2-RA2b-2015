#!/bin/bash

i=$1
j=$2
k=$3

if [ $i -eq 1 ]
then
  #######################################################
  # TTbar
  #######
#  #root -l -b -q Plot_closure_Data.C'("mht_200","NJet","TTbar_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","NBtag","TTbar_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","HT","TTbar_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","MHT","TTbar_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","DelPhi1","TTbar_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","DelPhi2","TTbar_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","DelPhi3","TTbar_stacked",1)'



  #root -l -b -q Plot_closure_Data.C'("delphi","NJet","TTbar_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","NBtag","TTbar_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","HT","TTbar_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","MHT","TTbar_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","DelPhi1","TTbar_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","DelPhi2","TTbar_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","DelPhi3","TTbar_stacked",1)'

  #root -l -b -q Plot_searchBin_full_Data.C'("TTbar_stacked","searchH_b",1)'
  #root -l -b -q Plot_searchBin.C'("TTbar_stacked","searchH",1)'
  echo "TTbar"
fi
########################################################
#WJet
#####

if [ $j -eq 1 ]; then 
#  #root -l -b -q Plot_closure_Data.C'("mht_200","NJet","WJet_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","NBtag","WJet_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","HT","WJet_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","MHT","WJet_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","DelPhi1","WJet_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","DelPhi2","WJet_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","DelPhi3","WJet_stacked",1)'



  #root -l -b -q Plot_closure_Data.C'("delphi","NJet","WJet_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","NBtag","WJet_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","HT","WJet_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","MHT","WJet_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","DelPhi1","WJet_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","DelPhi2","WJet_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","DelPhi3","WJet_stacked",1)'
  #root -l -b -q Plot_searchBin_full_Data.C'("WJet_stacked","searchH_b",1)'
  #root -l -b -q Plot_searchBin.C'("WJet_stacked","searchH",1)'
  echo "WJet"
fi
########################################################
#Single Top
#####

if [ $j -eq 1 ]; then 
#  #root -l -b -q Plot_closure_Data.C'("mht_200","NJet","T_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","NBtag","T_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","HT","T_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","MHT","T_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","DelPhi1","T_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","DelPhi2","T_stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","DelPhi3","T_stacked",1)'



  #root -l -b -q Plot_closure_Data.C'("delphi","NJet","T_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","NBtag","T_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","HT","T_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","MHT","T_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","DelPhi1","T_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","DelPhi2","T_stacked",1)'
  #root -l -b -q Plot_closure_Data.C'("delphi","DelPhi3","T_stacked",1)'
  #root -l -b -q Plot_searchBin_full_Data.C'("T_stacked","searchH_b",1)'
  #root -l -b -q Plot_searchBin.C'("T_stacked","searchH",1)'
  echo "T"
fi
########################################################
#TTbar+WJet+SingleT
#####

if [ $k -eq 1 ]; then

#  #root -l -b -q Plot_closure_Data.C'("mht_200","NJet","stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","NBtag","stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","HT","stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","MHT","stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","DelPhi1","stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","DelPhi2","stacked",1)'
#  #root -l -b -q Plot_closure_Data.C'("mht_200","DelPhi3","stacked",1)'



  root -l -b -q Plot_closure_Data.C'("delphi","NJet","stacked",1)'
  root -l -b -q Plot_closure_Data.C'("delphi","NBtag","stacked",1)'
  root -l -b -q Plot_closure_Data.C'("delphi","HT","stacked",1)'
  root -l -b -q Plot_closure_Data.C'("delphi","MHT","stacked",1)'
  root -l -b -q Plot_closure_Data.C'("delphi","DelPhi1","stacked",1)'
  root -l -b -q Plot_closure_Data.C'("delphi","DelPhi2","stacked",1)'
  root -l -b -q Plot_closure_Data.C'("delphi","DelPhi3","stacked",1)'

#  root -l -b -q Plot_Commissioning_Data.C'("NJet",0)'
#  root -l -b -q Plot_Commissioning_Data.C'("NBtag",0)'
#  root -l -b -q Plot_Commissioning_Data.C'("HT",0)'
#  root -l -b -q Plot_Commissioning_Data.C'("MHT",0)'
#  root -l -b -q Plot_Commissioning_Data.C'("DelPhi1",0)'
#  root -l -b -q Plot_Commissioning_Data.C'("DelPhi2",0)'
#  root -l -b -q Plot_Commissioning_Data.C'("DelPhi3",0)'

   root -l -b -q Plot_Commissioning.C'("HT2","delphi",40.0,"SingleMuon",false,0,0.15,0.955)'
   root -l -b -q Plot_Commissioning.C'("MHT2","delphi",40.0,"SingleMuon",false,0,0.15,0.955)'
   root -l -b -q Plot_Commissioning.C'("NJet","delphi",40.0,"SingleMuon",false,0,0.15,0.955)'
   root -l -b -q Plot_Commissioning.C'("NBtag","delphi",40.0,"SingleMuon",false,0,0.15,0.955)'

  root -l -b -q Plot_searchBin_full_Data.C'("stacked","searchH_b",1)'
  root -l -b -q Plot_searchBin_Data.C'("stacked","searchH",1)'
  echo "stacked"
fi
