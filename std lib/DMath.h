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


static inline DSL_float32 DSL_InvSqrt32(DSL_float32 x) {
    return 1.0f / sqrtf(x);
}

static inline DSL_float64 DSL_InvSqrt64(DSL_float64 x) {
    return 1.0d / sqrt(x)
}

// ------------------------------ ADDITION ------------------------------
DSL_int8 DSL_AddInt8(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int8 result = 0;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_int8 num = va_arg(args, DSL_int8);
        CHECK_OVERFLOW(result, num, INT8_MAX, INT8_MIN, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

DSL_uint8 DSL_AddUint8(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint8 result = 0;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_uint8 num = va_arg(args, DSL_uint8);
        CHECK_OVERFLOW(result, num, UINT8_MAX, 0, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

DSL_int16 DSL_AddInt16(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int16 result = 0;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_int16 num = va_arg(args, DSL_int16);
        CHECK_OVERFLOW(result, num, INT16_MAX, INT16_MIN, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

DSL_uint16 DSL_AddUint16(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint16 result = 0;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_uint16 num = va_arg(args, DSL_uint16);
        CHECK_OVERFLOW(result, num, UINT16_MAX, 0, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

DSL_int32 DSL_AddInt32(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int32 result = 0;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_int32 num = va_arg(args, DSL_int32);
        CHECK_OVERFLOW(result, num, INT32_MAX, INT32_MIN, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

DSL_uint32 DSL_AddUint32(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint32 result = 0;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_uint32 num = va_arg(args, DSL_uint32);
        CHECK_OVERFLOW(result, num, UINT32_MAX, 0, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

DSL_int64 DSL_AddInt64(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int64 result = 0;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_int64 num = va_arg(args, DSL_int64);
        CHECK_OVERFLOW(result, num, INT64_MAX, INT64_MIN, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

DSL_uint64 DSL_AddUint64(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint64 result = 0;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_uint64 num = va_arg(args, DSL_uint64);
        CHECK_OVERFLOW(result, num, UINT64_MAX, 0, "addition");
        result += num;
    }
    va_end(args);
    return result;
}

// ------------------------------ FLOATING POINT ADDITION ------------------------------
DSL_float32 DSL_AddFloat32(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_float32 result = 0.0f;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_float32 num = va_arg(args, DSL_float32);
        result += num;
    }
    va_end(args);
    return result;
}

DSL_float64 DSL_AddFloat64(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_float64 result = 0.0;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_float64 num = va_arg(args, DSL_float64);
        result += num;
    }
    va_end(args);
    return result;
}

// ------------------------------ MULTIPLICATION ------------------------------
DSL_int8 DSL_MulInt8(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int8 result = 1;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_int8 num = va_arg(args, DSL_int8);
        CHECK_MUL_OVERFLOW(result, num, INT8_MAX, INT8_MIN, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

DSL_uint8 DSL_MulUint8(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint8 result = 1;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_uint8 num = va_arg(args, DSL_uint8);
        CHECK_MUL_OVERFLOW(result, num, UINT8_MAX, 0, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

DSL_int16 DSL_MulInt16(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int16 result = 1;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_int16 num = va_arg(args, DSL_int16);
        CHECK_MUL_OVERFLOW(result, num, INT16_MAX, INT16_MIN, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

DSL_uint16 DSL_MulUint16(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint16 result = 1;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_uint16 num = va_arg(args, DSL_uint16);
        CHECK_MUL_OVERFLOW(result, num, UINT16_MAX, 0, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

DSL_int32 DSL_MulInt32(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int32 result = 1;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_int32 num = va_arg(args, DSL_int32);
        CHECK_MUL_OVERFLOW(result, num, INT32_MAX, INT32_MIN, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

DSL_uint32 DSL_MulUint32(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint32 result = 1;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_uint32 num = va_arg(args, DSL_uint32);
        CHECK_MUL_OVERFLOW(result, num, UINT32_MAX, 0, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

DSL_int64 DSL_MulInt64(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_int64 result = 1;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_int64 num = va_arg(args, DSL_int64);
        CHECK_MUL_OVERFLOW(result, num, INT64_MAX, INT64_MIN, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

DSL_uint64 DSL_MulUint64(DSL_int8 count, ...) {
    va_list args;
    va_start(args, count);
    DSL_uint64 result = 1;
    for (DSL_int8 i = 0; i < count; ++i) {
        DSL_uint64 num = va_arg(args, DSL_uint64);
        CHECK_MUL_OVERFLOW(result, num, UINT64_MAX, 0, "multiplication");
        result *= num;
    }
    va_end(args);
    return result;
}

// -------------------- Utility Functions --------------------
static inline DSL_float32 DSL_Abs32(DSL_float32 x) {
    return fabsf(x);
}

static inline DSL_float64 DSL_Abs64(DSL_float64 x) {
    return fabs(x);
}

static inline int32_t DSL_AbsInt32(DSL_int32 x) {
    return x < 0 ? -x : x;
}

static inline int64_t DSL_AbsInt64(DSL_int32 x) {
    return x < 0 ? -x : x;
}

static inline DSL_float32 DSL_Round32(DSL_float32 x) {
    return roundf(x);
}

static inline DSL_float64 DSL_Round64(DSL_float64 x) {
    return round(x);
}

static inline DSL_float32 DSL_Floor32(DSL_float32 x) {
    return floorf(x);
}

static inline DSL_float64 DSL_Floor64(DSL_float64 x) {
    return floor(x);
}

static inline DSL_float32 DSL_Ceil32(DSL_float32 x) {
    return ceilf(x);
}

static inline DSL_float64 DSL_Ceil64(DSL_float64 x) {
    return ceil(x);
}

// Fast inverse square root (Quake III approximation)
static inline DSL_float32 DSL_FastInvSqrt32(DSL_float32 x) {
    union { DSL_float32 f; DSL_uint32 i; } conv = { x };
    conv.i = 0x5F3759DF - (conv.i >> 1);
    return conv.f * (1.5f - (x * 0.5f * conv.f * conv.f));
}

static inline DSL_float64 DSL_FastInvSqrt64(DSL_float64 x) {
    union { DSL_float64 f; DSL_uint64 i; } conv = { x };
    conv.i = 0x5FE6EB50C7B537A9 - (conv.i >> 1);
    return conv.f * (1.5 - (x * 0.5 * conv.f * conv.f));
}

static inline DSL_float32 DSL_InvSqrt32(DSL_float32 x) {
    return 1.0f / sqrtf(x);
}

static inline DSL_float64 DSL_InvSqrt64(DSL_float64 x) {
    return 1.0 / sqrt(x);
}

// ------------------------------ TRIGONOMETRIC FUNCTIONS ------------------------------
static inline DSL_float32 DSL_Sin32(DSL_float32 x) {
    return sinf(x);
}

static inline DSL_float64 DSL_Sin64(DSL_float64 x) {
    return sin(x);
}

static inline DSL_float32 DSL_Cos32(DSL_float32 x) {
    return cosf(x);
}

static inline DSL_float64 DSL_Cos64(DSL_float64 x) {
    return cos(x);
}

static inline DSL_float32 DSL_Tan32(DSL_float32 x) {
    return tanf(x);
}
static inline DSL_float64 DSL_Tan64(DSL_float64 x) {
    return tan(x);
}

// ------------------------------ LOGARITHMIC FUNCTIONS ------------------------------
static inline DSL_float32 DSL_Log32(DSL_float32 x) {
    return logf(x);
}

static inline DSL_float64 DSL_Log64(DSL_float64 x) {
    return log(x);
}

static inline DSL_float32 DSL_Log10_32(DSL_float32 x) {
    return log10f(x);
}

static inline DSL_float64 DSL_Log10_64(DSL_float64 x) {
    return log10(x);
}

// ------------------------------ EXPONENTIAL FUNCTIONS ------------------------------
static inline DSL_float32 DSL_Exp32(DSL_float32 x) {
    return expf(x);
}

static inline DSL_float64 DSL_Exp64(DSL_float64 x) {
    return exp(x);
}

static inline DSL_float32 DSL_Pow32(DSL_float32 base, DSL_float32 exp) {
    return powf(base, exp);
}

static inline DSL_float64 DSL_Pow64(DSL_float64 base, DSL_float64 exp) {
    return pow(base, exp);
}

// ------------------------------ HYPERBOLIC FUNCTIONS ------------------------------
static inline DSL_float32 DSL_Sinh32(DSL_float32 x) {
    return sinhf(x);
}

static inline DSL_float64 DSL_Sinh64(DSL_float64 x) {
    return sinh(x);
}

static inline DSL_float32 DSL_Cosh32(DSL_float32 x) {
    return coshf(x);
}

static inline DSL_float64 DSL_Cosh64(DSL_float64 x) {
    return cosh(x);
}

static inline DSL_float32 DSL_Tanh32(DSL_float32 x) {
    return tanhf(x);
}

static inline DSL_float64 DSL_Tanh64(DSL_float64 x) {
    return tanh(x);
}

#endif
