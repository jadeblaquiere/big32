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

void big32_promo_u128_from_u64(big32_u128_t *dest, const big32_u64_t *src1)
{
	dest->r32.lsw = src1->r32.lsw ;
	dest->r32.s2w = src1->r32.msw ;
	dest->r32.s3w = 0 ;
	dest->r32.msw = 0 ;
}

void big32_promo_u256_from_u128(big32_u256_t *dest, const big32_u128_t *src1)
{
	dest->r32.lsw = src1->r32.lsw ;
	dest->r32.s2w = src1->r32.s2w ;
	dest->r32.s3w = src1->r32.s3w ;
	dest->r32.s4w = src1->r32.msw ;
	dest->r32.s5w = 0 ;
	dest->r32.s6w = 0 ;
	dest->r32.s7w = 0 ;
	dest->r32.msw = 0 ;
}

void big32_trunc_u64_from_u128(big32_u64_t *dest, const big32_u128_t *src1)
{
	dest->r32.lsw = src1->r32.lsw ;
	dest->r32.msw = src1->r32.s2w ;
}

void big32_trunc_u128_from_u256(big32_u128_t *dest, const big32_u256_t *src1)
{
	dest->r32.lsw = src1->r32.lsw ;
	dest->r32.s2w = src1->r32.s2w ;
	dest->r32.s3w = src1->r32.s3w ;
	dest->r32.msw = src1->r32.s4w ;
}

