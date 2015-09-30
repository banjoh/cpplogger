#include "logger.h"
template<class T>
void Logger<T>::log(std::string msg)
{
    pimpl->log(msg);
}
