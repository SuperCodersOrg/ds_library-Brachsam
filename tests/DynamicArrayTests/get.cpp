#include <gtest/gtest.h>
#include "DynamicArray.h"
#include "exception.h"

TEST(Get, ReturnsCorrectValuesAtEachIndex) {
    DynamicArray<int> arr;
    for (int i = 0; i < 5; i++) arr.append(i * 10);
    for (int i = 0; i < 5; i++) EXPECT_EQ(arr.get(i), i * 10);
}
 
TEST(Get, FirstAndLastElement) {
    DynamicArray<int> arr;
    for (int i = 1; i <= 20; i++) arr.append(i);
    EXPECT_EQ(arr.get(0), 1);
    EXPECT_EQ(arr.get(19), 20);
}
 
TEST(Get, ConstOverloadWorks) {
    DynamicArray<int> arr;
    arr.append(7);
    const DynamicArray<int>& ref = arr;
    EXPECT_EQ(ref.get(0), 7); // forces the const get() overload
}
 
TEST(Get, ReflectsStateAfterInsertAndRemove) {
    DynamicArray<int> arr;
    for (int i = 1; i <= 5; i++) arr.append(i);
    arr.insert(0, 0);   // [0,1,2,3,4,5]
    arr.remove(3);       // removes value 2 -> [0,1,2,4,5]
    EXPECT_EQ(arr.get(0), 0);
    EXPECT_EQ(arr.get(2), 2);
    EXPECT_EQ(arr.get(3), 4);
}
 
TEST(Get, NegativeIndexThrowsException)
{
    DynamicArray<int> arr;
    arr.append(1);

    EXPECT_THROW(
        arr.get(-1),
        DynamicArrayException
    );
}
 
TEST(Get, IndexEqualToSizeThrowsException)
{
    DynamicArray<int> arr;
    arr.append(1);
    arr.append(2);

    EXPECT_THROW(
        arr.get(arr.size()),
        DynamicArrayException
    );
}
 
TEST(Get, OnEmptyArrayExitsProgram)
{
    DynamicArray<int> arr;

    EXPECT_THROW(
        arr.get(0),
        DynamicArrayException
    );
}

TEST(Get, GetFirstElement)
{
    DynamicArray<int> arr;

    arr.append(10);
    arr.append(20);
    arr.append(30);

    EXPECT_EQ(arr.get(0),10);
}

TEST(Get, GetLastElement)
{
    DynamicArray<int> arr;

    arr.append(10);
    arr.append(20);
    arr.append(30);

    EXPECT_EQ(arr.get(2),30);
}

TEST(Get, GetMiddleElement)
{
    DynamicArray<int> arr;

    for(int i=1;i<=5;i++)
        arr.append(i);

    EXPECT_EQ(arr.get(2),3);
}

TEST(Get, GetAfterInsertAndRemove)
{
    DynamicArray<int> arr;

    for(int i=1;i<=5;i++)
        arr.append(i);

    arr.insert(2,100);
    arr.remove(4);

    EXPECT_EQ(arr.get(0),1);
    EXPECT_EQ(arr.get(1),2);
    EXPECT_EQ(arr.get(2),100);
    EXPECT_EQ(arr.get(3),3);
    EXPECT_EQ(arr.get(4),5);
}

TEST(Get, GetNegativeIndex)
{
    DynamicArray<int> arr;
    arr.append(10);

    EXPECT_THROW(
        arr.get(-1),
        DynamicArrayException
    );
}
