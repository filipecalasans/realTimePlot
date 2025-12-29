#!/usr/bin/env bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

mkdir "$SCRIPT_DIR/out" &> /dev/null || true

QT6_DIR=$(brew --prefix qt6)

(cd "$SCRIPT_DIR/out" && cmake ../ -DCMAKE_PREFIX_PATH=$QT6_DIR/ -DCMAKE_BUILD_TYPE=Debug && make)

