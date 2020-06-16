executable				= submit_job.sh
output                	= gjets.log
error                 	= gjets.log
log                   	= gjets.log
arguments               = $(inFile)
should_transfer_files   = Yes
when_to_transfer_output = ON_EXIT
Requirements 			= (Machine != "zebra01.spa.umn.edu")
request_memory			= 8000M
request_disk			= 1000M
+JobFlavour 			= longlunch
queue inFile from /local/cms/user/wadud/aNTGCmet/slc6/CMSSW_9_4_17/src/Configuration/Generator/generateGJets4ID/Prod_2020_04_15.txt
