#include <gtest/gtest.h>

#define private public

#include <mcquack_vector/vector.hpp>


TEST(FrontTest, FrontInt)
{
    // Create a vector of ints
    mcquack::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // Test front()
    EXPECT_EQ(vec.front(), 1);
}

TEST(FrontTest, FrontString)
{
    // Create a vector of strings
    mcquack::vector<std::string> vec;
    vec.push_back("first");
    vec.push_back("second");
    vec.push_back("third");

    // Test front()
    EXPECT_EQ(vec.front(), "first");
}
