#!/bin/bash
set -euxo pipefail

version=3.25.2

script=cmake-${version}-linux-x86_64.sh
wget https://github.com/Kitware/CMake/releases/download/v${version}/${script}
chmod +x ${script}
./${script} --skip-license --prefix=/usr/local

rm ${script}
