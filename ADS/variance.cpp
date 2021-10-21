#include "ads_maths.h"

/**
 * @note "register" is used on dev to force value to be
 *    evaluated only once even in debug mode
 */
double variance(double numbers[], const unsigned count) {
  double _average = average(numbers, count);
  for(unsigned i = 0; i < count; ++i) {
    register const double dev = numbers[i] - _average;
    numbers[i] = dev * dev;
  }
  return average(numbers, count);
}