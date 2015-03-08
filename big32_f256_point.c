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

#define USE_JACOBIAN
#define	USE_JACOBIAN_PRECOMP

void big32_f256_pt_copy(big32_f256pt_t *dest, const big32_f256pt_t *src1)
{
	big32_u256_copy(&(dest->x), &(src1->x));
	big32_u256_copy(&(dest->y), &(src1->y));
}

#ifdef	USE_JACOBIAN
void big32_f256_jpt_from_pt(big32_f256jpt_t *dest, const big32_f256pt_t *src1)
{
	big32_u256_t	one   = { .r32 = { 1, 0, 0, 0, 0, 0, 0, 0 } } ;
	big32_u256_copy(&(dest->x), &(src1->x));
	big32_u256_copy(&(dest->y), &(src1->y));
	big32_u256_copy(&(dest->z), &one);
}

void big32_f256_pt_from_jpt(big32_f256pt_t *dest, const big32_f256jpt_t *src1)
{
	big32_u256_t	t0, t1 ;
	big32_u256_t	z2inv ;
	big32_u256_t	z3inv ;
	
	big32_u256_copy(&t0, &(src1->z));
	big32_f256_mul256(&t1, &t0, &(src1->z));
	big32_f256_mul256(&t0, &t1, &(src1->z));
	big32_f256_inv(&z2inv, &t1);
	big32_f256_inv(&z3inv, &t0);
	big32_f256_mul256(&(dest->x), &(src1->x), &z2inv);
	big32_f256_mul256(&(dest->y), &(src1->y), &z3inv);
}

void big32_f256_jpt_copy(big32_f256jpt_t *dest, const big32_f256jpt_t *src1)
{
	big32_u256_copy(&(dest->x), &(src1->x));
	big32_u256_copy(&(dest->y), &(src1->y));
	big32_u256_copy(&(dest->z), &(src1->z));
}
#endif

#ifdef	USE_JACOBIAN
/* see : http://www.hyperelliptic.org/EFD/g1p/auto-shortw-jacobian.html#doubling-dbl-2007-bl 

XX = X1^2
YY = Y1^2
YYYY = YY^2
ZZ = Z1^2
t0 = X1+YY
t1 = t0^2
t2 = t1-XX
t3 = t2-YYYY
S = 2*t3
t4 = ZZ^2
t5 = a*t4
t6 = 3*XX
M = t6+t5
t7 = M^2
t8 = 2*S
T = t7-t8
X3 = T
t9 = S-T
t10 = 8*YYYY
t11 = M*t9
Y3 = t11-t10
t12 = Y1+Z1
t13 = t12^2
t14 = t13-YY
Z3 = t14-ZZ

*/

