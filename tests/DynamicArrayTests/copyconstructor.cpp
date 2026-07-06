#include <gtest/gtest.h>
#include "DynamicArray.h"
#include "exception.h"

TEST(CopyConstructor, CopiesAllValues) {
    DynamicArray<int> a;
    for (int i = 0; i < 5; i++) a.append(i);
    DynamicArray<int> b = a;
    EXPECT_EQ(b.size(), 5);
    for (int i = 0; i < 5; i++) EXPECT_EQ(b.get(i), i);
}
 
TEST(CopyConstructor, IsADeepCopyNotShared) {
    DynamicArray<int> a;
    a.append(1);
    a.append(2);
    DynamicArray<int> b = a;
    b.remove(0);          // mutate the copy
    EXPECT_EQ(a.size(), 2); // original must be unaffected
    EXPECT_EQ(a.get(0), 1);
}
 
TEST(CopyConstructor, PreservesCapacityToo) {
    DynamicArray<int> a;
    for (int i = 0; i < 10; i++) a.append(i); // cap grows to 16
    DynamicArray<int> b = a;
    EXPECT_EQ(b.capacity(), a.capacity());
}
 
TEST(CopyConstructor, WorksOnEmptyArray) {
    DynamicArray<int> a;
    DynamicArray<int> b = a;
    EXPECT_EQ(b.size(), 0);
}
 
TEST(CopyConstructor, WorksAfterMultipleResizesOnSource) {
    DynamicArray<int> a;
    for (int i = 0; i < 200; i++) a.append(i);
    DynamicArray<int> b = a;
    EXPECT_EQ(b.size(), a.size());
    for (int i = 0; i < 200; i++) EXPECT_EQ(b.get(i), i);
}
 
TEST(CopyConstructor, LargeDatasetStress) {
    DynamicArray<int> a;
    for (int i = 0; i < 1000; i++) a.append(i * 2);
    DynamicArray<int> b = a;
    for (int i = 0; i < 1000; i++) EXPECT_EQ(b.get(i), i * 2);
}

TEST(CopyConstructor, CopyEmptyArray)
{
    DynamicArray<int> arr;

    DynamicArray<int> copy(arr);

    EXPECT_EQ(copy.size(),0);
    EXPECT_EQ(copy.capacity(),arr.capacity());
}

TEST(CopyConstructor, CopySingleElement)
{
    DynamicArray<int> arr;

    arr.append(100);

    DynamicArray<int> copy(arr);

    EXPECT_EQ(copy.size(),1);
    EXPECT_EQ(copy.get(0),100);
}

TEST(CopyConstructor, CopyMultipleElements)
{
    DynamicArray<int> arr;

    for(int i=1;i<=10;i++)
        arr.append(i);

    DynamicArray<int> copy(arr);

    EXPECT_EQ(copy.size(),arr.size());

    for(int i=0;i<arr.size();i++)
        EXPECT_EQ(copy.get(i),arr.get(i));
}

TEST(CopyConstructor, ModifyOriginalAfterCopy)
{
    DynamicArray<int> arr;

    arr.append(1);
    arr.append(2);
    arr.append(3);

    DynamicArray<int> copy(arr);

    arr.remove(0);

    EXPECT_EQ(copy.size(),3);
    EXPECT_EQ(copy.get(0),1);
    EXPECT_EQ(copy.get(1),2);
    EXPECT_EQ(copy.get(2),3);
}

TEST(CopyConstructor, ModifyCopyDoesNotAffectOriginal)
{
    DynamicArray<int> arr;

    arr.append(10);
    arr.append(20);
    arr.append(30);

    DynamicArray<int> copy(arr);

    copy.remove(1);

    EXPECT_EQ(arr.size(),3);
    EXPECT_EQ(arr.get(0),10);
    EXPECT_EQ(arr.get(1),20);
    EXPECT_EQ(arr.get(2),30);

    EXPECT_EQ(copy.size(),2);
}

TEST(CopyConstructor, CopyLargeArray)
{
    DynamicArray<int> arr;

    for(int i=0;i<1000;i++)
        arr.append(i);

    DynamicArray<int> copy(arr);

    EXPECT_EQ(copy.size(),1000);

    for(int i=0;i<1000;i++)
        EXPECT_EQ(copy.get(i),i);
}