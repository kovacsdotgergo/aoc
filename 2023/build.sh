#!/usr/bin/env bash

basedir=$(dirname $0)
filename=$(basename -- "$1")
binname="${filename%.*}"

g++ -o $basedir/build/$binname ${basedir}/$1 && build/$binname
