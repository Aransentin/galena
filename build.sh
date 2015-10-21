#!/bin/bash
cat kernels/*.cl | ./bufferize.py > src/kernels.src.h
clang -std=c11 -Weverything -Wno-padded -Wno-format-nonliteral -DDEBUG -Ofast -flto src/*.c -lm -lglfw -lOpenCL -o bin.elf
