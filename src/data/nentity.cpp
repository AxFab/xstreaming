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

namespace xstm {

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

}  // namespace xstm
