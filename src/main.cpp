#include <Arduino.h>

#include "ENV.h"

void setup() {
  Serial.begin(9600);
  ENV env;
  String inp("\"Hello, world!\" \\+ 1 2.1 3 4 + * -");
  env.run(inp);
  inp = "";
}

void loop() {}