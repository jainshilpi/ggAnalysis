#!/bin/bash
 
# for configFile in $(find jobs -mindepth 4 -maxdepth 4 -type f -name "crab*.log" | sort); do

# 	jobName=$(basename $(dirname ${configFile}))
# 	jobName=${jobName##*crab_}

# 	datasetName=$(grep "inputDataset" ${configFile})

# 	datasetName=${datasetName##*"inputDataset"}
# 	datasetName=${datasetName%%"userWebDirURL"*}
# 	datasetName=${datasetName#*"'"}
# 	datasetName=${datasetName#*"u'"}
# 	datasetName=${datasetName%%"'"*}

# 	echo $jobName, $datasetName

# done


for configFile in $(find jobs -mindepth 3 -maxdepth 3 -type f -name "crab*.py" | sort); do

	jobName=$(basename $(dirname ${configFile}))
	jobName=${jobName##*crab_}

	datasetName=$(grep "inputDataset" ${configFile})

	datasetName=${datasetName##*"inputDataset"}
	datasetName=${datasetName%%"userWebDirURL"*}
	datasetName=${datasetName#*"'"}
	datasetName=${datasetName#*"u'"}
	datasetName=${datasetName%%"'"*}

	echo $jobName, $datasetName

done