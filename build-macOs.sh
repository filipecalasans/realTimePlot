#!/usr/bin/env bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

mkdir "$SCRIPT_DIR/out" &> /dev/null || true

QT5_DIR=$(brew --prefix qt5)

(cd "$SCRIPT_DIR/out" && cmake ../ -DCMAKE_PREFIX_PATH=$QT5_DIR/ -DCMAKE_BUILD_TYPE=Debug && make)

