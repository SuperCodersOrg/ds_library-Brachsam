#include "Linkedlist.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(DoublyRemoveVal, RemoveHead)
{
    DoublyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    EXPECT_TRUE(list.removeVal(10));

    EXPECT_EQ(list.size(),2);
    EXPECT_EQ(list.get(0),20);
    EXPECT_EQ(list.get(1),30);
}

TEST(DoublyRemoveVal, RemoveTail)
{
    DoublyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    EXPECT_TRUE(list.removeVal(30));

    EXPECT_EQ(list.size(),2);

    EXPECT_EQ(list.get(0),10);
    EXPECT_EQ(list.get(1),20);
}

TEST(DoublyRemoveVal, RemoveMiddle)
{
    DoublyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    EXPECT_TRUE(list.removeVal(20));

    EXPECT_EQ(list.size(),2);

    EXPECT_EQ(list.get(0),10);
    EXPECT_EQ(list.get(1),30);
}

TEST(DoublyRemoveVal, RemoveDuplicateValues)
{
    DoublyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(20);
    list.insertBack(30);

    EXPECT_TRUE(list.removeVal(20));

    EXPECT_EQ(list.size(),3);

    EXPECT_EQ(list.get(0),10);
    EXPECT_EQ(list.get(1),20);
    EXPECT_EQ(list.get(2),30);
}

TEST(DoublyRemoveVal, RemoveValueNotPresent)
{
    DoublyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);

    EXPECT_FALSE(list.removeVal(100));

    EXPECT_EQ(list.size(),2);
}

TEST(DoublyRemoveVal, RemoveFromEmptyList)
{
    DoublyLinkedList<int> list;

    EXPECT_FALSE(list.removeVal(10));

    EXPECT_EQ(list.size(),0);
}

TEST(DoublyRemoveVal, RemoveEveryElement)
{
    DoublyLinkedList<int> list;

    for(int i=1;i<=10;i++)
        list.insertBack(i);

    for(int i=1;i<=10;i++)
        EXPECT_TRUE(list.removeVal(i));

    EXPECT_EQ(list.size(),0);
}

TEST(DoublyRemoveVal, RemoveAfterMixedOperations)
{
    DoublyLinkedList<int> list;

    for(int i=1;i<=10;i++)
        list.insertBack(i);

    list.insert(5,100);
    list.deleteFront();
    list.deleteBack();

    EXPECT_TRUE(list.removeVal(100));

    EXPECT_EQ(list.size(),8);

    EXPECT_FALSE(list.search(100));
}

TEST(DoublyRemoveVal, StressRemoveVal)
{
    DoublyLinkedList<int> list;

    for(int i=0;i<1000;i++)
        list.insertBack(i);

    for(int i=0;i<500;i++)
        EXPECT_TRUE(list.removeVal(i));

    EXPECT_EQ(list.size(),500);

    EXPECT_EQ(list.get(0),500);
}

