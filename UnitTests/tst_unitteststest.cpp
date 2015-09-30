#include <QString>
#include <QtTest>
#include <iostream>
#include <sstream>
#include <memory>
#include <thread>
#include <vector>

#include "logger.h"

using namespace std;

class UnitTestsTest : public QObject
{
    Q_OBJECT

public:
    UnitTestsTest(){}

private Q_SLOTS:
    void tcApi1();
    void tcApi2();
    void tcApi3();
    void tcApi4();
    void tcApi5();
    void tcApi6();
    void tcApi7();
    void tcImpl1();
    void tcImpl2();
    void tcThreading1();
    void tcThreading2();
};

class Point3D
{
public:
    Point3D(int x, int y, int z)
        : xCoord(x), yCoord(y), zCoord(z)
    {}
    friend std::ostream& operator<<(std::ostream& out, const Point3D& p){
       return out << "Point(" << p.xCoord << "," << p.yCoord << "," << p.zCoord << ")";
    }

private:
    int xCoord;
    int yCoord;
    int zCoord;
};

// Test cases
void UnitTestsTest::tcApi1()
{
    stringstream s;
    Logger<string> l(s);
    string msg = "Some log";
    l.logInfo(msg);
    QVERIFY2(("INFO: " + msg + "\n").compare(s.str()) == 0, "log does not match with the message");
}

void UnitTestsTest::tcApi2()
{
    stringstream s;
    Logger<string> l(s);
    string msg = "Some log";
    l.logWarning(msg);
    QVERIFY2(("WARN: " + msg + "\n").compare(s.str()) == 0, "log does not match with the message");
}

void UnitTestsTest::tcApi3()
{
    stringstream s;
    Logger<string> l(s);
    string msg = "Some log";
    l.logError(msg);
    QVERIFY2(("ERROR: " + msg + "\n").compare(s.str()) == 0, "log does not match with the message");
}

void UnitTestsTest::tcApi4()
{
    stringstream s;
    Logger<string> l(s);
    string msg = "Some log";
    l.logDebug(msg);
    QVERIFY2(("DEBUG: " + msg + "\n").compare(s.str()) == 0, "log does not match with the message");
}

void UnitTestsTest::tcApi5()
{
    stringstream s;
    Logger<int> l(s);
    l.logDebug(234);
    string ss = "DEBUG: 234\n";
    QVERIFY2(ss.compare(s.str()) == 0, "log does not match with the message");
}

void UnitTestsTest::tcApi6()
{
    stringstream s;
    Logger<float> l(s);
    l.logDebug(23.45);
    string ss = "DEBUG: 23.45\n";
    QVERIFY2(ss.compare(s.str()) == 0, "log does not match with the message");
}

void UnitTestsTest::tcApi7()
{
    stringstream s;
    Point3D point(24, 56, 78);
    Logger<Point3D> l(s);

    l.logDebug(point);
    string ss = "DEBUG: Point(24,56,78)\n";
    QVERIFY2(ss.compare(s.str()) == 0, "log does not match with the message");
}

void UnitTestsTest::tcImpl1()
{
    stringstream s;
    Logger<string> l(s);
    QVERIFY2(l.pimpl != nullptr, "Logger pimpl instance not created");
}

void UnitTestsTest::tcImpl2()
{
    stringstream s;
    Logger<string> l(s);
    QVERIFY2(l.pimpl != nullptr, "Logger pimpl instance not created");

    l.pimpl->log("some");
    l.pimpl->log("text");
    l.pimpl->log("I");
    l.pimpl->log("need");
    l.pimpl->log("to");
    l.pimpl->log("see");
    l.pimpl->log("in");
    l.pimpl->log("order");

    string log = "some\ntext\nI\nneed\nto\nsee\nin\norder\n";
    QVERIFY2(log.compare(s.str()) == 0, "log does not match with the stream messages");
}

void UnitTestsTest::tcThreading1()
{
    stringstream s;
    Logger<string> l(s);

    std::thread th([](auto logger){
        logger.logInfo("log me");
    }, l);
    th.join();

    string msg = "INFO: log me\n";
    QVERIFY2(msg.compare(s.str()) == 0, "message does not match with the log stream");
}

void UnitTestsTest::tcThreading2()
{
    stringstream s;
    Logger<string> l(s);

    list<std::thread> ths;
    for (int i = 0; i < 10; i++) {
        auto str = "log " + to_string(i);
        ths.push_back(std::thread([str](auto logger){
            logger.logInfo(str);
        }, l));
    }

    for (auto& th : ths) {
        th.join();
    }

    stringstream msg;
    for (int j = 0; j < 10; j++) {
        msg << "INFO: log " + to_string(j) << endl;
    }

    QVERIFY2(msg.str().compare(s.str()) == 0, "message does not match with the log stream");
}

QTEST_APPLESS_MAIN(UnitTestsTest)

#include "tst_unitteststest.moc"
