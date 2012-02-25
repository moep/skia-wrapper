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

# Compile Skia sources
echo "Compiling Skia..."
(cd skia_src && ./gyp_skia && make -j)
echo "Finished compiling."

echo "----------------"
echo "You can now run GNU make to compile the JNI wrapper."
