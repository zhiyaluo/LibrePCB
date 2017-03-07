#!/usr/bin/env bash

# set shell settings (see https://sipb.mit.edu/doc/safe-shell/)
set -eufv -o pipefail

# run tests
if [ "${TRAVIS_OS_NAME}" = "linux" ]
then
  docker run -it -v ${TRAVIS_BUILD_DIR}:/librepcb ${DOCKER_IMAGE} /librepcb/dev/ci/test.sh
elif [ "${TRAVIS_OS_NAME}" = "osx" ]
then
  ./build/generated/mac/qztest
  ./build/generated/mac/tests
fi

