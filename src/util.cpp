#include "util.h"

STR Util::toSTR(ANY* x) { return STR(x->toString()); }
CMD Util::toCMD(ANY* x) { return CMD(x->toString()); }
NUM Util::toNUM(ANY* x) { return NUM(x->toDouble()); }
FN Util::toFN(ANY* x) {
  if (x->type() == "STR") {
    String s = x->toString();
    Parser p;
    p.parse(s);
    s = "";
    return FN(p.xs);
  }
  List<ANY*> x1 = x->toList();
  return FN(x1);
}