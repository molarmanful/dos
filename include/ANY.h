#ifndef _ANY_h
#define _ANY_h

#include "deps.h"

template <typename T>
class Ls {
 public:
  static void listCopy(List<T>&, List<T>&);
};

class ANY {
 public:
  ANY();
  virtual ~ANY();

  virtual String type();
  virtual String toString();
  virtual String toForm();
  virtual double toDouble();
  virtual List<ANY*> toList();
};

class STR : public ANY {
 public:
  String x;

  STR(String);

  String type() override;
  String toString() override;
  String toForm() override;
  double toDouble() override;
  List<ANY*> toList() override;
};

class CMD : public ANY {
 public:
  String x;

  CMD(String);

  String type() override;
  String toString() override;
  String toForm() override;
  double toDouble() override;
  List<ANY*> toList() override;
};

class NUM : public ANY {
 public:
  double x;

  NUM(double);

  String type() override;
  String toString() override;
  String toForm() override;
  double toDouble() override;
  List<ANY*> toList() override;
};

class FN : public ANY {
 public:
  List<ANY*> x;

  FN(List<ANY*>&);

  String type() override;
  String toString() override;
  String toForm() override;
  double toDouble() override;
  List<ANY*> toList() override;
};

#endif