CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
INCLUDEDIR = -I/opt/homebrew/Cellar/boost/1.87.0_1/include/ -I/opt/homebrew/Cellar/sfml/3.0.0_1/include/
LIBDIR = -L/opt/homebrew/Cellar/boost/1.87.0_1/lib/ -L/opt/homebrew/Cellar/sfml/3.0.0_1/lib/
DEPS = EDistance.hpp
# Object files
OBJECTS = EDistance.o
# Program and test names
PROGRAM = EDistance
TEST_EXEC = test
STATIC_LIB = EDistance.a

.PHONY: all clean lint

all: $(PROGRAM) $(TEST_EXEC) $(STATIC_LIB)

# Compile object files from corresponding .cpp files
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(INCLUDEDIR)

# Build main program
$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)

# Create static library
$(STATIC_LIB): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

test.o: test.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(INCLUDEDIR) -DTEST

$(TEST_EXEC): test.o EDistance.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIB)	

# Cleanup
clean:
	rm -f *.o $(PROGRAM) $(STATIC_LIB) $(TEST_EXEC)

# Run linter
lint:
	cpplint *.cpp *.hpp