int big32_f256_jpt_double(big32_f256jpt_t *dest, big32_f256jpt_t *src1)
{
	//big32_u256_t	xx, yy, yyyy, zz, s, m, t;
	big32_u256_t	xx, yy, yyyy, zz, s, m;
	//big32_u256_t	t0, t1, t2, t3, t4, t5, t6 ,t7, t8, t9;
	big32_u256_t	t0, t1, t2, t3, t7, t8, t9;
	big32_u256_t	t10, t11, t12, t13, t14;
	big32_u256_t	eight = { .r32 = { 8, 0, 0, 0, 0, 0, 0, 0 } } ;

	/* XX = X1^2 */
	big32_f256_mul256(&xx, &(src1->x), &(src1->x));
	
	/* YY = Y1^2 */
	big32_f256_mul256(&yy, &(src1->y), &(src1->y));
	
	/* YYYY = YY^2 */
	big32_f256_mul256(&yyyy, &yy, &yy);
	
	/* ZZ = Z1^2 */
	big32_f256_mul256(&zz, &(src1->z), &(src1->z));
	
	/* t0 = X1+YY */
	big32_f256_add(&t0, &(src1->x), &yy);
	
	/* t1 = t0^2 */
	big32_f256_mul256(&t1, &t0, &t0);
	
	/* t2 = t1-XX */
	big32_f256_sub(&t2, &t1, &xx);
	
	/* t3 = t2-YYYY */
	big32_f256_sub(&t3, &t2, &yyyy);
	
	/* S = 2*t3 */
	big32_f256_add(&s, &t3, &t3);
	
	/* t4 = ZZ^2 */
	/* big32_f256_mul256(&t4, &zz, &zz); */
	
	/* t5 = a*t4 */
	/*big32_f256_mul256(&t5, (a), &t4); ... but a == 0 for secp256k1 */
	
	/* t6 = 3*XX */
	/* M = t6+t5 */
	/* big32_f256_add(&m, &t5, &t6); but t5 = 0, so M == t6 == 3*XX */
	big32_f256_add(&m, &xx, &xx);
	big32_f256_pluseq(&m, &xx);
	
	/* t7 = M^2 */
	big32_f256_mul256(&t7, &m, &m);
	
	/* t8 = 2*S */
	big32_f256_add(&t8, &s, &s);
	
	/* T = t7-t8 */
	/* X3 = T */
	big32_f256_sub(&(dest->x), &t7, &t8);
	
	/* t9 = S-T */
	big32_f256_sub(&t9, &s, &(dest->x));
	
	/* t10 = 8*YYYY */
	big32_f256_mul256(&t10, &eight, &yyyy);
	
	/* t11 = M*t9 */
	big32_f256_mul256(&t11, &m, &t9);
	
	/* Y3 = t11-t10 */
	big32_f256_sub(&(dest->y), &t11, &t10);
	
	/* t12 = Y1+Z1 */
	big32_f256_add(&t12, &(src1->y), &(src1->z));
	
	/* t13 = t12^2 */
	big32_u256_copy(&t0, &t12);
	big32_f256_mul256(&t13, &t0, &t12);
	
	/* t14 = t13-YY */
	big32_f256_sub(&t14, &t13, &yy);
	
	/* Z3 = t14-ZZ */
	big32_f256_sub(&(dest->z), &t14, &zz);
	
	return 0;
}
#else
int big32_f256_pt_double(big32_f256pt_t *dest, big32_f256pt_t *src1)
{
	big32_u256_t	three = { .r32 = { 3, 0, 0, 0, 0, 0, 0, 0 } } ;
	big32_u256_t	two   = { .r32 = { 2, 0, 0, 0, 0, 0, 0, 0 } } ;
	
	big32_u256_t		tmp1, tmp2, tmp3;
	big32_u256_t		s;
	
	// s = 3px^2 / ( 2py ) 
	// numerator would include +a, but a=0 for secp256k1
	big32_u256_copy(&tmp1, &(src1->x));
	big32_f256_mul256(&tmp2, &tmp1, &(src1->x));
	big32_f256_mul256(&tmp1, &three, &tmp2);
	big32_f256_mul256(&tmp3, &two, &(src1->y));
	big32_f256_inv(&tmp2,&tmp3);
	big32_f256_mul256(&s, &tmp1, &tmp2);
	
	// rx = s^2 - 2px
	big32_u256_copy(&tmp1, &s);
	big32_f256_mul256(&tmp2, &tmp1, &s);
	big32_f256_mul256(&tmp1, &two, &(src1->x));
	big32_f256_sub(&(dest->x), &tmp2, &tmp1);
	
	// ry = s ( px - rx ) - py
	big32_f256_sub(&tmp3, &(src1->x), &(dest->x));
	big32_f256_mul256(&tmp2, &s, &tmp3);
	big32_f256_sub(&(dest->y), &tmp2, &(src1->y)) ;

	return 0;
}
#endif

