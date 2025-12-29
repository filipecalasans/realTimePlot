#!/usr/bin/env bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

mkdir "$SCRIPT_DIR/out" &> /dev/null || true

CMAKE_ARGS=(
  -DCMAKE_BUILD_TYPE=Debug
)

if [ "$QT6_DIR" == "" ]
then
  echo "\$QT6_DIR env variable not provided. Using system-wide path."
else
 CMAKE_ARGS+=(-DCMAKE_PREFIX_PATH="${QT6_DIR}")
fi

(cd "$SCRIPT_DIR/out" && cmake ../ ${CMAKE_ARGS[@]}  && make)


