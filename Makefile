CC=g++
CXXFLAGS=-Wall -Wextra -Wuninitialized -MMD -O3 -fdiagnostics-color=auto -I$(HOME)/Documents/dev/lib/include/
LDFLAGS=-static -L$(HOME)/Documents/dev/lib/lib/ -lopenblas
SRC=$(wildcard *.cc)
OBJ=$(addprefix build/,$(SRC:.cc=.o))
DEP=$(addprefix build/,$(SRC:.cc=.d))

all: cholesky

cholesky: $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

build/%.o: %.cc
	@mkdir -p build
	$(CC) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf build

-include $(DEP)
