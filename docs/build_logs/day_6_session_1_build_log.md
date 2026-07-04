## Date: June 30

## Duration: 9:30 a.m. – 11:30 p.m. (2 Hours)

## Goal
Write comprehensive Google Test test cases for the DynamicArray implementation.

## Problem Encountered 
While writing the test cases, I needed to ensure that every function was tested independently, including normal operations, edge cases, and invalid inputs. Designing test cases that covered all scenarios without redundancy required careful planning. This is one of the error I encountered while testing the cases. 

C:\Users\brach\OneDrive\Documents\Project-01\tests\DynamicArrayTests\assignment.cpp:1:5: error: expected constructor, destructor, or type conversion before '(' token
    1 | TEST(Assignment, CopiesAllValues) {
      |     ^
C:\Users\brach\OneDrive\Documents\Project-01\tests\DynamicArrayTests\assignment.cpp:11:5: error: expected constructor, destructor, or type conversion before '(' token
   11 | TEST(Assignment, SelfAssignmentDoesNotCorruptData) {
      |     ^
C:\Users\brach\OneDrive\Documents\Project-01\tests\DynamicArrayTests\assignment.cpp:19:5: error: expected constructor, destructor, or type conversion before '(' token
   19 | TEST(Assignment, IsADeepCopyNotShared) {
      |     ^
C:\Users\brach\OneDrive\Documents\Project-01\tests\DynamicArrayTests\assignment.cpp:28:5: error: expected constructor, destructor, or type conversion before '(' token
   28 | TEST(Assignment, OverwritesExistingLargerData) {
      |     ^
C:\Users\brach\OneDrive\Documents\Project-01\tests\DynamicArrayTests\assignment.cpp:40:5: error: expected constructor, destructor, or type conversion before '(' token
   40 | TEST(Assignment, ChainedAssignmentWorks) {
      |     ^
C:\Users\brach\OneDrive\Documents\Project-01\tests\DynamicArrayTests\assignment.cpp:51:5: error: expected constructor, destructor, or type conversion before '(' token
   51 | TEST(Assignment, EmptyAssignedIntoNonEmptyClearsIt) {
      |     ^
C:\Users\brach\OneDrive\Documents\Project-01\tests\DynamicArrayTests\assignment.cpp:59:5: error: expected constructor, destructor, or type conversion before '(' token
   59 | TEST(Assignment, AssignEmptyArray)
      |     ^
C:\Users\brach\OneDrive\Documents\Project-01\tests\DynamicArrayTests\assignment.cpp:70:5: error: expected constructor, destructor, or type conversion before '(' token
   70 | TEST(Assignment, AssignNonEmptyArray)
      |     ^
C:\Users\brach\OneDrive\Documents\Project-01\tests\DynamicArrayTests\assignment.cpp:86:5: error: expected constructor, destructor, or type conversion before '(' token
   86 | TEST(Assignment, ModifyOriginalAfterAssignment)
      |     ^
C:\Users\brach\OneDrive\Documents\Project-01\tests\DynamicArrayTests\assignment.cpp:105:5: error: expected constructor, destructor, or type conversion before '(' token
  105 | TEST(Assignment, ModifyAssignedArray)
      |     ^
C:\Users\brach\OneDrive\Documents\Project-01\tests\DynamicArrayTests\assignment.cpp:126:5: error: expected constructor, destructor, or type conversion before '(' token
  126 | TEST(Assignment, SelfAssignment)
      |     ^
C:\Users\brach\OneDrive\Documents\Project-01\tests\DynamicArrayTests\assignment.cpp:141:5: error: expected constructor, destructor, or type conversion before '(' token
  141 | TEST(Assignment, AssignLargeArray)
      |     ^
CMakeFiles\CollectionTests.dir\build.make:93: recipe for target 'CMakeFiles/CollectionTests.dir/tests/DynamicArrayTests/assignment.cpp.obj' failed
mingw32-make.exe[2]: *** [CMakeFiles/CollectionTests.dir/tests/DynamicArrayTests/assignment.cpp.obj] Error 1
CMakeFiles\Makefile2:295: recipe for target 'CMakeFiles/CollectionTests.dir/all' failed
mingw32-make.exe[1]: *** [CMakeFiles/CollectionTests.dir/all] Error 2
Makefile:144: recipe for target 'all' failed
mingw32-make.exe: *** [all] Error 2

## What I tried
Created Google Test cases for:
- Constructor
- append()
- insert()
- remove()
- get()
- size()
- capacity()
- clear()
- Copy Constructor
- Copy Assignment Operator


## Outcome
Successfully completed the DynamicArray test suite. Verified that all implemented functions behaved correctly under normal and edge-case scenarios.

#### Next Step:
Begin writing unit tests for the LinkedList implementation.