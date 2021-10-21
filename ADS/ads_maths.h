#pragma once

/**
 * @brief Compute mathematical average of numbers[count]
 * 
 * @note The function is force-inlined to avoid the function
 *    call cost in complexity calculation
 * 
 * @param numbers[] The array of numbers to compute
 * @param count The amount of elements in numbers
 * @return The average of numbers
 */
inline double average(double numbers[], const unsigned count) {
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