#include <gtest/gtest.h>
#include "Linkedlist.h"
#include "exception.h"

TEST(SinglyConstructor, EmptyList)
{
    SinglyLinkedList<int> list;

    EXPECT_EQ(list.size(), 0);
}

TEST(SinglyConstructor, SearchInEmptyList)
{
    SinglyLinkedList<int> list;

    EXPECT_FALSE(list.search(10));
}

TEST(SinglyConstructor, GetFromEmptyList)
{
    SinglyLinkedList<int> list;

    EXPECT_THROW(
        list.get(0),
        LinkedListException
    );
}

TEST(SinglyConstructor, DeleteFrontFromEmptyList)
{
    SinglyLinkedList<int> list;

    EXPECT_THROW(
        list.deleteFront(),
        EmptyListException
    );
}

TEST(SinglyConstructor, DeleteBackFromEmptyList)
{
    SinglyLinkedList<int> list;

    EXPECT_THROW(
        list.deleteBack(),
        EmptyListException
    );
}

TEST(SinglyConstructor, RemoveFromEmptyList)
{
    SinglyLinkedList<int> list;

    EXPECT_THROW(
        list.remove(0),
        LinkedListException
    );
}