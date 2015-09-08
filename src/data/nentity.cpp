#include "xstm/nschema.hpp"

using namespace axkit;

NEntity::NEntity(cstr name, NSchema *schema)
  : NDescr(name)
{
  schema_ = schema;
  schema->addEntity(this);
}


void NEntity::setSecurityCheck(cstr type, cstr expr)
{
}


NString NEntity::getSqlCreate()
{
  NString str = NString::Empty;
  if (sqlTable_.empty())
    return str;

  str += "CREATE TABLE IF NOT EXISTS " + sqlTable_ + " (\n";
  
  for (NList<NProperty>::const_iterator it = properties_.begin(); 
      it != properties_.end(); ++it) {
    str += (*it)->getSqlCreate();

  }
  str += ");\n\n";
  return str;
}



NEnum::NEnum(cstr name, NSchema *schema)
  : NDescr(name)
{
  schema_ = schema;
  schema->addEnum(this);
}


void NEnum::addValue(cstr name, cstr value)
{
  if (!value)
    value = name;
  values_[name] = new NString(value);
}



NString NProperty::getSqlCreate()
{
  NString str = NString::Empty;
  if (!sqlForeignkey_.empty()) {
    str += "  foreign " + name_ + " !\n";
    return str;

  } else if (!sqlJoin_.empty()) {
    str += "  join " + name_ + " !\n";
    return str;
  }

  if (sqlColumn_.empty())
    sqlColumn_ = type_.substr(0, 1) + name_; 
  
  str += "  " + sqlColumn_ + " " + type_ + ",\n";
  return str;
}
