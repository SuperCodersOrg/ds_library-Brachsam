#include "LinkedList.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(SinglySize, EmptyList)
{
    SinglyLinkedList<int> list;

    EXPECT_EQ(list.size(),0);
}

TEST(SinglySize, SizeAfterInsertFront)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<10;i++)
    {
        list.insertFront(i);
        EXPECT_EQ(list.size(),i+1);
    }
}

TEST(SinglySize, SizeAfterInsertBack)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<20;i++)
    {
        list.insertBack(i);
        EXPECT_EQ(list.size(),i+1);
    }
}

TEST(SinglySize, SizeAfterMixedOperations)
{
    SinglyLinkedList<int> list;

    list.insertBack(1);
    list.insertBack(2);
    list.insertFront(0);
    list.deleteBack();
    list.insert(1,100);
    list.remove(0);

    EXPECT_EQ(list.size(),2);
}

TEST(SinglySize, SizeNeverNegative)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);

    list.deleteFront();

    EXPECT_EQ(list.size(),0);

    EXPECT_THROW(
        list.deleteFront(),
        EmptyListException
    );
}

TEST(SinglySize, SizeAfterClear)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<100;i++)
        list.insertBack(i);

    list.clear();

    EXPECT_EQ(list.size(),0);
}

TEST(SinglySize, StressSizeUpdates)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<1000;i++)
        list.insertBack(i);

    for(int i=0;i<500;i++)
        list.deleteFront();

    for(int i=0;i<250;i++)
        list.deleteBack();

    EXPECT_EQ(list.size(),250);
}

