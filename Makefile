EXENAME=nonogram-solver

BUILDDIR=./build

CFLAGS=-std=c++11 -O2 -fopenmp -Wall -pthread -g
LDFLAGS=
INCLUDES=-I./ 
CC=g++

SRCS=$(shell find ./ -name \*.c) $(shell find ./ -name \*.cpp)
OBJS=$(addprefix $(BUILDDIR)/, $(addsuffix .o, $(SRCS)))

.PHONY: all

all: $(OBJS)
	@echo LINK $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o ${EXENAME}

.PHONY: clean
clean:
	rm -rf $(BUILDDIR) core

$(OBJS): $(BUILDDIR)/%.o: %
	@mkdir -p $(dir $@)
	@echo CC $< 
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
