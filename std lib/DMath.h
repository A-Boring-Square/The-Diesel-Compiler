#ifndef DSL_STD_LIB_MATH_H
#define DSL_STD_LIB_MATH_H

#include "DIESEL.h"

// -------------------- Type-safe math with overflow/underflow checks --------------------

#ifdef DSL_STD_LIB_FLAG_USE_TYPE_SAFE_MATH

// Macro for checking overflow in addition, subtraction, and multiplication
#define CHECK_OVERFLOW(result, num, max_val, min_val, op_type) \
    if ((num > 0 && result > max_val - num) || (num < 0 && result < min_val - num)) { \
        DSL_Crash_And_Burn("Overflow/Underflow in %s operation with operands %d and %d", op_type, result, num); \
    }

// Macro for multiplication overflow check
#define CHECK_MUL_OVERFLOW(result, num, max_val, min_val, op_type) \
    if ((num != 0 && result > max_val / num) || (num != 0 && result < min_val / num)) { \
        DSL_Crash_And_Burn("Overflow/Underflow in %s operation with operands %d and %d", op_type, result, num); \
    }

#else
// No overflow checks, just the operations (for performance optimization)
#define CHECK_OVERFLOW(result, num, max_val, min_val, op_type)
#define CHECK_MUL_OVERFLOW(result, num, max_val, min_val, op_type)
#endif

#ifdef DSL_STD_LIB_FLAG_USE_CUSTOM_MATH_CONSTANTS
// Custom math constants for minimal environments
#define DSL_PI 3.14159265358979323846
#define DSL_E  2.71828182845904523536
#define DSL_SQRT2 1.41421356237309504880
#else
// Fallback to the standard math constants if math.h is available
#ifndef M_PI
#define DSL_PI 3.14159265358979323846
#else
#define DSL_PI M_PI
#endif

#ifndef M_E
#define DSL_E 2.71828182845904523536
#else
#define DSL_E M_E
#endif

#ifndef M_SQRT2
#define DSL_SQRT2 1.41421356237309504880
#else
#define DSL_SQRT2 M_SQRT2
#endif
#endif

#ifdef DSL_STD_LIB_FLAG_USE_FAST_INVERSE_SQRT || !defined(DSL_STD_LIB_FLAG_USE_MATH_H)
// Fast inverse square root implementation
static inline float DSL_InvSqrt(float x) {
    float half = 0.5f * x;
    int32_t i = *(int32_t*)&x;        // Treat float as int
    i = 0x5f3759df - (i >> 1);        // The magic number
    x = *(float*)&i;                   // Convert back to float
    x = x * (1.5f - half * x * x);     // One iteration of Newton's method
    return x;
}
#else
// Fallback: Standard inverse square root using math ibrary
static inline float DSL_FastInvSqrt(float x) {
    // NOTE: this could error in certen IDEs because of the highly macroed nature of the Diesel standard library
    return 1.0f / sqrtf(x);
}
#endif

