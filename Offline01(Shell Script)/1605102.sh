#!/bin/bash
#Taking input filename and directory as command line arguments
if [[ $# -eq 2 ]]; then
	Input=$1
	Directory=$2
	#echo "$Input"
	#cd "$Directory"
elif [[ $# -eq 0 ]]; then
	echo "No input file."
	exit
else Input=$1
	Directory='.'
	#echo "$Input"
	#cd "$Directory"
fi

if test -f "$Input"; then
	echo ""
    else
    	echo "$Input file doesn't exist in this directory."
    	exit
fi


#Reading input file parameters


i=0

while read line 
do
	array[i]=$line
	#echo "${array[$i]}"
	i=`expr $i + 1`
done <$Input



cd "$Directory"

Directory1="$(dirname "$Directory")/Output"
mkdir -p "$Directory1"

#Creates .csv file

>"$Directory1"/1605102.csv




#Stores all the matched readable files in the OutFiles array


j=0

func(){
for entry in *
do

if [[ -d "$entry" ]];then
	#echo "---> $entry"
	cd "$entry"
	func
	cd ..
elif [[ -r "$entry" ]];then


       if [[ ${array[0]} == "begin" ]]; then
	       if  head -${array[1]} $entry | grep -q ${array[2]} 
	       then

#Renaming the filepath

            currentdirectory=`pwd`
	       	value=`readlink -f $entry`
	       	base=$(basename -- "$value")
	       	filename="${base%.*}"
	       	extension="${base##*.}"
	       	if [[ $extension == $filename ]]; then
	       		extension=""

	       		else
	       			extension=".$extension"
	       	fi
	       	

	       	lineno=$(grep -n -m 1 ${array[2]} "$entry"|sed 's/\([0-9]*\).*/\1/')
	       	#echo "$lineno"

	       	rename="$currentdirectory/$filename$lineno$extension"

	       	#replcing / with .
	       	rename1="$(sed s/[/]/./g <<<$rename)"
	       	rename1="$(sed s/.// <<<$rename1)"

	       	# echo "$rename1"

	       	# rename1="$(sed s <<<$rename1)"

#Writing into .csv file

			lines=`head -${array[1]} $entry | grep -n ${array[2]} | sed 's/:/	/'`
			
			IFS=$'\n'

			for line in $lines
			do
				printf "${rename1}\t${line}\n" >> "$Directory1"/1605102.csv
			done

	       	
	       	
	       	cp $entry $Directory1

	       	current=`pwd`

	       	cd $Directory1

	       	# echo "$entry -------------------> $rename1"
	       	mv $entry $rename1

	       	cd $current

	       	outputFiles[j]=$entry
	       	j=`expr $j + 1`
		
	       fi
       

       elif [[ ${array[0]} == "end" ]]; then
	       if  tail -${array[1]} $entry | grep -q ${array[2]} 
	       then
	       	currentdirectory=`pwd`
	       	value=`readlink -f $entry`
	       	base=$(basename -- "$value")
	       	filename="${base%.*}"
	       	extension="${base##*.}"
	       	if [[ $extension == $filename ]]; then
	       		extension=""

	       		else
	       			extension=".$extension"
	       	fi
	       	

	       	lineno=$(cat -n "$entry"|grep ${array[2]} |tail -1| cut -f 1)
	       	lineno="$(echo "$lineno" | sed -e 's/[ \t][ \t]*//g' )"
	       	#echo "$lineno"

	       	rename="$currentdirectory/$filename$lineno$extension"

	       	# echo "$lineno"

	       	#replcing / with .
	       	rename1="$(sed s/[/]/./g <<<$rename)"
	       	rename1="$(sed s/.// <<<$rename1)"

	       	
	       	# rename1="$(sed s <<<$rename1)"

#Writing into .csv file

			lines=`tail -${array[1]} $entry | grep -n ${array[2]} | sed 's/:/	/'`
			
			IFS=$'\n'

			for line in $lines
			do
				printf "${rename1}\t${line}\n" >> "$Directory1"/1605102.csv
			done

	       	
	       	
	       	cp $entry $Directory1

	       	current=`pwd`

	       	cd $Directory1

	       	# echo "$entry -------------------> $rename1"
	       	mv $entry $rename1

	       	cd $current

	       	outputFiles[j]=$entry
	       	j=`expr $j + 1`
	       fi
       fi



fi

done
}

func

echo "$j files matched the criteria."