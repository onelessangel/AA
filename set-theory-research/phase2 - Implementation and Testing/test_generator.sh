#!/bin/bash

n=$1
input_type=$2
FILE="./in/out"

rm -f $FILE

generate_command() {
	arr[0]="insert "
	arr[1]="delete "
	arr[2]="modify "

	rand=$[ $RANDOM % 3]  # max RANDOM: 32767 = 2^16 / 2 - 1, which is the upper limit for a signed 16 bit integer
	cmd=${arr[$rand]}
}

pick_existing_value() {
	existing_value=$(cat $FILE  2> /dev/null | tail -10 | shuf -n 1 2> /dev/null)
	existing_value=$(echo $existing_value | cut -d " " -f $(echo $existing_value | wc -w) 2> /dev/null)
}

pick_new_value() {
	if [[ "$input_type" == "int" ]]; then
		new_value=$RANDOM
	else
		new_value=$(shuf -n 1 engmix.txt)
	fi
}

generate_test() {
	for i in $(seq 1 $n)
	do	
		generate_command

		if [[ "$cmd" == "insert " ]] ; then
			pick_new_value
			echo $cmd $new_value >> $FILE
		elif [[ "$cmd" == "delete " ]]; then
			pick_existing_value
			echo -n $cmd >> $FILE
			if [ -z "$existing_value" ]; then
				pick_new_value
				echo " $new_value" >> $FILE
			else
				echo " $existing_value" >> $FILE
			fi
		else
			pick_existing_value
			echo -n $cmd >> $FILE
			if [ -z "$existing_value" ]; then
				pick_new_value
				echo -n " $new_value" >> $FILE
				pick_new_value
				echo " $new_value" >> $FILE
			else
				echo -n " $existing_value" >> $FILE
				pick_new_value
					echo " $new_value" >> $FILE
		fi
		fi
	done
}

if [[ "$1" -eq "$1" &&  "$1"  -gt 0 ]] 2>/dev/null; then
	generate_test
	
	if [[ "$input_type" == "int" ]]; then
		echo -e "$n $input_type\n$(cat $FILE)" > $FILE
	else
		echo -e "$n string\n$(cat $FILE)" > $FILE
	fi
else
	echo "Wrong usage! Please input a valid command :)"
fi