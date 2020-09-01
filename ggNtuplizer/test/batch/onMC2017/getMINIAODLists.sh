#!/bin/bash

searchPath=$1
writeDir=$2

function listNtuples(){
	SearchPath=$1
	WriteDir=$2
	# outfile=${SearchPath/'crab_'/''}
	# outfile=${WriteDir}/${outfile##*/}.txt
	
	# rm -f ${outfile}

	# if test -f $outfile; then
	# 	echo "$outfile exist!"
	# 	continue;
	# fi

	# find ${SearchPath} -name "*.root" -not -path '*/failed/*' -type f | tee ${outfile}
	outfile=$(basename ${SearchPath})
	outfile=${outfile##*/} 
	outfile=${writeDir}/$(echo ${outfile} | sed 's/[^a-zA-Z0-9]//g').txt
	echo $outfile
	find ${SearchPath} -name "*.root" -type f | tee ${outfile}
}

# mkdir -p $writeDir

for directory in $(find "${searchPath}" -maxdepth 1 -mindepth 1 -type d -not -path '*/\.*' -and -not -path '*failed*');
# for directory in $(find "${searchPath}" -maxdepth 2 -mindepth 1 -type d -path "*_300_1200/*");
do
	echo -e "\t\t" $directory
	listNtuples ${directory} $writeDir
done
