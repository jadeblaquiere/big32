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

int big32_f64_inv(big32_u64_t *dest, const big32_u64_t *src1)
{
	big32_u64_t	one64 = { .r32 = { 1, 0} };
	big32_u64_t	u1 = { .r32 = { 1, 0 } };
	big32_u64_t	u3;
	big32_u64_t	v1 = { .r32 = { 0, 0 } };
	big32_u64_t	v3;
	big32_u64_t	t1;
	big32_u64_t	t3;
	big32_u64_t	q;
	big32_u64_t	tmp;
	int	iter;
	int	comp;
	
	big32_u64_copy(&u3, src1);
	big32_u64_copy(&v3, &field_p_u64);
	
	iter = 1;

	while (!big32_u64_is_zero(&v3)) {
	
		// q = u3 / v3; t3 = u3 % v3;
		big32_u64_div(&q, &t3, &u3, &v3);
		
		// t1 = u1 + q * v1;
		big32_u64_mul64(&tmp, &q, &v1);
		big32_u64_add(&t1, &u1, &tmp);
		
		// u1 = v1; v1 = t1; u3 = v3; v3 = t3;
		big32_u64_copy(&u1, &v1);
		big32_u64_copy(&v1, &t1);
		big32_u64_copy(&u3, &v3);
		big32_u64_copy(&v3, &t3);
		
		iter = -iter;

		} ;
	
	comp = big32_u64_compare(&u3, &one64);
	if (comp != 0) {  return -1 ; } ;
	if (iter < 0) {
		big32_u64_sub(dest, &field_p_u64, &u1); }
	else {
		big32_u64_copy(dest, &u1); }
		
	return 0;
}

