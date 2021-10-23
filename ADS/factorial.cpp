/*
 * ads © 2021 by Kilian Jugie is licensed under Attribution 4.0 International.
 * To view a copy of this license, visit http ://creativecommons.org/licenses/by/4.0/
 */


/* Spectre mitigation due to n read on ccand used after */
#pragma warning(disable: 5045)

unsigned factorial(unsigned n) {
  return n <= 1 ? 1 : n * factorial(n - 1);
}

#pragma warning(default: 5045)