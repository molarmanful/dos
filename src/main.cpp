#include <Arduino.h>
#include <ListLib.h>

class ANY {
public:
  virtual ~ANY() {}
  String toString() { return ""; }
};

class STR : public ANY {
public:
  String x;
  STR(String s) { x = s; }
  String toString() { return x; }
};

class CMD : public ANY {
public:
  String x;
  CMD(String c) { x = c; }
  String toString() { return x; }
};

class NUM : public ANY {
public:
  double x;
  NUM(double n) { x = n; }
  String toString() { return String(x); }
};

class Parser {

  List<ANY> xs;
  enum Type { Un, Num, Str, Cmd, Esc, Dot };
  Type type;
  String word;

public:
  Parser() { type = Un; }

  void clean() {
    switch (type) {
    case Str:
      xs.Add(STR(word));
      break;
    case Esc:
      xs.Add(STR(word + '\\'));
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
          xs.Add(CMD(String(c)));
        }
      } else {
        xs.Add(CMD(word));
      }
      break;
    }
    case Dot:
      if (word == ".")
        xs.Add(CMD(word));
      else if (word.indexOf('.') > 0) {
        xs.Add(CMD(word.substring(0, word.length() - 1)));
        xs.Add(CMD("."));
      } else {
        xs.Add(NUM(word.toDouble()));
      }
      break;
    case Num:
      xs.Add(NUM(word.toDouble()));
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

  List<ANY> parse(String cs) {
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
    return xs;
  }
};

void setup() {
  Serial.begin(9600);
  Serial.println("PARSED:");
  Parser p;
  List<ANY> xs = p.parse("asdf 1 2.1 3 4+");
  for (int i = 0; i < xs.Count(); i++) {
    Serial.println(xs[i].toString());
  }
}

void loop() {}