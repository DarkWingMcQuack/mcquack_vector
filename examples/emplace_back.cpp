#include <mcquack_vector/vector.hpp>
#include <string>

auto main() -> int
{
    mcquack::vector<std::string> vec;

    for(int i = 0; i < 100; i++) {
        vec.emplace_back(std::to_string(i));
    }
}
