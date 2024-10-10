#!/usr/bin/env bash

set -e

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

if [ $1 == "" ] 
then
  echo "No input file specified."
  exit 1
fi

ffmpeg -i "$1" -s 600x400 -pix_fmt rgb24 -r 20 -f gif "$SCRIPT_DIR/../example.gif"

