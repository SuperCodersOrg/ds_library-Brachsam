#include "Linkedlist.h"
#include "hmap.h"
#include "Dynamicarray.h"
#include <gtest/gtest.h>
#include "exception.h"


TEST(HashMapValues, EmptyMap)
{
    HashMap<int,int> map;

    DynamicArray<int> values = map.values();

    EXPECT_EQ(values.size(),0);
}

TEST(HashMapValues, SingleValue)
{
    HashMap<int,int> map;

    map.set(10,100);

    DynamicArray<int> values = map.values();

    EXPECT_EQ(values.size(),1);
    EXPECT_EQ(values.get(0),100);
}

TEST(HashMapValues, MultipleValues)
{
    HashMap<int,int> map;

    for(int i=1;i<=5;i++)
        map.set(i,i*10);

    DynamicArray<int> values = map.values();

    EXPECT_EQ(values.size(),5);
}

TEST(HashMapValues, DuplicateValues)
{
    HashMap<int,int> map;

    map.set(1,100);
    map.set(2,100);
    map.set(3,100);

    DynamicArray<int> values = map.values();

    EXPECT_EQ(values.size(),3);
}

TEST(HashMapValues, ValuesAfterUpdate)
{
    HashMap<int,int> map;

    map.set(1,100);

    map.set(1,500);

    DynamicArray<int> values = map.values();

    EXPECT_EQ(values.size(),1);
    EXPECT_EQ(map.get(1),500);
}

TEST(HashMapValues, ValuesAfterRemove)
{
    HashMap<int,int> map;

    map.set(1,10);
    map.set(2,20);
    map.set(3,30);

    map.remove(2);

    DynamicArray<int> values = map.values();

    EXPECT_EQ(values.size(),2);

    EXPECT_FALSE(map.exists(2));
}

TEST(HashMapValues, ValuesAfterClear)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i);

    map.clear();

    DynamicArray<int> values = map.values();

    EXPECT_EQ(values.size(),0);
}

TEST(HashMapValues, ValuesAfterRehash)
{
    HashMap<int,int> map;

    for(int i=0;i<100;i++)
        map.set(i,i*10);

    DynamicArray<int> values = map.values();

    EXPECT_EQ(values.size(),100);

    for(int i=0;i<100;i++)
        EXPECT_EQ(map.get(i),i*10);
}

TEST(HashMapValues, MixedOperations)
{
    HashMap<int,int> map;

    for(int i=0;i<20;i++)
        map.set(i,i);

    map.remove(5);
    map.remove(10);

    map.set(100,1000);

    DynamicArray<int> values = map.values();

    EXPECT_EQ(values.size(),19);

    EXPECT_EQ(map.get(100),1000);
}

TEST(HashMapValues, StressValues)
{
    HashMap<int,int> map;

    for(int i=0;i<5000;i++)
        map.set(i,i*2);

    DynamicArray<int> values = map.values();

    EXPECT_EQ(values.size(),5000);
}

