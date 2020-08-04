#!/bin/bash

### syntax:  bash csub.sh [path_to_ntuple_lists]  [write_directory]

cmsswfile="/cvmfs/cms.cern.ch/cmsset_default.sh"
cmsswDir=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/
# workDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"/

jobList=$1
writeDir=/local/cms/user/wadud/aNTGCmet/ntuples/METv5data/
jobsDir=${writeDir}
workDir=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onData2017/jobsMETv5/


# espresso     = 20 minutes
# microcentury = 1 hour
# longlunch    = 2 hours
# workday      = 8 hours
# tomorrow     = 1 day
# testmatch    = 3 days
# nextweek     = 1 week

jobflavor=testmatch
splitfiles=10


############################################################################
runScriptTemplate=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onData2017//runOnDataTemplate.sh
condorCFGtemplate=/local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onData2017//condor_job.sh

mkdir -p ${writeDir}

current_date_time=$(date +%Y-%m-%d_%H-%M-%S)

echo $current_date_time;
echo -e "\n\n"echo 'Work directory = '${workDir}''
echo 'Job directory = '${jobsDir}''
echo 'Write directory = '${writeDir}''
echo 'Job list = '${jobList}''


function preSelectDataset(){
	#### grab inputs ####
	fileListPath=$(echo $1 | tr -d '\040\011\012\015')
	jobName=$(echo $2 | tr -d '\040\011\012\015')
	jobDir=$(echo $3 | tr -d '\040\011\012\015')
	writeOutDir=$(echo $4 | tr -d '\040\011\012\015')
	logDir=${jobDir}/log/
	

	#### display inputs ####
	echo	-e		"\t\t Creating job for " ${fileListPath}
	echo 	-e		"\t\t Job name "${jobName}
	echo 	-e		"\t\t Job directory "${jobDir}
	echo 	-e		"\t\t Ouput directory "${writeOutDir}
	
	#### check that file list exists ####
	if [ ! -f ${fileListPath} ]; then
		echo "Error! File not found! Offending file: " ${fileListPath}
		exit
	fi

	nFiles=$(sed -n '=' ${fileListPath} | wc -l)
	echo	-e	"\t\t# of files = " ${nFiles}

	#### output root file ###
	outFile=${writeOutDir}/${jobName}.root
	echo	-e	"\t\tOutput file = "${outFile}

	### prepare run script ###
	runScript=${jobDir}/${jobName}.sh
	cp ${runScriptTemplate} ${runScript}
	sed -i 's|#cmsswDir|'${cmsswDir}'|g' ${runScript}
	sed -i 's|#cmssetsh|'${cmsswfile}'|g' ${runScript}
	sed -i 's|#jobDir|'${jobDir}'|g' ${runScript}
	sed -i 's|#jobName|'${jobName}'|g' ${runScript}
	sed -i 's|#jobList|'${fileListPath}'|g' ${runScript}
	sed -i 's|#outFile|'${outFile}'|g' ${runScript}
	
	chmod +x ${runScript}

	### prepare condor script ###
	condorCFG=${jobDir}/condor_${jobName}.sh
	cp ${condorCFGtemplate} ${condorCFG}


	sed -i 's|#script|'${runScript}'|g' ${condorCFG}
	sed -i 's|#logDir|'${logDir}'|g' ${condorCFG}
	sed -i 's|#jobName|'${jobName}'|g' ${condorCFG}
	sed -i 's|#jobflavour|'${jobflavor}'|g' ${condorCFG}


	chmod +x ${condorCFG}

	
	cd ${jobDir}
	##bash ${runScript}
	condor_submit ${condorCFG}
	cd ${workDir}
}


[ ! -f $jobList ] && { echo "$jobList file not found"; exit 99; }


jobBaseName=$(basename "${jobList}")
jobBaseName="${jobBaseName%.*}"
jobBaseName=$(echo ${jobBaseName} | tr -cd [:alnum:])

jobDir=${workDir}/${jobBaseName}/
logDir=${jobDir}/log/
mkdir -p ${logDir}
mkdir -p ${jobDir}/jobReport/

nFiles=$(sed -n '=' ${jobList} | wc -l)
echo	-e	"\t # of files in base job = " ${nFiles}

split -d -a 3 -l ${splitfiles} ${jobList} ${jobDir}/${jobBaseName}_

echo -e "***********************************************************************************************************************************************"
echo -e "***********************************************************************************************************************************************"
echo -e "\n Preparing job: List = ${jobList} ouput directory = ${jobDir}"

for subJobList in $(find "${jobDir}" -name "${jobBaseName}_*");
do

	echo -e "\n Submitting job: ${subJobList}"

	jobName=$(basename ${subJobList})
	jobName="${jobName%.*}"
	echo -e	"\t Submitting "${jobName}
	mkdir -p ${writeDir}/${jobBaseName}/
	preSelectDataset ${subJobList} ${jobName} ${jobDir} ${writeDir}/${jobBaseName}/

done

echo -e "***********************************************************************************************************************************************"


echo "Submission complete!"
current_date_time=$(date +%Y-%m-%d_%H-%M-%S)
echo $current_date_time;
