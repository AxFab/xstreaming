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
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <cstdint>
#include "nkit/string.hpp"
#include "nkit/collections.hpp"

#ifdef _WIN32
# define strtok_r strtok_s
#endif

namespace nkit {

NString NString::Empty = NString("");


NString::NString()
  : std::string()
{
}

NString::NString(const std::string& value)
  : std::string(value)
{
}

NString::NString(cstr value)
  : std::string(value)
{
}

int NString::indexOf(char ch) {
  size_t s = find(ch);
  return (s >= size()) ? -1 : s;
}
static NString Empty;

std::string NString::trim_start()
{
  int i = 0;
  while (i < (int)size() && isspace(at(i))) i++;
  return substr(i);
}

std::string NString::trim()
{
  int i = 0;
  while (i < (int)size() && at(i) > 0 && isspace(at(i))) i++;
  NString str = NString(substr(i));
  if (str != "") {
    i = size() - 1;
    while (i > 0 && at(i) > 0 && isspace(at(i))) i--;
    if (++i < (int)this->size())
      str.at(i) = '\0';
  }

  return str;
}

bool NString::ends_with(cstr string)
{
  int lg = strlen(string);
  return memcmp(&(c_str()[size() - lg]), string, lg) == 0;
}


std::string NString::extract_until(char ch, int from, char escape)
{
  std::string pfx;
  int k = -1;
  while (k < 0) {
    k = find(ch, from);
    if (k < 0)
      return "";
    if (at(k-1) == escape) {
      from = k+1;
      k = -1;
    }
  }

  pfx = substr(0, k+1);
  assign(&c_str()[k+1]);
  return pfx;
}

void NString::split(cstr delim, NStrings* strings)
{
  char* ctx;
  char* buf = strdup(this->c_str());

  char* ptr = strtok_r(buf, delim, &ctx);
  while (ptr) {
    strings->push_back(new NString(ptr));
    ptr = strtok_r(NULL, delim, &ctx);
  }

  free(buf);
}


NString NString::Concat(cstr str, ...)
{
  va_list ap;
  NString string(str);

  va_start(ap, str);
  for (;;) {
    cstr nx = va_arg(ap, cstr);
    if (nx)
      string += nx;
    else
      break;
  }

  va_end(ap);
  return string;
}

NString::operator cstr()
{
  return this->c_str();
}

NString::operator std::string()
{
  return std::string(this->c_str());
}

}  // namespace nkit

#ifdef _WIN32


static int _bmPatternMatch(const uint8_t* pattern, int patternLength, int portion, int offset) {

  int virtual_begin = patternLength - offset - portion;
  int ignore = 0;

  if (virtual_begin < 0) {
    ignore = -virtual_begin;
    virtual_begin = 0;
  }

  if (virtual_begin > 0 && pattern[virtual_begin - 1] == pattern[patternLength-portion - 1])
    return 0;

	return memcmp (&pattern [patternLength-portion+ignore], &pattern[virtual_begin], portion - ignore) == 0;
}


/// The memmem() function locates the first occurrence of the byte string
/// needle in the byte string haystack.
/// The algorithm used here is the Boyer-Moore algorithm.
void *memmem(const void *haystack, size_t haystacklen, 
             const void *needle, size_t needlelen)
{
  size_t *skip;
  int lastOccur[512];
  const uint8_t* pneedle = reinterpret_cast<const uint8_t*>(needle);
  const uint8_t* phaystack = reinterpret_cast<const uint8_t*>(haystack);

  if (needlelen > haystacklen || needlelen <= 0 || !haystack || !needle) 
    return NULL;

	// Initialize an array with last occurance of every value.
  for (size_t i = 0; i < 512; i++) {
    lastOccur[i] = -1;
  }

  for (size_t i = 0; i < needlelen - 1; i++) {
    lastOccur[pneedle[i]] = i;
  }

  // Init skip array! This allow to optimise search using repeated patterns.
  // TODO(AxFab) improvment needed here
  skip = new size_t [needlelen];
  for (size_t i = 0; i < needlelen; i++) {
    size_t shift = 0;
    while (shift < needlelen && !_bmPatternMatch (pneedle, needlelen, i, shift)) {
      shift++;
    }
    skip [needlelen - i - 1] = shift;
  }

  // Do the actual search
	size_t hpos = 0;  // offset
  while (hpos <= haystacklen - needlelen) {
    size_t npos = needlelen - 1;
    while (pneedle[npos] == phaystack[npos + hpos]) {
      if (npos == 0) {
        delete[] skip;
        return const_cast<uint8_t*>(&phaystack[hpos]);
      }
      --npos;
    }
    hpos += std::max(skip[npos], npos - lastOccur[(int)phaystack[npos + hpos]]);
  }

  // We looked everywhere...
  delete[] skip;
  return NULL;
}

#endif