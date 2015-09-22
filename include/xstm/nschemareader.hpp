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
#pragma once

#include "nschema.hpp"
#include "xstream.hpp"

namespace xstm {

class NSchemaReader
{
private:
  XReader *reader_;
  NSchema *schema_;

public:
  /// Initializes a new instance of NSchemaReader class from a XReader object.
  explicit NSchemaReader(XReader *reader);
  /// Destructor, doens't handle the resulting schema.
  ~NSchemaReader();
  /// Destroy remaining resources.
  void close();
  /// Destroy every resources including the resulting schema.
  void dispose();
  /// Start the reading process and create the resulting schema.
  NSchema* read();
  /// Gets the resulting schema.
  NSchema *schema() const { return schema_; }
  /// Gets the schema matching those.
  NSchema *schema(cstr nms, cstr name) const;
private:
  int readEntity(XElement* ndEntity);
  int readEnum(XElement* ndEnum);
  int readCommonProperties(XElement* ndEntity, NDescr* item);

  int readKey(XElement* ndKey, NEntity *entity);
  int readSysFilter(XElement* ndKey, NEntity *entity);
  int readProperty(XElement* ndKey, NEntity *entity);

  void extendEntity(NEntity *entity, cstr schema);
};

}  // namespace xstm
