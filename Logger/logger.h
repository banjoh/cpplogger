#ifndef LOGGER_H
#define LOGGER_H

#include "logger_global.h"
#include <iostream>
#include <memory>

using namespace std;

/**
 * @brief This is a logging class meant to write logs to an output stream
 * The stream can be a file or the console (std::out).
 */
class LOGGERSHARED_EXPORT Logger
{
    friend class UnitTestsTest;
public:
    Logger(ostream& o);
    ~Logger();

    // API
    void logInfo(string message);
    void logWarning(string message);
    void logError(string message);
    void logDebug(string message);

private:
    class Impl;
    unique_ptr<Impl> pimpl;
};

#endif // LOGGER_H
