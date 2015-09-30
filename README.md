### A simple C++ logger
With this logger you get a simple API to write logs to an output stream. This maybe a file, console output or a buffer.

### Design choices
The logger uses the PIMPL technique to encapsulate the private implementation so as to have the main API binary compatible after any future changes to the implementation have been made. For multithreading, the logs to the stream are serialized using concurrency primitives. Custom user types can be logged using this logger as well. The user type would however have to overload the operator<< function i.e.
```
std::ostream& operator<<(std::ostream& out, const Point3D& p){
   return out << "Point(" << p.xCoord << "," << p.yCoord << "," << p.zCoord << ")";
}
```

### Improvement ideas
The API can be extended with a function that takes several output stream as a parameter i.e.
```
Logger(std::vector<std::ostream>& outs);
```

Multithreading can also be improved. Instead of synchronising writes to the output stream on the main thread, which would cause performance issues, this can be done on a different worker thread. The Producer Consumer design pattern can be used here for example. Several threads could be producing log messages and the Logger instance would be the consumer. This would require a blocking queue datastructure for example.

### Compilation
To complile you will need the Qt toolchain. If you have the MinGW installation, version 4.9.1 at minimum is required due to dependencies on C++14 features. The latest, Qt 5.5.0 for example will work just fine. Open the .pro file from Qt Creator IDE and build both the Logger and UnitTests. You can run the tests are well.
