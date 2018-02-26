#include <algorithm>
#include "benchmark/benchmark.h"
#include <chrono>
#include <cmath>
#include <random>
#include <string>
#include <type_traits>

template <typename T, typename Foo>
static auto foo(T const& x, T const& y, Foo&& function) {
  T result(x.size(), 0);
  std::forward<Foo>(function)(x, y, result);
  return result.size();
}

static void BM_BlockCalculation(benchmark::State& state) {
  int const bytes = state.range(0);
  int const count = std::sqrt((bytes / sizeof(int)) / 2);
  std::vector<int> x(count * count), y(count * count);
  auto gen = std::mt19937(std::random_device{}());
  std::uniform_int_distribution<int> dis(0, 1);
  std::generate(std::begin(x), std::end(x),
                [& dis = dis, &gen = gen ] { return dis(gen); });
  std::generate(std::begin(y), std::end(y),
                [& dis = dis, &gen = gen ] { return dis(gen); });
  std::shuffle(std::begin(x), std::end(x), gen);
  std::shuffle(std::begin(y), std::end(y), gen);

  for (auto _ : state) {
    auto value = foo(x, y, [
      size = count, block = state.range(1)
    ](auto const& x, auto const& y, auto& result) {
      for (std::size_t i = 0; i < size; i += block)
        for (std::size_t j = 0; j < size; j += block)
          for (std::size_t k = 0; k < size; k += block)
            for (auto i1 = i; i1 < std::min<size_t>(i + block, size); ++i1)
              for (auto j1 = j; j1 < std::min<size_t>(j + block, size); ++j1)
                for (auto k1 = k; k1 < std::min<size_t>(k + block, size); ++k1)
                  result[i1 * size + j1] +=
                      x[i1 * size + k1] * y[k1 * size + j1];
    });
    benchmark::DoNotOptimize(value);
  }
  state.SetBytesProcessed(long(state.iterations()) * long(bytes));
  state.SetLabel(std::to_string(bytes / (1 << 20)) + "mb");
}

BENCHMARK(BM_BlockCalculation)
    ->Unit(benchmark::kMillisecond)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 20, 1 << 24}, {1 << 10, 1 << 15}});

static void BM_LinearCalculation(benchmark::State& state) {
  int const bytes = state.range(0);
  int const count = std::sqrt((bytes / sizeof(int)) / 2);
  std::vector<int> x(count * count), y(count * count);
  auto gen = std::mt19937(std::random_device{}());
  std::uniform_int_distribution<int> dis(0, 1);
  std::generate(std::begin(x), std::end(x),
                [& dis = dis, &gen = gen ] { return dis(gen); });
  std::generate(std::begin(y), std::end(y),
                [& dis = dis, &gen = gen ] { return dis(gen); });
  std::shuffle(std::begin(x), std::end(x), gen);
  std::shuffle(std::begin(y), std::end(y), gen);

  for (auto _ : state) {
    auto value =
        foo(x, y, [size = count](auto const& x, auto const& y, auto& result) {
          for (std::size_t i = 0; i < size; ++i)
            for (std::size_t j = 0; j < size; ++j)
              for (std::size_t k = 0; k < size; ++k)
                result[i * size + j] += x[i * size + k] * y[k * size + j];
        });
    benchmark::DoNotOptimize(value);
  }
  state.SetBytesProcessed(long(state.iterations()) * long(bytes));
  state.SetLabel(std::to_string(bytes / (1 << 20)) + "mb");
}
BENCHMARK(BM_LinearCalculation)
    ->Unit(benchmark::kMillisecond)
    ->RangeMultiplier(2)
    ->Range(1 << 20, 1 << 24);

BENCHMARK_MAIN();
