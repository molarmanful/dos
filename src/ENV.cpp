#include "ENV.h"

ENV::ENV() {}

void printList(List<ANY*>& xs) {
  for (int i = 0; i < xs.Count(); i++) {
    String ci(xs[i]->toForm());
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
  if (code.Count() > 0) {
    ANY* c = code[0];
    code.RemoveFirst();
    Serial.print("EXEC: ");
    Serial.println(c->toForm());
    if (c->type() == "CMD") {
      String c1(c->toString());
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

ANY* ENV::pop() {
  ANY* x = stack[stack.Count() - 1];
  stack.RemoveLast();
  return x;
}

ANY* ENV::pop(int i) {
  if (i < 0) return pop(~i);
  ANY* x = stack[i];
  stack.Remove(i);
  return x;
}

ANY* ENV::get(int i) {
  if (i < 0) return get(~i);
  return stack[i];
}

void ENV::over() { push(get(-2)); }
void ENV::swap() { push(pop(-2)); }
void ENV::rot() { push(pop(-3)); }
void ENV::rotu() {
  ANY* z = pop();
  ANY* y = pop();
  ANY* x = pop();
  push(z), push(y), push(x);
}

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
    String c1(c);
    c1.remove(0, 1);
    push(new CMD(c1));
  } else if (c[0] == '#' && c.length() > 1)
    ;
  else {
    if (c == "#")
      ;
    else if (c == "out")
      Serial.print(pop()->toString());
    else if (c == "outn")
      Serial.println(pop()->toString());

    else if (c == "(") {
      List<ANY*> res;
      for (int lvl = 1;;) {
        ANY* c = code[0];
        code.RemoveFirst();
        if(c->type() == "CMD"){
          String c1(c->toString());
        }
        if (c->type() == "CMD" && c->toString().indexOf('(') > -1)
          lvl++;
        else if (c->type() == "CMD" && c->toString().indexOf(')') > -1)
          lvl--;
        if (lvl <= 0) {
          cmd(c->toString());
          break;
        }
        res.Add(c);
      }
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
      swap(), over();

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

    else
      Serial.println("ERR: fn not found");
  }
}

STR toSTR(ANY* x) { return STR(x->toString()); }
CMD toCMD(ANY* x) { return CMD(x->toString()); }
NUM toNUM(ANY* x) { return NUM(x->toDouble()); }