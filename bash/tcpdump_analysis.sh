#!/bin/bash

iplist=$(grep -E -o "([0-9]{1,3}[\.]){3}[0-9]{1,3}" tcpdump.log | sort | uniq)
regex="Flags\[.{0,}S.{0,}\]"

for line in $iplist
do 
	#linesWithIp=$(grep $line tcpdump.log)
	#flagCount=0

	#for someLine in $linesWithIp
	#do
	#	if [[ $someLine=~$regex ]] ; then
	#		let "flagCount = flagCount + 1"
	#	fi
	#done

	flagCount=$(grep $line tcpdump.log | grep -E -c "Flags \[.{0,}S")
	#flagCount=$(grep $line tcpdump.log | grep -E "Flags \[.{0,}S" | cat -n | tail -n 1)


	echo "Ip: " $line " Count with S-flag: " $flagCount
done
