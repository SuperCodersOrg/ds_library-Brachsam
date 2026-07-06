#include <gtest/gtest.h>
#include "DynamicArray.h"
#include "exception.h"

TEST(DynamicArrayAppendTest, AppendOneElement)
{
    DynamicArray<int> arr;

    arr.append(10);

    EXPECT_EQ(arr.size(),1);
    EXPECT_EQ(arr.get(0),10);
}

TEST(DynamicArrayAppendTest, AppendMultipleElements)
{
    DynamicArray<int> arr;

    for(int i=1;i<=5;i++)
        arr.append(i);

    EXPECT_EQ(arr.size(),5);

    for(int i=0;i<5;i++)
        EXPECT_EQ(arr.get(i),i+1);
}

TEST(DynamicArrayAppendTest, AppendTriggersResize)
{
    DynamicArray<int> arr;

    int oldCap = arr.capacity();

    for(int i=0;i<oldCap+1;i++)
        arr.append(i);

    EXPECT_GT(arr.capacity(),oldCap);

    for(int i=0;i<oldCap+1;i++)
        EXPECT_EQ(arr.get(i),i);
}

TEST(DynamicArrayAppendTest, AppendLargeDataset)
{
    DynamicArray<int> arr;

    for(int i=0;i<10000;i++)
        arr.append(i);

    EXPECT_EQ(arr.size(),10000);

    EXPECT_EQ(arr.get(0),0);
    EXPECT_EQ(arr.get(9999),9999);
}

TEST(DynamicArrayAppendTest, AppendDuplicateValues)
{
    DynamicArray<int> arr;

    for(int i=0;i<10;i++)
        arr.append(5);

    EXPECT_EQ(arr.size(),10);

    for(int i=0;i<10;i++)
        EXPECT_EQ(arr.get(i),5);
}

TEST(DynamicArrayAppendTest, AppendNegativeNumbers)
{
    DynamicArray<int> arr;

    arr.append(-5);
    arr.append(-10);

    EXPECT_EQ(arr.get(0),-5);
    EXPECT_EQ(arr.get(1),-10);
}