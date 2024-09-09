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

#include <cstdio>
#include <iostream>

#include <godot_cpp/core/error_macros.hpp>

#ifndef NDEBUG
  //
  // In debug mode, checks the passed in condition and outputs
  // detailed information to stederr, including a custom error
  // message when the condition evaluates to false.
  //
  #define assertion(condition, message)                                             \
      do                                                                            \
      {                                                                             \
          if (!(condition)) [[unlikely]]                                            \
          {                                                                         \
              ::godot::_err_print_error(__FUNCTION__, __FILE__, __LINE__,           \
                                        message " => condition: (" #condition ")"); \
              ::godot::_err_flush_stdout();                                         \
              GENERATE_TRAP();                                                      \
          }                                                                         \
      }                                                                             \
      while (false)

  #define error_msg(message)                                                    \
      do                                                                        \
      {                                                                         \
          ::godot::_err_print_error(__FUNCTION__, __FILE__, __LINE__, message); \
          ::godot::_err_flush_stdout();                                         \
          GENERATE_TRAP();                                                      \
      }                                                                         \
      while (false)

  #define runtime_assert(condition) assertion(condition, "validation check failed")

#else
//
// In release mode the macro does nothing ((void)0), including
// the execution of the condition so don't define the expression
// as anything that would be considered program logics.
//
  #define assertion(condition, message) static_cast<void>(0)
  #define error_msg(message)            static_cast<void>(0)
  #define runtime_assert(condition)     static_cast<void>(0)
#endif
