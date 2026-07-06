#include "LinkedList.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(SinglyClear, ClearEmptyList)
{
    SinglyLinkedList<int> list;
    list.clear();
    EXPECT_EQ(list.size(),0);
}

TEST(SinglyClear, ClearSingleElement)
{
    SinglyLinkedList<int> list;
    list.insertBack(10);
    list.clear();
    EXPECT_EQ(list.size(),0);
    EXPECT_FALSE(list.search(10));
}

TEST(SinglyClear, ClearMultipleElements)
{
    SinglyLinkedList<int> list;
    for(int i=0;i<100;i++)
        list.insertBack(i);

    list.clear();
    EXPECT_EQ(list.size(),0);
    EXPECT_FALSE(list.search(50));
}

TEST(SinglyClear, ReuseAfterClear)
{
    SinglyLinkedList<int> list;
    for(int i=0;i<20;i++)
        list.insertBack(i);

    list.clear();
    list.insertBack(100);
    EXPECT_EQ(list.size(),1);
    EXPECT_EQ(list.get(0),100);
}

TEST(SinglyClear, ClearMultipleTimes)
{
    SinglyLinkedList<int> list;
    for(int i=0;i<10;i++)
        list.insertBack(i);

    list.clear();
    list.clear();
    list.clear();
    EXPECT_EQ(list.size(),0);
}

TEST(SinglyClear, ClearAfterMixedOperations)
{
    SinglyLinkedList<int> list;
    for(int i=1;i<=20;i++)
        list.insertBack(i);

    list.deleteFront();
    list.deleteBack();
    list.remove(5);
    list.clear();
    EXPECT_EQ(list.size(),0);
}

TEST(SinglyClear, StressClear)
{
    SinglyLinkedList<int> list;
    for(int i=0;i<5000;i++)
        list.insertBack(i);

    list.clear();
    EXPECT_EQ(list.size(),0);
}

TEST(SinglyClear, SearchAfterClear)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    list.clear();

    EXPECT_FALSE(list.search(10));
    EXPECT_FALSE(list.search(20));
    EXPECT_FALSE(list.search(30));
}