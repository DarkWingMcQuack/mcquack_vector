#pragma once

#include "utils.hpp"
#include <benchmark/benchmark.h>
#include <mcquack_vector/vector.hpp>
#include <string>
#include <vector>


template<template<class> class Vec, class T>
static void EmptyConstruct(benchmark::State& state)
{
    for(auto _ : state) {
        Vec<T> v;

        benchmark::DoNotOptimize(v);
    }
}

template<template<class> class Vec, class T>
static void ConstructWithSize(benchmark::State& state)
{
    for(auto _ : state) {
        Vec<T> v(state.range(0));

        benchmark::DoNotOptimize(v);
    }
}

template<template<class> class Vec, class T>
static void ConstructWithElem(benchmark::State& state)
{

    for(auto _ : state) {

        if constexpr(std::is_same_v<std::string, T>) {
            Vec<T> v(state.range(0), std::to_string(std::rand()));
            benchmark::DoNotOptimize(v);
        } else {
            Vec<T> v(state.range(0), static_cast<T>(std::rand()));
            benchmark::DoNotOptimize(v);
        }
    }
}


template<template<class> class Vec, class T>
static void ConstructCopy(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming(); // Pause timing to exclude setup from the benchmark

        Vec<T> temp(state.range(0));

        for (int i = 0; i < state.range(0); i++) {
            temp[i] = i;
        }

        state.ResumeTiming(); // Resume timing to include only the constructor
        Vec<T> vec(temp);
        benchmark::DoNotOptimize(vec); // Ensure that the whole construction is not optimized away
    }
}

template<template<class> class Vec, class T>
static void ConstructMove(benchmark::State& state)
{
    for (auto _ : state) {
        state.PauseTiming(); // Pause timing to exclude setup from the benchmark

        Vec<T> temp(state.range(0));

        for (int i = 0; i < state.range(0); i++) {
            temp[i] = i;
        }

        state.ResumeTiming(); // Resume timing to include only the constructor
        Vec<T> vec(std::move(temp));
        benchmark::DoNotOptimize(vec); // Ensure that the whole construction is not optimized away
    }
}
