#!/bin/bash -xe

gcc -fPIC -shared -std=c99 -Wno-deprecated-declarations \
    -o dpi_rng.so \
    rng.c dpi_wrapper.c \
    -lcrypto

verilator --binary -j 0 -sv --top-module tb \
    -CFLAGS "-std=c99 -Wno-deprecated-declarations" \
    -LDFLAGS "-lcrypto" \
    tb.sv rng.c dpi_wrapper.c
