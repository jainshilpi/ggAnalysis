#!/bin/bash

scriptDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"/
input_datasets=${scriptDir}/"mc_UL_2017.txt"

jobsetName=jobsUL2017v1

writedir=${scriptDir}/jobs//${jobsetName}/
testDir=$(readlink -f ${scriptDir}"/..")
psetname=${testDir}"/run_mc2017_106X.py"
writeSite="T2_US_Wisconsin"
# mainOutputDir="/store/user/rusack/aNTGCmet/ntuples/UL2017/"${jobsetName}
mainOutputDir="/store/user/wadud/aNTGCmet/ntuples/UL2017/"${jobsetName}

lumiMaskFile=${scriptDir}/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt
prefiringWeights=${testDir}'/L1PrefiringMaps.root'
maxFiles=50000
inputDBS=global
# inputDBS=phys03


################################################################################################################
source /cvmfs/cms.cern.ch/cmsset_default.sh;
source /cvmfs/cms.cern.ch/crab3/crab.sh;
eval `scramv1 runtime -sh`;
voms-proxy-init --voms cms


crab_cfg_template=crab_submit.py
units_perjob=4
splitting='FileBased'
blacklist="'T2_US_Purdue'"
whitelist="'T3_US_UCR','T3_US_FNALLPC','T3_US_Rice','T3_US_Rutgers','T3_US_FIT','T3_US_PSC','T3_US_OSU','T3_US_TAMU','T3_US_UMD','T3_US_VC3_NotreDame','T3_US_SDSC','T3_US_Colorado','T3_US_OSG','T3_US_Princeton_ICSE','T3_US_NERSC','T3_US_Baylor','T2_US_Nebraska','T2_US_UCSD','T2_US_Wisconsin','T2_US_MIT','T3_US_TACC','T3_US_UMiss','T2_US_Caltech','T2_US_Florida','T2_US_Vanderbilt'"

mkdir -p ${writedir}
submit_log_file=${writedir}/crab_submitted_datasets_$(date '+%d_%m_%Y_%H_%M_%S').log

echo "*************************************************************************" | tee --append ${submit_log_file}
echo "Git Info" | tee --append ${submit_log_file}
git remote -v | tee --append ${submit_log_file}
git branch -a | tee --append ${submit_log_file}
git rev-parse HEAD | tee --append ${submit_log_file}
echo "*************************************************************************" | tee --append ${submit_log_file}


for dataset in `sed '/^$/d' ${input_datasets}`;
do
	jobName=$(echo ${dataset} | cut -f2,3 -d'/')
	# jobName=$(echo ${dataset////_})
	jobName=${jobName#"_"}
	jobName=$(echo ${jobName} | sed 's/[^a-zA-Z0-9]//g')

	jobDir=${writedir}/${jobName}/

	# rm -rf $jobDir

	# rm -rf crab_${jobName}/

	echo "Submitting " ${jobName}
	echo "Job directory: "${jobDir}
	echo "Write site: " ${writeSite}

	if [ -d "$jobDir" ]; then
		echo "Error! Directory "$jobDir "exists!"
		echo -e "\t\t\tSkipping!\n\n"
		# exit
		continue
	fi

	mkdir -p ${jobDir}

	crab_cfg_file=${jobDir}/crab_${jobName}.py
	cp ${crab_cfg_template} ${crab_cfg_file}

	prefiringWeightsCpy=${prefiringWeights}
	# prefiringWeightsCpy=${jobDir}/L1PrefiringMaps.root
	# cp ${prefiringWeights} ${prefiringWeightsCpy}

	sed -i 's|#psetname|'$psetname'|g' ${crab_cfg_file}
	sed -i 's|#workarea|'$jobDir'|g' ${crab_cfg_file}
	sed -i 's|#jobname|'$jobName'|g' ${crab_cfg_file}
	sed -i 's|#inputDataset|'$dataset'|g' ${crab_cfg_file}
	sed -i 's|#storageSite|'$writeSite'|g' ${crab_cfg_file}
	sed -i 's|#whitelist|'$whitelist'|g' ${crab_cfg_file}
	sed -i 's|#blacklist|'$blacklist'|g' ${crab_cfg_file}
	sed -i 's|#splitting|'$splitting'|g' ${crab_cfg_file}
	sed -i 's|#unitsperjob|'$units_perjob'|g' ${crab_cfg_file}
	sed -i 's|#mainOutputDir|'$mainOutputDir'|g' ${crab_cfg_file}
	sed -i 's|#prefiringweights|'$prefiringWeightsCpy'|g' ${crab_cfg_file}

	sed -i 's|#inputDBS|'$inputDBS'|g' ${crab_cfg_file}


	sed -i 's|#config.Data.totalUnits|'config.Data.totalUnits'|g' ${crab_cfg_file}
	sed -i 's|#totalUnits|'$maxFiles'|g' ${crab_cfg_file}

	# sed -i 's|#config.Data.lumiMask|'config.Data.lumiMask'|g' ${crab_cfg_file}
	sed -i 's|#lumiMaskFile|'${lumiMaskFile}'|g' ${crab_cfg_file}

	python ${crab_cfg_file} | tee --append ${submit_log_file}
done
