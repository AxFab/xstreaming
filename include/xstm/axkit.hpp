
#pragma once

#include <cstdlib>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <stack>

typedef const char* cstr;

#define __abstract 

namespace axkit {

class NMemoryLeakException
{
};

class NStrings;
class NString : public std::string
{
public:
  NString();
  NString(const std::string& value);
  NString(cstr value);
  int indexOf(char ch);
  static NString Empty;
  
  std::string trim_start();
  std::string trim();
  bool ends_with(cstr string);
  std::string extract_until(char ch, int from = 0, char escape = '\0');
  operator cstr();
  operator std::string();
  void split(cstr delim, NStrings* strings);
};

template <typename T> class NList : public std::list<T*>
{
public:
  virtual ~NList() { if (this->size() > 0) throw new NMemoryLeakException(); }
};

template <typename T> class NStack : public std::stack<T*>
{
public:
  virtual ~NStack() { if (this->size() > 0) throw new NMemoryLeakException(); }
};

template <typename T> class NVector : public std::vector<T*>
{
public:
  virtual ~NVector() { if (this->size() > 0) throw new NMemoryLeakException(); }
};

template <typename T> class NMap : public std::map<NString, T*>
{
public:
  virtual ~NMap() { if (this->size() > 0) throw new NMemoryLeakException(); }
  T* find_key(cstr name) const
  {
    typedef typename NMap<T>::const_iterator iterator;
    iterator it = this->find(name);
    return it == this->end() ? NULL : it->second;
  }
};

class NStrings : public NVector<NString> 
{
};

__abstract class NEncoding 
{
private:
  NString name_;
protected:
  NEncoding(cstr name);
public:
  virtual int readStream(std::istream* stream, char* buf, int cap) const = 0;
  cstr name() const { return name_.c_str(); }
  static const NEncoding &UTF8();
  static const NEncoding &Latin1();
  static const NEncoding &UTF16_LE();
  static const NEncoding &UTF16_BE();
};

} // namespace axkit

