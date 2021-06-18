#!/bin/bash

hostname

source /cvmfs/cms.cern.ch/cmsset_default.sh

cd /local/cms/user/wadud/aNTGCmet/CMSSW_10_6_25/src/ggAnalysis/ggNtuplizer/test/ 

eval `scramv1 runtime -sh`

export X509_USER_PROXY=/local/cms/user/wadud/aNTGCmet/CMSSW_10_6_25/src/ggAnalysis/ggNtuplizer/jobsResubmitUL2017v1//SinglePhotonRun2017FUL2017MiniAODv2v1//X509fl
voms-proxy-info -all
voms-proxy-info -all -file ${X509_USER_PROXY}

if [ ! -f "$X509_USER_PROXY" ]; then
    echo "ERROR! x509 proxy wasn't found!!"
    exit 113
fi

cmsRun --jobreport=/local/cms/user/wadud/aNTGCmet/CMSSW_10_6_25/src/ggAnalysis/ggNtuplizer/jobsResubmitUL2017v1//SinglePhotonRun2017FUL2017MiniAODv2v1//jobReport/SinglePhotonRun2017FUL2017MiniAODv2v1_001.xml /local/cms/user/wadud/aNTGCmet/CMSSW_10_6_25/src/ggAnalysis/ggNtuplizer/test/run_data2017_106X_HTCondor.py InputFileList=/local/cms/user/wadud/aNTGCmet/CMSSW_10_6_25/src/ggAnalysis/ggNtuplizer/jobsResubmitUL2017v1//SinglePhotonRun2017FUL2017MiniAODv2v1/SinglePhotonRun2017FUL2017MiniAODv2v1_001 outputFile=/local/cms/user/wadud/aNTGCmet/ntuples/resubmit_UL2017v1//SinglePhotonRun2017FUL2017MiniAODv2v1//SinglePhotonRun2017FUL2017MiniAODv2v1_001.root maxEvents=-1
