# The independent
A humble independent program that rebuilds itself using the go_rebuild_ir_self technology ...

## Inspiration
the [nob.h](https://www.github.com/tsoding/nob.h) library espetialy the auto-rebuild feature .

## Quick start
the program needs to be bootsraped once then it will rebuild itself after any modifications ...

do :
```console
$ gcc -lcrypto -lssl -o main main.c
```
or simply use make :
```console
$ make
```

## Dependencies
The program depends on some standard library functions for reading files and printing to the console .

It also depends on openssl and libcrypto to do some hash calculations cuz that's how i chack for changes, using hash functions seemed more eficient for my little brain .

So you may need to install the libssl if you don't have it on your machine .

You can do that if you have an ubuntu os by running : 
```console
$ sudo apt install libssl-dev
```
