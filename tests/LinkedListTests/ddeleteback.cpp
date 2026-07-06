#include "LinkedList.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(DoublyDeleteBack, DeleteSingleElement)
{
    DoublyLinkedList<int> list;
    list.insertBack(10);
    list.deleteBack();
    EXPECT_EQ(list.size(),0);
}

TEST(DoublyDeleteBack, DeleteBackMultipleElements)
{
    DoublyLinkedList<int> list;
    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);
    list.deleteBack();

    EXPECT_EQ(list.size(),2);
    EXPECT_EQ(list.get(0),10);
    EXPECT_EQ(list.get(1),20);
}

TEST(DoublyDeleteBack, DeleteUntilEmpty)
{
    DoublyLinkedList<int> list;
    for(int i=0;i<100;i++)
        list.insertBack(i);

    while(list.size()>0)
        list.deleteBack();
    EXPECT_EQ(list.size(),0);
}

TEST(DoublyDeleteBack, DeleteFromEmptyList)
{
    DoublyLinkedList<int> list;

    EXPECT_THROW(
        list.deleteBack(),
        EmptyListException
    );
}

TEST(DoublyDeleteBack, AlternateFrontBackDeletion)
{
    DoublyLinkedList<int> list;

    for(int i=1;i<=20;i++)
        list.insertBack(i);

    while(list.size()>1)
    {
        list.deleteFront();

        if(list.size())
            list.deleteBack();
    }

    EXPECT_LE(list.size(),1);
}

TEST(DoublyDeleteBack, DeleteAfterMiddleInsertions)
{
    DoublyLinkedList<int> list;

    for(int i=1;i<=10;i++)
        list.insertBack(i);

    list.insert(5,100);
    list.insert(3,200);

    list.deleteBack();

    EXPECT_EQ(list.size(),11);

    EXPECT_EQ(list.get(9),8);
    EXPECT_EQ(list.get(10),9);
}

TEST(DoublyDeleteBack, ReuseAfterDeletingEverything)
{
    DoublyLinkedList<int> list;

    list.insertBack(1);
    list.insertBack(2);

    list.deleteBack();
    list.deleteBack();

    list.insertBack(100);

    EXPECT_EQ(list.size(),1);
    EXPECT_EQ(list.get(0),100);
}

TEST(DoublyDeleteBack, StressDeleteBack)
{
    DoublyLinkedList<int> list;

    for(int i=0;i<5000;i++)
        list.insertBack(i);

    while(list.size()>0)
        list.deleteBack();

    EXPECT_EQ(list.size(),0);
}