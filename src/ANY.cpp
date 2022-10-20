#include "ANY.h"

ANY::~ANY() {}
String ANY::toString() { return ""; }
String ANY::toForm() { return "UN"; }

STR::STR(String s) { x = s; }
String STR::toString() { return x; }
String STR::toForm() { return "STR(" + x + ")"; };

CMD::CMD(String c) { x = c; }
String CMD::toString() { return x; }
String CMD::toForm() { return "CMD(" + x + ")"; }

NUM::NUM(double n) { x = n; }
String NUM::toString() { return String(x); }
String NUM::toForm() { return "NUM(" + toString() + ")"; }