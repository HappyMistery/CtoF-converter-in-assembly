/*----------------------------------------------------------------
|   Testing temperature data processing;
| ----------------------------------------------------------------
|	santiago.romani@urv.cat
|	pere.millan@urv.cat
|	(April 2021, March 2022)
| ----------------------------------------------------------------*/

#include "Q12.h"				/* external declarations of types, defines and
								   macro for dealing with Q12 numbers */
#include "avgmaxmintemp.h"		/* mmres: return type from avgmaxmin routines */

#define NUM_TEST_ROWS	7

Q12 test_data[NUM_TEST_ROWS][12] = {
	{MAKE_Q12(13.4), MAKE_Q12(13.4), MAKE_Q12(20.0), MAKE_Q12(13.4),	// several replicated min and max
	 MAKE_Q12(20.0), MAKE_Q12(20.0), MAKE_Q12(25.9), MAKE_Q12(25.9),
	 MAKE_Q12(20.0), MAKE_Q12(20.0), MAKE_Q12(20.0), MAKE_Q12(25.9)},
	{MAKE_Q12(-2.2), MAKE_Q12(-3.5), MAKE_Q12(-5.8), MAKE_Q12(-7.5),	// all negatives
	 MAKE_Q12(-11.5), MAKE_Q12(-15.4), MAKE_Q12(-18.8), MAKE_Q12(-18.5),
	 MAKE_Q12(-14.9), MAKE_Q12(-10.3), MAKE_Q12(-5.7), MAKE_Q12(-3.0)},
	{MAKE_Q12(0.1), MAKE_Q12(0.3), MAKE_Q12(0.7), MAKE_Q12(0.8),		// all values around 0º Celsius
	 MAKE_Q12(0.8), MAKE_Q12(-0.9), MAKE_Q12(-0.7), MAKE_Q12(0.5),
	 MAKE_Q12(0.0), MAKE_Q12(0.7), MAKE_Q12(0.5), MAKE_Q12(-0.9)},
	 
	{MAKE_Q12(54.7), MAKE_Q12(30.0), MAKE_Q12(64.2), MAKE_Q12(0.5),		// TEST EXTRA 1
	 MAKE_Q12(12.0), MAKE_Q12(99.9), MAKE_Q12(54.8), MAKE_Q12(27.4),
	 MAKE_Q12(16.2), MAKE_Q12(16.3), MAKE_Q12(0.4), MAKE_Q12(36.9)},
	{MAKE_Q12(13.4), MAKE_Q12(35.7), MAKE_Q12(23.5), MAKE_Q12(15.6),	// TEST EXTRA 2
	 MAKE_Q12(37.2), MAKE_Q12(32.5), MAKE_Q12(4.7), MAKE_Q12(27.8),
	 MAKE_Q12(5.3), MAKE_Q12(11.1), MAKE_Q12(3.0), MAKE_Q12(45.9)},
	{MAKE_Q12(12.0), MAKE_Q12(17.8), MAKE_Q12(24.1), MAKE_Q12(36.7),	// TEST EXTRA 3
	 MAKE_Q12(0.5), MAKE_Q12(-23.4), MAKE_Q12(2.0), MAKE_Q12(-12.9),
	 MAKE_Q12(26.8), MAKE_Q12(4.1), MAKE_Q12(24.0), MAKE_Q12(-5.4)},
	{MAKE_Q12(18.0), MAKE_Q12(27.8), MAKE_Q12(27.1), MAKE_Q12(16.7),	// TEST EXTRA 4
	 MAKE_Q12(10.5), MAKE_Q12(-29.4), MAKE_Q12(22.0), MAKE_Q12(-22.9),
	 MAKE_Q12(16.8), MAKE_Q12(24.1), MAKE_Q12(29.0), MAKE_Q12(5.4)},
};

/* type definition of the structured record that holds the test case values */
typedef struct {
	unsigned char op;	/* type of operation ('C': by city, 'M': by month) */
	unsigned short id;	/* index to be checked (city or month) */
	Q12 xavg;			/* expected average */
	t_maxmin xmm;		/* expected max-min results */
} test_struct;

