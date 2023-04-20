@;----------------------------------------------------------------
@;  Declaració de constants GAS per al tractament de dades 
@;	en format Coma Fixa 1:19:12.
@;----------------------------------------------------------------
@;	pere.millan@urv.cat
@;	santiago.romani@urv.cat
@;	(Març 2021, Març 2022)
@;----------------------------------------------------------------

	@; MÀSCARES per als camps de bits de valors 1:19:12
MASK_SIGN = 0x80000000				@; bit 31:		signe
MASK_INT  = 0x7FFFF000				@; bits 30..12:	part entera
MASK_FRAC =	0x00000FFF				@; bits 11..0:	part fraccionària
