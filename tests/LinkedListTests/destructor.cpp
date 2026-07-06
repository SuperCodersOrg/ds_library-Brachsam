#include "LinkedList.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(SinglyDestructor, DestroyEmptyList)
{
    {
        SinglyLinkedList<int> list;
    }
    SUCCEED();
}

TEST(SinglyDestructor, DestroySingleNode)
{
    {
        SinglyLinkedList<int> list;
        list.insertBack(10);
    }
    SUCCEED();
}

TEST(SinglyDestructor, DestroyLargeList)
{
    {
        SinglyLinkedList<int> list;
        for(int i=0;i<5000;i++)
            list.insertBack(i);
    }
    SUCCEED();
}

TEST(SinglyDestructor, DestroyAfterClear)
{
    {
        SinglyLinkedList<int> list;
        for(int i=0;i<100;i++)
            list.insertBack(i);
        list.clear();
    }
    SUCCEED();
}

TEST(SinglyDestructor, DestroyCopiedLists)
{
    {
        SinglyLinkedList<int> list;
        for(int i=0;i<100;i++)
            list.insertBack(i);
        SinglyLinkedList<int> copy(list);
    }
    SUCCEED();
}

TEST(SinglyDestructor, DestroyAssignedLists)
{
    {
        SinglyLinkedList<int> list1;
        SinglyLinkedList<int> list2;
        for(int i=0;i<100;i++)
            list1.insertBack(i);
        list2 = list1;
    }
    SUCCEED();
}

TEST(SinglyDestructor, NestedObjects)
{
    {
        SinglyLinkedList<int> outer;
        outer.insertBack(1);
        {
            SinglyLinkedList<int> inner;
            inner.insertBack(2);
            inner.insertBack(3);
        }
        EXPECT_EQ(outer.size(),1);
    }
    SUCCEED();
}

TEST(SinglyDestructor, MultipleObjects)
{
    {
        SinglyLinkedList<int> list1;
        SinglyLinkedList<int> list2;
        SinglyLinkedList<int> list3;
        for(int i=0;i<50;i++)
        {
            list1.insertBack(i);
            list2.insertBack(i);
            list3.insertBack(i);
        }
    }
    SUCCEED();
}