/* the list of test case values */
test_struct test_case[] =
	/* Tests for cities */
{{'C', 0, MAKE_Q12(19.8),				/*  0: several replicated min and max */
	{MAKE_Q12(13.4), MAKE_Q12(25.9),
	 MAKE_Q12(56.12), MAKE_Q12(78.62),
	 0, 6}},
 {'C', 1, MAKE_Q12(-9.8),				/*  1: all negatives */
	{MAKE_Q12(-18.8), MAKE_Q12(-2.2),
	 MAKE_Q12(-1.84), MAKE_Q12(28.04),
	 6, 0}},
 {'C', 2, MAKE_Q12(0.2),				/*  2: all values around 0º Celsius */
	{MAKE_Q12(-0.9), MAKE_Q12(0.8),
	 MAKE_Q12(30.38), MAKE_Q12(33.44),
	 5, 3}},
	 
	 
	 
 {'C', 3, MAKE_Q12(34.44),				/*  TEST EXTRA 1 */
	{MAKE_Q12(0.4), MAKE_Q12(99.9),
	 MAKE_Q12(32.72), MAKE_Q12(211.82),
	 10, 5}},
 {'C', 4, MAKE_Q12(21.30),				/*  TEST EXTRA 2 */
	{MAKE_Q12(3.0), MAKE_Q12(45.9),
	 MAKE_Q12(37.4), MAKE_Q12(114.62),
	 10, 11}},




	/* Tests  for months */
 {'M', 0, MAKE_Q12(15.62),				/*  3: first column (January) */
	{MAKE_Q12(-2.2), MAKE_Q12(54.7),
	 MAKE_Q12(28.0), MAKE_Q12(130.46),
	 1, 3}},
 {'M', 6, MAKE_Q12(12.84),				/*  4: middle column (July) */
	{MAKE_Q12(-18.8), MAKE_Q12(54.8),
	 MAKE_Q12(-1.8), MAKE_Q12(130.64),
	 1, 3}},
 {'M', 11, MAKE_Q12(14.9),				/*  5: last column (Desember) */
	{MAKE_Q12(-5.4), MAKE_Q12(45.9),
	 MAKE_Q12(22.28), MAKE_Q12(114.62),
	 5, 4}},
	 
	 
	 
 {'M', 1, MAKE_Q12(17.35),				/*  TEST EXTRA 3 (Febrer)*/
	{MAKE_Q12(-3.5), MAKE_Q12(35.7),
	 MAKE_Q12(25.7), MAKE_Q12(96.26),
	 1, 4}},
 {'M', 10, MAKE_Q12(10.17),				/*  TEST EXTRA 4 (Novembre)*/
	{MAKE_Q12(-5.7), MAKE_Q12(29.0),
	 MAKE_Q12(21.74), MAKE_Q12(84.2),
	 1, 6}}
};


unsigned int abs_value(int x) { return(x < 0 ? -x : x); }

unsigned char error_bits(Q12 avg, t_maxmin *maxmin, Q12 xavg, t_maxmin *xmm)
{
	unsigned char nerr = 0;
	unsigned int error;						/* marginql error */
	
	error = abs_value(avg - xavg);
	if (error > 1024)					/* average divergence error */
		nerr |= 1;						// set bit 0

	error = abs_value(maxmin->tmin_C - xmm->tmin_C);
	if (error > 4)						/* min temp. (ºC) divergence error */
		nerr |= 2;						// set bit 1

	error = abs_value(maxmin->tmax_C - xmm->tmax_C);
	if (error > 4)						/* max temp. (ºC) divergence error */
		nerr |= 4;						// set bit 2
	
	error = abs_value(maxmin->tmin_F - xmm->tmin_F);
	if (error > 1024)					/* min temp. (ºF) divergence error */
		nerr |= 8;						// set bit 3
	
	error = abs_value(maxmin->tmax_F - xmm->tmax_F);
	if (error > 1024)					/* max temp. (ºF) divergence error */
		nerr |= 16;						// set bit 4
	
	if (maxmin->id_min != xmm->id_min) /* min index divergence error */
		nerr |= 32;						// set bit 5
	
	if (maxmin->id_max != xmm->id_max) /* max index divergence error */
		nerr |= 64;						// set bit 6

	return(nerr);
}

int main(void)
{
	unsigned int i;						/* loop index */
	Q12 avg;							/* routine results */
	t_maxmin maxmin;
	unsigned int num_ok = 0;			/* number of right tests */
	unsigned int num_ko = 0;			/* number of wrong tests */
	unsigned int num_tests = 			/* total number of tests */
					sizeof(test_case) / sizeof(test_struct);

	/********* evaluate the list of test case values *********/
	for (i = 0; i < num_tests; i++)
	{
		if (test_case[i].op == 'C')
			avg = avgmaxmin_city(test_data, NUM_TEST_ROWS, test_case[i].id, &maxmin);
		else
			avg = avgmaxmin_month(test_data, NUM_TEST_ROWS, test_case[i].id, &maxmin);
		
		if (error_bits(avg, &maxmin, test_case[i].xavg, &test_case[i].xmm) == 0)
			num_ok++;
		else
			num_ko++;
	}

/* TESTING POINT: check if number of ok tests 
				  is equal to number of total tests
				  or if number of ko tests is 0.
	(gdb) p num_ok
	(gdb) p num_ko
	(gdb) p num_tests
*/

/* BREAKPOINT */
	return(0);
}
