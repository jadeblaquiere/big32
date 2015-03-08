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

#if 0
/* Extended Euclidean Algorithm (for unsigned numbers)
 * from : http://www.di-mgt.com.au/euclidean.html#code-modinv
 * see also : http://www.johannes-bauer.com/compsci/ecc/
 *
 * unsigned int modinv(unsigned int u, unsigned int v)
 * {
 *     unsigned int inv, u1, u3, v1, v3, t1, t3, q;
 *     int iter;
 *     // Step X1. Initialise 
 *     u1 = 1;
 *     u3 = u;
 *     v1 = 0;
 *     v3 = v;
 *     // Remember odd/even iterations 
 *     iter = 1;
 *     // Step X2. Loop while v3 != 0 
 *     while (v3 != 0)
 *     {
 *         // Step X3. Divide and "Subtract" 
 *         q = u3 / v3;
 *         t3 = u3 % v3;
 *         t1 = u1 + q * v1;
 *         // Swap 
 *         u1 = v1; v1 = t1; u3 = v3; v3 = t3;
 *         iter = -iter;
 *     }
 *     // Make sure u3 = gcd(u,v) == 1 
 *     if (u3 != 1)
 *         return 0;   // Error: No inverse exists 
 *     // Ensure a positive result 
 *     if (iter < 0)
 *         inv = v - u1;
 *     else
 *         inv = u1;
 *     return inv;
 * }
 */

int big32_f256_inv(big32_u256_t *dest, const big32_u256_t *src1)
{
	big32_u256_t	one256 = { .r32 = { 1, 0, 0, 0, 0, 0, 0, 0 } };
	big32_u256_t	u1 = { .r32 = { 1, 0, 0, 0, 0, 0, 0, 0 } };
	big32_u256_t	u3;
	big32_u256_t	v1 = { .r32 = { 0, 0, 0, 0, 0, 0, 0, 0 } };
	big32_u256_t	v3;
	big32_u256_t	t1;
	big32_u256_t	t3;
	big32_u256_t	q;
	big32_u256_t	tmp;
	int	iter;
	int	comp;
	
	big32_u256_copy(&u3, src1);
	big32_u256_copy(&v3, &field_p_u256);
	
	iter = 1;

	while (!big32_u256_is_zero(&v3)) {
	
		// q = u3 / v3; t3 = u3 % v3;
		big32_u256_div(&q, &t3, &u3, &v3);
		
		// t1 = u1 + q * v1;
		big32_u256_mul256(&tmp, &q, &v1);
		big32_u256_add(&t1, &u1, &tmp);
		
		// u1 = v1; v1 = t1; u3 = v3; v3 = t3;
		big32_u256_copy(&u1, &v1);
		big32_u256_copy(&v1, &t1);
		big32_u256_copy(&u3, &v3);
		big32_u256_copy(&v3, &t3);
		
		iter = -iter;

		} ;
	
	comp = big32_u256_compare(&u3, &one256);
	if (comp != 0) {  return -1 ; } ;
	if (iter < 0) {
		big32_u256_sub(dest, &field_p_u256, &u1); }
	else {
		big32_u256_copy(dest, &u1); }
		
#ifdef	_BIG32_VERIFY_BASIC_MATH
	{
		big32_u256_t	check;
		big32_f256_mul256(&check, src1, dest);
		if(big32_u256_compare(&check, &one256)) {
			printf("big32_f256_inv: inverse does not work!\n");
			big32_u256_print("a   :",src1); printf("\n");
			big32_u256_print("a^-1:",dest); printf("\n");
			big32_u256_print(" *= :",&check); printf("\n");
		}
	}
#endif
	return 0;
}

#else

/* Binary Euclidean Algrithm */

/* see : http://jes.eurasipjournals.com/content/pdf/1687-3963-2006-032192.pdf */

/* 
 * U <- m ; V <- a;
 * R <- 0 ; S <- 1;
 * while (V>0) {
 *   if (U is even) {
 *     U <- U/2;
 *     if (R is even) R <- R/2 ;
 *     else R <- (R+m)/2 ;
 *   } else if (V is even) {
 *     V <- V/2;
 *     if (S is even) S <- S/2 ;
 *     else S <- (S+m)/2 ;
 *   } else { //U,V both odd
 *     if (U > V) {
 *       U <- U - V; R <- R - S;
 *       if (R < 0) R <- R + m;
 *     } else {
 *       V <- V - U; S <- S - R;
 *       if (S < 0) S <- S + m;
 *     }
 *   }
 * }
 * if (U > 1) return 0;
 * if (R > m) R <- R - m;
 * if (R < 0) R <- r + m;
 * return R; // a^-1 mod m     
 */ 
	

int big32_f256_inv(big32_u256_t *dest, const big32_u256_t *src1)
{
	big32_u256_t	one256 = { .r32 = { 1, 0, 0, 0, 0, 0, 0, 0 } };
	big32_u256_t	u ;
	big32_u256_t	v ;
	big32_u256_t	r = { .r32 = { 0, 0, 0, 0, 0, 0, 0, 0 } } ;
	big32_u256_t	s = { .r32 = { 1, 0, 0, 0, 0, 0, 0, 0 } } ;
	big32_u256_t	field_h ;
	uint32_t	is_odd;
	
	big32_u256_copy(&u, &field_p_u256);
	big32_u256_copy(&v, src1);
	
	/* precalculate m+1/2 */
	big32_u256_copy(&field_h, &field_p_u256);
	big32_u256_pluseq(&field_h, &one256);
	big32_u256_shift_righteq(&field_h, 1);
	
	while (!big32_u256_is_zero(&v)) {

		if (!(u.word[0] & 0x01)) {
			big32_u256_shift_righteq(&u,1);
			is_odd = r.word[0] & 0x01 ;
			big32_u256_shift_righteq(&r,1);
			if (is_odd) { 
				big32_u256_pluseq(&r, &field_h);
			}
		} else if (!(v.word[0] & 0x01)) {
			big32_u256_shift_righteq(&v,1);
			is_odd = s.word[0] & 0x01 ;
			big32_u256_shift_righteq(&s,1);
			if (is_odd) { 
				big32_u256_pluseq(&s, &field_h);
			}
		} else {
			if (big32_u256_compare(&u,&v) > 0){
				big32_u256_minuseq(&u, &v) ;
				big32_f256_minuseq(&r, &s) ;
			} else {
				big32_u256_minuseq(&v, &u) ;
				big32_f256_minuseq(&s, &r) ;
			}
			
		}
	}

	if (big32_u256_compare(&u, &one256)>0 ) 
		big32_u256_set_zero(dest);
	else
		big32_f256_from_u256(dest, &r);
	
#ifdef	_BIG32_VERIFY_BASIC_MATH
	{
		big32_u256_t	check;
		big32_f256_mul256(&check, src1, dest);
		if(big32_u256_compare(&check, &one256)) {
			printf("big32_f256_inv: inverse does not work!\n");
			big32_u256_print("a   :",src1); printf("\n");
			big32_u256_print("a^-1:",dest); printf("\n");
			big32_u256_print(" *= :",&check); printf("\n");
		}
	}
#endif
	return 0 ;
}

#endif
