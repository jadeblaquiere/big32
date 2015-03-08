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

#include <big32.h>

static big32_f256pt_t secp256k1_G = 
	{ { .r32 = { 0x16F81798, 0x59F2815B, 0x2DCE28D9, 0x029BFCDB, 
		     0xCE870B07, 0x55A06295, 0xF9DCBBAC, 0x79BE667E }}, 
	  { .r32 = { 0xFB10D4B8, 0x9C47D08F, 0xA6855419, 0xFD17B448,
		     0x0E1108A8, 0x5DA4FBFC, 0x26A3C465, 0x483ADA77 }}};

/* 18E14A7B 6A307F42 6A94F811 4701E7C8 E774E7F9 A47E2C20 35DB29A2 06321725 */
static big32_u256_t private_key_test = { .r32 = 
	{ 0x06321725, 0x35DB29A2, 0xA47E2C20, 0xE774E7F9, 
	  0x4701E7C8, 0x6A94F811, 0x6A307F42, 0x18E14A7B }} ;   


int main(int argc, char **argv)
{
	uint64_t	a;
	uint64_t	b;
	uint64_t	b2;
	uint64_t	c;
	uint64_t	d;
	uint64_t	e;
	uint64_t	f;
	uint64_t	g;

	uint64_t	u64_f = 0xFFFFFFFFFFFFFFC5ULL;

	uint64_t	a_f;
	uint64_t	b_f;
	uint64_t	c_f;
	uint64_t	d_f;
	uint64_t	e_f;
	uint64_t	f_f;
	uint64_t	g_f;

#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	__uint128_t	aa_a_f;
	__uint128_t	bb_b_f;
	__uint128_t	ee_e_f;
	__uint128_t	ff_f_f;
	__uint128_t	gg_g_f;
	__uint128_t	hh_h_f;

	__uint128_t	aa;
	__uint128_t	bb;
	__uint128_t	bb2;
	__uint128_t	cc;
	__uint128_t	dd;
	__uint128_t	ee;
	__uint128_t	ff;
	__uint128_t	gg;

	__uint128_t	aa_a;
	__uint128_t	bb_b;
	__uint128_t	cc_c;
	__uint128_t	dd_d;
	__uint128_t	ee_e;

	__uint128_t	sz128;
#else
	big32_u128_t	aa;
	big32_u128_t	bb;
	big32_u128_t	bb2;
	big32_u128_t	aa_a_f;
	big32_u128_t	bb_b_f;
	big32_u128_t	ee_e_f;
#endif

	uint64_t	sz64;

	big32_u64_t		_my_c;
	big32_u64_t		_my_d;
	big32_u64_t		_my_e;
	big32_u64_t		_my_f;
	big32_u64_t		_my_g;
	big32_u64_t		_my_c_tc;
	big32_u64_t		_my_d_tc;
	big32_u64_t		_my_e_tc;

	big32_u64_t		_my_a_f;
	big32_u64_t		_my_b_f;
	big32_u64_t		_my_c_f;
	big32_u64_t		_my_d_f;
	big32_u64_t		_my_e_f;

	big32_u64_t		*my_a;
	big32_u64_t		*my_b;
	big32_u64_t		*my_b2;
	big32_u64_t		*my_c;
	big32_u64_t		*my_d;
	big32_u64_t		*my_e;
	big32_u64_t		*my_f;
	big32_u64_t		*my_g;

	big32_u64_t		*my_c_t;
	big32_u64_t		*my_d_t;
	big32_u64_t		*my_e_t;
	big32_u64_t		*my_f_t;
	big32_u64_t		*my_g_t;

	big32_u64_t		*my_c_tc;
	big32_u64_t		*my_d_tc;
	big32_u64_t		*my_e_tc;

	big32_u64_t		*my_a_f;
	big32_u64_t		*my_b_f;
	big32_u64_t		*my_c_f;
	big32_u64_t		*my_d_f;
	big32_u64_t		*my_e_f;
	big32_u64_t		*my_f_f;
	big32_u64_t		*my_g_f;

	big32_u64_t		*my_a_ft;
	big32_u64_t		*my_b_ft;
	big32_u64_t		*my_c_ft;
	big32_u64_t		*my_d_ft;
	big32_u64_t		*my_e_ft;
	big32_u64_t		*my_f_ft;

	big32_u64_t		_my_a_aa_a;
	big32_u64_t		_my_b_bb_b;
	big32_u64_t		_my_c_cc_c;
	big32_u64_t		_my_d_dd_d;
	big32_u64_t		_my_e_ee_e;

	big32_u64_t		*my_a_aa_a;
	big32_u64_t		*my_b_bb_b;
	big32_u64_t		*my_c_cc_c;
	big32_u64_t		*my_d_dd_d;
	big32_u64_t		*my_e_ee_e;
	big32_u128_t	*my_ee_e_t;

	big32_u128_t	_my_cc;
	big32_u128_t	_my_dd;
	big32_u128_t	_my_ee;
	big32_u128_t	_my_ff;
	big32_u128_t	_my_gg;

	big32_u128_t	_my_cc_tc;
	big32_u128_t	_my_dd_tc;
	big32_u128_t	_my_ee_tc;

	big32_u128_t	*my_aa;
	big32_u128_t	*my_bb;
	big32_u128_t	*my_bb2;
	big32_u128_t	*my_cc;
	big32_u128_t	*my_dd;
	big32_u128_t	*my_ee;
	big32_u128_t	*my_ff;
	big32_u128_t	*my_gg;

	big32_u128_t	_my_aa_f;
	big32_u128_t	_my_bb_f;
	big32_u128_t	_my_cc_f;
	big32_u128_t	_my_dd_f;
	big32_u128_t	_my_ee_f;
	big32_u128_t	_my_ff_f;
	big32_u128_t	_my_gg_f;
	big32_u128_t	_my_hh_f;
	big32_u128_t	_my_ii_f;

	big32_u128_t	*my_aa_f;
	big32_u128_t	*my_bb_f;
	big32_u128_t	*my_cc_f;
	big32_u128_t	*my_dd_f;
	big32_u128_t	*my_ee_f;
	big32_u128_t	*my_ff_f;
	big32_u128_t	*my_gg_f;
	big32_u128_t	*my_hh_f;
	big32_u128_t	*my_ii_f;

#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	big32_u128_t	*my_cc_t;
	big32_u128_t	*my_dd_t;
	big32_u128_t	*my_ee_t;
	big32_u128_t	*my_ff_t;
	big32_u128_t	*my_gg_t;
#endif

	big32_u128_t	*my_cc_tc;
	big32_u128_t	*my_dd_tc;
	big32_u128_t	*my_ee_tc;

	big32_u128_t	*my_aa_a;
	big32_u128_t	*my_bb_b;
	big32_u128_t	*my_cc_c;
	big32_u128_t	*my_dd_d;
	big32_u128_t	*my_ee_e;

	big32_u128_t	_my_aa_a;
	big32_u128_t	_my_bb_b;
	big32_u128_t	_my_cc_c;
	big32_u128_t	_my_dd_d;
	big32_u128_t	_my_ee_e;

	big32_u64_t		my_sz64;
	big32_u128_t	my_sz128;
	big32_u256_t	my_sz256;
	big32_u512_t	my_sz512;

	big32_u256_t	_my_aaa;
	big32_u256_t	_my_bbb;
	big32_u256_t	_my_ccc;
	big32_u256_t	_my_ddd;
	big32_u256_t	_my_eee;

	big32_u256_t	_my_aaa_aa;
	big32_u256_t	_my_bbb_bb;
	big32_u256_t	_my_eee_ee;
	big32_u256_t	_my_fff_ff;
	big32_u256_t	_my_ggg_gg;

	big32_u256_t	_my_eee_ee_f;
	big32_u256_t	_my_fff_ff_f;
	big32_u256_t	_my_ggg_gg_f;
	big32_u256_t	_my_hhh_hh_f;

	big32_u128_t	_my_ee_eee_ee;
	big32_u128_t	_my_ff_fff_ff;
	big32_u128_t	_my_gg_ggg_gg;

	big32_u256_t	*my_aaa;
	big32_u256_t	*my_bbb;
	big32_u256_t	*my_ccc;
	big32_u256_t	*my_ddd;
	big32_u256_t	*my_eee;

	big32_u256_t	*my_aaa_aa;
	big32_u256_t	*my_bbb_bb;
	big32_u256_t	*my_eee_ee;
	big32_u256_t	*my_fff_ff;
	big32_u256_t	*my_ggg_gg;

	big32_u256_t	*my_eee_ee_f;
	big32_u256_t	*my_fff_ff_f;
	big32_u256_t	*my_ggg_gg_f;
	big32_u256_t	*my_hhh_hh_f;

	big32_u128_t	*my_ee_eee_ee;
	big32_u128_t	*my_ff_fff_ff;
	big32_u128_t	*my_gg_ggg_gg;
	
	big32_f256pt_t	_ptA;
	big32_f256pt_t	*ptA;
	
	big32_u64_t		one_u64 = { .r32 = { 1, 0 } } ;
	big32_u128_t	one_u128 = { .r32 = { 1, 0, 0, 0 } } ;
	big32_u256_t	one_u256 = { .r32 = { 1, 0, 0, 0, 0, 0, 0, 0 } } ;

	FILE	*urandom;
	
	uint64_t count;
	int32_t	test_shift;
	
	my_a = (big32_u64_t *)&a;
	my_b = (big32_u64_t *)&b;
	my_b2 = (big32_u64_t *)&b2;
	my_c = &_my_c;
	my_d = &_my_d;
	my_e = &_my_e;
	my_f = &_my_f;
	my_g = &_my_g;
	
	my_a_f = &_my_a_f;
	my_b_f = &_my_b_f;
	my_c_f = &_my_c_f;
	my_d_f = &_my_d_f;
	my_e_f = &_my_e_f;
	my_f_f = (big32_u64_t *)&f_f;
	my_g_f = (big32_u64_t *)&g_f;
	
	my_c_t = (big32_u64_t *)&c;
	my_d_t = (big32_u64_t *)&d;
	my_e_t = (big32_u64_t *)&e;
	my_f_t = (big32_u64_t *)&f;
	my_g_t = (big32_u64_t *)&g;

	my_c_tc = (big32_u64_t *)&_my_c_tc;
	my_d_tc = (big32_u64_t *)&_my_d_tc;
	my_e_tc = (big32_u64_t *)&_my_e_tc;

	my_a_ft = (big32_u64_t *)&a_f;
	my_b_ft = (big32_u64_t *)&b_f;
	my_c_ft = (big32_u64_t *)&c_f;
	my_d_ft = (big32_u64_t *)&d_f;
	my_e_ft = (big32_u64_t *)&e_f;
	my_f_ft = (big32_u64_t *)&f_f;

	my_aa = (big32_u128_t *)&aa;
	my_bb = (big32_u128_t *)&bb;
	my_bb2 = (big32_u128_t *)&bb2;
	my_cc = &_my_cc;
	my_dd = &_my_dd;
	my_ee = &_my_ee;
	my_ff = &_my_ff;
	my_gg = &_my_gg;

	my_aa_f = &_my_aa_f;
	my_bb_f = &_my_bb_f;
	my_cc_f = &_my_cc_f;
	my_dd_f = &_my_dd_f;
	my_ee_f = &_my_ee_f;
	my_ff_f = &_my_ff_f;
	my_gg_f = &_my_gg_f;
	my_hh_f = &_my_hh_f;
	my_ii_f = &_my_ii_f;

#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	my_cc_t = &cc;
	my_dd_t = &dd;
	my_ee_t = &ee;
	my_ff_t = &ff;
	my_gg_t = &gg;
#endif

	my_cc_tc = &_my_cc_tc;
	my_dd_tc = &_my_dd_tc;
	my_ee_tc = &_my_ee_tc;

	my_aa_a = &_my_aa_a;
	my_bb_b = &_my_bb_b;
	my_cc_c = &_my_cc_c;
	my_dd_d = &_my_dd_d;
	my_ee_e = &_my_ee_e;

	my_a_aa_a = (big32_u64_t *)&_my_a_aa_a;
	my_b_bb_b = (big32_u64_t *)&_my_b_bb_b;
	my_c_cc_c = (big32_u64_t *)&_my_c_cc_c;
	my_d_dd_d = (big32_u64_t *)&_my_d_dd_d;
	my_e_ee_e = (big32_u64_t *)&_my_e_ee_e;
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	my_ee_e_t = (big32_u128_t *)&ee_e;
#endif
	
	my_aaa = &_my_aaa;
	my_bbb = &_my_bbb;
	my_ccc = &_my_ccc;
	my_ddd = &_my_ddd;
	my_eee = &_my_eee;
	
	my_aaa_aa = &_my_aaa_aa;
	my_bbb_bb = &_my_bbb_bb;
	my_eee_ee = &_my_eee_ee;
	my_fff_ff = &_my_fff_ff;
	my_ggg_gg = &_my_ggg_gg;

	my_eee_ee_f = &_my_eee_ee_f;
	my_fff_ff_f = &_my_fff_ff_f;
	my_ggg_gg_f = &_my_ggg_gg_f;
	my_hhh_hh_f = &_my_hhh_hh_f;

	my_ee_eee_ee = &_my_ee_eee_ee;
	my_ff_fff_ff = &_my_ff_fff_ff;
	my_gg_ggg_gg = &_my_gg_ggg_gg;
	
	ptA = &_ptA;

	printf("sizeof(u64)     = %02u\n", sizeof(sz64));
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	printf("sizeof(u128)    = %02lu\n", sizeof(sz128));
#endif
	printf("sizeof(my_u64)  = %02u\n", sizeof(my_sz64));
	printf("sizeof(my_u128) = %02u\n", sizeof(my_sz128));
	printf("sizeof(my_u256) = %02u\n", sizeof(my_sz256));
	printf("sizeof(my_u512) = %02u\n", sizeof(my_sz512));

	urandom = fopen("/dev/urandom","rb");
	if (urandom == NULL) {
		fprintf(stderr,"Error opening /dev/urandom, exiting\n") ;
		exit(1); } ;
		
	if (fread(&a, sizeof(a), 1, urandom) != 1) {
		fprintf(stderr,"Error reading long long\n"); exit (2); } ;
		
	if (fread(&b, sizeof(b), 1, urandom) != 1) {
		fprintf(stderr,"Error reading long long\n"); exit (2); } ;

	do {
		if (fread(&b2, sizeof(b2), 1, urandom) != 1) {
			fprintf(stderr,"Err reading uint64\n"); exit (2); } ;

		if (fread(&test_shift, sizeof(test_shift), 1, urandom) != 1) {
			fprintf(stderr,"Error reading shift\n"); exit (2); } ;

		test_shift &= 0x3F;
		b2 >>= test_shift ;

	} while (b2 == 0);

	if (fread(&aa, sizeof(aa), 1, urandom) != 1) {
		fprintf(stderr,"Error reading uint128_t\n"); exit (2); } ;
		
	if (fread(&bb, sizeof(bb), 1, urandom) != 1) {
		fprintf(stderr,"Error reading uint128_t\n"); exit (2); } ;
		
	do {
		if (fread(&bb2, sizeof(bb2), 1, urandom) != 1) {
			fprintf(stderr,"Err reading uint128_t\n"); exit (2); } ;

		if (fread(&test_shift, sizeof(test_shift), 1, urandom) != 1) {
			fprintf(stderr,"Error reading shift\n"); exit (2); } ;

		test_shift &= 0x7F;
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
		bb2 >>= test_shift ;

	} while (bb2 == 0);
#else
		{
			big32_u128_t	temp;
			big32_u128_copy(&temp, &bb2);
			big32_u128_shift_right(&bb2, &temp, test_shift);
		}
	} while (big32_u128_is_zero(&bb2));	
