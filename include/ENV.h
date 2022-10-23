#ifndef _ENV_h
#define _ENV_h

#include "Util.h"

class ENV {
 public:
  UA<ANY *> stack;
  UA<ANY *> code;
  UA<UM<String, ANY *>> loc;
  UA<UM<String, ANY *>> glob;

  ENV();

  static void printArray(UA<ANY *> &);

  void run(String &);
  void exec();
  void push(ANY *);
  void push(UA<ANY *> &);

  ANY *pop(int);
  ANY *&get(int);
  void set(int, ANY *);
  void ins(int, ANY *);

  void eval();

  void over();
  void swap();
  void rot();
  void rotu();
  void trunc_();
  void neg();
  void add();
  void sub();
  void mul();
  void div();
  void divi();
  void mod();
  void pow_();

  void cmd(String &);
};

#endif