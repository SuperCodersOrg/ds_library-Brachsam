#include "Linkedlist.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(SinglyAssignment, AssignEmptyList)
{
    SinglyLinkedList<int> list1;
    SinglyLinkedList<int> list2;

    list2 = list1;

    EXPECT_EQ(list2.size(),0);
}

TEST(SinglyAssignment, AssignSingleElement)
{
    SinglyLinkedList<int> list1;

    list1.insertBack(10);

    SinglyLinkedList<int> list2;

    list2 = list1;

    EXPECT_EQ(list2.size(),1);
    EXPECT_EQ(list2.get(0),10);
}

TEST(SinglyAssignment, AssignMultipleElements)
{
    SinglyLinkedList<int> list1;

    for(int i=1;i<=10;i++)
        list1.insertBack(i);

    SinglyLinkedList<int> list2;

    list2 = list1;

    EXPECT_EQ(list2.size(),10);

    for(int i=0;i<10;i++)
        EXPECT_EQ(list2.get(i),i+1);
}

TEST(SinglyAssignment, ModifyOriginalAfterAssignment)
{
    SinglyLinkedList<int> list1;

    for(int i=1;i<=5;i++)
        list1.insertBack(i);

    SinglyLinkedList<int> list2;

    list2 = list1;

    list1.remove(0);

    EXPECT_EQ(list2.size(),5);

    EXPECT_EQ(list2.get(0),1);
    EXPECT_EQ(list2.get(1),2);
    EXPECT_EQ(list2.get(2),3);
    EXPECT_EQ(list2.get(3),4);
    EXPECT_EQ(list2.get(4),5);
}

TEST(SinglyAssignment, ModifyAssignedList)
{
    SinglyLinkedList<int> list1;

    for(int i=1;i<=5;i++)
        list1.insertBack(i);

    SinglyLinkedList<int> list2;

    list2 = list1;

    list2.remove(2);

    EXPECT_EQ(list1.size(),5);
    EXPECT_EQ(list2.size(),4);

    EXPECT_EQ(list1.get(2),3);
    EXPECT_EQ(list2.get(2),4);
}

TEST(SinglyAssignment, SelfAssignment)
{
    SinglyLinkedList<int> list;

    for(int i=0;i<10;i++)
        list.insertBack(i);

    list = list;

    EXPECT_EQ(list.size(),10);

    for(int i=0;i<10;i++)
        EXPECT_EQ(list.get(i),i);
}

TEST(SinglyAssignment, AssignOverExistingList)
{
    SinglyLinkedList<int> list1;
    SinglyLinkedList<int> list2;

    for(int i=1;i<=5;i++)
        list1.insertBack(i);

    for(int i=100;i<=110;i++)
        list2.insertBack(i);

    list2 = list1;

    EXPECT_EQ(list2.size(),5);

    for(int i=0;i<5;i++)
        EXPECT_EQ(list2.get(i),i+1);
}

TEST(SinglyAssignment, LargeAssignment)
{
    SinglyLinkedList<int> list1;

    for(int i=0;i<1000;i++)
        list1.insertBack(i);

    SinglyLinkedList<int> list2;

    list2 = list1;

    EXPECT_EQ(list2.size(),1000);

    EXPECT_EQ(list2.get(0),0);
    EXPECT_EQ(list2.get(999),999);
}

TEST(SinglyAssignment, AssignmentAfterClear)
{
    SinglyLinkedList<int> list1;
    SinglyLinkedList<int> list2;

    for(int i=0;i<20;i++)
        list1.insertBack(i);

    list1.clear();

    list2 = list1;

    EXPECT_EQ(list2.size(),0);
}