#endif

	if (fread(my_aaa, sizeof(_my_aaa), 1, urandom) != 1) {
		fprintf(stderr,"Error reading uint256_t\n"); exit (2); } ;
		
	if (fread(my_bbb, sizeof(_my_bbb), 1, urandom) != 1) {
		fprintf(stderr,"Error reading uint256_t\n"); exit (2); } ;

	c = a + b ;
	d = a - b ;
	e = a * b ;
	f = a / b2 ;
	g = a % b2 ;

	big32_u64_add(my_c, my_a, my_b);
	big32_u64_sub(my_d, my_a, my_b);
	big32_u64_mul64(my_e, my_a, my_b);
	big32_u64_div(my_f, my_g, my_a, my_b2);
	
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	aa_a = a ;
	bb_b = b ;
	
	cc_c = aa_a + bb_b ;
	dd_d = aa_a - bb_b ;
	ee_e = aa_a * bb_b ;
#endif
	
	a_f = a % u64_f ;
	b_f = b % u64_f ;
	c_f = a_f > u64_f - b_f ? ( a_f + b_f ) - u64_f : a_f + b_f ;
	d_f = a_f >= b_f ? a_f - b_f: (a_f - b_f) + u64_f ;
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	aa_a_f = a_f ;
	bb_b_f = b_f ;
	ee_e_f = (aa_a_f * bb_b_f) % ((__int128_t)u64_f) ;
	e_f = ee_e_f & 0xFFFFFFFFFFFFFFFFULL;
