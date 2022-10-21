#include "ENV.h"

ENV::ENV() {}

void ENV::run(String s) {
  Parser p;
  p.parse(s);
  code = p.xs;
  Serial.print("PARSED: ");
  for (int i = 0; i < code.Count(); i++) {
    Serial.print(code[i]->toForm() + " ");
  }
  Serial.println();
  exec();
}

void ENV::exec() {
  if (code.Count() > 0) {
    ANY* c = code[0];
    code.RemoveFirst();
    if (c->type() == "CMD")
      cmd(c->toString());
    else {
      stack.Add(c);
      for (int i = 0; i < stack.Count(); i++) {
        Serial.print(stack[i]->toForm() + " ");
      }
      Serial.println();
    }
    exec();
  }
}

void ENV::cmd(String c) {
  Serial.print("EXEC: ");
  Serial.println(c);
}