## Date: June 29

## Duration: 2:30 p.m. – 5:30 p.m. (3 Hours)

## Goal
Upgrade the development environment, configure Google Test successfully, and prepare the project for writing unit tests.

## Problem Encountered 
After upgrading MinGW, several project settings still referenced the older compiler installation. CMake continued detecting the previous compiler, preventing the project from compiling with the updated toolchain. The build configuration had to be regenerated using the correct compiler.

## What I tried
Installed the latest MSYS2 UCRT64 MinGW compiler. Updated the system PATH environment variable. Verified the new compiler version using g++ --version. Deleted the previous build directory. Regenerated the CMake configuration Rebuilt the project. Configured Google Test successfully Created the initial test project structure for all the three data typrs: DynamicArray Test, LinkedList Test, HashMap Tests

Verified that the project compiled successfully with the updated compiler.

## Outcome
Successfully completed the development environment setup. Google Test was integrated successfully into the project, and the Collections Library was ready for writing comprehensive unit tests. Prepared the testing framework that would be used to validate DynamicArray, LinkedList, and HashMap implementations in the following sessions.

Next Step:
Begin implementing detailed unit test cases for each data structure.