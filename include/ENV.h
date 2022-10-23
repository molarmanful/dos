#ifndef _ENV_h
#define _ENV_h

#include "Util.h"

class ENV {
  ANY *Un;

 public:
  Stack<Stack<ANY *>> stacks;
  Stack<Stack<ANY *>> codes;
  Stack<UM<String, ANY *>> loc;
  UM<String, ANY *> glob;

  ENV();
  ~ENV();

  static void printArray(UA<ANY *> &);

  void run(String &);
  void exec();

  Stack<ANY *> &gstack();
  Stack<ANY *> &gcode();
  UM<String, ANY *> &gloc();

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