#ifdef	USE_JACOBIAN
/* see : http://www.hyperelliptic.org/EFD/g1p/auto-shortw-jacobian-0.html#addition-add-2007-bl

Z1Z1 = Z1^2
Z2Z2 = Z2^2
U1 = X1*Z2Z2
U2 = X2*Z1Z1
t0 = Z2*Z2Z2
S1 = Y1*t0
t1 = Z1*Z1Z1
S2 = Y2*t1
H = U2-U1
t2 = 2*H
I = t2^2
J = H*I
t3 = S2-S1
r = 2*t3
V = U1*I
t4 = r^2
t5 = 2*V
t6 = t4-J
X3 = t6-t5
t7 = V-X3
t8 = S1*J
t9 = 2*t8
t10 = r*t7
Y3 = t10-t9
t11 = Z1+Z2
t12 = t11^2
t13 = t12-Z1Z1
t14 = t13-Z2Z2
Z3 = t14*H
*/

int big32_f256_jpt_add(big32_f256jpt_t *dest, big32_f256jpt_t *src1, big32_f256jpt_t *src2)
{
	big32_u256_t	z1z1, z2z2, u1, u2, s1, s2, h, i, j, r, v;
	big32_u256_t	t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14;
	
	/* short circuit for infinty point */
	if (big32_u256_is_zero(&(src1->z))) {
		big32_f256_jpt_copy(dest, src2); 
		return 0 ; } ;

	/* Z1Z1 = Z1^2 */
	big32_f256_mul256(&z1z1, &(src1->z), &(src1->z));
	
	/* Z2Z2 = Z2^2 */
	big32_f256_mul256(&z2z2, &(src2->z), &(src2->z));
	
	/* U1 = X1*Z2Z2 */
	big32_f256_mul256(&u1, &(src1->x), &z2z2);
	
	/* U2 = X2*Z1Z1 */
	big32_f256_mul256(&u2, &(src2->x), &z1z1);
	
	/* t0 = Z2*Z2Z2 */
	big32_f256_mul256(&t0, &(src2->z), &z2z2);

	/* S1 = Y1*t0 */
	big32_f256_mul256(&s1, &(src1->y), &t0);

	/* t1 = Z1*Z1Z1 */
	big32_f256_mul256(&t1, &(src1->z), &z1z1);

	/* S2 = Y2*t1 */
	big32_f256_mul256(&s2, &(src2->y), &t1);

	/* H = U2-U1 */
	big32_f256_sub(&h, &u2, &u1);

	/* t2 = 2*H */
	big32_u256_copy(&t2, &h);
	big32_f256_pluseq(&t2, &h);

	/* I = t2^2 */
	big32_u256_copy(&t0, &t2);
	big32_f256_mul256(&i, &t0, &t2);

	/* J = H*I */
	big32_f256_mul256(&j, &h, &i);

	/* t3 = S2-S1 */
	big32_f256_sub(&t3, &s2, &s1);

	/* r = 2*t3 */
	big32_u256_copy(&r, &t3);
	big32_f256_pluseq(&r, &t3);

	/* V = U1*I */
	big32_f256_mul256(&v, &u1, &i);

	/* t4 = r^2 */
	big32_u256_copy(&t0, &r);
	big32_f256_mul256(&t4, &t0, &r);

	/* t5 = 2*V */
	big32_u256_copy(&t5, &v);
	big32_f256_pluseq(&t5, &v);

	/* t6 = t4-J */
	big32_f256_sub(&t6, &t4, &j);

	/* X3 = t6-t5 */
	big32_f256_sub(&(dest->x), &t6, &t5);

	/* t7 = V-X3 */
	big32_f256_sub(&t7, &v, &(dest->x));

	/* t8 = S1*J */
	big32_f256_mul256(&t8, &s1, &j);

	/* t9 = 2*t8 */
	big32_u256_copy(&t9, &t8);
	big32_f256_pluseq(&t9, &t8);

	/* t10 = r*t7 */
	big32_f256_mul256(&t10, &r, &t7);

	/* Y3 = t10-t9 */
	big32_f256_sub(&(dest->y), &t10, &t9);

	/* t11 = Z1+Z2 */
	big32_f256_add(&t11, &(src1->z), &(src2->z));

	/* t12 = t11^2 */
	big32_u256_copy(&t0, &t11);
	big32_f256_mul256(&t12, &t0, &t11);

	/* t13 = t12-Z1Z1 */
	big32_f256_sub(&t13, &t12, &z1z1);

	/* t14 = t13-Z2Z2 */
	big32_f256_sub(&t14, &t13, &z2z2);

	/* Z3 = t14*H */
	big32_f256_mul256(&(dest->z), &t14, &h);
	
	return 0;
}
#else
int big32_f256_pt_add(big32_f256pt_t *dest, big32_f256pt_t *src1, big32_f256pt_t *src2)
{
	big32_u256_t		tmp1, tmp2, tmp3;
	big32_u256_t		s;
	
	if (big32_u256_is_zero(&(src1->x)) && big32_u256_is_zero(&(src1->y))) {
		big32_f256_pt_copy(dest, src2); 
		return 0 ; } ;

	// calculating R = P + Q
	
	// s = ( py - qy ) / ( px - qx )
	big32_f256_sub(&tmp1, &(src1->y), &(src2->y));
	big32_f256_sub(&tmp2, &(src1->x), &(src2->x));
	
	// if P = Q, handle as special case, if px - qx = 0 cannot invert
	if (big32_u256_is_zero(&tmp2)) {
		if (big32_u256_is_zero(&tmp1)) {
			// src1 == src2 
			return big32_f256_pt_double(dest, src1); }
		else {
			// point at infinty? 
			//printf("Error, point divide by zero?\n");
			return -1; } ; } ;
	
	// division is defined by multiplication by inverse
	big32_f256_inv(&tmp3, &tmp2);
	big32_f256_mul256(&s, &tmp1, &tmp3);
	
	// rx = s^2 - px - qx
	big32_u256_copy(&tmp1, &s);
	big32_f256_mul256(&tmp3, &s, &tmp1);
	big32_f256_sub(&tmp2, &tmp3, &(src1->x));
	big32_f256_sub(&(dest->x), &tmp2, &(src2->x));
	
	// ry = s * ( px - rx ) - py
	big32_f256_sub(&tmp3, &(src1->x), &(dest->x));
	big32_f256_mul256(&tmp2, &s, &tmp3);
	big32_f256_sub(&(dest->y), &tmp2, &(src1->y)) ;

	return 0;
}
#endif

