# Compilation
The makefile can be run with multiple parameters.

Running it with "setup" ("$ make setup") builds the directories in which the executable, object and data files will be built. This should be run before trying to build any of the executables.

The other two targets are "bin/gen_mult" and "bin/gen_inv" (e.g. "$ make bin/gen_mult"). They can be built individually, or together by running make with no parameter.

# Trying out the code
The Makefile builds two executables: "bin/gen_mult" and "bin/gen_inv". These executables respectively test the correctness of our implementations of multiplication and inversion, and create data for analysis. 

We have included data in our submission already. To generate new data, the files "src/generate_mult.c" and "src/generate_inv.c" contain a variable "generate" which must be set to 1. By default, the matrices which we create are randomly generated. They are printed out together with their results after different operations.

After data is generated it can be visualised by running the files from the "plot" directory with a Python interpreter (we worked with Python version 3.10).