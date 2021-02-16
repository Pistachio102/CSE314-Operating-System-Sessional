#!/bin/bash

#2 params: #1 is the level #2 is the file name
print_in_level()
{
    for((i = 1;i < $1;i = i + 1))
    do
        echo -ne '|  '
    done
    echo '|--'$2
    
}

#2 params: #1 is the current directory #2 is the current level
directory_tree_printing()
{
    cd "$1"
    
    for f in *
    do
        if [ -d "$f" ]; then
            x=$(expr $2 + 1)
            print_in_level $2 "$f"
            directory_tree_printing "$f" $x
        elif [ -f "$f" ]; then
            print_in_level $2 "$f"
        fi
    done
    cd ../
    
}

if [ $# -eq 1 ]; then
    echo $1
    directory_tree_printing $1 1
else 
    echo .
    directory_tree_printing . 1
fi
#directory_tree_printing .. 1
