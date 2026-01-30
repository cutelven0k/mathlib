#include <mathlib.h>

namespace mathlib {
ml_result ml_add(int a, int b) { return {a + b, ml_error::ok}; }

ml_result ml_sub(int a, int b) { return {a - b, ml_error::ok}; }

ml_result ml_mul(int a, int b) { return {a * b, ml_error::ok}; }

ml_result ml_div(int a, int b) {
  if (b == 0) {
    return {0, ml_error::div0};
  }
  return {a / b, ml_error::ok};
}

ml_result ml_pow(int base, unsigned int exp) {
  int result = 1;
  for (unsigned int i = 0; i < exp; ++i) {
    result *= base;
  }

  return {result, ml_error::ok};
}

ml_result ml_fact(unsigned int n) {
  if (n <= 1) {
    return {1, ml_error::ok};
  }
  return {static_cast<int>(n * ml_fact(n - 1).value), ml_error::ok};
}

} // namespace mathlib
