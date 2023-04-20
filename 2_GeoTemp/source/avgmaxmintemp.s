@; ----------------------------------------------------------------
@; "avgmaxmintemp.c": rutines de càlcul de valors mitjans, màxims
@;	i mínims d'una taula de temperatures, expressades en graus
@;	Celsius o Fahrenheit, en format Q12 (coma fixa 1:19:12).
@; ----------------------------------------------------------------
@;	santiago.romani@urv.cat
@;	pere.millan@urv.cat
@;	(Abril 2021, Març 2022)
@;----------------------------------------------------------------
@;	Programador/a 1: nil.monfort@estudiants.urv.cat
@;	Programador/a 2: jaume.tello@estudiants.urv.cat
@;----------------------------------------------------------------*/
.include "include/avgmaxmintemp.i"

.text
		.align 2
		.arm

@; avgmaxmin_city(): calcula la temperatura mitjana, màxima i mínima d'una
@;				ciutat d'una taula de temperatures, amb una fila per ciutat i
@;				una columna per mes, expressades en graus Celsius en format
@;				Q12.
@;	Paràmetres:
@;		R0 = ttemp[][12]	->	taula de temperatures, amb 12 columnes i nrows files
@;		R1 = nrows		->	número de files de la taula
@;		R2 = id_city		->	índex de la fila (ciutat) a processar
@;		R3 = *mmres		->	adreça de l'estructura t_maxmin que retornarà els
@;						resultats de temperatures màximes i mínimes
@;	Resultat:	temperatura mitjana, expressada en graus Celsius, en format Q12.
	
	.global avgmaxmin_city
