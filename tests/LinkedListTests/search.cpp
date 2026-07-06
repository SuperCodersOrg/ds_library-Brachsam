#include "LinkedList.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(SinglySearch, SearchInEmptyList)
{
    SinglyLinkedList<int> list;

    EXPECT_FALSE(list.search(10));
}

TEST(SinglySearch, SearchExistingElement)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    EXPECT_TRUE(list.search(10));
    EXPECT_TRUE(list.search(20));
    EXPECT_TRUE(list.search(30));
}

TEST(SinglySearch, SearchNonExistingElement)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    EXPECT_FALSE(list.search(100));
}

TEST(SinglySearch, SearchAfterDeletion)
{
    SinglyLinkedList<int> list;

    for(int i=1;i<=5;i++)
        list.insertBack(i);

    list.remove(2);

    EXPECT_FALSE(list.search(3));

    EXPECT_TRUE(list.search(1));
    EXPECT_TRUE(list.search(2));
    EXPECT_TRUE(list.search(4));
    EXPECT_TRUE(list.search(5));
}

TEST(SinglySearch, SearchDuplicateValues)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(20);
    list.insertBack(30);

    EXPECT_TRUE(list.search(20));
}

TEST(SinglySearch, SearchNegativeValues)
{
    SinglyLinkedList<int> list;

    list.insertBack(-10);
    list.insertBack(-20);

    EXPECT_TRUE(list.search(-10));
    EXPECT_TRUE(list.search(-20));
    EXPECT_FALSE(list.search(-30));
}

TEST(SinglySearch, SearchAfterClear)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<20;i++)
        list.insertBack(i);

    list.clear();

    EXPECT_EQ(list.size(),0);

    EXPECT_FALSE(list.search(10));
}

TEST(SinglySearch, StressSearch)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<1000;i++)
        list.insertBack(i);

    EXPECT_TRUE(list.search(999));
    EXPECT_TRUE(list.search(500));
    EXPECT_FALSE(list.search(1001));
}