#ifndef _ENV_h
#define _ENV_h

#include <Arduino.h>

#include "ANY.h"
#include "Parser.h"

class ENV {
 public:
  List<ANY *> stack;
  List<ANY *> code;

  ENV();

  void run(String s);
  void exec();
  void cmd(String c);
};

#endif