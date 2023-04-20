@;----------------------------------------------------------------
@;  CelsiusFahrenheit.s: rutines de conversió de temperatura en 
@;						 format Q12 (Coma Fixa 1:19:12). 
@;----------------------------------------------------------------
@;	santiago.romani@urv.cat
@;	pere.millan@urv.cat
@;	(Març 2021, Març 2022)
@;----------------------------------------------------------------
@;	Programador/a 1: nil.monfort@estudiants.urv.cat
@;	Programador/a 2: jaume.tello@estudiants.urv.cat
@;----------------------------------------------------------------*/

.include "Q12.i"

.data 
     KfToC:   .word 0x000008E4        ;@ valor de la fraccio 5/9 (0'555) en Q12 
	 KcToF:   .word 0x00001CCD         ;@ valor de la fraccio 9/5 (1'8) en Q12 
	 trenta2: .word 0x00020000         ;@ valor de la constant 32 en Q12

    

.text
		.align 2
		.arm


@; Celsius2Fahrenheit(): converteix una temperatura en graus Celsius a la
@;						temperatura equivalent en graus Fahrenheit, utilitzant
@;						valors codificats en Coma Fixa 1:19:12.
@;	Entrada:
@;		input 	-> R0
@;	Sortida:
@;		R0 		-> output = (input * 9/5) + 32.0;
	.global Celsius2Fahrenheit
Celsius2Fahrenheit:
		push {r1-r7, lr}
		
		mov r1, #12             ;@ Guardem el 12 per fer els desplaçament		
		ldr r5, =KcToF          ;@ Apuntem a la constant R1 = KcToF = 1'8
		ldr r2, [r5]            ;@ Guardem la constant R1 = KcToF = 1,8
		smull r5, r6, r2, r0    ;@ Result = Q12(KcToF) * Q12(INPUT) |R6(Hi) = R2*R0 // R5(Lo) = R2*R0
		rsb r3, r1, #32         ;@ R3 = 32-12 = 20
		mov r5, r5, lsr r1      ;@ Desplaçar a la dreta part baixa
		orr r5, r6, lsl r3      ;@ Afegir a Rlo els d bits entre Rhi i Rlo
		mov r6, r6, asr r1      ;@ Desplaçar a la dreta part alta ...
                                ;@ ... mantenint el Signe
		ldr r4, =trenta2
        ldr r7, [r4]        	;@ Guardem la constant 32 R7 = 32
		add r5, r7      		;@ Guardem operacio R4 = 32+(R5)
		
		mov r0, r5       		;@ Guarderm  R0 output = (input * 9/5) + 32.0
		
		pop {r1-r7, pc}



@; Fahrenheit2Celsius(): converteix una temperatura en graus Fahrenheit a la
@;						temperatura equivalent en graus Celsius, utilitzant
@;						valors codificats en Coma Fixa 1:19:12.
@;	Entrada:
@;		input 	-> R0
@;	Sortida:
@;		R0 		-> output = (input - 32.0) * 5/9;
	.global Fahrenheit2Celsius
Fahrenheit2Celsius:
		push {r1-r6, lr}
		
		mov r5, #12				;@ Assignem el valor 12 a R5 per fer els desplaçaments
        ldr r1, =trenta2		;@ Apuntem a la constant 32
		ldr r2, [r1]			;@ Carreguem la constant 32 al registre R2
		sub r0, r2				;@ Treiem el desplaçament de l'escala Fahrenheit
		ldr r1, =KfToC			;@ Apuntem a la constant 		R1 = KfToC = 0,555
		ldr r2, [r1]			;@ Carreguem la constant 0,555 al registre R2
		smull r3, r4, r0, r2	;@ Result = Q12(INPUT-32) * Q12(0,555) |R4(Hi) = R0*R2 // R3(Lo) = R0*R2
		rsb r6, r5, #32			;@ R6 = 32-R5 = 32-12 = 20
		mov r3, r3, lsr r5		;@ Desplacem a la dreta la part baixa R3(lo)
		orr r3, r4, lsl r6		;@ Afegim a R3(lo) els bits entre R4(hi) i R3(lo)
		mov r4, r4, asr r5		;@ Desplacem a la dreta la part alta R4(hi)...
								;@ ...mantenint el signe
		mov r0, r3				;@ El resultat es retorna per R0
		
		pop {r1-r6, pc}
		
		