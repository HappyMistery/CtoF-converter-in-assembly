@;-----------------------------------------------------------------
@;  Q12.s: rutines que permeten fer operacions aritmetiques amb
@;  valors codificats en codificacio 1:19:12(Q12). 
@;-----------------------------------------------------------------
@;	santiago.romani@urv.cat
@;	pere.millan@urv.cat
@;	(Març 2022)
@;----------------------------------------------------------------
@;	Programador/a 1: nil.monfort@estudiants.urv.cat
@;	Programador/a 2: jaume.tello@estudiants.urv.cat
@;----------------------------------------------------------------*/
.include "includes/Q12.i"

.text
    .align 2
    .arm
    .global add_Q12
    .global sub_Q12
    .global mul_Q12
    .global div_Q12

@; add_Q12(): 
@;          calcula i retorna la suma dels 2 primers operands,
@;          (num1 + num2)	codificats en Coma fixa 1:19:12.
@; Parametres:
@;          R0 -> primer operand
@;          R1 -> segon operand
@;          R2 -> retorna l'overflow:
@;          		0: no s'ha produït overflow, resultat correcte.
@;          		1: hi ha overflow (resultat massa gran) i el que es
@;          		retorna són els bits baixos del resultat.
@; Retorna:
@;          R0 -> suma de num1 + num2
add_Q12:
    push {r3, lr}
	
    mov r3, #0                      @; Per si s'ha produit overflow, ini=0
    adds r0, r1                     @; Suma els 2 nombres i modifica el flag 
    movvs r3, #1                    @; R3=1 si overflow 
    strb r3, [r2]                   @; Guarda l'overflow

    pop {r3, pc}

@; sub_Q12(): 
@;          calcula i retorna la resta dels 2 primers operands,
@;          (num1 - num2)	codificats en Coma fixa 1:19:12.
@; Paràmetres:
@;          R0 -> primer operand
@;          R1 -> segon operand
@;          R2 -> retorna l'overflow:
@;          		0: no s'ha produït overflow, resultat correcte.
@;          		1: hi ha overflow (resultat massa gran) i el que es
@;          		retorna són els bits baixos del resultat.
@; Retorna:
@;          R0 -> resta de num1 - num2
sub_Q12:
    push {r3, lr}
	
    mov r3, #0                      @; Inicialitzem la variable ov (inicialment a false, 0)
    subs r0, r1                     @; Fem la resta R0 = R0 - R1 tenint en compte el signe
    movvs r3, #1                    @; Si s'activa el flag de overflow, R3 passarà a ser true, 1
    strb r3, [r2]                   @; Guardem el resultat a memoria
	
    pop {r3, pc}
	
	
@; mul_Q12(): 
@;          calcula i retorna la multiplicació dels 2 primers operands,
@;			(num1 * num2) codificats en Coma fixa 1:19:12.
@; Paràmetres:
@;          R0 -> primer operand
@;          R1 -> segon operand
@;          R2 -> retorna l'overflow:
@;				0: no s'ha produït overflow, resultat correcte.
@;				1: hi ha overflow (resultat massa gran) i el que es
@;				retorna són els bits baixos del resultat.
@; Retorna:
@;          R0 -> multiplicació de num1*num2
mul_Q12:
    push {r3-r7, lr}

    mov r3, #0                      @; per si s'ha produit overflow, ini=0
    mov r4, #0                      @; bits baixos n1 * n2
    mov r5, #0                      @; bits alts n1 * n2

    smull r4, r5, r0, r1            @; fa el producte de n1*n2 i guarda el  R4 and R5 (baixos alts)

    mov r6, #12                     @; guardem els bits a desplacar
    rsb r7, r6, #32                 @; R7 = 32 - 12 = 20
    mov r4, r4, lsr r6              @; Desplacem a la dreta la part baixa R4(lo)
    orr r4, r5, lsl r7              @; Afegim a R4(lo) els bits entre R5(hi) i R4(lo)
    mov r5, r5, asr r6              @; Desplacem a la dreta la part alta R5(hi)...
	
	cmp r4, #0                  	@; Mirem el signe del resultat(Rlo) 
	mvnlt r5, r5                	@; Invertim els bits, 0->1 ; 1->0
	cmp r5, #0                  	@; Mirem si el Rhi es positiu
	movne r3, #1                	@; Si es !0 canviem a 1 a overflow
	
    mov r0, r4                      @; return 
    strb r3, [r2]                   @; guarda a la memoria el overflow

    pop {r3-r7, pc}
	
	
