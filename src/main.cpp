#include <Arduino.h>
#include <ListLib.h>

class ANY {
public:
  virtual ~ANY() {}
  virtual String toString() { return ""; }
  virtual String toForm() { return "UN"; }
};

class STR : public ANY {
public:
  String x;
  STR(String s) { x = s; }
  String toString() override { return x; }
  String toForm() override { return "STR(" + x + ")"; }
};

class CMD : public ANY {
public:
  String x;
  CMD(String c) { x = c; }
  String toString() override { return x; }
  String toForm() override { return "CMD(" + x + ")"; }
};

class NUM : public ANY {
public:
  double x;
  NUM(double n) { x = n; }
  String toString() override { return String(x); }
  String toForm() override { return "NUM(" + toString() + ")"; }
};

class Parser {

  enum Type { Un, Num, Str, Cmd, Esc, Dot };
  Type type;
  String word;

public:
  List<ANY *> xs;

  Parser() { type = Un; }

  void clean() {
    switch (type) {
    case Str:
      xs.Add(new STR(word));
      break;
    case Esc:
      xs.Add(new STR(word + '\\'));
      break;
    case Cmd: {
      bool p = true;
      String pars = "()[]{}";
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
      else if (word.indexOf('.') > 0) {
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

  void pstr(char c) {
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

  void pnum(char c) {
    if (type != Dot && type != Num) {
      clean();
      type = Num;
    }
    word += c;
  }

  void pdot() {
    if (type == !Num) {
      clean();
      type = Dot;
    }
    word += '.';
  }

  void pcmd(char c) {
    if (type != Cmd) {
      clean();
      type = Cmd;
    }
    word += c;
  }

  void parse(String cs) {
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
  }
};

void setup() {
  Serial.begin(9600);
  Serial.print("PARSING: ");
  Parser p;
  String inp = "asdf \"test\" 1 2.1 3 4+";
  Serial.println(inp);
  p.parse(inp);
  for (int i = 0; i < p.xs.Count(); i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(p.xs[i]->toForm());
  }
}

void loop() {}