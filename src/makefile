# Compiler version and flags
CC=gcc
CFLAGS=-Wall -pedantic -I $(IDIR)

# Directories
ODIR=./obj
LDIR =../lib
IDIR =../include
# # Macro for common libraries: math
# LIBS=-lm

# List all .h and .c files
_DEPS = header.h
_OBJ = main.o source.o
_OBJ_SERVER = server.o source.o
_OBJ_CLIENT = client.o source.o


# Create directories for the header files
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# Create the directories for object files
# using the object file list and object dir
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
OBJ_SERVER = $(patsubst %,$(ODIR)/%,$(_OBJ_SERVER))
OBJ_CLIENT = $(patsubst %,$(ODIR)/%,$(_OBJ_CLIENT))

# Create dependencies between the .o, .c and .h files
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Compile everything.
.PHONY: all

all: start server client

# Compile command for start
start: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# Compile command for server
server: $(OBJ_SERVER)
	$(CC) -o server $^ $(CFLAGS) $(LIBS)

# Compile command for client
client: $(OBJ_CLIENT)
	$(CC) -o client $^ $(CFLAGS) $(LIBS)

# clean
.PHONY: clean
clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ start server client
