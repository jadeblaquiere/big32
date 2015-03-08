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

void big32_u64_mul64(big32_u64_t *dest, const big32_u64_t *a, const big32_u64_t *b)
{
	int i,j,k;
	uint32_t	result;
	uint32_t	save;
	uint32_t	carry;
	
	int	start;
	int	stop;
	
	dest->word[0] = a->hword[0] * b->hword[0] ;
	carry = 0 ;
	
	for (i = 1 ; i < 2 ; i++)
	{
		dest->word[i] = carry ;
		carry = 0;
		
		/* traverse set defined by j+k = 2i -1 */
		stop = ( i << 1 ) - 1 ;
		start = stop - 3 ;
		start = start < 0 ? 0 : start ; 
		stop = stop > 3 ? 3 : stop ;
		for (j = start ; j <= stop ; j++)
		{
			k = ( ( i << 1 ) - 1 ) - j ;
			
			result = a->hword[j] * b->hword[k] ;
			
			save = dest->word[i-1] ;
			dest->word[i-1] += result << 16 ;
			if (save > dest->word[i-1]) dest->word[i]++ ;
			
			dest->word[i] += result >> 16 ;
		}
		
		/* traverse set defined by j+k = 2i */
		stop = i << 1  ;
		start = stop - 3 ;
		start = start < 0 ? 0 : start ; 
		stop = stop > 3 ? 3 : stop ;
		for (j = start ; j <= stop ; j++)
		{
			k = ( i << 1 ) - j ;
			
			result = a->hword[j] * b->hword[k] ;
			
			save = dest->word[i] ;
			dest->word[i] += result ;
			if (save > dest->word[i]) carry++ ;
		}
	}		

	/* traverse set defined by j+k = 2i -1 */
	for (j = 0 ; j <= 3 ; j++)
	{
		k = 3 - j ;
		
		result = a->hword[j] * b->hword[k] ;
		
		dest->word[1] += result << 16 ;
	}

#ifdef	_VERIFY_BASIC_MATH
	if (*((uint64_t *)dest) != ( *((uint64_t *)a) * *((uint64_t *)b))) { printf("U64 Mulitply error!\n");
		big32_u64_print("src1",a);
		big32_u64_print("dest",b);
		big32_u64_print("dest",dest); 
		exit(-1) ; } ;
#endif
}

