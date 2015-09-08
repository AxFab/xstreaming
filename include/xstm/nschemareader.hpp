#pragma once

#include "nschema.hpp"
#include "xstream.hpp"

namespace axkit {

class NSchemaReader
{
private:
  XReader *reader_;
  NSchema *schema_;

public:
  /// Initializes a new instance of NSchemaReader class from a XReader object.
  NSchemaReader(XReader *reader);
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

} // namespace axkit
