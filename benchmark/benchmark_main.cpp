#include "emplace_back.hpp"
#include "construct.hpp"

#include <benchmark/benchmark.h>
#include <cstddef>
#include <cstdint>
#include <mcquack_vector/vector.hpp>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>


BENCHMARK(ConstructWithSize<std::vector, std::string>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<mcquack::vector, std::string>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<std::vector, std::uint64_t>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<mcquack::vector, std::uint64_t>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<std::vector, std::uint32_t>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<mcquack::vector, std::uint32_t>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<std::vector, std::uint16_t>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<mcquack::vector, std::uint16_t>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<std::vector, std::uint8_t>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<mcquack::vector, std::uint8_t>)->Range(1, 1 << 20);

BENCHMARK(ConstructWithSize<std::vector, std::string>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<mcquack::vector, std::string>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<std::vector, std::uint64_t>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<mcquack::vector, std::uint64_t>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<std::vector, std::uint32_t>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<mcquack::vector, std::uint32_t>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<std::vector, std::uint16_t>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<mcquack::vector, std::uint16_t>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<std::vector, std::uint8_t>)->Range(1, 1 << 20);
BENCHMARK(ConstructWithSize<mcquack::vector, std::uint8_t>)->Range(1, 1 << 20);

BENCHMARK(EmptyConstruct<std::vector, std::string>)->Range(1, 1 << 20);
BENCHMARK(EmptyConstruct<mcquack::vector, std::string>)->Range(1, 1 << 20);
BENCHMARK(EmptyConstruct<std::vector, std::uint64_t>)->Range(1, 1 << 20);
BENCHMARK(EmptyConstruct<mcquack::vector, std::uint64_t>)->Range(1, 1 << 20);
BENCHMARK(EmptyConstruct<std::vector, std::uint32_t>)->Range(1, 1 << 20);
BENCHMARK(EmptyConstruct<mcquack::vector, std::uint32_t>)->Range(1, 1 << 20);
BENCHMARK(EmptyConstruct<std::vector, std::uint16_t>)->Range(1, 1 << 20);
BENCHMARK(EmptyConstruct<mcquack::vector, std::uint16_t>)->Range(1, 1 << 20);
BENCHMARK(EmptyConstruct<std::vector, std::uint8_t>)->Range(1, 1 << 20);
BENCHMARK(EmptyConstruct<mcquack::vector, std::uint8_t>)->Range(1, 1 << 20);

BENCHMARK(EmplaceBack<std::vector, std::string>)->Range(1, 1 << 20);
BENCHMARK(EmplaceBack<mcquack::vector, std::string>)->Range(1, 1 << 20);
BENCHMARK(EmplaceBack<std::vector, std::uint64_t>)->Range(1, 1 << 20);
BENCHMARK(EmplaceBack<mcquack::vector, std::uint64_t>)->Range(1, 1 << 20);
BENCHMARK(EmplaceBack<std::vector, std::uint32_t>)->Range(1, 1 << 20);
BENCHMARK(EmplaceBack<mcquack::vector, std::uint32_t>)->Range(1, 1 << 20);
BENCHMARK(EmplaceBack<std::vector, std::uint16_t>)->Range(1, 1 << 20);
BENCHMARK(EmplaceBack<mcquack::vector, std::uint16_t>)->Range(1, 1 << 20);
BENCHMARK(EmplaceBack<std::vector, std::uint8_t>)->Range(1, 1 << 20);
BENCHMARK(EmplaceBack<mcquack::vector, std::uint8_t>)->Range(1, 1 << 20);



// main function
BENCHMARK_MAIN();
