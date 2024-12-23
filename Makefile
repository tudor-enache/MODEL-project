# flags
CFLAGS = -Iinclude -Wall -Wextra -g

# object files for each compilation target
OBJ_1 = build/gen_mult.o \
		build/utils.o \
		build/naive_multiplication.o \
		build/strassen_multiplication.o

OBJ_2 = build/gen_inv.o \
		build/utils.o \
		build/naive_multiplication.o \
		build/strassen_multiplication.o \
		build/lu_decomposition.o \
		build/lu_inversion.o \
		build/strassen_inversion.o

# target executables
TARGET_1 = bin/gen_mult
TARGET_2 = bin/gen_inv

# rules
all: setup $(TARGET_1) $(TARGET_2)

setup:
	mkdir -p bin build data

# rules for implementation files
build/utils.o: src/utils.c include/utils.h
	gcc $(CFLAGS) -c src/utils.c -o build/utils.o

build/lu_decomposition.o: src/lu_decomposition.c include/lu_decomposition.h include/utils.h
	gcc $(CFLAGS) -c src/lu_decomposition.c -o build/lu_decomposition.o

build/lu_inversion.o: src/lu_inversion.c include/lu_inversion.h include/utils.h
	gcc $(CFLAGS) -c src/lu_inversion.c -o build/lu_inversion.o

build/naive_multiplication.o: src/naive_multiplication.c include/naive_multiplication.h include/utils.h
	gcc $(CFLAGS) -c src/naive_multiplication.c -o build/naive_multiplication.o

build/strassen_inversion.o: src/strassen_inversion.c include/strassen_inversion.h include/lu_inversion.h include/utils.h
	gcc $(CFLAGS) -c src/strassen_inversion.c -o build/strassen_inversion.o

build/strassen_multiplication.o: src/strassen_multiplication.c include/strassen_multiplication.h include/naive_multiplication.h include/utils.h
	gcc $(CFLAGS) -c src/strassen_multiplication.c -o build/strassen_multiplication.o

# rules for generating multiplication timings
$(TARGET_1): $(OBJ_1)
	gcc $(CFLAGS) -o $(TARGET_1) $(OBJ_1)

build/gen_mult.o: src/generate_mult.c include/*
	gcc $(CFLAGS) -c src/generate_mult.c -o build/gen_mult.o

# rules for generating inversion timings
$(TARGET_2): $(OBJ_2)
	gcc $(CFLAGS) -o $(TARGET_2) $(OBJ_2)

build/gen_inv.o: src/generate_inv.c include/*
	gcc $(CFLAGS) -c src/generate_inv.c -o build/gen_inv.o

# cleaning command
clean:
	rm -rf bin build