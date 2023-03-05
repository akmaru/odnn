#!/bin/bash
set -euo pipefail

apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python3-pip \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

python3 -m pip install cmakelang
