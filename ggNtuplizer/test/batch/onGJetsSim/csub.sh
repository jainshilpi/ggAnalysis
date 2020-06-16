#!/bin/bash

writeDir=$1
nEvtsPerJob=$2
nJobs=$3



nThreads=4
jobflavor=testmatch

# espresso     = 20 minutes
# microcentury = 1 hour
# longlunch    = 2 hours
# workday      = 8 hours
# tomorrow     = 1 day
# testmatch    = 3 days
# nextweek     = 1 week

nEvtPuFile=1200
nPUfiles=50
puPremixListFile=/local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/Configuration/Generator/generateGJets4ID/puPremixSubset.txt
runScriptTemplate=/local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/Configuration/Generator/generateGJets4ID/batch/submit_job.sh
condorCFGtemplate=/local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/Configuration/Generator/generateGJets4ID/batch/condor_job.sh
step1cfgTemplate=/local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/Configuration/Generator/generateGJets4ID/aNTGC_GJets_step1.py
step2cfgTemplate=/local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/Configuration/Generator/generateGJets4ID/aNTGC_GJets_step2.py
cmsswfile="/cvmfs/cms.cern.ch/cmsset_default.sh"
cmsswDir=/local/cms/user/wadud/aNTGCmet/CMSSW_9_4_17/src/
workDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"/

replacePUText="'puFile'"

mkdir -p ${writeDir}

current_date_time=$(date +%Y-%m-%d_%H-%M-%S)
echo $current_date_time;
echo -e "\n\n"echo 'Work directory = '${workDir}''
echo -e 'Write directory = '${writeDir}''

[ ! -f $pileupList ] && { echo "$pileupList file not found"; exit 99; }

function pickRandomPU(){
	puList=$1
	nFiles=$2
	list=($(shuf -n ${nFiles} ${puList}))
	delimitedlist=""
	for file in ${list[@]};
	do
		delimitedList+="'"
		delimitedList+=file:${file}
		delimitedList+="', "
	done
	delimitedList=${delimitedList%", "}
	echo ${delimitedList}
}


for iJob in $(seq 1 $nJobs)
do
	jobName=GJetsEMenriched_$iJob
	jobDir=${writeDir}/${jobName}/
	runScript=${jobDir}/${jobName}.sh

	if [ -d "${jobDir}" ]; then
		# rm -rf ${jobDir}
		echo -e "\t Error! Job directory already exists "${jobDir}
		continue
	fi

	mkdir -p ${jobDir}

	echo -e "***********************************************************************************************************************************************"
	echo -e "\n\tPreparing job #" $jobName ", # of events = "${nEvtsPerJob}
	echo -e	"\tOutput directory = "${jobDir}

	### prepare step1cfg ###
	step1cfg=${jobDir}/${jobName}_s1.py
	cp ${step1cfgTemplate} ${step1cfg}
	puFileList=$(pickRandomPU ${puPremixListFile} ${nPUfiles})
	gensimfile=${jobDir}/${jobName}_GENSIM.root
	# sed -i 's#'"'"'puFile'"'"'#'${puFileList}'#g' ${step1cfg}

	sed -i "s|${replacePUText}|${puFileList}|g" ${step1cfg}

	sed -i 's|gensimfile|'${gensimfile}'|g' ${step1cfg}
	sed -i 's|12345|'${nEvtsPerJob}'|g' ${step1cfg}

	### prepare step2cfg ###
	step2cfg=${jobDir}/${jobName}_s2.py
	cp ${step2cfgTemplate} ${step2cfg}
	miniaodsimfile=${jobDir}/${jobName}_MINIAODSIM.root
	sed -i 's|gensimfile|'${gensimfile}'|g' ${step2cfg}
	sed -i 's|miniaodsimfile|'${miniaodsimfile}'|g' ${step2cfg}
	sed -i 's|12345|'${nEvtsPerJob}'|g' ${step2cfg}

	### prepare run script ###
	runScript=${jobDir}/${jobName}.sh
	cp ${runScriptTemplate} ${runScript}
	sed -i 's|#cmsswdir|'${cmsswDir}'|g' ${runScript}
	sed -i 's|#cmssetsh|'${cmsswfile}'|g' ${runScript}
	sed -i 's|#jobdir|'${jobDir}'|g' ${runScript}
	sed -i 's|#step1cfg|'${step1cfg}'|g' ${runScript}
	sed -i 's|#step2cfg|'${step2cfg}'|g' ${runScript}

	chmod +x ${runScript}

	### prepare condor script ###
	condorCFG=${jobDir}/condor_${jobName}.sh
	cp ${condorCFGtemplate} ${condorCFG}
	sed -i 's|#script|'${runScript}'|g' ${condorCFG}
	sed -i 's|#writeDir|'${jobDir}'|g' ${condorCFG}
	sed -i 's|#jobname|'${jobName}'|g' ${condorCFG}
	sed -i 's|#step1cfg|'${step1cfg}'|g' ${condorCFG}
	sed -i 's|#step2cfg|'${step2cfg}'|g' ${condorCFG}
	sed -i 's|#jobflavour|'${jobflavor}'|g' ${condorCFG}
	sed -i 's|#nThreads|'${nThreads}'|g' ${condorCFG}
	
	cd ${jobDir}
	##bash ${runScript}
	# condor_submit ${condorCFG}
	cd ${workDir}

	echo -e "***********************************************************************************************************************************************"

done


echo "Submission complete!"
current_date_time=$(date +%Y-%m-%d_%H-%M-%S)
echo $current_date_time;
