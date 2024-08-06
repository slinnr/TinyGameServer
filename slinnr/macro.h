#pragma once

#include <string.h>

#define SYLAR_ASSERT(x) \
    if (!(x)) {\
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ASSERTION: " #x << "\n backtrace: \n" \
        << sylar::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }

#define SYLAR_ASSERT2(x, w) \
    if (!(x)) {\
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ASSERTION: " #x << "\n backtrace: \n" \
        << "\n" << w \
        << sylar::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }