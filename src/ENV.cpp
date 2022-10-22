#include "ENV.h"

ENV::ENV() {}

void printList(List<ANY*>& xs) {
  for (int i = 0; i < xs.Count(); i++) {
    String ci = xs[i]->toForm();
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
  printList(code);
  Serial.println("---");
  exec();
  Serial.println("---\nDONE");
}

void ENV::exec() {
  if (!code.IsEmpty()) {
    ANY* c = code[0];
    code.RemoveFirst();
    Serial.print("EXEC: ");
    Serial.println(c->toForm());
    if (c->type() == "CMD") {
      String c1 = c->toString();
      cmd(c1);
      c1 = "";
    } else {
      push(c);
    }
    printList(stack);
    exec();
  }
}

void ENV::push(ANY* x) { stack.Add(x); }

void ENV::push(List<ANY*>& x) {
  for (int i = 0; i < x.Count(); i++) push(x[i]);
}

ANY* ENV::pop() {
  ANY* x = stack[stack.Count() - 1];
  stack.RemoveLast();
  return x;
}

ANY* ENV::pop(int i) {
  if (i < 0) return pop(stack.Count() + i);
  ANY* x = stack[i];
  stack.Remove(i);
  return x;
}

ANY* ENV::get(int i) {
  if (i < 0) return get(stack.Count() + i);
  return stack[i];
}

void ENV::ins(int i, ANY* x) {
  if (i < 0) i += stack.Count();
  stack.Insert(i, x);
}

void ENV::eval() {
  FN f = Util::toFN(pop());
  code.InsertRange(0, f.x.ToArray(), f.x.Count());
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
      List<ANY*> res;
      for (int lvl = 1; !code.IsEmpty();) {
        ANY* c = code[0];
        code.RemoveFirst();
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
        res.Add(c);
      }
      push(new FN(res));
    } else if (c == ")")
      ;

    else if (c == "dup")
      push(get(-1));
    else if (c == "dups")
      ;
    else if (c == "over")
      push(get(-2));

    else if (c == "pop")
      pop();
    else if (c == "clr")
      stack.Clear();
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