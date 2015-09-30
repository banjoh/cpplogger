#include "logger.h"
#include <mutex>

using namespace std;

// Private implementation
class Logger::Impl
{
public:
    Impl(ostream& o) : out(o){}
    ~Impl(){}
    void log(string message);
private:
    ostream& out;
    // Protects concurrent writes to stream
    std::mutex mutex;
};

void Logger::Impl::log(string message)
{
    // Buffer will always be flushed by 'endl' to maintain order of log messages
    // so there is no need to class flush explicitely
    std::lock_guard<std::mutex> lock(mutex);
    out << message << endl;
}

//Public API
Logger::Logger(ostream& o)
    : pimpl (new Impl(o))
{}

Logger::~Logger()
{}

void Logger::logInfo(string message)
{
    pimpl->log("INFO: " + message);
}

void Logger::logWarning(string message)
{
    pimpl->log("WARN: " + message);
}

void Logger::logError(string message)
{
    pimpl->log("ERROR: " + message);
}

void Logger::logDebug(string message)
{
    pimpl->log("DEBUG: " + message);
}