@; div_Q12: 
@;          calcula i retorna la divisió dels 2 primers operands,
@;			(num1 / num2) codificats en Coma fixa 1:19:12.
@; Paràmetres:
@;          R0 -> primer operand
@;          R1 -> segon operand
@;          R2 -> retorna l'overflow:
@;				0: no s'ha produït overflow, resultat correcte.
@;				1: hi ha overflow (resultat massa gran) i el que es
@;				retorna són els bits baixos del resultat.
@; Retorna:
@;          R0 -> divisió de num1/num2
div_Q12:
    push {r3-r9, lr}

    mov r3, #0                     		;@ Inicialitzem la variable ov (inicialment a false, 0)
    mov r4, #0                     		;@ El segon operand és negatiu? (nicialment a false, 0) 
    mov r6, r2                     		;@ Movem el registre R2 a un altre registre...
										;@ ...ja que R2 quedarà sobreescrit al fer div_mod
                                   
    .Lifdivisor0:                  
        cmp r1, #0                 		;@ Mirem si el divisor és igual a 0
        beq .Ldivisio_per_zero 			;@ Saltem si el divisor és 0
	.Lfiifdivisor0:
	.Lelse:
		cmp r1, #0                 		;@ Mirem si el 2n operand és positiu o negatiu
		movlt r4, #1               		;@ Si el 2n operand és negatiu, actualitzem op2neg a true(1)
		rsblt r1, r1, #0				;@ Si el 2n operand és negatiu, el passem a positiu
		;@movgt r1, r1					;@ Si el 2n operand és positiu, no cal canviar-li el signe
		
		@;div_mod
		sub sp, #12                    	;@ Reservem 12 bytes a la pila, 4 per cada variable: quo, mod i ov
		
		mov r7, r3                      ;@ Movem ov i num1 a altres registres ja que al...
		mov r8, r0                      ;@ ...fer div_mod, aquests quedaràn sobreescrits
		
		@; Com que hem de fer num1*(1/num2), primer de tot calculem 1/num2
		;@mov r1, r1					;@ A R1 ja tenim l'operador en positiu
		mov r9, #1
		mov r0, r9, lsl #24             ;@ R0 = MAKE_Q12(1.0) << 12 = (1.0 << 12) << 12 = 1.0 << 24 
		mov r2, sp                      ;@ R2 = quo
		add r3, sp, #4                  ;@ R3 = mod 
		bl div_mod						;@ Cridem la funció div_mod
		mov r0, r8                      ;@ Recuperem el valor de num1 al registre R0
		ldr r1, [r2]                    ;@ Guardem el resultat de la divisió a R1 = 1/num2
		add r2, sp, #8                  ;@ R2 conté l'adreça de memòria de la variable ov
		bl mul_Q12                      ;@ Fem la multiplicació num1*(1/num2)
		ldrb r3, [r2]               	;@ mul_12 pot modificar l'estat de l'overflow...
										;@ ...per tant, actualitzem R3
										
		add sp, #12                     ;@ Recuperem els 12 bytes reservats anteriorment
			
		cmp r4, #1                  	;@ Mirem si op2neg era true(1) abans de fer la divisió
		rsblo r0, r0, #0				;@ Si op2neg era true(1), canviem el signe del resultat
		;@movhi r0, r0					;@ Si op2neg era false(0), no canviem el signe del resultat
		b .Lfidivisio_per_zero          ;@ Evitem que s'actualitzi l'ov 
	.Lfielse:
	
    .Ldivisio_per_zero:
        mov r0, #0
        mov r3, #1                  	;@ ov = true = 1
        strb r3, [r2]					;@ Escribim el resultat de overflow a memoria
    .Lfidivisio_per_zero:	
	
    strb r3, [r6]                   	;@ Escribim el resultat de overflow a memoria
	
    pop {r3-r9, pc}

.end

