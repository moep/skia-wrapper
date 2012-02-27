#!/usr/bin/env bash

# This script downloads and installs skia sources and all dependencies for compiling them

# Install dependencies (TODO)
# libc6-dev-i386  
# ttf-mscorefonts-installer

# Download Skia sources
if [ ! -d ./skia_src/ ];
then
  echo "Downloading Skia sources..."
  mkdir skia_src
  (cd skia_src &&  svn checkout http://skia.googlecode.com/svn/trunk .)
  echo "Finished downloading Skia sources."
fi

echo "----------------"
echo "Type 'make -j' to compile the wrapper."
