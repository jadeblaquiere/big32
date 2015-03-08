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

void big32_u128_shift_right(big32_u128_t *dest, const big32_u128_t *src1, uint32_t shift)
{
	int i=3;
	int j=3;
	
	while ((i >= 0) && (shift > 31))
	{
		dest->word[i] = 0;
		shift -= 32 ;
		i--;
	}
	
	if (shift == 0) {
		while (i >= 0) {
			dest->word[i] = src1->word[j];
			i--; j--; } ;
	} else {
		if (i >= 0) {
			dest->word[i] = src1->word[j] >> shift ;
			i--; j--; } ;
		while (i >= 0) {
			dest->word[i] = (src1->word[j] >> shift) + 
				(src1->word[j+1] << (32-shift)) ;
			i--; j--; } ; } ;
}

void big32_u128_shift_righteq(big32_u128_t *dest, uint32_t shift)
{
	big32_u128_t temp;
	big32_u128_shift_right(&temp,dest,shift);
	big32_u128_copy(dest, &temp);
}

void big32_u128_shift_left(big32_u128_t *dest, const big32_u128_t *src1, uint32_t shift)
{
	int i=0;
	int j=0;
	
	while ((i <= 3) && (shift > 31))
	{
		shift -= 32 ;
		dest->word[i] = 0 ;
		i++;
	}
	
	if (shift == 0) {
		while (i <= 3) {
			dest->word[i] = src1->word[j];
			i++; j++; } ;
	} else {
		if (i <= 3) {
			dest->word[i] = src1->word[j] << shift ;
			i++; j++; } ;
		while (i <= 3) {
			dest->word[i] = (src1->word[j] << shift) + 
				(src1->word[j-1] >> (32-shift)) ;
			i++; j++; } ; } ;
}

void big32_u128_shift_lefteq(big32_u128_t *dest, uint32_t shift)
{
	big32_u128_t temp;
	big32_u128_shift_left(&temp,dest,shift);
	big32_u128_copy(dest, &temp);
}

