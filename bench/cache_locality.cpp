#include <algorithm>
#include <benchmark/benchmark.h>
#include <random>
#include <vector>

static void BM_Cache(benchmark::State& state) {
  int const bytes = 1 << state.range(0);
  int const count = (bytes / sizeof(int)) / 2;
  std::vector<int> data(count), indices(count);
  std::iota(std::begin(indices), std::end(indices), 0);

  auto gen = std::mt19937(std::random_device{}());
  std::uniform_int_distribution<int> dis(0, 1);
  std::generate(std::begin(data), std::end(data),
                [& dis = dis, &gen = gen ] { return dis(gen); });
  std::shuffle(std::begin(indices), std::end(indices), gen);
  std::shuffle(std::begin(data), std::end(data), gen);

  int x = 0;
  for (auto _ : state) {
    for (auto i : indices)
      x += data[i];
    benchmark::DoNotOptimize(x);
  }

  state.SetBytesProcessed(long(state.iterations()) * long(bytes));
  state.SetLabel(std::to_string(bytes / (1 << 10)) + "kb");
}

BENCHMARK(BM_Cache)->DenseRange(13, 20);

BENCHMARK_MAIN();
