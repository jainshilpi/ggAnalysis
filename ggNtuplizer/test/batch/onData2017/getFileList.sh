#!/bin/bash

voms-proxy-init --voms cms

input_datasets="list2get.txt"
for dataset in `sed '/^$/d' ${input_datasets}`;
do
	jobName=$(echo ${dataset} | cut -f1-3 -d'/')
	# jobName=$(echo ${dataset} | cut -f1,2 -d'/')
	jobName=${jobName#"_"}
	jobName=$(echo ${jobName} | sed 's/[^a-zA-Z0-9]//g')
	
	echo -e "\n\n"${dataset}
	outFile=samplesXRD/${jobName}.txt
	echo $outFile
	# # dasgoclient --query="summary dataset=${dataset}"  | tee ${outFile}
	dasgoclient --query="file dataset=${dataset}"  | tee ${outFile}
	sed -i -e 's/^/root:\/\/cmsxrootd.fnal.gov\//' ${outFile}
done 
