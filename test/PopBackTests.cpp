#include <gtest/gtest.h>

#define private public

#include <mcquack_vector/vector.hpp>

TEST(PopBAckTest, PopBackInt)
{
    // Create a vector of ints
    mcquack::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // Test pop_back()
    vec.pop_back();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.back(), 2);
}

TEST(PopBAckTest, PopBackString)
{
    // Create a vector of strings
    mcquack::vector<std::string> vec;
    vec.push_back("first");
    vec.push_back("second");
    vec.push_back("third");

    // Test pop_back()
    vec.pop_back();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.back(), "second");
}

TEST(PopBAckTest, PopBackUntilEmpty)
{
    // Create a vector of ints
    mcquack::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // Test popping back until empty
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    EXPECT_TRUE(vec.empty());
}

TEST(PopBackTest, PopBackAndBackInt)
{
    // Create a vector of ints
    mcquack::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // Test pop_back() and back()
    vec.pop_back();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.back(), 2);

    vec.pop_back();
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.back(), 1);
}

TEST(PopBackTest, PopBackAndBackString)
{
    // Create a vector of strings
    mcquack::vector<std::string> vec;
    vec.push_back("first");
    vec.push_back("second");
    vec.push_back("third");

    // Test pop_back() and back()
    vec.pop_back();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.back(), "second");

    vec.pop_back();
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.back(), "first");
}

TEST(PopBackTest, PopBackUntilEmptyAndBack)
{
    // Create a vector of ints
    mcquack::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // Test popping back until one element left and back()
    vec.pop_back();
    vec.pop_back();
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.back(), 1);

    // Test pop_back on the last element
    vec.pop_back();
    EXPECT_TRUE(vec.empty());
    // Here we do not call vec.back() as it would be undefined behavior on an empty vector
}
