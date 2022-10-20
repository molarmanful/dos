#include "Parser.h"
#include <Arduino.h>

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