#ifdef	USE_JACOBIAN
#ifdef	USE_JACOBIAN_PRECOMP

#define JACOBIAN_PRECOMP_BITS	(1)
#define	JACOBIAN_PRECOMP_TABLE_MINOR	(1<<(JACOBIAN_PRECOMP_BITS-1))
#define	JACOBIAN_PRECOMP_TABLE_MAJOR	(256/JACOBIAN_PRECOMP_TABLE_MINOR)
#define	JACOBIAN_PRECOMP_MASK	((1<<JACOBIAN_PRECOMP_BITS)-1)
#define JACOBIAN_PROCOMP_TABLE_LENGTH	(JACOBIAN_PRECOMP_TABLE_MAJOR*JACOBIAN_PRECOMP_TABLE_MINOR)

#if	defined(__epiphany__)
static big32_f256jpt_t precomp[JACOBIAN_PROCOMP_TABLE_LENGTH] __attribute__((section(".shared_dram"))) __attribute__((aligned(8))) ;
#else
static big32_f256jpt_t precomp[JACOBIAN_PROCOMP_TABLE_LENGTH] ;
#endif

void big32_f256_seed_precomp_jpt(const big32_f256jpt_t *src1)
{
	int32_t	count;
	big32_f256jpt_t	a;
	
	/* no need to re-init for same value of src1 */
	if (big32_u256_is_equal(&(precomp[0].x), &(src1->x)) &&
	    big32_u256_is_equal(&(precomp[0].y), &(src1->y)) &&
	    big32_u256_is_equal(&(precomp[0].z), &(src1->z))) { return ; } ;
		
	big32_f256_jpt_copy(&a, src1);
	for (count = 0 ; count < 255 ; count++)
	{
		big32_f256_jpt_copy(&(precomp[count]), &a);
		big32_f256_jpt_double(&a, &(precomp[count]));
	}
	big32_f256_jpt_copy(&(precomp[255]), &a);
}


