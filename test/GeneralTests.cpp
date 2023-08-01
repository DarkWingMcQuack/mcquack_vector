#include <gtest/gtest.h>

#define private public

#include <mcquack_vector/vector.hpp>


TEST(GeneralTest, AllElementSizesCtor)
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
