#!/bin/bash
set -euxo pipefail

MAJOR=16

echo "deb http://apt.llvm.org/jammy/ llvm-toolchain-jammy-${MAJOR} main" >> /etc/apt/sources.list
echo "deb-src http://apt.llvm.org/jammy/ llvm-toolchain-jammy-${MAJOR} main" >> /etc/apt/sources.list
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -

apt-get update && apt-get install -y --no-install-recommends \
    clang-${MAJOR} \
    clang-format-${MAJOR} \
    clang-tidy-${MAJOR} \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

update-alternatives --install /usr/bin/clang clang /usr/bin/clang-${MAJOR} 1
update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-${MAJOR} 1
