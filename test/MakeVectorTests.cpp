#include <gtest/gtest.h>

#define private public

#include <mcquack_vector/vector.hpp>

TEST(MakeVectorTest, Int)
{
    auto vec = mcquack::make_vector(1, 2, 3, 4, 5);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
}

TEST(MakeVectorTest, String)
{
    auto vec = mcquack::make_vector(std::string("Hello"), std::string("World"));
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], "Hello");
    EXPECT_EQ(vec[1], "World");
}
