/*----------------------------------------------------------------
|   CelsiusFahrenheit.c: rutines de conversió de temperatura en 
|						 format Q12 (Coma Fixa 1:19:12). 
| ----------------------------------------------------------------
|	santiago.romani@urv.cat
|	pere.millan@urv.cat
|	(Març 2021, Febrer 2022)
| ----------------------------------------------------------------*/

#include "Q12.h"	/* Q12: tipus Coma Fixa 1:19:12
					   MAKE_Q12(real): codifica un valor real en format Q12
					   MASK_SIGN: màscara per obtenir el bit de signe
					*/


/* Celsius2Fahrenheit(): converteix una temperatura en graus Celsius a la
						temperatura equivalent en graus Fahrenheit, utilitzant
						valors codificats en Coma Fixa 1:19:12.
	output = (input * 9/5) + 32.0;
*/
Q12 Celsius2Fahrenheit(Q12 input)
{
	Q12 output;
	long long prod64;		// resultat de la multiplicació (64 bits)

		// ajust d'escala (input * 9/5), amb multiplicació de 64 bits
	prod64 = (((long long) input) * MAKE_Q12(9.0/5.0));
	
		// ajustar bits fraccionaris:
		//	prod64 = real(input) * 2^12 * real(9/5) * 2^12
		//	output = prod64 / 2^12 = real(input * 9/5) * 2^12
	output = (Q12) (prod64 >> 12);
	
	output += MAKE_Q12(32.0);		// afegir desplaçament d'escala Fahrenheit

	return(output);
}


/* Fahrenheit2Celsius(): converteix una temperatura en graus Fahrenheit a la
						temperatura equivalent en graus Celsius, utilitzant
						valors codificats en Coma Fixa 1:19:12.
	output = (input - 32.0) * 5/9;
*/
Q12 Fahrenheit2Celsius(Q12 input)
{
	Q12 output;
	long long prod64;		// resultat de la multiplicació (64 bits)
	
	input -= MAKE_Q12(32.0);		// treure desplaçament d'escala Fahrenheit
		
		// ajust d'escala ((input - 32.0) * 5/9), amb multiplicació de 64 bits
	prod64 = (((long long) input) * MAKE_Q12(5.0/9.0));
	
		// ajustar bits fraccionaris:
		//	prod64 = real(input - 32.0) * 2^12 * real(5/9) * 2^12
		//	output = prod64 / 2^12 = real(input - 32.0) * real(5/9) * 2^12
	output = (Q12) (prod64 >> 12);

	return(output);
}

