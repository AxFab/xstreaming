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
#include <nkit/string.hpp>
#include <nkit/collections.hpp>

namespace xstm {

class NDescr;
class NSchema;
class NEntity;
class NEnum;
class NDataKey;
class NProperty;


class NDescr
{
protected:
  NString name_;
  NString label_;
  NString labelSingular_;
  NString brief_;
  NString image_;

public:
  explicit NDescr(cstr name) { name_ = name; }
  void setLabel(cstr value) { label_ = value; }
  void setLabelSingular(cstr value) { labelSingular_ = value; }
  void setBrief(cstr value) { brief_ = value; }
  void setImage(cstr value) { image_ = value; }

  cstr name() const { return name_.c_str(); }
  cstr label() const { return label_.c_str(); }
  cstr labelSingular() const { return labelSingular_.c_str(); }
  cstr brief() const { return brief_.c_str(); }
  cstr image() const { return image_.c_str(); }
  // NString getSqlCreate();
};

class NSchema : public NDescr
{
private:
  NString namespace_;
  NList<NEntity> entities_;
  NList<NEnum> enums_;

public:
  explicit NSchema(cstr name, cstr nms = NULL);
  void addEntity(NEntity* e) { entities_.push_back(e); }
  void addEnum(NEnum* e) { enums_.push_back(e); }
  cstr nms() const { return namespace_.c_str(); }
  NEntity* entity(cstr name);
  NString getSqlCreate();
};

class NEntity : public NDescr
{
private:
  NString sqlTable_;
  NString format_;
  NSchema *schema_;
  NList<NDataKey> keys_;
  NList<NProperty> properties_;

public:
  explicit NEntity(cstr name, NSchema *schema = NULL);
  void inheritsFrom(NEntity *entity, int type = 0);
  void setSecurityCheck(cstr type, cstr expr);
  void setSqlTable(cstr name) { sqlTable_ = name; }
  void setFormat(cstr name) { format_ = name; }
  void addKey(NDataKey *key) { keys_.push_back(key); }
  void addProperty(NProperty*prop) { properties_.push_back(prop); }
  NString getSqlCreate();
  NSchema *schema() const { return schema_; }
};

class NEnum : public NDescr
{
private:
  NSchema *schema_;
  NMap<NString> values_;

public:
  explicit NEnum(cstr name, NSchema *schema = NULL);
  void addValue(cstr name, cstr value = NULL);
};

class NDataKey: public NDescr
{
private:
  NList<NString> fields_;
public:
  explicit NDataKey(cstr name): NDescr(name) {}
  void addField(cstr path) { fields_.push_back(new NString(path)); }
};

class NProperty : public NDescr
{
private:
  NString type_;
  NString mapping_;
  NString length_;
  NString defaultValue_;
  NString policy_;
  NString localizable_;
  NString sqlColumn_;
  NString sqlForeignkey_;
  NString sqlJoin_;
  NString expression_;

public:
  explicit NProperty(cstr name, cstr type) : NDescr(name) { type_ = type; }
  void setMapping(cstr value) { mapping_ = value; }
  void setLength(cstr value) { length_ = value; }
  void setDefaultValue(cstr value) { defaultValue_ = value; }
  void setPolicy(cstr value) { policy_ = value; }
  void setLocalizable(cstr value) { localizable_ = value; }
  void setSqlColumn(cstr value) { sqlColumn_ = value; }
  void setSqlForeignkey(cstr value) { sqlForeignkey_ = value; }
  void setSqlJoin(cstr value) { sqlJoin_ = value; }
  void setExpression(cstr value) { expression_ = value; }

  NString getSqlCreate();
};



}  // namespace xstm
