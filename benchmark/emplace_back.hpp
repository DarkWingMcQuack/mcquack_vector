#pragma once

#include "utils.hpp"

#include <benchmark/benchmark.h>
#include <vector>

template<template<class> class Vec, class T>
static void EmplaceBack(benchmark::State& state)
{
    for(auto _ : state) {

        // state.PauseTiming();
        Vec<T> v;
        // state.ResumeTiming();

        for(int i = 0; i < state.range(0); ++i) {
            if constexpr(std::is_same_v<std::string, T>) {
                v.emplace_back(random_str(std::min(i, 100)));
            } else {
                v.emplace_back(static_cast<T>(i));
            }
        }

        benchmark::DoNotOptimize(v);

        // state.PauseTiming();
    }
}
