#!/bin/bash
set -euo pipefail

if [ -z ${1+x} ]; then
    version=3.25.2
else
    version=$1
fi

script=cmake-${version}-linux-x86_64.sh
wget https://github.com/Kitware/CMake/releases/download/v${version}/${script}
chmod +x ${script}
./${script} --skip-license --prefix=/usr/local

rm ${script}
