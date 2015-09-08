#include "xstm/axkit.hpp"
#include <fstream>
#include <cstring>

using namespace axkit;

namespace axkit {

class NEncodingUTF8 : public NEncoding
{
public:
  NEncodingUTF8() : NEncoding("UTF-8") {};
  virtual int readStream(std::istream* stream, char* buf, int cap) const;
};

class NEncodingLatin1 : public NEncoding
{
public:
  NEncodingLatin1() : NEncoding("ISO-8859-1") {};
  virtual int readStream(std::istream* stream, char* buf, int cap) const;
};

class NEncodingASCII : public NEncoding
{
public:
  NEncodingASCII() : NEncoding("ASCII") {};
  virtual int readStream(std::istream* stream, char* buf, int cap) const;
};

} // namespace axkit

NEncoding::NEncoding(cstr name)
{
  name_ = name;
}

const NEncoding &NEncoding::UTF8()
{
  static NEncodingUTF8 encoding;
  return encoding;
}

const NEncoding &NEncoding::Latin1()
{
  static NEncodingLatin1 encoding;
  return encoding;
}

const NEncoding &NEncoding::UTF16_LE()
{
  static NEncodingASCII encoding;
  return encoding;
}

const NEncoding &NEncoding::UTF16_BE()
{
  static NEncodingASCII encoding;
  return encoding;
}


int NEncodingUTF8::readStream(std::istream* stream, char* pstr, int cap) const
{
  unsigned char ch[6];
  char* sv = pstr;
  static unsigned short charsetUp[256] = { 0
  };

  while (pstr - sv + 6 < cap) {
    if (stream->eof())
      return pstr - sv;
    stream->read((char*)ch, 1);
    if (*ch == '\r') {
      stream->read((char*)&ch[1], 1);
      if (ch[1] == '\n')
        *(pstr++) = ch[1];
      else
        stream->unget();

    } else if (*ch < 0x80) {
      *(pstr++) = *ch;

    } else if ((*ch & 0xC0) == 0x80) {
      *(pstr++) = 0x7f; // Invalid character !
      
    } else if ((*ch & 0xE0) == 0xC0) {
      stream->read((char*)&ch[1], 1);
      if ((ch[1] & 0xC0) == 0x80) {
        memcpy(pstr, ch, 2);
        pstr += 2;
      } else {
        *(pstr++) = 0x7f; // Invalid character !
      }
    
    } else if ((*ch & 0xF0) == 0xE0) {
      stream->read((char*)&ch[1], 2);
      if ((ch[1] & 0xC0) == 0x80 && (ch[2] & 0xC0) == 0x80) {
        memcpy(pstr, ch, 3);
        pstr += 3;
      } else {
        *(pstr++) = 0x7f; // Invalid character !
      }
    
    } else if ((*ch & 0xF8) == 0xF0) {
      stream->read((char*)&ch[1], 3);
      if ((ch[1] & 0xC0) == 0x80 && (ch[2] & 0xC0) == 0x80 && (ch[3] & 0xC0) == 0x80) {
        memcpy(pstr, ch, 4);
        pstr += 4;
      } else {
        *(pstr++) = 0x7f; // Invalid character !
      }
    
    } else if ((*ch & 0xFC) == 0xF8) {
      stream->read((char*)&ch[1], 4);
      if ((ch[1] & 0xC0) == 0x80 && (ch[2] & 0xC0) == 0x80 && (ch[3] & 0xC0) == 0x80 && (ch[4] & 0xC0) == 0x80) {
        memcpy(pstr, ch, 5);
        pstr += 5;
      } else {
        *(pstr++) = 0x7f; // Invalid character !
      }
    
    } else if ((*ch & 0xFE) == 0xFC) {
      stream->read((char*)&ch[1], 5);
      if ((ch[1] & 0xC0) == 0x80 && (ch[2] & 0xC0) == 0x80 && (ch[3] & 0xC0) == 0x80 && (ch[4] & 0xC0) == 0x80 && (ch[5] & 0xC0) == 0x80) {
        memcpy(pstr, ch, 6);
        pstr += 6;
      } else {
        *(pstr++) = 0x7f; // Invalid character !
      }

    } else {
      *(pstr++) = 0x7f; // Invalid character !
    }
  }

  return pstr - sv;
}

