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
#ifndef _XSTM_XELEMENT_HPP
#define _XSTM_XELEMENT_HPP 1
#include "xcontainer.hpp"

namespace xstm {

class XAttributeMap;

class XName
{
private:
  NString name_;
  NString prefix_;
  NString namespace_;
public:
  operator NString()
  {
    NString str = NString::Empty;
    str += NString(namespace_) + NString(name_);
    return str;
  }
};


/// This abstract object define the base of all items related
/// to XML node tree.
class XElement : public XContainer
{
public:  // Constructors & Public Methods
  ///
  explicit XElement(cstr name, XAttributeMap *map = NULL);
  virtual ~XElement();
  /// Returns the indented XML for this object.
  virtual cstr toString() const;

  ///
  NString attributeString(cstr name) const;
  ///
  bool attributeBool(cstr name, bool *value) const;

public:  // Public Accessors
  NString name() { return name_; }

public:
  static XElement* Load(cstr url);

protected:  // Protected Data-Members
  NString name_;
  XAttributeMap *attributes_;
};

}  // namespace xstm

#endif /* _XSTM_XELEMENT_HPP */
