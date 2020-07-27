#!/bin/bash

hostname

source #cmssetsh

cd #cmsswDir 

eval `scramv1 runtime -sh`

cmsRun --jobreport=#jobDir/jobReport/#jobName.xml /local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/ggAnalysis/ggNtuplizer/test/run_condor_data2017_94X.py InputFileList=#jobList outputFile=#outFile maxEvents=-1
