#pragma once

#include <string>
#include <string_view>

inline auto random_str(std::size_t len) noexcept -> std::string
{
    constexpr std::string_view alphanum =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "\n\t\r !§$%%&/()=?\"'#*+~-.,;:_><";

    std::string tmp_s;
    tmp_s.reserve(len);

    for(std::size_t i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (alphanum.size() - 1)];
    }

    return tmp_s;
}
