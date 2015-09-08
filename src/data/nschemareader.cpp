#include "xstm/nschemareader.hpp"
#include <cstring>

using namespace axkit;

NSchemaReader::NSchemaReader(XReader *reader)
{
  reader_ = reader;
}

NSchemaReader::~NSchemaReader()
{
  close();
}

void NSchemaReader::close()
{
  if (reader_) {
    reader_->dispose();
    delete reader_;
    reader_ = NULL;
  }
}

void NSchemaReader::dispose()
{
  close();
  if (schema_) {
    delete schema_;
    schema_ = NULL;
  }
}

int NSchemaReader::readCommonProperties(XElement* ndEntity, NDescr* item)
{
  NString name = ndEntity->name();
  NString str;
  if (reader_->readTheString(ndEntity, str))
    return -1;
  
  if (name == "label")
    item->setLabel(str);
  else if (name == "labelSingular")
    item->setLabelSingular(str);
  else if (name == "brief")
    item->setBrief(str);
  else if (name == "image")
    item->setImage(str);

  return 0;
}

void NSchemaReader::extendEntity(NEntity *entity, cstr type)
{
  NProperty *prop = new NProperty("", type);
  prop->setMapping("element");
  prop->setSqlColumn("*");
  entity->addProperty(prop);
}

int NSchemaReader::readKey(XElement* ndKey, NEntity *entity)
{
  XNode *current = static_cast<XNode*>(ndKey);
  NDataKey *datakey = new NDataKey(ndKey->attributeString("name"));
  NString uniq = ndKey->attributeString("uniq");
  NString primary = ndKey->attributeString("sql-primary");
  entity->addKey(datakey);
  for (;;) {
    XNode *node = reader_->read();
    if (node == current) {
      node->parent()->removeNodes();
      return 0;
    }
    
    if (node->nodeType() == XNODE_TEXT)
      return -1;
    if (node->nodeType() != XNODE_ELEMENT)
      continue;
    
    XElement* ndElm = reinterpret_cast<XElement*>(node);
    if (ndElm->name() == "keyField") {
      // TODO Get value and other attributes!
      NString str;
      if (reader_->readTheString(ndElm, str))
        return -1;
      datakey->addField(str);
      
    } else
      readCommonProperties(ndElm, datakey);
  }
}

int NSchemaReader::readSysFilter(XElement* ndFilter, NEntity *entity)
{
  XNode *current = static_cast<XNode*>(ndFilter);
  NString name = ndFilter->attributeString("name");
  NString type = ndFilter->attributeString("type");
  NString expr;
  if (reader_->readTheString(ndFilter, expr))
    return -1;

  entity->setSecurityCheck(type, expr);
  return 0;
}

int NSchemaReader::readProperty(XElement* ndProp, NEntity *entity)
{
  XNode *current = static_cast<XNode*>(ndProp);
  NProperty *prop = new NProperty(ndProp->attributeString("name"), ndProp->attributeString("type"));
  prop->setMapping(ndProp->attributeString("mapping"));
  prop->setLength(ndProp->attributeString("length"));
  prop->setDefaultValue(ndProp->attributeString("default"));
  prop->setPolicy(ndProp->attributeString("policy"));
  prop->setLocalizable(ndProp->attributeString("localizable"));
  prop->setSqlColumn(ndProp->attributeString("sql-column"));
  prop->setSqlForeignkey(ndProp->attributeString("sql-foreignkey"));
  prop->setSqlJoin(ndProp->attributeString("sql-join"));
  entity->addProperty(prop);

  if (reader_->didClose())
    return 0;

  for (;;) {
    XNode *node = reader_->read();
    if (node == current) {
      node->parent()->removeNodes();
      return 0;
    }
    
    if (node->nodeType() == XNODE_TEXT)
      return -1;
    if (node->nodeType() != XNODE_ELEMENT)
      continue;
    
    XElement* ndElm = reinterpret_cast<XElement*>(node);
    if (ndElm->name() == "expression") {
      NString str;
      if (reader_->readTheString(ndElm, str))
        return -1;
      prop->setExpression(str);
    
    } else
      readCommonProperties(ndElm, prop);
  }
}

