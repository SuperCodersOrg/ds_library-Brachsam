#include <gtest/gtest.h>
#include "DynamicArray.h"
#include "exception.h"

TEST(Assignment, CopiesAllValues) {
    DynamicArray<int> a;
    for (int i = 0; i < 5; i++) a.append(i);
    DynamicArray<int> b;
    b.append(999); // b starts with unrelated data
    b = a;
    EXPECT_EQ(b.size(), 5);
    for (int i = 0; i < 5; i++) EXPECT_EQ(b.get(i), i);
}
 
TEST(Assignment, SelfAssignmentDoesNotCorruptData) {
    DynamicArray<int> a;
    for (int i = 0; i < 5; i++) a.append(i);
    a = a; // must be guarded by the this==&other check
    EXPECT_EQ(a.size(), 5);
    for (int i = 0; i < 5; i++) EXPECT_EQ(a.get(i), i);
}
 
TEST(Assignment, IsADeepCopyNotShared) {
    DynamicArray<int> a, b;
    a.append(1);
    a.append(2);
    b = a;
    b.append(3);          // mutate b only
    EXPECT_EQ(a.size(), 2); // a must stay unaffected
}
 
TEST(Assignment, OverwritesExistingLargerData) {
    DynamicArray<int> a; // small, 2 elements
    a.append(1);
    a.append(2);
    DynamicArray<int> b; // bigger, 50 elements
    for (int i = 0; i < 50; i++) b.append(i);
    b = a; // b should shrink down to match a exactly
    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b.get(0), 1);
    EXPECT_EQ(b.get(1), 2);
}
 
TEST(Assignment, ChainedAssignmentWorks) {
    DynamicArray<int> a, b, c;
    a.append(7);
    a.append(8);
    b = c = a; // chained: c=a first, then b=c
    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(c.size(), 2);
    EXPECT_EQ(b.get(1), 8);
    EXPECT_EQ(c.get(1), 8);
}
 
TEST(Assignment, EmptyAssignedIntoNonEmptyClearsIt) {
    DynamicArray<int> a; // empty
    DynamicArray<int> b;
    for (int i = 0; i < 5; i++) b.append(i);
    b = a;
    EXPECT_EQ(b.size(), 0);
}

TEST(Assignment, AssignEmptyArray)
{
    DynamicArray<int> arr1;
    DynamicArray<int> arr2;

    arr2 = arr1;

    EXPECT_EQ(arr2.size(), 0);
    EXPECT_EQ(arr2.capacity(), arr1.capacity());
}

TEST(Assignment, AssignNonEmptyArray)
{
    DynamicArray<int> arr1;

    for(int i = 1; i <= 5; i++)
        arr1.append(i);

    DynamicArray<int> arr2;
    arr2 = arr1;

    EXPECT_EQ(arr2.size(), arr1.size());

    for(int i = 0; i < arr1.size(); i++)
        EXPECT_EQ(arr2.get(i), arr1.get(i));
}

TEST(Assignment, ModifyOriginalAfterAssignment)
{
    DynamicArray<int> arr1;

    arr1.append(10);
    arr1.append(20);
    arr1.append(30);

    DynamicArray<int> arr2;
    arr2 = arr1;

    arr1.remove(1);

    EXPECT_EQ(arr2.size(), 3);
    EXPECT_EQ(arr2.get(0), 10);
    EXPECT_EQ(arr2.get(1), 20);
    EXPECT_EQ(arr2.get(2), 30);
}

TEST(Assignment, ModifyAssignedArray)
{
    DynamicArray<int> arr1;

    arr1.append(1);
    arr1.append(2);
    arr1.append(3);

    DynamicArray<int> arr2;
    arr2 = arr1;

    arr2.remove(0);

    EXPECT_EQ(arr1.size(), 3);
    EXPECT_EQ(arr1.get(0), 1);
    EXPECT_EQ(arr1.get(1), 2);
    EXPECT_EQ(arr1.get(2), 3);

    EXPECT_EQ(arr2.size(), 2);
}

TEST(Assignment, SelfAssignment)
{
    DynamicArray<int> arr;

    for(int i = 1; i <= 5; i++)
        arr.append(i);

    arr = arr;

    EXPECT_EQ(arr.size(), 5);

    for(int i = 0; i < 5; i++)
        EXPECT_EQ(arr.get(i), i + 1);
}

TEST(Assignment, AssignLargeArray)
{
    DynamicArray<int> arr1;

    for(int i = 0; i < 1000; i++)
        arr1.append(i);

    DynamicArray<int> arr2;
    arr2 = arr1;

    EXPECT_EQ(arr2.size(), 1000);

    for(int i = 0; i < 1000; i++)
        EXPECT_EQ(arr2.get(i), i);
}