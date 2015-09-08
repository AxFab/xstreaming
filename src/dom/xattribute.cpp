#include "xstm/xnode.hpp"
#include "xstm/xstream.hpp"

using namespace axkit;

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


/// Writes this node to a stream.
void XAttribute::writeTo(const XWriter& stream) const
{
  stream.write(this->toString());
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
