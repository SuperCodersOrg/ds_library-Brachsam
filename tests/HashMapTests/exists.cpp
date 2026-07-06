#include "hmap.h"
#include "Dynamicarray.h"
#include <gtest/gtest.h>
#include "Linkedlist.h"
#include "exception.h"

TEST(HashMapExists, ExistingKey)
{
    HashMap<int,int> map;
    map.set(1,100);
    EXPECT_TRUE(map.exists(1));
}

TEST(HashMapExists, MissingKey)
{
    HashMap<int,int> map;
    map.set(1,100);
    EXPECT_FALSE(map.exists(2));
}

TEST(HashMapExists, ExistsAfterUpdate)
{
    HashMap<int,int> map;
    map.set(5,100);
    map.set(5,500);
    EXPECT_TRUE(map.exists(5));
}

TEST(HashMapExists, ExistsAfterRemove)
{
    HashMap<int,int> map;
    map.set(1,100);
    map.remove(1);
    EXPECT_FALSE(map.exists(1));
}

TEST(HashMapExists, ExistsAfterClear)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i);

    map.clear();

    for(int i=0;i<20;i++)
        EXPECT_FALSE(map.exists(i));
}

TEST(HashMapExists, ExistsAfterRehash)
{
    HashMap<int,int> map;

    for(int i=0;i<100;i++)
        map.set(i,i);

    for(int i=0;i<100;i++)
        EXPECT_TRUE(map.exists(i));
}

TEST(HashMapExists, NegativeKeys)
{
    HashMap<int,int> map;

    map.set(-10,100);
    map.set(-20,200);

    EXPECT_TRUE(map.exists(-10));
    EXPECT_TRUE(map.exists(-20));
    EXPECT_FALSE(map.exists(-30));
}

TEST(HashMapExists, StressExists)
{
    HashMap<int,int> map;

    for(int i=0;i<5000;i++)
        map.set(i,i);

    for(int i=0;i<5000;i++)
        EXPECT_TRUE(map.exists(i));

    EXPECT_FALSE(map.exists(10000));
}

TEST(HashMapExists, MixedOperations)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i);

    map.remove(5);
    map.remove(10);

    map.set(25,250);

    EXPECT_TRUE(map.exists(25));
    EXPECT_TRUE(map.exists(15));

    EXPECT_FALSE(map.exists(5));
    EXPECT_FALSE(map.exists(10));
}