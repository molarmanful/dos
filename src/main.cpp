#include <Arduino.h>

#include "ENV.h"

void setup() {
  Serial.begin(9600);
  ENV env;
  String inp = "asdf \"test\\\"1234\" 1 2.1 3 4 +";
  Serial.println(inp);
  env.run(inp);
}

void loop() {}