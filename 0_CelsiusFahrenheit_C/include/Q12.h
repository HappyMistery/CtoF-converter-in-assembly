/*-----------------------------------------------------------------
|   Declaració de tipus, màscares i macro del format Q12, és a dir, 
|	en format Coma Fixa 1:19:12.
| -----------------------------------------------------------------
|	pere.millan@urv.cat
|	santiago.romani@urv.cat
|	(Març 2021, Febrer 2022)
| ----------------------------------------------------------------*/

#ifndef Q12_H
#define Q12_H


/* Declaració de tipus Coma Fixa 1:19:12 
		 1 bit  de signe (bit 31), =0 -> positiu, =1 -> negatiu
		19 bits de part entera (bits 30..12), aprox. 5-6 dígits en base 10
		12 bits de part fraccionària (bits 11..0), aprox. 3-4 dígits en base 10
*/
typedef int Q12;


/* Macro per convertir valors reals en valors Coma Fixa 1:19:12
		Exemples:
		MAKE_Q12(3.1416) --> 0x00003244
		MAKE_Q12(-5.125) --> 0xFFFEAE00
*/
#define MAKE_Q12(real)	(int)((real)*(1<<12)+(real<0?-0.5:0.5)) 


/* MÀSCARES per als camps de bits de valors 1:19:12 */
#define MASK_SIGN	0x80000000	/* bit 31:		signe */
#define MASK_INT	0x7FFFF000	/* bits 30..12:	part entera */
#define MASK_FRAC	0x00000FFF	/* bits 11..0:	part fraccionària */


#endif /* Q12_H */
