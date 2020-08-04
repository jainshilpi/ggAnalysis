executable				= /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsMETv5//GJetsHT200To400TuneCP513TeVmadgraphMLMpythia8//GJetsHT200To400TuneCP513TeVmadgraphMLMpythia8_011.sh
output                	= /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsMETv5//GJetsHT200To400TuneCP513TeVmadgraphMLMpythia8//log//GJetsHT200To400TuneCP513TeVmadgraphMLMpythia8_011.out
error                 	= /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsMETv5//GJetsHT200To400TuneCP513TeVmadgraphMLMpythia8//log//GJetsHT200To400TuneCP513TeVmadgraphMLMpythia8_011.err
log                   	= /local/cms/user/wadud/aNTGCmet/CMSSW_10_2_23/src/ggAnalysis/ggNtuplizer/test/batch/onMC2017/jobsMETv5//GJetsHT200To400TuneCP513TeVmadgraphMLMpythia8//log//GJetsHT200To400TuneCP513TeVmadgraphMLMpythia8_011.log
should_transfer_files   = Yes
when_to_transfer_output = ON_EXIT
request_memory			= 3000M
request_disk			= 2000M
Requirements 			= (Machine != "spa-sl7test.spa.umn.edu") && (Machine != "zebra01.spa.umn.edu") && (Machine != "zebra02.spa.umn.edu")  && (Machine != "zebra03.spa.umn.edu")  && (Machine != "zebra04.spa.umn.edu") && (Machine != "scorpion3.spa.umn.edu") && (Machine != "scorpion4.spa.umn.edu") && (Machine != "scorpion5.spa.umn.edu")
+JobFlavour 			= "workday"
queue