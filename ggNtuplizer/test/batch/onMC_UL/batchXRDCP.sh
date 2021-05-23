#!/bin/bash

### syntax:  bash batchXRDCP.sh [path to file list]  [write_directory]

jobList=$1
writeDir=$2
logFile=$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )/copyLog_$(date '+%d_%m_%Y_%H_%M_%S').log

exec 3>&1 4>&2
trap 'exec 2>&4 1>&3' 0 1 2 3
exec 1> >(tee -ia ${logFile}) 2>&1

hostname

voms-proxy-init --voms cms --valid 720:00

echo -e "Copying via XRDCP (xrdcp root://cmsxrootd.fnal.gov//) files listed in "${jobList} " to " ${writeDir}

mkdir -p ${writeDir}

lastCheckedFile=""

echo $(date '+%d_%m_%Y_%H_%M_%S')
function copyFile(){
	originalPath=$1
	fileName=$(basename ${originalPath})
	trimmedPath=$(cut -d/ -f4-8 <<< ${originalPath})
	destinationDirectory=${writeDir}/${trimmedPath}/
	destinationPath=${writeDir}/${trimmedPath}/${fileName}	

	if [ ! -d ${destinationDirectory} ];
	then
		echo -e "Making directory " ${destinationDirectory}
		mkdir -p ${destinationDirectory}
	fi

	if [[ -f ${destinationPath} ]]
	then
		echo "${destinationPath} exists on your filesystem."
		continue
		# rm -rf ${destinationPath}
	fi

	echo -e "\t\t xrdcp -v "${originalPath} ${destinationDirectory}/

	xrdcp -vf ${originalPath} ${destinationDirectory}/
}

echo -e "Log file: "${logFile}
echo -e "********************************************************************************************************************************"
for iFile in `sed '/^$/d' ${jobList}`;
do
	copyFile ${iFile}
	echo -e "********************************************************************************************************************************"
	echo -e "\n\n"
done

echo -e "Done!"
