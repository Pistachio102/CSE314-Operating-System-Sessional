#!/bin/bash

if [ $# -ne 1 ]; then
	echo "please run the script as: $0 input_file_name"
	exit
fi
input=$1

rm -r ../output_dir
mkdir ../output_dir
output_dir_path="$(realpath ../output_dir)"
root="$(realpath .)"
base_root="${root##*/}"
remove_from_root="${root%/*$base_root}"
echo $base_root $remove_from_root

cmd=$(head -n 1 "$input" | tail -n 1)
nol=$(head -n 2 "$input" | tail -n 1)
word_to_search=$(head -n 3 "$input" | tail -n 1)


# first param: directory to go
traverse_directories() {
    cd "$1"

	for f in *
	do
		if [ -d "$f" ]; then
			# next level directory
			traverse_directories "$f"
		elif [ -f "$f" ]; then
			if file "$f" | grep -q text ; then
				# text file; need to process
				if $cmd -n $nol $f | grep -qi $word_to_search; then
					fn="${f%.*}"
					ext="${f##*.}"
					line_no=$($cmd -n $nol $f | grep -ni $word_to_search | cut -f1 -d':')
					new_file_name="${fn}_${line_no}.${ext}"
					cp $f "${output_dir_path}/${new_file_name}"
				fi
			else
				echo $f is a non text file
			fi
		fi
	done

	cd ../
}


traverse_directories . 