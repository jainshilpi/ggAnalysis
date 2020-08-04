#!/bin/bash

hostname

source /cvmfs/cms.cern.ch/cmsset_default.sh

cd /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/ 

eval `scramv1 runtime -sh`

cmsRun --jobreport=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsXsec//QCDHT300to500TuneCP513TeVmadgraphpythia8//jobReport/QCDHT300to500TuneCP513TeVmadgraphpythia8_000.xml /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/XsecAna.py InputFileList=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsXsec//QCDHT300to500TuneCP513TeVmadgraphpythia8/QCDHT300to500TuneCP513TeVmadgraphpythia8_000 outputFile=/local/cms/user/wadud/aNTGCmet/Xsecs//QCDHT300to500TuneCP513TeVmadgraphpythia8//QCDHT300to500TuneCP513TeVmadgraphpythia8_000.root maxEvents=-1
