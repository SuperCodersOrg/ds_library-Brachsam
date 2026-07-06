#include "hmap.h"
#include "Dynamicarray.h"
#include <gtest/gtest.h>
#include "Linkedlist.h"
#include "exception.h"

TEST(HashMapLoadFactor, InitialLoadFactor)
{
    HashMap<int,int> map;

    EXPECT_FLOAT_EQ(map.loadFactor(),0.0f);
}

TEST(HashMapLoadFactor, OneInsertion)
{
    HashMap<int,int> map;

    map.set(1,100);

    EXPECT_FLOAT_EQ(map.loadFactor(),1.0f/8.0f);
}

TEST(HashMapLoadFactor, MultipleInsertions)
{
    HashMap<int,int> map;

    for(int i=0;i<4;i++)
        map.set(i,i);

    EXPECT_FLOAT_EQ(map.loadFactor(),4.0f/8.0f);
}

TEST(HashMapLoadFactor, UpdateExistingKey)
{
    HashMap<int,int> map;

    map.set(1,100);

    float before = map.loadFactor();

    map.set(1,200);

    EXPECT_FLOAT_EQ(map.loadFactor(),before);
}

TEST(HashMapLoadFactor, LoadFactorAfterRemove)
{
    HashMap<int,int> map;

    map.set(1,10);
    map.set(2,20);

    map.remove(1);

    EXPECT_FLOAT_EQ(map.loadFactor(),1.0f/8.0f);
}

TEST(HashMapLoadFactor, LoadFactorAfterClear)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i);

    map.clear();

    EXPECT_FLOAT_EQ(map.loadFactor(),0.0f);
}

TEST(HashMapLoadFactor, LoadFactorAfterRehash)
{
    HashMap<int,int> map;

    for(int i=0;i<6;i++)
        map.set(i,i);

    EXPECT_LT(map.loadFactor(),0.7f);
}

TEST(HashMapLoadFactor, StressLoadFactor)
{
    HashMap<int,int> map;

    for(int i=0;i<500;i++)
        map.set(i,i);

    EXPECT_LT(map.loadFactor(),0.7f);
}

