#!/bin/bash

#possible arguments: (e.g. run './build.sh DEBUG NOSHARING' )
#	DEBUG		Print performance measurements, analyze return codes and such
#	NOSHARING	Don't use the CL_KHR_gl_sharing extension - slower, but wider support

for var in "$@"; do
	DEFINES="$DEFINES -D$var"
done

OPT="-Ofast"
WARN="-Weverything -Wno-padded -Wno-format-nonliteral"
LIBS="-lm -lglfw -lOpenCL"

cat kernels/*.cl | ./bufferize.py > src/kernels.src.h
clang -std=c11 $WARN $DEFINES $OPT src/*.c $LIBS -o bin.elf
