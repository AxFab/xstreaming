#include "xstm/xnode.hpp"

using namespace axkit;


XDocument::XDocument()
  : XContainer(XNODE_DOCUMENT)
{
}


/// Returns the indented XML for this object.
cstr XDocument::toString() const
{
  throw new XNotImplementedException();
}


/// Writes this node to a stream.
void XDocument::writeTo(const XWriter& stream) const
{
  throw new XNotImplementedException();
}



