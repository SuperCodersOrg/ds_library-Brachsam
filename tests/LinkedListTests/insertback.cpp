#include <gtest/gtest.h>
#include "Linkedlist.h"
#include "exception.h"

TEST(SinglyInsertBack, InsertIntoEmptyList)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);

    EXPECT_EQ(list.size(),1);
    EXPECT_EQ(list.get(0),10);
}

TEST(SinglyInsertBack, InsertMultipleElements)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    EXPECT_EQ(list.size(),3);

    EXPECT_EQ(list.get(0),10);
    EXPECT_EQ(list.get(1),20);
    EXPECT_EQ(list.get(2),30);
}

TEST(SinglyInsertBack, InsertLargeNumberOfElements)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<1000;i++)
        list.insertBack(i);

    EXPECT_EQ(list.size(),1000);

    EXPECT_EQ(list.get(0),0);
    EXPECT_EQ(list.get(999),999);
}

TEST(SinglyInsertBack, InsertDuplicateValues)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<5;i++)
        list.insertBack(50);

    EXPECT_EQ(list.size(),5);

    for(int i=0;i<5;i++)
        EXPECT_EQ(list.get(i),50);
}

TEST(SinglyInsertBack, AlternateFrontBackInsertions)
{
    SinglyLinkedList<int> list;

    list.insertBack(2);
    list.insertFront(1);
    list.insertBack(3);
    list.insertFront(0);

    EXPECT_EQ(list.size(),4);

    EXPECT_EQ(list.get(0),0);
    EXPECT_EQ(list.get(1),1);
    EXPECT_EQ(list.get(2),2);
    EXPECT_EQ(list.get(3),3);
}

TEST(SinglyInsertBack, DeleteBackAfterInsertion)
{
    SinglyLinkedList<int> list;

    for(int i=1;i<=10;i++)
        list.insertBack(i);

    list.deleteBack();

    EXPECT_EQ(list.size(),9);
    EXPECT_EQ(list.get(8),9);
}

TEST(SinglyInsertBack, InsertNegativeValues)
{
    SinglyLinkedList<int> list;

    list.insertBack(-10);
    list.insertBack(-20);

    EXPECT_EQ(list.get(0),-10);
    EXPECT_EQ(list.get(1),-20);
}

TEST(SinglyInsertBack, ContinuousInsertDelete)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<200;i++)
        list.insertBack(i);

    while(list.size()>0)
        list.deleteBack();

    EXPECT_EQ(list.size(),0);
}