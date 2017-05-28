#all: main

#main: image.o feature.o loader.o main.cpp
#	mpic++ main.cpp image.o feature.o loader.o -o main

#loader.o: loader.cpp loader.hpp image.cpp image.hpp
#	g++ -c loader.cpp

#feature.o: feature.cpp util.hpp feature.hpp
#	g++ -c feature.cpp

#image.o: image.cpp image.hpp util.hpp
#	g++ -c image.cpp

#clean:
#	rm main *.o

# user-definable settings
TRIVIAL =      # 1=YES, [empty] = no
DEBUG =        # 1=YES, [empty] = no
SETUP = sallesinfo # possibilities: macosx, ubuntu, sallesinfo

# defines and compiler
DEFINES =
CXX = c++

DEFINES =
MPICXX = mpic++

DEFINES =
GXX = g++

ifdef TRIVIAL
  DEFINES += -DTRIVIAL
endif

# flags
FLAGS = $(DEFINES)
ifdef DEBUG
  FLAGS += -g
else
  FLAGS += -O3
endif

ifeq "$(SETUP)" "sallesinfo "
  ## salles informatiques @X
  $(info building for $(SETUP))
  INCLUDE = -I/usr/local/boost-1.58.0/include/ -I/usr/local/CImg-1.6.2/
  LIBS = -lpthread -lX11 -L/usr/local/boost-1.58.0/lib/
  LDPATH = LD_LIBRARY_PATH=/usr/local/boost-1.58.0/lib:/usr/lib/alliance/lib
endif

ifeq "$(SETUP)" "ubuntu "
  # ubuntu linux
  $(info building for $(SETUP))
  INCLUDE =
  LIBS = -lpthread -lX11
  LDPATH =
endif

ifeq "$(SETUP)" "macosx "
  # macosx
  $(info building for $(SETUP))
  INCLUDE = -I/usr/local/include -I/opt/X11/include
  LIBS = -lpthread -L/usr/local/lib -L/opt/X11/lib -lX11
  DEFINES += -std=c++0x
  LDPATH = DYLD_LIBRARY_PATH=/usr/local/lib
endif

# name of executable
BIN = main

# object files it depends on
OBJS = loader.o image.o feature.o

# remove command
RM = rm -f

# default rule - typing "make" will start this rule
#   the dependency is on Makefile itself (so if the Makefile was changed
#   the whole project is rebuilt) and on the executable
all:	$(BIN) Makefile

# rule to build the executable
$(BIN): $(OBJS) $(BIN).cpp Makefile
	$(MPICXX) $(FLAGS) $(INCLUDE) -o $(BIN) $(BIN).cpp $(OBJS) $(LIBS)

loader.o: image.* loader.* Makefile
	$(MPICXX) $(FLAGS) $(INCLUDE) -o $@ loader.cpp $(LIBS)

image.o: image.* feature.* Makefile
	$(MPICXX) $(FLAGS) $(INCLUDE) -o $@ image.cpp $(LIBS)

feature.o: feature.* Makefile
	$(MPICXX) $(FLAGS) $(INCLUDE) -o $@ feature.cpp $(LIBS)

# clean objects and executable
clean:
	$(RM) $(OBJS) $(BIN) main

# restore directory to pristine state
distclean: clean
	$(RM) core *~

# catch-all rule to compile object files
#   $@ refers to the rule name (.o) and %< to the first item in rule (.cpp)
%.o:	%.cpp %.h Makefile
	$(CXX) $(FLAGS) $(INCLUDE) -c -o $@ $<
