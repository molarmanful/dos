#include "ANY.h"

// ANY

ANY::ANY() {}
ANY::~ANY() {}

String ANY::type() { return "UN"; }

String ANY::toString() { return ""; }

String ANY::toForm() { return type(); }

double ANY::toDouble() { return 0; }

UA<ANY*> ANY::toArray() {
  UA<ANY*> o;
  return o;
}

// STR

STR::STR(String s) { x = s; }

String STR::type() { return "STR"; }

String STR::toString() { return x; }

String STR::toForm() {
  auto x1 = x;
  x1.replace("\"", "\\\"");
  return "\"" + x1 + "\"";
}

double STR::toDouble() { return toString().toDouble(); }

UA<ANY*> STR::toArray() {
  UA<ANY*> o;
  for (auto& c : x) ADD(o, new STR(String(c)));
  return o;
}

// CMD

CMD::CMD(String c) { x = c; }

String CMD::type() { return "CMD"; }

String CMD::toString() { return x; }

String CMD::toForm() { return toString(); }

double CMD::toDouble() { return toString().toDouble(); }

UA<ANY*> CMD::toArray() {
  UA<ANY*> o;
  ADD(o, this);
  return o;
}

// NUM

NUM::NUM(double n) { x = n; }

String NUM::type() { return "NUM"; }

String NUM::toString() { return String(x); }

String NUM::toForm() { return toString(); }

double NUM::toDouble() { return x; }

UA<ANY*> NUM::toArray() {
  UA<ANY*> o;
  ADD(o, this);
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

FN::FN(UA<ANY*>& f) {
  int i = 0;
  for (auto& a : f) x[i++] = a;
}

String FN::type() { return "FN"; }

String FN::toString() {
  String s;
  join(x, s);
  return s;
}

String FN::toForm() { return "(" + toString() + ")"; }

double FN::toDouble() { return toString().toDouble(); }

UA<ANY*> FN::toArray() { return x; }

// ARR

ARR::ARR(UA<ANY*>& f) {
  int i = 0;
  for (auto& a : f) x[i++] = a;
}

String ARR::type() { return "ARR"; }

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