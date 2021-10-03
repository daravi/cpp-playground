#!/bin/bash
set -e

arg1=${1:-i}

project_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cwd=$(pwd)

cd ${project_dir}

if [[ $arg1 == 'c' ]]; then
	rm -rf ./build
	mkdir build
	conan install -s build_type=Debug -s cmake:build_type=Release -s ninja:build_type=Release --build missing -r mmicoreconan -if ./build .
	cmake -B./build -S. -DCMAKE_BUILD_TYPE=Debug -G Ninja
fi

source build/activate.sh
	cmake --build ./build --target all -j"$(nproc)"
source build/deactivate.sh

if [[ $arg1 == 'c' ]]; then
	source build/conanrunenv.sh
fi

cd ${cwd}
