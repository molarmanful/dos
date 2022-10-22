#ifndef _util_h
#define _util_h

#include "Parser.h"

class Util {
 public:
  static STR toSTR(ANY *);
  static CMD toCMD(ANY *);
  static NUM toNUM(ANY *);
  static FN toFN(ANY *);
};

#endif