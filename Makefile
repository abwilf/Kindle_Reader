## Makefile
CXX=g++
OPTFLAGS=-O3
CXXFLAGS=-Wall -Werror -Wextra -pedantic -std=c++14 $(OPTFLAGS)
LDFLAGS=$(OPTFLAGS)
SOURCES=Kindle_Reader.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXEC=notes

all : $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

install : $(EXEC)
ifndef  $(BINDIR)
	@echo "You have not specified a BINDIR to install the executable to."
else
	cp $(EXEC) $(BINDIR)/
endif

clean :
	rm -f $(EXEC) $(OBJECTS)