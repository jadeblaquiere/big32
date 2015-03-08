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


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef uint16_t	div_lut_t;

#define	NUM_BITS_PER_SIDE	(5)
#define NUM_BITS	(2 * NUM_BITS_PER_SIDE)
#define	LUT_SIDE	(1 << NUM_BITS_PER_SIDE)
#define	LUT_SZ	(1 << NUM_BITS)

#define	BITS_LUT_TYPE	((sizeof(div_lut_t) * 8)

#define	SHIFT_DIVIDEND	((int)(BITS_LUT_TYPE-1) - NUM_BITS_PER_SIDE))

//#define	DEBUG
//#define	VERBOSE

static	div_lut_t	div_lut[LUT_SZ];

void initialize_div_lut()
{
	int count_divd;
	int count_divr;
	
	uint32_t	dividend;
	uint32_t	divisor;
	uint32_t	quotient;
	
	printf("LUT size (%dx%d) = %lu ( 0x%08lX ) bytes\n", NUM_BITS_PER_SIDE, NUM_BITS_PER_SIDE, sizeof(div_lut), sizeof(div_lut));
	
	/* build LUT */
	for (count_divd = 0 ; count_divd < LUT_SIDE ; count_divd++) {
	for (count_divr = 0 ; count_divr < LUT_SIDE ; count_divr++) {
	
		dividend = ( LUT_SIDE + count_divd ) << SHIFT_DIVIDEND ;
		
		divisor = LUT_SIDE + count_divr ;
		
		quotient = dividend / divisor ;
		
		div_lut[count_divr + (LUT_SIDE * count_divd)] = quotient;
		
#ifdef	DEBUG
		printf("LUT(0x%08X,0x%08X) = 0x%08X\n", dividend, divisor, quotient);
#endif
	}} ;
}

void print_div_lut()
{
	int i;

	if (sizeof(div_lut_t) == 1) {
		printf("uint8_t div_lut_%d_%d[",NUM_BITS_PER_SIDE,8);
		} else if (sizeof(div_lut_t) == 2) {
		printf("uint16_t div_lut_%d_%d[",NUM_BITS_PER_SIDE,16);
		} else if (sizeof(div_lut_t) == 4) {
		printf("uint32_t div_lut_%d_%d[",NUM_BITS_PER_SIDE,32);
		} else {
		fprintf(stderr,"LUT type unknown, exiting.\n");
		exit(1);
		} ;

	printf("%d] = { ",LUT_SZ);
	
	for (i = 0 ; i < LUT_SZ ; i++ ) {
		if ((i & 0x7) == 0) { printf("\n	"); } ;
		
		if (sizeof(div_lut_t) == 1) {
			printf("0x%02X", div_lut[i]);
			} else if (sizeof(div_lut_t) == 2) {
			printf("0x%04X", div_lut[i]);
			} else if (sizeof(div_lut_t) == 4) {
			printf("0x%08X", div_lut[i]);
			} ;
		
		if (i != (LUT_SZ-1)) { printf(", "); } ; } ;
		
	printf("}; \n");

}

int count_leading_zeros_128(const __uint128_t *src)
{
	int i = 127;
	while ((i >= 0) && ((((__uint128_t)1<<i) & *src) == 0)) {
		i--;
		} ;
	
	return ( 127 - i ) ;
}

