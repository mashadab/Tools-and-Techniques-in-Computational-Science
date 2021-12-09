#Q1:adding two numbers
#!/bin/bash
#5th Commit

if [[ $# = 2 ]] ; then   #checks if number of inputs is 2
 	# For removing decimal points + zeros
	i1=$(echo "$1"| grep -oE "^[+-]?[0-9]+")
	i2=$(echo "$2"| grep -oE "^[+-]?[0-9]+")
	
	k1=$(($i1 + $i2))
   	echo "The summation of $1 and $2 is $k1."
else
	echo "Invalid number of samples."
fi
