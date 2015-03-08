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

/* largest 64 bit unsigned prime is 2^64 - 59, 59 = 2^ (0,1,3,4,5) */
big32_u64_t field_p_u64 = { .r32 = { 0xFFFFFFC5UL , 0xFFFFFFFFUL } } ;

void big32_f64_from_u64(big32_u64_t *dest, const big32_u64_t *src1)
{
	dest->r32.lsw = src1->r32.lsw ;
	dest->r32.msw = src1->r32.msw ;
	if (big32_u64_compare(dest,&field_p_u64) > 0) { 
		big32_u64_minuseq(dest,&field_p_u64); } ;
}

void big32_f64_add(big32_u64_t *dest, const big32_u64_t *src1, const big32_u64_t *src2)
{
	uint32_t	carry;

	dest->r32.lsw = src1->r32.lsw + src2->r32.lsw ;
	carry = 0 ; 
	if (dest->r32.lsw < src1->r32.lsw) { carry = 1; } ;

	dest->r32.msw = src1->r32.msw + src2->r32.msw + carry;
	if ((dest->r32.msw < (src1->r32.msw + carry)) || 
	    ((dest->r32.msw - carry) < src1->r32.msw)) { 
		big32_u64_minuseq(dest,&field_p_u64) ; }
	else if (big32_u64_compare(dest,&field_p_u64) > 0) { 
		big32_u64_minuseq(dest,&field_p_u64); } ;
}

void big32_f64_pluseq(big32_u64_t *dest, const big32_u64_t *src2)
{
#if 0
	big32_u64_t temp;
	big32_u64_copy(&temp,dest);
	big32_f64_add(dest, &temp, src2); 
#else
	uint32_t	carry;
	uint32_t	save;

	save = dest->r32.lsw ;
	dest->r32.lsw = save + src2->r32.lsw ;
	carry = 0 ; 
	if (dest->r32.lsw < save) { carry = 1; } ;

	save = dest->r32.msw ;
	dest->r32.msw = save + src2->r32.msw + carry;
	if ((dest->r32.msw < (save + carry)) || 
	    ((dest->r32.msw - carry) < save)) { 
		big32_u64_minuseq(dest,&field_p_u64) ; }
	else if (big32_u64_compare(dest,&field_p_u64) > 0) { 
		big32_u64_minuseq(dest,&field_p_u64); } ;
#endif
}

void big32_f64_sub(big32_u64_t *dest, const big32_u64_t *src1, const big32_u64_t *src2)
{
	int comp = big32_u64_compare(src2, src1) ;
	
	big32_u64_sub(dest, src1, src2);
	if (comp > 0) { big32_u64_pluseq(dest,&field_p_u64); } ;
}

void big32_f64_minuseq(big32_u64_t *dest, const big32_u64_t *src1)
{
	int comp = big32_u64_compare(src1, dest) ;
	
	big32_u64_minuseq(dest, src1);
	if (comp > 0) { big32_u64_pluseq(dest,&field_p_u64); } ;
}