// ------------------------------ ADDITION ------------------------------
DSL_int8 DSL_add_int8(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int8 result = 0;
    for (int8_t i = 0; i < count; ++i) {
        DSL_int8 num = va_arg(args, DSL_int8);
        CHECK_OVERFLOW(result, num, INT8_MAX, INT8_MIN, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

DSL_uint8 DSL_add_uint8(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint8 result = 0;
    for (int8_t i = 0; i < count; ++i) {
        DSL_uint8 num = va_arg(args, DSL_uint8);
        CHECK_OVERFLOW(result, num, UINT8_MAX, 0, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

DSL_int16 DSL_add_int16(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int16 result = 0;
    for (int8_t i = 0; i < count; ++i) {
        DSL_int16 num = va_arg(args, DSL_int16);
        CHECK_OVERFLOW(result, num, INT16_MAX, INT16_MIN, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

DSL_uint16 DSL_add_uint16(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint16 result = 0;
    for (int8_t i = 0; i < count; ++i) {
        DSL_uint16 num = va_arg(args, DSL_uint16);
        CHECK_OVERFLOW(result, num, UINT16_MAX, 0, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

DSL_int32 DSL_add_int32(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int32 result = 0;
    for (int8_t i = 0; i < count; ++i) {
        DSL_int32 num = va_arg(args, DSL_int32);
        CHECK_OVERFLOW(result, num, INT32_MAX, INT32_MIN, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

DSL_uint32 DSL_add_uint32(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint32 result = 0;
    for (int8_t i = 0; i < count; ++i) {
        DSL_uint32 num = va_arg(args, DSL_uint32);
        CHECK_OVERFLOW(result, num, UINT32_MAX, 0, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

DSL_int64 DSL_add_int64(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int64 result = 0;
    for (int8_t i = 0; i < count; ++i) {
        DSL_int64 num = va_arg(args, DSL_int64);
        CHECK_OVERFLOW(result, num, INT64_MAX, INT64_MIN, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

DSL_uint64 DSL_add_uint64(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint64 result = 0;
    for (int8_t i = 0; i < count; ++i) {
        DSL_uint64 num = va_arg(args, DSL_uint64);
        CHECK_OVERFLOW(result, num, UINT64_MAX, 0, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

// ------------------------------ FLOATING POINT ADDITION ------------------------------
DSL_float32 DSL_add_float32(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_float32 result = 0.0f;
    for (int8_t i = 0; i < count; ++i) {
        DSL_float32 num = va_arg(args, DSL_float32);
        result += num;
    }
    va_end(args);
    return result;
}

DSL_float64 DSL_add_float64(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_float64 result = 0.0;
    for (int8_t i = 0; i < count; ++i) {
        DSL_float64 num = va_arg(args, DSL_float64);
        result += num;
    }
    va_end(args);
    return result;
}

// ------------------------------ MULTIPLICATION ------------------------------
DSL_int8 DSL_mul_int8(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int8 result = 1;
    for (int8_t i = 0; i < count; ++i) {
        DSL_int8 num = va_arg(args, DSL_int8);
        CHECK_MUL_OVERFLOW(result, num, INT8_MAX, INT8_MIN, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

DSL_uint8 DSL_mul_uint8(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint8 result = 1;
    for (int8_t i = 0; i < count; ++i) {
        DSL_uint8 num = va_arg(args, DSL_uint8);
        CHECK_MUL_OVERFLOW(result, num, UINT8_MAX, 0, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

DSL_int16 DSL_mul_int16(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int16 result = 1;
    for (int8_t i = 0; i < count; ++i) {
        DSL_int16 num = va_arg(args, DSL_int16);
        CHECK_MUL_OVERFLOW(result, num, INT16_MAX, INT16_MIN, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

DSL_uint16 DSL_mul_uint16(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint16 result = 1;
    for (int8_t i = 0; i < count; ++i) {
        DSL_uint16 num = va_arg(args, DSL_uint16);
        CHECK_MUL_OVERFLOW(result, num, UINT16_MAX, 0, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

DSL_int32 DSL_mul_int32(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int32 result = 1;
    for (int8_t i = 0; i < count; ++i) {
        DSL_int32 num = va_arg(args, DSL_int32);
        CHECK_MUL_OVERFLOW(result, num, INT32_MAX, INT32_MIN, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

DSL_uint32 DSL_mul_uint32(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint32 result = 1;
    for (int8_t i = 0; i < count; ++i) {
        DSL_uint32 num = va_arg(args, DSL_uint32);
        CHECK_MUL_OVERFLOW(result, num, UINT32_MAX, 0, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

DSL_int64 DSL_mul_int64(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int64 result = 1;
    for (int8_t i = 0; i < count; ++i) {
        DSL_int64 num = va_arg(args, DSL_int64);
        CHECK_MUL_OVERFLOW(result, num, INT64_MAX, INT64_MIN, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

DSL_uint64 DSL_mul_uint64(int8_t count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint64 result = 1;
    for (int8_t i = 0; i < count; ++i) {
        DSL_uint64 num = va_arg(args, DSL_uint64);
        CHECK_MUL_OVERFLOW(result, num, UINT64_MAX, 0, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

#endif
