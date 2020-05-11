//
// Created by christopher on 16.04.2020.
//

#include "Tests.h"
#include "model/Sample.h"

#include <QImageWriter>
#include <QTemporaryFile>

using namespace waft::model;

void Tests::testParsing() {
  // Create a temporary file in current working directory
  QTemporaryFile file("example_XXXXXX.jpg");
  QVERIFY(file.open());
  {
    QImage image(64, 64, QImage::Format_RGB32);
    image.fill(Qt::red);
    QImageWriter writer(file.fileName());
    QVERIFY2(writer.write(image), writer.supportedImageFormats().join(' '));
  }

  // Test invalid sample
  auto sample_1 = Sample::parse("");
  QVERIFY(!sample_1);
  QVERIFY(!sample_1.isMeaningful());

  // Test sample with invalid ellipse
  QString buffer;
  QTextStream stream(&buffer);
  auto sample_2 = Sample::parse(file.fileName());
  sample_2.write(stream, QDir());
  auto sample_2_deserialized = Sample::parse(buffer);
  for (auto &sample: {sample_2, sample_2_deserialized}) {
    QVERIFY(sample_2);
    QVERIFY(!sample_2.isMeaningful());
  }

  // Test valid sample
  buffer.clear();
  auto sample_3 = Sample::parse(file.fileName() + "\t0.5\t0.6\t0.2\t0.1\t-42");
  sample_3.write(stream, QDir());
  auto sample_3_deserialized = Sample::parse(buffer);
  for (auto &sample: {sample_3, sample_3_deserialized}) {
    QVERIFY(sample);
    QVERIFY(sample.isMeaningful());
    QCOMPARE(sample.ellipse().position(), QPointF(0.5f, 0.6f));
    QCOMPARE(sample.ellipse().axes(), QPointF(0.2f, 0.1f));
    QCOMPARE(sample.ellipse().rotation(), 318);
  }
}

void Tests::testEllipse() {
  Ellipse ellipse;

  ellipse.setRotation(0);
  QCOMPARE(ellipse.rotation(), 0);

  ellipse.setRotation(359.9f);
  QCOMPARE(ellipse.rotation(), 359.9f);

  ellipse.setRotation(360);
  QCOMPARE(ellipse.rotation(), 0);

  ellipse.setRotation(402);
  QCOMPARE(ellipse.rotation(), 42);

  ellipse.setRotation(-42);
  QCOMPARE(ellipse.rotation(), 318);
}
