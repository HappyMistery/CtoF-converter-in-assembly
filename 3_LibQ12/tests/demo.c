/*-----------------------------------------------------------------------
|   Description: a program to check some fixed point arithmetic functions
|				implemented in "libQ12.a"; specifically, it computes the
|				area of a trapezium, given the key parameters (long base,
|				short base, height).
|------------------------------------------------------------------------
|	Author: Santiago Romani (DEIM, URV)
|	Date:   April/2021, March/2022 
| -----------------------------------------------------------------------*/

#include "Q12.h"	/* external declarations of types, defines, macros
				   and function prototypes for operating with Q12 numbers */


/* global variables as inputs and output, for computing the areas */
Q12 long_base = MAKE_Q12(45.12);		// B = 45.12 cm
Q12 short_base = MAKE_Q12(30.75);		// b = 30.75 cm
Q12 height = MAKE_Q12(29.99);			// h = 29.99 cm
Q12 trapezium_area;		// expected value: (B+b)*h/2 = 1137.67065 cm^2

int main(void)
{
	unsigned char ov;			/* possible overflow */
	Q12 pr;						/* partial result */
	
		// trapezium_area = (long_base + short_base)*height / 2.0
	pr = add_Q12(long_base, short_base, &ov);
	if (!ov)
	{			// proceed with remaining ops only if not overflow
		pr = mul_Q12(pr, height, &ov);
		if (!ov)
		{
			pr = div_Q12(pr, MAKE_Q12(2.0), &ov);
			if (!ov)				// if everthing went fine,
				trapezium_area = pr;	// update output global variable
		}
	}

/* TESTING POINT: check the result (if no overflow)
	(gdb) p ov
	(gdb) p /f trapezium_area/4096.0
*/

/* BREAKPOINT */
	return(ov);
}
