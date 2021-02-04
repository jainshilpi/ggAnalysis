#!/bin/bash

### syntax:  bash csub.sh [path_to_ntuple_lists]


jobsList='runList.txt'

voms-proxy-init --voms cms --valid 720:00

cmsswfile="/cvmfs/cms.cern.ch/cmsset_default.sh"
cmsswDir=/local/cms/user/wadud/aNTGCmet/CMSSW_10_6_9/src/ggAnalysis/ggNtuplizer/test/
# workDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"/

writeDir=/local/cms/user/wadud/aNTGCmet/Xsecs/
workDir=/local/cms/user/wadud/aNTGCmet/CMSSW_10_6_9/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsXsecSignals/
pset="/local/cms/user/wadud/aNTGCmet/CMSSW_10_6_9/src/ggAnalysis/ggNtuplizer/test/XsecAna.py"
splitfiles=200000


# writeDir=/local/cms/user/wadud/aNTGCmet/ntuples/METv5/
# workDir=/local/cms/user/wadud/aNTGCmet/CMSSW_10_6_9/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsMETv5Signals/
# pset="/local/cms/user/wadud/aNTGCmet/CMSSW_10_6_9/src/ggAnalysis/ggNtuplizer/test//run_condor_mc2017_94X.py"
# splitfiles=34


x509file=/tmp/x509up_u926763

if [ ! -f "$x509file" ]; then
	echo "ERROR! x509 proxy file could not be found!"
fi


jobsDir=${writeDir}


# espresso     = 20 minutes
# microcentury = 1 hour
# longlunch    = 2 hours
# workday      = 8 hours
# tomorrow     = 1 day
# testmatch    = 3 days
# nextweek     = 1 week

jobflavor=workday


############################################################################
runScriptTemplate=/local/cms/user/wadud/aNTGCmet/CMSSW_10_6_9/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017//runOnMCxrdTemplate.sh
condorCFGtemplate=/local/cms/user/wadud/aNTGCmet/CMSSW_10_6_9/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017//condor_job.sh

mkdir -p ${writeDir}

current_date_time=$(date +%Y-%m-%d_%H-%M-%S)

echo $current_date_time;
echo -e "\n\n"'Work directory = '${workDir}''
echo 'Job directory = '${jobsDir}''
echo 'Write directory = '${writeDir}''
echo 'Jobs list = '${jobList}''


function submitSubJob(){
	#### grab inputs ####
	fileListPath=$(echo $1 | tr -d '\040\011\012\015')
	jobName=$(echo $2 | tr -d '\040\011\012\015')
	jobDir=$(echo $3 | tr -d '\040\011\012\015')
	writeOutDir=$(echo $4 | tr -d '\040\011\012\015')
	logDir=${jobDir}/log/
	x509copy=$5
	

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
	sed -i 's|#pset|'${pset}'|g' ${runScript}
	sed -i 's|#jobList|'${fileListPath}'|g' ${runScript}
	sed -i 's|#outFile|'${outFile}'|g' ${runScript}
	sed -i 's|#X509FILE|'${x509copy}'|g' ${runScript}
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
	condor_submit ${condorCFG}
	cd ${workDir}
}


[ ! -f $jobList ] && { echo "$jobList file not found"; exit 99; }


function submitJob(){
	jobListFile=$1
	jobBaseName=$(basename "${jobListFile}")
	jobBaseName="${jobBaseName%.*}"
	jobBaseName=$(echo ${jobBaseName} | tr -cd [:alnum:])

	jobDir=${workDir}/${jobBaseName}/
	logDir=${jobDir}/log/
	outFileDir=${writeDir}/${jobBaseName}/

	if [[ -d ${outFileDir} ]]; then
		echo ${outFileDir} "exists! Skipping..."
		continue
	fi

	if [[ -d ${jobDir} ]]; then
		echo ${jobDir} "exists! Skipping..."
		continue
	fi

	mkdir -p ${outFileDir}
	mkdir -p ${logDir}
	mkdir -p ${jobDir}/jobReport/

	x509cpy=${jobDir}/${x509file##*/}
	cp  ${x509file} ${x509cpy}

	if [ ! -f "$x509cpy" ]; then
		echo "ERROR! x509 proxy file could not be copied!"
	fi

	nFiles=$(sed -n '=' ${jobListFile} | wc -l)
	echo	-e	"\t # of files in base job = " ${nFiles}

	split -d -a 3 -l ${splitfiles} ${jobListFile} ${jobDir}/${jobBaseName}_


	echo -e "\n\n\n***********************************************************************************************************************************************"
	echo -e "\nPreparing job: List = ${jobListFile} ouput directory = ${jobDir}"

	for subJobList in $(find "${jobDir}" -name "${jobBaseName}_*" | sort );
	do
		echo -e "\n Submitting job: ${subJobList}"

		jobName=$(basename ${subJobList})
		jobName="${jobName%.*}"
		echo -e	"\t Submitting "${jobName}

		submitSubJob ${subJobList} ${jobName} ${jobDir} ${outFileDir} ${x509cpy}

	done

	echo -e "***********************************************************************************************************************************************\n\n\n\n"
}


while read iFile; do
	submitJob $iFile
done < $jobsList


echo "Submission complete!"
current_date_time=$(date +%Y-%m-%d_%H-%M-%S)
echo $current_date_time;
