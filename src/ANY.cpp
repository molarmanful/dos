#include "ANY.h"

// ANY

ANY::ANY() {}
ANY::~ANY() {}

String ANY::type() { return "UN"; }
String ANY::toString() { return ""; }
String ANY::toForm() { return "UN"; }
double ANY::toDouble() { return toString().toDouble(); }

// STR

STR::STR(String s) { x = s; }

String STR::type() { return "STR"; }
String STR::toString() { return x; }
String STR::toForm() {
  String x1(x);
  x1.replace("\"", "\\\"");
  return "\"" + x1 + "\"";
}

// CMD

CMD::CMD(String c) { x = c; }

String CMD::type() { return "CMD"; }
String CMD::toString() { return x; }
String CMD::toForm() { return x; }

// NUM

NUM::NUM(double n) { x = n; }

String NUM::type() { return "NUM"; }
String NUM::toString() { return String(x); }
String NUM::toForm() { return toString(); }
double NUM::toDouble() { return x; }

// FN

FN::FN(List<ANY*> f) { x = f; }

String FN::type() { return "FN"; }
void join(List<ANY*>& xs, String& s, String sep) {
  for (int i = 0, l = xs.Count(); i < l; i++) {
    s += xs[i]->toString();
    if (i < l - 1) s += sep;
  }
}
String FN::toString() {
  String s;
  join(x, s, " ");
  return s;
}
String FN::toForm() { return "(" + toString() + ")"; }