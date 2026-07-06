#include <gtest/gtest.h>
#include "Linkedlist.h"
#include "exception.h"

TEST(SinglyInsertFront, ReverseOrderCheck)
{
    SinglyLinkedList<int> list;

    for(int i=1;i<=100;i++)
        list.insertFront(i);

    EXPECT_EQ(list.size(),100);

    for(int i=0;i<100;i++)
        EXPECT_EQ(list.get(i),100-i);
}

TEST(SinglyInsertFront, InsertIntoEmptyList)
{
    SinglyLinkedList<int> list;

    list.insertFront(10);

    EXPECT_EQ(list.size(),1);
    EXPECT_EQ(list.get(0),10);
}

TEST(SinglyInsertFront, InsertMultipleElements)
{
    SinglyLinkedList<int> list;

    list.insertFront(10);
    list.insertFront(20);
    list.insertFront(30);

    EXPECT_EQ(list.size(),3);

    EXPECT_EQ(list.get(0),30);
    EXPECT_EQ(list.get(1),20);
    EXPECT_EQ(list.get(2),10);
}

TEST(SinglyInsertFront, InsertLargeNumberOfElements)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<1000;i++)
        list.insertFront(i);

    EXPECT_EQ(list.size(),1000);

    EXPECT_EQ(list.get(0),999);
    EXPECT_EQ(list.get(999),0);
}

TEST(SinglyInsertFront, InsertDuplicateValues)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<5;i++)
        list.insertFront(100);

    EXPECT_EQ(list.size(),5);

    for(int i=0;i<5;i++)
        EXPECT_EQ(list.get(i),100);
}

TEST(SinglyInsertFront, AlternateFrontAndBackInsertion)
{
    SinglyLinkedList<int> list;

    list.insertFront(2);
    list.insertBack(3);
    list.insertFront(1);
    list.insertBack(4);

    EXPECT_EQ(list.size(),4);

    EXPECT_EQ(list.get(0),1);
    EXPECT_EQ(list.get(1),2);
    EXPECT_EQ(list.get(2),3);
    EXPECT_EQ(list.get(3),4);
}

TEST(SinglyInsertFront, SearchAfterInsertions)
{
    SinglyLinkedList<int> list;

    list.insertFront(10);
    list.insertFront(20);
    list.insertFront(30);

    EXPECT_TRUE(list.search(10));
    EXPECT_TRUE(list.search(20));
    EXPECT_TRUE(list.search(30));
    EXPECT_FALSE(list.search(100));
}

TEST(SinglyInsertFront, ContinuousInsertAndRemove)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<100;i++)
        list.insertFront(i);

    for(int i=0;i<100;i++)
        list.deleteFront();

    EXPECT_EQ(list.size(),0);
}

TEST(SinglyInsertFront, InsertNegativeValues)
{
    SinglyLinkedList<int> list;

    list.insertFront(-10);
    list.insertFront(-20);

    EXPECT_EQ(list.get(0),-20);
    EXPECT_EQ(list.get(1),-10);
}

