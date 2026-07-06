#include "hmap.h"
#include "Dynamicarray.h"
#include <gtest/gtest.h>
#include "Linkedlist.h"
#include "exception.h"

TEST(HashMapGet, GetExistingKey)
{
    HashMap<int,int> map;

    map.set(1,100);

    EXPECT_EQ(map.get(1),100);
}

TEST(HashMapGet, GetMultipleKeys)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i*10);

    for(int i=0;i<20;i++)
        EXPECT_EQ(map.get(i),i*10);
}

TEST(HashMapGet, GetUpdatedValue)
{
    HashMap<int,int> map;

    map.set(5,100);
    map.set(5,500);

    EXPECT_EQ(map.get(5),500);
}

TEST(HashMapGet, GetAfterRemove)
{
    HashMap<int,int> map;

    map.set(1,100);

    map.remove(1);

    EXPECT_THROW(
        map.get(1),
        KeyNotFoundException
    );
}

TEST(HashMapGet, GetMissingKey)
{
    HashMap<int,int> map;

    EXPECT_THROW(
        map.get(100),
        KeyNotFoundException
    );
}

TEST(HashMapGet, GetAfterClear)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i);

    map.clear();

    EXPECT_THROW(
        map.get(10),
        KeyNotFoundException
    );
}

TEST(HashMapGet, GetAfterRehash)
{
    HashMap<int,int> map;

    for(int i=0;i<50;i++)
        map.set(i,i*2);

    for(int i=0;i<50;i++)
        EXPECT_EQ(map.get(i),i*2);
}

TEST(HashMapGet, GetNegativeKey)
{
    HashMap<int,int> map;

    map.set(-10,500);

    EXPECT_EQ(map.get(-10),500);
}

TEST(HashMapGet, StressGet)
{
    HashMap<int,int> map;

    for(int i=0;i<5000;i++)
        map.set(i,i);

    for(int i=0;i<5000;i++)
        EXPECT_EQ(map.get(i),i);
}

TEST(HashMapGet, GetAfterMixedOperations)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i);

    map.remove(5);
    map.remove(10);

    map.set(25,250);
    map.set(30,300);

    EXPECT_EQ(map.get(0),0);
    EXPECT_EQ(map.get(25),250);
    EXPECT_EQ(map.get(30),300);

    EXPECT_THROW(
        map.get(5),
        KeyNotFoundException
    );
}