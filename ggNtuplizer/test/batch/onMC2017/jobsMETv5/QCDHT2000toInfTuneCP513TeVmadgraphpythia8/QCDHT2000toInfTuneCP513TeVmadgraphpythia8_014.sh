#!/bin/bash

hostname

source /cvmfs/cms.cern.ch/cmsset_default.sh

cd /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/ 

eval `scramv1 runtime -sh`

cmsRun --jobreport=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsMETv5//QCDHT2000toInfTuneCP513TeVmadgraphpythia8//jobReport/QCDHT2000toInfTuneCP513TeVmadgraphpythia8_014.xml /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test//run_condor_mc2017_94X.py InputFileList=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsMETv5//QCDHT2000toInfTuneCP513TeVmadgraphpythia8/QCDHT2000toInfTuneCP513TeVmadgraphpythia8_014 outputFile=/local/cms/user/wadud/aNTGCmet/ntuples/METv5/QCDHT2000toInfTuneCP513TeVmadgraphpythia8//QCDHT2000toInfTuneCP513TeVmadgraphpythia8_014.root maxEvents=-1
