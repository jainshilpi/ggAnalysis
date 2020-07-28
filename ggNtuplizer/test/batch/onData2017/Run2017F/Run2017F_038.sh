#!/bin/bash

hostname

source /cvmfs/cms.cern.ch/cmsset_default.sh

cd /local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/ggAnalysis/ggNtuplizer/test/ 

eval `scramv1 runtime -sh`

cmsRun --jobreport=/local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/ggAnalysis/ggNtuplizer/test/batch/onData2017//Run2017F//jobReport/Run2017F_038.xml /local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/ggAnalysis/ggNtuplizer/test/run_condor_data2017_94X.py InputFileList=/local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/ggAnalysis/ggNtuplizer/test/batch/onData2017//Run2017F/Run2017F_038 outputFile=/local/cms/user/wadud/aNTGCmet/ntuples/METv4/SinglePhoton2017//Run2017F_038.root maxEvents=-1