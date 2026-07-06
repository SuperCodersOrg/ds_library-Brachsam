#include <gtest/gtest.h>
#include "DynamicArray.h"
#include "exception.h"

TEST(Remove, FromBeginning) {
    DynamicArray<int> arr;
    for (int i = 1; i <= 5; i++) arr.append(i);
    arr.remove(0);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr.get(0), 2);
}
 
TEST(Remove, FromMiddle) {
    DynamicArray<int> arr;
    for (int i = 1; i <= 5; i++) arr.append(i);
    arr.remove(2); // removes value 3
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr.get(2), 4);
}
 
TEST(Remove, FromEnd) {
    DynamicArray<int> arr;
    for (int i = 1; i <= 5; i++) arr.append(i);
    arr.remove(4);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr.get(3), 4);
}
 
TEST(Remove, UntilArrayIsEmpty) {
    DynamicArray<int> arr;
    for (int i = 0; i < 10; i++) arr.append(i);
    for (int i = 0; i < 10; i++) arr.remove(0);
    EXPECT_EQ(arr.size(), 0);
}
 
TEST(Remove, DoesNotAutoShrinkCapacity) {
    DynamicArray<int> arr;
    for (int i = 0; i < 10; i++) arr.append(i); // cap becomes 16
    int capBefore = arr.capacity();
    arr.remove(0);
    arr.remove(0);
    EXPECT_EQ(arr.capacity(), capBefore); // by design, no auto-shrink
}
 
TEST(Remove, NegativeIndexExitsProgram) {
    DynamicArray<int> arr;
    EXPECT_THROW(
        arr.remove(-1),
        DynamicArrayException
    );
}
 
TEST(Remove, OnEmptyArrayExitsProgram) {
    EXPECT_THROW({
        DynamicArray<int> arr;
        arr.remove(0); // n==0, so 0 >= n is true -> should hit error()
    }, DynamicArrayException);
}

TEST(Remove, RemoveFirst)
{
    DynamicArray<int> arr;

    for(int i=1;i<=5;i++)
        arr.append(i);

    arr.remove(0);

    EXPECT_EQ(arr.size(),4);
    EXPECT_EQ(arr.get(0),2);
}

TEST(Remove, RemoveMiddle)
{
    DynamicArray<int> arr;

    for(int i=1;i<=5;i++)
        arr.append(i);

    arr.remove(2);

    EXPECT_EQ(arr.get(2),4);
}

TEST(Remove, RemoveLast)
{
    DynamicArray<int> arr;

    arr.append(10);
    arr.append(20);

    arr.remove(1);

    EXPECT_EQ(arr.size(),1);
    EXPECT_EQ(arr.get(0),10);
}

TEST(Remove, RemoveUntilEmpty)
{
    DynamicArray<int> arr;

    arr.append(1);
    arr.remove(0);

    EXPECT_EQ(arr.size(),0);
}

TEST(Remove, RemoveInvalidIndex)
{
    DynamicArray<int> arr;

    EXPECT_THROW(
        arr.remove(0),
        DynamicArrayException
    );
}

TEST(Remove, RemoveNegativeIndex)
{
    DynamicArray<int> arr;

    EXPECT_THROW(
        arr.remove(-1),
        DynamicArrayException
    );
}

TEST(Remove, RepeatedRemoveFromFront)
{
    DynamicArray<int> arr;

    for (int i = 1; i <= 10; i++)
        arr.append(i);

    for (int i = 0; i < 10; i++)
    {
        arr.remove(0);

        EXPECT_EQ(arr.size(), 9 - i);

        for (int j = 0; j < arr.size(); j++)
            EXPECT_EQ(arr.get(j), i + j + 2);
    }
}