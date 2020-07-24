include_dirs = -Iinc
CPPFLAGS = $(include_dirs) -std=c++14 -g

all: out/baseencode.o out/test run

out/baseencode.o: src/BaseEncode.cpp inc/BaseEncode.hpp
	mkdir -p out
	g++ $(CPPFLAGS) -c src/baseencode.cpp -o out/baseencode.o

out/test: out/baseencode.o tests/BaseEncodeTest.cpp
	g++ $(CPPFLAGS) out/baseencode.o tests/BaseEncodeTest.cpp -o out/test

run: out/test
	./out/test

clean: 
	rm -rf out/