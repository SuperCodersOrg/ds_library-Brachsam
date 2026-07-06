#include "Linkedlist.h"
#include "hmap.h"
#include "Dynamicarray.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(HashMapConstructor, EmptyHashMap)
{
    HashMap<int,int> map;
    EXPECT_EQ(map.size(),0);
    EXPECT_EQ(map.bucketCount,8);
}

TEST(HashMapConstructor, InitialLoadFactor)
{
    HashMap<int,int> map;
    EXPECT_FLOAT_EQ(map.loadFactor(),0.0f);
}

TEST(HashMapConstructor, EmptyKeys)
{
    HashMap<int,int> map;
    DynamicArray<int> keys = map.keys();
    EXPECT_EQ(keys.size(),0);
}

TEST(HashMapConstructor, EmptyValues)
{
    HashMap<int,int> map;
    DynamicArray<int> values = map.values();
    EXPECT_EQ(values.size(),0);
}

TEST(HashMapConstructor, ExistsInEmptyMap)
{
    HashMap<int,int> map;
    EXPECT_FALSE(map.exists(10));
}

TEST(HashMapConstructor, GetFromEmptyMap)
{
    HashMap<int,int> map;
    EXPECT_THROW(
        map.get(10),
        KeyNotFoundException
    );
}

TEST(HashMapConstructor, RemoveFromEmptyMap)
{
    HashMap<int,int> map;
    EXPECT_THROW(
        map.remove(10),
        KeyNotFoundException
    );
}