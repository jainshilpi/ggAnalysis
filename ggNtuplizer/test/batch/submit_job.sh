#!/bin/bash
echo $(hostname)

current_date_time="`date +%Y-%m-%d-%H:%M:%S`";
echo "Begin script @ " $current_date_time

workDir=/local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/ggAnalysis/ggNtuplizer/test/batch/

source /cvmfs/cms.cern.ch/cmsset_default.sh
cd /local/cms/user/wadud/aNTGCmet/slc6/CMSSW_9_4_17/src/; eval `scramv1 runtime -sh`; cd $workDir;

outFileName=$(basename $1)
outFileName=/local/cms/user/wadud/aNTGCmet/slc6/CMSSW_9_4_17/src/Configuration/Generator/generateGJets4ID/ntuplesProd_2020_04_15/${outFileName%MINIAODSIM.root}_aNTGC.root

cmsRun /local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/ggAnalysis/ggNtuplizer/test/run_mc2017_94X.py inputFiles=file:$1 outputFile=${outFileName}

current_date_time="`date +%Y-%m-%d-%H:%M:%S`";
echo "End script @ " $current_date_time
