#!/usr/bin/make

ESDK=$(EPIPHANY_HOME)

ELIBS=$(ESDK)/tools/host/lib
EINCS=$(ESDK)/tools/host/include
ELDF=$(ESDK)/bsps/parallella_E16G3_1GB/internal.ldf

EPCC=epiphany-elf-gcc
EPAR=epiphany-elf-ar
EPRL=epiphany-elf-ranlib

EPCFLAGS=-O2 -mfp-mode=int -ffast-math 
EPARFLAGS=--target=elf32-epiphany
EPLDFLAGS=-L.
#EPLDLIBS=-le-lib -lsecp256k1
EPLDLIBS=-le-lib

CFLAGS=-g -pg -O2 -Wall
RANL=ranlib
LDFLAGS=-L.
LDLIBS=-lbig32
EXES = libepiphany-big32.a libbig32.a

all:	$(EXES)

libbig32.a:	big32lib.o \
	big32_print.o big32_promotrunc.o \
	big32_u64_basic.o big32_u128_basic.o big32_u256_basic.o \
	big32_u64_mul64.o big32_u64_mul128.o \
	big32_u128_mul128.o big32_u128_mul256.o \
	big32_u256_mul256.o big32_u256_mul512.o \
	big32_u64_shift.o big32_u128_shift.o big32_u256_shift.o \
	big32_divlut_5_16.o \
	big32_u64_divide.o big32_u128_divide.o big32_u256_divide.o \
	big32_f64_basic.o big32_f128_basic.o big32_f256_basic.o \
	big32_f64_mul.o big32_f128_mul.o big32_f256_mul.o \
	big32_f64_inv.o big32_f128_inv.o big32_f256_inv.o \
	big32_f256_point.o
	$(AR) rcs $@ $^
	$(RANL) $@ 

libepiphany-big32.a:	big32lib.epio \
	big32_print.epio big32_promotrunc.epio \
	big32_u64_basic.epio big32_u128_basic.epio big32_u256_basic.epio \
	big32_u64_mul64.epio big32_u64_mul128.epio \
	big32_u128_mul128.epio big32_u128_mul256.epio \
	big32_u256_mul256.epio big32_u256_mul512.epio \
	big32_u64_shift.epio big32_u128_shift.epio big32_u256_shift.epio \
	big32_divlut_5_16.epio \
	big32_u64_divide.epio big32_u128_divide.epio big32_u256_divide.epio \
	big32_f64_basic.epio big32_f128_basic.epio big32_f256_basic.epio \
	big32_f64_mul.epio big32_f128_mul.epio big32_f256_mul.epio \
	big32_f64_inv.epio big32_f128_inv.epio big32_f256_inv.epio \
	big32_f256_point.epio
	$(AR) rcs $@ $^
	$(RANL) $@ 

clean:
	rm -f $(EXES)
	rm -f *.o *.epio *.asm-list

%.epio: %.c
	$(EPCC) $(EPCFLAGS) -Wa,-adhln=$<.asm-list -g -fverbose-asm -c $< -o $@ 

