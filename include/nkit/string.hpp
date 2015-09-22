/*
  This file is part of the XStreaming library
  Copyright (c) 2015 Fabien Bavent

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
  DEALINGS IN THE SOFTWARE.
*/
#ifndef _NKIT_STRING_HPP
#define _NKIT_STRING_HPP 1
#include <string>

typedef const char* cstr;

#ifdef _WIN32
/// The memmem() function locates the first occurrence of the byte string
/// needle in the byte string haystack.
void *memmem(const void *haystack, size_t haystacklen, 
             const void *needle, size_t needlelen);
#endif

namespace nkit {

#define strict_expl
// #define strict_expl explicit

class NStrings;

/// Handle string written as UTF8. This class is based on std::string.
class NString : public std::string
{
public:  // Constructor & Public Methods
  /// Constructor
  NString();
  strict_expl NString(const std::string& value);
  strict_expl NString(cstr value);
  int indexOf(char ch);
  static NString Empty;

  std::string trim_start();
  std::string trim();
  bool ends_with(cstr string);
  std::string extract_until(char ch, int from = 0, char escape = '\0');
  operator cstr();
  operator std::string();
  void split(cstr delim, NStrings* strings);
  static NString Concat(cstr str, ...);
};


class NSecureString : private NString
{
  // TODO(axfab) Experiement for safe copy pardigme and safe delete!
};


}  // namespace nkit

#endif  /* _NKIT_STRING_HPP */
