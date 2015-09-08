#include "xstm/xstream.hpp"
#include <iostream>
#include <cstring>

using namespace axkit;
using namespace std;

XStream::XStream(istream* stream)
  : encoding_(XStream::detectEncoding(stream))
{
  stream_ = stream;
  capacity_ = 512;
  buffer_ = new char[capacity_];
  size_ = 0;
  position_ = 0;
  inval();
}

XStream::~XStream()
{
  if (stream_)
    delete stream_;
  delete[] buffer_;
}

bool isUTF8Char(unsigned char *str, int lg)
{
  int k = 0;
  int c = str[0];
  while (c & 0x80) {
    c = c << 1;
    k++;
  }

  if (k == 0)
    return true;
  else if (k < 2 || k > 6)
    return false;

  k = max(k, lg);
  for (int i = 1; i < k; ++i) {
    if ((str[i] & 0xC0) != 0x80)
      return false;
  }

  return true;
}

const NEncoding& XStream::detectEncoding(istream* stream)
{
  unsigned char buf[16];
  stream->seekg(0);
  stream->read(reinterpret_cast<char*>(buf), 16);
  if (buf[0] == 0xef && buf[1] == 0xbb && buf[2] == 0xbf) {// UTF8 BOM
    stream->seekg(3);
    return NEncoding::UTF8();
  } else if (buf[0] == 0xFE && buf[1] == 0xFF) {
    stream->seekg(2);
    return NEncoding::UTF16_BE();
  } else if (buf[0] == 0xFF && buf[1] == 0xFE) {
    stream->seekg(2);
    return NEncoding::UTF16_LE();
  } else {
    // ASCII, UTF-8 or Latin1
    stream->seekg(0);
    for (int i=0; i<16; ++i) {
      if (buf[i] > 0x80) {
        if (isUTF8Char(&buf[i], 16))
          return NEncoding::UTF8();
        else
          return NEncoding::Latin1();
      }
    }

    return NEncoding::UTF8(); // Default to UTF8 !?
  }
}

int XStream::indexOf(const char *str)
{
  char *s = string();
  char* p = (char*)memmem(s, available(), str, strlen(str));
  if (p == NULL)
    return -1;
  return p - s;
}

//int XStream::indexOf(int c)
//{
//}


void XStream::inval()
{
  int avail = available();
  if (avail > 0)
    memmove(buffer_, &buffer_[position_], avail);
  position_ = 0;
  size_ = avail;
  int read = encoding_.readStream(stream_, &buffer_[size_], capacity_ - size_);
  size_ += read;
  if (read == 0) {
    read++;
  }

}

bool XStream::peek(char* str, int lg)
{
  int avail = available();
  if (avail > lg) {
    memcpy(str, string(), lg);
    return true;
  }

  return false;
}

void XStream::read(int sz)
{
  position_ += sz;
  if (available() < 20)
    inval();
}

char* XStream::string() const
{
  return &buffer_[position_];
}

int XStream::available() const
{
  return size_ - position_;
}




void XWriter::write(cstr string) const
{
  throw new XNotImplementedException();
}

void XWriter::writeAsIs(cstr string) const
{
  throw new XNotImplementedException();
}

void XWriter::newline() const
{
  throw new XNotImplementedException();
}


cstr XObject::FormatAttName(cstr value)
{
  return value;
}

cstr XObject::FormatAttText(cstr value)
{
  return value;
}

cstr XObject::FormatName(cstr value)
{
  return value;
}

cstr XObject::FormatText(cstr value)
{
  return value;
}

