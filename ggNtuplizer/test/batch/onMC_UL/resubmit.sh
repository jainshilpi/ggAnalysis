#!/bin/bash

searchDir=$1
doResubmit=$2

voms-proxy-init --voms cms --valid 720:00

x509file=/tmp/x509up_u926763

if [ -z "$searchDir" ]; then
	exit
fi

FILES=($(find ${searchDir} -name "*.err" 2>/dev/null)) 

declare finished_jobs
declare running_jobs

echo -e "Resubmitting Failed Tasks: "
FILES=($(find ${searchDir} -name "*.log" 2>/dev/null)) 

mkdir -p failed
rm -rf failed/failed.txt

function xrdInFiles(){
	condorFile=$1
	inFileList=$(echo ${condorFile} | sed 's|condor_||g')
	inFileList=${inFileList%.sh}
	cat ${inFileList} | tee -a failed/failed.txt
}

function resubmit(){
	file=$1
	fileName=$(basename $file)
	pathName=$(dirname $file)
	pathName=${pathName%log}
	condorFile=${pathName}/condor_${fileName}
	condorFile=${condorFile%.*}.sh

	if [ ! -f $condorFile ]; then
		return 0
	fi

	x509cpy=${pathName}/X509fl
	cp  ${x509file} ${x509cpy}
	# echo $x509cpy

	if [ -z "$doResubmit" ];	then
    	echo $condorFile
		condor_submit $condorFile
	else	
		logFile=${pathName}/log/${fileName%.*}.out
		echo $logFile
		xrdInFiles ${condorFile}
	fi
}

for file in "${FILES[@]}"; do
	file=$(readlink -e $file)
	fileName=$(basename $file)

	normTermLine=$(tac $file | grep -m 1 "Normal termination")
	killLine=$(tac $file | grep -m 1 "Job was aborted by the user")
	updateLine=$(tac $file | grep -m 1 "Image size of job updated")
	submittedN=$(tac $file | grep -n -m 1 "Job submitted from host" | cut -d : -f 1)
	hostLine=$(tac $file | grep -m 1 "Job executing on host")	
	hostLineN=$(tac $file | grep -n -m 1 "Job executing on host" | cut -d : -f 1)

	jobID=${hostLine#*\(}
	jobID=${jobID%\)*}
	jobID=${jobID%00.000*}	

	hostName=${hostLine#*<}
	hostName=${hostName%:*}


	updateN=$(tac $file | grep -n -m 1 "Image size of job updated" | cut -d : -f 1)
	
	if grep -q "Normal termination (return value 0)" "$file"; then
		finished_jobs+="\t"
		finished_jobs+=$fileName
		finished_jobs+="\n"
		continue;	
	fi

	if ( [ ! -z "$normTermLine" ] && [ ! -z "$killLine" ] ); then
		normTermLineN=$(tac $file | grep -n -m 1 "Normal termination" | cut -d : -f 1)
		killLineN=$(tac $file | grep -n -m 1 "Job was aborted by the user" | cut -d : -f 1)
		
		if ( ( [ "$updateN" -lt "$killLineN" ]  && [ "$updateN" -lt "$normTermLineN" ] ) || ( [ "$submittedN" -lt "$killLineN" ] && [ "$submittedN" -lt "$normTermLineN" ] ) );then
			continue
		fi

		resubmit $file
	elif ( [ ! -z "$normTermLine" ] ); then
		normTermLineN=$(tac $file | grep -n -m 1 "Normal termination" | cut -d : -f 1)

		if ( [ "$updateN" -lt "$normTermLineN" ] || [ "$submittedN" -lt "$normTermLineN" ] );then
			continue
		fi

		resubmit $file
	elif ( [ ! -z "$killLine" ] ); then
		killLineN=$(tac $file | grep -n -m 1 "Job was aborted by the user" | cut -d : -f 1)
		updateN=$(tac $file | grep -n -m 1 "Image size of job updated" | cut -d : -f 1)

		if ( [ "$updateN" -lt "$killLineN" ] || [ "$submittedN" -lt "$killLineN" ] );then
			continue
		fi

		resubmit $file
	fi
done

nFinished=$(echo -e "$finished_jobs" | wc -l)
nFinished=$((nFinished - 1))
echo -e "\n\n\n\nFinished jobs:" $nFinished
echo -e "$finished_jobs" | sort
