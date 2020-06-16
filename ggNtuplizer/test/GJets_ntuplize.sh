#!/usr/bin/bash

workDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"/

source /cvmfs/cms.cern.ch/cmsset_default.sh
cd $workDir; eval `scramv1 runtime -sh`; cd -;

MINIAODlist=/local/cms/user/wadud/aNTGCmet/slc6/CMSSW_9_4_17/src/Configuration/Generator/generateGJets4ID/Prod_2020_04_15.txt
outputFile=/local/cms/user/wadud/aNTGCmet/slc6/CMSSW_9_4_17/src/Configuration/Generator/generateGJets4ID/Prod_2020_04_15_out.root

inFileParam=""
while IFS= read -r inFile
do
	inFileParam="${inFileParam} inputFiles=file:${inFile}"
done < "$MINIAODlist"

cmsRun run_mc2017_94X.py outputFile=$outputFile $inFileParam