/*
 * ads © 2021 by Kilian Jugie is licensed under Attribution 4.0 International.
 * To view a copy of this license, visit http ://creativecommons.org/licenses/by/4.0/
 */

#include "ads_maths.h"

/**
 * @note "register" is used to generate clean assembly
 *  and avoid inlining optimization, unwanted for our study
 */
double variance(double numbers[], const unsigned count) {
  double _average = average(numbers, count);
  for(unsigned i = 0; i < count; ++i) {
    register const double dev = numbers[i] - _average;
    numbers[i] = dev * dev;
  }
  return average(numbers, count);
}