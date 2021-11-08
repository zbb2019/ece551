#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  explicit Expression() {}
  virtual std::string toString() const = 0;  //abstract method
  virtual long evaluate() const = 0;         //abstract method
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 protected:
  long number;

 public:
  NumExpression() {}
  explicit NumExpression(long x) : number(x) {}

  virtual std::string toString() const {  //actually implement it
    std::stringstream s;
    s << number;
    return s.str();
  }

  virtual long evaluate() const {  //abstract method
    return number;
  }

  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 protected:
  Expression * l;
  Expression * r;

 public:
  explicit PlusExpression(Expression * lhs, Expression * rhs) : l(lhs), r(rhs) {}

  virtual std::string toString() const {  //actually implement it
    std::stringstream s;
    s << l->toString() << " + " << r->toString() << std::endl;
    return s.str();
  }

  virtual long evaluate() const {  //abstract method
    return l->evaluate() + r->evaluate();
  }

  virtual ~PlusExpression() {
    delete l;
    delete r;
  }
};

class MinusExpression : public Expression {
 protected:
  Expression * l;
  Expression * r;

 public:
  MinusExpression(Expression * lhs, Expression * rhs);

  virtual std::string toString() const {  //actually implement it
    std::stringstream s;
    s << l->toString() << " - " << r->toString() << std::endl;
    return s.str();
  }

  virtual long evaluate() const {  //abstract method
    return l->evaluate() - r->evaluate();
  }

  virtual ~MinusExpression() {
    delete l;
    delete r;
  }
};

class TimesExpression : public Expression {
 protected:
  Expression * l;
  Expression * r;

 public:
  TimesExpression(Expression * lhs, Expression * rhs);

  virtual std::string toString() const {  //actually implement it
    std::stringstream s;
    s << l->toString() << " * " << r->toString() << std::endl;
    return s.str();
  }

  virtual long evaluate() const {  //abstract method
    return l->evaluate() * r->evaluate();
  }

  virtual ~TimesExpression() {
    delete l;
    delete r;
  }
};

class DivExpression : public Expression {
 protected:
  Expression * l;
  Expression * r;

 public:
  DivExpression(Expression * lhs, Expression * rhs);

  virtual std::string toString() const {  //actually implement it
    std::stringstream s;
    s << l->toString() << " / " << r->toString() << std::endl;
    return s.str();
  }

  virtual long evaluate() const {  //abstract method
    return l->evaluate() / r->evaluate();
  }

  virtual ~DivExpression() {
    delete l;
    delete r;
  }
};
