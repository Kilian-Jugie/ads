/*
 * ads © 2021 by Kilian Jugie is licensed under Attribution 4.0 International.
 * To view a copy of this license, visit http ://creativecommons.org/licenses/by/4.0/
 */


#pragma once
#include "ads_compiler.h"

/**
 * @brief Compute mathematical average of numbers[count]
 * 
 * @note This function is forced inlined because compiler
 *  would probably not do it by itself due to loop with
 *  non-constexpr condition (loop unwinding) and we need
 *  the "call" to this function to be zero overhead
 * 
 * @param numbers[] The array of numbers to compute
 * @param count The amount of elements in numbers
 * @return The average of numbers
 */
ADS_FORCEINLINE double average(double numbers[], const unsigned count) {
  double average = numbers[0];
  for(unsigned i = 1; i < count; ++i) {
    average += numbers[i];
  }
  average /= count;
  return average;
}

/**
 * @brief Compute mathematical variance of numbers[count]
 *
 * @param numbers[] The array of numbers to compute
 * @param count The amount of elements in numbers
 * @return The mathematical variance
 */
double variance(double numbers[], const unsigned count);

/**
 * @brief Compute the mathematical factorial of n
 * 
 * @param n The number to compute the factorial to
 * @return The mathematical factorial
 */
unsigned factorial(unsigned n);