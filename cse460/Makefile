
CC = g++
PROG    = dot_product
LIBSDL =  -L/usr/local/lib -Wl,-rpath,/usr/local/lib -lSDL -lpthread
INCLS   =  -I/usr/local/include/SDL
#source codes
SRCS = $(PROG).cpp
#substitute .c by .o to obtain object filenames
OBJS = $(SRCS:.cpp=.o)
 
#$< evaluates to the target's dependencies,
#$@ evaluates to the target
 
$(PROG): $(OBJS)
        $(CC) -o $@ $(OBJS)   $(LIBSDL)
 
$(OBJS):
        $(CC) -c  $*.cpp $(INCLS)
 
clean:
        rm $(OBJS)


