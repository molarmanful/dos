#ifndef _Any_h
#define _Any_h

#include <Arduino.h>

class ANY {
public:
  ANY();
  virtual ~ANY();
  virtual String toString();
  virtual String toForm();
};

class STR : public ANY {
public:
  String x;
  STR(String s);
  String toString() override;
  String toForm() override;
};

class CMD : public ANY {
public:
  String x;
  CMD(String c);
  String toString() override;
  String toForm() override;
};

class NUM : public ANY {
public:
  double x;
  NUM(double n);
  String toString() override;
  String toForm() override;
};

#endif