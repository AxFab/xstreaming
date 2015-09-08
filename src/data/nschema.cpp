#include "xstm/nschema.hpp"
#include <cstring>

using namespace std;
using namespace axkit;

NSchema::NSchema(cstr name, cstr nms)
  : NDescr(name)
{
  namespace_ = nms;
}

NEntity* NSchema::entity(cstr name)
{
  for (NList<NEntity>::const_iterator it = entities_.begin(); 
      it != entities_.end(); ++it) {
    if (strcmp((*it)->name(), name) == 0)
      return *it;
  }
  return NULL;
}

NString NSchema::getSqlCreate()
{
  NString str = NString::Empty;
  
  
  for (NList<NEntity>::const_iterator it = entities_.begin(); 
      it != entities_.end(); ++it) {
    str += (*it)->getSqlCreate();

  }

  return str;
}



