#include "logger.h"

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
};

void Logger::Impl::log(string message)
{
    out << message;
}

Logger::Logger(ostream& o)
    : pimpl (new Impl(o))
{
}

//Public API
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

