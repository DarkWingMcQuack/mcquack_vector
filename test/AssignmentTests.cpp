#include <gtest/gtest.h>

#define private public

#include <mcquack_vector/vector.hpp>

TEST(VectorTests, StringVectorCopyAssignment)
{
    mcquack::vector<std::string> original{"a", "b", "c"};
    mcquack::vector<std::string> copy;

    copy = original; // Copy assignment

    EXPECT_EQ(original.size(), copy.size());
    for(size_t i = 0; i < original.size(); i++) {
        EXPECT_EQ(original[i], copy[i]);
    }
}

TEST(VectorTests, StringVectorMoveAssignment)
{
    mcquack::vector<std::string> original{"a", "b", "c"};
    mcquack::vector<std::string> copy;

    copy = std::move(original); // Move assignment

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy[0], "a");
    EXPECT_EQ(copy[1], "b");
    EXPECT_EQ(copy[2], "c");
}

TEST(VectorTests, IntVectorCopyAssignment)
{
    mcquack::vector<int> original{1, 2, 3};
    mcquack::vector<int> copy;

    copy = original; // Copy assignment

    EXPECT_EQ(original.size(), copy.size());
    for(size_t i = 0; i < original.size(); i++) {
        EXPECT_EQ(original[i], copy[i]);
    }
}

TEST(VectorTests, IntVectorMoveAssignment)
{
    mcquack::vector<int> original{1, 2, 3};
    mcquack::vector<int> copy;

    copy = std::move(original); // Move assignment

    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
    EXPECT_EQ(copy[2], 3);
}
