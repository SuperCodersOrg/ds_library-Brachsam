#include <gtest/gtest.h>
#include "DynamicArray.h"
#include "exception.h"

TEST(Insert, AtBeginning) {
    DynamicArray<int> arr;
    for (int i = 1; i <= 5; i++) arr.append(i);
    arr.insert(0, 100);
    EXPECT_EQ(arr.size(), 6);
    EXPECT_EQ(arr.get(0), 100);
    EXPECT_EQ(arr.get(1), 1);
    EXPECT_EQ(arr.get(5), 5);
}
 
TEST(Insert, AtMiddle) {
    DynamicArray<int> arr;
    for (int i = 1; i <= 5; i++) arr.append(i);
    arr.insert(2, 99);
    EXPECT_EQ(arr.size(), 6);
    EXPECT_EQ(arr.get(2), 99);
    EXPECT_EQ(arr.get(3), 3);
}
 
TEST(Insert, AtEndEqualsAppend) {
    DynamicArray<int> arr;
    for (int i = 1; i <= 5; i++) arr.append(i);
    arr.insert(arr.size(), 200);
    EXPECT_EQ(arr.size(), 6);
    EXPECT_EQ(arr.get(5), 200);
}
 
TEST(Insert, TriggersResizeWhenFull) {
    DynamicArray<int> arr;
    for (int i = 0; i < 4; i++) arr.append(i); // fill to cap=4
    int oldCap = arr.capacity();
    arr.insert(2, -1);
    EXPECT_GT(arr.capacity(), oldCap);
    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr.get(2), -1);
}
 
TEST(Insert, NegativeIndexExitsProgram)
{
    DynamicArray<int> arr;
    EXPECT_THROW(
        arr.insert(-1, 5),
        DynamicArrayException
    );
}
 
TEST(Insert, IndexPastEndExitsProgram)
{
    DynamicArray<int> arr;
    arr.append(10);
    EXPECT_THROW(
        arr.insert(5, 5),
        DynamicArrayException
    );
}

TEST(DynamicArrayInsertDeathTest, InsertNegativeIndex)
{
    DynamicArray<int> arr;
    EXPECT_THROW(
        arr.insert(-1,5),
        DynamicArrayException
    );
}


TEST(DynamicArrayInsertDeathTest, InsertPastEnd)
{
    DynamicArray<int> arr;
    arr.append(10);
    EXPECT_THROW(
        arr.insert(5,50),
        DynamicArrayException
    );
} 