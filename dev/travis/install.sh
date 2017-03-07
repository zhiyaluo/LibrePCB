#!/usr/bin/env bash

# install dependencies
if [ "${TRAVIS_OS_NAME}" = "linux" ]
then
  docker pull ${DOCKER_IMAGE}
elif [ "${TRAVIS_OS_NAME}" = "osx" ]
then
  brew update
  brew install qt5
  brew link --force qt5
fi

