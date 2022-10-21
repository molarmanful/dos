#ifndef _Parser_h
#define _Parser_h

#include "ANY.h"
#include "deps.h"

class Parser {
  enum Type { Un, Num, Str, Cmd, Esc, Dot };
  Type type;
  String word;

 public:
  List<ANY *> xs;
  Parser();
  void clean();
  void pstr(char c);
  void pnum(char c);
  void pdot();
  void pcmd(char c);
  void parse(String &cs);
};

#endif