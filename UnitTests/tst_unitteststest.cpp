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

private:
    auto threadParam(shared_ptr<Logger>& l, string& msg)
    {
        return std::make_tuple(l, msg);
    }

private Q_SLOTS:
    void tcApi1();
    void tcApi2();
    void tcApi3();
    void tcApi4();
    void tcImpl1();
    void tcImpl2();
    void tcThreading1();
    void tcThreading2();
};

// Test cases
void UnitTestsTest::tcApi1()
{
    stringstream s;
    unique_ptr<Logger> l(new Logger(s));
    QVERIFY2(l != nullptr, "Logger instance not created");
    string msg = "Some log";
    l->logInfo(msg);
    QVERIFY2(("INFO: " + msg + "\n").compare(s.str()) == 0, "log does not match with the message");
}

void UnitTestsTest::tcApi2()
{
    stringstream s;
    unique_ptr<Logger> l(new Logger(s));
    QVERIFY2(l != nullptr, "Logger instance not created");
    string msg = "Some log";
    l->logWarning(msg);
    QVERIFY2(("WARN: " + msg + "\n").compare(s.str()) == 0, "log does not match with the message");
}

void UnitTestsTest::tcApi3()
{
    stringstream s;
    unique_ptr<Logger> l(new Logger(s));
    QVERIFY2(l != nullptr, "Logger instance not created");
    string msg = "Some log";
    l->logError(msg);
    QVERIFY2(("ERROR: " + msg + "\n").compare(s.str()) == 0, "log does not match with the message");
}

void UnitTestsTest::tcApi4()
{
    stringstream s;
    unique_ptr<Logger> l(new Logger(s));
    QVERIFY2(l != nullptr, "Logger instance not created");
    string msg = "Some log";
    l->logDebug(msg);
    QVERIFY2(("DEBUG: " + msg + "\n").compare(s.str()) == 0, "log does not match with the message");
}

void UnitTestsTest::tcImpl1()
{
    stringstream s;
    unique_ptr<Logger> l(new Logger(s));
    QVERIFY2(l != nullptr, "Logger instance not created");
    QVERIFY2(l->pimpl != nullptr, "Logger pimpl instance not created");
}

void UnitTestsTest::tcImpl2()
{
    stringstream s;
    unique_ptr<Logger> l(new Logger(s));
    QVERIFY2(l != nullptr, "Logger instance not created");

    l->logInfo("some");
    l->logInfo("text");
    l->logInfo("I");
    l->logInfo("need");
    l->logInfo("to");
    l->logInfo("see");
    l->logInfo("in");
    l->logInfo("order");

    string log = "INFO: some\nINFO: text\nINFO: I\nINFO: need\nINFO: to\nINFO: see\nINFO: in\nINFO: order\n";
    QVERIFY2(log.compare(s.str()) == 0, "log does not match with the stream messages");
}

void UnitTestsTest::tcThreading1()
{
    stringstream s;
    shared_ptr<Logger> l(new Logger(s));
    QVERIFY2(l != nullptr, "Logger instance not created");

    std::thread th([](auto logger){
        logger->logInfo("log me");
    }, l);
    th.join();

    string msg = "INFO: log me\n";
    QVERIFY2(msg.compare(s.str()) == 0, "message does not match with the log stream");
}

void UnitTestsTest::tcThreading2()
{
    stringstream s;
    shared_ptr<Logger> l(new Logger(s));
    QVERIFY2(l != nullptr, "Logger instance not created");

    list<std::thread> ths;
    for (int i = 0; i < 100; i++) {
        auto str = "log " + to_string(i);
        ths.push_back(std::thread([str](auto logger){
            logger->logInfo(str);
        }, l));
    }

    for (auto& th : ths) {
        th.join();
    }

    stringstream msg;
    for (int j = 0; j < 100; j++) {
        msg << "INFO: log " + to_string(j) << endl;
    }

    QVERIFY2(msg.str().compare(s.str()) == 0, "message does not match with the log stream");
}

QTEST_APPLESS_MAIN(UnitTestsTest)

#include "tst_unitteststest.moc"
