/*-----------------------------------------------------------------------
|   "geotempData.c":
|		Dades per a ser processades pel les rutines definides en
|	"avgmaxmintemp.c", a partir de taules que contenen valors de
|	temperatura per a diferents ciutats del món durant els 12 mesos
|	de l'any.
|	Font: https://en.wikipedia.org/wiki/List_of_cities_by_average_temperature
|------------------------------------------------------------------------
|	santiago.romani@urv.cat
|	pere.millan@urv.cat
|	(Març 2021, Març 2022)
| -----------------------------------------------------------------------*/

#include "Q12.h"				/* Q12: tipus Coma Fixa 1:19:12 */
#include "geotemp.h"			/* t_cityinfo: tipus amb info. de ciutat */
#include "data.h"				/* defines número de ciutats */			

Q12 tempHNord_2020[NUMCITIESHNORD][12] = {
	{MAKE_Q12(13.4), MAKE_Q12(13.9), MAKE_Q12(15.7), MAKE_Q12(18.5),	// Alexandria
	 MAKE_Q12(21.2), MAKE_Q12(24.3), MAKE_Q12(25.9), MAKE_Q12(26.3),
	 MAKE_Q12(25.1), MAKE_Q12(22.0), MAKE_Q12(18.7), MAKE_Q12(14.9)},
	{MAKE_Q12(2.2), MAKE_Q12(3.5), MAKE_Q12(5.8), MAKE_Q12(7.5),		// Andorra la Vella
	 MAKE_Q12(11.5), MAKE_Q12(15.4), MAKE_Q12(18.8), MAKE_Q12(18.5),
	 MAKE_Q12(14.9), MAKE_Q12(10.3), MAKE_Q12(5.7), MAKE_Q12(3.0)},
	{MAKE_Q12(-3.1), MAKE_Q12(0.3), MAKE_Q12(6.7), MAKE_Q12(14.8),		// Beijing
	 MAKE_Q12(20.8), MAKE_Q12(24.9), MAKE_Q12(26.7), MAKE_Q12(25.5),
	 MAKE_Q12(20.8), MAKE_Q12(13.7), MAKE_Q12(5.0), MAKE_Q12(-0.9)},
	{MAKE_Q12(-7.1), MAKE_Q12(-5.4), MAKE_Q12(-1.6), MAKE_Q12(4.6),		// Calgary
	 MAKE_Q12(9.7), MAKE_Q12(13.7), MAKE_Q12(16.5), MAKE_Q12(15.8),
	 MAKE_Q12(11.0), MAKE_Q12(5.2), MAKE_Q12(-2.4), MAKE_Q12(-6.8)},
	{MAKE_Q12(-24.8), MAKE_Q12(-25.4), MAKE_Q12(-22.1), MAKE_Q12(-17.2),// Dikson
	 MAKE_Q12(-7.8), MAKE_Q12(0.4), MAKE_Q12(4.9), MAKE_Q12(5.5),
	 MAKE_Q12(1.6), MAKE_Q12(-7.5), MAKE_Q12(-17.5), MAKE_Q12(-22.9)},
	{MAKE_Q12(25.1), MAKE_Q12(25.7), MAKE_Q12(27.0), MAKE_Q12(28.7),	// Djibouti
	 MAKE_Q12(31.0), MAKE_Q12(34.2), MAKE_Q12(36.4), MAKE_Q12(36.0),
	 MAKE_Q12(33.1), MAKE_Q12(29.3), MAKE_Q12(26.9), MAKE_Q12(25.4)},
	{MAKE_Q12(78.4), MAKE_Q12(79.0), MAKE_Q12(79.9), MAKE_Q12(81.7),	// George Town
	 MAKE_Q12(83.3), MAKE_Q12(84.6), MAKE_Q12(85.3), MAKE_Q12(85.5),
	 MAKE_Q12(84.7), MAKE_Q12(83.3), MAKE_Q12(81.5), MAKE_Q12(79.2)},
	{MAKE_Q12(28.8), MAKE_Q12(33.5), MAKE_Q12(44.2), MAKE_Q12(54.8),	// Kansas City
	 MAKE_Q12(64.5), MAKE_Q12(73.5), MAKE_Q12(78.3), MAKE_Q12(77.0),
	 MAKE_Q12(68.1), MAKE_Q12(56.3), MAKE_Q12(43.6), MAKE_Q12(31.4)},
	{MAKE_Q12(4.6), MAKE_Q12(5.1), MAKE_Q12(8.4), MAKE_Q12(14.2),		// Kyoto
	 MAKE_Q12(19.0), MAKE_Q12(23.0), MAKE_Q12(26.8), MAKE_Q12(28.2),
	 MAKE_Q12(24.1), MAKE_Q12(17.8), MAKE_Q12(12.1), MAKE_Q12(7.0)},
	{MAKE_Q12(17.4), MAKE_Q12(18.1), MAKE_Q12(19.7), MAKE_Q12(22.1),	// La Paz
	 MAKE_Q12(24.5), MAKE_Q12(27.1), MAKE_Q12(29.7), MAKE_Q12(30.2),
	 MAKE_Q12(29.3), MAKE_Q12(26.2), MAKE_Q12(22.0), MAKE_Q12(18.6)},
	{MAKE_Q12(41.3), MAKE_Q12(45.5), MAKE_Q12(54.0), MAKE_Q12(63.0),	// Memphis
	 MAKE_Q12(71.7), MAKE_Q12(79.6), MAKE_Q12(82.7), MAKE_Q12(82.1),
	 MAKE_Q12(75.2), MAKE_Q12(64.1), MAKE_Q12(53.2), MAKE_Q12(43.6)},
	{MAKE_Q12(13.8), MAKE_Q12(16.5), MAKE_Q12(22.1), MAKE_Q12(28.7),	// New Delhi
	 MAKE_Q12(32.8), MAKE_Q12(34.0), MAKE_Q12(30.9), MAKE_Q12(29.7),
	 MAKE_Q12(29.0), MAKE_Q12(26.1), MAKE_Q12(20.5), MAKE_Q12(15.3)},
	{MAKE_Q12(10.6), MAKE_Q12(10.6), MAKE_Q12(13.1), MAKE_Q12(17.1),	// Nicosia
	 MAKE_Q12(22.3), MAKE_Q12(26.9), MAKE_Q12(29.7), MAKE_Q12(29.4),
	 MAKE_Q12(26.2), MAKE_Q12(22.3), MAKE_Q12(16.3), MAKE_Q12(12.0)},
	{MAKE_Q12(16.0), MAKE_Q12(18.2), MAKE_Q12(23.1), MAKE_Q12(27.9),	// Reggane
	 MAKE_Q12(32.2), MAKE_Q12(36.4), MAKE_Q12(39.8), MAKE_Q12(38.4),
	 MAKE_Q12(35.5), MAKE_Q12(29.2), MAKE_Q12(22.0), MAKE_Q12(17.8)},
	{MAKE_Q12(77.6), MAKE_Q12(77.9), MAKE_Q12(78.9), MAKE_Q12(80.3),	// San Juan
	 MAKE_Q12(81.9), MAKE_Q12(83.3), MAKE_Q12(83.4), MAKE_Q12(83.7),
	 MAKE_Q12(83.5), MAKE_Q12(82.6), MAKE_Q12(80.6), MAKE_Q12(76.7)},
	{MAKE_Q12(60.6), MAKE_Q12(63.2), MAKE_Q12(67.1), MAKE_Q12(71.7),	// Tampa
	 MAKE_Q12(78.2), MAKE_Q12(82.0), MAKE_Q12(82.8), MAKE_Q12(83.0),
	 MAKE_Q12(81.5), MAKE_Q12(76.0), MAKE_Q12(69.0), MAKE_Q12(63.0)},
	{MAKE_Q12(-21.6), MAKE_Q12(-16.6), MAKE_Q12(-7.4), MAKE_Q12(2.0),	// Ulaanbaatar
	 MAKE_Q12(10.1), MAKE_Q12(15.7), MAKE_Q12(18.2), MAKE_Q12(16.0),
	 MAKE_Q12(9.6), MAKE_Q12(0.5), MAKE_Q12(-11.9), MAKE_Q12(-19.0)},
	{MAKE_Q12(-38.6), MAKE_Q12(-33.8), MAKE_Q12(-20.1), MAKE_Q12(-4.8),	// Yakutsk
	 MAKE_Q12(7.5), MAKE_Q12(16.4), MAKE_Q12(19.5), MAKE_Q12(15.2),
	 MAKE_Q12(6.1), MAKE_Q12(-7.8), MAKE_Q12(-27.0), MAKE_Q12(-37.6)}
	};


