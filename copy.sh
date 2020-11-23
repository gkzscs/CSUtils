#!/bin/bash

#Just modify these 2 variables to change the source directory and destination directory
src=`pwd`/src
dst=`pwd`/include

traverse_dir()
{
	local filepath=$1

	for file in `ls $filepath`
	do
		if [ -d $filepath/$file ] 
		then
			if [[ $file != '.' && $file != '..' && $filepath/$file != $dst ]] 
			then
				traverse_dir $filepath/$file
			fi
		else 
			check_suffix $filepath/$file
		fi
	done
}

check_suffix()
{
	local file=$1

	if [ "${file##*.}"x = "h"x ] || [ "${file##*.}"x == "hpp"x ]; then
		# Dest directory, keep the relative path, use regex expression to replace string
		local tmpDst=${file/$src/$dst}
		# Create the path when it doesn't exists
		create_dir $tmpDst
		# Copy file to dest directory
		cp $file $tmpDst
	fi
}

create_dir()
{
	local dir=$1

	if [ -d $dir ]
	then
		echo 'mkdir -d:', $dir
		mkdir -p $dir
	else
		# If `dir` is not a directory, then create its parent directory
		local tmpDir=`dirname $dir`
		#echo 'mkdir', $tmpDir
		mkdir -p $tmpDir
	fi
}


# Source directory
traverse_dir $src

