#include "LinkedList.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(SinglyGet, GetFirstElement)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    EXPECT_EQ(list.get(0),10);
}

TEST(SinglyGet, GetLastElement)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    EXPECT_EQ(list.get(2),30);
}

TEST(SinglyGet, GetMiddleElement)
{
    SinglyLinkedList<int> list;

    for(int i=1;i<=5;i++)
        list.insertBack(i);

    EXPECT_EQ(list.get(2),3);
}

TEST(SinglyGet, GetAfterInsertDeleteOperations)
{
    SinglyLinkedList<int> list;

    for(int i=1;i<=10;i++)
        list.insertBack(i);

    list.deleteFront();
    list.deleteBack();
    list.insert(3,100);

    EXPECT_EQ(list.get(0),2);
    EXPECT_EQ(list.get(3),100);
    EXPECT_EQ(list.get(8),9);
}

TEST(SinglyGet, GetFromEmptyList)
{
    SinglyLinkedList<int> list;

    EXPECT_THROW(
        list.get(0),
        LinkedListException
    );
}

TEST(SinglyGet, GetNegativeIndex)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);

    EXPECT_THROW(
        list.get(-1),
        LinkedListException
    );
}

TEST(SinglyGet, GetIndexEqualToSize)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);

    EXPECT_THROW(
        list.get(2),
        LinkedListException
    );
}

TEST(SinglyGet, GetLargeIndex)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<20;i++)
        list.insertBack(i);

    EXPECT_THROW(
        list.get(100),
        LinkedListException
    );
}

TEST(SinglyGet, StressGet)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<1000;i++)
        list.insertBack(i);

    EXPECT_EQ(list.get(0),0);
    EXPECT_EQ(list.get(250),250);
    EXPECT_EQ(list.get(500),500);
    EXPECT_EQ(list.get(999),999);
}

TEST(SinglyGet, GetAfterRepeatedRemovals)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<20;i++)
        list.insertBack(i);

    for(int i=0;i<5;i++)
        list.remove(5);

    EXPECT_EQ(list.get(5),10);
    EXPECT_EQ(list.size(),15);
}

