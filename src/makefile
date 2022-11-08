# Compiler version and flags
CC=gcc
CFLAGS= -std=gnu99 -g -Wall -pedantic -I $(IDIR)


PROGRAM=start
TESTER=as1_testbench

# Directories
ODIR=./obj
LDIR =../lib
IDIR =../include

# List all .h and .c files
_DEPS = start.h server.h client.h delay.h morse.h
_OBJ = start.o delay.o
_OBJ_BENCH = as1_testbench.o
_OBJ_SERVER = server.o delay.o morse.o
_OBJ_CLIENT = client.o delay.o morse.o

TFLAGS=-std=gnu99 -g -Wall -pedantic

# Create directories for the header files
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Create the directory lists for object files
# using the object file list and object dir
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
OBJ_BENCH = $(patsubst %,$(ODIR)/%,$(_OBJ_BENCH))
OBJ_SERVER = $(patsubst %,$(ODIR)/%,$(_OBJ_SERVER))
OBJ_CLIENT = $(patsubst %,$(ODIR)/%,$(_OBJ_CLIENT))

# Create dependencies between the .o, .c and .h files
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Compile everything.
.PHONY: all
all: start server client bench

# Compile command for bench
bench: $(OBJ_BENCH)
	$(CC) -o bench $^ $(TFLAGS)

# Compile command for start
start: $(OBJ)
	$(CC) -o start $^ $(CFLAGS) $(LIBS)

# Compile command for server
server: $(OBJ_SERVER)
	$(CC) -o server $^ $(CFLAGS) $(LIBS)

# Compile command for client
client: $(OBJ_CLIENT)
	$(CC) -o client $^ $(CFLAGS) $(LIBS)

# clean
.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ start server client bench