int NEncodingLatin1::readStream(std::istream* stream, char* pstr, int cap) const
{
  char ch;
  char* sv = pstr;
  static unsigned short charsetUp[256] = { 
    0x80C2, 0x81C2, 0x82C2, 0x83C2, 0x84C2, 0x85C2, 0x86C2, 0x87C2, // 0x80 - 128
    0x88C2, 0x89C2, 0x8AC2, 0x8BC2, 0x8CC2, 0x8DC2, 0x8EC2, 0x8FC2, // 0x88 - 136
    0x90C2, 0x91C2, 0x92C2, 0x93C2, 0x94C2, 0x95C2, 0x96C2, 0x97C2, // 0x90 - 144
    0x98C2, 0x99C2, 0x9AC2, 0x9BC2, 0x9CC2, 0x9DC2, 0x9EC2, 0x9FC2, // 0x98 - 152

    0xA0C2, 0xA4C2, 0xA2C2, 0xA3C2, 0xA4C2, 0xA5C2, 0xA6C2, 0xA7C2, // 0xA0 - 160
    0xA8C2, 0xA9C2, 0xAAC2, 0xABC2, 0xACC2, 0xADC2, 0xAEC2, 0xAFC2, // 0xA8 - 168
    0xB0C2, 0xB1C2, 0xB2C2, 0xB3C2, 0xB4C2, 0xB5C2, 0xB6C2, 0xB7C2, // 0xB0 - 176
    0xB8C2, 0xB9C2, 0xBAC2, 0xBBC2, 0xBCC2, 0xBDC2, 0xBEC2, 0xBFC2, // 0xB8 - 184
    
    0x80C3, 0x81C3, 0x82C3, 0x83C3, 0x84C3, 0x85C3, 0x86C3, 0x87C3, // 0xC0 - 192
    0x88C3, 0x89C3, 0x8AC3, 0x8BC3, 0x8CC3, 0x8DC3, 0x8EC3, 0x8FC3, // 0xC8 - 200
    0x90C3, 0x91C3, 0x92C3, 0x93C3, 0x94C3, 0x95C3, 0x96C3, 0x97C3, // 0xD0 - 208
    0x98C3, 0x99C3, 0x9AC3, 0x9BC3, 0x9CC3, 0x9DC3, 0x9EC3, 0x9FC3, // 0xD8 - 216

    0xA0C3, 0xA1C3, 0xA2C3, 0xA3C3, 0xA4C3, 0xA5C3, 0xA6C3, 0xA7C3, // 0xE0 - 224
    0xA8C3, 0xA9C3, 0xAAC3, 0xABC3, 0xACC3, 0xADC3, 0xAEC3, 0xAFC3, // 0xE8 - 232
    0xB0C3, 0xB1C3, 0xB2C3, 0xB3C3, 0xB4C3, 0xB5C3, 0xB6C3, 0xB7C3, // 0xF0 - 240
    0xB8C3, 0xB9C3, 0xBAC3, 0xBBC3, 0xBCC3, 0xBDC3, 0xBEC3, 0xBFC3, // 0xF8 - 248
  };

  while (cap > 2) {
    stream->read(&ch, 1);
    if (ch > 0) {
      *(pstr++) = ch;
    } else {
      *((unsigned short*)pstr) = charsetUp[-ch];
      pstr += 2;
    }
  }

  return pstr - sv;
}

int NEncodingASCII::readStream(std::istream* stream, char* pstr, int cap) const
{
  stream->read(pstr, cap);
  for (int i=0; i<cap; ++i)
    if (pstr[i] < 0)
      pstr[i] = 0x7f; // Invalid character !
  return cap;
}

