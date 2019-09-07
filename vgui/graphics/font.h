#pragma once

namespace vgui
{
    constexpr float default_font_size = 18;

    enum class FontWeight
    {
        NORMAL,
        BOLD,
    };
    constexpr FontWeight default_font_weight = FontWeight::NORMAL;

    enum class FontType
    {
        NORMAL,
        ITALIC,
        OBLIQUE
    };
    constexpr FontType default_font_type = FontType::NORMAL;


    struct FontStyle
    {
        FontType font_type = default_font_type;
        FontWeight font_weight = default_font_weight;
    };
    constexpr FontStyle default_font_style = { default_font_type, default_font_weight };

}