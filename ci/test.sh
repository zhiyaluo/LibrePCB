#!/usr/bin/env bash

# set shell settings (see https://sipb.mit.edu/doc/safe-shell/)
set -eufv -o pipefail

# run unit tests
if [ "${TRAVIS_OS_NAME-}" = "linux" ]
then
  xvfb-run -a ./build/output/qztest
  xvfb-run -a ./build/output/librepcb-unittests
elif [ "${TRAVIS_OS_NAME-}" = "osx" ]
then
  ./build/output/qztest
  ./build/output/librepcb-unittests
else
  ./build/output/qztest.exe
  ./build/output/librepcb-unittests.exe
fi

# run CLI system tests
if [ "${TRAVIS_OS_NAME-}" = "linux" ]
then
  xvfb-run -a --server-args="-screen 0 1024x768x24" pytest -v --librepcb-executable="build/install/opt/bin/librepcb-cli" ./tests/cli
elif [ "${TRAVIS_OS_NAME-}" = "osx" ]
then
  pytest -v --librepcb-executable="build/install/opt/librepcb-cli.app/Contents/MacOS/librepcb-cli" ./tests/cli
else
  pytest -v --librepcb-executable="build/install/opt/bin/librepcb-cli.exe" ./tests/cli
fi

# run functional tests
if [ "${TRAVIS_OS_NAME-}" = "linux" ]
then
  xvfb-run -a --server-args="-screen 0 1024x768x24" pytest -v --librepcb-executable="build/install/opt/bin/librepcb" ./tests/funq
elif [ "${TRAVIS_OS_NAME-}" = "osx" ]
then
  pytest -v --librepcb-executable="build/install/opt/librepcb.app/Contents/MacOS/librepcb" ./tests/funq
else
  pytest -v --librepcb-executable="build/install/opt/bin/librepcb.exe" ./tests/funq
fi
