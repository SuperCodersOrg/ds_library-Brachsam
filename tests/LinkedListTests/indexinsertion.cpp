#include <gtest/gtest.h>
#include "Linkedlist.h"
#include "exception.h"

TEST(SinglyInsert, InsertAtBeginning)
{
    SinglyLinkedList<int> list;

    list.insertBack(2);
    list.insertBack(3);

    list.insert(0,1);

    EXPECT_EQ(list.size(),3);

    EXPECT_EQ(list.get(0),1);
    EXPECT_EQ(list.get(1),2);
    EXPECT_EQ(list.get(2),3);
}

TEST(SinglyInsert, InsertAtEnd)
{
    SinglyLinkedList<int> list;

    list.insertBack(1);
    list.insertBack(2);

    list.insert(list.size(),3);

    EXPECT_EQ(list.size(),3);

    EXPECT_EQ(list.get(0),1);
    EXPECT_EQ(list.get(1),2);
    EXPECT_EQ(list.get(2),3);
}

TEST(SinglyInsert, InsertAtMiddle)
{
    SinglyLinkedList<int> list;

    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(4);

    list.insert(2,3);

    EXPECT_EQ(list.size(),4);

    EXPECT_EQ(list.get(0),1);
    EXPECT_EQ(list.get(1),2);
    EXPECT_EQ(list.get(2),3);
    EXPECT_EQ(list.get(3),4);
}

TEST(SinglyInsert, MultipleMiddleInsertions)
{
    SinglyLinkedList<int> list;

    list.insertBack(1);

    for(int i=2;i<=10;i++)
        list.insert(1,i);

    EXPECT_EQ(list.size(),10);

    EXPECT_EQ(list.get(0),1);

    for(int i=1;i<10;i++)
        EXPECT_EQ(list.get(i),11-i);
}

TEST(SinglyInsert, InsertIntoEmptyList)
{
    SinglyLinkedList<int> list;

    list.insert(0,100);

    EXPECT_EQ(list.size(),1);
    EXPECT_EQ(list.get(0),100);
}

TEST(SinglyInsert, InsertNegativeIndex)
{
    SinglyLinkedList<int> list;

    EXPECT_THROW(
        list.insert(-1,10),
        LinkedListException
    );
}

TEST(SinglyInsert, InsertPastEnd)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);

    EXPECT_THROW(
        list.insert(5,20),
        LinkedListException
    );
}

TEST(SinglyInsert, InsertAfterMultipleOperations)
{
    SinglyLinkedList<int> list;

    for(int i=1;i<=20;i++)
        list.insertBack(i);

    for(int i=0;i<5;i++)
        list.deleteFront();

    for(int i=0;i<5;i++)
        list.deleteBack();

    list.insert(5,999);

    EXPECT_EQ(list.get(5),999);
    EXPECT_EQ(list.size(),11);
}

TEST(SinglyInsert, InsertDuplicateValues)
{
    SinglyLinkedList<int> list;

    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);

    list.insert(1,2);

    EXPECT_EQ(list.size(),4);

    EXPECT_EQ(list.get(0),1);
    EXPECT_EQ(list.get(1),2);
    EXPECT_EQ(list.get(2),2);
    EXPECT_EQ(list.get(3),3);
}

TEST(SinglyInsert, StressInsertMiddle)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<500;i++)
        list.insertBack(i);

    for(int i=0;i<100;i++)
        list.insert(250,-1);

    EXPECT_EQ(list.size(),600);
}