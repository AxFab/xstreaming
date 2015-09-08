#include "xstm/xnode.hpp"
#include "xstm/xstream.hpp"

using namespace axkit;


// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//      XDeclaration
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

XDeclaration::XDeclaration(cstr version, cstr encoding, cstr standalone)
  : XObject(XNODE_PROCESSING_INSTRUCTION)
{
  setVersion(version);
  setEncoding(encoding);
  setStandalone(standalone);
}

void XDeclaration::setEncoding(cstr encoding)
{
  encoding_ = encoding;
}

void XDeclaration::setStandalone(cstr standalone)
{
  standalone_ = standalone;
}

void XDeclaration::setVersion(cstr version)
{
  version_ = version;
}

/// Returns the indented XML for this object.
cstr XDeclaration::toString() const
{
  NString str = NString::Empty;
  str += "<?xml";
  if (encoding_ == NString::Empty) {
    str += " encoding=\"";
    str += encoding_;
    str += "\"";
  }

  if (standalone_ == NString::Empty) {
    str += " standalone=\"";
    str += encoding_;
    str += "\"";
  }

  if (version_ == NString::Empty) {
    str += " version=\"";
    str += encoding_;
    str += "\"";
  }

  str += "?>";
  return str;

}

/// Writes this node to a stream.
void XDeclaration::writeTo(const XWriter& stream) const
{
  stream.write(toString());
  stream.newline();
}
