#!/usr/bin/env bash

number_patterns=${1:-'42'}
exposure_time_sec_pre=${2:-'0.75'}
exposure_time_sec_pos=${2:-'0.25'}

echo "Sending mouse events for ${number_patterns} patterns"

xdotool mousemove 440 815 click 3
for (( i=1; i<=${number_patterns}; i++ ))
do
	echo "Send mouse events number ${i}"
	sleep ${exposure_time_sec_pre}
	xdotool mousemove 440 815 click 3
	sleep ${exposure_time_sec_pos}
	xdotool mousemove 440 415 click 1
done
