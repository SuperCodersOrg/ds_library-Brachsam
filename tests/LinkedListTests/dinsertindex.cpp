#include "LinkedList.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(DoublyInsert, InsertMiddle)
{
    DoublyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(40);

    list.insert(2,30);

    EXPECT_EQ(list.size(),4);

    EXPECT_EQ(list.get(0),10);
    EXPECT_EQ(list.get(1),20);
    EXPECT_EQ(list.get(2),30);
    EXPECT_EQ(list.get(3),40);
}

TEST(DoublyInsert, MultipleMiddleInsertions)
{
    DoublyLinkedList<int> list;

    list.insertBack(1);

    for(int i=2;i<=10;i++)
        list.insert(1,i);

    EXPECT_EQ(list.size(),10);

    EXPECT_EQ(list.get(0),1);

    for(int i=1;i<10;i++)
        EXPECT_EQ(list.get(i),11-i);
}

TEST(DoublyInsert, InsertAfterDeletions)
{
    DoublyLinkedList<int> list;

    for(int i=1;i<=10;i++)
        list.insertBack(i);

    list.deleteFront();
    list.deleteBack();

    list.insert(4,100);

    EXPECT_EQ(list.size(),9);

    EXPECT_EQ(list.get(4),100);
}

TEST(DoublyInsert, InsertAtBeginning)
{
    DoublyLinkedList<int> list;

    list.insertBack(20);
    list.insertBack(30);

    list.insert(0,10);

    EXPECT_EQ(list.size(),3);

    EXPECT_EQ(list.get(0),10);
    EXPECT_EQ(list.get(1),20);
    EXPECT_EQ(list.get(2),30);
}

TEST(DoublyInsert, InsertAtEnd)
{
    DoublyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);

    list.insert(list.size(),30);

    EXPECT_EQ(list.size(),3);

    EXPECT_EQ(list.get(2),30);
}

TEST(DoublyInsert, InsertNegativeIndex)
{
    DoublyLinkedList<int> list;

    EXPECT_THROW(
        list.insert(-1,10),
        LinkedListException
    );
}

TEST(DoublyInsert, InsertPastEnd)
{
    DoublyLinkedList<int> list;

    list.insertBack(10);

    EXPECT_THROW(
        list.insert(5,20),
        LinkedListException
    );
}

TEST(DoublyInsert, StressInsertMiddle)
{
    DoublyLinkedList<int> list;

    for(int i=0;i<500;i++)
        list.insertBack(i);

    for(int i=0;i<100;i++)
        list.insert(250,-1);

    EXPECT_EQ(list.size(),600);
}