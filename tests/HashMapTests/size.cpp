#include "Linkedlist.h"
#include "hmap.h"
#include "Dynamicarray.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(HashMapSize, InitialSize)
{
    HashMap<int,int> map;
    EXPECT_EQ(map.size(),0);
}

TEST(HashMapSize, SizeAfterInsertions)
{
    HashMap<int,int> map;
    for(int i=0;i<20;i++)
    {
        map.set(i,i*10);
        EXPECT_EQ(map.size(),i+1);
    }
}

TEST(HashMapSize, UpdateExistingKey)
{
    HashMap<int,int> map;

    map.set(1,100);
    map.set(1,200);
    map.set(1,300);

    EXPECT_EQ(map.size(),1);
    EXPECT_EQ(map.get(1),300);
}

TEST(HashMapSize, SizeAfterRemove)
{
    HashMap<int,int> map;

    map.set(1,10);
    map.set(2,20);
    map.set(3,30);

    map.remove(2);

    EXPECT_EQ(map.size(),2);
}

TEST(HashMapSize, SizeAfterClear)
{
    HashMap<int,int> map;

    for(int i=0;i<50;i++)
        map.set(i,i);

    map.clear();

    EXPECT_EQ(map.size(),0);
}

TEST(HashMapSize, MixedOperations)
{
    HashMap<int,int> map;

    map.set(1,10);
    map.set(2,20);
    map.set(3,30);

    map.remove(2);

    map.set(4,40);
    map.set(5,50);

    map.set(1,100);

    EXPECT_EQ(map.size(),4);
}

TEST(HashMapSize, SizeAfterRehash)
{
    HashMap<int,int> map;

    for(int i=0;i<100;i++)
        map.set(i,i);

    EXPECT_EQ(map.size(),100);
}

TEST(HashMapSize, StressSizeUpdates)
{
    HashMap<int,int> map;

    for(int i=0;i<1000;i++)
        map.set(i,i);

    for(int i=0;i<500;i++)
        map.remove(i);

    EXPECT_EQ(map.size(),500);
}

