#include <gtest/gtest.h>

#define private public

#include <mcquack_vector/vector.hpp>


TEST(BackTest, BackInt) {
    // Create a vector of ints
    mcquack::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // Test back()
    EXPECT_EQ(vec.back(), 3);
}

TEST(BackTest, BackString) {
    // Create a vector of strings
    mcquack::vector<std::string> vec;
    vec.push_back("first");
    vec.push_back("second");
    vec.push_back("third");

    // Test back()
    EXPECT_EQ(vec.back(), "third");
}
