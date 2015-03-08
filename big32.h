/*
 * Copyright (c) 2015, Joseph deBlaquiere
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef	_big_32_h_included
#define	_big_32_h_included

#ifdef __cplusplus
extern "C" {
#endif

//#define		_BIG32_VERIFY_BASIC_MATH
#define		_BIG32_INLINE_COPY

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef union
{
	struct
	{
		uint16_t	lsh;
		uint16_t	s2h;
		uint16_t	s3h;
		uint16_t	msh;
	} r16;
	struct
	{
		uint32_t	lsw;
		uint32_t	msw;
	} r32;
	struct
	{
		uint64_t	lsd;
	} r64;
	uint16_t	hword[4];
	uint32_t	word[2];
	uint64_t	dword[1];
} big32_u64_t ;

typedef union
{
	struct
	{
		uint16_t	lsh;
		uint16_t	s2h;
		uint16_t	s3h;
		uint16_t	s4h;
		uint16_t	s5h;
		uint16_t	s6h;
		uint16_t	s7h;
		uint16_t	msh;
	} r16;
	struct 
	{
		uint32_t	lsw;
		uint32_t	s2w;
		uint32_t	s3w;
		uint32_t	msw;
	} r32;
	struct 
	{
		uint64_t	lsd;
		uint64_t	msd;
	} r64;
	uint16_t	hword[8];
	uint32_t	word[4];
	uint64_t	dword[2];
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	struct
	{
		__uint128_t	lsz;
	} r128;
	__uint128_t	qword[1];
#endif
} big32_u128_t ;

typedef union
{
	struct 
	{
		uint16_t	lsh;
		uint16_t	s2h;
		uint16_t	s3h;
		uint16_t	s4h;
		uint16_t	s5h;
		uint16_t	s6h;
		uint16_t	s7h;
		uint16_t	s8h;
		uint16_t	s9h;
		uint16_t	sah;
		uint16_t	sbh;
		uint16_t	sch;
		uint16_t	sdh;
		uint16_t	seh;
		uint16_t	sfh;
		uint16_t	msh;
	} r16;
	struct 
	{
		uint32_t	lsw;
		uint32_t	s2w;
		uint32_t	s3w;
		uint32_t	s4w;
		uint32_t	s5w;
		uint32_t	s6w;
		uint32_t	s7w;
		uint32_t	msw;
	} r32;
	struct 
	{
		uint64_t	lsd;
		uint64_t	s2d;
		uint64_t	s3d;
		uint64_t	msd;
	} r64;
	uint16_t	hword[16];
	uint32_t	word[8];
	uint64_t	dword[4];
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	struct
	{
		__uint128_t	lsz;
		__uint128_t	msz;
	} r128;
	__uint128_t	qword[2];
#endif
} big32_u256_t ;

typedef union
{
	struct 
	{
		uint16_t	lsh;
		uint16_t	s02h;
		uint16_t	s03h;
		uint16_t	s04h;
		uint16_t	s05h;
		uint16_t	s06h;
		uint16_t	s07h;
		uint16_t	s08h;
		uint16_t	s09h;
		uint16_t	s0ah;
		uint16_t	s0bh;
		uint16_t	s0ch;
		uint16_t	s0dh;
		uint16_t	s0eh;
		uint16_t	s0fh;
		uint16_t	s10h;
		uint16_t	s11h;
		uint16_t	s12h;
		uint16_t	s13h;
		uint16_t	s14h;
		uint16_t	s15h;
		uint16_t	s16h;
		uint16_t	s17h;
		uint16_t	s18h;
		uint16_t	s19h;
		uint16_t	s1ah;
		uint16_t	s1bh;
		uint16_t	s1ch;
		uint16_t	s1dh;
		uint16_t	s1eh;
		uint16_t	s1fh;
		uint16_t	msh;
	} r16;
	struct 
	{
		uint32_t	lsw;
		uint32_t	s2w;
		uint32_t	s3w;
		uint32_t	s4w;
		uint32_t	s5w;
		uint32_t	s6w;
		uint32_t	s7w;
		uint32_t	s8w;
		uint32_t	s9w;
		uint32_t	sAw;
		uint32_t	sBw;
		uint32_t	sCw;
		uint32_t	sDw;
		uint32_t	sEw;
		uint32_t	sFw;
		uint32_t	msw;
	} r32;
	struct 
	{
		uint64_t	lsd;
		uint64_t	s2d;
		uint64_t	s3d;
		uint64_t	s4d;
		uint64_t	s5d;
		uint64_t	s6d;
		uint64_t	s7d;
		uint64_t	msd;
	} r64;
	uint16_t	hword[32];
	uint32_t	word[16];
	uint32_t	dword[8];
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	struct
	{
		__uint128_t	lsz;
		__uint128_t	s2z;
		__uint128_t	s3z;
		__uint128_t	msz;
	} r128;
	__uint128_t	qword[4];
#endif
} big32_u512_t ;

typedef struct {
	big32_u64_t		x;
	big32_u64_t		y;
} big32_f64pt_t ;

typedef struct {
	big32_u128_t	x;
	big32_u128_t	y;
} big32_f128pt_t ;

typedef struct {
	big32_u256_t	x;
	big32_u256_t	y;
} big32_f256pt_t ;

typedef struct {
	big32_u64_t		x;
	big32_u64_t		y;
	big32_u64_t		z;
} big32_f64jpt_t ;

typedef struct {
	big32_u128_t	x;
	big32_u128_t	y;
	big32_u128_t	z;
} big32_f128jpt_t ;

typedef struct {
	big32_u256_t	x;
	big32_u256_t	y;
	big32_u256_t	z;
} big32_f256jpt_t ;


/* prime field constants */

