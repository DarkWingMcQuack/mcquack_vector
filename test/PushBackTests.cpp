#include <cstddef>
#include <cstdint>
#include <gtest/gtest.h>

#define private public

#include <mcquack_vector/vector.hpp>


TEST(VectorTest, PushBackSingleElement)
{
    mcquack::vector<int> vec;
    vec.push_back(1);

    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 1);
}

TEST(VectorTest, PushBackMultipleElements)
{
    mcquack::vector<int> vec;
    for(int i = 0; i < 2; i++) {
        vec.push_back(i);
    }

    ASSERT_EQ(vec.size(), 2);
    for(int i = 0; i < 2; i++) {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(VectorTest, PushBackPastSmallCapacity)
{
    mcquack::vector<int> vec;
    for(size_t i = 0; i < mcquack::vector<int>::SMALL_CAPACITY + 12; i++) {
        vec.push_back(static_cast<int>(i));
    }

    ASSERT_EQ(vec.size(), mcquack::vector<int>::SMALL_CAPACITY + 12);
    for(size_t i = 0; i < mcquack::vector<int>::SMALL_CAPACITY + 12; i++) {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(VectorTest, PushBackCopy)
{
    mcquack::vector<std::string> vec;
    std::string str = "Test String";
    vec.push_back(str);

    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], "Test String");
}

TEST(VectorTest, PushBackMove)
{
    mcquack::vector<std::string> vec;
    vec.push_back(std::string("Test String"));

    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], "Test String");
}

TEST(VectorTest, AllElementSizes)
{
    mcquack::vector<std::array<std::uint8_t, 0>> vec0;
    mcquack::vector<std::array<std::uint8_t, 1>> vec1;
    mcquack::vector<std::array<std::uint8_t, 2>> vec2;
    mcquack::vector<std::array<std::uint8_t, 3>> vec3;
    mcquack::vector<std::array<std::uint8_t, 4>> vec4;
    mcquack::vector<std::array<std::uint8_t, 5>> vec5;
    mcquack::vector<std::array<std::uint8_t, 6>> vec6;
    mcquack::vector<std::array<std::uint8_t, 7>> vec7;
    mcquack::vector<std::array<std::uint8_t, 8>> vec8;
    mcquack::vector<std::array<std::uint8_t, 9>> vec9;
    mcquack::vector<std::array<std::uint8_t, 10>> vec10;
    mcquack::vector<std::array<std::uint8_t, 11>> vec11;
    mcquack::vector<std::array<std::uint8_t, 12>> vec12;
    mcquack::vector<std::array<std::uint8_t, 13>> vec13;
    mcquack::vector<std::array<std::uint8_t, 14>> vec14;
    mcquack::vector<std::array<std::uint8_t, 15>> vec15;
    mcquack::vector<std::array<std::uint8_t, 16>> vec16;
    mcquack::vector<std::array<std::uint8_t, 17>> vec17;
    mcquack::vector<std::array<std::uint8_t, 18>> vec18;
    mcquack::vector<std::array<std::uint8_t, 19>> vec19;
    mcquack::vector<std::array<std::uint8_t, 20>> vec20;
    mcquack::vector<std::array<std::uint8_t, 21>> vec21;
    mcquack::vector<std::array<std::uint8_t, 22>> vec22;
    mcquack::vector<std::array<std::uint8_t, 23>> vec23;
    mcquack::vector<std::array<std::uint8_t, 24>> vec24;
    mcquack::vector<std::array<std::uint8_t, 25>> vec25;
}