#else
	big32_promo_u128_from_u64(&aa_a_f, (big32_u64_t *)&a_f);
	big32_promo_u128_from_u64(&bb_b_f, (big32_u64_t *)&b_f);
	{
		big32_u128_t temp1,temp2, temp3;
		big32_promo_u128_from_u64(&temp1, &field_p_u64);
		big32_u128_mul128(&temp2, &bb_b_f, &aa_a_f);
		big32_u128_div(&temp3, &ee_e_f, &temp2, &temp1); }
	big32_trunc_u64_from_u128((big32_u64_t *)&e_f, &ee_e_f);
#endif
	
	big32_f64_from_u64(my_a_f, my_a);
	big32_f64_from_u64(my_b_f, my_b);
	big32_f64_add(my_c_f, my_a_f, my_b_f);
	big32_f64_sub(my_d_f, my_a_f, my_b_f);
	big32_f64_mul64(my_e_f, my_a_f, my_b_f);
	big32_f64_inv(my_f_f, my_b_f);
	big32_f64_mul64(my_g_f, my_f_f, my_b_f);
	
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	ff_f_f = f_f;
	gg_g_f = bb_b_f * ff_f_f;
	hh_h_f = gg_g_f % u64_f;
#endif
	
	big32_promo_u128_from_u64(my_aa_a, my_a);
	big32_promo_u128_from_u64(my_bb_b, my_b);
	big32_u128_add(my_cc_c, my_aa_a, my_bb_b);
	big32_u128_sub(my_dd_d, my_aa_a, my_bb_b);
	big32_trunc_u64_from_u128(my_a_aa_a,my_aa_a);
	big32_trunc_u64_from_u128(my_b_bb_b,my_bb_b);
	big32_trunc_u64_from_u128(my_c_cc_c,my_cc_c);
	big32_trunc_u64_from_u128(my_d_dd_d,my_dd_d);
	big32_u64_mul128(my_ee_e, my_a, my_b);
	
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	cc = aa + bb ;
	dd = aa - bb ;
	ee = aa * bb ;
	ff = aa / bb2 ;
	gg = aa % bb2 ;
#endif

	big32_u128_add(my_cc, my_aa, my_bb);
	big32_u128_sub(my_dd, my_aa, my_bb);
	big32_u128_mul128(my_ee, my_aa, my_bb);
	big32_u128_div(my_ff, my_gg, my_aa, my_bb2);
	
	big32_f128_from_u128(my_aa_f, my_aa);
	big32_f128_from_u128(my_bb_f, my_bb);
	big32_f128_add(my_cc_f, my_aa_f, my_bb_f);
	big32_f128_sub(my_dd_f, my_aa_f, my_bb_f);
	big32_f128_sub(my_ee_f, my_cc_f, my_aa_f);
	big32_f128_add(my_ff_f, my_dd_f, my_bb_f);
	big32_f128_inv(my_gg_f, my_aa_f);
	big32_f128_mul128(my_hh_f, my_aa_f, my_gg_f);
	
	big32_u128_mul256(my_eee_ee_f, my_aa_f, my_gg_f);
	big32_promo_u256_from_u128(my_fff_ff_f, &field_p_u128);
	big32_u256_div(my_ggg_gg_f, my_hhh_hh_f, my_eee_ee_f, my_fff_ff_f);
	
	big32_u256_add(my_ccc, my_aaa, my_bbb);
	big32_u256_sub(my_ddd, my_aaa, my_bbb);
	big32_u256_mul256(my_eee, my_aaa, my_bbb);
	
	big32_u128_mul256(my_eee_ee, my_aa, my_bb);
	big32_promo_u256_from_u128(my_aaa_aa, my_aa);
	big32_promo_u256_from_u128(my_bbb_bb, my_bb);
	big32_u256_div(my_fff_ff, my_ggg_gg, my_eee_ee, my_bbb_bb);
	big32_trunc_u128_from_u256(my_ee_eee_ee,my_eee_ee);
	big32_trunc_u128_from_u256(my_ff_fff_ff,my_fff_ff);
	big32_trunc_u128_from_u256(my_gg_ggg_gg,my_ggg_gg);
	
	big32_f256_scalar_pt_mul256(ptA, &private_key_test, &secp256k1_G);

	printf("a     = 0x%016llX ", a);
	printf("b     = 0x%016llX ", b);	
	printf("b2    = 0x%016llX ", b2);	
	printf("c     = 0x%016llX ", c);
	printf("d     = 0x%016llX\n", d);
	printf("e     = 0x%016llX ", e);
	printf("f     = 0x%016llX ", f);
	printf("g     = 0x%016llX\n", g);

	printf("my_a  = 0x%08X%08X ", my_a->r32.msw, my_a->r32.lsw);
	printf("my_b  = 0x%08X%08X ", my_b->r32.msw, my_b->r32.lsw);	
	printf("my_b2 = 0x%08X%08X ", my_b2->r32.msw, my_b2->r32.lsw);	
	printf("my_c  = 0x%08X%08X ", my_c->r32.msw, my_c->r32.lsw);
	printf("my_d  = 0x%08X%08X\n", my_d->r32.msw, my_d->r32.lsw);
	printf("my_e  = 0x%08X%08X ", my_e->r32.msw, my_e->r32.lsw);
	printf("my_f  = 0x%08X%08X ", my_f->r32.msw, my_f->r32.lsw);
	printf("my_g  = 0x%08X%08X\n", my_g->r32.msw, my_g->r32.lsw);

	printf("my_a h= 0x%04hX%04hX%04hX%04hX ", my_a->r16.msh, my_a->r16.s3h, my_a->r16.s2h, my_a->r16.lsh);
	printf("my_b h= 0x%04hX%04hX%04hX%04hX ", my_b->r16.msh, my_b->r16.s3h, my_b->r16.s2h, my_b->r16.lsh);
	
	printf("my_c h= 0x%04hX%04hX%04hX%04hX ", my_c->r16.msh, my_c->r16.s3h, my_c->r16.s2h, my_c->r16.lsh);
	printf("my_d h= 0x%04hX%04hX%04hX%04hX ", my_d->r16.msh, my_d->r16.s3h, my_d->r16.s2h, my_d->r16.lsh);
	printf("my_e h= 0x%04hX%04hX%04hX%04hX\n", my_e->r16.msh, my_e->r16.s3h, my_e->r16.s2h, my_e->r16.lsh);

	printf("a_f   = 0x%016llX ", a_f);
	printf("b_f   = 0x%016llX ", b_f);
	
	printf("c_f   = 0x%016llX ", c_f);
	printf("d_f   = 0x%016llX ", d_f);
	printf("e_f   = 0x%016llX\n", e_f);

	printf("my_a f= 0x%08X%08X ", my_a_f->r32.msw, my_a_f->r32.lsw);
	printf("my_b f= 0x%08X%08X ", my_b_f->r32.msw, my_b_f->r32.lsw);
	
	printf("my_c f= 0x%08X%08X ", my_c_f->r32.msw, my_c_f->r32.lsw);
	printf("my_d f= 0x%08X%08X ", my_d_f->r32.msw, my_d_f->r32.lsw);
	printf("my_e f= 0x%08X%08X\n", my_e_f->r32.msw, my_e_f->r32.lsw);
	printf("my_f f= 0x%08X%08X ", my_f_f->r32.msw, my_f_f->r32.lsw);
	printf("my_g f= 0x%08X%08X\n", my_g_f->r32.msw, my_g_f->r32.lsw);

