#include "ENV.h"
#include "deps.h"

struct Result {
  bool done;
  String data;
};

Result readSD(char f[]) {
  File file;
  Serial.print("INIT SD... ");
  if (!SD.begin()) {
    Serial.println("fail");
    return {false};
  }
  Serial.println("done");
  Serial.print("WRITE ");
  Serial.print(f);
  Serial.print("... ");
  SD.remove(f);
  file = SD.open(f, FILE_WRITE);
  if (!file) {
    Serial.println("fail");
    return {false};
  }
  file.println("\"Hello, world!\" \\+ 1 2.1 3 4 + * -");
  file.close();
  Serial.println("done");
  Serial.print("READ ");
  Serial.print(f);
  Serial.print("... ");
  file = SD.open(f, FILE_READ);
  if (!file) {
    Serial.println("fail");
    return {false};
  }
  String data(file.readString());
  file.close();
  Serial.println("done");
  return {true, data};
}

void setup() {
  Serial.begin(9600);
  // Result test = readSD("test.lin");
  // if (!test.done) return;
  String inp("\"Hello, world!\" \\+ 1 2.1 3 4 + * -");
  ENV env;
  env.run(inp);
  // String inp(test.data);
  // env.run(inp);
  inp = "";
}

void loop() {}