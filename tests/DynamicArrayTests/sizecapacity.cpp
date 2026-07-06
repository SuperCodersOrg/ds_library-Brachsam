#include <gtest/gtest.h>
#include "DynamicArray.h"
#include "exception.h"

TEST(SizeCapacity, FreshArrayStartsAtZeroSizeCapFour) {
    DynamicArray<int> arr;
    EXPECT_EQ(arr.size(), 0);
    EXPECT_EQ(arr.capacity(), 4);
}
 
TEST(SizeCapacity, SizeGrowsOneAtATimeWithAppend) {
    DynamicArray<int> arr;
    for (int i = 0; i < 7; i++) {
        arr.append(i);
        EXPECT_EQ(arr.size(), i + 1); // size must track exactly, not just at the end
    }
}
 
TEST(SizeCapacity, CapacityNeverShrinksBelowHighWaterMark) {
    DynamicArray<int> arr;
    for (int i = 0; i < 20; i++) arr.append(i); // cap grows to 32
    int peakCap = arr.capacity();
    for (int i = 0; i < 15; i++) arr.remove(0); // remove almost everything
    EXPECT_EQ(arr.capacity(), peakCap); // by design: no auto-shrink anywhere
    EXPECT_EQ(arr.size(), 5);
}
 
TEST(SizeCapacity, SizeAndCapacityStayConsistentAfterInsertRemoveMix) {
    DynamicArray<int> arr;
    for (int i = 0; i < 5; i++) arr.append(i);   // size 5
    arr.insert(0, -1);                            // size 6
    arr.remove(3);                                 // size 5
    arr.insert(5, 999);                            // size 6
    EXPECT_EQ(arr.size(), 6);
    EXPECT_GE(arr.capacity(), arr.size()); // capacity must never be less than size
}
 
TEST(SizeCapacity, CapacityIsAlwaysPowerOfTwo) {
    DynamicArray<int> arr;
    for (int i = 0; i < 500; i++) {
        arr.append(i);
        int cap = arr.capacity();
        EXPECT_EQ(cap & (cap - 1), 0) << "capacity " << cap << " is not a power of two at n=" << arr.size();
    }
}
 
TEST(SizeCapacity, CopyAndAssignPreserveSizeExactly) {
    DynamicArray<int> a;
    for (int i = 0; i < 9; i++) a.append(i);
    DynamicArray<int> b = a;
    DynamicArray<int> c;
    c = a;
    EXPECT_EQ(b.size(), 9);
    EXPECT_EQ(c.size(), 9);
}

TEST(SizeCapacity, MultipleResizeCycles)
{
    DynamicArray<int> arr;

    for(int round = 0; round < 5; round++)
    {
        for(int i = 0; i < 100; i++)
            arr.append(i);

        for(int i = 0; i < 95; i++)
            arr.remove(0);
    }

    EXPECT_EQ(arr.size(),25);
    EXPECT_GE(arr.capacity(),arr.size());
}

TEST(SizeCapacity, SizeNeverNegative)
{
    DynamicArray<int> arr;

    arr.append(10);
    arr.remove(0);

    EXPECT_EQ(arr.size(), 0);

    EXPECT_THROW(
        arr.remove(0),
        DynamicArrayException
    );
}

TEST(SizeCapacity, CapacityDoesNotChangeWithoutResize)
{
    DynamicArray<int> arr;

    int initial = arr.capacity();

    arr.append(1);
    arr.append(2);
    arr.append(3);

    EXPECT_EQ(arr.capacity(),initial);
}

TEST(SizeCapacity, CapacityDoublesExactly)
{
    DynamicArray<int> arr;

    int oldCap = arr.capacity();

    for(int i = 0; i < oldCap; i++)
        arr.append(i);

    arr.append(100);

    EXPECT_EQ(arr.capacity(),oldCap * 2);
}

TEST(SizeCapacity, AssignmentCopiesCapacity)
{
    DynamicArray<int> a;

    for(int i=0;i<17;i++)
        a.append(i);

    DynamicArray<int> b;
    b = a;

    EXPECT_EQ(b.capacity(),a.capacity());
}

TEST(SizeCapacity, CopyConstructorCopiesCapacity)
{
    DynamicArray<int> a;

    for(int i=0;i<17;i++)
        a.append(i);

    DynamicArray<int> b(a);

    EXPECT_EQ(b.capacity(),a.capacity());
}