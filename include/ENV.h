#ifndef _ENV_h
#define _ENV_h

#include "ANY.h"
#include "Parser.h"
#include "deps.h"

class ENV {
 public:
  List<ANY *> stack;
  List<ANY *> code;

  ENV();

  void run(String &s);
  void exec();
  void push(ANY *x);

  ANY *pop();
  ANY *pop(int i);
  ANY *get(int i);

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

  void cmd(String &c);
};

#endif