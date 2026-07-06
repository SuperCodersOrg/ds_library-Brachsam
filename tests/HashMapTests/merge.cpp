#include "Linkedlist.h"
#include "hmap.h"
#include "Dynamicarray.h"
#include <gtest/gtest.h>
#include "exception.h"

TEST(HashMapMerge, EmptyIntoEmpty)
{
    HashMap<int,int> map1;
    HashMap<int,int> map2;

    map1.merge(map2);

    EXPECT_EQ(map1.size(),0);
}

TEST(HashMapMerge, MergeEmptyMap)
{
    HashMap<int,int> map1;
    HashMap<int,int> map2;

    map1.set(1,100);
    map1.set(2,200);

    map1.merge(map2);

    EXPECT_EQ(map1.size(),2);

    EXPECT_EQ(map1.get(1),100);
    EXPECT_EQ(map1.get(2),200);
}

TEST(HashMapMerge, MergeIntoEmptyMap)
{
    HashMap<int,int> map1;
    HashMap<int,int> map2;

    map2.set(10,100);
    map2.set(20,200);

    map1.merge(map2);

    EXPECT_EQ(map1.size(),2);

    EXPECT_EQ(map1.get(10),100);
    EXPECT_EQ(map1.get(20),200);
}

TEST(HashMapMerge, MergeDifferentKeys)
{
    HashMap<int,int> map1;
    HashMap<int,int> map2;

    map1.set(1,100);
    map1.set(2,200);

    map2.set(3,300);
    map2.set(4,400);

    map1.merge(map2);

    EXPECT_EQ(map1.size(),4);

    EXPECT_EQ(map1.get(1),100);
    EXPECT_EQ(map1.get(2),200);
    EXPECT_EQ(map1.get(3),300);
    EXPECT_EQ(map1.get(4),400);
}

TEST(HashMapMerge, MergeDuplicateKeys)
{
    HashMap<int,int> map1;
    HashMap<int,int> map2;

    map1.set(1,100);

    map2.set(1,999);

    map1.merge(map2);

    EXPECT_EQ(map1.size(),1);

    EXPECT_EQ(map1.get(1),100);
}

TEST(HashMapMerge, MergeAfterRehash)
{
    HashMap<int,int> map1;
    HashMap<int,int> map2;

    for(int i=0;i<50;i++)
        map1.set(i,i);

    for(int i=50;i<100;i++)
        map2.set(i,i);

    map1.merge(map2);

    EXPECT_EQ(map1.size(),100);

    for(int i=0;i<100;i++)
        EXPECT_EQ(map1.get(i),i);
}

TEST(HashMapMerge, MergeLargeMaps)
{
    HashMap<int,int> map1;
    HashMap<int,int> map2;

    for(int i=0;i<500;i++)
        map1.set(i,i);

    for(int i=500;i<1000;i++)
        map2.set(i,i);

    map1.merge(map2);

    EXPECT_EQ(map1.size(),1000);
}

TEST(HashMapMerge, MergeTwice)
{
    HashMap<int,int> map1;
    HashMap<int,int> map2;

    map2.set(1,100);
    map2.set(2,200);

    map1.merge(map2);
    map1.merge(map2);

    EXPECT_EQ(map1.size(),2);

    EXPECT_EQ(map1.get(1),100);
    EXPECT_EQ(map1.get(2),200);
}

TEST(HashMapMerge, MergeAfterClear)
{
    HashMap<int,int> map1;
    HashMap<int,int> map2;

    map1.set(1,100);
    map1.clear();

    map2.set(2,200);

    map1.merge(map2);

    EXPECT_EQ(map1.size(),1);

    EXPECT_EQ(map1.get(2),200);
}

TEST(HashMapMerge, StressMerge)
{
    HashMap<int,int> map1;
    HashMap<int,int> map2;

    for(int i=0;i<2500;i++)
        map1.set(i,i);

    for(int i=2500;i<5000;i++)
        map2.set(i,i);

    map1.merge(map2);

    EXPECT_EQ(map1.size(),5000);
}