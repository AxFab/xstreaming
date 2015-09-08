#include "xstm/xstream.hpp"
#include "xstm/nschemareader.hpp"
#include <iostream>
#include <fstream>

using namespace axkit;
using namespace std;


int main() 
{
  const char* file = "./datakit/schemas/xtk_schema.xml";
  XReader* read = new XReader(new ifstream(file, ifstream::in));

  if (1) {    
    XObject* obj;
    do  {
      obj = read->read(); 
    } while (obj);

    XDocument* doc = read->document();

    read->dispose();
    delete read;
    return 0; // Should be passed by valgrind!

  } else {
    NSchemaReader sch (read);
    NSchema *schema = sch.read();
    NString sql = schema->getSqlCreate();
  }

  return 0;
}