#!/bin/bash

hostname

source /cvmfs/cms.cern.ch/cmsset_default.sh

cd /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/ 

eval `scramv1 runtime -sh`

cmsRun --jobreport=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsMETv5//GJetsDR0p4HT200To400TuneCP513TeVmadgraphMLMpythia8v2//jobReport/GJetsDR0p4HT200To400TuneCP513TeVmadgraphMLMpythia8v2_018.xml /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test//run_condor_mc2017_94X.py InputFileList=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsMETv5//GJetsDR0p4HT200To400TuneCP513TeVmadgraphMLMpythia8v2/GJetsDR0p4HT200To400TuneCP513TeVmadgraphMLMpythia8v2_018 outputFile=/local/cms/user/wadud/aNTGCmet/ntuples/METv5/GJetsDR0p4HT200To400TuneCP513TeVmadgraphMLMpythia8v2//GJetsDR0p4HT200To400TuneCP513TeVmadgraphMLMpythia8v2_018.root maxEvents=-1
