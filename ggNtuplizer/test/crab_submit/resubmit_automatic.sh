#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh;
source /cvmfs/cms.cern.ch/crab3/crab.sh;
eval `scramv1 runtime -sh`;
voms-proxy-init --voms cms --valid 720:00


repeatHours=345600

START=`date +%s`
while [ $(( $(date +%s) - ${repeatHours} )) -lt $START ]; do
	find /afs/hep.wisc.edu/user/rusack/private/CMSSW_10_6_24/src/ggAnalysis/ggNtuplizer/test/crab_submit/jobs/jobsUL2017v1 -maxdepth 2 -mindepth 2 -type d -name "crab*" -exec sh -c "basename {}; crab resubmit -d {} --maxjobruntime 5000" {} \;
	sleep 10m
done