extern big32_u64_t field_p_u64;
extern big32_u128_t field_p_u128;
extern big32_u256_t field_p_u256;


/* convenience functions */

extern void big32_u64_print(char *label, const big32_u64_t *src1);
extern void big32_u128_print(char *label, const big32_u128_t *src1);
extern void big32_u256_print(char *label, const big32_u256_t *src1);


extern void big32_u64_set_zero(big32_u64_t *dest);
extern void big32_u128_set_zero(big32_u128_t *dest);
extern void big32_u256_set_zero(big32_u256_t *dest);


#ifdef	_BIG32_INLINE_COPY
static inline void big32_u64_copy(big32_u64_t *dest, const big32_u64_t *src1)
{
	dest->r64.lsd = src1->r64.lsd ;
}
static inline void big32_u128_copy(big32_u128_t *dest, const big32_u128_t *src1)
{
	dest->r64.lsd = src1->r64.lsd ;
	dest->r64.msd = src1->r64.msd ;
}
static inline void big32_u256_copy(big32_u256_t *dest, const big32_u256_t *src1)
{
	int	count;
	
	for (count = 0; count < 4; count++) {
		dest->dword[count] = src1->dword[count] ; } ;
}
#else
extern void big32_u64_copy(big32_u64_t *dest, const big32_u64_t *src1);
extern void big32_u128_copy(big32_u128_t *dest, const big32_u128_t *src1);
extern void big32_u256_copy(big32_u256_t *dest, const big32_u256_t *src1);
/*extern void big32_u512_copy(big32_u512_t *dest, const big32_u512_t *src1);*/
#endif


/* basic math operations */

extern void big32_u64_add(big32_u64_t *dest, const big32_u64_t *src1, const big32_u64_t *src2);
extern void big32_u128_add(big32_u128_t *dest, const big32_u128_t *src1, const big32_u128_t *src2);
extern void big32_u256_add(big32_u256_t *dest, const big32_u256_t *src1, const big32_u256_t *src2);


extern void big32_u64_pluseq(big32_u64_t *dest, const big32_u64_t *src2);
extern void big32_u128_pluseq(big32_u128_t *dest, const big32_u128_t *src2);
extern void big32_u256_pluseq(big32_u256_t *dest, const big32_u256_t *src2);


