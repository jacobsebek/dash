# > Dash >
Dash is a simple low-level data structure library written in C99.
Its features include:
* Vectors
* Convenient dynamic string tools
* Queues
* Stacks
* Linked lists
* Simplified access to files

## How to use
The installation is very straight forward as Dash is just plain C. Make sure you have `gcc` and binutils' `ar` in PATH (default GCC/MinGW installation) and simply run the `compile` script. This creates the file `libdash.a` in the directory.  
You can compile your projects with it by simply adding `-Ipath_to_include_folder -Lpath_to_lib_folder -ldash` to GCC
