#!/usr/bin/env bash

process_name=${1:-'image_view'}
window_name=${2:-'/virtual_camera/image_raw'}

until ps -e | grep ${process_name} ; do sleep 1; done
sleep 1
until wmctrl -r ${window_name} -b toggle,fullscreen,above ; do sleep 1; done
