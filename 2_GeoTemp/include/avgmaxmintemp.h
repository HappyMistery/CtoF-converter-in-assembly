/*---------------------------------------------------------------------
|   Declaraci� de prototipus de rutines de c�lcul de valors mitjos,
|	m�xims i m�nims d'una taula de temperatures, expressades en graus
|	Celsius, en format Q12 (coma fixa 1:19:12).
| ---------------------------------------------------------------------
|	pere.millan@urv.cat
|	santiago.romani@urv.cat
|	(Mar� 2021, Mar� 2022)
| ---------------------------------------------------------------------*/

#ifndef AVGMAXMINTEMP_H
#define AVGMAXMINTEMP_H

#include "Q12.h"				// definici� tipus Q12


  	/* declaraci� del tipus t_maxmin, per retornar resultats */
typedef struct
{	
	Q12 tmin_C;				// temperatura m�nima, en graus Celsius
	Q12 tmax_C;				// temperatura m�xima, en graus Celsius
	Q12 tmin_F;				// temperatura m�nima, en graus Fahrenheit
	Q12 tmax_F;				// temperatura m�xima, en graus Fahrenheit
	unsigned short id_min;	// �ndex temperatura m�nima
	unsigned short id_max; 	// �ndex temperatura m�xima
} t_maxmin;


/* avgmaxmin_city(): calcula la temperatura mitjana, m�xima i m�nima d'una
|				ciutat d'una taula de temperatures, amb una fila per ciutat i
|				una columna per mes, expressades en graus Celsius en format
|				Q12.
|	Par�metres:
|		ttemp[][12]	->	taula de temperatures, amb 12 columnes i nrows files
|		nrows		->	n�mero de files de la taula
|		id_city		->	�ndex de la fila (ciutat) a processar
|		*mmres		->	adre�a de l'estructura t_maxmin que retornar� els
|						resultats de temperatures m�ximes i m�nimes
|	Resultat:	temperatura mitjana, expressada en graus Celsius, en format Q12.
*/		
Q12 avgmaxmin_city(Q12 ttemp[][12], unsigned short nrows, unsigned short id_city, t_maxmin *mmres);


/* avgmaxmin_month(): calcula la temperatura mitjana, m�xima i m�nima d'un mes
|				d'una taula de temperatures, amb una fila per ciutat i una
|				columna per mes, expressades en graus Celsius en format Q12.
|	Par�metres:
|		ttemp[][12]	->	taula de temperatures, amb 12 columnes i nrows files
|		nrows		->	n�mero de files de la taula
|		id_month	->	�ndex de la columna (mes) a processar
|		*mmres		->	adre�a de l'estructura t_maxmin que retornar� els
|						resultats de temperatures m�ximes i m�nimes
|	Resultat:	temperatura mitjana, expressada en graus Celsius, en format Q12.
*/		
Q12 avgmaxmin_month(Q12 ttemp[][12], unsigned short nrows, unsigned short id_month, t_maxmin *mmres);


#endif 	/* AVGMAXMINTEMP_H */