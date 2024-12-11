# flags
CFLAGS = -Iinclude -Wall -Wextra -g

# object files for each compilation target
OBJ_1 = build/correct.o \
		build/utils.o \
		build/lu_decomposition.o \
		build/lu_inversion.o \
		build/naive_multiplication.o \
		build/strassen_inversion.o \
		build/strassen_multiplication.o 

# target executables
TARGET_1 = bin/correct

# rules
all: setup $(TARGET_1)

setup:
	mkdir -p bin build data

# rules for implementation files
build/utils.o: src/utils.c include/utils.h
	gcc $(CFLAGS) -c src/utils.c -o build/utils.o

build/lu_decomposition.o: src/lu_decomposition.c include/lu_decomposition.h
	gcc $(CFLAGS) -c src/lu_decomposition.c -o build/lu_decomposition.o

build/lu_inversion.o: src/lu_inversion.c include/lu_inversion.h
	gcc $(CFLAGS) -c src/lu_inversion.c -o build/lu_inversion.o

build/naive_multiplication.o: src/naive_multiplication.c include/naive_multiplication.h include/utils.h
	gcc $(CFLAGS) -c src/naive_multiplication.c -o build/naive_multiplication.o

build/strassen_inversion.o: src/strassen_inversion.c include/strassen_inversion.h
	gcc $(CFLAGS) -c src/strassen_inversion.c -o build/strassen_inversion.o

build/strassen_multiplication.o: src/strassen_multiplication.c include/strassen_multiplication.h include/naive_multiplication.h include/utils.h
	gcc $(CFLAGS) -c src/strassen_multiplication.c -o build/strassen_multiplication.o

# rules for testing correctness
$(TARGET_1): $(OBJ_1)
	gcc $(OBJ_1) -o $(TARGET_1)

build/correct.o: src/test_correctness.c include/*
	gcc $(CFLAGS) -c src/test_correctness.c -o build/correct.o

# cleaning command
clean:
	rm -rf bin build