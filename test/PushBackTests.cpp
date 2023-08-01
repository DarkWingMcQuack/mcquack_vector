#include <cstddef>
#include <cstdint>
#include <gtest/gtest.h>
#include <string>
#include <valarray>

#define private public

#include <mcquack_vector/vector.hpp>


TEST(PushBackTest, PushBackSingleIntElement)
{
    mcquack::vector<int> vec;
    vec.push_back(1);

    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 1);
}

TEST(PushBackTest, PushBackSingleStrElement)
{
    using std::string_literals::operator""s;

    mcquack::vector<std::string> vec;
    vec.push_back("ads");

    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], "ads"s);
}

TEST(PushBackTest, PushBackMultipleIntElements)
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

TEST(PushBackTest, PushBackMultipleStrElements)
{
    mcquack::vector<std::string> vec;
    for(int i = 0; i < 2; i++) {
        vec.push_back(std::to_string(i));
    }

    ASSERT_EQ(vec.size(), 2);
    for(int i = 0; i < 2; i++) {
        EXPECT_EQ(vec[i], std::to_string(i));
    }
}

TEST(PushBackTest, PushBackIntPastSmallCapacity)
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

TEST(PushBackTest, PushBackStrPastSmallCapacity)
{
    mcquack::vector<std::string> vec;
    for(size_t i = 0; i < mcquack::vector<int>::SMALL_CAPACITY + 12; i++) {
        vec.push_back(std::to_string(i));
    }

    ASSERT_EQ(vec.size(), mcquack::vector<int>::SMALL_CAPACITY + 12);
    for(size_t i = 0; i < mcquack::vector<int>::SMALL_CAPACITY + 12; i++) {
        EXPECT_EQ(vec[i], std::to_string(i));
    }
}

TEST(PushBackTest, PushBackIntPastHeapCapacity)
{
    mcquack::vector<int> vec;
    for(size_t i = 0; i < 20000; i++) {
        vec.push_back(static_cast<int>(i));
    }

    ASSERT_EQ(vec.size(), 20000);
    for(size_t i = 0; i < 20000; i++) {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(PushBackTest, PushBackStrPastHeapCapacity)
{
    mcquack::vector<std::string> vec;
    for(size_t i = 0; i < 20000; i++) {
        vec.push_back(std::to_string(i));
    }

    ASSERT_EQ(vec.size(), 20000);
    for(size_t i = 0; i < 20000; i++) {
        EXPECT_EQ(vec[i], std::to_string(i));
    }
}

TEST(PushBackTest, PushBackCopy)
{
    mcquack::vector<std::string> vec;
    std::string str = "Test String";
    vec.push_back(str);

    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], "Test String");
}

TEST(PushBackTest, PushBackMove)
{
    mcquack::vector<std::string> vec;
    vec.push_back(std::string("Test String"));

    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], "Test String");
}
