/*
 * ads © 2021 by Kilian Jugie is licensed under Attribution 4.0 International.
 * To view a copy of this license, visit http ://creativecommons.org/licenses/by/4.0/
 */

#include <cmath>
#include <iostream>
#include <random>
#include <chrono>
#include "ads_maths.h"

#define _TEST_PRINT_FAILED

#define _ADS_CAT(x, y) x##y
#define ADS_CAT(x, y) _ADS_CAT(x,y)
#define _ADS_STR(x) #x
#define ADS_STR(x) _ADS_STR(x)

#ifdef _DEBUG
/* TODO: Extract TEST_CMP expr and generalize TEST_EQ(_X) */
#include <cassert>
#define _EVAL1(...) __VA_ARGS__
#define _TEST_PRINT_DBG(l,r) std::cerr << "Test number " << ADS_COUNTER << " at " << __FILE__ << ":" << __LINE__ << " failed : " << "expected " << r << " got " << l << "\n"
#define _TEST_BLK_DBG(l,r) { _TEST_PRINT_DBG(l,r); _EVAL1(assert(0)); }

#define TEST_EQ_E(l,r,e) if (r < l-e && r > l+e) _TEST_BLK_DBG(l,r)

#define TEST_EQ(l,r) if(l != r) _TEST_BLK_DBG(l,r)
#define TEST_EQ_D(l,r) TEST_EQ_E(l,r,std::numeric_limits<double>::epsilon())
#else
#error This code should only be executed without optimizations. Comment this line out to acknowledge the warning

#define _TEST_BLK_RLS { exit(-ADS_COUNTER); }

#define TEST_EQ(l,r) if(l != r) _TEST_BLK_RLS
#define TEST_EQ_E(l,r,e) if (r < l-e && r > l+e) _TEST_BLK_RLS
#define TEST_EQ_D(l,r) TEST_EQ_E(l,r,std::numeric_limits<double>::epsilon())
#endif // DEBUG

namespace utils {
  template<typename T, size_t N>constexpr size_t length(T(&)[N]) {
    return N;
  }
}

namespace base {
  int log2(int n) {
    int i = 0;
    while (n > 1) {
      n /= 2;
      i++;
    }
    return i;
  }

  // Warning says that we have padding here
  struct ab {
    short a;
    // char __padd[2];
    int b;
  };
}

namespace optimized {
  int log2(int n) {
    int i = 0;
    while (n > 1) {
      n >>= 1;
      ++i;
    }
    return i;
  }

  // Data is contiguous
  struct ab {
    int b;
    short a;
  };
}

// Verification algorithms, eprouved
namespace verif {
  constexpr uint32_t __log2_32_tab32[32] = {
   0,  9,  1, 10, 13, 21,  2, 29,
  11, 14, 16, 18, 22, 25,  3, 30,
   8, 12, 20, 28, 15, 17, 24,  7,
  19, 27, 23,  6, 26,  5,  4, 31 };

  inline constexpr uint32_t log2_32(uint32_t value)
  {
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    return __log2_32_tab32[(uint32_t)(value * 0x07C4ACDD) >> 27];
  }
}

constexpr unsigned ADS_TESTS_LOG2_NB = 4096;
namespace tests {
  void log2() {
    std::default_random_engine reng;
    std::uniform_int_distribution<int> dist;
    int t, v;
    for (unsigned i = 0; i < ADS_TESTS_LOG2_NB; ++i) {
      t = dist(reng); // [0, INT_MAX]
      v = (int)::verif::log2_32((uint32_t)t);
      TEST_EQ(::base::log2(t), v);
      TEST_EQ(::optimized::log2(t), v);
    }
  }

  void factorial() {
    TEST_EQ(::factorial(9), 362880);
    TEST_EQ(::factorial(1), 1);
    TEST_EQ(::factorial(0), 1);
    TEST_EQ(::factorial(10), 3628800);
  }

  void average() {
    double test_array[] = {1,0,2,5,4,9,8,5.62,548.5,.12,56.6,5896.51,4568.544558464,254551.2254654,265654564.9897546};
    constexpr unsigned nb = utils::length(test_array);
    TEST_EQ(::average(test_array, 5), 2.4);
    TEST_EQ(::average(&test_array[2], 1), 2);
    
    TEST_EQ_D(::average(test_array, nb), 17728014.740652);
  }

  void variance() {
    double test_array[] = {1,0,2,5,4,9,8,5.62,548.5,.12,56.6,5896.51,4568.544558464,254551.2254654,265654564.9897546};
    constexpr unsigned nb = utils::length(test_array);
    TEST_EQ_D(::variance(test_array, nb), 4.7041554E+15);
  }
}

template<typename _TD>
class TD;

static uint64_t ads_bench_count = 100000000;
static uint64_t _ads_bench_counter = 0;
namespace benchmark {
  template<typename _ArgTy, typename _ArgRet, typename _DurTy = std::chrono::milliseconds,
   typename _ChTy>
    void bench(_ChTy&& name, _ArgRet(*fnc)(_ArgTy), _ArgTy _min = 0,
      _ArgTy _max = std::numeric_limits<_ArgTy>::max()) 
      requires std::is_same_v<const char*, std::decay_t<_ChTy>> {
    std::default_random_engine reng{};
    std::uniform_int_distribution<_ArgTy> dist{_min,_max};
    std::chrono::high_resolution_clock clk{};
    _ArgRet r;
    auto start = clk.now();
    for (uint64_t i{ 0 }; i < ads_bench_count; ++i) 
      r = fnc(dist(reng));
    auto end = clk.now();
    std::cerr << "Benchmark n" << _ads_bench_counter++ << " (" << std::forward<const char*>(name) 
      << ") : " << std::chrono::duration_cast<_DurTy>(end - start) << "\n";
  }
}

#define ads_autobench(fnc) benchmark::bench(ADS_STR(fnc), fnc)

int main() {
  tests::factorial();
  tests::average();
  tests::variance();
  tests::log2();

  ads_autobench(::base::log2);
  ads_autobench(::optimized::log2);
  ads_autobench(::verif::log2_32);

  std::cout << "All tests success\n";
  return 0;
}