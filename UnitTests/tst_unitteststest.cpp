#include <QString>
#include <QtTest>
#include <iostream>
#include <sstream>

#include "logger.h"

class UnitTestsTest : public QObject
{
    Q_OBJECT

public:
    UnitTestsTest();

private Q_SLOTS:
    void testCase1();
};

UnitTestsTest::UnitTestsTest()
{
}

void UnitTestsTest::testCase1()
{
    std::stringstream s;
    Logger* l = new Logger(s);
    QVERIFY2(l != nullptr, "Logger instance not created");
    string msg = "Some log";
    l->logInfo(msg);
    QVERIFY2(("INFO: " + msg).compare(s.str()) == 0, "log does not match with the message");
    delete l;
}

QTEST_APPLESS_MAIN(UnitTestsTest)

#include "tst_unitteststest.moc"
