#include "Linkedlist.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(SinglyCopyConstructor, CopyEmptyList)
{
    SinglyLinkedList<int> list;
    SinglyLinkedList<int> copy(list);
    EXPECT_EQ(copy.size(),0);
}

TEST(SinglyCopyConstructor, CopySingleElement)
{
    SinglyLinkedList<int> list;

    list.insertBack(10);

    SinglyLinkedList<int> copy(list);

    EXPECT_EQ(copy.size(),1);
    EXPECT_EQ(copy.get(0),10);
}

TEST(SinglyCopyConstructor, CopyMultipleElements)
{
    SinglyLinkedList<int> list;

    for(int i=1;i<=10;i++)
        list.insertBack(i);

    SinglyLinkedList<int> copy(list);

    EXPECT_EQ(copy.size(),10);

    for(int i=0;i<10;i++)
        EXPECT_EQ(copy.get(i),i+1);
}

TEST(SinglyCopyConstructor, ModifyOriginalAfterCopy)
{
    SinglyLinkedList<int> list;

    for(int i=1;i<=5;i++)
        list.insertBack(i);

    SinglyLinkedList<int> copy(list);

    list.remove(0);

    EXPECT_EQ(copy.size(),5);

    EXPECT_EQ(copy.get(0),1);
    EXPECT_EQ(copy.get(1),2);
    EXPECT_EQ(copy.get(2),3);
    EXPECT_EQ(copy.get(3),4);
    EXPECT_EQ(copy.get(4),5);
}

TEST(SinglyCopyConstructor, ModifyCopyOnly)
{
    SinglyLinkedList<int> list;

    for(int i=1;i<=5;i++)
        list.insertBack(i);

    SinglyLinkedList<int> copy(list);

    copy.remove(2);

    EXPECT_EQ(list.size(),5);
    EXPECT_EQ(copy.size(),4);

    EXPECT_EQ(list.get(2),3);
    EXPECT_EQ(copy.get(2),4);
}

TEST(SinglyCopyConstructor, CopyLargeList)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<1000;i++)
        list.insertBack(i);

    SinglyLinkedList<int> copy(list);

    EXPECT_EQ(copy.size(),1000);

    EXPECT_EQ(copy.get(0),0);
    EXPECT_EQ(copy.get(999),999);
}

TEST(SinglyCopyConstructor, CopyAfterClear)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<20;i++)
        list.insertBack(i);

    list.clear();

    SinglyLinkedList<int> copy(list);

    EXPECT_EQ(copy.size(),0);
}

TEST(SinglyCopyConstructor, MultipleCopies)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<10;i++)
        list.insertBack(i);

    SinglyLinkedList<int> copy1(list);
    SinglyLinkedList<int> copy2(copy1);

    EXPECT_EQ(copy2.size(),10);

    for(int i=0;i<10;i++)
        EXPECT_EQ(copy2.get(i),i);
}

