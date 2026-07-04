## Date: June 29

## Duration: 11:30 a.m. – 1:30 p.m. (2 Hours)

## Goal
Complete the implementation of Redis lite and Set up Google Test and begin writing unit test cases for the Collections Library.

## Problem Encountered 
Although I had already studied the architecture of Redis lite but I had to make sure invalid commands and missing arguments were handled correctly without crashing the program. While setting up Google Test, the project failed to compile because the installed MinGW compiler version did not support some of the C++17 features used by Google Test. Errors related to standard library headers such as string_view indicated that the compiler version was outdated.

## What I tried
The very first thing I did was to download the Google Test repositiry as a Git submodule, Added the Google Test directory to the CMake project, then attempted to build the project several times. Verified the compiler version using terminal commands.Compared the compiler version with the requirements for Google Test. Investigated the compilation errors and identified that the existing MinGW installation was outdated.

## Outcome
Upgraded the compiler, determined that the issue was not caused by the project code but by the compiler version. 
Identified that upgrading MinGW to a newer GCC version supporting C++17 was necessary before continuing with the testing phase.