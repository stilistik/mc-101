#!/bin/bash

display_usage()
{
   # script help text
   echo
   echo "Usage: ./send_midi c v [-h]"
   echo "options:"
   echo "  c    The midi channel to send on"
   echo "  v      The midi value to send"
   echo "  h          Print this Help."
   echo
}

# if less than two arguments supplied, display usage 
	if [  $# -le 1 ] 
	then 
		display_usage
		exit 1
	fi 
 
# check whether user had supplied -h or --help . If yes display usage 
	if [[ ( $# == "--help") ||  $# == "-h" ]] 
	then 
		display_usage
		exit 0
	fi 

channel=$(echo "obase=16; $1" | bc)
value=$(echo "obase=16; $2" | bc)

amidi -p hw:1,0,0 -S "B0 $channel $value"