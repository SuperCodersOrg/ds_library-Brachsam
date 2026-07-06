#include "Linkedlist.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(SinglyDeleteBack, DeleteSingleElement)
{
    SinglyLinkedList<int> list;
    list.insertBack(10);
    list.deleteBack();
    EXPECT_EQ(list.size(),0);
}

TEST(SinglyDeleteBack, DeleteBackMultipleElements)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    list.deleteBack();

    EXPECT_EQ(list.size(),2);

    EXPECT_EQ(list.get(0),10);
    EXPECT_EQ(list.get(1),20);
}

TEST(SinglyDeleteBack, DeleteBackUntilEmpty)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<100;i++)
        list.insertBack(i);

    while(list.size()>0)
        list.deleteBack();

    EXPECT_EQ(list.size(),0);
}

TEST(SinglyDeleteBack, DeleteBackFromEmptyList)
{
    SinglyLinkedList<int> list;

    EXPECT_THROW(
        list.deleteBack(),
        EmptyListException
    );
}

TEST(SinglyDeleteBack, AlternateInsertDelete)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<50;i++)
    {
        list.insertBack(i);
        list.deleteBack();
    }

    EXPECT_EQ(list.size(),0);
}

TEST(SinglyDeleteBack, DeleteAfterInsertFront)
{
    SinglyLinkedList<int> list;

    list.insertFront(1);
    list.insertFront(2);
    list.insertFront(3);

    list.deleteBack();

    EXPECT_EQ(list.size(),2);

    EXPECT_EQ(list.get(0),3);
    EXPECT_EQ(list.get(1),2);
}

TEST(SinglyDeleteBack, DeleteAfterMixedOperations)
{
    SinglyLinkedList<int> list;

    for(int i=1;i<=20;i++)
        list.insertBack(i);

    for(int i=0;i<5;i++)
        list.deleteFront();

    for(int i=0;i<5;i++)
        list.deleteBack();

    EXPECT_EQ(list.size(),10);

    EXPECT_EQ(list.get(0),6);
    EXPECT_EQ(list.get(9),15);
}

TEST(SinglyDeleteBack, StressDeleteBack)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<1000;i++)
        list.insertBack(i);

    for(int i=0;i<1000;i++)
        list.deleteBack();

    EXPECT_EQ(list.size(),0);
}

TEST(SinglyDeleteBack, ReuseAfterDeletingAllElements)
{
    SinglyLinkedList<int> list;

    list.insertBack(1);
    list.insertBack(2);

    list.deleteBack();
    list.deleteBack();

    list.insertBack(100);

    EXPECT_EQ(list.size(),1);
    EXPECT_EQ(list.get(0),100);
}