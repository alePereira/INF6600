#!/bin/sh

LINE=`ps | grep "TP4"`
TRIM="$(echo -e "${LINE}" | sed -e 's/^[[:space:]]*//')"
PID=`echo $TRIM | cut -d " " -f1`

while true
do
	echo "1. Reset glucose"
	echo "2. Reset Insuline"
	echo "3. Stop"
	
	read ANS
	if [ $ANS -eq 1 ]
	then
		kill -SIGUSR1 $PID
	fi
	if [ $ANS -eq 2 ]
	then
		kill -SIGUSR2 $PID
	fi
	if [ $ANS -eq 3 ]
	then
		kill -SIGINT $PID
		exit
	fi
done