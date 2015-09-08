#include "xstm/xnode.hpp"
#include <iostream>

using namespace axkit;


XElement::XElement(cstr name, XAttributeMap *map)
  : XContainer(XNODE_ELEMENT)
{
  name_ = name;
  attributes_ = map;
}

XElement::~XElement() 
{
  delete attributes_;
}

/// Returns the indented XML for this object.
cstr XElement::toString() const
{
  throw new XNotImplementedException();
}

/// Writes this node to a stream.
void XElement::writeTo(const XWriter& stream) const
{
  throw new XNotImplementedException();
}
