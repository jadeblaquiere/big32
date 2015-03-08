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

/* using secp256k1 field: 2^256 - 2^ (0,4,6,7,8,9,32) */
big32_u256_t field_p_u256 = { .r32 = { 0xFFFFFC2FUL, 0xFFFFFFFEUL , 
					 0xFFFFFFFFUL , 0xFFFFFFFFUL ,
					 0xFFFFFFFFUL , 0xFFFFFFFFUL ,
					 0xFFFFFFFFUL , 0xFFFFFFFFUL } } ;

void big32_f256_from_u256(big32_u256_t *dest, const big32_u256_t *src1)
{
	int count;

	for (count = 0 ; count < 8 ; count++ ) {
		dest->word[count] = src1->word[count]; } ;

	if (big32_u256_compare(dest,&field_p_u256) > 0) { 
		big32_u256_minuseq(dest,&field_p_u256); } ;
}

void big32_f256_add(big32_u256_t *dest, const big32_u256_t *src1, const big32_u256_t *src2)
{
	uint32_t	carry;
	int32_t		c;

	dest->word[0] = src1->word[0] + src2->word[0] ;
	carry = dest->word[0] < src1->word[0] ? 1 : 0 ;

	for (c = 1 ; c < 8 ; c++ ) {
		if (carry) { dest->word[c] = src1->word[c] + src2->word[c] + 1 ;
			carry = dest->word[c] <= src1->word[c] ? 1 : 0 ; }
		else { dest->word[c] = src1->word[c] + src2->word[c] ;
			carry = dest->word[c] < src1->word[c] ? 1 : 0 ;  } ; };

	if (carry) { big32_u256_minuseq(dest,&field_p_u256) ; }
	else if (big32_u256_compare(dest,&field_p_u256) > 0) { 
		big32_u256_minuseq(dest,&field_p_u256); } ;
}

void big32_f256_pluseq(big32_u256_t *dest, const big32_u256_t *src2)
{
#if 0
	big32_u256_t temp;
	big32_u256_copy(&temp,dest);
	big32_f256_add(dest, &temp, src2); 
#else
	uint32_t	carry;
	uint32_t	save;
	int32_t		c;

	save = dest->word[0];
	dest->word[0] = save + src2->word[0] ;
	carry = dest->word[0] < save ? 1 : 0 ;

	for (c = 1 ; c < 8 ; c++ ) {
		if (carry) { save = dest->word[c] ;
			dest->word[c] = save + src2->word[c] + 1 ;
			carry = dest->word[c] <= save ? 1 : 0 ; }
		else { save = dest->word[c] ;
			dest->word[c] = save + src2->word[c] ;
			carry = dest->word[c] < save ? 1 : 0 ;  } ; };

	if (carry) { big32_u256_minuseq(dest,&field_p_u256) ; }
	else if (big32_u256_compare(dest,&field_p_u256) > 0) { 
		big32_u256_minuseq(dest,&field_p_u256); } ;
#endif
}

void big32_f256_sub(big32_u256_t *dest, const big32_u256_t *src1, const big32_u256_t *src2)
{
	int comp = big32_u256_compare(src2, src1) ;
	
	big32_u256_sub(dest, src1, src2);
	if (comp > 0) { big32_u256_pluseq(dest,&field_p_u256); } ;
}

void big32_f256_minuseq(big32_u256_t *dest, const big32_u256_t *src1)
{
	int comp = big32_u256_compare(src1, dest) ;
	
	big32_u256_minuseq(dest, src1);
	if (comp > 0) { big32_u256_pluseq(dest,&field_p_u256); } ;
}

