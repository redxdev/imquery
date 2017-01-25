#!/bin/bash

mkdir -p deps
cd deps

if [ ! -d cmake-3.3.2-Linux-x86_64 ]
then
    echo "Downloading cmake..."
    wget https://cmake.org/files/v3.3/cmake-3.3.2-Linux-x86_64.tar.gz
    tar xzf cmake-3.3.2-Linux-x86_64.tar.gz
else
    echo "Using cached cmake download..."
fi
echo "Installing cmake..."
cd cmake-3.3.2-Linux-x86_64
sudo rm /usr/bin/cmake
sudo ln -s "$(pwd)/bin/cmake" /usr/bin/cmake
cd ..

if [ ! -d premake-5.0.0-alpha10 ]
then
    echo "Downloading premake5..."
    mkdir premake-5.0.0-alpha10
    cd premake-5.0.0-alpha10
    wget https://github.com/premake/premake-core/releases/download/v5.0.0-alpha10/premake-5.0.0-alpha10-linux.tar.gz -O premake-5.0.0-alpha10.tar.gz
    tar xzf premake-5.0.0-alpha10.tar.gz
    cd ..
else
    echo "Using cached premake5 download..."
fi
echo "Installing premake5..."
sudo cp premake-5.0.0-alpha10/premake5 /usr/bin

if [ ! -d apache-maven-3.3.9 ]
then
    echo "Downloading maven..."
    wget http://download.nextag.com/apache/maven/maven-3/3.3.9/binaries/apache-maven-3.3.9-bin.zip -O maven-3.3.9.zip
    unzip maven-3.3.9.zip
else
    echo "Using cached maven download..."
fi
echo "Installing maven..."
sudo ln -s "$(pwd)/apache-maven-3.3.9/bin/mvn" /usr/bin/mvn

if [ ! -d googletest-release-1.8.0 ]
then
    echo "Downloading google test..."
    wget https://github.com/google/googletest/archive/release-1.8.0.zip -O googletest-1.8.zip
    unzip googletest-1.8.zip
    echo "Building google test..."
    cd googletest-release-1.8.0/googletest
    cmake .
    make
    cd ../..
else
    echo "Using cached google test build..."
fi

if [ ! -d antlr4 ]
then
    echo "Downloading antlr4..."
    git clone https://github.com/antlr/antlr4.git antlr4
    cd antlr4
    git checkout 4.6
    echo "Building antlr4 jar..."
    mvn package -DskipTests=true
    echo "Building antlr4 cpp runtime..."
    cd runtime/Cpp
    cmake .
    make antlr4_static
    cd ../../..
else
    echo "Using cached antlr4 build..."
fi

cd ..
