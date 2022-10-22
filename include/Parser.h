#ifndef _Parser_h
#define _Parser_h

#include "ANY.h"

class Parser {
  enum Type { Un, Num, Str, Cmd, Esc, Dot };
  Type type;
  String word;

 public:
  List<ANY *> xs;
  Parser();
  void clean();
  void pstr(char);
  void pnum(char);
  void pdot();
  void pcmd(char);
  void parse(String &);
};

#endif