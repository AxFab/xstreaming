
#include "xstm/axkit.hpp"
#include <cstring>

using namespace axkit;

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
  int i=0; 
  while (i < (int)size() && isspace(at(i))) i++;
  return substr(i);
}
  
std::string NString::trim()
{
  // TODO 
  int i=0; 
  while (i < (int)size() && at(i) > 0 && isspace(at(i))) i++;
  NString str = substr(i);
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

NString::operator cstr() 
{ 
  return this->c_str(); 
}

NString::operator std::string() 
{ 
  return std::string(this->c_str()); 
}

