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

int big32_u256_is_equal(const big32_u256_t *src1, const big32_u256_t *src2)
{
	return ((src1->r32.lsw == src2->r32.lsw) && (src1->r32.s2w == src2->r32.s2w) &&
		(src1->r32.s3w == src2->r32.s3w) && (src1->r32.s4w == src2->r32.s4w) && 
		(src1->r32.s5w == src2->r32.s5w) && (src1->r32.s6w == src2->r32.s6w) && 
		(src1->r32.s7w == src2->r32.s7w) && (src1->r32.msw == src2->r32.msw)) ;
}

int big32_u256_compare(const big32_u256_t *src1, const big32_u256_t *src2)
{
	if (src2->r32.msw > src1->r32.msw) { return -1; } ;
	if (src2->r32.msw < src1->r32.msw) { return  1; } ;
	if (src2->r32.s7w > src1->r32.s7w) { return -1; } ;
	if (src2->r32.s7w < src1->r32.s7w) { return  1; } ;
	if (src2->r32.s6w > src1->r32.s6w) { return -1; } ;
	if (src2->r32.s6w < src1->r32.s6w) { return  1; } ;
	if (src2->r32.s5w > src1->r32.s5w) { return -1; } ;
	if (src2->r32.s5w < src1->r32.s5w) { return  1; } ;
	if (src2->r32.s4w > src1->r32.s4w) { return -1; } ;
	if (src2->r32.s4w < src1->r32.s4w) { return  1; } ;
	if (src2->r32.s3w > src1->r32.s3w) { return -1; } ;
	if (src2->r32.s3w < src1->r32.s3w) { return  1; } ;
	if (src2->r32.s2w > src1->r32.s2w) { return -1; } ;
	if (src2->r32.s2w < src1->r32.s2w) { return  1; } ;
	if (src2->r32.lsw > src1->r32.lsw) { return -1; } ;
	if (src2->r32.lsw < src1->r32.lsw) { return  1; } ;
	return 0;
}

int big32_u256_is_zero(const big32_u256_t *src1)
{
	int i;
	for (i = 0 ; i < 8 ; i++) {
		if (src1->word[i] != 0) return 0 ; } ;
	return 1 ;
}

void big32_u256_set_zero(big32_u256_t *dest)
{
	int count;
	
	for(count = 0 ; count < 8 ; count++ ) {
		dest->word[count] = 0 ; } ;
}

#ifndef	_BIG32_INLINE_COPY
void big32_u256_copy(big32_u256_t *dest, const big32_u256_t *src1)
{
	int	count;
	
	for (count = 0; count < 4; count++) {
		dest->dword[count] = src1->dword[count] ; } ;
}
#endif

void big32_promo_u256_from_uint(big32_u256_t *dest, const uint32_t src1)
{
	dest->r32.lsw = src1 ;
	dest->r32.s2w = 0 ;
	dest->r32.s3w = 0 ;
	dest->r32.s4w = 0 ;
	dest->r32.s5w = 0 ;
	dest->r32.s6w = 0 ;
	dest->r32.s7w = 0 ;
	dest->r32.msw = 0 ;
}

uint32_t big32_trunc_uint_from_u256(const big32_u256_t *src1)
{
	return src1->r32.lsw ;
}

void big32_u256_add(big32_u256_t *dest, const big32_u256_t *src1, const big32_u256_t *src2)
{
	uint32_t	carry;
	int32_t		c;

	dest->word[0] = src1->word[0] + src2->word[0] ;
	carry = dest->word[0] < src1->word[0] ? 1 : 0 ;

	for (c = 1 ; c < 7 ; c++ ) {
		if (carry) { dest->word[c] = src1->word[c] + src2->word[c] + 1 ;
			carry = dest->word[c] <= src1->word[c] ? 1 : 0 ; }
		else { dest->word[c] = src1->word[c] + src2->word[c] ;
			carry = dest->word[c] < src1->word[c] ? 1 : 0 ;  } ; };

	dest->word[7] = ( src1->word[7] + src2->word[7] ) + carry ;
}

void big32_u256_pluseq(big32_u256_t *dest, const big32_u256_t *src2)
{
	big32_u256_t temp;
	big32_u256_copy(&temp, dest);
	big32_u256_add(dest, &temp, src2);
}

void big32_u256_sub(big32_u256_t *dest, const big32_u256_t *src1, const big32_u256_t *src2)
{
	uint32_t	borrow;
	int32_t		c;

	dest->word[0] = src1->word[0] - src2->word[0] ;
	borrow = src1->word[0] < src2->word[0] ? 1 : 0 ; 

	for (c = 1 ; c < 7 ; c++ ) {
		if (borrow) { borrow = src1->word[c] <= src2->word[c] ? 1 : 0 ;
			dest->word[c] = src1->word[c] - src2->word[c] ;
			dest->word[c] -- ; }
		else { borrow = src1->word[c] < src2->word[c] ? 1 : 0 ;
			dest->word[c] = src1->word[c] - src2->word[c] ;  } ; };

	dest->word[7] = ( src1->word[7] - src2->word[7] ) - borrow ;
}

void big32_u256_minuseq(big32_u256_t *dest, const big32_u256_t *src2)
{
	big32_u256_t temp;
	big32_u256_copy(&temp, dest);
	big32_u256_sub(dest, &temp, src2);
}

int big32_u256_bitcheck(const big32_u256_t *src1, const uint32_t bit)
{
	uint32_t word = ((bit >> 5) & 0x07) ;
	uint32_t wbit = (bit & 0x1F) ;
	
	if (bit > 255) { return 0 ; } ;
	
	if ((src1->word[word] & (1 << wbit)) == 0) {
		return 0 ; } ;
	
	return 1;
}

