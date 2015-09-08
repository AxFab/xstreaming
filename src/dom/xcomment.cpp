#include "xstm/xnode.hpp"
#include "xstm/xstream.hpp"

using namespace axkit;

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//      XComment
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


/// Initializes a new instance of XCData class.
XComment::XComment(cstr string)
  : XNode(XNODE_COMMENT)
{
  value_ = string;
}


/// Returns the indented XML for this object.
cstr XComment::toString() const
{
  NString string = NString::Empty;
  string += "<!--";
  string += value_;
  string += "-->";
  return value();
}


/// Writes this node to a stream.
void XComment::writeTo(const XWriter& stream) const
{
  stream.write("<!--");
  stream.writeAsIs(value());
  stream.write("-->");
  stream.newline();
}
