#!/bin/bash

searchDir=$1

FILES=($(find ${searchDir} -name "*.err" 2>/dev/null)) 

# echo -e "Completed Tasks: "
echo -e "Resubmitting Failed Tasks: "
FILES=($(find ${searchDir} -name "*.log" 2>/dev/null)) 

for file in "${FILES[@]}"; do
	file=$(readlink -e $file)
	
	normTermLine=$(tac $file | grep -m 1 "Normal termination" "$file")
	killLine=$(tac $file | grep -m 1 "Job was aborted by the user" "$file")

	# updateLine=$(tac $file | grep -n -m 1 "Image size of job updated" "$file")

	# if ( [ "$killLine" -gt "$updateLine" ] || [ "$normTermLine" -gt "$updateLine" ] ); then
	# 	echo $normTermLine $killLine $updateLine 
	# fi

	if grep -q "Normal termination (return value 0)" "$file"; then
		continue;
	fi

	if ( [ -z "$normTermLine" ] && [ -z "$killLine" ] ); then
		continue
	fi



	if ( [ ! -z "$normTermLine" ] && [ ! -z "$killLine" ] ); then
		
		normTermLineN=$(tac $file | grep -n -m 1 "Normal termination" "$file" | cut -d : -f 1)
		killLineN=$(tac $file | grep -n -m 1 "Job was aborted by the user" "$file" | cut -d : -f 1)
		updateN=$(tac $file | grep -n -m 1 "Image size of job updated" "$file" | cut -d : -f 1)

		if ( [ "$updateN" -gt "$killLineN" ]  && [ "$updateN" -gt "$normTermLineN" ] );then
			echo "1 Job is running" $updateN $normTermLineN $killLineN
			continue
		fi

		# cat $file
		pathName=$(dirname $file)
		pathName=${pathName%log}
		fileName=$(basename $file)
		condorFile=${pathName}/condor_${fileName}
		condorFile=${condorFile%.*}.sh

		
		echo 1 $condorFile $updateN $normTermLineN $killLineN
		# echo $condorFile
		# condor_submit $condorFile
		# echo -e "******************************************************************************************************************"
		echo -e "******************************************************************************************************************\n\n\n"
	elif ( [ ! -z "$normTermLine" ] ); then
		
		normTermLineN=$(tac $file | grep -n -m 1 "Normal termination" "$file" | cut -d : -f 1)
		updateN=$(tac $file | grep -n -m 1 "Image size of job updated" "$file" | cut -d : -f 1)

		if ( [ "$updateN" -gt "$normTermLineN" ] );then
			echo "2 Job is running" $updateN $normTermLineN
			continue
		fi

		# cat $file
		pathName=$(dirname $file)
		pathName=${pathName%log}
		fileName=$(basename $file)
		condorFile=${pathName}/condor_${fileName}
		condorFile=${condorFile%.*}.sh

		echo 2 $condorFile $updateN $normTermLineN

		# echo $condorFile
		# condor_submit $condorFile
		# echo -e "******************************************************************************************************************"
		echo -e "******************************************************************************************************************\n\n\n"
	elif ( [ ! -z "$killLine" ] ); then
		
		killLineN=$(tac $file | grep -n -m 1 "Job was aborted by the user" "$file" | cut -d : -f 1)
		updateN=$(tac $file | grep -n -m 1 "Image size of job updated" "$file" | cut -d : -f 1)

		if ( [ "$updateN" -gt "$killLineN" ] );then

			echo "3 Job is running" $updateN $killLineN
			continue
		fi

		# cat $file
		pathName=$(dirname $file)
		pathName=${pathName%log}
		fileName=$(basename $file)
		condorFile=${pathName}/condor_${fileName}
		condorFile=${condorFile%.*}.sh

		echo 3 $condorFile $updateN $killLineN

		# echo $condorFile
		# condor_submit $condorFile
		# echo -e "******************************************************************************************************************"
		echo -e "******************************************************************************************************************\n\n\n"
	fi


done
