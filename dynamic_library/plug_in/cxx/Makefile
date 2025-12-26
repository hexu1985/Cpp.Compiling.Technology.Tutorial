
CREATE_SO = g++ -shared
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -c -std=c++11 #-DNDEBUG
TARGETS = client

.PHONY: all
all: $(TARGETS)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) $(TARGETS) *.o *.so

.PHONY: distclean
distclean:
	$(RM) $(TARGETS) *.o *.so

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -fPIC $<

client: client.o dictionary_manager.o
	$(CXX) -o $@ $^ -ldl

