# flags
CFLAGS = -Iinclude -Wall -Wextra -g

# object files for each compilation target
OBJ_1 = build/lu_decomposition.o build/lu_inversion.o build/naive_mutliplication.o build/strassen_inversion.o build/strassen_multiplication.o

# target executables
TARGET_1 = bin/correct

# rules
all: setup $(TARGET_1)

setup:
	mkdir -p bin build data

# rules for implementation files
build/lu_decomposition.o: src/lu_decomposition.c include/lu_decomposition.h
	gcc $(CFLAGS) -c src/lu_decomposition.c -o build/lu_decomposition.o

build/lu_inversion.o: src/lu_inversion.c include/lu_inversion.h
	gcc $(CFLAGS) -c src/lu_inversion.c -o build/lu_inversion.o

build/naive_mutliplication.o: src/naive_mutliplication.c include/naive_mutliplication.h
	gcc $(CFLAGS) -c src/naive_mutliplication.c -o build/naive_mutliplication.o

build/strassen_inversion.o: src/strassen_inversion.c include/strassen_inversion.h
	gcc $(CFLAGS) -c src/strassen_inversion.c -o build/strassen_inversion.o

build/strassen_multiplication.o: src/strassen_multiplication.c include/strassen_multiplication.h
	gcc $(CFLAGS) -c src/strassen_multiplication.c -o build/strassen_multiplication.o

# rules for testing correctness
$(TARGET_1): $(OBJ_1)
	gcc $(OBJ_1) -o $(TARGET_1)

build/correct.o: src/testing_correctness.c include/*
	gcc $(CFLAGS) -c src/testing_correctness.c -o build/correct.o

# cleaning command
clean:
	rm -rf bin build