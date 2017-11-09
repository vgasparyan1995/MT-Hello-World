# Multithreaded Hello World

The working tree consists of `src/` directory with all the source files in it, a makefile and a `test.sh` bash script.
There are two executable targets defined in the makefile. Use
```
make
```
to build them both.
It will create a subdirectory called `objects/` with all compiled object files in it and two executables: `hello_world` and `mp_hello_world`.
To build only one of them use:
```
make hello_world
```
or
```
make mp_hello_world
```
The usage of both executables is as follows:
```
hello_world           # This prints "Hello World!" continuously
hello_world -n 30     # This prints "Hello World!" exactly 30 times
```
What the `test.sh` script does is build these executables if they are not already, run them with several different configs and check the results.
So you can use
```
make
./test.sh
```
or
```
./test.sh # It will build first if necessary
```
