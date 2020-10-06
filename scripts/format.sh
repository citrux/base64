#!/bin/bash

# set current directory to this script parent directory
cd "${0%/*}"

clang-format -style=file -i ../src/*
clang-format -style=file -i ../examples/*
