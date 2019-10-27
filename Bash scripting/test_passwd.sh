#!/bin/bash

passCount=$(echo $1 | wc -c)
digitCount=$(echo $1 | egrep -o "[0-9]" | wc -l)
alphaNumericCount=$(echo $1 | egrep -o "[,#$%&*+-=]+" | wc -l)


echo $alphaNumericCount
if [ $passCount -lt 8 ] || [ $digitCount -lt 1 ] || [ $alphaNumericCount -lt 1 ];
then
	echo weak password
else
	echo strong password
fi