t_cityinfo info_HNord[NUMCITIESHNORD] = {
	{"Alexandria", 'C'},				// Egypt
	{"Andorra la Vella", 'C'},			// Andorra
	{"Beijing", 'C'},					// China
	{"Calgary", 'C'},					// Canada
	{"Dikson", 'C'},					// Russia
	{"Djibouti", 'C'},					// Djibouti
	{"George Town", 'F'},				// Cayman Islands
	{"Kansas City", 'F'},				// USA
	{"Kyoto", 'C'},						// Japan
	{"La Paz", 'C'},					// Mexico
	{"Memphis", 'F'},					// USA
	{"New Delhi", 'C'},					// India
	{"Nicosia", 'C'},					// Cyprus
	{"Reggane", 'C'},					// Argelia
	{"San Juan", 'F'},					// Puerto Rico
	{"Tampa", 'F'},						// USA
	{"Ulaanbaatar", 'C'},				// Mongolia
	{"Yakutsk", 'C'}					// Russia
};	


Q12 tempHSud_2020[NUMCITIESHSUD][12] = {
	{MAKE_Q12(23.2), MAKE_Q12(23.3), MAKE_Q12(20.9), MAKE_Q12(17.6),	// Adelaide
	 MAKE_Q12(13.5), MAKE_Q12(12.1), MAKE_Q12(11.4), MAKE_Q12(12.4),
	 MAKE_Q12(14.4), MAKE_Q12(16.7), MAKE_Q12(19.7), MAKE_Q12(21.3)},
	{MAKE_Q12(15.0), MAKE_Q12(14.8), MAKE_Q12(11.9), MAKE_Q12(7.9),		// Bariloche
	 MAKE_Q12(4.9), MAKE_Q12(2.9), MAKE_Q12(2.1), MAKE_Q12(3.0),
	 MAKE_Q12(5.1), MAKE_Q12(8.0), MAKE_Q12(10.8), MAKE_Q12(13.5)},
	{MAKE_Q12(20.6), MAKE_Q12(20.1), MAKE_Q12(17.6), MAKE_Q12(13.4),	// Canberra
	 MAKE_Q12(9.4), MAKE_Q12(6.7), MAKE_Q12(5.7), MAKE_Q12(7.0),
	 MAKE_Q12(9.8), MAKE_Q12(12.8), MAKE_Q12(15.8), MAKE_Q12(18.8)},
	{MAKE_Q12(27.7), MAKE_Q12(27.6), MAKE_Q12(27.4), MAKE_Q12(27.4),	// Dili
	 MAKE_Q12(27.0), MAKE_Q12(26.8), MAKE_Q12(25.5), MAKE_Q12(25.1),
	 MAKE_Q12(25.4), MAKE_Q12(26.0), MAKE_Q12(27.2), MAKE_Q12(27.4)},
	{MAKE_Q12(20.8), MAKE_Q12(20.8), MAKE_Q12(20.0), MAKE_Q12(18.9),	// Fianarantsoa
	 MAKE_Q12(16.7), MAKE_Q12(14.5), MAKE_Q12(14.0), MAKE_Q12(14.4),
	 MAKE_Q12(16.2), MAKE_Q12(18.3), MAKE_Q12(19.7), MAKE_Q12(20.4)},
	{MAKE_Q12(25.9), MAKE_Q12(25.3), MAKE_Q12(24.1), MAKE_Q12(21.2),	// Ghanzi
	 MAKE_Q12(17.6), MAKE_Q12(14.3), MAKE_Q12(14.1), MAKE_Q12(17.1),
	 MAKE_Q12(21.5), MAKE_Q12(24.6), MAKE_Q12(25.7), MAKE_Q12(26.1)},
	{MAKE_Q12(23.3), MAKE_Q12(23.7), MAKE_Q12(23.1), MAKE_Q12(21.9),	// Hanga Roa
	 MAKE_Q12(20.1), MAKE_Q12(18.9), MAKE_Q12(18.0), MAKE_Q12(17.9),
	 MAKE_Q12(18.3), MAKE_Q12(19.0), MAKE_Q12(20.4), MAKE_Q12(21.8)},
	{MAKE_Q12(21.0), MAKE_Q12(20.7), MAKE_Q12(20.3), MAKE_Q12(18.8),	// Harare
	 MAKE_Q12(16.1), MAKE_Q12(13.7), MAKE_Q12(13.4), MAKE_Q12(15.5),
	 MAKE_Q12(18.6), MAKE_Q12(20.8), MAKE_Q12(21.2), MAKE_Q12(20.9)},
	{MAKE_Q12(27.1), MAKE_Q12(26.9), MAKE_Q12(27.1), MAKE_Q12(27.3),	// Jayapura
	 MAKE_Q12(27.2), MAKE_Q12(26.9), MAKE_Q12(26.4), MAKE_Q12(26.6),
	 MAKE_Q12(26.9), MAKE_Q12(27.2), MAKE_Q12(27.3), MAKE_Q12(27.0)},
	{MAKE_Q12(19.5), MAKE_Q12(19.0), MAKE_Q12(18.0), MAKE_Q12(15.3),	// Johannesburg
	 MAKE_Q12(12.6), MAKE_Q12(9.6), MAKE_Q12(10.0), MAKE_Q12(12.5),
	 MAKE_Q12(15.9), MAKE_Q12(17.1), MAKE_Q12(17.9), MAKE_Q12(19.0)},
	{MAKE_Q12(15.2), MAKE_Q12(14.8), MAKE_Q12(12.4), MAKE_Q12(9.2),		// Lake Tekapo
	 MAKE_Q12(5.9), MAKE_Q12(2.6), MAKE_Q12(1.4), MAKE_Q12(3.6),
	 MAKE_Q12(6.5), MAKE_Q12(8.8), MAKE_Q12(11.1), MAKE_Q12(13.2)},
	{MAKE_Q12(23.0), MAKE_Q12(22.5), MAKE_Q12(20.6), MAKE_Q12(17.2),	// Montevideo
	 MAKE_Q12(14.0), MAKE_Q12(11.1), MAKE_Q12(10.9), MAKE_Q12(11.7),
	 MAKE_Q12(13.4), MAKE_Q12(16.0), MAKE_Q12(18.6), MAKE_Q12(21.3)},
	{MAKE_Q12(27.4), MAKE_Q12(27.3), MAKE_Q12(27.1), MAKE_Q12(27.0),	// Port Moresby
	 MAKE_Q12(26.9), MAKE_Q12(26.1), MAKE_Q12(25.7), MAKE_Q12(26.1),
	 MAKE_Q12(26.5), MAKE_Q12(27.5), MAKE_Q12(27.6), MAKE_Q12(27.8)},
	{MAKE_Q12(10.8), MAKE_Q12(10.3), MAKE_Q12(8.5), MAKE_Q12(6.2),		// Punta Arenas
	 MAKE_Q12(3.7), MAKE_Q12(1.5), MAKE_Q12(1.4), MAKE_Q12(2.3),
	 MAKE_Q12(4.2), MAKE_Q12(6.4), MAKE_Q12(8.4), MAKE_Q12(9.9)},
	{MAKE_Q12(26.3), MAKE_Q12(26.6), MAKE_Q12(26.0), MAKE_Q12(24.4),	// Rio de Janeiro
	 MAKE_Q12(22.8), MAKE_Q12(21.8), MAKE_Q12(21.3), MAKE_Q12(21.8),
	 MAKE_Q12(22.2), MAKE_Q12(22.9), MAKE_Q12(24.0), MAKE_Q12(25.3)},
	{MAKE_Q12(9.5), MAKE_Q12(8.9), MAKE_Q12(8.1), MAKE_Q12(6.1),		// Stanley
	 MAKE_Q12(3.9), MAKE_Q12(2.2), MAKE_Q12(1.9), MAKE_Q12(2.2),
	 MAKE_Q12(3.9), MAKE_Q12(5.3), MAKE_Q12(7.0), MAKE_Q12(8.1)},
	{MAKE_Q12(16.2), MAKE_Q12(15.7), MAKE_Q12(15.8), MAKE_Q12(15.5),	// Sucre
	 MAKE_Q12(14.9), MAKE_Q12(13.8), MAKE_Q12(13.9), MAKE_Q12(14.9),
	 MAKE_Q12(16.2), MAKE_Q12(16.9), MAKE_Q12(17.3), MAKE_Q12(16.7)},
	{MAKE_Q12(9.6), MAKE_Q12(9.3), MAKE_Q12(7.7), MAKE_Q12(5.7),		// Ushuaia
	 MAKE_Q12(3.2), MAKE_Q12(1.7), MAKE_Q12(1.3), MAKE_Q12(2.2),
	 MAKE_Q12(4.1), MAKE_Q12(6.2), MAKE_Q12(7.8), MAKE_Q12(9.1)},
	{MAKE_Q12(16.9), MAKE_Q12(17.2), MAKE_Q12(15.8), MAKE_Q12(13.7),	// Wellington
	 MAKE_Q12(11.7), MAKE_Q12(9.7), MAKE_Q12(8.9), MAKE_Q12(9.4),
	 MAKE_Q12(10.8), MAKE_Q12(12.0), MAKE_Q12(13.5), MAKE_Q12(15.4)}
};


t_cityinfo info_HSud[NUMCITIESHSUD] = {
	{"Adelaide", 'C'},					// Australia
	{"Bariloche", 'C'},					// Argentina
	{"Canberra", 'C'},					// Australia
	{"Dili", 'C'},						// East Timor
	{"Fianarantsoa", 'C'},				// Madagascar
	{"Ghanzi", 'C'},					// Botswana
	{"Hanga Roa", 'C'},					// Chile
	{"Harare", 'C'},					// Zimbabwe
	{"Jayapura", 'C'},					// Indonesia
	{"Johannesburg", 'C'},				// South Africa
	{"Lake Tekapo", 'C'},				// New Zealand
	{"Montevideo", 'C'},				// Uruguay
	{"Port Moresby", 'C'},				// Papua New Guinea
	{"Punta Arenas", 'C'},				// Chile
	{"Rio de Janeiro", 'C'},			// Brazil
	{"Stanley", 'C'},					// Falkland Islands
	{"Sucre", 'C'},						// Bolivia
	{"Ushuaia", 'C'},					// Argentina
	{"Wellington", 'C'}					// New Zealand
};

