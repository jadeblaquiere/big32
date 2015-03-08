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

/* largest 128 bit unsigned prime is 2^128 - 159, 159 = 2^ (0,1,2,3,4,7) */
big32_u128_t field_p_u128 = { .r32 = { 0xFFFFFF61UL, 0xFFFFFFFFUL ,
					 0xFFFFFFFFUL, 0xFFFFFFFFUL } } ;

void big32_f128_from_u128(big32_u128_t *dest, const big32_u128_t *src1)
{
	dest->r32.lsw = src1->r32.lsw ;
	dest->r32.s2w = src1->r32.s2w ;
	dest->r32.s3w = src1->r32.s3w ;
	dest->r32.msw = src1->r32.msw ;
	if (big32_u128_compare(dest,&field_p_u128) > 0) { 
		big32_u128_minuseq(dest,&field_p_u128); } ;
}

void big32_f128_add(big32_u128_t *dest, const big32_u128_t *src1, const big32_u128_t *src2)
{
	uint32_t	carry;
	int32_t		c;

	dest->word[0] = src1->word[0] + src2->word[0] ;
	carry = dest->word[0] < src1->word[0] ? 1 : 0 ;

	for (c = 1 ; c < 4 ; c++ ) {
		if (carry) { dest->word[c] = src1->word[c] + src2->word[c] + 1 ;
			carry = dest->word[c] <= src1->word[c] ? 1 : 0 ; }
		else { dest->word[c] = src1->word[c] + src2->word[c] ;
			carry = dest->word[c] < src1->word[c] ? 1 : 0 ;  } ; };

	if (carry) { big32_u128_minuseq(dest,&field_p_u128) ; }
	else if (big32_u128_compare(dest,&field_p_u128) > 0) { 
		big32_u128_minuseq(dest,&field_p_u128); } ;
	
#ifdef	_BIG32_VERIFY_BASIC_MATH
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	if ( (carry) || ( ( *((__uint128_t *)src1) + *((__uint128_t *)src2)) >
		  *((__uint128_t*)&field_p_u128)) ) {
		if ( *((__uint128_t *)dest) != ( *((__uint128_t *)src1) +
		     *((__uint128_t *)src2)) - *((__uint128_t*)&field_p_u128))
		     { printf("U128 Add error!\n");
			big32_u128_print("src1",src1);
			big32_u128_print("dest",src2);
			big32_u128_print("dest",dest); 
			exit(-1) ; } }
	else if ( *((__uint128_t *)dest) != ( *((__uint128_t *)src1) +
		  *((__uint128_t *)src2)) )
		    { printf("U128 Add error!\n");
			big32_u128_print("src1",src1);
			big32_u128_print("dest",src2);
			big32_u128_print("dest",dest); 
			exit(-1) ; } ;
#endif
#endif
} 

void big32_f128_pluseq(big32_u128_t *dest, const big32_u128_t *src2)
{
#if 0
	big32_u128_t temp;
	big32_u128_copy(&temp,dest);
	big32_f128_add(dest, &temp, src2); 
#else
	uint32_t	carry;
	uint32_t	save;
	int32_t		c;

	save = dest->word[0];
	dest->word[0] = save + src2->word[0] ;
	carry = dest->word[0] < save ? 1 : 0 ;

	for (c = 1 ; c < 4 ; c++ ) {
		if (carry) { save = dest->word[c] ;
			dest->word[c] = save + src2->word[c] + 1 ;
			carry = dest->word[c] <= save ? 1 : 0 ; }
		else { save = dest->word[c] ;
			dest->word[c] = save + src2->word[c] ;
			carry = dest->word[c] < save ? 1 : 0 ;  } ; };

	if (carry) { big32_u128_minuseq(dest,&field_p_u128) ; }
	else if (big32_u128_compare(dest,&field_p_u128) > 0) { 
		big32_u128_minuseq(dest,&field_p_u128); } ;
#endif
}

void big32_f128_sub(big32_u128_t *dest, const big32_u128_t *src1, const big32_u128_t *src2)
{
	int comp = big32_u128_compare(src2, src1) ;
	
	big32_u128_sub(dest, src1, src2);
	if (comp > 0) { big32_u128_pluseq(dest,&field_p_u128); } ;
}

void big32_f128_minuseq(big32_u128_t *dest, const big32_u128_t *src1)
{
	int comp = big32_u128_compare(src1, dest) ;
	
	big32_u128_minuseq(dest, src1);
	if (comp > 0) { big32_u128_pluseq(dest,&field_p_u128); } ;
}

