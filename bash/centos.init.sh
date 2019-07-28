#!/bin/bash/ 

packageFlagList=(j g m v a)
packageList=(java git maven verbose all)
additionalCommandList=(help list more)
verbose=false
currentFlags=()
additionalCommands=()
input=("$@")

function install_package {
	t=$(rpm -qa | grep "$1")
	if [ -z "$t" ]; then
		if [ "$verbose" == "true" ]; then
			echo "Install: start: \"$1\""
			yum install "$1" -y 
			echo "Install: finish: \"$1\""
		else
			echo "Install: start: \"$1\""
			yum install "$1" -y &> /dev/null
			echo "Install: finish: \"$1\""
		fi
	else
		echo -e "package is installed yet: \"$1\""
	fi	
}

function echo_help {
	echo -e "CentOS init command v1.0\n"
	echo -e "usage: centos.init [flags] [additionals] ... \n"
	echo -e "Avaliable packages list:"
	echo_list	
	echo -e "\n"
	echo -e "More commands:"
	echo_more
} 

function echo_list {
	echo -e "\t-j : Java"
	echo -e "\t-g : Git"
	echo -e "\t-m : Maven"
	echo -e "\t-s : SQL(MySQL)"
	echo -e "\t-a : All"
}

function echo_more {
	echo -e "\t--list : List of avaliable packages" 
	echo -e "\t--help : Help about centos.init"
	echo -e "\t--more : Show additional commands"
	echo -e "\t-v     : verbose -> show all logs"
}

function find_flags {
	local flagArr=()
	args=( "${input[@]}" )

	for arg in "${args[@]}"; do
		if [ "${arg:0:1}" == "-" ] && [ "${arg:1:1}" != "-" ]; then
			for (( i = 1; i < "${#arg}"; i++ )); do
				for (( j = 0; j < "${#packageFlagList[@]}"; j++)); do
					if [ "${packageFlagList[j]}" == "${arg:i:1}" ]; then	
						flagArr+=( "${packageList[$j]}" )
					fi
				done
			done	
		fi
	done
	read -r currentFlags<<<"$(printf '%s\n' "${flagArr[@]}" | sort -u)"
}	

function find_additional_commands {
	local commandArr=()
	args=( "${input[@]}" )
	for arg in "${args[@]}"; do
		if [ "${arg:0:1}" == "-" ] && [ "${arg:1:1}" == "-" ]; then
			additionalCommand=$(echo "${arg:2:${#arg}}" | tr [A-Z] [a-z])
			if [[ "${additionalCommandList[*]}" == *"$additionalCommand"* ]]; then
				commandArr+=( "$additionalCommand" )
			fi
		fi
	done

	read -r res<<<"$(printf '%s\n' "${commandArr[@]}" | sort -u)"
	additionalCommands=( "${res[@]}" )
}

function set_verbose {
	for a in "${currentFlags[@]}"; do
		if [ "$a" == "verbose" ]; then
			verbose="true"
		fi
	done
}

function check_for_all {
	for a in "${currentFlags[@]}"; do
		if [ "$a" == "all" ]; then
			delete=(all)
			currentFlags=( "${packageList[@]/${delete[@]}}" )
			delete=(verbose)
			currentFlags=( "${currentFlags[@]/${delete[@]}}" )
		fi
	done
}

function exec_additional_commands {
	commands=("${additionalCommands[@]}")

	for c in "${commands[@]}"; do
		if [ -n "$c" ]; then
			echo_"$c"		
		fi
	done
}

function exec_flags {
	flags=("${currentFlags[@]}")

	for f in "${flags[@]}"; do
		install_package "$f"
	done
}

function check_verbose {
	if [ "$verbose" == "true" ]; then
		delete=(verbose)
		currentFlags=( "${currentFlags[@]/${delete[@]}}" )
	fi
}

function set_distinct_flags { 
	currentFlags=($(printf '%s\n' "${currentFlags[@]}" | sort -u))
}

find_flags 
set_verbose 
check_verbose 
check_for_all 
set_distinct_flags
find_additional_commands
exec_additional_commands
exec_flags 
