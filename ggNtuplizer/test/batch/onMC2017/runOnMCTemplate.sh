#!/bin/bash

hostname

source #cmssetsh

cd #cmsswDir 

eval `scramv1 runtime -sh`

cmsRun --jobreport=#jobDir/jobReport/#jobName.xml #pset InputFileList=#jobList outputFile=#outFile maxEvents=-1
