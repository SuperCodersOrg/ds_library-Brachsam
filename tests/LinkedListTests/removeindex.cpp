#include "Linkedlist.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(SinglyRemove, RemoveFirstElement)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    list.remove(0);

    EXPECT_EQ(list.size(),2);

    EXPECT_EQ(list.get(0),20);
    EXPECT_EQ(list.get(1),30);
}

TEST(SinglyRemove, RemoveLastElement)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    list.remove(2);

    EXPECT_EQ(list.size(),2);

    EXPECT_EQ(list.get(0),10);
    EXPECT_EQ(list.get(1),20);
}

TEST(SinglyRemove, RemoveMiddleElement)
{
    SinglyLinkedList<int> list;

    for(int i=1;i<=5;i++)
        list.insertBack(i);

    list.remove(2);

    EXPECT_EQ(list.size(),4);

    EXPECT_EQ(list.get(0),1);
    EXPECT_EQ(list.get(1),2);
    EXPECT_EQ(list.get(2),4);
    EXPECT_EQ(list.get(3),5);
}

TEST(SinglyRemove, RemoveMiddleRepeatedly)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<20;i++)
        list.insertBack(i);

    while(list.size()>2)
        list.remove(1);

    EXPECT_EQ(list.size(),2);

    EXPECT_EQ(list.get(0),0);
    EXPECT_EQ(list.get(1),19);
}

TEST(SinglyRemove, RemoveUntilEmpty)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<50;i++)
        list.insertBack(i);

    while(list.size()>0)
        list.remove(0);

    EXPECT_EQ(list.size(),0);
}

TEST(SinglyRemove, RemoveNegativeIndex)
{
    SinglyLinkedList<int> list;

    EXPECT_THROW(
        list.remove(-1),
        LinkedListException
    );
}

TEST(SinglyRemove, RemovePastEnd)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);

    EXPECT_THROW(
        list.remove(5),
        LinkedListException
    );
}

TEST(SinglyRemove, RemoveFromEmptyList)
{
    SinglyLinkedList<int> list;

    EXPECT_THROW(
        list.remove(0),
        LinkedListException
    );
}

TEST(SinglyRemove, MixedInsertRemoveOperations)
{
    SinglyLinkedList<int> list;

    for(int i=1;i<=10;i++)
        list.insertBack(i);

    list.remove(3);
    list.remove(5);

    list.insertFront(100);
    list.insertBack(200);

    EXPECT_EQ(list.size(),10);

    EXPECT_EQ(list.get(0),100);
    EXPECT_EQ(list.get(9),200);
}

TEST(SinglyRemove, StressRemove)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<1000;i++)
        list.insertBack(i);

    while(list.size()>0)
        list.remove(list.size()/2);

    EXPECT_EQ(list.size(),0);
}

