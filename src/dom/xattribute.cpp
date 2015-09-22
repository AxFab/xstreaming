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
#include "xstm/xattribute.hpp"

namespace xstm {

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//      XAttribute
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

/// Initializes a new instance of the XAttribute class by copy.
XAttribute::XAttribute(const XAttribute& attribut)
  : XObject(XNODE_ATTRIBUTE)
{
  this->name_ = XObject::FormatAttName(attribut.name());
  this->value_ = XObject::FormatAttText(attribut.value());
  this->next_ = NULL;
  this->previous_ = NULL;
}


/// Initializes a new instance of the XAttribute class from the
/// specified name and value.
XAttribute::XAttribute(cstr name, cstr value)
  : XObject(XNODE_ATTRIBUTE)
{
  this->name_ = XObject::FormatAttName(name);
  this->value_ = XObject::FormatAttText(value);
  this->next_ = NULL;
  this->previous_ = NULL;
}


/// Removes this attribute from its parent element.
XAttribute* XAttribute::remove()
{
  if (this->next_)
    this->next_->previous_ = this->previous_;

  if (this->previous_)
    this->previous_->next_ = this->next_;

  this->parent_ = NULL;
  return this;
}


/// Returns the indented XML for this object.
cstr XAttribute::toString() const
{
  NString str = NString::Empty;
  str += name_;
  str += "=\"";
  str += value_;
  str += "\"";
  return str;
}



// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//      XAttributeMap
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


XAttributeMap::~XAttributeMap()
{
  while (this->size()) {
    XAttribute *attr = this->begin()->second;
    this->erase(this->begin());
    delete attr;
  }
}

cstr XAttributeMap::string(cstr name) const
{
  XAttribute* attribute = find_key(name);
  if (attribute == NULL)
    return NString::Empty;
  return attribute->value();
}

XAttributeMap* XAttributeMap::Parse(cstr string)
{
  XAttributeMap *map = new XAttributeMap();
  NString str = string;
  NString key;
  NString value;

  for (;;) {
    str = str.trim_start();
    if (str == "")
      return map;

    key = str.extract_until('=');
    if (key == NString::Empty)
      return map;
    key[key.size()-1] = '\0';

    if (str.at(0) == '"')
      value = str.extract_until('"', 1, '\\');
    else if (str.at(0) == '\'')
      value = str.extract_until('\'', 1, '\\');
    value = value.substr(1, value.size() -2);
    XAttribute *attr = new XAttribute(key, value);
    (*map)[attr->name()] = attr;
  }
}


}  // namespace xstm

