#include "hmap.h"
#include "Dynamicarray.h"
#include <gtest/gtest.h>
#include "Linkedlist.h"
#include "exception.h"

TEST(HashMapClear, ClearEmptyMap)
{
    HashMap<int,int> map;

    map.clear();

    EXPECT_EQ(map.size(),0);
}

TEST(HashMapClear, ClearSingleElement)
{
    HashMap<int,int> map;

    map.set(1,100);

    map.clear();

    EXPECT_EQ(map.size(),0);
    EXPECT_FALSE(map.exists(1));
}

TEST(HashMapClear, ClearMultipleElements)
{
    HashMap<int,int> map;

    for(int i=0;i<100;i++)
        map.set(i,i);

    map.clear();

    EXPECT_EQ(map.size(),0);

    for(int i=0;i<100;i++)
        EXPECT_FALSE(map.exists(i));
}

TEST(HashMapClear, ReuseAfterClear)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i);

    map.clear();

    map.set(100,500);

    EXPECT_EQ(map.size(),1);

    EXPECT_TRUE(map.exists(100));
    EXPECT_EQ(map.get(100),500);
}

TEST(HashMapClear, ClearMultipleTimes)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i);

    map.clear();
    map.clear();
    map.clear();

    EXPECT_EQ(map.size(),0);
}

TEST(HashMapClear, ClearAfterRehash)
{
    HashMap<int,int> map;

    for(int i=0;i<100;i++)
        map.set(i,i);

    map.clear();

    EXPECT_EQ(map.size(),0);

    EXPECT_FALSE(map.exists(50));
}

TEST(HashMapClear, MixedOperationsThenClear)
{
    HashMap<int,int> map;

    for(int i=0;i<30;i++)
        map.set(i,i);

    map.remove(5);
    map.remove(10);

    map.set(100,1000);

    map.clear();

    EXPECT_EQ(map.size(),0);

    EXPECT_FALSE(map.exists(100));
}

TEST(HashMapClear, StressClear)
{
    HashMap<int,int> map;

    for(int i=0;i<5000;i++)
        map.set(i,i);

    map.clear();

    EXPECT_EQ(map.size(),0);
}

