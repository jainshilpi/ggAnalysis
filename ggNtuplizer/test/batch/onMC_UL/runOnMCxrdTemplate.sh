#!/bin/bash

source /cvmfs/cms.cern.ch/cmsset_default.sh

date

hName=$(hostname)
echo -e "Running on "$hName

cd #cmsswDir 

eval `scramv1 runtime -sh`

export X509_USER_PROXY=#X509FILE
voms-proxy-info -all
if [ ! -f "$X509_USER_PROXY" ]; then
    echo "ERROR! x509 proxy wasn't found!!"
    exit 113
fi
voms-proxy-info -all -file ${X509_USER_PROXY}

echo -e "\n\n"

git show --format="%h %T %cn %cI %s" --no-patch

echo -e "\n\n"

n=0
until [ "$n" -ge #nRetries ]
do
	echo -e "Try number "$n

	date

	cmsRun --jobreport=#jobDir/jobReport/#jobName.xml #pset InputFileList=#jobList outputFile=#outFile maxEvents=-1 && break

	n=$((n+1)) 

	sleep 10
done

echo -e "Complete!"

date