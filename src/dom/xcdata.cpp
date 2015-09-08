#include "xstm/xnode.hpp"
#include "xstm/xstream.hpp"

using namespace axkit;

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//      XCData
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

/// Initializes a new instance of XCData class.
XCData::XCData(cstr string)
  : XNode(XNODE_CDATA_SECTION)
{
  value_ = string;
}


/// Returns the indented XML for this object.
cstr XCData::toString() const
{
  NString string = NString::Empty;
  string += "<[CDATA[";
  string += value();
  string += "]]>";
  return string;
}


/// Writes this node to a stream.
void XCData::writeTo(const XWriter& stream) const
{
  stream.write("<[CDATA[");
  stream.newline();
  stream.writeAsIs(value());
  stream.newline();
  stream.write("]]>");
  stream.newline();
}

