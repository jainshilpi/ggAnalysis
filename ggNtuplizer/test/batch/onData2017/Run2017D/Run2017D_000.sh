#!/bin/bash

hostname

source /cvmfs/cms.cern.ch/cmsset_default.sh

cd /local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/ggAnalysis/ggNtuplizer/test/ 

eval `scramv1 runtime -sh`

cmsRun --jobreport=/local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/ggAnalysis/ggNtuplizer/test/batch/onData2017//Run2017D//jobReport/Run2017D_000.xml /local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/ggAnalysis/ggNtuplizer/test/run_condor_data2017_94X.py InputFileList=/local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/ggAnalysis/ggNtuplizer/test/batch/onData2017//Run2017D/Run2017D_000 outputFile=/local/cms/user/wadud/aNTGCmet/ntuples/METv4//Run2017D_000.root maxEvents=-1
