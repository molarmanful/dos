#ifndef _Stack_h
#define _Stack_h

#include "deps.h"

template <typename T>
class Stack {
 public:
  UA<T> xs;

  Stack() {}
  Stack(T& x) { setDef(x); }
  ~Stack() {}

  unsigned int toi(int i) {
    if (i < 0) i += xs.length();
    return i;
  }

  bool isEmpty() { return xs.isEmpty(); }
  bool length() { return xs.length(); }

  void setDef(T& x) { xs.setInvalidValue(x); }

  T& get(int i) { return xs[toi(i)]; }

  T pop(int i = -1) {
    auto i1 = toi(i);
    auto x = xs[i1];
    xs.erase(i1);
    return x;
  }

  void push(T& x) { xs.add(x); }

  void push(UA<T>& ys) {
    for (auto& y : ys) push(ys);
  }

  void pushRev(UA<T>& ys) {
    for (int i = ys.length() - 1; i >= 0; i--) push(ys[i]);
  }

  void ins(int i, T& x) {
    auto l = xs.length();
    if (i < 0) i += l;
    for (int j = l - 1; j >= i; j--) xs[j + 1] = xs[j];
    xs[i] = x;
  }

  void clr() { xs.erase(); }
};

#endif