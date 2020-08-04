#!/bin/bash

FILES=($(find . -name "*.err" 2>/dev/null)) 

echo -e "Resubmitting Failed Tasks: "
for file in "${FILES[@]}"; do
	file=$(readlink -e $file)
	if grep -q "A fatal system signal has occurred:" "$file"; then
		fileName=$(basename $file)
		pathName=$(dirname $file)
		pathName=${pathName%log}
		condorFile=${pathName}/condor_${fileName}
		condorFile=${condorFile%.*}.sh
		if [ -f /$condorFile ]; then
			echo -e "\t\t" $fileName
			condor_submit $condorFile
		fi
	fi
done


echo -e "Completed Tasks: "
FILES=($(find . -name "*.log" 2>/dev/null)) 

for file in "${FILES[@]}"; do
	file=$(readlink -e $file)
	if grep -q "Normal termination (return value 0)" "$file"; then
		echo -e "\t\t" $(basename $file)
	fi
done
