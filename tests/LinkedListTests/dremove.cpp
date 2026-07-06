#include "LinkedList.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(DoublyRemove, RemoveMiddleElement)
{
    DoublyLinkedList<int> list;

    for(int i=1;i<=5;i++)
        list.insertBack(i);

    list.remove(2);

    EXPECT_EQ(list.size(),4);

    EXPECT_EQ(list.get(0),1);
    EXPECT_EQ(list.get(1),2);
    EXPECT_EQ(list.get(2),4);
    EXPECT_EQ(list.get(3),5);
}

TEST(DoublyRemove, RemoveMiddleRepeatedly)
{
    DoublyLinkedList<int> list;

    for(int i=0;i<20;i++)
        list.insertBack(i);

    while(list.size()>2)
        list.remove(1);

    EXPECT_EQ(list.size(),2);

    EXPECT_EQ(list.get(0),0);
    EXPECT_EQ(list.get(1),19);
}

TEST(DoublyRemove, RemoveAfterMixedInsertions)
{
    DoublyLinkedList<int> list;

    for(int i=1;i<=10;i++)
        list.insertBack(i);

    list.insert(3,100);
    list.insert(5,200);

    list.remove(4);

    EXPECT_EQ(list.size(),11);

    EXPECT_EQ(list.get(3),100);
    EXPECT_EQ(list.get(4),200);
}

TEST(DoublyRemove, RemoveUntilEmpty)
{
    DoublyLinkedList<int> list;

    for(int i=0;i<100;i++)
        list.insertBack(i);

    while(list.size()>0)
        list.remove(0);

    EXPECT_EQ(list.size(),0);
}

TEST(DoublyRemove, RemoveInvalidIndex)
{
    DoublyLinkedList<int> list;

    list.insertBack(10);

    EXPECT_THROW(
        list.remove(5),
        LinkedListException
    );
}

TEST(DoublyRemove, RemoveNegativeIndex)
{
    DoublyLinkedList<int> list;

    EXPECT_THROW(
        list.remove(-1),
        LinkedListException
    );
}

TEST(DoublyRemove, RemoveAfterPreviousDeletions)
{
    DoublyLinkedList<int> list;

    for(int i=1;i<=15;i++)
        list.insertBack(i);

    list.deleteFront();
    list.deleteBack();

    list.remove(5);

    EXPECT_EQ(list.size(),12);

    EXPECT_EQ(list.get(5),8);
}

TEST(DoublyRemove, StressRemove)
{
    DoublyLinkedList<int> list;

    for(int i=0;i<1000;i++)
        list.insertBack(i);

    while(list.size()>0)
        list.remove(list.size()/2);

    EXPECT_EQ(list.size(),0);
}