void big32_f256_seed_precomp_pt(const big32_f256pt_t *src1)
{
	big32_f256jpt_t	a;
	big32_f256_jpt_from_pt(&a, src1);
	big32_f256_seed_precomp_jpt(&a);
}
#endif

int big32_f256_scalar_pt_mul256(big32_f256pt_t *dest, const big32_u256_t *src1, const big32_f256pt_t *src2)
{
	big32_f256jpt_t	s2;
	big32_f256jpt_t	d;
#ifndef	USE_JACOBIAN_PRECOMP
	big32_f256jpt_t	N;
#endif
	//big32_f256pt_t	Np;
	//big32_f256pt_t	Tp;
	big32_f256jpt_t	T;
	big32_f256jpt_t	Z = { { .r32 = { 0, 0, 0, 0, 0, 0, 0, 0 }}, 
			      { .r32 = { 1, 0, 0, 0, 0, 0, 0, 0 }}, 
			      { .r32 = { 0, 0, 0, 0, 0, 0, 0, 0 }}} ;
	
	int count;
	
	big32_f256_jpt_from_pt(&s2, src2);
#ifdef	USE_JACOBIAN_PRECOMP
	big32_f256_seed_precomp_jpt(&s2);
#else
	big32_f256_jpt_copy(&N, &s2);
#endif
	big32_f256_jpt_copy(&d, &Z);
	for ( count = 0 ; count < 256 ; count++ ) {
		if (big32_u256_bitcheck(src1, count)) {
#ifdef	USE_JACOBIAN_PRECOMP
			big32_f256_jpt_add(&T, &d, &(precomp[count]));
#else
			big32_f256_jpt_add(&T, &d, &N);
#endif
			big32_f256_jpt_copy(&d, &T); } ;
	
		//big32_f256_pt_from_jpt(&Tp, &d);
		//big32_f256_pt_from_jpt(&Np, &N);
		//printf("count = %d\n",count);
		//big32_u256_print("Nx:", &(Np.x)); printf(" ");
		//big32_u256_print("Ny:", &(Np.y)); printf("\n");
		//big32_u256_print("Tx:", &(Tp.x)); printf(" ");
		//big32_u256_print("Ty:", &(Tp.y)); printf("\n");

#ifdef	USE_JACOBIAN_PRECOMP
		}
#else
		big32_f256_jpt_double(&T, &N);
		big32_f256_jpt_copy(&N, &T); }
#endif
	
	big32_f256_pt_from_jpt(dest, &d);
	return 0;
}
#else
int big32_f256_scalar_pt_mul256(big32_f256pt_t *dest, const big32_u256_t *src1, const big32_f256pt_t *src2)
{
	big32_f256pt_t	N;
	big32_f256pt_t	T;
	big32_f256pt_t	Z = { { .r32 = { 0, 0, 0, 0, 0, 0, 0, 0 }}, 
			      { .r32 = { 0, 0, 0, 0, 0, 0, 0, 0 }}} ;
	
	int count;
	
	big32_f256_pt_copy(&N, src2);
	big32_f256_pt_copy(dest, &Z);
	for ( count = 0 ; count < 256 ; count++ ) {
		if (big32_u256_bitcheck(src1, count)) {
			big32_f256_pt_add(&T, dest, &N);
			big32_f256_pt_copy(dest, &T); } ;
	
		//printf("count = %d\n",count);
		//big32_u256_print("Nx:", &(N.x)); printf(" ");
		//big32_u256_print("Ny:", &(N.y)); printf("\n");
		//big32_u256_print("Tx:", &(dest->x)); printf(" ");
		//big32_u256_print("Ty:", &(dest->y)); printf("\n");

		big32_f256_pt_double(&T, &N);
		big32_f256_pt_copy(&N, &T); }
	
	return 0;
}
#endif
