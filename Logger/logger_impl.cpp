#include <mutex>
#include <iostream>

using namespace std;

/**
 * @brief Private implementation of the logger class. Extensions of the
 * logger class will be added here
 */
class Impl
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

void Impl::log(string message)
{
    // Buffer will always be flushed by 'endl' to maintain order of log messages
    // so there is no need to class flush explicitely
    mutex.lock();
    out << message << endl;
    mutex.unlock();
}
