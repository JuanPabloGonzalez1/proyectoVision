El formato de los archivos .dat es el siguiente:

======================
===== datosX.dat =====

	M	N
	x_1	x_2	...	x_N
	x_1	x_2	...	x_N
	.	.
	.		.
	.			.
	x_1	x_2	...	x_N	(Ejemplo M)


======================
===== datosY.dat =====

	y_1
	y_2
	.
	.
	.
	y_M

donde M es el número de ejemplos y N es la dimensión del vector ejemplo x.

IMPORTANTE:

Los primeros m/2 ejemplos deben ser del mismo tipo y los restantes m/2 del otro tipo.
Por ejemplo, si los primeros m/2 ejemplos son positivos, los restantes m/2 deben ser negativos.
Por lo tanto se requiere contar con el mismo número de ejemplos positivos (m/2) y negativos (m/2).

