#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh

date

hName=$(hostname)
echo -e "Running on "$hName

cd #cmsswDir 

eval `scramv1 runtime -sh`

export X509_USER_PROXY=#X509FILE
voms-proxy-info -all
voms-proxy-info -all -file ${X509_USER_PROXY}

if [ ! -f "$X509_USER_PROXY" ]; then
    echo "ERROR! x509 proxy wasn't found!!"
    exit 113
fi

echo -e "\n\n"

git show --format="%h %T %cn %cI %s" --no-patch

echo -e "\n\n"

cmsRun --jobreport=#jobDir/jobReport/#jobName.xml #pset InputFileList=#jobList outputFile=#outFile maxEvents=-1

echo -e "Complete!"

date