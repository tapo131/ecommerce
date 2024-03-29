#!/bin/bash 
dir=./build
if [ -d "$dir" ]; then
	echo "rm -rf $dir"
	rm -rf "$dir"
fi

#https://kamino.hatenablog.com/entry/cmake_tutorial1
mkdir build
cd build
# cmake ..
cmake CMAKE_BUILD_TYPE=DEBUG ..
cmake --build .

echo "run the following command: ./build/main.exe probs/solomon_***/***.txt"
