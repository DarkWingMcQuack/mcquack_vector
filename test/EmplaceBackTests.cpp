#include <cstddef>
#include <cstdint>
#include <gtest/gtest.h>
#include <string>
#include <valarray>

#define private public

#include <mcquack_vector/vector.hpp>


TEST(EmplaceBackTest, EmplaceBackSingleIntElement)
{
    mcquack::vector<int> vec;
    vec.emplace_back(1);

    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 1);
}

TEST(EmplaceBackTest, EmplaceBackSingleStrElement)
{
    using std::string_literals::operator""s;

    mcquack::vector<std::string> vec;
    vec.emplace_back("ads");

    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], "ads"s);
}

TEST(EmplaceBackTest, EmplaceBackMultipleIntElements)
{
    mcquack::vector<int> vec;
    for(int i = 0; i < 2; i++) {
        vec.emplace_back(i);
    }

    ASSERT_EQ(vec.size(), 2);
    for(int i = 0; i < 2; i++) {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(EmplaceBackTest, EmplaceBackMultipleStrElements)
{
    mcquack::vector<std::string> vec;
    for(int i = 0; i < 2; i++) {
        vec.emplace_back(std::to_string(i));
    }

    ASSERT_EQ(vec.size(), 2);
    for(int i = 0; i < 2; i++) {
        EXPECT_EQ(vec[i], std::to_string(i));
    }
}

TEST(EmplaceBackTest, EmplaceBackIntPastSmallCapacity)
{
    mcquack::vector<int> vec;
    for(size_t i = 0; i < mcquack::vector<int>::SMALL_CAPACITY + 12; i++) {
        vec.emplace_back(static_cast<int>(i));
    }

    ASSERT_EQ(vec.size(), mcquack::vector<int>::SMALL_CAPACITY + 12);
    for(size_t i = 0; i < mcquack::vector<int>::SMALL_CAPACITY + 12; i++) {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(EmplaceBackTest, EmplaceBackStrPastSmallCapacity)
{
    mcquack::vector<std::string> vec;
    for(size_t i = 0; i < mcquack::vector<int>::SMALL_CAPACITY + 12; i++) {
        vec.emplace_back(std::to_string(i));
    }

    ASSERT_EQ(vec.size(), mcquack::vector<int>::SMALL_CAPACITY + 12);
    for(size_t i = 0; i < mcquack::vector<int>::SMALL_CAPACITY + 12; i++) {
        EXPECT_EQ(vec[i], std::to_string(i));
    }
}

TEST(EmplaceBackTest, EmplaceBackIntPastHeapCapacity)
{
    mcquack::vector<int> vec;
    for(size_t i = 0; i < 20000; i++) {
        vec.emplace_back(static_cast<int>(i));
    }

    ASSERT_EQ(vec.size(), 20000);
    for(size_t i = 0; i < 20000; i++) {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(EmplaceBackTest, EmplaceBackStrPastHeapCapacity)
{
    mcquack::vector<std::string> vec;
    for(size_t i = 0; i < 20000; i++) {
        vec.emplace_back(std::to_string(i));
    }

    ASSERT_EQ(vec.size(), 20000);
    for(size_t i = 0; i < 20000; i++) {
        EXPECT_EQ(vec[i], std::to_string(i));
    }
}

TEST(EmplaceBackTest, EmplaceBackCopy)
{
    mcquack::vector<std::string> vec;
    std::string str = "Test String";
    vec.emplace_back(str);

    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], "Test String");
}

TEST(EmplaceBackTest, EmplaceBackConstruction)
{
    mcquack::vector<std::string> vec;
    vec.emplace_back("Test String");

    ASSERT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], "Test String");
}
