CXX = g++
CXXFLAGS = -g3 -Wall -Wextra -I.

PROG_OBJS = main.o 
PROGRAM = FactoryMethod 

LIB_HDRS = $(shell ls */*.hpp)
LIBRARYS = idcard/libidcard.a framework/libframework.a

.PHONY: all
all: $(PROGRAM)

$(PROGRAM): $(PROG_OBJS) $(LIBRARYS)
	$(CXX) -o $@ $(PROG_OBJS) $(LIBRARYS)

$(LIBRARYS): T := all
$(LIBRARYS): libs_everything

libs_everything:
	$(MAKE) $(T) --directory=framework
	$(MAKE) $(T) --directory=idcard

%.o: %.cpp $(LIB_HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY:
clean: T := clean
clean: libs_everything
	$(RM) $(PROGRAM) $(PROG_OBJS) 
