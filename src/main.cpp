#include "ENV.h"

struct Result {
  bool done;
  String data;
};

String inp = "1 2 \\+ =$$a a";

Result readSD(char f[]) {
  File file;
  SPR("INIT SD... ");
  if (!SD.begin()) {
    SPN("fail");
    return {false};
  }
  SPN("done");
  SPR("WRITE "), SPR(f), SPR("... ");
  SD.remove(f);
  file = SD.open(f, FILE_WRITE);
  if (!file) {
    SPN("fail");
    return {false};
  }
  file.println(inp);
  file.close();
  SPN("done");
  SPR("READ "), SPR(f), SPR("... ");
  file = SD.open(f, FILE_READ);
  if (!file) {
    SPN("fail");
    return {false};
  }
  String data = file.readString();
  file.close();
  SPN("done");
  return {true, data};
}

ENV env;
void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;
  // Result test = readSD("test.lin");
  // if (!test.done) return;
  // String x = test.data;
  // env.run(x);
  env.run(inp);
}

void loop() {}