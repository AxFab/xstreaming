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
#ifndef _NKIT_ENCODING_HPP
#define _NKIT_ENCODING_HPP 1
#include <iostream>
#include "nkit/string.hpp"

namespace nkit {

#ifndef __abstract
/// Add a macro (often empty) to signal an abstract class
# define __abstract
#endif


__abstract class NEncoding
{
public:  // Static Accessors
  static const NEncoding &UTF8();
  static const NEncoding &Latin1();
  static const NEncoding &UTF16_LE();
  static const NEncoding &UTF16_BE();

public:  // Public methods
  virtual int readStream(std::istream* stream, char* buf, int cap) const = 0;
  cstr name() const { return name_.c_str(); }

protected:  // Protected methods
  /// Protected constructor usable only for a new encoding subclass
  NEncoding(cstr name);

private:
  NString name_;
};


}  // namespace nkit

#endif  /* _NKIT_ENCODING_HPP */
