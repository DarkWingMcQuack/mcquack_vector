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
        benchmark::ClobberMemory();
    }
}

template<template<class> class Vec, class T>
static void ConstructWithSize(benchmark::State& state)
{
    for(auto _ : state) {
        Vec<T> v(state.range(0));

        benchmark::DoNotOptimize(v);
        benchmark::ClobberMemory();
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

        benchmark::ClobberMemory();
    }
}
