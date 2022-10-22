#include "ANY.h"

template <typename T>
void Ls<T>::listCopy(List<T>& x, List<T>& y) {
  y.AddRange(x.ToArray(), x.Count());
}

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

List<ANY*> ANY::toList() {
  List<ANY*> o;
  return o;
}

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

List<ANY*> STR::toList() {
  List<ANY*> o;
  for (auto c : x) {
    String c1(c);
    o.Add(new STR(c1));
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

List<ANY*> CMD::toList() {
  List<ANY*> o;
  o.Add(this);
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

List<ANY*> NUM::toList() {
  List<ANY*> o;
  o.Add(this);
  return o;
}

// FN

void join(List<ANY*>& xs, String& s, String sep) {
  int l = xs.Count();
  for (int i = 0; i < l; i++) {
    s += xs[i]->toForm();
    if (i < l - 1) s += sep;
  }
}

FN::FN(List<ANY*>& f) { Ls<ANY*>::listCopy(f, x); }

String FN::type() {
  String o = "FN";
  return o;
}

String FN::toString() {
  String s;
  join(x, s, " ");
  return s;
}

String FN::toForm() { return "(" + toString() + ")"; }

double FN::toDouble() { return toString().toDouble(); }

List<ANY*> FN::toList() {
  List<ANY*> o;
  Ls<ANY*>::listCopy(x, o);
  return o;
}