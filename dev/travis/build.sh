#!/usr/bin/env bash

# set shell settings (see https://sipb.mit.edu/doc/safe-shell/)
set -eufv -o pipefail

# build librepcb
if [ "${TRAVIS_OS_NAME}" = "linux" ]
then
  docker run -it -e QMAKE_SPEC=${QMAKE_SPEC} -v ${TRAVIS_BUILD_DIR}:/librepcb -v $HOME/.ccache:/ccache ${DOCKER_IMAGE} /librepcb/dev/ci/build.sh
elif [ "${TRAVIS_OS_NAME}" = "osx" ]
then
  ./dev/ci/build.sh
fi

