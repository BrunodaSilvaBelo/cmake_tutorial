#include "allocator.h"
#include "pimpl.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>

template <typename T, typename Foo>
static auto foo(T const& x, T const& y, Foo&& function) {
  typename std::remove_reference<T>::type result(x.size(), 0);
  std::forward<Foo>(function)(x, y, result);
  return result;
}

int main(int argc, char** argv) {
  int const bytes = 1 << 13;
  int const count = std::sqrt((bytes / sizeof(int)) / 2);
  std::vector<double> x(count * count), y(count * count);
  auto gen = std::mt19937(std::random_device{}());
  std::uniform_int_distribution<int> dis(0, 1);
  std::generate(std::begin(x), std::end(x),
                [& dis = dis, &gen = gen ] { return dis(gen); });
  std::generate(std::begin(y), std::end(y),
                [& dis = dis, &gen = gen ] { return dis(gen); });
  std::shuffle(std::begin(x), std::end(x), gen);
  std::shuffle(std::begin(y), std::end(y), gen);

  auto a = foo(x, y, [ size  = count,
                       block = 8 ](auto const& x, auto const& y, auto& result) {
    for (std::size_t i = 0; i < size; i += block)
      for (std::size_t j = 0; j < size; j += block)
        for (std::size_t k = 0; k < size; k += block)
          for (auto i1 = i; i1 < i + block; ++i1)
            for (auto j1 = j; j1 < j + block; ++j1)
              for (auto k1 = k; k1 < k + block; ++k1)
                result[i1 * size + j1] += x[i1 * size + k1] * y[k1 * size + j1];
  });

  auto b =
      foo(x, y, [size = count](auto const& x, auto const& y, auto& result) {
        for (std::size_t i = 0; i < size; ++i)
          for (std::size_t j = 0; j < size; ++j)
            for (std::size_t k = 0; k < size; ++k)
              result[i * size + j] += x[i * size + k] * y[k * size + j];
      });

  std::cout << std::boolalpha << (a == b) << "\n";
  return 0;
}
