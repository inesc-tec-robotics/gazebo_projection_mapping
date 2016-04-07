#!/usr/bin/env bash

process_name=${1:-'scan3d-capture'}
window_name=${2:-'scan3d-capture'}

until ps -e | grep ${process_name} ; do sleep 1; done
until wmctrl -r ${window_name} -b toggle,fullscreen ; do sleep 1; done