#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	printf("bb_b_f= 0x%016llX %016llX ", ((uint64_t)(bb_b_f >> 64)) , ((uint64_t)(bb_b_f & 0xFFFFFFFFFFFFFFFFULL)));
	printf("ff_f_f= 0x%016llX %016llX\n", ((uint64_t)(ff_f_f >> 64)) , ((uint64_t)(ff_f_f & 0xFFFFFFFFFFFFFFFFULL)));
	printf("gg_g_f= 0x%016llX %016llX ", ((uint64_t)(gg_g_f >> 64)) , ((uint64_t)(gg_g_f & 0xFFFFFFFFFFFFFFFFULL)));
	printf("hh_h_f= 0x%016llX %016llX\n", ((uint64_t)(hh_h_f >> 64)) , ((uint64_t)(hh_h_f & 0xFFFFFFFFFFFFFFFFULL)));

	printf("aa    = 0x%016llX %016llX ", ((uint64_t)(aa >> 64)) , ((uint64_t)(aa & 0xFFFFFFFFFFFFFFFFULL)));
	printf("bb    = 0x%016llX %016llX ", ((uint64_t)(bb >> 64)) , ((uint64_t)(bb & 0xFFFFFFFFFFFFFFFFULL)));
	printf("bb2   = 0x%016llX %016llX\n", ((uint64_t)(bb2 >> 64)) , ((uint64_t)(bb2 & 0xFFFFFFFFFFFFFFFFULL)));
#endif
	
	printf("my_aa = 0x%08X%08X %08X%08X ", my_aa->r32.msw, my_aa->r32.s3w, my_aa->r32.s2w, my_aa->r32.lsw);
	printf("my_bb = 0x%08X%08X %08X%08X ", my_bb->r32.msw, my_bb->r32.s3w, my_bb->r32.s2w, my_bb->r32.lsw);
	printf("my_bb2= 0x%08X%08X %08X%08X\n", my_bb2->r32.msw, my_bb2->r32.s3w, my_bb2->r32.s2w, my_bb2->r32.lsw);
	
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	printf("cc    = 0x%016llX %016llX ", ((uint64_t)(cc >> 64)) , ((uint64_t)(cc & 0xFFFFFFFFFFFFFFFFULL)));
	printf("dd    = 0x%016llX %016llX ", ((uint64_t)(dd >> 64)) , ((uint64_t)(dd & 0xFFFFFFFFFFFFFFFFULL)));
	printf("ee    = 0x%016llX %016llX\n", ((uint64_t)(ee >> 64)) , ((uint64_t)(ee & 0xFFFFFFFFFFFFFFFFULL)));
#endif

	printf("my_cc = 0x%08X%08X %08X%08X ", my_cc->r32.msw, my_cc->r32.s3w, my_cc->r32.s2w, my_cc->r32.lsw);
	printf("my_dd = 0x%08X%08X %08X%08X ", my_dd->r32.msw, my_dd->r32.s3w, my_dd->r32.s2w, my_dd->r32.lsw);
	printf("my_ee = 0x%08X%08X %08X%08X\n", my_ee->r32.msw, my_ee->r32.s3w, my_ee->r32.s2w, my_ee->r32.lsw);

#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	printf("ff    = 0x%016llX %016llX ", ((uint64_t)(ff >> 64)) , ((uint64_t)(ff & 0xFFFFFFFFFFFFFFFFULL)));
	printf("gg    = 0x%016llX %016llX\n", ((uint64_t)(gg >> 64)) , ((uint64_t)(gg & 0xFFFFFFFFFFFFFFFFULL)));
#endif

	printf("my_ff = 0x%08X%08X %08X%08X ", my_ff->r32.msw, my_ff->r32.s3w, my_ff->r32.s2w, my_ff->r32.lsw);
	printf("my_gg = 0x%08X%08X %08X%08X\n", my_gg->r32.msw, my_gg->r32.s3w, my_gg->r32.s2w, my_gg->r32.lsw);

	printf("my_aa f= 0x%08X%08X %08X%08X ", my_aa_f->r32.msw, my_aa_f->r32.s3w, my_aa_f->r32.s2w, my_aa_f->r32.lsw);
	printf("my_bb f= 0x%08X%08X %08X%08X\n", my_bb_f->r32.msw, my_bb_f->r32.s3w, my_bb_f->r32.s2w, my_bb_f->r32.lsw);
	printf("my_cc f= 0x%08X%08X %08X%08X ", my_cc_f->r32.msw, my_cc_f->r32.s3w, my_cc_f->r32.s2w, my_cc_f->r32.lsw);
	printf("my_dd f= 0x%08X%08X %08X%08X\n", my_dd_f->r32.msw, my_dd_f->r32.s3w, my_dd_f->r32.s2w, my_dd_f->r32.lsw);
	printf("my_ee f= 0x%08X%08X %08X%08X ", my_ee_f->r32.msw, my_ee_f->r32.s3w, my_ee_f->r32.s2w, my_ee_f->r32.lsw);
	printf("my_ff f= 0x%08X%08X %08X%08X\n", my_ff_f->r32.msw, my_ff_f->r32.s3w, my_ff_f->r32.s2w, my_ff_f->r32.lsw);

	printf("my_gg f= 0x%08X%08X %08X%08X ", my_gg_f->r32.msw, my_gg_f->r32.s3w, my_gg_f->r32.s2w, my_gg_f->r32.lsw);
	printf("my_hh f= 0x%08X%08X %08X%08X\n", my_hh_f->r32.msw, my_hh_f->r32.s3w, my_hh_f->r32.s2w, my_hh_f->r32.lsw);

	printf("my_eee_ee f= 0x%016llX %016llX %016llX %016llX\n", my_eee_ee_f->dword[3], my_eee_ee_f->dword[2], my_eee_ee_f->dword[1], my_eee_ee_f->dword[0]);
	printf("my_fff_ff f= 0x%016llX %016llX %016llX %016llX\n", my_fff_ff_f->dword[3], my_fff_ff_f->dword[2], my_fff_ff_f->dword[1], my_fff_ff_f->dword[0]);
	printf("my_ggg_gg f= 0x%016llX %016llX %016llX %016llX\n", my_ggg_gg_f->dword[3], my_ggg_gg_f->dword[2], my_ggg_gg_f->dword[1], my_ggg_gg_f->dword[0]);
	printf("my_hhh_hh f= 0x%016llX %016llX %016llX %016llX\n", my_hhh_hh_f->dword[3], my_hhh_hh_f->dword[2], my_hhh_hh_f->dword[1], my_hhh_hh_f->dword[0]);

#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	printf("aa_a    = 0x%016llX %016llX ", ((uint64_t)(aa_a >> 64)) , ((uint64_t)(aa_a & 0xFFFFFFFFFFFFFFFFULL)));
	printf("bb_b    = 0x%016llX %016llX\n", ((uint64_t)(bb_b >> 64)) , ((uint64_t)(bb_b & 0xFFFFFFFFFFFFFFFFULL)));
	
	printf("cc_c    = 0x%016llX %016llX ", ((uint64_t)(cc_c >> 64)) , ((uint64_t)(cc_c & 0xFFFFFFFFFFFFFFFFULL)));
	printf("dd_d    = 0x%016llX %016llX ", ((uint64_t)(dd_d >> 64)) , ((uint64_t)(dd_d & 0xFFFFFFFFFFFFFFFFULL)));
	printf("ee_e    = 0x%016llX %016llX\n", ((uint64_t)(ee_e >> 64)) , ((uint64_t)(ee_e & 0xFFFFFFFFFFFFFFFFULL)));
