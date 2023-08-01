#include <cstddef>
#include <cstdint>
#include <gtest/gtest.h>
#include <string>
#include <valarray>

#define private public

#include <mcquack_vector/vector.hpp>

// Test for non-const data() method
TEST(DataTest, DataMethodNonConst)
{
    mcquack::vector<int> int_vec;

    // Add some elements to the vector
    int_vec.push_back(1);
    int_vec.push_back(2);
    int_vec.push_back(3);

    // Test
    int* data_ptr = int_vec.data();
    ASSERT_NE(data_ptr, nullptr) << "Data pointer shouldn't be null";
    EXPECT_EQ(data_ptr[0], 1) << "First element should be 1";
    EXPECT_EQ(data_ptr[1], 2) << "Second element should be 2";
    EXPECT_EQ(data_ptr[2], 3) << "Third element should be 3";
}

// Test for const data() method
TEST(DataTest, DataMethodConst)
{
    mcquack::vector<int> int_vec;

    // Add some elements to the vector
    int_vec.push_back(4);
    int_vec.push_back(5);
    int_vec.push_back(6);

    // Test
    const int* data_ptr = static_cast<const mcquack::vector<int>&>(int_vec).data();
    ASSERT_NE(data_ptr, nullptr) << "Data pointer shouldn't be null";
    EXPECT_EQ(data_ptr[0], 4) << "First element should be 4";
    EXPECT_EQ(data_ptr[1], 5) << "Second element should be 5";
    EXPECT_EQ(data_ptr[2], 6) << "Third element should be 6";
}

TEST(DataTest, SmallOptimizationEnabled)
{
    mcquack::vector<int> vec;
    for(std::size_t i = 0; i < mcquack::vector<int>::SMALL_CAPACITY; ++i) {
        vec.push_back(static_cast<int>(i));
    }

    for(std::size_t i = 0; i < mcquack::vector<int>::SMALL_CAPACITY; ++i) {
        EXPECT_EQ(vec.data()[i], i);
    }

    EXPECT_EQ(vec.size(), vec.SMALL_CAPACITY);
}

TEST(DataTest, SmallToDynamicTransition)
{
    mcquack::vector<int> vec;
    for(std::size_t i = 0; i < mcquack::vector<int>::SMALL_CAPACITY + 10; ++i) {
        vec.push_back(static_cast<int>(i));
    }

    for(std::size_t i = 0; i < mcquack::vector<int>::SMALL_CAPACITY + 10; ++i) {
        EXPECT_EQ(vec.data()[i], i);
    }

    EXPECT_EQ(vec.size(), vec.SMALL_CAPACITY + 10);
}

TEST(DataTest, SingleElementString)
{
    mcquack::vector<std::string> vec;
    vec.push_back("Hello");
    EXPECT_EQ(*vec.data(), "Hello");
    EXPECT_EQ(vec.size(), 1);
}

TEST(DataTest, MultipleElementsString)
{
    mcquack::vector<std::string> vec;
    vec.push_back("Hello");
    vec.push_back("World");
    vec.push_back("Vector");
    EXPECT_EQ(vec.data()[0], "Hello");
    EXPECT_EQ(vec.data()[1], "World");
    EXPECT_EQ(vec.data()[2], "Vector");
    EXPECT_EQ(vec.size(), 3);
}

TEST(DataTest, SmallOptimizationEnabledString)
{
    mcquack::vector<std::string> vec;
    for(std::size_t i = 0; i < mcquack::vector<std::string>::SMALL_CAPACITY; ++i) {
        vec.push_back(std::to_string(i));
    }

    for(std::size_t i = 0; i < mcquack::vector<std::string>::SMALL_CAPACITY; ++i) {
        EXPECT_EQ(vec.data()[i], std::to_string(i));
    }

    EXPECT_EQ(vec.size(), vec.SMALL_CAPACITY);
}

TEST(DataTest, SmallToDynamicTransitionString)
{
    mcquack::vector<std::string> vec;
    for(std::size_t i = 0; i <= mcquack::vector<std::string>::SMALL_CAPACITY; ++i) {
        vec.push_back(std::to_string(i));
    }

    for(std::size_t i = 0; i <= mcquack::vector<std::string>::SMALL_CAPACITY; ++i) {
        EXPECT_EQ(vec.data()[i], std::to_string(i));
    }

    EXPECT_EQ(vec.size(), vec.SMALL_CAPACITY + 1);
}
