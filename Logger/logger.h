#ifndef LOGGER_H
#define LOGGER_H

#include "logger_global.h"
#include <iostream>
#include <memory>
#include <string>
#include "logger_impl.cpp"

template<class T>

/**
 * @brief This is a logging class meant to write logs to an output stream
 * The stream can be a file or the console (std::out).
 */
class LOGGERSHARED_EXPORT Logger
{
    friend class UnitTestsTest;
public:
    Logger(std::ostream& o) : pimpl (new Impl(o)){}
    ~Logger(){ pimpl.reset(); }

    /**
     * @brief logging information. Logs contain an INFO: prefix before the message
     * @param message Log message to show
     */
    void logInfo(const T& message) { log("INFO: " + to_string(message)); }

    /**
     * @brief logging warnings. Logs contain an WARN: prefix before the message
     * @param message Log message to show
     */
    void logWarning(const T& message) { log("WARN: " + to_string(message)); }

    /**
     * @brief logging errors. Logs contain an ERROR: prefix before the message
     * @param message Log message to show
     */
    void logError(const T& message) { log("ERROR: " + to_string(message)); }

    /**
     * @brief logging debug logs. Logs contain an DEBUG: prefix before the message
     * @param message Log message to show
     */
    void logDebug(const T& message) { log("DEBUG: " + to_string(message)); }

private:
    std::shared_ptr<Impl> pimpl;
    void log(std::string msg)
    {
        pimpl->log(msg);
    }
    std::string to_string(const T& val)
    {
        std::stringstream ss;
        ss << val << flush;
        return ss.str();
    }
};

#endif // LOGGER_H
