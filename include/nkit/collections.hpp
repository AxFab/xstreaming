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
#ifndef _NKIT_COLLECTIONS_HPP
#define _NKIT_COLLECTIONS_HPP 1
#include <cassert>
#include <list>
#include <stack>
#include <queue>
#include <vector>
#include <map>
#include "nkit/string.hpp"

namespace nkit {

template <typename T>
class NList : public std::list<T*>
{
public:
  /// Destructor, add an assertion to avoid memory leak
  virtual ~NList() { assert(this->size() == 0); }
};

template <typename T>
class NStack : public std::stack<T*>
{
public:
  /// Destructor, add an assertion to avoid memory leak
  virtual ~NStack()  { assert(this->size() == 0); }
};

template <typename T>
class NQueue : public std::queue<T*>
{
public:
  /// Destructor, add an assertion to avoid memory leak
  virtual ~NQueue()  { assert(this->size() == 0); }
};

template <typename T>
class NVector : public std::vector<T*>
{
public:
  /// Destructor, add an assertion to avoid memory leak
  virtual ~NVector() { assert(this->size() == 0); }
};

template <typename T>
class NMap : public std::map<NString, T*>
{
public:
  /// Destructor, add an assertion to avoid memory leak
  virtual ~NMap() { assert(this->size() == 0); }
  /// Find an item by use of its key
  T* find_key(cstr name) const;
};


class NStrings : public NVector<NString> {};



/// Find an item by use of its key
template <typename T>
T* NMap<T>::find_key(cstr name) const
{ //NOLINT
  typedef typename NMap<T>::const_iterator iterator;
  iterator it = this->find(name);
  return it == this->end() ? NULL : it->second;
}

}  // namespace nkit

#endif /* _NKIT_COLLECTIONS_HPP */
