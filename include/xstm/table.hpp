
#ifndef _AX_DATA_TABLE_HPP 
#define _AX_DATA_TABLE_HPP 1

#include <cstdlib>

namespace axkit {

typedef const wchar_t* pszc;


class DConstraint;
class DColumn;
class DRelation;
class DRow;
class DSet;
class DView;
class DTable
{
  public:
    DTable();
    ~DTable();
};


};

#endif /* _AX_DATA_TABLE_HPP */
