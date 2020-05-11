//
// Created by christopher on 16.04.2020.
//

#ifndef WAFT_SRC_TESTS_H_
#define WAFT_SRC_TESTS_H_

#include <QtTest>

class Tests : public QObject {
 Q_OBJECT

 public:
  Tests() : QObject(nullptr) {}

 private slots:
  void testParsing();
  void testEllipse();
};

#endif //WAFT_SRC_TESTS_H_