avgmaxmin_city:	
		push {r1, r4-r12, lr}

		mov r1, #12						;@ Numero de columnes de ttemp
		mov r4, #0						;@ Inicialitzem avg
		mov r5, #0						;@ Inicialitzem min
		mov r6, #0						;@ Inicialitzem max
		mov r7, #1						;@ Inicialitzem i
		mov r8, #0						;@ Inicialitzem tvar
		mov r9, #0						;@ Inicialitzem idmax
		mov r10, #0						;@ Inicialitzem idmin
		mov r11, #0	
			
		mul r11, r2, r1					;@ Posicio a la matriu de la ciutat actual * numero de columnes (id_city*NC = id_city * 12)
		ldr r4, [r0, r11, lsl #2]		;@ avg = ttemp[id_city][0]
		mov r6, r4						;@ max = avg
		mov r5, r4						;@ min = avg
			
		@;Cos del for
		.Lfor: 
			add r12, r11, r7			;@ R12 = id_city*NC + i 
			ldr r8, [r0, r12, lsl #2]	;@ Obtenim la temperatura del següent mes (tvar = ttemp[id_city][i])
			add r4, r8					;@ Actualitzem avg --> avg += tvar
			cmp r8, r6
			ble .Lfiifnoumax			;@ Salta si tvar<=max // Salta si no troba un màxim superior a l'actual
			.Lifnoumax:
				mov r6, r8				;@ Actualitzem el màxim
				mov r9, r7				;@ Actualitzem la posició del màxim
			.Lfiifnoumax:
			cmp r8, r5
			bge .Lfiifnoumin			;@ Salta si tvar>=min // Salta si troba un mínim inferior a l'actual
			.Lifnoumin:
				mov r5, r8				;@ Actualitzem el mínim
				mov r10, r7				;@ Actualitzem la posició del mínim
			.Lfiifnoumin:
			add r7, #1					;@ Saltem a la següent columna
			cmp r7, r1
			blo .Lfor					;@ Repeteix el bucle mentre i<NC
		.Lfifor:
		
		mov r12, #0
		cmp r4, #0						;@ La funció div_mod treballa amb números naturals...
		rsblt r4, r4, #0				;@ ...per tant, li hem de passar un número positiu
		movlt r12, #1					;@ R12 = 1 si avg<0
			
		mov r7, r3						;@ Movem el valor d'R3 a un altre registre...
										;@ ...ja que R3 queda sobreescrit al fer div_mod
			
		@;div_mod	
		sub sp, #8						;@ Fem espai a la pila per a div_mod
		mov r0, r4                 		;@ Passem parametres....
		mov r1, #12						;@ ... a div_mod...
		mov r2, sp						;@ R2 = quo
		add r3, sp, #4					;@ R3 = mod
		bl div_mod	
		ldr r4, [r2]					;@ avg = (avg/12) = r2 = quo
		add sp, #8						;@ Retirem l'espai de la pila reservat per div_mod
			
		cmp r12, #1						;@ Mirem si abans de div_mod, avg era negatiu
		rsbeq r4, r4, #0				;@ Si avg era negatiu, li tornem el signe negatiu
			
		@;Modifiquem el multicamp *mmres
		str r5, [r7, #MM_TMINC]			;@ mmres->tmin_C = min
		str r6, [r7, #MM_TMAXC]			;@ mmres->tmax_C = max
			
		mov r0, r5						;@ Passem paràmentres a Celsius2Fahrenheit
		bl Celsius2Fahrenheit			;@ Cridem la rutina
		str r0, [r7, #MM_TMINF]			;@ mmres->tmin_F = Celsius2Fahrenheit(min)
		mov r0, r6						;@ Passem paràmentres a Celsius2Fahrenheit
		bl Celsius2Fahrenheit			;@ Cridem la rutina
		str r0, [r7, #MM_TMAXF]			;@ mmres->tmax_F = Celsius2Fahrenheit(max)
			
		strh r9, [r7, #MM_IDMAX]  		;@ mmres->id_min = idmax
		strh r10, [r7, #MM_IDMIN]		;@ mmres->id_max = idmin
			
		mov r0, r4						;@ Retornem el resultat de la divisió per R0
		
		pop {r1, r4-r12, pc}
	

@; avgmaxmin_month(): calcula la temperatura mitjana, màxima i mínima d'un mes
@;				d'una taula de temperatures, amb una fila per ciutat i una
@;				columna per mes, expressades en graus Celsius en format Q12.
@;	Paràmetres:
@;		R0 = ttemp[][12]	->	taula de temperatures, amb 12 columnes i nrows files
@;		R1 = nrows		->	número de files de la taula (mínim 1 fila)
@;		R2 = id_month	->	índex de la columna (mes) a processar
@;		R3 = *mmres		->	adreça de l'estructura t_maxmin que retornarà els
@;						resultats de temperatures màximes i mínimes
@;	Resultat:	temperatura mitjana, expressada en graus Celsius, en format Q12.

	.global avgmaxmin_month
avgmaxmin_month:			
	push {r4-r12, lr}

		mov r4, #0						;@ Inicialitzem avg
		mov r5, #0						;@ Inicialitzem min
		mov r6, #0						;@ Inicialitzem max
		mov r7, #1						;@ Inicialitzem i
		mov r8, #0						;@ Inicialitzem tvar
		mov r9, #0						;@ Inicialitzem idmax
		mov r10, #0						;@ Inicialitzem idmin
		mov r11, #12					;@ Numero de columnes de ttemp
		mov r12, #0						;@ Inicialitzem avgNeg
			
		ldr r4, [r0, r2, lsl #2]		;@ avg = ttemp[0][id_month]
		mov r6, r4						;@ max = avg
		mov r5, r4						;@ min = avg
			
		;@Cos del while
		.Lwhile:
			cmp r7, r1             		
			bhs .Lfiwhile         		;@ salta al final del bucle si i >= nrows
			mla r12, r7, r11, r2     	;@ R11=> index = (i*nrows) + id_month
			ldr r8, [r0, r12, lsl #2]  	;@ tvar = ttemp[i][id_month] 
			add r4, r8                	;@ avg += tvar;
			
			;@ Primer if tvar > max
			cmp r8, r6      			;@ tvar > max
			ble .Lfiifnewmax 
			.Lifnewmax:
				mov r6, r8   			;@  max = tvar
				mov r9, r7  			;@  idmax = i
		   .Lfiifnewmax:
			;@ Primer if tvar < min
			cmp r8, r5      			;@ tvar < min
			bge .Lfiifnewmin    
			.Lifnewmin:
				mov r5, r8      		;@  min = tvar
				mov r10, r7     		;@  idmin = i
		   .Lfiifnewmin:
			add r7, #1      			;@ Actualitzem index del bucle (i++;)
			b .Lwhile
		.Lfiwhile:
		
	    cmp r4, #0       				;@ avgNeg = (avg < 0); 
		rsblt r8, r4, #0  				;@ Si avg es negatiu --> tvar = |avg|
		movlt r12, #1					;@ avgNeg = true si avg<0 
		movgt r8 , r4    				;@ Si avg es positiu --> tvar = avg
		
		mov r7, r3						;@ Movem el valor d'R3 a un altre registre...
										;@ ...ja que R3 queda sobreescrit al fer div_mod
		
		@;div_mod
		sub sp, #8						;@ Fem espai a la pila per a div_mod
		mov r0, r8                  	;@ Passem parametres....
										;@ ... a div_mod...
		;@mov r1, r1					;@ (Es redundant)
		mov r2, sp						;@ R2 = quo
		add r3, sp, #4					;@ R3 = mod
		bl div_mod
		ldr r4, [r2]					;@ avg = (tvar/nrows)
		add sp, #8						;@ Retirem l'espai de la pila reservat per div_mod
			
		cmp r12, #1	
		rsbeq r4, r4, #0            	;@ Si avg era negatiu abans de div_mod, ara el passem a negatiu un altre cop  
		;@movne r8, r8                  ;@ Si =0 el deixem igual(per aclarir)
		
		
		@;Modifiquem *mmres
			str r5, [r7, #MM_TMINC]		;@ mmres->tmin_C = min
			str r6, [r7, #MM_TMAXC]		;@ mmres->tmax_C = max
			
			mov r0, r5					;@ Passem paràmentres a Celsius2Fahrenheit
			bl Celsius2Fahrenheit		;@ Cridem la rutina
			str r0, [r7, #MM_TMINF]		;@ mmres->tmin_F = Celsius2Fahrenheit(min)
			mov r0, r6					;@ Passem paràmentres a Celsius2Fahrenheit
			bl Celsius2Fahrenheit		;@ Cridem la rutina
			str r0, [r7, #MM_TMAXF]		;@ mmres->tmax_F = Celsius2Fahrenheit(max)
			
			strh r10, [r7, #MM_IDMIN]  	;@ mmres->id_min = idmin
			strh r9, [r7, #MM_IDMAX]	;@ mmres->id_max = idmax
			mov r0, r4					;@ Retornem el resultat de la divisió per R0
      
	pop {r4-r12, pc}