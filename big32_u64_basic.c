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

int big32_u64_is_equal(const big32_u64_t *src1, const big32_u64_t *src2)
{
	return ((src1->r32.lsw == src2->r32.lsw) && (src1->r32.msw == src2->r32.msw)) ;
}

int big32_u64_compare(const big32_u64_t *src1, const big32_u64_t *src2)
{
	if (src2->r32.msw > src1->r32.msw) { return -1; } ;
	if (src2->r32.msw < src1->r32.msw) { return  1; } ;
	if (src2->r32.lsw > src1->r32.lsw) { return -1; } ;
	if (src2->r32.lsw < src1->r32.lsw) { return  1; } ;
	return 0;
}

int big32_u64_is_zero(const big32_u64_t *src1)
{
	int i;
	for (i = 0 ; i < 2 ; i++) {
		if (src1->word[i] != 0) return 0 ; } ;
	return 1 ;
}

void big32_u64_set_zero(big32_u64_t *dest)
{
	dest->word[0] = 0 ;
	dest->word[1] = 0 ;
}

#ifndef	_BIG32_INLINE_COPY
void big32_u64_copy(big32_u64_t *dest, const big32_u64_t *src1)
{
	dest->r64.lsd = src1->r64.lsd ;
}
#endif

void big32_promo_u64_from_uint(big32_u64_t *dest, const uint32_t src1)
{
	dest->r32.lsw = src1 ;
	dest->r32.msw = 0 ;
}

uint32_t big32_trunc_uint_from_u64(const big32_u64_t *src1)
{
	return src1->r32.lsw ;
}

void big32_u64_add(big32_u64_t *dest, const big32_u64_t *src1, const big32_u64_t *src2)
{
	uint32_t	carry = 0;

	dest->r32.lsw = src1->r32.lsw + src2->r32.lsw ;
	if (dest->r32.lsw < src1->r32.lsw) { carry = 1; } ;
	dest->r32.msw = src1->r32.msw + src2->r32.msw + carry;

#ifdef	_BIG32_VERIFY_BASIC_MATH
	if (*((uint64_t *)dest) != ( *((uint64_t *)src1) + *((uint64_t *)src2))) { printf("U64 Add error!\n");
		big32_u64_print("src1",src1);
		big32_u64_print("dest",src2);
		big32_u64_print("dest",dest); 
		exit(-1) ; } ;
#endif
}

void big32_u64_pluseq(big32_u64_t *dest, const big32_u64_t *src2)
{
	big32_u64_t	temp;
	big32_u64_copy(&temp, dest);
	big32_u64_add(dest, &temp, src2);
}

void big32_u64_sub(big32_u64_t *dest, const big32_u64_t *src1, const big32_u64_t *src2)
{
	uint32_t	borrow = 0;

	dest->r32.lsw = src1->r32.lsw - src2->r32.lsw ;
	if (dest->r32.lsw > src1->r32.lsw) { borrow = 1; } ;
	dest->r32.msw = src1->r32.msw - ( src2->r32.msw + borrow ) ;

#ifdef	_BIG32_VERIFY_BASIC_MATH
	if (*((uint64_t *)dest) != ( *((uint64_t *)src1) - *((uint64_t *)src2))) { printf("U64 Subtract error!\n");
		big32_u64_print("src1",src1);
		big32_u64_print("dest",src2);
		big32_u64_print("dest",dest); 
		exit(-1) ; } ;
#endif
}

void big32_u64_minuseq(big32_u64_t *dest, const big32_u64_t *src2)
{
	big32_u64_t	temp;
	big32_u64_copy(&temp, dest);
	big32_u64_sub(dest, &temp, src2);
}

int big32_u64_bitcheck(const big32_u64_t *src1, const uint32_t bit)
{
	uint32_t word = ((bit >> 5) & 0x01) ;
	uint32_t wbit = (bit & 0x1F) ;
	
	if (bit > 63) { return 0 ; } ;
	
	if ((src1->word[word] & (1 << wbit)) == 0) {
		return 0 ; } ;
	
	return 1;
}

