#include "ANY.h"

ANY::ANY() {}
ANY::~ANY() {}
String ANY::type() { return "UN"; }
String ANY::toString() { return ""; }
String ANY::toForm() { return "UN"; }

STR::STR(String s) { x = s; }
String STR::type() { return "STR"; }
String STR::toString() { return x; }
String STR::toForm() {
  String x1 = String(x);
  x1.replace("\"", "\\\"");
  return "\"" + x1 + "\"";
};

CMD::CMD(String c) { x = c; }
String CMD::type() { return "CMD"; }
String CMD::toString() { return x; }
String CMD::toForm() { return x; }

NUM::NUM(double n) { x = n; }
String NUM::type() { return "NUM"; }
String NUM::toString() { return String(x); }
String NUM::toForm() { return toString(); }