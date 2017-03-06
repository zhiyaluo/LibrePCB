#!/usr/bin/env sh

# set shell settings (see https://sipb.mit.edu/doc/safe-shell/)
set -eufv

# determine build directory using relative path from the location of this script
SCRIPT_DIR=$(dirname $(readlink -f "$0"))
BUILD_DIR="${SCRIPT_DIR}/../../build"

# build librepcb
mkdir ${BUILD_DIR} && cd ${BUILD_DIR}
qmake -r -spec ${QMAKE_SPEC} ../librepcb.pro
make -j8

