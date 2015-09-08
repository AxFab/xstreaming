
#ifndef _AX_DATA_XSTREAM_HPP 
#define _AX_DATA_XSTREAM_HPP 1
#include "axkit.hpp"
#include "xnode.hpp"

namespace axkit {

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
  XStream(std::istream* stream);
  ~XStream();
  int indexOf(const char*);
  void inval();
  bool peek(char*, int);
  void read(int);

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
  XReader(std::istream* stream);
  XReader(XStream* stream);
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

} // namespace axkit

#endif /* _AX_DATA_XSTREAM_HPP */

