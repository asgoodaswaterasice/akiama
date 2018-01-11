#!/bin/sh

rm -rf build

if test -e build;then
    echo "build dir already exists; rm -rf build and re-run"
    exit 1
fi

mkdir build
cd build
cmake "$@" ..
