#!/bin/bash
set -euo pipefail

if [ -z ${1+x} ]; then
    major=16
else
    major=$1
fi

apt-get update && apt-get install -y --no-install-recommends \
    gnupg \
    lsb-release \
    && apt-get clean && rm -rf /var/lib/apt/lists/*


# Setup for installing the latest llvm tools
# cf. https://apt.llvm.org/
codename=$(lsb_release -cs)
echo deb http://apt.llvm.org/${codename}/ llvm-toolchain-${codename}-${major} main >> /etc/apt/sources.list.d/llvm.list
echo deb-src http://apt.llvm.org/${codename}/ llvm-toolchain-${codename}-${major} main >> /etc/apt/sources.list.d/llvm.list
wget -q -O - http://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -

apt-get update && apt-get install -y --no-install-recommends \
    llvm-${major} \
    clang-${major} \
    clang-format-${major} \
    clangd-${major} \
    clang-tidy-${major} \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

update-alternatives --install /usr/bin/clang clang /usr/bin/clang-${major} 1
update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-${major} 1
update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-${major} 1
update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-${major} 1
update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-${major} 1
