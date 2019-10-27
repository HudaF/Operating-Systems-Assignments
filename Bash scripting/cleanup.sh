#!/bin/bash


if [ "$#" -ne 2 ] 
then 
	echo "illegal number of parameters" 
fi

if [ -s "$1" ] &&[ -d "$2" ];
then 
	count=$(awk -F "\"*,\"*" '$2' "$1" | wc -l)
	echo count: $count
	
	while IFS=, read -r col1 col2 col3 col4
	do
	    stDir="st"
	    stDir+=$col2
	    if [ ! -d "$2/$stDir" ];
	    then 
	    	echo $stDir’s directory was not found.
	    else
		rm -rf $2/$stDir/*.o
	        deleted=$(ls -lR $2/$stDir | grep ".txt$" | wc -l)
		echo deleted files: $deleted

	for file in $(find $2/$stDir -type f -name '*.txt')
		do
		  firstline=$(head -1 $file)
		  if [ "$firstline" == "#!/bin/bash" ];
		   then
			renamed=$(ls -lR $2/$stDir | grep ".txt$" | wc -l)
			mv "$file" "${file%.*}.sh"
			echo renamed files: $renamed
		  fi
			
		done

	    fi

	done < $1	

else
	echo "arg1 doesnt exist or is not a file or a file of size 0 or arg2 doesnt exist or is not a directory" 
fi



