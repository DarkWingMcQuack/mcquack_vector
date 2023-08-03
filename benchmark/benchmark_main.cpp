#include <benchmark/benchmark.h>
#include <cstddef>
#include <cstdint>
#include <mcquack_vector/vector.hpp>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

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

template<class T>
static void BM_VectorEmplaceBack(benchmark::State& state)
{
    for(auto _ : state) {
        std::vector<T> v;

        for(int i = 0; i < state.range(0); ++i) {
            if constexpr(std::is_same_v<std::string, T>) {
                v.emplace_back(random_str(i));
            } else {
                v.emplace_back(static_cast<T>(i));
            }
        }
        benchmark::DoNotOptimize(v);
        benchmark::ClobberMemory();
    }
}

template<class T>
static void BM_McQuackVectorEmplaceBack(benchmark::State& state)
{
    for(auto _ : state) {
        mcquack::vector<T> v;

        for(int i = 0; i < state.range(0); ++i) {
            if constexpr(std::is_same_v<std::string, T>) {
                v.emplace_back(random_str(i));
            } else {
                v.emplace_back(static_cast<T>(i));
            }
        }
        benchmark::DoNotOptimize(v);
        benchmark::ClobberMemory();
    }
}

// Register the function as a benchmark
// Arguments macro specifies an argument for a benchmark, it can take any number of arguments
BENCHMARK(BM_VectorEmplaceBack<std::string>)->Range(1, 1 << 10);
BENCHMARK(BM_McQuackVectorEmplaceBack<std::string>)->Range(1, 1 << 10);
BENCHMARK(BM_VectorEmplaceBack<int>)->Range(1, 1 << 20);
BENCHMARK(BM_McQuackVectorEmplaceBack<int>)->Range(1, 1 << 20);
BENCHMARK(BM_VectorEmplaceBack<std::int8_t>)->Range(1, 1 << 20);
BENCHMARK(BM_McQuackVectorEmplaceBack<std::int8_t>)->Range(1, 1 << 20);

// main function
BENCHMARK_MAIN();
