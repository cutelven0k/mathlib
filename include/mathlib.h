#pragma once
#ifndef MATHLIB_H
#define MATHLIB_H

#include <cstdint>

namespace mathlib {

enum class ml_error : std::uint8_t {
    ok = 0,
    div0,
    overflow
};

enum class ml_kind : std::uint8_t {
    i64 = 0,
    u64
};

struct ml_result {
    ml_kind kind;
    ml_error error;
    union {
        std::int64_t i64;
        std::uint64_t u64;
    } value;
};

ml_result ml_add(std::int64_t a, std::int64_t b);
ml_result ml_sub(std::int64_t a, std::int64_t b);
ml_result ml_mul(std::int64_t a, std::int64_t b);

ml_result ml_div(std::int64_t a, std::int64_t b);
ml_result ml_pow(std::int64_t base, std::uint64_t exp);

ml_result ml_fact(std::uint64_t n);

} // namespace mathlib

#endif