#endif

	printf("my_aa_a = 0x%08X%08X %08X%08X ", my_aa_a->r32.msw, my_aa_a->r32.s3w, my_aa_a->r32.s2w, my_aa_a->r32.lsw);
	printf("my_bb_b = 0x%08X%08X %08X%08X\n", my_bb_b->r32.msw, my_bb_b->r32.s3w, my_bb_b->r32.s2w, my_bb_b->r32.lsw);

	printf("my_cc_c = 0x%08X%08X %08X%08X ", my_cc_c->r32.msw, my_cc_c->r32.s3w, my_cc_c->r32.s2w, my_cc_c->r32.lsw);
	printf("my_dd_d = 0x%08X%08X %08X%08X ", my_dd_d->r32.msw, my_dd_d->r32.s3w, my_dd_d->r32.s2w, my_dd_d->r32.lsw);
	printf("my_ee_e = 0x%08X%08X %08X%08X\n", my_ee_e->r32.msw, my_ee_e->r32.s3w, my_ee_e->r32.s2w, my_ee_e->r32.lsw);

	printf("my_a_aa_a = 0x%08X%08X ", my_a_aa_a->r32.msw, my_a_aa_a->r32.lsw);
	printf("my_b_bb_b = 0x%08X%08X ", my_b_bb_b->r32.msw, my_b_bb_b->r32.lsw);
	
	printf("my_c_cc_c = 0x%08X%08X ", my_c_cc_c->r32.msw, my_c_cc_c->r32.lsw);
	printf("my_d_dd_d = 0x%08X%08X\n", my_d_dd_d->r32.msw, my_d_dd_d->r32.lsw);

	printf("my_aaa = 0x%016llX %016llX %016llX %016llX\n", my_aaa->dword[3], my_aaa->dword[2], my_aaa->dword[1], my_aaa->dword[0]);
	printf("my_bbb = 0x%016llX %016llX %016llX %016llX\n", my_bbb->dword[3], my_bbb->dword[2], my_bbb->dword[1], my_bbb->dword[0]);
	printf("my_ccc = 0x%016llX %016llX %016llX %016llX\n", my_ccc->dword[3], my_ccc->dword[2], my_ccc->dword[1], my_ccc->dword[0]);
	printf("my_ddd = 0x%016llX %016llX %016llX %016llX\n", my_ddd->dword[3], my_ddd->dword[2], my_ddd->dword[1], my_ddd->dword[0]);
	printf("my_eee = 0x%016llX %016llX %016llX %016llX\n", my_eee->dword[3], my_eee->dword[2], my_eee->dword[1], my_eee->dword[0]);

	printf("my_aaa_aa = 0x%016llX %016llX %016llX %016llX\n", my_aaa_aa->dword[3], my_aaa_aa->dword[2], my_aaa_aa->dword[1], my_aaa_aa->dword[0]);
	printf("my_bbb_bb = 0x%016llX %016llX %016llX %016llX\n", my_bbb_bb->dword[3], my_bbb_bb->dword[2], my_bbb_bb->dword[1], my_bbb_bb->dword[0]);
	printf("my_eee_ee = 0x%016llX %016llX %016llX %016llX\n", my_eee_ee->dword[3], my_eee_ee->dword[2], my_eee_ee->dword[1], my_eee_ee->dword[0]);
	printf("my_fff_ff = 0x%016llX %016llX %016llX %016llX\n", my_fff_ff->dword[3], my_fff_ff->dword[2], my_fff_ff->dword[1], my_fff_ff->dword[0]);
	printf("my_ggg_gg = 0x%016llX %016llX %016llX %016llX\n", my_ggg_gg->dword[3], my_ggg_gg->dword[2], my_ggg_gg->dword[1], my_ggg_gg->dword[0]);
	
	printf("Generator Point = 04 0x%016llX %016llX %016llX %016llX 0x%016llX %016llX %016llX %016llX\n", secp256k1_G.x.dword[3], secp256k1_G.x.dword[2], secp256k1_G.x.dword[1], secp256k1_G.x.dword[0], secp256k1_G.y.dword[3], secp256k1_G.y.dword[2], secp256k1_G.y.dword[1], secp256k1_G.y.dword[0]);

	printf("Test Private Key = 0x%016llX %016llX %016llX %016llX\n", private_key_test.dword[3], private_key_test.dword[2], private_key_test.dword[1], private_key_test.dword[0]);
	
	printf("Public Key = 04 0x%016llX %016llX %016llX %016llX 0x%016llX %016llX %016llX %016llX\n", ptA->x.dword[3], ptA->x.dword[2], ptA->x.dword[1], ptA->x.dword[0], ptA->y.dword[3], ptA->y.dword[2], ptA->y.dword[1], ptA->y.dword[0]);

	//for (count = 0 ; count < 100000000 ; count++) {
	count = 0 ; 
	while (1) {
		count++;
		
		if (fread(&a, sizeof(a), 1, urandom) != 1) {
			fprintf(stderr,"Err reading uint64\n"); exit (2); } ;
		
		if (fread(&b, sizeof(b), 1, urandom) != 1) {
			fprintf(stderr,"Err reading uint64\n"); exit (2); } ;

		//a     = 0x0AB62A220E3B7B2E b     = 0xC7383FFFFFFFFD31
		//a     = 0x0AB62A220E3B7B2EULL ;
		//b     = 0xC7383FFFFFFFFD31ULL ;
		
		do {
			if (fread(&b2, sizeof(b2), 1, urandom) != 1) {
				fprintf(stderr,"Err reading uint64\n"); exit (2); } ;

			if (fread(&test_shift, sizeof(test_shift), 1, urandom) != 1) {
				fprintf(stderr,"Error reading shift\n"); exit (2); } ;

			test_shift &= 0x3F;
			b2 >>= test_shift ;
			
		} while (b2 == 0);

		if (fread(&aa, sizeof(aa), 1, urandom) != 1) {
			fprintf(stderr,"Err reading uint128\n"); exit (2); } ;
		
		if (fread(&bb, sizeof(bb), 1, urandom) != 1) {
			fprintf(stderr,"Err reading uint128\n"); exit (2); } ;
			
		// aa    = 0x2870307FDDEC6268 A18D070A0000002D bb    = 0x5825599FCE7A8185 9B117234EA955C86

		//my_aa->r64.msd = 0x2870307FDDEC6268ULL ;
		//my_aa->r64.lsd = 0xA18D070A0000002DULL ;
		//my_bb->r64.msd = 0x5825599FCE7A8185ULL ; 
		//my_bb->r64.lsd = 0x9B117234EA955C86ULL ;
		
		// my_aa f= 0xF2542D1935E43906 24AC438848F33637 my_bb f= 0x9D8499FDA1BD637D 4944C6614DEDD273

		//my_aa->r64.msd = 0xF2542D1935E43906ULL ;
		//my_aa->r64.lsd = 0x24AC438848F33637ULL ;
		//my_bb->r64.msd = 0x9D8499FDA1BD637DULL ; 
		//my_bb->r64.lsd = 0x4944C6614DEDD273ULL ;
		
		do {
			if (fread(&bb2, sizeof(bb2), 1, urandom) != 1) {
				fprintf(stderr,"Err reading uint128\n"); exit (2); } ;

			if (fread(&test_shift, sizeof(test_shift), 1, urandom) != 1) {
				fprintf(stderr,"Error reading shift\n"); exit (2); } ;

			test_shift &= 0x7F;
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
			bb2 >>= test_shift ;

		} while (bb2 == 0);
#else
			{
				big32_u128_t	temp;
				big32_u128_copy(&temp, &bb2);
				big32_u128_shift_right(&bb2, &temp, test_shift);
			}
		} while (big32_u128_is_zero(&bb2));	
#endif

		if (fread(my_aaa, sizeof(_my_aaa), 1, urandom) != 1) {
			fprintf(stderr,"Error reading uint256_t\n"); exit (2); } ;
		
		if (fread(my_bbb, sizeof(_my_bbb), 1, urandom) != 1) {
			fprintf(stderr,"Error reading uint256_t\n"); exit (2); } ;

		c = a + b ;
		d = a - b ;
		e = a * b ;
		f = a / b2 ;
		g = a % b2 ;

		big32_u64_add(my_c, my_a, my_b);
		big32_u64_sub(my_d, my_a, my_b);
		big32_u64_mul64(my_e, my_a, my_b);
		big32_u64_div(my_f, my_g, my_a, my_b2);
		
		big32_u64_copy(my_c_tc, my_a);
		big32_u64_copy(my_d_tc, my_a);
		
		if (!big32_u64_is_equal(my_a, my_c_tc)) {
			fprintf(stderr,"Err : a != c_tc\n"); exit (2); } ;

		big32_u64_pluseq(my_c_tc, my_b);
		big32_u64_minuseq(my_d_tc, my_b);
	
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
		aa_a = a ;
		bb_b = b ;
	
		cc_c = aa_a + bb_b ;
		dd_d = aa_a - bb_b ;
		ee_e = aa_a * bb_b ;
#endif
	
		a_f = a % u64_f ;
		b_f = b % u64_f ;
		c_f = a_f > u64_f - b_f ? ( a_f + b_f ) - u64_f : a_f + b_f ;
		d_f = a_f >= b_f ? a_f - b_f: (a_f - b_f) + u64_f ;
		
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
		aa_a_f = a_f ;
		bb_b_f = b_f ;
		ee_e_f = (aa_a_f * bb_b_f) % ((__int128_t)u64_f) ;
		e_f = ee_e_f & 0xFFFFFFFFFFFFFFFFULL;
#else
		big32_promo_u128_from_u64(&aa_a_f, (big32_u64_t *)&a_f);
		big32_promo_u128_from_u64(&bb_b_f, (big32_u64_t *)&b_f);
		{
			big32_u128_t temp1,temp2, temp3;
			big32_promo_u128_from_u64(&temp1, &field_p_u64);
			big32_u128_mul128(&temp2, &bb_b_f, &aa_a_f);
			big32_u128_div(&temp3, &ee_e_f, &temp2, &temp1); }
		big32_trunc_u64_from_u128((big32_u64_t *)&e_f, &ee_e_f);