extern void big32_u64_sub(big32_u64_t *dest, const big32_u64_t *src1, const big32_u64_t *src2);
extern void big32_u128_sub(big32_u128_t *dest, const big32_u128_t *src1, const big32_u128_t *src2);
extern void big32_u256_sub(big32_u256_t *dest, const big32_u256_t *src1, const big32_u256_t *src2);


extern void big32_u64_minuseq(big32_u64_t *dest, const big32_u64_t *src2);
extern void big32_u128_minuseq(big32_u128_t *dest, const big32_u128_t *src2);
extern void big32_u256_minuseq(big32_u256_t *dest, const big32_u256_t *src2);


extern void big32_u64_mul64(big32_u64_t *dest, const big32_u64_t *a, const big32_u64_t *b);
extern void big32_u128_mul128(big32_u128_t *dest, const big32_u128_t *a, const big32_u128_t *b);
extern void big32_u256_mul256(big32_u256_t *dest, const big32_u256_t *a, const big32_u256_t *b);


extern void big32_u64_mul128(big32_u128_t *dest, const big32_u64_t *a, const big32_u64_t *b);
extern void big32_u128_mul256(big32_u256_t *dest, const big32_u128_t *a, const big32_u128_t *b);
extern void big32_u256_mul512(big32_u512_t *dest, const big32_u256_t *a, const big32_u256_t *b);


extern void big32_promo_u64_from_uint(big32_u64_t *dest, const uint32_t src1);
extern void big32_promo_u128_from_uint(big32_u128_t *dest, const uint32_t src1);
extern void big32_promo_u256_from_uint(big32_u256_t *dest, const uint32_t src1);


extern void big32_promo_u128_from_u64(big32_u128_t *dest, const big32_u64_t *src1);
extern void big32_promo_u256_from_u128(big32_u256_t *dest, const big32_u128_t *src1);


extern uint32_t big32_trunc_uint_from_u64(const big32_u64_t *src1);
extern uint32_t big32_trunc_uint_from_u128(const big32_u128_t *src1);
extern uint32_t big32_trunc_uint_from_u256(const big32_u256_t *src1);


extern void big32_trunc_u64_from_u128(big32_u64_t *dest, const big32_u128_t *src1);
extern void big32_trunc_u128_from_u256(big32_u128_t *dest, const big32_u256_t *src1);


extern int big32_u64_is_equal(const big32_u64_t *src1, const big32_u64_t *src2);
extern int big32_u128_is_equal(const big32_u128_t *src1, const big32_u128_t *src2);
extern int big32_u256_is_equal(const big32_u256_t *src1, const big32_u256_t *src2);


extern int big32_u64_compare(const big32_u64_t *src1, const big32_u64_t *src2);
extern int big32_u128_compare(const big32_u128_t *src1, const big32_u128_t *src2);
extern int big32_u256_compare(const big32_u256_t *src1, const big32_u256_t *src2);


extern int big32_u64_is_zero(const big32_u64_t *src1);
extern int big32_u128_is_zero(const big32_u128_t *src1);
extern int big32_u256_is_zero(const big32_u256_t *src1);


extern int big32_u64_bitcheck(const big32_u64_t *src1, const uint32_t bit);
extern int big32_u128_bitcheck(const big32_u128_t *src1, const uint32_t bit);
extern int big32_u256_bitcheck(const big32_u256_t *src1, const uint32_t bit);


extern void big32_u64_shift_right(big32_u64_t *dest, const big32_u64_t *src1, uint32_t shift);
extern void big32_u64_shift_righteq(big32_u64_t *dest, uint32_t shift);

extern void big32_u128_shift_right(big32_u128_t *dest, const big32_u128_t *src1, uint32_t shift);
extern void big32_u128_shift_righteq(big32_u128_t *dest, uint32_t shift);

extern void big32_u256_shift_right(big32_u256_t *dest, const big32_u256_t *src1, uint32_t shift);
extern void big32_u256_shift_righteq(big32_u256_t *dest, uint32_t shift);


extern void big32_u64_shift_left(big32_u64_t *dest, const big32_u64_t *src1, uint32_t shift);
extern void big32_u64_shift_lefteq(big32_u64_t *dest, uint32_t shift);

