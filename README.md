# my_nm/my_objdump

A rudimentary implementation of the nm and objdump commands in C.

## Build

To build the project you can use the following command :

```
make                build the project
make re             clean and rebuild the project
make clean          clean object files
make fclean         clean object files and shared library
```

The result of the build are the `my_nm` and `my_objdump` binaries.

## Usage

### my_nm

```
./my_nm <binary/library file path> ...
```

### my_objdump

```
./my_objdump <binary/library file path> ...
```