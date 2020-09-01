#!/bin/bash

hostname

source /cvmfs/cms.cern.ch/cmsset_default.sh

cd /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/ 

eval `scramv1 runtime -sh`

cmsRun --jobreport=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsMETv5//QCDPt1400to1800TuneCP513TeVpythia8//jobReport/QCDPt1400to1800TuneCP513TeVpythia8_003.xml /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test//run_condor_mc2017_94X.py InputFileList=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsMETv5//QCDPt1400to1800TuneCP513TeVpythia8/QCDPt1400to1800TuneCP513TeVpythia8_003 outputFile=/local/cms/user/wadud/aNTGCmet/ntuples/METv5//QCDPt1400to1800TuneCP513TeVpythia8//QCDPt1400to1800TuneCP513TeVpythia8_003.root maxEvents=-1
