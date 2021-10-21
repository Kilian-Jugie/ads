// Spectre mitigation due to n read on cc and used after
#pragma warning(disable: 5045)

unsigned factorial(unsigned n) {
  return n <= 1 ? 1 : n * factorial(n - 1);
}

#pragma warning(default: 5045)