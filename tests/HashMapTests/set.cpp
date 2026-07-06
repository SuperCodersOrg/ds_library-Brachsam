#include "hmap.h"
#include "Dynamicarray.h"
#include <gtest/gtest.h>
#include "Linkedlist.h"
#include "exception.h"

TEST(HashMapSet, InsertSingleKey)
{
    HashMap<int,int> map;

    map.set(1,100);

    EXPECT_EQ(map.size(),1);
    EXPECT_EQ(map.get(1),100);
}

TEST(HashMapSet, InsertMultipleKeys)
{
    HashMap<int,int> map;

    for(int i=0;i<10;i++)
        map.set(i,i*10);

    EXPECT_EQ(map.size(),10);

    for(int i=0;i<10;i++)
        EXPECT_EQ(map.get(i),i*10);
}

TEST(HashMapSet, UpdateExistingKey)
{
    HashMap<int,int> map;

    map.set(10,100);
    map.set(10,200);

    EXPECT_EQ(map.size(),1);
    EXPECT_EQ(map.get(10),200);
}

TEST(HashMapSet, InsertNegativeKeys)
{
    HashMap<int,int> map;

    map.set(-1,100);
    map.set(-2,200);

    EXPECT_EQ(map.get(-1),100);
    EXPECT_EQ(map.get(-2),200);
}

TEST(HashMapSet, DuplicateValuesDifferentKeys)
{
    HashMap<int,int> map;

    map.set(1,500);
    map.set(2,500);
    map.set(3,500);

    EXPECT_EQ(map.size(),3);

    EXPECT_EQ(map.get(1),500);
    EXPECT_EQ(map.get(2),500);
    EXPECT_EQ(map.get(3),500);
}

TEST(HashMapSet, TriggerRehash)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i);

    EXPECT_GT(map.bucketCount,8);

    for(int i=0;i<20;i++)
        EXPECT_EQ(map.get(i),i);
}

TEST(HashMapSet, InsertAfterRehash)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i);

    map.set(100,500);

    EXPECT_EQ(map.get(100),500);
}

TEST(HashMapSet, SequentialInsertions)
{
    HashMap<int,int> map;

    for(int i=0;i<100;i++)
    {
        map.set(i,i);
        EXPECT_TRUE(map.exists(i));
    }

    EXPECT_EQ(map.size(),100);
}

TEST(HashMapSet, LargeInsertion)
{
    HashMap<int,int> map;

    for(int i=0;i<5000;i++)
        map.set(i,i*2);

    EXPECT_EQ(map.size(),5000);

    EXPECT_EQ(map.get(0),0);
    EXPECT_EQ(map.get(4999),9998);
}

TEST(HashMapSet, UpdateAfterRehash)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i);

    map.set(10,999);

    EXPECT_EQ(map.size(),20);
    EXPECT_EQ(map.get(10),999);
}

