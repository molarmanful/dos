#ifndef _ANY_h
#define _ANY_h

#include "deps.h"

class ANY {
 public:
  ANY();
  virtual ~ANY();

  virtual String type();
  virtual String toString();
  virtual String toForm();
  virtual double toDouble();
};

class STR : public ANY {
 public:
  String x;

  STR(String s);

  String type() override;
  String toString() override;
  String toForm() override;
};

class CMD : public ANY {
 public:
  String x;

  CMD(String c);

  String type() override;
  String toString() override;
  String toForm() override;
};

class NUM : public ANY {
 public:
  double x;

  NUM(double n);

  String type() override;
  String toString() override;
  String toForm() override;
  double toDouble() override;
};

#endif