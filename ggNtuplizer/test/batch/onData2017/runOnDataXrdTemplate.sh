#!/bin/bash

hostname

source #cmssetsh

cd #cmsswDir 

eval `scramv1 runtime -sh`

export X509_USER_PROXY=#X509FILE
voms-proxy-info -all
voms-proxy-info -all -file ${X509_USER_PROXY}

if [ ! -f "$X509_USER_PROXY" ]; then
    echo "ERROR! x509 proxy wasn't found!!"
    exit 113
fi

cmsRun --jobreport=#jobDir/jobReport/#jobName.xml #pset InputFileList=#jobList outputFile=#outFile maxEvents=-1
