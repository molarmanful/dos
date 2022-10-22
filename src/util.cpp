#include "Util.h"

UA<ANY*> Util::toFArray(ANY*& x) {
  if (x->type() == "STR") {
    auto s = x->toString();
    Parser p;
    p.parse(s);
    s = "";
    return p.xs;
  }
  return x->toArray();
}