#endif

		big32_f64_from_u64(my_a_f, my_a);
		big32_f64_from_u64(my_b_f, my_b);
		big32_f64_add(my_c_f, my_a_f, my_b_f);
		big32_f64_sub(my_d_f, my_a_f, my_b_f);
		big32_f64_mul64(my_e_f, my_a_f, my_b_f);
		big32_f64_inv(my_f_f, my_b_f);
		big32_f64_mul64(my_g_f, my_f_f, my_b_f);

#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
		ff_f_f = f_f;
		gg_g_f = bb_b_f * ff_f_f;
		hh_h_f = gg_g_f % u64_f;
#endif
	
		big32_u128_copy(my_cc_tc, my_aa);
		big32_u128_copy(my_dd_tc, my_aa);
		
		if (!big32_u128_is_equal(my_aa, my_cc_tc)) {
			fprintf(stderr,"Err : a != c_tc\n"); exit (2); } ;

		big32_u128_pluseq(my_cc_tc, my_bb);
		big32_u128_minuseq(my_dd_tc, my_bb);
	
		big32_promo_u128_from_u64(my_aa_a, my_a);
		big32_promo_u128_from_u64(my_bb_b, my_b);
		big32_u128_add(my_cc_c, my_aa_a, my_bb_b);
		big32_u128_sub(my_dd_d, my_aa_a, my_bb_b);
		big32_trunc_u64_from_u128(my_a_aa_a,my_aa_a);
		big32_trunc_u64_from_u128(my_b_bb_b,my_bb_b);
		big32_trunc_u64_from_u128(my_c_cc_c,my_cc_c);
		big32_trunc_u64_from_u128(my_d_dd_d,my_dd_d);
		big32_u64_mul128(my_ee_e,my_a,my_b);
	
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
		cc = aa + bb ;
		dd = aa - bb ;
		ee = aa * bb ;
		ff = aa / bb2 ;
		gg = aa % bb2 ;
#endif

		big32_u128_add(my_cc, my_aa, my_bb);
		big32_u128_sub(my_dd, my_aa, my_bb);
		big32_u128_mul128(my_ee, my_aa, my_bb);
		big32_u128_div(my_ff, my_gg, my_aa, my_bb2);
		
		big32_u128_add(my_cc, my_aa, my_bb);
		big32_u128_sub(my_dd, my_aa, my_bb);
		big32_u128_mul128(my_ee, my_aa, my_bb);
		
		big32_f128_from_u128(my_aa_f, my_aa);
		big32_f128_from_u128(my_bb_f, my_bb);
		big32_f128_add(my_cc_f, my_aa_f, my_bb_f);
		big32_f128_sub(my_dd_f, my_aa_f, my_bb_f);
		big32_f128_sub(my_ee_f, my_cc_f, my_aa_f);
		big32_f128_add(my_ff_f, my_dd_f, my_bb_f);
		big32_f128_inv(my_gg_f, my_aa_f);
		big32_f128_mul128(my_hh_f, my_aa_f, my_gg_f);
	
		big32_u128_mul256(my_eee_ee_f, my_aa_f, my_gg_f);
		big32_promo_u256_from_u128(my_fff_ff_f, &field_p_u128);
		big32_u256_div(my_ggg_gg_f, my_hhh_hh_f, my_eee_ee_f, my_fff_ff_f);
	
		big32_u128_mul256(my_eee_ee, my_aa, my_bb);
		big32_promo_u256_from_u128(my_bbb_bb, my_bb);
		big32_promo_u256_from_u128(my_aaa_aa, my_aa);
		big32_u256_div(my_fff_ff, my_ggg_gg, my_eee_ee, my_bbb_bb);
		big32_trunc_u128_from_u256(my_ee_eee_ee,my_eee_ee);
		big32_trunc_u128_from_u256(my_ff_fff_ff,my_fff_ff);
		big32_trunc_u128_from_u256(my_gg_ggg_gg,my_ggg_gg);

		if (!big32_u64_is_equal(my_a_f, my_a_ft)) {
			fprintf(stderr,"Err : a_f != a_ft\n"); goto choke ; } ;

		if (!big32_u64_is_equal(my_b_f, my_b_ft)) {
			fprintf(stderr,"Err : b_f != b_ft\n"); goto choke ; } ;

		if (!big32_u64_is_equal(my_c_f, my_c_ft)) {
			fprintf(stderr,"Err : c_f != c_ft\n"); goto choke ; } ;

		if (!big32_u64_is_equal(my_d_f, my_d_ft)) {
			fprintf(stderr,"Err : d_f != d_ft\n"); goto choke ; } ;

		if (!big32_u64_is_equal(my_e_f, my_e_ft)) {
			fprintf(stderr,"Err : e_f != e_ft\n"); goto choke ; } ;

		if (!big32_u64_is_equal(my_g_f, &one_u64)) {
			fprintf(stderr,"Err : my_g_f != 1\n"); goto choke ; } ;

#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
		if (hh_h_f != 1) {
			fprintf(stderr,"Err : hh_h_f != 1\n"); goto choke ; } ;
#endif

		if (!big32_u64_is_equal(my_a, my_a_aa_a)) {
			fprintf(stderr,"Err : a != a_aa_a\n"); goto choke ; } ;

		if (!big32_u64_is_equal(my_b, my_b_bb_b)) {
			fprintf(stderr,"Err : b != b_bb_b\n"); goto choke ; } ;

		if (!big32_u64_is_equal(my_c, my_c_cc_c)) {
			fprintf(stderr,"Err : c != c_cc_c\n"); goto choke ; } ;

		if (!big32_u64_is_equal(my_d, my_d_dd_d)) {
			fprintf(stderr,"Err : d != d_dd_d\n"); goto choke ; } ;
			
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
		if (!big32_u128_is_equal(my_ee_e_t, my_ee_e)) {
			fprintf(stderr,"Err : ee_e_t != ee_e\n"); goto choke ; } ;
#endif
			
		if (!big32_u64_is_equal(my_c, my_c_t)) {
			fprintf(stderr,"Err : c != c_t\n"); goto choke ; } ;

		if (!big32_u64_is_equal(my_d, my_d_t)) {
			fprintf(stderr,"Err : d != d_t\n"); goto choke ; } ;
			
		if (!big32_u64_is_equal(my_e, my_e_t)) {
			fprintf(stderr,"Err : e != e_t\n"); goto choke ; } ;
			
		if (!big32_u64_is_equal(my_f, my_f_t)) {
			fprintf(stderr,"Err : f != f_t\n"); goto choke ; } ;
			
		if (!big32_u64_is_equal(my_g, my_g_t)) {
			fprintf(stderr,"Err : g != g_t\n"); goto choke ; } ;
			
		if (big32_u64_is_equal(my_c, my_d)) {
			fprintf(stderr,"Err : c == d\n"); goto choke ; } ;
			
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
		if (!big32_u128_is_equal(my_cc, my_cc_t)) {
			fprintf(stderr,"Err : cc != cc_t\n"); goto choke ; } ;

		if (!big32_u128_is_equal(my_dd, my_dd_t)) {
			fprintf(stderr,"Err : dd != dd_t\n"); goto choke ; } ;
			
		if (!big32_u128_is_equal(my_ee, my_ee_t)) {
			fprintf(stderr,"Err : ee != ee_t\n"); goto choke ; } ;
			
		if (!big32_u128_is_equal(my_ff, my_ff_t)) {
			fprintf(stderr,"Err : ff != ff_t\n"); goto choke ; } ;
			
		if (!big32_u128_is_equal(my_gg, my_gg_t)) {
			fprintf(stderr,"Err : gg != gg_t\n"); goto choke ; } ;
			
		if (big32_u128_is_equal(my_dd, my_cc)) {
			fprintf(stderr,"Err : cc != dd\n"); goto choke ; } ;
#endif
			
		if (!big32_u128_is_equal(my_aa_f, my_ff_f)) {
			fprintf(stderr,"Err : aa_f != ff_f\n"); goto choke ; } ;
			
		if (!big32_u128_is_equal(my_bb_f, my_ee_f)) {
			fprintf(stderr,"Err : bb_f != ee_f\n"); goto choke ; } ;
			
		if (!big32_u128_is_equal(my_hh_f, &one_u128)) {
			fprintf(stderr,"Err : hh_f != 1\n"); goto choke ; } ;
			
		if (!big32_u256_is_equal(my_hhh_hh_f, &one_u256)) {
			fprintf(stderr,"Err : hhh_hh_f != 1\n"); goto choke ; } ;
			
		if ((c > d) && (big32_u64_compare(my_c, my_d) != 1)) {
			fprintf(stderr,"Err : c>d != mc>md\n"); goto choke ; } ;
			
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
		if ((cc > dd) && (big32_u128_compare(my_cc, my_dd) != 1)) {
			fprintf(stderr,"Err : cc>dd != mcc>mdd\n"); goto choke ; } ;
