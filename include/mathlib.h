#pragma once
#ifndef MATHLIB_H
#define MATHLIB_H

namespace mathlib {
enum class ml_error { ok, div0 };

struct ml_result {
  int value;
  ml_error error;
};

ml_result ml_add(int a, int b);
ml_result ml_sub(int a, int b);
ml_result ml_mul(int a, int b);

ml_result ml_div(int a, int b);
ml_result ml_pow(int base, unsigned int exp);
ml_result ml_fact(unsigned int n);
} // namespace mathlib

#endif
