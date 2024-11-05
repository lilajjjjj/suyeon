SRCS = main.c
LIBSRCS = open.c close.c put.c get.c 
TARG = kvs_static
TARG_DYNAMIC = kvs_dynamic

CC = gcc
OPTS = -Wall -g
LIBS = -L. -lkvs

OBJS = $(SRCS:.c=.o)
LOBJS = $(LIBSRCS:.c=.o)
LARS = libkvs.a
LDSO = libkvs.so

all: static dynamic

static: $(TARG)

$(TARG): $(OBJS) $(LARS)
	$(CC) -o $(TARG) $(OBJS) $(LIBS) -static

$(LARS): $(LOBJS)
	ar rs $(LARS) $(LOBJS)
	@echo "Static library $(LARS) created."

dynamic: $(OBJS) $(TARG_DYNAMIC)

$(TARG_DYNAMIC): $(OBJS) $(LDSO)
	$(CC) -o $(TARG_DYNAMIC) $(OBJS) $(LIBS)
	@echo "Dynamic executable $(TARG_DYNAMIC) created."

$(LDSO): $(LOBJS)
	$(CC) -shared -o $(LDSO) $(LOBJS)
	@echo "Shared library $(LDSO) created."

%.o: %.c
	$(CC) $(OPTS) -c $< -o $@
	@echo "Compiled $< to $@."

clean:
	rm -f $(OBJS) $(LOBJS) $(LARS) $(LDSO) $(TARG) $(TARG_DYNAMIC)
	@echo "Cleaned all generated files."
