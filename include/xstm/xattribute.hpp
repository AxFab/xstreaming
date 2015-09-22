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
#ifndef _XSTM_XATTRIBUTE_HPP
#define _XSTM_XATTRIBUTE_HPP 1
#include <nkit/collections.hpp>
#include "xobject.hpp"

namespace xstm {


class XAttribute : public XObject
{
public:
  /// Initializes a new instance of the XAttribute class by copy.
  explicit XAttribute(const XAttribute& attribut);
  /// Initializes a new instance of the XAttribute class from the
  /// specified name and value.
  explicit XAttribute(cstr name, cstr value = NULL);
  /// Removes this attribute from its parent element.
  XAttribute* remove();
  /// Returns the indented XML for this object.
  virtual cstr toString() const;

public:
  /// Gets the next attribute of the parent element.
  XAttribute* next() const { return next_; }
  /// Gets the previous attribute of the parent element.
  XAttribute* previous() const { return previous_; }
  /// Gets the value of this attribute.
  cstr name() const { return name_.c_str(); }
  /// Gets the value of this attribute.
  cstr value() const { return value_.c_str(); }
  /// Sets the value of this attribute.
  void setValue(cstr value) { value_ = XObject::FormatAttText(value); }

protected:
  NString name_;
  NString value_;
  XAttribute* next_;
  XAttribute* previous_;


// Attribute are part of element. An element handle the hierarchie of its
// attributes.
friend class XElement;
};


class XAttributeMap : public NMap<XAttribute>
{
public:
  virtual ~XAttributeMap();
  static XAttributeMap* Parse(cstr string);
  cstr string(cstr name) const; //NOLINT
};



}  // namespace xstm

#endif /* _XSTM_XATTRIBUTE_HPP */