int lut_divide(__uint128_t *quotient, __uint128_t *remainder, const __uint128_t *dividend, const __uint128_t *divisor)
{
	uint32_t	lut_divd;
	uint32_t	lut_divr;
	int32_t	lut_shift;

	int32_t	zeros_divd;
	int32_t	zeros_divr;
	int32_t	zeros_net;
	
	__uint128_t	guess_quot;
	__uint128_t	guess_product;
	__uint128_t	guess_remainder;
	__uint128_t	difference;

#ifdef	DEBUG
	printf("dividend  = 0x%016llX %016llX ", ((uint64_t)(*dividend >> 64)) , ((uint64_t)(*dividend & 0xFFFFFFFFFFFFFFFFULL)));
	printf("divisor   = 0x%016llX %016llX\n", ((uint64_t)(*divisor >> 64)) , ((uint64_t)(*divisor & 0xFFFFFFFFFFFFFFFFULL)));
#endif
	
	/* divide by zero, return error */
	if (*divisor == 0) { return -1 ; } ;
	
	/* divide of zero, return 0,0 */
	if (*dividend == 0) { *quotient = 0 ; *remainder = 0 ; return 0 ; } ;

	/* count leading zeros */
	zeros_divd = count_leading_zeros_128(dividend);
	zeros_divr = count_leading_zeros_128(divisor);
	zeros_net = zeros_divr - zeros_divd ;

#ifdef	DEBUG
	printf("zeros(dividend) = %d ",zeros_divd);
	printf("zeros(divisor)  = %d ",zeros_divr);
	printf("zeros(net)      = %d\n",zeros_net);
#endif	
	/* shift msb to position of 1 << NUM_BITS_PER_SIDE */
	lut_shift = (127-NUM_BITS_PER_SIDE) - zeros_divd;
	if (lut_shift >= 0) {
		lut_divd = *dividend >> lut_shift ; } else {
		lut_divd = *dividend << (-lut_shift) ; } ;
		
	lut_shift = (127-NUM_BITS_PER_SIDE) - zeros_divr;
	if (lut_shift >= 0) {
		lut_divr = *divisor >> lut_shift ; } else {
		lut_divr = *divisor << (-lut_shift) ; } ;
	//lut_divr = *divisor >> ((127-NUM_BITS_PER_SIDE) - zeros_divr);
	
	/* mask lsb*/
	lut_divd &= ((1 << NUM_BITS_PER_SIDE) - 1);
	lut_divr &= ((1 << NUM_BITS_PER_SIDE) - 1);
	lut_shift = zeros_net - SHIFT_DIVIDEND ;

#ifdef	DEBUG
	printf("lut(dividend)   = 0x%02X ",lut_divd);
	printf("lut(divisor)    = 0x%02X ",lut_divr);
	printf("lutval          = 0x%08X ",div_lut[(LUT_SIDE * lut_divd) + lut_divr]);
	printf("shift           = %d\n",(zeros_net - SHIFT_DIVIDEND));
#endif
	
	if (lut_shift >= 0) {
		guess_quot = ( ((__uint128_t)div_lut[(LUT_SIDE * lut_divd) + lut_divr]) << lut_shift) ; } else {
		guess_quot = ( ((__uint128_t)div_lut[(LUT_SIDE * lut_divd) + lut_divr]) >> (-lut_shift)) ; }

	guess_product = guess_quot * (*divisor) ;

#ifdef	DEBUG
	printf("guess_quot= 0x%016llX %016llX ", ((uint64_t)(guess_quot >> 64)) , ((uint64_t)(guess_quot & 0xFFFFFFFFFFFFFFFFULL)));
	printf("guess_prod= 0x%016llX %016llX ", ((uint64_t)(guess_product >> 64)) , ((uint64_t)(guess_product & 0xFFFFFFFFFFFFFFFFULL)));
	printf("difference= 0x%016llX %016llX\n", ((uint64_t)((guess_product - *dividend) >> 64)) , ((uint64_t)((guess_product - *dividend) & 0xFFFFFFFFFFFFFFFFULL)));
#endif

	/* ceck for zeros_divd and MSB = 0x0? is to detect overflow */ 
	if ((guess_product > *dividend) || ((zeros_divd == 0) &&
		((guess_product & (((__uint128_t)0xF) << 124)) == 0))){
			__uint128_t next_quotient;
			__uint128_t next_remainder;
			int recurse;
			
			difference = guess_product - *dividend ;
			if ( difference < *divisor ) {
				*quotient = guess_quot - 1 ;
				*remainder = *divisor - difference ;
#ifdef	DEBUG
				printf(" a ");
				printf("quot= 0x%016llX %016llX ",
					((uint64_t)(*quotient >> 64)) ,
					((uint64_t)(*quotient &
					0xFFFFFFFFFFFFFFFFULL)));
				printf("rmdr= 0x%016llX %016llX\n",
					((uint64_t)(*remainder >> 64)) ,
					((uint64_t)(*remainder &
					0xFFFFFFFFFFFFFFFFULL)));
#endif
				return 1 ; } ;

			/* recurse */
#ifdef	DEBUG
			printf("  b  ");
#endif
			recurse = lut_divide (&next_quotient, &next_remainder, &difference, divisor);
			if ( next_remainder == 0) {
			*quotient = guess_quot - next_quotient;
			*remainder = next_remainder ;
			} else {
			*quotient = guess_quot - (next_quotient + 1);
			*remainder = *divisor - next_remainder ;
			}
#ifdef	DEBUG
	printf("quot= 0x%016llX %016llX ", ((uint64_t)(*quotient >> 64)) , ((uint64_t)(*quotient & 0xFFFFFFFFFFFFFFFFULL)));
	printf("rmdr= 0x%016llX %016llX\n", ((uint64_t)(*remainder >> 64)) , ((uint64_t)(*remainder & 0xFFFFFFFFFFFFFFFFULL)));
#endif
			return recurse + 1;
		} else {
			__uint128_t next_quotient;
			__uint128_t next_remainder;
			int recurse;
			
			difference = *dividend - guess_product ;
			if ( difference < *divisor ) {
				*quotient = guess_quot ;
				*remainder = difference ;
#ifdef	DEBUG
				printf("  c  ");
	printf("quot= 0x%016llX %016llX ", ((uint64_t)(*quotient >> 64)) , ((uint64_t)(*quotient & 0xFFFFFFFFFFFFFFFFULL)));
	printf("rmdr= 0x%016llX %016llX\n", ((uint64_t)(*remainder >> 64)) , ((uint64_t)(*remainder & 0xFFFFFFFFFFFFFFFFULL)));
#endif
				return 1 ; } 

			/* recurse */
#ifdef	DEBUG
			printf("  d  ");
#endif
			recurse = lut_divide (&next_quotient, &next_remainder, &difference, divisor);
			*quotient = guess_quot + next_quotient ;
			*remainder = next_remainder ;
#ifdef	DEBUG
	printf("quot= 0x%016llX %016llX ", ((uint64_t)(*quotient >> 64)) , ((uint64_t)(*quotient & 0xFFFFFFFFFFFFFFFFULL)));
	printf("rmdr= 0x%016llX %016llX\n", ((uint64_t)(*remainder >> 64)) , ((uint64_t)(*remainder & 0xFFFFFFFFFFFFFFFFULL)));
#endif
			return recurse + 1;
		} ;
} 

