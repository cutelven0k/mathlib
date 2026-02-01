#include <climits>
#include <mathlib.h>

namespace mathlib {

inline ml_result make_i64(ml_error e, std::int64_t v) { return { ml_kind::i64, e, { .i64 = v } }; }
inline ml_result make_u64(ml_error e, std::uint64_t v) { return { ml_kind::u64, e, { .u64 = v } }; }

inline ml_result ovf_i64() { return make_i64(ml_error::overflow, 0); }
inline ml_result ovf_u64() { return make_u64(ml_error::overflow, 0); }
inline ml_result div0_i64() { return make_i64(ml_error::div0, 0); }

ml_result ml_add(std::int64_t a, std::int64_t b)
{
    if ((b > 0 && a > INT64_MAX - b) || (b < 0 && a < INT64_MIN - b)) {
        return ovf_i64();
    }
    return make_i64(ml_error::ok, a + b);
}

ml_result ml_sub(std::int64_t a, std::int64_t b)
{
    if ((b > 0 && a < INT64_MIN + b) || (b < 0 && a > INT64_MAX + b)) {
        return ovf_i64();
    }
    return make_i64(ml_error::ok, a - b);
}

ml_result ml_mul(std::int64_t a, std::int64_t b)
{
    if ((a == INT64_MIN && b == -1) || (b == INT64_MIN && a == -1)) {
        return ovf_i64();
    }
    if (a > 0) {
        if (b > 0) {
            if (a > INT64_MAX / b)
                return ovf_i64();
        } else {
            if (b < INT64_MIN / a)
                return ovf_i64();
        }
    } else {
        if (b > 0) {
            if (a < INT64_MIN / b)
                return ovf_i64();
        } else {
            if (a != 0 && b < INT64_MAX / a)
                return ovf_i64();
        }
    }
    return make_i64(ml_error::ok, a * b);
}

ml_result ml_div(std::int64_t a, std::int64_t b)
{
    if (b == 0) {
        return div0_i64();
    }
    if (a == INT64_MIN && b == -1) {
        return ovf_i64();
    }
    return make_i64(ml_error::ok, a / b);
}

ml_result ml_pow(std::int64_t base, std::uint64_t exp)
{
    std::int64_t result = 1;
    for (uint64_t i = 0; i < exp; ++i) {
        ml_result r = ml_mul(result, base);
        if (r.error != ml_error::ok) {
            return r;
        }
        result = r.value.i64;
    }
    return make_i64(ml_error::ok, result);
}

ml_result ml_fact(std::uint64_t n)
{
    if (n <= 1) {
        return make_u64(ml_error::ok, 1);
    }

    ml_result prev = ml_fact(n - 1);
    if (prev.error != ml_error::ok) {
        return prev;
    }

    if (prev.value.u64 > (UINT64_MAX / n)) {
        return ovf_u64();
    }
    return make_u64(ml_error::ok, prev.value.u64 * n);
}

} // namespace mathlib
