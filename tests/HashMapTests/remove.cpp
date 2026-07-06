#include "hmap.h"
#include "Dynamicarray.h"
#include <gtest/gtest.h>
#include "Linkedlist.h"
#include "exception.h"

TEST(HashMapRemove, RemoveExistingKey)
{
    HashMap<int,int> map;

    map.set(1,100);

    map.remove(1);

    EXPECT_EQ(map.size(),0);
    EXPECT_FALSE(map.exists(1));
}

TEST(HashMapRemove, RemoveMultipleKeys)
{
    HashMap<int,int> map;

    for(int i=0;i<10;i++)
        map.set(i,i);

    for(int i=0;i<10;i++)
        map.remove(i);

    EXPECT_EQ(map.size(),0);
}

TEST(HashMapRemove, RemoveMiddleKey)
{
    HashMap<int,int> map;

    map.set(10,100);
    map.set(20,200);
    map.set(30,300);

    map.remove(20);

    EXPECT_EQ(map.size(),2);

    EXPECT_FALSE(map.exists(20));

    EXPECT_EQ(map.get(10),100);
    EXPECT_EQ(map.get(30),300);
}

TEST(HashMapRemove, RemoveMissingKey)
{
    HashMap<int,int> map;

    map.set(1,100);

    EXPECT_THROW(
        map.remove(5),
        KeyNotFoundException
    );
}

TEST(HashMapRemove, RemoveFromEmptyMap)
{
    HashMap<int,int> map;

    EXPECT_THROW(
        map.remove(1),
        KeyNotFoundException
    );
}

TEST(HashMapRemove, RemoveAfterRehash)
{
    HashMap<int,int> map;

    for(int i=0;i<50;i++)
        map.set(i,i);

    map.remove(25);

    EXPECT_FALSE(map.exists(25));

    EXPECT_EQ(map.size(),49);
}

TEST(HashMapRemove, RemoveThenInsertAgain)
{
    HashMap<int,int> map;

    map.set(10,100);

    map.remove(10);

    map.set(10,500);

    EXPECT_EQ(map.size(),1);
    EXPECT_EQ(map.get(10),500);
}

TEST(HashMapRemove, RemoveAllKeys)
{
    HashMap<int,int> map;

    for(int i=0;i<100;i++)
        map.set(i,i);

    for(int i=0;i<100;i++)
        map.remove(i);

    EXPECT_EQ(map.size(),0);
}

TEST(HashMapRemove, MixedOperations)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i);

    map.remove(5);
    map.remove(10);

    map.set(100,1000);

    EXPECT_EQ(map.size(),19);

    EXPECT_TRUE(map.exists(100));

    EXPECT_FALSE(map.exists(5));
    EXPECT_FALSE(map.exists(10));
}

TEST(HashMapRemove, StressRemove)
{
    HashMap<int,int> map;

    for(int i=0;i<1000;i++)
        map.set(i,i);

    for(int i=0;i<1000;i++)
        map.remove(i);

    EXPECT_EQ(map.size(),0);
}