#include <gtest/gtest.h>

#define private public

#include <mcquack_vector/vector.hpp>

using mcquack::vector;


TEST(SwapTest, SwapSmallVectors) {
    vector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    vector<int> vec2;
    vec2.push_back(4);
    vec2.push_back(5);
    vec2.push_back(6);

    vec1.swap(vec2);

    ASSERT_EQ(vec1.size(), 3);
    ASSERT_EQ(vec2.size(), 3);

    EXPECT_EQ(vec1[0], 4);
    EXPECT_EQ(vec1[1], 5);
    EXPECT_EQ(vec1[2], 6);

    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
    EXPECT_EQ(vec2[2], 3);
}

TEST(SwapTest, SwapLargeVectors) {
    vector<int> vec1;
    vector<int> vec2;

    for (int i = 0; i < 100; ++i) {
        vec1.push_back(i);
        vec2.push_back(100 - i);
    }

    vec1.swap(vec2);

    ASSERT_EQ(vec1.size(), 100);
    ASSERT_EQ(vec2.size(), 100);

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(vec1[i], 100 - i);
        EXPECT_EQ(vec2[i], i);
    }
}

TEST(SwapTest, SwapSmallAndLargeVectors) {
    vector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    vector<int> vec2;

    for (int i = 0; i < 100; ++i) {
        vec2.push_back(i);
    }

    vec1.swap(vec2);

    ASSERT_EQ(vec1.size(), 100);
    ASSERT_EQ(vec2.size(), 3);

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(vec1[i], i);
    }

    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
    EXPECT_EQ(vec2[2], 3);
}
TEST(SwapTest, SwapEmptyVectorSmallVector) {
    vector<int> vec1;

    vector<int> vec2;
    vec2.push_back(1);
    vec2.push_back(2);
    vec2.push_back(3);

    vec1.swap(vec2);

    ASSERT_EQ(vec1.size(), 3);
    ASSERT_EQ(vec2.size(), 0);

    EXPECT_EQ(vec1[0], 1);
    EXPECT_EQ(vec1[1], 2);
    EXPECT_EQ(vec1[2], 3);
}

TEST(SwapTest, SwapEmptyVectorLargeVector) {
    vector<int> vec1;

    vector<int> vec2;
    for (int i = 0; i < 100; ++i) {
        vec2.push_back(i);
    }

    vec1.swap(vec2);

    ASSERT_EQ(vec1.size(), 100);
    ASSERT_EQ(vec2.size(), 0);

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(vec1[i], i);
    }
}

TEST(SwapTest, StringVectorSwapSmallToSmall) {
    vector<std::string> vec1;
    vec1.push_back("A");

    vector<std::string> vec2;
    vec2.push_back("B");

    vec1.swap(vec2);

    ASSERT_EQ(vec1.size(), 1);
    EXPECT_EQ(vec1[0], "B");

    ASSERT_EQ(vec2.size(), 1);
    EXPECT_EQ(vec2[0], "A");
}

TEST(SwapTest, StringVectorSwapSmallToLarge) {
    vector<std::string> vec1;
    vec1.push_back("A");

    vector<std::string> vec2;
    for (int i = 0; i < 100; ++i) {
        vec2.push_back("B");
    }

    vec1.swap(vec2);

    ASSERT_EQ(vec1.size(), 100);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(vec1[i], "B");
    }

    ASSERT_EQ(vec2.size(), 1);
    EXPECT_EQ(vec2[0], "A");
}

TEST(SwapTest, StringVectorSwapLargeToLarge) {
    vector<std::string> vec1;
    for (int i = 0; i < 100; ++i) {
        vec1.push_back("A");
    }

    vector<std::string> vec2;
    for (int i = 0; i < 100; ++i) {
        vec2.push_back("B");
    }

    vec1.swap(vec2);

    ASSERT_EQ(vec1.size(), 100);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(vec1[i], "B");
    }

    ASSERT_EQ(vec2.size(), 100);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(vec2[i], "A");
    }
}
