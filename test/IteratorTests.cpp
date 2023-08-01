#include <gtest/gtest.h>

#define private public

#include <mcquack_vector/vector.hpp>

TEST(IteratorTest, BeginEndInt)
{
    // Create a vector of ints
    mcquack::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // Test begin() and end()
    auto it = vec.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, vec.end());
}

TEST(IteratorTest, BeginEndString)
{
    // Create a vector of strings
    mcquack::vector<std::string> vec;
    vec.push_back("first");
    vec.push_back("second");
    vec.push_back("third");

    // Test begin() and end()
    auto it = vec.begin();
    EXPECT_EQ(*it, "first");
    ++it;
    EXPECT_EQ(*it, "second");
    ++it;
    EXPECT_EQ(*it, "third");
    ++it;
    EXPECT_EQ(it, vec.end());
}

TEST(IteratorTest, BeginEndEmpty)
{
    // Create an empty vector
    mcquack::vector<int> vec;

    // Test begin() and end() on empty vector
    EXPECT_EQ(vec.begin(), vec.end());
}

TEST(IteratorTest, RBeginREndInt)
{
    // Create a vector of ints
    mcquack::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // Test rbegin() and rend()
    auto it = vec.rbegin();
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(it, vec.rend());
}

TEST(IteratorTest, RBeginREndString)
{
    // Create a vector of strings
    mcquack::vector<std::string> vec;
    vec.push_back("first");
    vec.push_back("second");
    vec.push_back("third");

    // Test rbegin() and rend()
    auto it = vec.rbegin();
    EXPECT_EQ(*it, "third");
    ++it;
    EXPECT_EQ(*it, "second");
    ++it;
    EXPECT_EQ(*it, "first");
    ++it;
    EXPECT_EQ(it, vec.rend());
}

TEST(IteratorTest, RBeginREndEmpty)
{
    // Create an empty vector
    mcquack::vector<int> vec;

    // Test rbegin() and rend() on empty vector
    EXPECT_EQ(vec.rbegin(), vec.rend());
}

TEST(IteratorTest, RangeForInt)
{
    mcquack::vector<int> vec;
    for(int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }

    int counter = 0;
    for(int value : vec) {
        EXPECT_EQ(value, counter++);
    }
}

TEST(IteratorTest, RangeForString)
{
    mcquack::vector<std::string> vec;
    vec.push_back("first");
    vec.push_back("second");
    vec.push_back("third");

    std::string expected_values[] = {"first", "second", "third"};
    int counter = 0;
    for(const auto& value : vec) {
        EXPECT_EQ(value, expected_values[counter++]);
    }
}
