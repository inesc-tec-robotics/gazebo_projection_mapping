#!/usr/bin/env bash

process_name=${1:-'image_view'}
window_name=${2:-'/virtual_camera/image_rect'}

until ps -e | grep ${process_name} ; do sleep 1; done
until wmctrl -r ${window_name} -b toggle,fullscreen ; do sleep 1; done

