#include "ENV.h"

ENV::ENV() {}

void printArray(UA<ANY*>& xs) {
  for (auto& x : xs) {
    String ci = x->toForm();
    ci += " ";
    Serial.print(ci);
    ci = "";
  }
  Serial.println();
}

void ENV::run(String& s) {
  Serial.print("START: ");
  Serial.println(s);
  Parser p;
  p.parse(s);
  code = p.xs;
  Serial.print("PARSED: ");
  printArray(code);
  Serial.println("---");
  exec();
  Serial.println("---\nDONE");
}

void ENV::exec() {
  if (!code.isEmpty()) {
    ANY* c = code[0];
    code.erase(0);
    Serial.print("EXEC: ");
    Serial.println(c->toForm());
    if (c->type() == "CMD") {
      String c1 = c->toString();
      cmd(c1);
      c1 = "";
    } else {
      push(c);
    }
    printArray(stack);
    exec();
  }
}

void ENV::push(ANY* x) { stack.add(x); }

void ENV::push(UA<ANY*>& x) {
  for (auto& a : x) push(a);
}

ANY* ENV::pop(int i = -1) {
  if (i < 0) return pop(stack.length() + i);
  ANY* x = stack[i];
  stack.erase(i);
  return x;
}

ANY* ENV::get(int i) {
  if (i < 0) i += stack.length();
  return stack[i];
}

void ENV::ins(int i, ANY* x) {
  int l = stack.length();
  if (i < 0) i += l;
  for (int j = l - 1; j >= i; j--) stack[j + 1] = stack[j];
  stack[i] = x;
}

void ENV::eval() {
  ANY* xs = pop();
  for (auto& x : Util::toFN(xs).x) code.add(x);
}

void ENV::over() { push(get(-2)); }
void ENV::swap() { push(pop(-2)); }
void ENV::rot() { push(pop(-3)); }
void ENV::rotu() { ins(-2, pop()); }

void ENV::trunc_() { push(new NUM(trunc(pop()->toDouble()))); }

void ENV::neg() { push(new NUM(-pop()->toDouble())); }
void ENV::add() {
  double y = pop()->toDouble();
  double x = pop()->toDouble();
  push(new NUM(x + y));
}
void ENV::sub() { neg(), add(); }
void ENV::mul() {
  double y = pop()->toDouble();
  double x = pop()->toDouble();
  push(new NUM(x * y));
}
void ENV::div() { push(new NUM(-1)), pow_(), mul(); }
void ENV::divi() {
  int y = pop()->toDouble();
  int x = pop()->toDouble();
  push(new NUM(x / y));
}
void ENV::mod() {
  int y = pop()->toDouble();
  int x = pop()->toDouble();
  push(new NUM(((x % y) + y) % y));
}
void ENV::pow_() {
  double y = pop()->toDouble();
  double x = pop()->toDouble();
  push(new NUM(pow(x, y)));
}

void ENV::cmd(String& c) {
  if (c[0] == '\\' && c.length() > 1) {
    String c1 = c;
    c1.remove(0, 1);
    push(new CMD(c1));
  } else if (c[0] == '#' && c.length() > 1)
    ;
  else {
    if (c == "#")
      eval();
    else if (c == "out")
      Serial.print(pop()->toString());
    else if (c == "outn")
      Serial.println(pop()->toString());

    else if (c == "(") {
      UA<ANY*> res;
      for (int lvl = 1; !code.isEmpty();) {
        ANY* c = code[0];
        code.erase(0);
        if (c->type() == "CMD") {
          String c1 = c->toString();
          if (c1.indexOf('(') > -1)
            lvl++;
          else if (c1.indexOf(')') > -1) {
            lvl--;
            if (lvl <= 0) {
              cmd(c1);
              c1 = "";
              break;
            }
          }
          c1 = "";
        }
        res.add(c);
      }
      push(new FN(res));
    } else if (c == ")")
      ;

    else if (c == "dup")
      push(get(-1));
    else if (c == "dups")
      push(new ARR(stack));
    else if (c == "over")
      push(get(-2));

    else if (c == "pop")
      pop();
    else if (c == "clr")
      stack.erase();
    else if (c == "nip")
      pop(-2);

    else if (c == "swap")
      push(pop(-2));
    else if (c == "tuck")
      ins(-2, get(-1));

    else if (c == "rot")
      rot();
    else if (c == "rot_")
      rotu();

    else if (c == "I")
      trunc_();

    else if (c == "_")
      neg();
    else if (c == "+")
      add();
    else if (c == "-")
      sub();
    else if (c == "*")
      mul();
    else if (c == "/")
      div();
    else if (c == "/~")
      divi();
    else if (c == "%")
      mod();
    else if (c == "/%")
      over(), over(), div(), rotu(), mod();
    else if (c == "^")
      pow_();

    else if (c == ".")
      ;

    else
      Serial.println("ERR: fn not found");
  }
}