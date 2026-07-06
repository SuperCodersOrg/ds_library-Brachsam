#include "Linkedlist.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(SinglyDeleteFront, DeleteSingleElement)
{
    SinglyLinkedList<int> list;
    list.insertBack(10);
    list.deleteFront();
    EXPECT_EQ(list.size(),0);
}

TEST(SinglyDeleteFront, DeleteFrontMultipleElements)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    list.deleteFront();

    EXPECT_EQ(list.size(),2);

    EXPECT_EQ(list.get(0),20);
    EXPECT_EQ(list.get(1),30);
}

TEST(SinglyDeleteFront, DeleteUntilEmpty)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<100;i++)
        list.insertBack(i);

    while(list.size()>0)
        list.deleteFront();

    EXPECT_EQ(list.size(),0);
}

TEST(SinglyDeleteFront, DeleteFromEmptyList)
{
    SinglyLinkedList<int> list;

    EXPECT_THROW(
        list.deleteFront(),
        EmptyListException
    );
}

TEST(SinglyDeleteFront, AlternateInsertDelete)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<50;i++)
    {
        list.insertBack(i);
        list.deleteFront();
    }

    EXPECT_EQ(list.size(),0);
}

TEST(SinglyDeleteFront, DeleteAfterInsertFront)
{
    SinglyLinkedList<int> list;

    list.insertFront(1);
    list.insertFront(2);
    list.insertFront(3);

    list.deleteFront();

    EXPECT_EQ(list.size(),2);

    EXPECT_EQ(list.get(0),2);
    EXPECT_EQ(list.get(1),1);
}

TEST(SinglyDeleteFront, DeleteAfterMixedInsertions)
{
    SinglyLinkedList<int> list;

    list.insertFront(2);
    list.insertBack(3);
    list.insertFront(1);
    list.insertBack(4);

    list.deleteFront();

    EXPECT_EQ(list.size(),3);

    EXPECT_EQ(list.get(0),2);
    EXPECT_EQ(list.get(1),3);
    EXPECT_EQ(list.get(2),4);
}

TEST(SinglyDeleteFront, StressDeleteFront)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<1000;i++)
        list.insertBack(i);

    for(int i=0;i<1000;i++)
        list.deleteFront();

    EXPECT_EQ(list.size(),0);
}