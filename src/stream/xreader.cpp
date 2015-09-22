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
#include <fstream>
#include <cstring>
#include "xstm/xstream.hpp"
#include "xstm/xattribute.hpp"
#include "xstm/xexception.hpp"

namespace xstm {



XReader::XReader(std::istream* stream)
{
  buffer_ = new XStream(stream);
  document_ = new XDocument();
  cursorStack_ = new NStack<XContainer>();
  cursorStack_->push(document_);
}

XReader::XReader(cstr url)
{
  std::istream* stream = new std::ifstream(url, std::ifstream::in);
  buffer_ = new XStream(stream);
  document_ = new XDocument();
  cursorStack_ = new NStack<XContainer>();
  cursorStack_->push(document_);
}

XReader::~XReader()
{
  while (cursorStack_->size())
    cursorStack_->pop();
  close();
  delete cursorStack_;
}

void XReader::close()
{
  if (buffer_) {
    delete buffer_;
    buffer_ = NULL;
  }
}

void XReader::dispose()
{
  close();
  if (document_) {
    delete document_;
    document_ = NULL;
  }
}


XText* XReader::readText() const
{
  char tmp[5];
  NString string = NString::Empty;
  for (;;) {
    int k = buffer_->indexOf("<");
    if (k < 0) {
      k = buffer_->available();
      string.append(buffer_->string(), k);
      buffer_->read(k);
      if (!buffer_->peek(tmp, 1)) {
        // End of the file!
        string.append(tmp);
        break;
      }
    } else {
      string.append(buffer_->string(), k);
      buffer_->read(k);
      if (!buffer_->peek(tmp, 5)) {
        // End of the file!
        string.append(tmp);
        break;
      } else if (tmp[1] == '?' || tmp[1] == '!' || tmp[1] == '[' ||
          tmp[1] == '/' || isalpha(tmp[1])) {  // TODO(axfab) UTF8_alpha
        break;
      }
      // TODO(axfab) Push Warning
      string.append(tmp, 1);
      buffer_->read(1);
    }
  }

  XText *text = new XText(string);
  NString val = NString(text->value()).trim();
  if (val == "") {
    // try to avoid this one! (Concept issue XText may process the string !?)
    delete text;
    return NULL;
  }
  cursorStack_->top()->add(text);
  return text;
}

XDeclaration* XReader::readDeclaration() const
{
  NString str = NString::Empty;
  int k;
  for (;;) {
    k = buffer_->indexOf("?>");
    if (k < 0) {
      k = buffer_->available();
      str.append(buffer_->string(), k);
      buffer_->read(k);

    } else {
      str.append(buffer_->string(), k + 2);
      buffer_->read(k + 2);

      if (memcmp(str.c_str(), "<?xml ", 6) == 0) {
        str = NString(str.substr(6, str.size()-8).c_str());
        XAttributeMap *map = XAttributeMap::Parse(str);
        XDeclaration *decl = new XDeclaration(map->string("version"),
          map->string("encoding"), map->string("standalone"));
        delete map;
        return decl;
      }

      throw new XNotImplementedException();
    }
  }
}

XComment* XReader::readComment() const
{
  NString str = NString::Empty;
  int k;
  for (;;) {
    k = buffer_->indexOf("-->");
    if (k < 0) {
      k = buffer_->available();
      str.append(buffer_->string(), k);
      buffer_->read(k);
    } else {
      str.append(buffer_->string(), k + 3);
      buffer_->read(k + 3);
      XComment *node = new XComment(str);
      cursorStack_->top()->add(node);
      return node;
    }
  }
}

XCData* XReader::readCData() const
{
  NString str = NString::Empty;
  int k;
  for (;;) {
    k = buffer_->indexOf("]]>");
    if (k < 0) {
      k = buffer_->available();
      str.append(buffer_->string(), k);
      buffer_->read(k);
    } else {
      str.append(buffer_->string(), k + 3);
      buffer_->read(k + 3);
      XCData *node = new XCData(str);
      cursorStack_->top()->add(node);
      return node;
    }
  }
}

XElement* XReader::readElement() const
{
  NString str = NString::Empty;
  int k;
  for (;;) {
    k = buffer_->indexOf(">");
    if (k < 0) {
      k = buffer_->available();
      str.append(buffer_->string(), k);
      buffer_->read(k);
    } else {
      str.append(buffer_->string(), k + 1);
      buffer_->read(k + 1);
      bool open = true;
      if (str.ends_with("/>")) {
        str = str.substr(1, str.size()-3);
        open = false;
      } else {
        str = str.substr(1, str.size()-2);
      }

      NString tag;
      if (str.indexOf(' ') > 0) {
        tag = NString(str.extract_until(' ')).trim();
      } else {
        tag = str;
        str = NString::Empty;
      }
      // TODO(axfab) remove ending (/)> and put a warning if Attribute
      // parsing doesn't finish clean!
      XAttributeMap *map = XAttributeMap::Parse(str);
      // If we end with /> we close the stuff!
      XElement *element = new XElement(tag, map);
      cursorStack_->top()->add(element);
      if (open)
        cursorStack_->push(element);
      else
        didClose_ = true;
      return element;
    }
  }
}

XElement* XReader::readClosing() const
{
  NString str = NString::Empty;
  int k;
  for (;;) {
    k = buffer_->indexOf(">");
    if (k < 0) {
      k = buffer_->available();
      str.append(buffer_->string(), k);
      buffer_->read(k);
    } else {
      str.append(buffer_->string(), k + 1);
      buffer_->read(k + 1);
      str = NString(str.substr(2, str.size()-3)).trim();

      XContainer *cursor = cursorStack_->top();
      XElement *element = static_cast<XElement*>(cursor);
      if (str != element->name()) {
        // TODO(axfab) Warning
        /* Open <property...> at l.29 should not be closed by </entity> at
        l.34 */
        std::cout << "Warning: closing tag doesn't match: '" << str
          << "' vs '" << element->name() << "'" << std::endl;
      }
      cursorStack_->pop();
      return element;
    }
  }
}

XNode* XReader::read() const
{
  char str[10];
  didClose_ = false;

  for (;;) {
    if (!buffer_->peek(str, 8))
      return NULL;  // TODO(axfab) Check that we don't have anything else!!!
    if (str[0] != '<') {
      XNode* txt = readText();
      if (!txt)
        continue;
      else
        return txt;
    }
    if (str[1] == '?') {
      XDeclaration* decl = readDeclaration();
      delete decl;  // TODO(axfab) include on Document!!!
      continue;
    }
    if (str[1] == '/') {
      return readClosing();
      continue;
    }
    if (memcmp(&str[1], "!--", 3) == 0)
      return readComment();
    if (memcmp(&str[1], "[CDATA[", 7) == 0)
      return readCData();
    if (isalpha(str[1]))
      return readElement();
    return NULL;  // TODO(axfab) This one is an error
  }
}


int XReader::readTheString(XNode* current, NString& content)
{
  XNode* node;
  NString str = NString::Empty;
  do {
    node = read();
    if (!node)
      return -1;
    if (node->nodeType() == XNODE_TEXT)
      str += static_cast<XText*>(node)->value();
  } while (node != current);


  content.assign(str);
  node->parent()->removeNodes();
  return 0;
}

}  // namespace xstm

