#!/bin/zsh
# Source this file before building to ensure the correct ARM toolchain is used:
#   source ./setup-toolchain.sh
#
# The PROS-compatible arm-gcc-bin@10 must take priority over the Homebrew
# arm-none-eabi-gcc (v15) which is missing libstdc++ and C++ headers.
export PATH="/opt/homebrew/Cellar/arm-gcc-bin@10/10.3-2021.10_1/bin:$PATH"
echo "Using ARM toolchain: $(arm-none-eabi-gcc --version | head -1)"
