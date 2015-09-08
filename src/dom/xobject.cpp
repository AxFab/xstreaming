
#include "xstm/xnode.hpp"

using namespace axkit;

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

