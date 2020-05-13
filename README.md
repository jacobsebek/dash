# > Dash >
Dash (stylized as >Dash>) is a simple low-level data structure manipulation wrapper in C. It allows simplified access to files, nice string tools, queues, stacks, lists, and a vector type.

## How to use
The installation should be very simple. Make sure you have gcc and binutils ar in PATH (default GCC/MinGW installation is ok) and simply run the `compile` script. A new file should pop up in the directory `dash-xx.a`, you can compile your projects with it by adding 
```-Ipath_to_include_folder -Lpath_to_lib_folder -ldash-xx.a```
to GCC