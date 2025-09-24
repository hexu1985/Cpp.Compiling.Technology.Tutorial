CXX = g++
CXXFLAGS = -g3 -Wall -Wextra -I.

LDFLAGS = -Wl,-rpath,'$$ORIGIN/idcard:$$ORIGIN/framework' -Wl,--enable-new-dtags -L./idcard -L./framework
LDLIBS = -lidcard -lframework

PROG_OBJS = main.o 
PROGRAM = FactoryMethod 

LIB_HDRS = $(shell ls */*.hpp)
LIBRARYS = idcard/libidcard.so framework/libframework.so

.PHONY: all
all: $(PROGRAM)

$(PROGRAM): $(PROG_OBJS) $(LIBRARYS)
	$(CXX) $(LDFLAGS) -o $(PROGRAM) $(PROG_OBJS) $(LDLIBS)

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
