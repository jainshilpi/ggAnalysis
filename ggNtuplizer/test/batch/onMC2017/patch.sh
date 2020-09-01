#!/bin/bash

inFile=runList.txt
writeDir=/local/cms/user/wadud/aNTGCmet/jobsMETv5/

while read iJob; do
	iJobName=$(basename ${iJob})
	iWritePath=${writeDir}/${iJobName%_*}
	iJobPath=${writeDir}/$(echo $iJobName | tr -cd [:alnum:])
	
	if( [ -d $iJobPath ] && [ -d $iWritePath ] )
	then
		/home/wadud/bin/ahadd.py -f ${iWritePath}/${iJobName}.root $iJobPath/*.root
	fi
done <$inFile
