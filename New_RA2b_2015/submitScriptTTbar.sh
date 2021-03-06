#!/bin/sh

ArgOne=$1   # 
ArgTwo=$2   # 
ArgThree=$3 # 
ArgFour=$4  # 
ArgFive=$5  # 
ArgSix=$6   # 
ArgSeven=$7 #  

#
# first go to the submission dir, and set up the environment
#
cd $ArgSeven 
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scram runtime -sh`

#
# now go to the condor's scratch area, where we copied the contents of New_RA2b_2015
#
cd ${_CONDOR_SCRATCH_DIR} 

#
# run the job
#
$ArgOne $ArgTwo $ArgThree "." $ArgFive $ArgSix

