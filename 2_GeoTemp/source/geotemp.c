/*-----------------------------------------------------------------------
|   "geotemp.c":
|		programa per calcular els valors mig, màxim i mínim d'una taula
|	de temperatures, expressades en graus ºC o ºF i en format Q12, on
|	cada fila correspon a una ciutat i cada columna a un mes.
|	Les taules amb la informació estan definides en un altre mòdul
|	(variables globals externes).
|------------------------------------------------------------------------
|	santiago.romani@urv.cat
|	pere.millan@urv.cat
|	(Abril 2021, Març 2022)
| -----------------------------------------------------------------------*/

#include "Q12.h"				/* Q12: tipus Coma Fixa 1:19:12 */
#include "divmod.h"				/* rutina div_mod(), en "LibFonCompus.a" */
#include "CelsiusFahrenheit.h"	/* rutines de conversió C->F i F->C */
#include "avgmaxmintemp.h"		/* mmres: tipus de retorn de màxim i mínim */
#include "geotemp.h"			/* t_cityinfo: tipus amb info. de ciutat */
#include "data.h"				/* definició de dades externes */


/* normalitzar_temperatures(): funció per a convertir les temperatures
			expressades en graus Fahrenheit a graus Celsius, segons el
			vector d'informació de les ciutats registrades.
	Paràmetres:
		vinfo[]		-> vector amb una entrada per ciutat, indicant el nom
					   i l'escala utilitzada per expressar les temperatures,
		ttemp[][12]	-> taula amb una fila per ciutat i una columna per mes;
					   se suposa que les temperatures de cada fila estaran
					   expressades en l'escala indicada en t_info[];
		num_cities	-> número de ciutats, tant al vector tinfo[] com a la
					   matriu ttemp[];
	Resultats:
		ttemp[][12]	-> les temperatures convertides a graus Celsius es
					   guardaran sobre la mateixa taula d'entrada (pas per
					   referencia).
*/
void normalitzar_temperatures(t_cityinfo vinfo[], Q12 ttemp[][12], unsigned short num_cities)
{
	unsigned short i, j;
	
	for (i = 0; i < num_cities; i++)	// recorregut de totes les ciutats
		if (vinfo[i].scale == 'F')		// si l'escala utilitzada és Fahrenheit
			for (j = 0; j < 12; j++)	// recorregut de tots els mesos
				ttemp[i][j] = Fahrenheit2Celsius(ttemp[i][j]);
}



int main(void)
{
	Q12	avgres[4];
	t_maxmin maxminres[4];
	
	normalitzar_temperatures(info_HNord, tempHNord_2020, NUMCITIESHNORD);
	normalitzar_temperatures(info_HSud, tempHSud_2020, NUMCITIESHSUD);
	
			// càlculs sobre George Town (Cayman Island)
	avgres[0] = avgmaxmin_city(tempHNord_2020, NUMCITIESHNORD, 6, &maxminres[0]);
			// càlculs sobre el mes d'agost (hemisferi nord)
	avgres[1] = avgmaxmin_month(tempHNord_2020, NUMCITIESHNORD, 7, &maxminres[1]);
			// càlculs sobre Wellington (New Zealand)
	avgres[2] = avgmaxmin_city(tempHSud_2020, NUMCITIESHSUD, 18, &maxminres[2]);
			// càlculs sobre el mes de desembre (hemisferi sud)
	avgres[3] = avgmaxmin_month(tempHSud_2020, NUMCITIESHSUD, 11, &maxminres[3]);
	
	
	Q12 dump = avgres[0];		// evitar warning "'avgres' set but not used"
	dump = dump;				// evitar warning "'dump' set but not used"
/* TESTING POINT: check the results
	(gdb) p avgres			-> {114254, 103387, 52906, 78255}
	(gdb) p maxminres[0]	-> {105606, 121766, 321167, 350256, 0, 7}
	(gdb) p maxminres[1]	-> {22528, 157286, 171623, 414194, 4, 13}
	(gdb) p info_HNord[4].name	-> "Dikson"
	(gdb) p info_HNord[13].name	-> "Reggane"
	(gdb) p maxminres[2]	-> {36454, 70451, 196690, 257887, 6, 1}
	(gdb) p maxminres[3]	-> {33178, 113869, 190794, 336041, 15, 12}
	(gdb) p info_HSud[15].name	-> "Stanley"
	(gdb) p info_HSud[12].name	-> "Port Moresby"	
*/

/* BREAKPOINT */
	return(0);
}