#endif
			
		if ((c < d) && (big32_u64_compare(my_c, my_d) != -1)) {
			fprintf(stderr,"Err : c>d != mc>md\n"); goto choke ; } ;
			
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
		if ((cc < dd) && (big32_u128_compare(my_cc, my_dd) != -1)) {
			fprintf(stderr,"Err : cc>dd != mcc>mdd\n"); goto choke ; } ;
#endif
			
		if (!big32_u64_is_equal(my_c_tc, my_c)) {
			fprintf(stderr,"Err : c != c_tc\n"); goto choke ; } ;
			
		if (!big32_u64_is_equal(my_d_tc, my_d)) {
			fprintf(stderr,"Err : d != d_tc\n"); goto choke ; } ;
			
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
		if (!big32_u128_is_equal(my_cc_tc, my_cc)) {
			fprintf(stderr,"Err : cc != cc_tc\n"); goto choke ; } ;
			
		if (!big32_u128_is_equal(my_dd_tc, my_dd)) {
			fprintf(stderr,"Err : dd != dd_tc\n"); goto choke ; } ;
#endif
			
		if (!big32_u128_is_equal(my_ee, my_ee_eee_ee)) {
			fprintf(stderr,"Err : ee != ee_eee_ee\n"); goto choke ; } ;

		if (!big32_u256_is_equal(my_aaa_aa, my_fff_ff)) {
			fprintf(stderr,"Err : aaa_aa != fff_ff\n"); goto choke ; } ;
			
		if (!big32_u128_is_equal(my_aa, my_ff_fff_ff)) {
			fprintf(stderr,"Err : aa != ff_fff_ff\n"); goto choke ; } ;
			
		if (!big32_u128_is_zero(my_gg_ggg_gg)) {
			fprintf(stderr,"Err : gg_ggg_gg != 0\n"); goto choke ; } ;
			
			
		if ((count % 100) == 0) { printf("count=%llu\r",count); } ;
		if ((count % 1000000) == 0) { printf("count=%llu\n",count); } ;
	} ;

	fclose(urandom);

	return 0;
	
choke:
	
	printf("a     = 0x%016llX ", a);
	printf("b     = 0x%016llX ", b);	
	printf("b2    = 0x%016llX ", b2);	
	printf("c     = 0x%016llX ", c);
	printf("d     = 0x%016llX\n", d);
	printf("e     = 0x%016llX ", e);
	printf("f     = 0x%016llX ", f);
	printf("g     = 0x%016llX\n", g);

	printf("my_a  = 0x%08X%08X ", my_a->r32.msw, my_a->r32.lsw);
	printf("my_b  = 0x%08X%08X ", my_b->r32.msw, my_b->r32.lsw);	
	printf("my_b2 = 0x%08X%08X ", my_b2->r32.msw, my_b2->r32.lsw);	
	printf("my_c  = 0x%08X%08X ", my_c->r32.msw, my_c->r32.lsw);
	printf("my_d  = 0x%08X%08X\n", my_d->r32.msw, my_d->r32.lsw);
	printf("my_e  = 0x%08X%08X ", my_e->r32.msw, my_e->r32.lsw);
	printf("my_f  = 0x%08X%08X ", my_f->r32.msw, my_f->r32.lsw);
	printf("my_g  = 0x%08X%08X\n", my_g->r32.msw, my_g->r32.lsw);

	printf("my_a h= 0x%04hX%04hX%04hX%04hX ", my_a->r16.msh, my_a->r16.s3h, my_a->r16.s2h, my_a->r16.lsh);
	printf("my_b h= 0x%04hX%04hX%04hX%04hX ", my_b->r16.msh, my_b->r16.s3h, my_b->r16.s2h, my_b->r16.lsh);
	
	printf("my_c h= 0x%04hX%04hX%04hX%04hX ", my_c->r16.msh, my_c->r16.s3h, my_c->r16.s2h, my_c->r16.lsh);
	printf("my_d h= 0x%04hX%04hX%04hX%04hX ", my_d->r16.msh, my_d->r16.s3h, my_d->r16.s2h, my_d->r16.lsh);
	printf("my_e h= 0x%04hX%04hX%04hX%04hX\n", my_e->r16.msh, my_e->r16.s3h, my_e->r16.s2h, my_e->r16.lsh);

	printf("a_f   = 0x%016llX ", a_f);
	printf("b_f   = 0x%016llX ", b_f);
	
	printf("c_f   = 0x%016llX ", c_f);
	printf("d_f   = 0x%016llX ", d_f);
	printf("e_f   = 0x%016llX\n", e_f);

	printf("my_a f= 0x%08X%08X ", my_a_f->r32.msw, my_a_f->r32.lsw);
	printf("my_b f= 0x%08X%08X ", my_b_f->r32.msw, my_b_f->r32.lsw);
	
	printf("my_c f= 0x%08X%08X ", my_c_f->r32.msw, my_c_f->r32.lsw);
	printf("my_d f= 0x%08X%08X ", my_d_f->r32.msw, my_d_f->r32.lsw);
	printf("my_e f= 0x%08X%08X\n", my_e_f->r32.msw, my_e_f->r32.lsw);
	printf("my_f f= 0x%08X%08X ", my_f_f->r32.msw, my_f_f->r32.lsw);
	printf("my_g f= 0x%08X%08X\n", my_g_f->r32.msw, my_g_f->r32.lsw);

#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	printf("bb_b_f= 0x%016llX %016llX ", ((uint64_t)(bb_b_f >> 64)) , ((uint64_t)(bb_b_f & 0xFFFFFFFFFFFFFFFFULL)));
	printf("ff_f_f= 0x%016llX %016llX\n", ((uint64_t)(ff_f_f >> 64)) , ((uint64_t)(ff_f_f & 0xFFFFFFFFFFFFFFFFULL)));
	printf("gg_g_f= 0x%016llX %016llX ", ((uint64_t)(gg_g_f >> 64)) , ((uint64_t)(gg_g_f & 0xFFFFFFFFFFFFFFFFULL)));
	printf("hh_h_f= 0x%016llX %016llX\n", ((uint64_t)(hh_h_f >> 64)) , ((uint64_t)(hh_h_f & 0xFFFFFFFFFFFFFFFFULL)));

	printf("aa    = 0x%016llX %016llX ", ((uint64_t)(aa >> 64)) , ((uint64_t)(aa & 0xFFFFFFFFFFFFFFFFULL)));
	printf("bb    = 0x%016llX %016llX ", ((uint64_t)(bb >> 64)) , ((uint64_t)(bb & 0xFFFFFFFFFFFFFFFFULL)));
	printf("bb2   = 0x%016llX %016llX\n", ((uint64_t)(bb2 >> 64)) , ((uint64_t)(bb2 & 0xFFFFFFFFFFFFFFFFULL)));
#endif
	
	printf("my_aa = 0x%08X%08X %08X%08X ", my_aa->r32.msw, my_aa->r32.s3w, my_aa->r32.s2w, my_aa->r32.lsw);
	printf("my_bb = 0x%08X%08X %08X%08X ", my_bb->r32.msw, my_bb->r32.s3w, my_bb->r32.s2w, my_bb->r32.lsw);
	printf("my_bb2= 0x%08X%08X %08X%08X\n", my_bb2->r32.msw, my_bb2->r32.s3w, my_bb2->r32.s2w, my_bb2->r32.lsw);
	
#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	printf("cc    = 0x%016llX %016llX ", ((uint64_t)(cc >> 64)) , ((uint64_t)(cc & 0xFFFFFFFFFFFFFFFFULL)));
	printf("dd    = 0x%016llX %016llX ", ((uint64_t)(dd >> 64)) , ((uint64_t)(dd & 0xFFFFFFFFFFFFFFFFULL)));
	printf("ee    = 0x%016llX %016llX\n", ((uint64_t)(ee >> 64)) , ((uint64_t)(ee & 0xFFFFFFFFFFFFFFFFULL)));
