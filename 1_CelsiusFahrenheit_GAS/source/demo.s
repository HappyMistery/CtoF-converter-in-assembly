@;-----------------------------------------------------------------------
@;   Description: a program to check the temperature-scale conversion
@;				functions implemented in "CelsiusFahrenheit.c".
@;	IMPORTANT NOTE: there is a much confident testing set implemented in
@;				"tests/test_CelsiusFahrenheit.c"; the aim of "demo.s" is
@;				to show how would it be a usual main() code invoking the
@;				mentioned functions.
@;-----------------------------------------------------------------------
@;	Author: Santiago Romani (DEIM, URV)
@;	Date:   March/2022 
@;----------------------------------------------------------------
@;	Programador/a 1: nil.monfort@estudiants.urv.cat
@;	Programador/a 2: jaume.tello@estudiants.urv.cat
@;----------------------------------------------------------------*/

.data
		.align 2
	temp1C:	.word 0x0002335C		@; temp1C = 35.21 ºC
	temp2F:	.word 0xFFFE8400		@; temp2F = -23.75 ºF

.bss
		.align 2
	temp1F:	.space 4				@; expected conversion:  95.379638671875 ºF
	temp2C:	.space 4				@; expected conversion: -30.978271484375 ºC


.text
		.align 2
		.arm
		.global main
main:
		push {r0, r1, lr}
		
			@; temp1F = Celsius2Fahrenheit(temp1C);
		ldr r1, =temp1C			;@Apuntem a la variable temp1C      R0=temp1C
		ldr r0, [r1]			;@Passem el valor de temp1C com a parametre 
		bl Celsius2Fahrenheit	;@Cridem la rutina (resultat retornat per R0)
		ldr r1, =temp1F			;@Apuntem a la variable temp1F      R1=temp1F
		str r0, [r1]			;@Guardem el resultat de la rutina a temp1F
		
			@; temp2C = Fahrenheit2Celsius(temp2F);
		ldr r1, =temp2F			;@Apuntem a la variable temp1C      R0=temp2F
		ldr r0, [r1]			;@Passem el valor de temp2F com a parametre
		bl Fahrenheit2Celsius	;@Cridem la rutina (resultat retornat per R0)
		ldr r1, =temp2C			;@Apuntem a la variable temp2C      R1=temp2C
		str r0, [r1]			;@Guardem el resultat de la rutina a temp2C

@; TESTING POINT: check the results
@;	(gdb) p /x temp1F		-> 0x0005F613
@;	(gdb) p /x temp2C		-> 0xFFFE1059
@; BREAKPOINT
		mov r0, #0					@; return(0)
		
		pop {r0, r1, pc}

.end

