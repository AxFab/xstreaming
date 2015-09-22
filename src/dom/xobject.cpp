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
#include "xstm/xobject.hpp"
#include "xstm/xelement.hpp"

namespace xstm {

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//      XObject
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

/// Initializes a new instance of XObject class.
XObject::XObject(XNodeType type)
{
  nodeType_ = type;
  document_ = NULL;
  parent_ = NULL;
}


/// Sets the parent element of this object.
void XObject::setParent(XElement *parent)
{
  parent_ = parent;
  setDocument(parent->document_);
}


/// Sets the parent element of this object.
void XObject::setDocument(XDocument *doc)
{
  document_ = doc;
}

cstr XObject::FormatAttName(cstr value)
{
  return value;
}

cstr XObject::FormatAttText(cstr value)
{
  return value;
}

cstr XObject::FormatName(cstr value)
{
  return value;
}

cstr XObject::FormatText(cstr value)
{
  return value;
}


}  // namespace xstm