int NSchemaReader::readEntity(XElement* ndEntity)
{
  XNode *current = static_cast<XNode*>(ndEntity);
  NEntity *entity = new NEntity(ndEntity->attributeString("name"), schema_);
  entity->setSqlTable(ndEntity->attributeString("sql-table"));

  for (;;) {
    XNode *node = reader_->read();
    if (node == current) {
      node->parent()->removeNodes();
      return 0;
    }
    
    if (node->nodeType() == XNODE_TEXT)
      return -1;
    if (node->nodeType() != XNODE_ELEMENT)
      continue;
    
    XElement* ndElm = reinterpret_cast<XElement*>(node);
    if (ndElm->name() == "format") {
      NString str;
      if (reader_->readTheString(ndElm, str))
        return -1;
      entity->setFormat(str);
    
    } else if (ndElm->name() == "extend") {
      NString str;
      if (reader_->readTheString(ndElm, str))
        return -1;
      extendEntity(entity, str);
      
    } else if (ndElm->name() == "key") {
      if (readKey(ndElm, entity))
        return -1;
      
    } else if (ndElm->name() == "sysFilter") {
      if (readSysFilter(ndElm, entity))
        return -1;
      
    } else if (ndElm->name() == "property") {
      if (readProperty(ndElm, entity))
        return -1;

    } else
      readCommonProperties(ndElm, entity);
  }

}

int NSchemaReader::readEnum(XElement* ndEnum)
{
  XNode *current = static_cast<XNode*>(ndEnum);
  NEnum *entity = new NEnum(ndEnum->attributeString("name"), schema_);
  for (;;) {
    XNode *node = reader_->read();
    if (node == current) {
      node->parent()->removeNodes();
      return 0;
    }
    
    if (node->nodeType() == XNODE_TEXT)
      return -1;
    if (node->nodeType() != XNODE_ELEMENT)
      continue;
    
    XElement* ndElm = reinterpret_cast<XElement*>(node);
    if (ndElm->name() == "field") {
      // TODO Get value and other attributes!
      NString str;
      if (reader_->readTheString(ndElm, str))
        return -1;
      entity->addValue(str);
      
    } else
      readCommonProperties(ndElm, entity);
  }
}


NSchema* NSchemaReader::read()
{
  // We should read a schema!
  XNode* current = reader_->read();
  if (current->nodeType() != XNODE_ELEMENT)
    return NULL;
  XElement* ndSchema = reinterpret_cast<XElement*>(current);
  if (ndSchema->name() != "schema")
    return NULL;

  schema_ = new NSchema(ndSchema->attributeString("name"), ndSchema->attributeString("namespace"));
  // TODO -- the schema also have a library="yes/no/true/false" attribute!
  // A schema can be composed of common items, require and entity element!
  for (;;) {
    XNode *node = reader_->read();
    if (node == current) {
      reader_->dispose();
      return schema_;
    }
    
    if (node->nodeType() == XNODE_TEXT)
      return NULL;
    if (node->nodeType() != XNODE_ELEMENT)
      continue;
    
    XElement* ndElm = reinterpret_cast<XElement*>(node);
    if (ndElm->name() == "require") {
      return NULL; // NOT IMPLEMENTED
      
    } else if (ndElm->name() == "entity") {
      if (readEntity(ndElm))
        return NULL;

    } else if (ndElm->name() == "enum") {
      if (readEnum(ndElm))
        return NULL;

    } else
      readCommonProperties(ndElm, schema_);
  }
}


NSchema *NSchemaReader::schema(cstr nms, cstr name) const 
{ 
  if (strcmp(schema_->nms(), nms) == 0 &&
    strcmp(schema_->name(), name) == 0 )
    return schema_; 
  return NULL;
}

