#include "xstm/xnode.hpp"
#include "xstm/xstream.hpp"

using namespace axkit;

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//      XText
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


/// Initializes a new instance of XText class.
XText::XText(cstr string)
  : XNode(XNODE_TEXT)
{
  value_ = XObject::FormatText(string);
}


/// Returns the indented XML for this object.
cstr XText::toString() const
{
  return value();
}


/// Writes this node to a stream.
void XText::writeTo(const XWriter& stream) const
{
  stream.write(value());
}