extern void big32_u128_shift_left(big32_u128_t *dest, const big32_u128_t *src1, uint32_t shift);
extern void big32_u128_shift_lefteq(big32_u128_t *dest, uint32_t shift);

extern void big32_u256_shift_left(big32_u256_t *dest, const big32_u256_t *src1, uint32_t shift);
extern void big32_u256_shift_lefteq(big32_u256_t *dest, uint32_t shift);


extern int big32_u64_leading_zeros(const big32_u64_t *src);
extern int big32_u128_leading_zeros(const big32_u128_t *src);
extern int big32_u256_leading_zeros(const big32_u256_t *src);


extern int big32_u64_div(big32_u64_t *quot, big32_u64_t *rmdr, const big32_u64_t *divd, const big32_u64_t *divr);
extern int big32_u128_div(big32_u128_t *quot, big32_u128_t *rmdr, const big32_u128_t *divd, const big32_u128_t *divr);
extern int big32_u256_div(big32_u256_t *quot, big32_u256_t *rmdr, const big32_u256_t *divd, const big32_u256_t *divr);


extern void big32_f64_from_u64(big32_u64_t *dest, const big32_u64_t *src1);
extern void big32_f128_from_u128(big32_u128_t *dest, const big32_u128_t *src1);
extern void big32_f256_from_u256(big32_u256_t *dest, const big32_u256_t *src1);


extern void big32_f64_add(big32_u64_t *dest, const big32_u64_t *src1, const big32_u64_t *src2);
extern void big32_f128_add(big32_u128_t *dest, const big32_u128_t *src1, const big32_u128_t *src2);
extern void big32_f256_add(big32_u256_t *dest, const big32_u256_t *src1, const big32_u256_t *src2);


extern void big32_f64_pluseq(big32_u64_t *dest, const big32_u64_t *src2);
extern void big32_f128_pluseq(big32_u128_t *dest, const big32_u128_t *src2);
extern void big32_f256_pluseq(big32_u256_t *dest, const big32_u256_t *src2);


extern void big32_f64_sub(big32_u64_t *dest, const big32_u64_t *src1, const big32_u64_t *src2);
extern void big32_f128_sub(big32_u128_t *dest, const big32_u128_t *src1, const big32_u128_t *src2);
extern void big32_f256_sub(big32_u256_t *dest, const big32_u256_t *src1, const big32_u256_t *src2);


extern void big32_f64_minuseq(big32_u64_t *dest, const big32_u64_t *src1);
extern void big32_f128_minuseq(big32_u128_t *dest, const big32_u128_t *src1);
extern void big32_f256_minuseq(big32_u256_t *dest, const big32_u256_t *src1);


extern void big32_f64_double(big32_u64_t *dest);
extern void big32_f128_double(big32_u128_t *dest);
extern void big32_f256_double(big32_u256_t *dest);


extern void big32_f64_mul64(big32_u64_t *dest, const big32_u64_t *src1, const big32_u64_t *src2);
extern void big32_f128_mul128(big32_u128_t *dest, const big32_u128_t *src1, const big32_u128_t *src2);
extern void big32_f256_mul256(big32_u256_t *dest, const big32_u256_t *src1, const big32_u256_t *src2);


extern int big32_f64_inv(big32_u64_t *dest, const big32_u64_t *src1);
extern int big32_f128_inv(big32_u128_t *dest, const big32_u128_t *src1);
extern int big32_f256_inv(big32_u256_t *dest, const big32_u256_t *src1);


extern void big32_f256_pt_copy(big32_f256pt_t *dest, const big32_f256pt_t *src1);


extern int big32_f256_pt_double(big32_f256pt_t *dest, big32_f256pt_t *src1);


extern int big32_f256_pt_add(big32_f256pt_t *dest, big32_f256pt_t *src1, big32_f256pt_t *src2);

void big32_f256_seed_precomp_pt(const big32_f256pt_t *src1);

extern int big32_f256_scalar_pt_mul256(big32_f256pt_t *dest, const big32_u256_t *src1, const big32_f256pt_t *src2);


#ifdef __cplusplus
}
#endif

#endif	/* _big_32_h_included */
