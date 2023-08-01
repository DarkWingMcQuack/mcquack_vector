#include <gtest/gtest.h>

#define private public

#include <mcquack_vector/vector.hpp>

// Test default constructor
TEST(CtorTest, DefaultConstructorInt)
{
    mcquack::vector<int> vec;
    EXPECT_TRUE(vec.empty());
}

TEST(CtorTest, DefaultConstructorString)
{
    mcquack::vector<std::string> vec;
    EXPECT_TRUE(vec.empty());
}

// Test constructor with size and default value
TEST(CtorTest, SizeValueConstructorInt)
{
    mcquack::vector<int> vec(5, 10);
    EXPECT_EQ(vec.size(), 5);
    for(int value : vec) {
        EXPECT_EQ(value, 10);
    }
}

TEST(CtorTest, SizeValueConstructorString)
{
    mcquack::vector<std::string> vec(3, "hello");
    EXPECT_EQ(vec.size(), 3);
    for(const auto& str : vec) {
        EXPECT_EQ(str, "hello");
    }
}

// Test constructor with size
TEST(CtorTest, SizeConstructorInt)
{
    mcquack::vector<int> vec(4);
    EXPECT_EQ(vec.size(), 4);
    for(int value : vec) {
        EXPECT_EQ(value, 0); // For int, the default value is 0
    }
}

TEST(CtorTest, SizeConstructorString)
{
    mcquack::vector<std::string> vec(2);
    EXPECT_EQ(vec.size(), 2);
    for(const auto& str : vec) {
        EXPECT_TRUE(str.empty()); // For std::string, the default value is an empty string
    }
}

// Test copy constructor
// TEST(CtorTest, CopyConstructorInt)
// {
//     mcquack::vector<int> vec1(3, 15);
//     mcquack::vector<int> vec2(vec1); // Copy constructor
//     EXPECT_EQ(vec2.size(), 3);
//     for(int value : vec2) {
//         EXPECT_EQ(value, 15);
//     }
// }

// TEST(CtorTest, CopyConstructorString)
// {
//     mcquack::vector<std::string> vec1(2, "world");
//     mcquack::vector<std::string> vec2(vec1); // Copy constructor
//     EXPECT_EQ(vec2.size(), 2);
//     for(const auto& str : vec2) {
//         EXPECT_EQ(str, "world");
//     }
// }
