#!/bin/bash

hostname

source /cvmfs/cms.cern.ch/cmsset_default.sh

cd /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/ 

eval `scramv1 runtime -sh`

cmsRun --jobreport=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsXsec//QCDPt3200toInfTuneCP513TeVpythia8//jobReport/QCDPt3200toInfTuneCP513TeVpythia8_000.xml /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/XsecAna.py InputFileList=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsXsec//QCDPt3200toInfTuneCP513TeVpythia8/QCDPt3200toInfTuneCP513TeVpythia8_000 outputFile=/local/cms/user/wadud/aNTGCmet/Xsecs//QCDPt3200toInfTuneCP513TeVpythia8//QCDPt3200toInfTuneCP513TeVpythia8_000.root maxEvents=-1
