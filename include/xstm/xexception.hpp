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
#ifndef _XSTM_XEXCEPTION_HPP
#define _XSTM_XEXCEPTION_HPP 1
#include <exception>
#include "nkit/string.hpp"

namespace xstm {


class XException : public std::exception
{
public:
  explicit XException(cstr msg) { msg_ = NString(msg); }
  virtual ~XException() throw() {}
  virtual const char* what() throw() { return msg_.c_str(); }
private:
  NString msg_;
};


class XNullParamException : public XException
{
public:
  XNullParamException()
    : XException("A non-null parameter was unset.") {}
  explicit XNullParamException(cstr param)
    : XException(NString::Concat("The parameter '", param,
      "' can't be null.", NULL).c_str()) {}
};


class XNotImplementedException : public XException
{
public:
  XNotImplementedException()
    : XException("The function invoked is not implemented.") {}
  explicit XNotImplementedException(cstr func)
    : XException(NString::Concat("The function '", func,
      "' is not implemented.", NULL).c_str()) {}
};


}  // namespace xstm

#endif /* _XSTM_XEXCEPTION_HPP */
