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
#ifndef _XSTM_XTEXT_HPP
#define _XSTM_XTEXT_HPP 1
#include "xstm/xnode.hpp"

namespace xstm {


class XText : public XNode
{
protected:
  NString value_;

public:
  /// Initializes a new instance of XText class.
  explicit XText(cstr string);
  /// Returns the indented XML for this object.
  virtual cstr toString() const;

public:
  /// Gets the value of this node.
  cstr value() const { return value_.c_str(); }
  /// Sets the value of this node.
  void setValue(cstr value) { value_ = XObject::FormatText(value); }
};

class XCData : public XNode
{
private:
  NString value_;

public:
  /// Initializes a new instance of XText class.
  explicit XCData(cstr string);
  /// Returns the indented XML for this object.
  virtual cstr toString() const;

public:
  /// Gets the value of this node.
  cstr value() const { return value_.c_str(); }
  /// Sets the value of this node.
  void setValue(cstr value) { value_ = value; }
};

class XComment : public XNode
{
private:
  NString value_;

public:
  /// Initializes a new instance of XComment class.
  explicit XComment(cstr string);
  /// Returns the indented XML for this object.
  virtual cstr toString() const;

public:
  /// Gets the value of this node.
  cstr value() const { return value_.c_str(); }
  /// Sets the value of this node.
  void setValue(cstr value) { value_ = value; }
};



}  // namespace xstm

#endif /* _XSTM_XTEXT_HPP */
