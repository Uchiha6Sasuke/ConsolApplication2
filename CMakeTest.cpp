#include <iostream>
#include <gtest/gtest.h>
#include "hashtable.h"
class HashTableTest : public testing::Test{
protected:
    void SetUp() override{
        d1.insert("Dasha", {.age = 19, .weight = 50});
        d1.insert("Vova", {.age = 19, .weight = 62});
        d2.insert("Alyona", {.age = 19, .weight = 55});
        d2.insert("Vitalya", {.age = 18, .weight = 75});
        d2.insert("Moks", {.age = 19, .weight = 65});
    }
    HashTable d0;
    HashTable d1;
    HashTable d2;
};
TEST_F(HashTableTest, SwapTest){
    d1.swap(d2);
    EXPECT_EQ(d1.size(), 3);
    EXPECT_EQ(d2.size(), 2);
    EXPECT_EQ(d2["Vova"].weight, 62);
}
TEST_F(HashTableTest, EraseTest){
    bool r = d2.erase("Alyona");
    EXPECT_EQ(r, true);
}
TEST_F(HashTableTest, EmptyTest){
    bool r = d1.empty();
    EXPECT_EQ(r, false);
    r = d0.empty();
    EXPECT_EQ(r, true);
}
TEST_F(HashTableTest, ContainsTest){
    bool r = d1.contains("Dasha");
    EXPECT_EQ(r, true);
    r = d1.contains("Sanya");
    EXPECT_EQ(r, false);
}
TEST_F(HashTableTest, AtTest){
    Value& x = d1.at("Dasha");
    EXPECT_EQ(x.weight, 50);
    ASSERT_ANY_THROW(d1.at("testing"));
}
TEST_F(HashTableTest, OperatorTest){
    bool r1 = d1 == d2;
    EXPECT_EQ(r1, false);
    bool r2 = d1 != d2;
    EXPECT_EQ(r2, true);
    unsigned int r3 = d2["Vitalya"].weight;
    EXPECT_EQ(r3, 70);
    d1 = d2;
    r1 = d1 == d2;
    EXPECT_EQ(r1, true);
}
TEST_F(HashTableTest, CopyTest){
    HashTable d3 = d1;
    EXPECT_EQ(d3.size(), 2);
    bool r0 = d3.contains("Vova");
    EXPECT_EQ(r0, true);
    bool r2 = d3.contains("Alyona");
    EXPECT_EQ(r2, false);
}
TEST_F(HashTableTest, MoveTest){
    HashTable d4 = std::move(d2);
    bool r0 = d4.contains("Alyona");
    bool r1 = d4.contains("Vitalya");
    bool r2 = d4.contains("Moks");
    bool r3 = d4.empty();
    EXPECT_EQ(r0, true);
    EXPECT_EQ(r1, true);
    EXPECT_EQ(r2, true);
    EXPECT_EQ(r3, true);
}