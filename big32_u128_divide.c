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

/* constants for table-based divide */

#define	NUM_BITS_PER_SIDE	(5)
#define	BITS_LUT_TYPE		(16)

#if	(BITS_LUT_TYPE == 16)	
typedef uint16_t	div_lut_t;
#endif

#define NUM_BITS	(2 * NUM_BITS_PER_SIDE)
#define	LUT_SIDE	(1 << NUM_BITS_PER_SIDE)
#define	LUT_SZ	(1 << NUM_BITS)

#define	SHIFT_DIVIDEND	((int)(BITS_LUT_TYPE-1) - NUM_BITS_PER_SIDE)

#if	(NUM_BITS_PER_SIDE == 5)
#if	(BITS_LUT_TYPE == 16)	
#define	div_lut(x)	(div_lut_5_16[x])
#endif
#endif

extern const uint16_t div_lut_5_16[1024];

int big32_u128_leading_zeros(const big32_u128_t *src)
{
	int i = 3;
	int j = 31;
	int zeros = 31;
	
	while ((i >= 0) && (src->word[i] == 0)) {
		i--;
		zeros += 32;
		} ;
	
	while ((j >= 0) && ((((uint32_t)1<<j) & src->word[i]) == 0)) {
		j--;
		} ;
		
	return ( zeros - j ) ;
}

int big32_u128_div(big32_u128_t *quot, big32_u128_t *rmdr, const big32_u128_t *divd, const big32_u128_t *divr)
{
	uint32_t	lut_divd;
	uint32_t	lut_divr;
	int32_t		lut_shift;
	
	int32_t		testval;

	int32_t	zeros_divd;
	int32_t	zeros_divr;
	int32_t	zeros_net;
	
	big32_u128_t	guess_quot;
	big32_u128_t	guess_product;
	big32_u128_t	difference;
	
	big32_u128_t	temp128;

	/* divide by zero, return error */
	if (big32_u128_is_zero(divr)) { return -1 ; } ;
	
	/* divide of zero, return 0,0 */
	if (big32_u128_is_zero(divd)) { big32_u128_set_zero(quot); 
		big32_u128_set_zero(rmdr); 
		return 0 ; } ;

	/* dividend less than divisor */
	testval = big32_u128_compare(divd, divr);
	if (testval < 0) {
		big32_u128_set_zero(quot);
		big32_u128_copy(rmdr, divd);
		return 0 ; } ;
	
	/* count leading zeros */
	zeros_divd = big32_u128_leading_zeros(divd);
	zeros_divr = big32_u128_leading_zeros(divr);
	zeros_net = zeros_divr - zeros_divd ;

	/* shift msb to position of 1 << NUM_BITS_PER_SIDE */
	lut_shift = (127-NUM_BITS_PER_SIDE) - zeros_divd;
	if (lut_shift >= 0) {
		big32_u128_shift_right(&temp128, divd, lut_shift) ; 
		lut_divd = temp128.word[0] ; } else {
		big32_u128_shift_left(&temp128, divd, -lut_shift) ; 
		lut_divd = temp128.word[0] ; } ;
		
	lut_shift = (127-NUM_BITS_PER_SIDE) - zeros_divr;

	if (lut_shift >= 0) {
		big32_u128_shift_right(&temp128, divr, lut_shift) ; 
		lut_divr = temp128.word[0] ; 
	} else {
		big32_u128_shift_left(&temp128, divr, -lut_shift) ; 
		lut_divr = temp128.word[0] ; } ;
	
	/* mask lsb*/
	lut_divd &= ((1 << NUM_BITS_PER_SIDE) - 1);
	lut_divr &= ((1 << NUM_BITS_PER_SIDE) - 1);
	lut_shift = zeros_net - SHIFT_DIVIDEND ;

	/* create large integer from shorter lookup value */
	big32_promo_u128_from_uint(&temp128,div_lut((LUT_SIDE * lut_divd) +
		lut_divr));

	if (lut_shift >= 0) {
		big32_u128_shift_left(&guess_quot,&temp128,lut_shift);
	} else {
		big32_u128_shift_right(&guess_quot,&temp128,-lut_shift); } ;

	big32_u128_mul128(&guess_product, &guess_quot, divr) ;

	testval = big32_u128_compare(&guess_product, divd);
	
	if ((testval > 0) || ((zeros_divd == 0) && 
		((guess_product.r32.msw & 0xF0000000) == 0))) {
		
		/* first clause is for where we overshot the target */
			
		big32_u128_t one128 = { .r32 = { 0x00000001UL , 0x00000000UL ,
			0x00000000UL , 0x00000000UL } } ;
			
		big32_u128_sub(&difference,&guess_product,divd);
		testval = big32_u128_compare(&difference,divr);
		
		if (testval < 0) {
		
			/* overshot but remainder less than divider */
			
			big32_u128_sub(quot, &guess_quot, &one128);
			big32_u128_sub(rmdr, divr, &difference);
		
			return 1 ; 

		} else {
		
			/* overshot and need to iterate */
			
			big32_u128_t	next_quot;
			big32_u128_t	next_rmdr;
			int recurse;
			
			recurse = big32_u128_div(&next_quot, &next_rmdr, 
				&difference, divr);
			
			if (big32_u128_is_zero(&next_rmdr)) {
				big32_u128_sub(quot, &guess_quot, &next_quot);
				big32_u128_copy(rmdr, &next_rmdr);
			} else {
				big32_u128_add(&temp128, &next_quot, &one128);
				big32_u128_sub(quot, &guess_quot, &temp128);
				big32_u128_sub(rmdr, divr, &next_rmdr); } ;
				
			return recurse + 1 ;
			
			} ;
			
	} else {
		
		/* this clause is for the undershot case */
		
		big32_u128_sub(&difference,divd,&guess_product);
		testval = big32_u128_compare(&difference,divr);
		
		if (testval < 0) {
		
			/* undershot but difference less than divisor */
			
			big32_u128_copy(quot, &guess_quot);
			big32_u128_copy(rmdr, &difference);
			
			return 1 ; 

		} else {

			/* undershot and need to iterate */
			
			big32_u128_t	next_quot;
			big32_u128_t	next_rmdr;
			int recurse;
			
			recurse = big32_u128_div(&next_quot, &next_rmdr, 
				&difference, divr);
			
			big32_u128_add(quot, &guess_quot, &next_quot);
			big32_u128_copy(rmdr, &next_rmdr);
			
			return recurse + 1 ; } ;
		}

	return 0;
}

