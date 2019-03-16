#pragma once
#include <stdint.h>
#include <memory>

namespace vgui
{
    typedef int32_t i32;
    typedef uint32_t u32;

    typedef int64_t i64;
    typedef uint64_t u64;

    template<typename T>
    using UPtr = std::unique_ptr<T>;

    template<typename T>
    using SPtr = std::shared_ptr<T>;
}