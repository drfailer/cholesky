CC=g++
CXXFLAGS=-Wall -Wextra -Wuninitialized -MMD -g -fdiagnostics-color=auto
LDFLAGS=-lopenblas
SRC=$(wildcard *.cc)
OBJ=$(addprefix build/,$(SRC:.cc=.o))
DEP=$(addprefix build/,$(SRC:.cc=.d))

cholesky: $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

build/%.o: %.cc
	@mkdir -p build
	$(CC) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf build

-include $(DEP)
