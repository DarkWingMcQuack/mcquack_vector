#include <cstddef>
#include <cstdio>
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
    for(std::size_t i = 0; i < 1000; i++) {
        mcquack::vector<int> vec(i, 10);
        EXPECT_EQ(vec.size(), i);
        for(int value : vec) {
            EXPECT_EQ(value, 10);
        }
    }
}

TEST(CtorTest, SizeValueConstructorString)
{

    for(std::size_t i = 0; i < 1000; i++) {
        mcquack::vector<std::string> vec(i, "hello");
        EXPECT_EQ(vec.size(), i);
        for(const auto& str : vec) {
            EXPECT_EQ(str, "hello");
        }
    }
}

// Test constructor with size
TEST(CtorTest, SizeConstructorInt)
{
    for(std::size_t i = 0; i < 1000; i++) {
        mcquack::vector<int> vec(i);
        EXPECT_EQ(vec.size(), i);
        for(int value : vec) {
            EXPECT_EQ(value, 0); // For int, the default value is 0
        }
    }
}

TEST(CtorTest, SizeConstructorString)
{
    for(std::size_t i = 0; i < 1000; i++) {
        mcquack::vector<std::string> vec(i);
        EXPECT_EQ(vec.size(), i);
        for(const auto& str : vec) {
            EXPECT_EQ(str, "");
        }
    }
}

// Test copy constructor
TEST(CtorTest, CopyConstructorInt)
{
    mcquack::vector<int> vec1(3, 15);
    mcquack::vector<int> vec2(vec1); // Copy constructor
    EXPECT_EQ(vec2.size(), 3);
    for(int value : vec2) {
        EXPECT_EQ(value, 15);
    }
}

TEST(CtorTest, CopyConstructorString)
{
    mcquack::vector<std::string> vec1(2, "world");
    mcquack::vector<std::string> vec2(vec1); // Copy constructor
    EXPECT_EQ(vec2.size(), 2);
    for(const auto& str : vec2) {
        EXPECT_EQ(str, "world");
    }
}

TEST(VectorTests, StringVectorInitializerListCtor)
{
    mcquack::vector<std::string> vec{"a", "b", "c"};

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], "a");
    EXPECT_EQ(vec[1], "b");
    EXPECT_EQ(vec[2], "c");
}

TEST(VectorTests, IntVectorInitializerListCtor)
{
    mcquack::vector<int> vec{1, 2, 3};

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

TEST(VectorTests, EmptyStringVectorInitializerListCtor)
{
    mcquack::vector<std::string> vec{};

    EXPECT_TRUE(vec.empty());
}

TEST(VectorTests, EmptyIntVectorInitializerListCtor)
{
    mcquack::vector<int> vec{};

    EXPECT_TRUE(vec.empty());
}
