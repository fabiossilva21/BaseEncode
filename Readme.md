# BaseEncode
This library implements the various types of encoding described in [RFC4648](https://tools.ietf.org/html/rfc4648), including Base16, Base32 and Base64.

## Usage
This is meant to be a portable library, that means, it should be compiled and ready to use with any project.
There is one namespace `BaseEncode` with multiple functions, `Base32Encode` and `Base32Decode` as an example.

## Supported platforms 
This library makes use of C++ version 14, although it should be able to be compiled in previous versions.
The library was tested in Linux (Debian) but should run in any other platform.

### Compilation process
For compilation purposes, a Makefile was included in the project to ease the compilation process, however the Makefile only generates the object (.o) file and the linkage should be handled by the programmer using it.

## Prerequisites
* [GNU Make](https://www.gnu.org/software/make/) (version 4.2.1 or higher)
* C++14 compatible toolchain (g++ 8.3.0 works fine)