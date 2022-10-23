#include "ENV.h"

ENV::ENV() { Un = new ANY(); }
ENV::~ENV() {}

void ENV::printArray(UA<ANY*>& xs) {
  for (auto& x : xs) SPR(x->toForm()), SPR(" ");
  SPN();
}

void ENV::run(String& s) {
  SPR("START: ");
  SPN(s);

  SPR("PARSED: ");
  Parser p;
  p.parse(s);
  printArray(p.xs);

  Stack<ANY*> st1(Un);
  stacks.push(st1);
  Stack<ANY*> st2(Un);
  codes.push(st2);
  UM<String, ANY*> m1;
  m1.setInvalidValue(Un);
  locs.push(m1);

  gcode().pushRev(p.xs);

  SPN("---\n");
  exec();
  SPN("---\nDONE");
}

void ENV::exec() {
  while (!gcode().isEmpty()) {
    SPR("QUEUE: ");
    printArray(gcode().xs);
    ANY* c = gcode().pop();
    if (c->type() == "CMD") {
      auto c1 = c->toString();
      cmd(c1);
      c1 = "";
    } else
      push(c);
    printArray(gstack().xs);
    SPN();
  }
}

Stack<ANY*>& ENV::gstack() { return stacks.get(-1); }
Stack<ANY*>& ENV::gcode() { return codes.get(-1); }
UM<String, ANY*>& ENV::gloc() { return locs.get(-1); }

void ENV::push(ANY* x) { gstack().push(x); }
void ENV::push(UA<ANY*>& x) {
  for (auto& a : x) push(a);
}

ANY* ENV::pop(int i = -1) { return gstack().pop(i); }

ANY*& ENV::get(int i) { return gstack().get(i); }

void ENV::ins(int i, ANY* x) { gstack().ins(i, x); }

void ENV::eval() {
  auto xs = pop();
  auto fs = Util::toFArray(xs);
  gcode().pushRev(fs);
}

void ENV::over() { push(get(-2)); }
void ENV::swap() { push(pop(-2)); }
void ENV::rot() { push(pop(-3)); }
void ENV::rotu() { ins(-2, pop()); }

void ENV::trunc_() {
  auto& o = get(-1);
  o = new NUM(trunc(o->toDouble()));
}

void ENV::neg() {
  auto& o = get(-1);
  o = new NUM(-o->toDouble());
}
void ENV::add() {
  auto y = pop()->toDouble();
  auto x = pop()->toDouble();
  push(new NUM(x + y));
}
void ENV::sub() { neg(), add(); }
void ENV::mul() {
  auto y = pop()->toDouble();
  auto x = pop()->toDouble();
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
  auto y = pop()->toDouble();
  auto x = pop()->toDouble();
  push(new NUM(pow(x, y)));
}

void ENV::cmd(String& c) {
  if (c[0] == '\\' && c.length() > 1) {
    ANY* c1 = new CMD(c.substring(1));
    auto f = Util::toFArray(c1);
    push(new FN(f));
  }

  else if (c.startsWith("=$$") && c.length() > 3)
    glob[c.substring(3)] = pop();
  else if (c.startsWith("=$") && c.length() > 2)
    gloc()[c.substring(2)] = pop();

  else if (c.startsWith("$$") && c.length() > 2 && glob.find(c) > -1)
    push(glob[c.substring(2)]);
  else if (c[0] == '$' && c.length() > 1 && gloc().find(c) > -1)
    push(gloc()[c.substring(1)]);
  else if (c[0] == '$' && c.length() > 1 && glob.find(c) > -1)
    push(glob[c.substring(1)]);

  else if (gloc().find(c) > -1)
    push(gloc()[c]), eval();
  else if (glob.find(c) > -1)
    push(glob[c]), eval();

  else if (c == "#")
    eval();

  else if (c == "UN")
    push(Un);

  else if (c == ">N") {
    auto o = get(-1);
    if (o->type() != "NUM") o = new NUM(o->toDouble());
  } else if (c == ">S") {
    auto o = get(-1);
    if (o->type() != "STR") o = new STR(o->toString());
  } else if (c == ">F") {
    auto o = get(-1);
    if (o->type() != "FN") {
      auto o1 = Util::toFArray(o);
      o = new FN(o1);
    }
  } else if (c == ">A") {
    auto o = get(-1);
    if (o->type() != "ARR") {
      auto o1 = o->toArray();
      printArray(o1);
      o = new ARR(o1);
    }
  }

  else if (c == "out")
    SPR(pop()->toString());
  else if (c == "outn")
    SPN(pop()->toString());

  else if (c == "(") {
    UA<ANY*> res;
    for (int lvl = 1; !gcode().isEmpty();) {
      auto c = gcode().pop();
      if (c->type() == "CMD") {
        auto c1 = c->toString();
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
  else if (c == "[") {
    Stack<ANY*> st(Un);
    stacks.push(st);
  } else if (c == "]" && stacks.length() > 1) {
    auto o = stacks.pop().xs;
    ANY* o1 = new ARR(o);
    gstack().push(o1);
  }

  else if (c == "dup")
    push(get(-1));
  else if (c == "dups")
    push(new ARR(gstack().xs));
  else if (c == "over")
    push(get(-2));

  else if (c == "pop")
    pop();
  else if (c == "clr")
    gstack().clr();
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
    // TODO: proper error handling
    SPN("ERR: fn not found");
}