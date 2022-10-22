#ifndef _Util_h
#define _Util_h

#include "Parser.h"

class Util {
 public:
  static STR toSTR(ANY *&);
  static CMD toCMD(ANY *&);
  static NUM toNUM(ANY *&);
  static FN toFN(ANY *&);
};

#endif