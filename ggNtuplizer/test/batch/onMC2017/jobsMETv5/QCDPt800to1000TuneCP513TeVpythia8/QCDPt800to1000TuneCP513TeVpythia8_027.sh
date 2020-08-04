#!/bin/bash

hostname

source /cvmfs/cms.cern.ch/cmsset_default.sh

cd /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/ 

eval `scramv1 runtime -sh`

cmsRun --jobreport=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsMETv5//QCDPt800to1000TuneCP513TeVpythia8//jobReport/QCDPt800to1000TuneCP513TeVpythia8_027.xml /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test//run_condor_mc2017_94X.py InputFileList=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsMETv5//QCDPt800to1000TuneCP513TeVpythia8/QCDPt800to1000TuneCP513TeVpythia8_027 outputFile=/local/cms/user/wadud/aNTGCmet/jobsMETv5//QCDPt800to1000TuneCP513TeVpythia8//QCDPt800to1000TuneCP513TeVpythia8_027.root maxEvents=-1
