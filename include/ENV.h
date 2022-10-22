#ifndef _ENV_h
#define _ENV_h

#include "util.h"

class ENV {
 public:
  List<ANY *> stack;
  List<ANY *> code;

  ENV();

  void run(String &);
  void exec();
  void push(ANY *);
  void push(List<ANY *> &);

  ANY *pop();
  ANY *pop(int);
  ANY *get(int);
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