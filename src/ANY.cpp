#include "ANY.h"

// ANY

ANY::ANY() {}
ANY::~ANY() {}

String ANY::type() {
  String o = "UN";
  return o;
}

String ANY::toString() {
  String o = "";
  return o;
}

String ANY::toForm() { return type(); }

double ANY::toDouble() { return 0; }

UA<ANY*> ANY::toArray() { return UA<ANY*>(); }

// STR

STR::STR(String s) { x = s; }

String STR::type() {
  String o = "STR";
  return o;
}

String STR::toString() {
  String o(x);
  return o;
}

String STR::toForm() {
  String x1 = x;
  x1.replace("\"", "\\\"");
  return "\"" + x1 + "\"";
}

double STR::toDouble() { return toString().toDouble(); }

UA<ANY*> STR::toArray() {
  UA<ANY*> o;
  for (auto& c : x) {
    String c1(c);
    ADD(o, new STR(c1));
    c1 = "";
  }
  return o;
}

// CMD

CMD::CMD(String c) { x = c; }

String CMD::type() {
  String o = "CMD";
  return o;
}

String CMD::toString() {
  String o(x);
  return o;
}

String CMD::toForm() { return toString(); }

double CMD::toDouble() { return toString().toDouble(); }

UA<ANY*> CMD::toArray() {
  UA<ANY*> o;
  o[0] = this;
  return o;
}

// NUM

NUM::NUM(double n) { x = n; }

String NUM::type() {
  String o = "NUM";
  return o;
}

String NUM::toString() {
  String o(x);
  return o;
}

String NUM::toForm() { return toString(); }

double NUM::toDouble() { return x; }

UA<ANY*> NUM::toArray() {
  UA<ANY*> o;
  o[0] = this;
  return o;
}

// FN

void join(UA<ANY*>& xs, String& s, String sep = " ") {
  int l = xs.length();
  int i = 0;
  for (auto& x : xs) {
    s += x->toForm();
    if (i < l - 1) s += sep;
    i++;
  }
}

FN::FN(UA<ANY*>& f) { x = UA<ANY*>(f); }

String FN::type() {
  String o = "FN";
  return o;
}

String FN::toString() {
  String s;
  join(x, s);
  return s;
}

String FN::toForm() { return "(" + toString() + ")"; }

double FN::toDouble() { return toString().toDouble(); }

UA<ANY*> FN::toArray() { return x; }

// ARR

ARR::ARR(UA<ANY*>& f) { x = UA<ANY*>(f); }

String ARR::type() {
  String o = "ARR";
  return o;
}

String ARR::toString() {
  String s;
  for (auto& a : x) s += a->toString();
  return s;
}

String ARR::toForm() {
  String s;
  join(x, s);
  return "[" + s + "]";
}

double ARR::toDouble() { return toString().toDouble(); }

UA<ANY*> ARR::toArray() { return x; }