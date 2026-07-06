#include "hmap.h"
#include "Dynamicarray.h"
#include <gtest/gtest.h>
#include "Linkedlist.h"
#include "exception.h"

TEST(HashMapKeys, EmptyMap)
{
    HashMap<int,int> map;

    DynamicArray<int> keys = map.keys();

    EXPECT_EQ(keys.size(),0);
}

TEST(HashMapKeys, SingleKey)
{
    HashMap<int,int> map;

    map.set(10,100);

    DynamicArray<int> keys = map.keys();

    EXPECT_EQ(keys.size(),1);
    EXPECT_EQ(keys.get(0),10);
}

TEST(HashMapKeys, MultipleKeys)
{
    HashMap<int,int> map;

    for(int i=1;i<=5;i++)
        map.set(i,i*10);

    DynamicArray<int> keys = map.keys();

    EXPECT_EQ(keys.size(),5);

    for(int i=1;i<=5;i++)
        EXPECT_TRUE(map.exists(i));
}

TEST(HashMapKeys, KeysAfterRemove)
{
    HashMap<int,int> map;

    map.set(1,10);
    map.set(2,20);
    map.set(3,30);

    map.remove(2);

    DynamicArray<int> keys = map.keys();

    EXPECT_EQ(keys.size(),2);

    EXPECT_FALSE(map.exists(2));
    EXPECT_TRUE(map.exists(1));
    EXPECT_TRUE(map.exists(3));
}

TEST(HashMapKeys, KeysAfterClear)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i);

    map.clear();

    DynamicArray<int> keys = map.keys();

    EXPECT_EQ(keys.size(),0);
}

TEST(HashMapKeys, KeysAfterRehash)
{
    HashMap<int,int> map;

    for(int i=0;i<100;i++)
        map.set(i,i);

    DynamicArray<int> keys = map.keys();

    EXPECT_EQ(keys.size(),100);

    for(int i=0;i<100;i++)
        EXPECT_TRUE(map.exists(i));
}

TEST(HashMapKeys, MixedOperations)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i);

    map.remove(5);
    map.remove(10);

    map.set(100,100);

    DynamicArray<int> keys = map.keys();

    EXPECT_EQ(keys.size(),19);

    EXPECT_FALSE(map.exists(5));
    EXPECT_FALSE(map.exists(10));
    EXPECT_TRUE(map.exists(100));
}

TEST(HashMapKeys, StressKeys)
{
    HashMap<int,int> map;

    for(int i=0;i<5000;i++)
        map.set(i,i);

    DynamicArray<int> keys = map.keys();

    EXPECT_EQ(keys.size(),5000);
}

