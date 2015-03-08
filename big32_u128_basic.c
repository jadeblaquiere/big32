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

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "big32.h"

int big32_u128_is_equal(const big32_u128_t *src1, const big32_u128_t *src2)
{
	return ((src1->r32.lsw == src2->r32.lsw) && (src1->r32.s2w == src2->r32.s2w) && (src1->r32.s3w == src2->r32.s3w) && (src1->r32.msw == src2->r32.msw)) ;
}

int big32_u128_compare(const big32_u128_t *src1, const big32_u128_t *src2)
{
	if (src2->r32.msw > src1->r32.msw) { return -1; } ;
	if (src2->r32.msw < src1->r32.msw) { return  1; } ;
	if (src2->r32.s3w > src1->r32.s3w) { return -1; } ;
	if (src2->r32.s3w < src1->r32.s3w) { return  1; } ;
	if (src2->r32.s2w > src1->r32.s2w) { return -1; } ;
	if (src2->r32.s2w < src1->r32.s2w) { return  1; } ;
	if (src2->r32.lsw > src1->r32.lsw) { return -1; } ;
	if (src2->r32.lsw < src1->r32.lsw) { return  1; } ;
	return 0;
}

int big32_u128_is_zero(const big32_u128_t *src1)
{
	int i;
	for (i = 0 ; i < 4 ; i++) {
		if (src1->word[i] != 0) return 0 ; } ;
	return 1 ;
}

void big32_u128_set_zero(big32_u128_t *dest)
{
	dest->word[0] = 0 ;
	dest->word[1] = 0 ;
	dest->word[2] = 0 ;
	dest->word[3] = 0 ;
}

#ifndef	_BIG32_INLINE_COPY
void big32_u128_copy(big32_u128_t *dest, const big32_u128_t *src1)
{
	dest->r64.lsd = src1->r64.lsd ;
	dest->r64.msd = src1->r64.msd ;
}
#endif

void big32_promo_u128_from_uint(big32_u128_t *dest, const uint32_t src1)
{
	dest->r32.lsw = src1 ;
	dest->r32.s2w = 0 ;
	dest->r32.s3w = 0 ;
	dest->r32.msw = 0 ;
}

uint32_t big32_trunc_uint_from_u128(const big32_u128_t *src1)
{
	return src1->r32.lsw ;
}

void big32_u128_add(big32_u128_t *dest, const big32_u128_t *src1, const big32_u128_t *src2)
{
	uint32_t	carry;
	int32_t		c;

	dest->word[0] = src1->word[0] + src2->word[0] ;
	carry = dest->word[0] < src1->word[0] ? 1 : 0 ;

	for (c = 1 ; c < 3 ; c++ ) {
		if (carry) { dest->word[c] = src1->word[c] + src2->word[c] + 1 ;
			carry = dest->word[c] <= src1->word[c] ? 1 : 0 ; }
		else { dest->word[c] = src1->word[c] + src2->word[c] ;
			carry = dest->word[c] < src1->word[c] ? 1 : 0 ;  } ; };

	dest->word[3] = ( src1->word[3] + src2->word[3] ) + carry ;
	
#ifdef	_BIG32_VERIFY_BASIC_MATH
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	if (*((__uint128_t *)dest) != ( *((__uint128_t *)src1) + *((__uint128_t *)src2))) { printf("U128 Add error!\n");
		big32_u128_print("src1",src1);
		big32_u128_print("dest",src2);
		big32_u128_print("dest",dest); 
		exit(-1) ; } ;
#endif
#endif
}

void big32_u128_pluseq(big32_u128_t *dest, const big32_u128_t *src2)
{
	big32_u128_t temp;
	big32_u128_copy(&temp, dest);
	big32_u128_add(dest, &temp, src2);
}

void big32_u128_sub(big32_u128_t *dest, const big32_u128_t *src1, const big32_u128_t *src2)
{
	uint32_t	borrow;
	int32_t		c;

	dest->word[0] = src1->word[0] - src2->word[0] ;
	borrow = src1->word[0] < src2->word[0] ? 1 : 0 ; 

	for (c = 1 ; c < 3 ; c++ ) {
		if (borrow) { borrow = src1->word[c] <= src2->word[c] ? 1 : 0 ;
			dest->word[c] = src1->word[c] - src2->word[c] ;
			dest->word[c] -- ; }
		else { borrow = src1->word[c] < src2->word[c] ? 1 : 0 ;
			dest->word[c] = src1->word[c] - src2->word[c] ;  } ; };

	dest->word[3] = ( src1->word[3] - src2->word[3] ) - borrow ;
	
#ifdef	_BIG32_VERIFY_BASIC_MATH
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	if (*((__uint128_t *)dest) != ( *((__uint128_t *)src1) - *((__uint128_t *)src2))) { printf("U128 Subtract error!\n");
		big32_u128_print("src1",src1);
		big32_u128_print("dest",src2);
		big32_u128_print("dest",dest); 
		exit(-1) ; } ;
#endif
#endif
}

void big32_u128_minuseq(big32_u128_t *dest, const big32_u128_t *src2)
{
	big32_u128_t temp;
	big32_u128_copy(&temp, dest);
	big32_u128_sub(dest, &temp, src2);
}

int big32_u128_bitcheck(const big32_u128_t *src1, const uint32_t bit)
{
	uint32_t word = ((bit >> 5) & 0x03) ;
	uint32_t wbit = (bit & 0x1F) ;
	
	if (bit > 127) { return 0 ; } ;
	
	if ((src1->word[word] & (1 << wbit)) == 0) {
		return 0 ; } ;
	
	return 1;
}

