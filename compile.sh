#! /bin/bash

gcc -Wall  \
    -I/usr/local/lib/erlang/usr/include  \
    -fPIC  \
    -o simple_nif.so  \
    -shared  \
    simple_nif.c simple.c
