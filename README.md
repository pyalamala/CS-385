# CS-385
Stevens Institute of Technology Data Structures (CS 385)

Build Docker Image:
```bash
docker build -f Dockerfile -t cs:latest .
```

Valgrind 
```bash
valgrind <executable> --leak-check=yes
```

[Makefile](https://gist.github.com/robertschaedler3/9f08ad456da951cbe609c2fc8eb67146):
```shell
CXX      = g++
CXX_FILE = $(wildcard *.cpp)
TARGET   = $(patsubst %.cpp,%,$(CXX_FILE))
CXXFLAGS = -g -std=c++11 -Wall -Werror -pedantic-errors -fmessage-length=0

all:
	$(CXX) $(CXXFLAGS) $(CXX_FILE) -o $(TARGET)
clean:
	rm -f $(TARGET) $(TARGET).exe
```