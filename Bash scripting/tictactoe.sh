#! /bin/bash

Array=('.' '.' '.' '.' '.' '.' '.' '.' '.') #9 positions
player=$(($(od -An -N1 -i /dev/urandom) % 2))
game=0 #true
right=1 #true
mark=0 #false
win=0 #false
visited=()

markturn() #1:oneD,2:player
{
	check=$(($player%2))
	if [ ${Array[$1]} == "." ]; then 
		if [ "$check"=="0" ]; then
			Array[$1]="X"
		else
			echo"came here"
			Array[$1]="O"
		mark=1
		visited+=($1) #append to array
		fi
	else
		echo "This position is already occupied. It is your turn again. Enter valid values"
		mark=0
	fi
}

showboard()
{
	echo "       |     |     "
	echo "   ${Array[0]}   |  ${Array[1]}  |   ${Array[2]}   "
	echo "       |     |     "
	echo "---------------------"

	echo "       |     |     "
	echo "   ${Array[3]}   |  ${Array[4]}  |   ${Array[5]}   "
	echo "       |     |     "
	echo "---------------------"

	echo "       |     |     "
	echo "   ${Array[6]}   |  ${Array[7]}  |   ${Array[8]}   "
	echo "       |     |     "
}

wincond()
{
	win=false
	if [ "${Arr[0]}" != "." ] && [ ${Arr[0]} == ${Arr[1]} ] && [ ${Arr[1]} == ${Arr[2]} ]; then
		win=1
	elif [ ${Arr[3]} != "." ] && [ ${Arr[3]} == ${Arr[4]} ] && [ ${Arr[4]} == ${Arr[4]} ]; then
		win=1
	elif [ ${Arr[6]} != "." ] && [ ${Arr[6]} == ${Arr[7]} ] && [ ${Arr[7]} == ${Arr[8]} ]; then
		win=1

	elif [ ${Arr[0]} != "." ] && [ ${Arr[0]} == ${Arr[3]} ] && [ ${Arr[3]} == ${Arr[6]} ]; then
		win=1
	elif [ ${Arr[1]} != "." ] && [ ${Arr[1]} == ${Arr[4]} ] && [ ${Arr[4]} == ${Arr[7]} ]; then
		win=1
	elif [ ${Arr[2]} != "." ] && [ ${Arr[2]} == ${Arr[5]} ] && [ ${Arr[5]} == ${Arr[8]} ]; then
		win=1

	elif [ ${Arr[0]} != "." ] && [ ${Arr[0]} == ${Arr[4]} ] && [ ${Arr[4]} == ${Arr[8]} ]; then
		win=1
	elif [ ${Arr[2]} != "." ] && [ ${Arr[2]} == ${Arr[4]} ] && [ ${Arr[4]} == ${Arr[6]} ]; then
		win=1
	fi
}

drawcounter=0
while [ "$game" == "0" ]; do
	mark=0
	echo ""
	echo "Welcome to tic tac toe. You symbol is X and the opponent's sumbol is O"
	showboard
	check=$(($player%2))
	if [ "$check"=="0" ]; then
		valid="0" #false
		while [ "$valid" == "0" ]; do
			echo "It is your turn. Please enter an inbound row value"
			read -r x
			echo "Please enter an inbound y value"
			read -r y
			if [ $x -ge 3 ] || [ $x -lt 0 ] || [ $y -gt 3 ] || [ $y -lt 0 ]; then
				echo "The value you added was out of bounds. Please enter an inbound row value"
			else
				valid="1"
			fi
		done

		oneD=$(((3*y) + x))

		echo $oneD
		for value in {0..8}
		do
			i=${Array[value]}
			if [ "$i" == "." ] && [ "$value" == "$oneD" ]
			then
				Array[$oneD]="X" 
			fi
		done
		showboard
	fi

	player=$((player + 1))
	nextcheck=$(($player%2))

	drawcounter=$((drawcounter + 1))

	if [ "$drawcounter" == "9" ]; then
		echo "It was a draw"
		game=1
	fi


	if [ "$nextcheck"!="0" ]; then
		echo "It is the computer's turn. The symbol is O"
		unique=0
		while [ "$unique" == "0" ]; do
			oneD=$[RANDOM%8]
			unique=$(unique + 1)
			if [[ ${Array[oneD]} == "." ]]; then
				break
			fi

			if [ $unique -gt 10 ]
			then
				game=1
				break
			fi
		done
		
		
		for value in {0..8}
		do
			i=${Array[value]}
			if [ "$i" == "." ] && [ "$value" == "$oneD" ]
			then
				Array[$oneD]="O" 
			fi
		done
		echo" "
		showboard
		#wincond

	fi

	player=$((player + 1))
	drawcounter=$((drawcounter + 1))


	if [ "$drawcounter" == "9" ]; then
		echo "It was a draw"
		game=1
	fi
	showboard
done