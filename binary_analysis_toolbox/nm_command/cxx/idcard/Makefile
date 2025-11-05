CXX = g++
CXXFLAGS = -fPIC -Wall -std=c++11 -I..
CREATE_SO = g++ -shared

LIBRARY = libidcard.so

SOURCES = $(shell ls *.cpp)
HEADERS = $(shell ls *.hpp)
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

.PHONY: all 
all: $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(CREATE_SO) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(LIBRARY)

