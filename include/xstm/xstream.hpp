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
#ifndef _XSTM_XSTREAM_HPP
#define _XSTM_XSTREAM_HPP 1
#include "xdocument.hpp"
#include "xdeclaration.hpp"
#include "xelement.hpp"
#include "xnode.hpp"
#include "xtext.hpp"

namespace xstm {

class XStream
{
private:
  std::istream* stream_;
  char* buffer_;
  int capacity_;
  int size_;
  int position_;
  const NEncoding &encoding_;

public:
  explicit XStream(std::istream* stream);
  ~XStream();
  int indexOf(const char* str);
  void inval();
  bool peek(char* str, int lg);
  void read(int sz);

  char* string() const;
  int available() const;
private:
  void fill();
  static const NEncoding& detectEncoding(std::istream* stream);
};

class XReader
{
private:
  XStream* buffer_;
  XContainer* cursor_;
  XDocument *document_;
  mutable bool didClose_;
  mutable NStack<XContainer> *cursorStack_;

public:
  explicit XReader(std::istream* stream);
  explicit XReader(XStream* stream);
  explicit XReader(cstr url);
  ~XReader();
  void close();
  /// Close the stream and destroy the resulting document at the same time.
  void dispose();
  XNode* read() const;
  XDocument * document() const { return document_; }
  bool didClose() const { return didClose_; }
  int readTheString(XNode* current, NString& content);
private:
  XText* readText() const;
  XDeclaration* readDeclaration() const;
  XComment* readComment() const;
  XCData* readCData() const;
  XElement* readElement() const;
  XElement* readClosing() const;
};

class XWriter
{
public:
  void write(cstr string) const;
  void writeAsIs(cstr string) const;
  void newline() const;
};

}  // namespace xstm

#endif /* _XSTM_XSTREAM_HPP */

