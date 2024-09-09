/**
License details have been added to this "substantial portion of
the original software", at: https://github.com/vorlac/godot-roguelite
as established by it's license as of 25-Mar-24:

"MIT License

Copyright (c) 2023 sal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE."
*/

#pragma once

#include <concepts>
#include <string>
#include <string_view>
#include <type_traits>

#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/char_string.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "core/assert.hpp"

namespace ns::inline utils
{
    /** Converts std string types to godot::String at compile time */
    template <typename TStr>
    struct GDStrConv
    {
        explicit constexpr GDStrConv(TStr&& s)
            : m_str{ std::move(s) }
        {
        }

        explicit operator godot::String()
            requires std::same_as<std::string>
        {
            return godot::String(m_str.c_str());
        }

        explicit operator godot::String()
            requires std::same_as<std::string_view>
        {
            return godot::String(m_str.data());
        }

        TStr m_str{};
    };

    /* Can cast between objects in the inheritance chain below a godot::Object */
    template <typename TOut, typename TIn>
        requires std::derived_from<std::remove_cvref_t<TIn>, godot::Object>
    constexpr inline TOut* gdcast(TIn* obj)
    {
        runtime_assert(obj != nullptr);
        auto ret{ godot::Object::cast_to<TOut>(obj) };
        runtime_assert(ret != nullptr);
        return ret;
    }

    template <typename TOut>
    inline auto to(const auto& in) -> TOut
    {
        return TOut(in);
    }

    template <>
    inline auto to(const godot::String& in) -> std::string
    {
        static_assert(std::is_same_v<godot::String, std::remove_cvref_t<decltype(in)>>);
        return std::string(in.ascii().ptr());
    }

    template <>
    inline auto to(const godot::String& in) -> std::string_view
    {
        static_assert(std::is_same_v<godot::String, std::remove_cvref_t<decltype(in)>>);
        return std::string_view(in.ascii().ptr());
    }

    template <>
    inline auto to(const godot::StringName& in) -> std::string
    {
        static_assert(std::is_same_v<godot::StringName, std::remove_cvref_t<decltype(in)>>);
        godot::String tmp(in);
        return std::string(tmp.ascii().ptr());
    }

    template <>
    inline auto to(const godot::StringName& in) -> std::string_view
    {
        static_assert(std::is_same_v<godot::StringName, std::remove_cvref_t<decltype(in)>>);
        godot::String tmp(in);
        return std::string_view(tmp.ascii().ptr());
    }
}
