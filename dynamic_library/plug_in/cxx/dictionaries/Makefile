
CREATE_SO = g++ -shared
RM = rm -f
CXX = g++
CXXFLAGS = -Wall -g -c -std=c++11 -I../ #-DNDEBUG
LIB1_OBJS = german_english_dictionary.o
LIB1_NAME = libgerman_english_dictionary.so
LIB2_OBJS = german_french_dictionary.o
LIB2_NAME = libgerman_french_dictionary.so

.PHONY: all
all: $(LIB1_NAME) $(LIB2_NAME)
	@echo "build OK!"

.PHONY: clean
clean:
	$(RM) *.o *.so

.PHONY: distclean
distclean:
	$(RM) $(TARGETS) *.o *.so

$(LIB1_NAME): $(LIB1_OBJS)
	$(CREATE_SO) $^ -o $(LIB1_NAME) 

$(LIB2_NAME): $(LIB2_OBJS)
	$(CREATE_SO) $^ -o $(LIB2_NAME) 

$(LIB1_OBJS):%.o: %.cpp
	$(CXX) $(CXXFLAGS) -fPIC $^

$(LIB2_OBJS):%.o: %.cpp
	$(CXX) $(CXXFLAGS) -fPIC $^

