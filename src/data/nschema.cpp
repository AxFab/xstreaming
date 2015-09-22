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
#include "xstm/nschema.hpp"
#include <cstring>

namespace xstm {

NSchema::NSchema(cstr name, cstr nms)
  : NDescr(name)
{
  namespace_ = nms;
}

NEntity* NSchema::entity(cstr name)
{
  for (NList<NEntity>::const_iterator it = entities_.begin();
      it != entities_.end(); ++it) {
    if (strcmp((*it)->name(), name) == 0)
      return *it;
  }
  return NULL;
}

NString NSchema::getSqlCreate()
{
  NString str = NString::Empty;


  for (NList<NEntity>::const_iterator it = entities_.begin();
      it != entities_.end(); ++it) {
    str += (*it)->getSqlCreate();
  }

  return str;
}

}  // namespace xstm