#endif

	printf("my_cc = 0x%08X%08X %08X%08X ", my_cc->r32.msw, my_cc->r32.s3w, my_cc->r32.s2w, my_cc->r32.lsw);
	printf("my_dd = 0x%08X%08X %08X%08X ", my_dd->r32.msw, my_dd->r32.s3w, my_dd->r32.s2w, my_dd->r32.lsw);
	printf("my_ee = 0x%08X%08X %08X%08X\n", my_ee->r32.msw, my_ee->r32.s3w, my_ee->r32.s2w, my_ee->r32.lsw);

#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	printf("ff    = 0x%016llX %016llX ", ((uint64_t)(ff >> 64)) , ((uint64_t)(ff & 0xFFFFFFFFFFFFFFFFULL)));
	printf("gg    = 0x%016llX %016llX\n", ((uint64_t)(gg >> 64)) , ((uint64_t)(gg & 0xFFFFFFFFFFFFFFFFULL)));
#endif

	printf("my_ff = 0x%08X%08X %08X%08X ", my_ff->r32.msw, my_ff->r32.s3w, my_ff->r32.s2w, my_ff->r32.lsw);
	printf("my_gg = 0x%08X%08X %08X%08X\n", my_gg->r32.msw, my_gg->r32.s3w, my_gg->r32.s2w, my_gg->r32.lsw);

	printf("my_aa f= 0x%08X%08X %08X%08X ", my_aa_f->r32.msw, my_aa_f->r32.s3w, my_aa_f->r32.s2w, my_aa_f->r32.lsw);
	printf("my_bb f= 0x%08X%08X %08X%08X\n", my_bb_f->r32.msw, my_bb_f->r32.s3w, my_bb_f->r32.s2w, my_bb_f->r32.lsw);
	printf("my_cc f= 0x%08X%08X %08X%08X ", my_cc_f->r32.msw, my_cc_f->r32.s3w, my_cc_f->r32.s2w, my_cc_f->r32.lsw);
	printf("my_dd f= 0x%08X%08X %08X%08X\n", my_dd_f->r32.msw, my_dd_f->r32.s3w, my_dd_f->r32.s2w, my_dd_f->r32.lsw);
	printf("my_ee f= 0x%08X%08X %08X%08X ", my_ee_f->r32.msw, my_ee_f->r32.s3w, my_ee_f->r32.s2w, my_ee_f->r32.lsw);
	printf("my_ff f= 0x%08X%08X %08X%08X\n", my_ff_f->r32.msw, my_ff_f->r32.s3w, my_ff_f->r32.s2w, my_ff_f->r32.lsw);

	printf("my_gg f= 0x%08X%08X %08X%08X ", my_gg_f->r32.msw, my_gg_f->r32.s3w, my_gg_f->r32.s2w, my_gg_f->r32.lsw);
	printf("my_hh f= 0x%08X%08X %08X%08X\n", my_hh_f->r32.msw, my_hh_f->r32.s3w, my_hh_f->r32.s2w, my_hh_f->r32.lsw);

	printf("my_eee_ee f= 0x%016llX %016llX %016llX %016llX\n", my_eee_ee_f->dword[3], my_eee_ee_f->dword[2], my_eee_ee_f->dword[1], my_eee_ee_f->dword[0]);
	printf("my_fff_ff f= 0x%016llX %016llX %016llX %016llX\n", my_fff_ff_f->dword[3], my_fff_ff_f->dword[2], my_fff_ff_f->dword[1], my_fff_ff_f->dword[0]);
	printf("my_ggg_gg f= 0x%016llX %016llX %016llX %016llX\n", my_ggg_gg_f->dword[3], my_ggg_gg_f->dword[2], my_ggg_gg_f->dword[1], my_ggg_gg_f->dword[0]);
	printf("my_hhh_hh f= 0x%016llX %016llX %016llX %016llX\n", my_hhh_hh_f->dword[3], my_hhh_hh_f->dword[2], my_hhh_hh_f->dword[1], my_hhh_hh_f->dword[0]);

#if	defined(__GNUC__) && defined(__SIZEOF_INT128__)
	printf("aa_a    = 0x%016llX %016llX ", ((uint64_t)(aa_a >> 64)) , ((uint64_t)(aa_a & 0xFFFFFFFFFFFFFFFFULL)));
	printf("bb_b    = 0x%016llX %016llX\n", ((uint64_t)(bb_b >> 64)) , ((uint64_t)(bb_b & 0xFFFFFFFFFFFFFFFFULL)));
	
	printf("cc_c    = 0x%016llX %016llX ", ((uint64_t)(cc_c >> 64)) , ((uint64_t)(cc_c & 0xFFFFFFFFFFFFFFFFULL)));
	printf("dd_d    = 0x%016llX %016llX ", ((uint64_t)(dd_d >> 64)) , ((uint64_t)(dd_d & 0xFFFFFFFFFFFFFFFFULL)));
	printf("ee_e    = 0x%016llX %016llX\n", ((uint64_t)(ee_e >> 64)) , ((uint64_t)(ee_e & 0xFFFFFFFFFFFFFFFFULL)));
#endif

	printf("my_aa_a = 0x%08X%08X %08X%08X ", my_aa_a->r32.msw, my_aa_a->r32.s3w, my_aa_a->r32.s2w, my_aa_a->r32.lsw);
	printf("my_bb_b = 0x%08X%08X %08X%08X\n", my_bb_b->r32.msw, my_bb_b->r32.s3w, my_bb_b->r32.s2w, my_bb_b->r32.lsw);

	printf("my_cc_c = 0x%08X%08X %08X%08X ", my_cc_c->r32.msw, my_cc_c->r32.s3w, my_cc_c->r32.s2w, my_cc_c->r32.lsw);
	printf("my_dd_d = 0x%08X%08X %08X%08X ", my_dd_d->r32.msw, my_dd_d->r32.s3w, my_dd_d->r32.s2w, my_dd_d->r32.lsw);
	printf("my_ee_e = 0x%08X%08X %08X%08X\n", my_ee_e->r32.msw, my_ee_e->r32.s3w, my_ee_e->r32.s2w, my_ee_e->r32.lsw);

	printf("my_a_aa_a = 0x%08X%08X ", my_a_aa_a->r32.msw, my_a_aa_a->r32.lsw);
	printf("my_b_bb_b = 0x%08X%08X ", my_b_bb_b->r32.msw, my_b_bb_b->r32.lsw);
	
	printf("my_c_cc_c = 0x%08X%08X ", my_c_cc_c->r32.msw, my_c_cc_c->r32.lsw);
	printf("my_d_dd_d = 0x%08X%08X\n", my_d_dd_d->r32.msw, my_d_dd_d->r32.lsw);

	printf("my_aaa = 0x%016llX %016llX %016llX %016llX\n", my_aaa->dword[3], my_aaa->dword[2], my_aaa->dword[1], my_aaa->dword[0]);
	printf("my_bbb = 0x%016llX %016llX %016llX %016llX\n", my_bbb->dword[3], my_bbb->dword[2], my_bbb->dword[1], my_bbb->dword[0]);
	printf("my_ccc = 0x%016llX %016llX %016llX %016llX\n", my_ccc->dword[3], my_ccc->dword[2], my_ccc->dword[1], my_ccc->dword[0]);
	printf("my_ddd = 0x%016llX %016llX %016llX %016llX\n", my_ddd->dword[3], my_ddd->dword[2], my_ddd->dword[1], my_ddd->dword[0]);
	printf("my_eee = 0x%016llX %016llX %016llX %016llX\n", my_eee->dword[3], my_eee->dword[2], my_eee->dword[1], my_eee->dword[0]);

	printf("my_aaa_aa = 0x%016llX %016llX %016llX %016llX\n", my_aaa_aa->dword[3], my_aaa_aa->dword[2], my_aaa_aa->dword[1], my_aaa_aa->dword[0]);
	printf("my_bbb_bb = 0x%016llX %016llX %016llX %016llX\n", my_bbb_bb->dword[3], my_bbb_bb->dword[2], my_bbb_bb->dword[1], my_bbb_bb->dword[0]);
	printf("my_eee_ee = 0x%016llX %016llX %016llX %016llX\n", my_eee_ee->dword[3], my_eee_ee->dword[2], my_eee_ee->dword[1], my_eee_ee->dword[0]);
	printf("my_fff_ff = 0x%016llX %016llX %016llX %016llX\n", my_fff_ff->dword[3], my_fff_ff->dword[2], my_fff_ff->dword[1], my_fff_ff->dword[0]);
	printf("my_ggg_gg = 0x%016llX %016llX %016llX %016llX\n", my_ggg_gg->dword[3], my_ggg_gg->dword[2], my_ggg_gg->dword[1], my_ggg_gg->dword[0]);

	fclose(urandom);

	return -1;
}
