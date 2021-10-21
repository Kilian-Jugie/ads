#include <cmath>
#include <iostream>
#include "ads_maths.h"

#define _TEST_FAILED  std::cerr << "Test number " << __COUNTER__ << " at " << __FILE__ << ":" << __LINE__ << " failed : "

#ifdef _DEBUG
#include <cassert>
#define TEST_EQ(l,r) if(l != r) { _TEST_FAILED << "expected " << r << " got " << l; assert(0); }
#define TEST_EQ_D(l,r,e) if (r < l-e && r > l+e) { _TEST_FAILED << "expected " << r << " got " << l; assert(0); }
#else
#error This code should only be executed without optimizations. Comment this line out to acknowledge the warning
#define TEST_EQ(l,r) if(l != r) { exit(-__COUNTER__); } 
#define TEST_EQ_D(l,r,e) if (r < l-e && r > l+e) { exit(-__COUNTER__); } 
#endif // DEBUG

namespace utils {
  template<typename T, size_t N>constexpr size_t length(T(&)[N]) {
    return N;
  }
}

namespace tests {
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
    
    TEST_EQ_D(::average(test_array, nb), 17728014.740652, std::numeric_limits<double>::epsilon());
  }

  void variance() {
    double test_array[] = {1,0,2,5,4,9,8,5.62,548.5,.12,56.6,5896.51,4568.544558464,254551.2254654,265654564.9897546};
    constexpr unsigned nb = utils::length(test_array);
    TEST_EQ_D(::variance(test_array, nb), 4.7041554E+15, std::numeric_limits<double>::epsilon());
  }
}

int main() {
  tests::factorial();
  tests::average();
  tests::variance();

  std::cout << "All tests success\n";
  return 0;
}