int main(int argc, char **argv)
{
	int i;
	int recurse ;
	int recurse_accum;
	float avg_recurse;

	uint32_t	test_shift;
	
	__uint128_t	test_divd;
	__uint128_t	test_divr;
	__uint128_t	test_quot;
	__uint128_t	test_rmdr;
	
	__uint128_t	guess_quot;
	__uint128_t	guess_rmdr;
	
	FILE	*urandom;
	
	initialize_div_lut();
	
	print_div_lut();
	
	urandom = fopen("/dev/urandom","rb");
	if (urandom == NULL) {
		fprintf(stderr,"Error opening /dev/urandom, exiting\n") ;
		exit(1); } ;
		
	recurse_accum = 0;
	for (i = 0 ; i < 100000 ; i++ ) {

		if (fread(&test_divd, sizeof(test_divd), 1, urandom) != 1) {
			fprintf(stderr,"Error reading dividend\n"); exit (2); } ;
		//test_divd >>= 1;
		test_divr = 0;
		while (test_divr == 0)
		{
			if (fread(&test_divr, sizeof(test_divr), 1, urandom) != 1) {
				fprintf(stderr,"Error reading divisor\n"); exit (2); } ;

			if (fread(&test_shift, sizeof(test_shift), 1, urandom) != 1) {
				fprintf(stderr,"Error reading shift\n"); exit (2); } ;

			while (test_divr > test_divd)
				test_divr >>= 1 ;

			test_shift &= 0x7F;
			test_divr >>= test_shift ; } ;

#ifdef	VERBOSE
		printf("dividend  = 0x%016llX %016llX ", ((uint64_t)(test_divd >> 64)) , ((uint64_t)(test_divd & 0xFFFFFFFFFFFFFFFFULL)));
		printf("divisor   = 0x%016llX %016llX\n", ((uint64_t)(test_divr >> 64)) , ((uint64_t)(test_divr & 0xFFFFFFFFFFFFFFFFULL)));
#endif

		test_quot = test_divd / test_divr ;
		test_rmdr = test_divd % test_divr ;

		if ((recurse = lut_divide(&guess_quot, &guess_rmdr, &test_divd, &test_divr)) < 0) {
			fprintf(stderr,"Error on divide (by zero?)\n"); exit (-1) ; } ;

#ifdef	VERBOSE
		printf("quotient  = 0x%016llX %016llX ", ((uint64_t)(test_quot >> 64)) , ((uint64_t)(test_quot & 0xFFFFFFFFFFFFFFFFULL)));
		printf("remainder = 0x%016llX %016llX\n", ((uint64_t)(test_rmdr >> 64)) , ((uint64_t)(test_rmdr & 0xFFFFFFFFFFFFFFFFULL)));

		printf("guess_quo = 0x%016llX %016llX ", ((uint64_t)(guess_quot >> 64)) , ((uint64_t)(guess_quot & 0xFFFFFFFFFFFFFFFFULL)));
		printf("guess_rem = 0x%016llX %016llX\n", ((uint64_t)(guess_rmdr >> 64)) , ((uint64_t)(guess_rmdr & 0xFFFFFFFFFFFFFFFFULL)));
		printf("depth of recurse = %d\n",recurse);
#endif
		
		if (test_quot != guess_quot) {
			fprintf(stderr,"quotient mismatch\n") ; exit(1) ; } ;
		if (test_rmdr != guess_rmdr) {
			fprintf(stderr,"remainder mismatch\n") ; exit(1) ; } ;
		
		recurse_accum += recurse;
	
	} ;
	avg_recurse =  ((float)recurse_accum) / ((float)100000) ;
	printf("average recurse depth = %f\n",avg_recurse);
}

