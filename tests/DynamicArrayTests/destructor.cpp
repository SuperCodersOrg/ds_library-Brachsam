#include <gtest/gtest.h>
#include "DynamicArray.h"
#include "exception.h"

TEST(Destructor, SelfAssignmentThenDestroy)
{
    {
        DynamicArray<int> arr;

        for(int i = 0; i < 100; i++)
            arr.append(i);

        arr = arr;
    }

    SUCCEED();
}

TEST(Destructor, MultipleCopies)
{
    {
        DynamicArray<int> arr;

        for(int i = 0; i < 100; i++)
            arr.append(i);

        DynamicArray<int> copy1(arr);
        DynamicArray<int> copy2(arr);
        DynamicArray<int> copy3(arr);
    }

    SUCCEED();
}

TEST(Destructor, ChainAssignment)
{
    {
        DynamicArray<int> a;
        DynamicArray<int> b;
        DynamicArray<int> c;

        for(int i = 0; i < 50; i++)
            a.append(i);

        b = a;
        c = b;
    }

    SUCCEED();
}

TEST(Destructor, CopyThenModifyOriginal)
{
    {
        DynamicArray<int> a;

        for(int i = 0; i < 20; i++)
            a.append(i);

        DynamicArray<int> b(a);

        for(int i = 0; i < 10; i++)
            a.remove(0);
    }

    SUCCEED();
}

TEST(Destructor, InsertIntoEmptyThenDestroy)
{
    {
        DynamicArray<int> arr;
        arr.insert(0,10);
    }

    SUCCEED();
}