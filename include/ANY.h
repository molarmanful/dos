#ifndef _ANY_h
#define _ANY_h

#include "Stack.h"

class ANY {
 public:
  ANY();
  virtual ~ANY();

  static void join(UA<ANY *> &, String &, String);

  virtual String type();
  virtual String toString();
  virtual String toForm();
  virtual double toDouble();
  virtual UA<ANY *> toArray();
};

class STR : public ANY {
 public:
  String x;

  STR(String);

  String type() override;
  String toString() override;
  String toForm() override;
  double toDouble() override;
  UA<ANY *> toArray() override;
};

class CMD : public ANY {
 public:
  String x;

  CMD(String);

  String type() override;
  String toString() override;
  String toForm() override;
  double toDouble() override;
  UA<ANY *> toArray() override;
};

class NUM : public ANY {
 public:
  double x;

  NUM(double);

  String type() override;
  String toString() override;
  String toForm() override;
  double toDouble() override;
  UA<ANY *> toArray() override;
};

class FN : public ANY {
 public:
  UA<ANY *> x;

  FN(UA<ANY *> &);

  String type() override;
  String toString() override;
  String toForm() override;
  double toDouble() override;
  UA<ANY *> toArray() override;
};

class ARR : public ANY {
 public:
  UA<ANY *> x;

  ARR(UA<ANY *> &);

  String type() override;
  String toString() override;
  String toForm() override;
  double toDouble() override;
  UA<ANY *> toArray() override;
};

#endif