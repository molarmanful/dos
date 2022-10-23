#ifndef _Util_h
#define _Util_h

#include "Parser.h"

class Util {
 public:
  static UA<ANY *> toFArray(ANY *&x) {
    if (x->type() == "STR") {
      auto s = x->toString();
      Parser p;
      p.parse(s);
      s = "";
      return p.xs;
    }
    return x->toArray();
  }
};

#endif