#pragma once
#include "common.h"

namespace vgui
{
    template<typename T>
    class vec2
    {
    public:
        vec2() {}
        constexpr vec2(T _x, T _y) : x(_x), y(_y) {}
        T x;
        T y;
    };
    using vec2f = vec2<float>;
    using vec2i = vec2<i32>;
    using vec2u = vec2<u32>;

    template<typename T>
    class vec3
    {
    public:
        vec3() {}
        constexpr vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
        T x;
        T y;
        T z;
    };
    using vec3f = vec3<float>;
    using vec3i = vec3<i32>;
    using vec3u = vec3<u32>;

    template<typename T>
    class vec4
    {
    public:
        vec4() {}
        constexpr vec4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
        T x;
        T y;
        T z;
        T w;
    };
    using vec4f = vec4<float>;
    using vec4i = vec4<i32>;
    using vec4u = vec4<u32>;

    static bool intersect_rect_mouse(float mouse_x, float mouse_y, float rect_x, float rect_y, float rect_width, float rect_height)
    {
        return mouse_x > rect_x && mouse_x < rect_x + rect_width && mouse_y > rect_y && mouse_y < rect_y + rect_height;
    }
}