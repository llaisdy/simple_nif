#! /bin/bash

gcc \
    -Wall  \
    -arch i386 -arch x86_64  \
    -I/usr/local/lib/erlang/usr/include  \
    -fPIC  \
    -bundle -flat_namespace -undefined suppress  \
    -o simple_nif.so  \
    simple_nif.c simple.c
