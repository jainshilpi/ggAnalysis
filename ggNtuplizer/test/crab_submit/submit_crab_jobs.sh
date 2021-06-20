#!/bin/bash

scriptDir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"/
testDir=$(readlink -f ${scriptDir}"/../")
writeSite="T2_US_Wisconsin"

# jobsetName=jobsUL2017v1
# mainOutputDir="/store/user/rusack/aNTGCmet/ntuples/UL2017/"${jobsetName}

# input_datasets=${scriptDir}/"mc_UL_2017.txt"
# psetname=${testDir}"/run_mc2017_106X.py"
# input_datasets=${scriptDir}/"mc_UL_2017.txt"

jobsetName=jobsUL2017v2
mainOutputDir="/store/user/mwadud/aNTGCmet/ntuples/UL2017/"${jobsetName}
psetname=${testDir}"/run_data2017_106X.py"
input_datasets=${scriptDir}/"data_UL_2017.txt"

# jobsetName=jobsUL2017v2Xsecs
# mainOutputDir="/store/user/mwadud/aNTGCmet/ntuples/"${jobsetName}
# psetname=${testDir}"/ana.py"
# units_perjob=10000
# splitting='FileBased'


# jobsetName=jobsUL2016PreVFPv1
# mainOutputDir="/store/user/mwadud/aNTGCmet/ntuples/UL2016PreVFP/"${jobsetName}
# psetname=${testDir}"/run_data2016PreVFP_106X.py"
# input_datasets=${scriptDir}/"data_UL_2016PreVFP.txt"

# jobsetName=jobsUL2016PostVFPv1
# mainOutputDir="/store/user/mwadud/aNTGCmet/ntuples/UL2016PostVFP/"${jobsetName}
# psetname=${testDir}"/run_data2016PostVFP_106X.py"
# input_datasets=${scriptDir}/"data_UL_2016PostVFP.txt"


# jobsetName=jobsUL2018AtoC
# mainOutputDir="/store/user/mwadud/aNTGCmet/ntuples/UL2018AtoC/"${jobsetName}
# psetname=${testDir}"/run_data2018AtoC_106X.py"
# input_datasets=${scriptDir}/"data_UL_2018AtoC.txt"


# jobsetName=jobsUL2018D
# mainOutputDir="/store/user/mwadud/aNTGCmet/ntuples/UL2018D/"${jobsetName}
# psetname=${testDir}"/run_data2018D_106X.py"
# input_datasets=${scriptDir}/"data_UL_2018D.txt"


units_perjob=4
splitting='FileBased'
# units_perjob=4
# splitting='LumiBased'

writedir=${scriptDir}/jobs//${jobsetName}/
writeSite="T2_US_Wisconsin"


lumiMaskFile=${scriptDir}/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt
# lumiMaskFile=${scriptDir}/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt
# lumiMaskFile=${scriptDir}/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt
inputDBS=global
# inputDBS=phys03


################################################################################################################
source /cvmfs/cms.cern.ch/cmsset_default.sh;
source /cvmfs/cms.cern.ch/crab3/crab.sh;
eval `scramv1 runtime -sh`;
voms-proxy-init --voms cms


crab_cfg_template=crab_submit.py
units_perjob=5
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
	jobName=${jobName#"_"}
	jobName=$(echo ${jobName} | sed 's/[^a-zA-Z0-9]//g')
	jobName=${jobName%mc201*}

	jobDir=${writedir}/${jobName}/

	echo "Submitting " ${jobName}
	echo "Job directory: "${jobDir}
	echo "Write site: " ${writeSite}

	if [ -d "$jobDir" ]; then
		echo "Error! Directory "$jobDir "exists!"
		echo -e "\t\t\tSkipping!\n\n"
		continue
	fi

	mkdir -p ${jobDir}

	cp ${psetname} ${jobDir}

	crab_cfg_file=${jobDir}/crab_${jobName}.py
	cp ${crab_cfg_template} ${crab_cfg_file}

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

	sed -i 's|#inputDBS|'$inputDBS'|g' ${crab_cfg_file}

	if [[ $psetname == *"data"* ]]; then
		echo -e "Applying lumi mask "${lumiMaskFile}
		sed -i 's|#config.Data.lumiMask|'config.Data.lumiMask'|g' ${crab_cfg_file}
		sed -i 's|#lumiMaskFile|'${lumiMaskFile}'|g' ${crab_cfg_file}
	fi

	python ${crab_cfg_file} | tee --append ${submit_log_file}

	echo -e "\n\n\n\n"
done
