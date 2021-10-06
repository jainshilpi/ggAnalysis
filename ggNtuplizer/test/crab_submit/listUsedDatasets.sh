#!/bin/bash
 
jobDir=$1

function getDatsetName(){
	_pyFile=$1
	DIR="$(dirname "${_pyFile}")"
	DIR=${DIR#*crab_}

	# datasetString=$(grep "config.Data.inputDataset" ${_pyFile})

	datasetString=$(grep "u'inputDataset': u'" ${_pyFile})

	# echo $datasetString ${DIR}

	# if [[ -z "$datasetString" ]]
	# then
	# 	continue
	# fi
	
	datasetString=${datasetString%, u\'userWebDirURL*}
	datasetString=${datasetString#*"u'inputDataset': u'"}
	# # datasetString=$(echo $datasetString | sed "s/config.Data.inputDataset//g")
	# datasetString=$(echo $datasetString | sed "s/'//g")
	# # datasetString=$(echo $datasetString | sed 's/=//g')
	# # datasetString=$(echo $datasetString | sed 's/ //g')

	echo ${DIR}, ${datasetString}

	# # isPreVFP=$datasetString
	# # _SampleName=$(echo ${datasetString} | cut -f2,3 -d'/')
	# # _SampleName=${_SampleName#"_"}
	# # _SampleName=$(echo ${_SampleName} | sed 's/[^a-zA-Z0-9]//g')
	# # _SampleName=${_SampleName%mc201*}
	# # _SampleName=${_SampleName%mcRun2*}

	# # if [[ "$isPreVFP" == *"preVFP"* ]]; then
	# # 	_SampleName=${_SampleName}"preVFP"
	# # fi	

	# # _SampleName=${_SampleName%upgrade2018*}

	# # echo ${_SampleName}, ${datasetString}
}


for configFile in $(find "${jobDir}" -type f -name "crab.log" | sort); do
	
	# echo $configFile
	getDatsetName $configFile

done