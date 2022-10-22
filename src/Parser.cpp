#include "Parser.h"

Parser::Parser() { type = Un; }

void Parser::clean() {
  switch (type) {
    case Str:
      xs.Add(new STR(word));
      break;
    case Esc:
      xs.Add(new STR(word + '\\'));
      break;
    case Cmd: {
      bool p = true;
      String pars("()[]{}");
      for (auto c : word) {
        if (pars.indexOf(c) < 0) {
          p = false;
          break;
        }
      }
      if (p) {
        for (auto c : word) {
          xs.Add(new CMD(String(c)));
        }
      } else {
        xs.Add(new CMD(word));
      }
      break;
    }
    case Dot:
      if (word == ".")
        xs.Add(new CMD(word));
      else if (word.indexOf('.') == word.length() - 1) {
        xs.Add(new CMD(word.substring(0, word.length() - 1)));
        xs.Add(new CMD("."));
      } else {
        xs.Add(new NUM(word.toDouble()));
      }
      break;
    case Num:
      xs.Add(new NUM(word.toDouble()));
      break;
    default:
      break;
  }
  word = "";
  type = Un;
}

void Parser::pstr(char c) {
  if (type == Esc) {
    word += c == '"' ? "\"" : "\\" + c;
    type = Str;
  } else {
    if (c == '\\')
      type = Esc;
    else if (c == '"')
      clean();
    else
      word += c;
  }
}

void Parser::pnum(char c) {
  if (type != Dot && type != Num) {
    clean();
    type = Num;
  }
  word += c;
}

void Parser::pdot() {
  if (type != Num) {
    clean();
    type = Dot;
  }
  word += '.';
}

void Parser::pcmd(char c) {
  if (type != Cmd) {
    clean();
    type = Cmd;
  }
  word += c;
}

void Parser::parse(String &cs) {
  for (auto c : cs) {
    if (type == Str || type == Esc)
      pstr(c);
    else if (c == '"') {
      clean();
      type = Str;
    } else if (c == '.')
      pdot();
    else if (isDigit(c))
      pnum(c);
    else if (isWhitespace(c))
      clean();
    else
      pcmd(c);
  }
  clean();
}