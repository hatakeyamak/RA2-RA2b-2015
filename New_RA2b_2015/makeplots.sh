#!/bin/bash

i=$1
j=$2
k=$3
l=$4

if [ $i -eq 1 ]
then
  #######################################################
  # TTbar
  #######
#  root -l -b -q Plot_closure.C'("mht_200","NJet","TTbar_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","NBtag","TTbar_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","HT","TTbar_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","MHT","TTbar_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","DelPhi1","TTbar_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","DelPhi2","TTbar_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","DelPhi3","TTbar_stacked",1)'



  root -l -b -q Plot_closure.C'("delphi","NJet","TTbar_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","NBtag","TTbar_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","HT","TTbar_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","MHT","TTbar_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","DelPhi1","TTbar_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","DelPhi2","TTbar_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","DelPhi3","TTbar_stacked",1)'

  root -l -b -q Plot_searchBin_full.C'("TTbar_stacked","searchH_b",1)'
  root -l -b -q Plot_searchBin.C'("TTbar_stacked","searchH",1)'

fi
########################################################
#WJet
#####

if [ $j -eq 1 ]; then 
#  root -l -b -q Plot_closure.C'("mht_200","NJet","WJet_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","NBtag","WJet_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","HT","WJet_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","MHT","WJet_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","DelPhi1","WJet_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","DelPhi2","WJet_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","DelPhi3","WJet_stacked",1)'



  root -l -b -q Plot_closure.C'("delphi","NJet","WJet_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","NBtag","WJet_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","HT","WJet_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","MHT","WJet_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","DelPhi1","WJet_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","DelPhi2","WJet_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","DelPhi3","WJet_stacked",1)'
  root -l -b -q Plot_searchBin_full.C'("WJet_stacked","searchH_b",1)'
  root -l -b -q Plot_searchBin.C'("WJet_stacked","searchH",1)'

fi
########################################################
#Single Top
#####

if [ $k -eq 1 ]; then 
#  root -l -b -q Plot_closure.C'("mht_200","NJet","T_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","NBtag","T_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","HT","T_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","MHT","T_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","DelPhi1","T_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","DelPhi2","T_stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","DelPhi3","T_stacked",1)'



  root -l -b -q Plot_closure.C'("delphi","NJet","T_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","NBtag","T_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","HT","T_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","MHT","T_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","DelPhi1","T_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","DelPhi2","T_stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","DelPhi3","T_stacked",1)'
  root -l -b -q Plot_searchBin_full.C'("T_stacked","searchH_b",1)'
  root -l -b -q Plot_searchBin.C'("T_stacked","searchH",1)'

fi
########################################################
#TTbar+WJet+SingleT
#####

if [ $l -eq 1 ]; then

#  root -l -b -q Plot_closure.C'("mht_200","NJet","stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","NBtag","stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","HT","stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","MHT","stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","DelPhi1","stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","DelPhi2","stacked",1)'
#  root -l -b -q Plot_closure.C'("mht_200","DelPhi3","stacked",1)'



  root -l -b -q Plot_closure.C'("delphi","NJet","stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","NBtag","stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","HT","stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","MHT","stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","DelPhi1","stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","DelPhi2","stacked",1)'
  root -l -b -q Plot_closure.C'("delphi","DelPhi3","stacked",1)'

  root -l -b -q Plot_searchBin_full.C'("stacked","searchH_b",1)'
  root -l -b -q Plot_searchBin.C'("stacked","searchH",1)'

fi
