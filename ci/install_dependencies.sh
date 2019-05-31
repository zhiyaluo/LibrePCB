#!/usr/bin/env bash

QTIFW_URL_BASE="https://download.qt.io/official_releases/qt-installer-framework/$QTIFW_VERSION"
LINUXDEPLOYQT_URL="https://github.com/probonopd/linuxdeployqt/releases/download/5/linuxdeployqt-5-x86_64.AppImage"

# Install dependencies on OS X
if [ "${TRAVIS_OS_NAME-}" = "osx" ]
then

  brew update
  brew install qt5 python@2
  brew link --force qt5

  # python packages
  pip2 install --user future flake8
  pip2 install --user -r ./tests/cli/requirements.txt
  pip2 install --user -r ./tests/funq/requirements.txt

  # Qt Installer Framework
  wget -cq "$QTIFW_URL_BASE/QtInstallerFramework-mac-x64.dmg"
  hdiutil attach ./QtInstallerFramework-mac-x64.dmg
  QTIFW_PATH="/Volumes/QtInstallerFramework-mac-x64/QtInstallerFramework-mac-x64.app/Contents/MacOS/QtInstallerFramework-mac-x64"
  chmod +x $QTIFW_PATH
  $QTIFW_PATH --script ./ci/qtifw-installer-noninteractive.qs --no-force-installations -v
  hdiutil detach "/Volumes/QtInstallerFramework-mac-x64/"

# Install dependencies on Windows (inside MSYS2)
elif [ -n "${APPVEYOR-}" ]
then

  # MSYS2 packages
  pacman -Sy --noconfirm --needed openssl libopenssl mingw-w64-x86_64-ccache
  ccache -s

  # python packages
  pip install future flake8
  pip install -r ./tests/cli/requirements.txt
  pip install -r ./tests/funq/requirements.txt

fi
