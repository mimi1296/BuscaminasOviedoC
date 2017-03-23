
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Juego buscaminas en C.
//--------------------------------------//
//Creacion de la matriz//
struct casilla
{
	char etiqueta;
	int nMinas;
	char tipo;
};

typedef struct casilla tipoCasilla;

tipoCasilla **crearCuadro(int f,int c){
	tipoCasilla **mat=(tipoCasilla **)malloc(f*sizeof(tipoCasilla*));
	int i;
	for (i=0;i<f; i++){

		mat[i]=(tipoCasilla *)malloc(c*sizeof(tipoCasilla));
	}
	return mat;
}

tipoCasilla **llenarCuadro(tipoCasilla **mat, int f, int c){
	int i,j;
	for (i = 0; i<f;i++){
		for (j=0;j<c;j++){
			mat[i][j].etiqueta = 'x'; 	// los cuadros son representados con una x
			mat[i][j].tipo = 'c';
			mat[i][j].nMinas = 0;
		}
	}
	return mat;
}

//Imprimir cuadro:
void **imprimir(tipoCasilla **matriz, int f,int c){
	int i,j;
	printf ("    ");
	for(j=0;j<c;j++){
		printf ("  %d  ",j);
	}
	printf ("\n");
	for (i = 0; i<f;i++){
		printf ("  %d ",i);
		for (j=0;j<c;j++){
			printf("| %c |", matriz[i][j].etiqueta);
		}
		printf("\n");
	}
}

void colocarMinas(int f, int c, tipoCasilla **mat, int n){
	int posFil, posCol, m;
	srand(time(NULL));
	m =0;
	while (m<n){
		posFil = rand() % f;
		posCol = rand() % c;
		if (mat[posFil][posCol].tipo != 'm'){
            m++;
            }
	mat[posFil][posCol].tipo = 'm';
	}
}

void colocarNumeros(int f, int c, tipoCasilla **mat){
	int i,j;
	for (i = 0; i<f;i++){
		for (j=0;j<c;j++){
			if  (mat[i][j].tipo == 'm'){
				mat[i][j].nMinas = 0;
			}else{
				if(i == 0 && j == 0){      //Esquina superior izq.//
					if(mat[i+1][j].tipo == 'm'){  // abajo
						mat[i][j].nMinas= mat[i][j].nMinas + 1;
					}else{
						if(mat[i+1][j+1].tipo == 'm'){ //abajo derecha
							mat[i][j].nMinas= mat[i][j].nMinas + 1;
						}else{
							if(mat[i][j+1].tipo == 'm'){  // derecha
								mat[i][j].nMinas= mat[i][j].nMinas + 1;
							}
						}
					}
				}else{
					if(i ==0  && j == c-1){  // esquina superior der.//
						if(mat[i][j-1].tipo == 'm'){  // izq.
							mat[i][j].nMinas= mat[i][j].nMinas + 1;
						}
						if(mat[i+1][j-1].tipo == 'm'){ //abajo izq.
							mat[i][j].nMinas= mat[i][j].nMinas + 1;
						}
						if(mat[i+1][j].tipo == 'm'){  // abajo
							mat[i][j].nMinas= mat[i][j].nMinas + 1;
						}


					}else{
						if(i == f-1 && j ==0){ //Esquina inferior izq.//
							if(mat[i-1][j].tipo == 'm'){  // arriba
								mat[i][j].nMinas= mat[i][j].nMinas + 1;
							}
							if(mat[i-1][j+1].tipo == 'm'){  // arriba der.
								mat[i][j].nMinas= mat[i][j].nMinas + 1;
							}
							if(mat[i][j+1].tipo == 'm'){ // derecha.
								mat[i][j].nMinas= mat[i][j].nMinas + 1;
							}
						}else{
							if(i == (f-1) && j == (c-1)){ // Esquina inferior der.//
								if(mat[i][j-1].tipo == 'm'){  // izq.
									mat[i][j].nMinas= mat[i][j].nMinas + 1;
								}
								if(mat[i-1][j-1].tipo == 'm'){  // arriba izq.
									mat[i][j].nMinas= mat[i][j].nMinas + 1;
								}
								if(mat[i-1][j].tipo == 'm'){ // arriba
									mat[i][j].nMinas= mat[i][j].nMinas + 1;
								}
							}else{
								if((i==0)&&(j>0 && j<(c-1))){ //Primera fila columnas intermedias//
									if(mat[i][j-1].tipo == 'm'){ //izq
										mat[i][j].nMinas= mat[i][j].nMinas + 1;
									}
									if(mat[i+1][j-1].tipo == 'm'){  //abajo izq
										mat[i][j].nMinas= mat[i][j].nMinas + 1;
									}
									if(mat[i+1][j].tipo == 'm'){  //abajo
										mat[i][j].nMinas= mat[i][j].nMinas + 1;
									}
									if(mat[i+1][j+1].tipo == 'm'){ 	//abajo der
										mat[i][j].nMinas= mat[i][j].nMinas + 1;
									}
									if(mat[i][j+1].tipo == 'm'){
										mat[i][j].nMinas= mat[i][j].nMinas + 1;
									}
								}else{
									if((i > 0 && i < f-1) && j==0){ 	//primera columna filas intermedias
										if(mat[i-1][j].tipo == 'm'){ // arriba
											mat[i][j].nMinas= mat[i][j].nMinas + 1;
										}
										if(mat[i-1][j+1].tipo == 'm'){ //arriba der
											mat[i][j].nMinas= mat[i][j].nMinas + 1;
										}
										if(mat[i][j+1].tipo == 'm'){	//der
											mat[i][j].nMinas= mat[i][j].nMinas + 1;
										}
										if(mat[i+1][j+1].tipo == 'm'){ //der abajo
											mat[i][j].nMinas= mat[i][j].nMinas + 1;
										}
										if(mat[i+1][j].tipo == 'm'){ // abajo
											mat[i][j].nMinas= mat[i][j].nMinas + 1;
										}
									}else{
										if((i>0 && i<f-1) && j== c-1){ //Ultima columna filas intermedias
											if(mat[i-1][j].tipo == 'm'){ // arriba
												mat[i][j].nMinas= mat[i][j].nMinas + 1;
											}
											if(mat[i-1][j-1].tipo == 'm'){ // arriba izq
												mat[i][j].nMinas= mat[i][j].nMinas + 1;
											}
											if(mat[i][j-1].tipo == 'm'){ // izq
												mat[i][j].nMinas= mat[i][j].nMinas + 1;
											}
											if(mat[i+1][j-1].tipo == 'm'){ // abajo izq
												mat[i][j].nMinas= mat[i][j].nMinas + 1;
											}
											if(mat[i+1][j].tipo == 'm'){ // arriba
												mat[i][j].nMinas= mat[i][j].nMinas + 1;
											}
										}else{
											if(i== f-1 &&(j>0 && j< c-1)){ //ultima fila columnas inermedias//
												if(mat[i][j-1].tipo == 'm'){ // izq
													mat[i][j].nMinas= mat[i][j].nMinas + 1;
												}
												if(mat[i-1][j-1].tipo == 'm'){ // arriba izq
													mat[i][j].nMinas= mat[i][j].nMinas + 1;
												}
												if(mat[i-1][j].tipo == 'm'){ // arriba
													mat[i][j].nMinas= mat[i][j].nMinas + 1;
												}
												if(mat[i-1][j+1].tipo == 'm'){ // arriba der
													mat[i][j].nMinas= mat[i][j].nMinas + 1;
												}
												if(mat[i][j+1].tipo == 'm'){ // der
													mat[i][j].nMinas= mat[i][j].nMinas + 1;
												}

											}else{
												if((i>0 && j>0) &&(i< f-1 && j <c-1)){  // centro//
													if(mat[i][j-1].tipo == 'm'){ // izq
														mat[i][j].nMinas= mat[i][j].nMinas + 1;
													}
													if(mat[i-1][j-1].tipo == 'm'){ // arriba izq
														mat[i][j].nMinas= mat[i][j].nMinas + 1;
													}
													if(mat[i-1][j].tipo == 'm'){ // arriba
														mat[i][j].nMinas= mat[i][j].nMinas + 1;
													}
													if(mat[i-1][j+1].tipo == 'm'){ // arriba der
														mat[i][j].nMinas= mat[i][j].nMinas + 1;
													}
													if(mat[i][j+1].tipo == 'm'){ // der
														mat[i][j].nMinas= mat[i][j].nMinas + 1;
													}
													if(mat[i+1][j+1].tipo == 'm'){ // der abajo
														mat[i][j].nMinas= mat[i][j].nMinas + 1;
													}
													if(mat[i+1][j].tipo == 'm'){ // abajo
														mat[i][j].nMinas= mat[i][j].nMinas + 1;
													}
													if(mat[i+1][j-1].tipo == 'm'){ // abajo izq
														mat[i][j].nMinas= mat[i][j].nMinas + 1;
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void AbrirNum(tipoCasilla **mat,int f, int c, int i, int j){
		if(i == 0 && j == 0){      //Esquina superior izq.//
			if(mat[i+1][j].tipo != 'm' && mat[i+1][j].etiqueta == 'x'){  // abajo
				mat[i+1][j].etiqueta= mat[i+1][j].nMinas + 48;
				if(mat[i+1][j].nMinas  == 0){
					AbrirNum(mat,f,c,i+1,j);
				}
			}
			if(mat[i+1][j+1].tipo != 'm'&& mat[i+1][j+1].etiqueta == 'x'){ //abajo derecha
				mat[i+1][j+1].etiqueta= mat[i+1][j+1].nMinas + +48;
				if(mat[i+1][j+1].nMinas == 0){
				 	AbrirNum(mat,f,c,i+1,j+1);
				}
			}
			if(mat[i][j+1].tipo != 'm'&& mat[i][j+1].etiqueta == 'x'){  // derecha
				mat[i][j+1].etiqueta= mat[i][j+1].nMinas + 48;
				if(mat[i][j+1].nMinas == 0){
					AbrirNum(mat,f,c,i,j+1);
				}
			}
		}else{
			if(i ==0  && j == c-1){  // esquina superior der.//
				if(mat[i][j-1].tipo != 'm' && mat[i][j-1].etiqueta == 'x'){  // izq.
					mat[i][j-1].etiqueta= mat[i][j-1].nMinas + 48;
					if(mat[i][j-1].nMinas == 0){
						AbrirNum(mat,f,c,i,j-1);
					}
				}
				if(mat[i+1][j-1].tipo != 'm' && mat[i+1][j-1].etiqueta == 'x'){ //abajo izq.
					mat[i+1][j-1].etiqueta= mat[i+1][j-1].nMinas + 48;
					if(mat[i][j-1].nMinas == 0){
						AbrirNum(mat,f,c,i+1,j-1);
					}
				}
				if(mat[i+1][j].tipo != 'm' && mat[i+1][j].etiqueta == 'x'){  // abajo
					mat[i+1][j].etiqueta= mat[i+1][j].nMinas+48;
					if(mat[i+1][j].nMinas == 0){
						AbrirNum(mat,f,c,i+1,j);
					}
				}

			}else{
				if(i == f-1 && j ==0){ //Esquina inferior izq.//
					if(mat[i-1][j].tipo != 'm' && mat[i-1][j].etiqueta == 'x'){  // arriba
						mat[i-1][j].etiqueta= mat[i-1][j].nMinas+ 48;
						if(mat[i-1][j].nMinas == 0){
							AbrirNum(mat,f,c,i-1,j);
						}
					}
					if(mat[i-1][j+1].tipo != 'm'){  // arriba der.
						mat[i-1][j+1].etiqueta= mat[i-1][j+1].nMinas +48;
						if(mat[i-1][j+1].nMinas == 0){
							AbrirNum(mat,f,c,i-1,j+1);
						}
					}
					if( mat[i][j+1].tipo != 'm' && mat[i][j+1].etiqueta == 'x'){ // derecha.
						mat[i][j+1].etiqueta= mat[i][j+1].nMinas +48;
						if(mat[i][j+1].nMinas == 0){
							AbrirNum(mat,f,c,i,j+1);
						}
					}
				}else{
					if(i == (f-1) && j == (c-1)){ // Esquina inferior der.//
						if(mat[i][j-1].tipo != 'm' && mat[i][j-1].etiqueta == 'x'){ //izq
							mat[i][j-1].etiqueta=mat[i][j-1].nMinas+48;
							if(mat[i][j-1].nMinas == 0){
								AbrirNum(mat,f,c,i,j-1);
							}
						}
						if(mat[i-1][j-1].tipo != 'm'&& mat[i-1][j-1].etiqueta == 'x'){  // arriba izq.
							mat[i-1][j-1].etiqueta= mat[i-1][j-1].nMinas + 48;
							if(mat[i-1][j-1].nMinas == 0){
								AbrirNum(mat,f,c,i-1,j-1);
							}
						}
						if(mat[i-1][j].tipo != 'm' && mat[i-1][j].etiqueta == 'x'){ // arriba
							mat[i-1][j].etiqueta = mat[i-1][j].nMinas + 48;
							if(mat[i-1][j].nMinas == 0){
								AbrirNum(mat,f,c,i-1,j);
							}
						}
					}else{
						if((i==0)&&(j>0 && j<(c-1))){ //Primera fila columnas intermedias//
							if(mat[i][j-1].tipo != 'm' && mat[i][j-1].etiqueta == 'x'){ //izq
								mat[i][j-1].etiqueta=mat[i][j-1].nMinas+48;
								if(mat[i][j-1].nMinas == 0){
									AbrirNum(mat,f,c,i,j-1);
								}
							}
							if(mat[i+1][j-1].tipo != 'm' && mat[i+1][j-1].etiqueta == 'x'){  //abajo izq
								mat[i+1][j-1].etiqueta= mat[i+1][j-1].nMinas+48;
								if(mat[i+1][j-1].nMinas == 0){
									AbrirNum(mat,f,c,i+1,j-1);
								}
							}
							if(mat[i+1][j].tipo != 'm' && mat[i+1][j].etiqueta == 'x'){  //abajo
								mat[i+1][j].etiqueta= mat[i+1][j].nMinas + 48;
								if(mat[i+1][j].nMinas == 0){
									AbrirNum(mat,f,c,i+1,j);
								}
							}
							if(mat[i+1][j+1].tipo != 'm' && mat[i+1][j+1].etiqueta == 'x'){ 	//abajo der
								mat[i+1][j+1].etiqueta= mat[i+1][j+1].nMinas +48;
								if(mat[i+1][j+1].nMinas == 0){
									AbrirNum(mat,f,c,i+1,j+1);
								}
							}
							if(mat[i][j+1].tipo != 'm' && mat[i][j+1].etiqueta == 'x'){
								mat[i][j+1].etiqueta= mat[i][j+1].nMinas+48;
								if(mat[i][j+1].nMinas == 0){
									AbrirNum(mat,f,c,i,j+1);
								}
							}
						}else{
							if((i > 0 && i < f-1) && j==0){ 	//primera columna filas intermedias
								if(mat[i-1][j].tipo != 'm' && mat[i-1][j].etiqueta == 'x'){ // arriba
									mat[i-1][j].etiqueta= mat[i-1][j].nMinas + 48;
									if(mat[i-1][j].nMinas == 0){
										AbrirNum(mat,f,c,i-1,j);
									}
								}
								if(mat[i-1][j+1].tipo != 'm' && mat[i-1][j+1].etiqueta == 'x'){ //arriba der
									mat[i-1][j+1].etiqueta= mat[i-1][j+1].nMinas + 48;
									if(mat[i-1][j+1].nMinas == 0){
										AbrirNum(mat,f,c,i-1,j+1);
									}
								}
								if(mat[i][j+1].tipo != 'm' && mat[i][j+1].etiqueta == 'x'){	//der
									mat[i][j+1].etiqueta= mat[i][j+1].nMinas + 48;
									if(mat[i][j+1].nMinas == 0){
										AbrirNum(mat,f,c,i,j+1);
									}
								}
								if(mat[i+1][j+1].tipo != 'm' && mat[i+1][j+1].etiqueta == 'x'){ //der abajo
									mat[i+1][j+1].etiqueta= mat[i+1][j+1].nMinas + 48;
									if(mat[i+1][j+1].nMinas == 0){
										AbrirNum(mat,f,c,i+1,j+1);
									}
								}
								if(mat[i+1][j].tipo != 'm' && mat[i+1][j].etiqueta == 'x'){ // abajo
									mat[i+1][j].etiqueta= mat[i+1][j].nMinas + 48;
									if(mat[i+1][j].nMinas == 0){
										AbrirNum(mat,f,c,i+1,j);
									}
								}
							}else{
								if((i>0 && i<f-1) && j== c-1){ //Ultima columna filas intermedias
									if(mat[i-1][j].tipo != 'm' && mat[i-1][j].etiqueta == 'x'){ // arriba
										mat[i-1][j].etiqueta= mat[i-1][j].nMinas + 48;
										if(mat[i-1][j].nMinas == 0){
											AbrirNum(mat,f,c,i-1,j);
										}
									}
									if(mat[i-1][j-1].tipo != 'm' && mat[i-1][j-1].etiqueta == 'x'){ // arriba izq
										mat[i-1][j-1].etiqueta= mat[i-1][j-1].nMinas + 48;
										if(mat[i-1][j-1].nMinas == 0){
											AbrirNum(mat,f,c,i-1,j-1);
										}
									}
									if(mat[i][j-1].tipo != 'm' && mat[i][j-1].etiqueta == 'x'){ // izq
										mat[i][j-1].etiqueta= mat[i][j-1].nMinas + 48;
										if(mat[i][j-1].nMinas == 0){
											AbrirNum(mat,f,c,i,j-1);
										}
									}
									if(mat[i+1][j-1].tipo != 'm' && mat[i+1][j-1].etiqueta == 'x'){ // abajo izq
										mat[i+1][j-1].etiqueta= mat[i+1][j-1].nMinas + 48;
										if(mat[i+1][j-1].nMinas == 0){
											AbrirNum(mat,f,c,i+1,j-1);
										}
									}
									if(mat[i+1][j].tipo != 'm' && mat[i+1][j].etiqueta == 'x'){ // arriba
										mat[i+1][j].etiqueta= mat[i+1][j].nMinas + 48;
										if(mat[i+1][j].nMinas == 0){
											AbrirNum(mat,f,c,i+1,j);
										}
									}
								}else{
									if(i== f-1 &&(j>0 && j< c-1)){ //ultima fila columnas inermedias//
										if(mat[i][j-1].tipo != 'm' && mat[i][j-1].etiqueta == 'x'){ // izq
											mat[i][j-1].etiqueta= mat[i][j-1].nMinas + 48;
											if(mat[i][j-1].nMinas == 0){
												AbrirNum(mat,f,c,i,j-1);
											}
										}
										if(mat[i-1][j-1].tipo != 'm' && mat[i-1][j-1].etiqueta == 'x'){ // arriba izq
											mat[i-1][j-1].etiqueta= mat[i-1][j-1].nMinas + 48;
											if(mat[i-1][j-1].nMinas == 0){
												AbrirNum(mat,f,c,i-1,j-1);
											}
										}
										if(mat[i-1][j].tipo != 'm' && mat[i-1][j].etiqueta == 'x'){ // arriba
											mat[i-1][j].etiqueta= mat[i-1][j].nMinas + 48;
											if(mat[i-1][j].nMinas == 0){
												AbrirNum(mat,f,c,i-1,j);
											}
										}
										if(mat[i-1][j+1].tipo != 'm' && mat[i-1][j+1].etiqueta == 'x'){ // arriba der
											mat[i-1][j+1].etiqueta= mat[i-1][j+1].nMinas + 48;
											if(mat[i-1][j+1].nMinas == 0){
												AbrirNum(mat,f,c,i-1,j+1);
											}
										}
										if(mat[i][j+1].tipo != 'm' && mat[i][j+1].etiqueta == 'x'){ // der
											mat[i][j+1].etiqueta= mat[i][j+1].nMinas + 48;
											if(mat[i][j+1].nMinas == 0){
												AbrirNum(mat,f,c,i,j+1);
											}
										}

									}else{
										if((i>0 && j>0) &&(i< f-1 && j <c-1)){  // centro//
											if(mat[i][j-1].tipo != 'm' && mat[i][j-1].etiqueta == 'x'){ // izq
												mat[i][j-1].etiqueta= mat[i][j-1].nMinas + 48;
												if(mat[i][j-1].nMinas == 0){
													AbrirNum(mat,f,c,i,j-1);
												}
											}
											if(mat[i-1][j-1].tipo != 'm' && mat[i-1][j-1].etiqueta == 'x'){ // arriba izq
												mat[i-1][j-1].etiqueta= mat[i-1][j-1].nMinas +48;
												if(mat[i-1][j-1].nMinas == 0){
													AbrirNum(mat,f,c,i-1,j-1);
												}
											}
											if(mat[i-1][j].tipo != 'm' && mat[i-1][j].etiqueta == 'x'){ // arriba
												mat[i-1][j].etiqueta= mat[i-1][j].nMinas + 48;
												if(mat[i-1][j].nMinas == 0){
													AbrirNum(mat,f,c,i-1,j);
												}	
											}
											if(mat[i-1][j+1].tipo != 'm' && mat[i-1][j+1].etiqueta == 'x'){ // arriba der
												mat[i-1][j+1].etiqueta= mat[i-1][j+1].nMinas + 48;
												if(mat[i-1][j+1].nMinas == 0){
													AbrirNum(mat,f,c,i-1,j+1);
												}
											}
											if(mat[i][j+1].tipo != 'm' && mat[i][j+1].etiqueta == 'x'){ // der
												mat[i][j+1].etiqueta= mat[i][j+1].nMinas + 48;
												if(mat[i][j+1].nMinas == 0){
													AbrirNum(mat,f,c,i,j+1);
												}
											}
											if(mat[i+1][j+1].tipo != 'm' && mat[i+1][j+1].etiqueta == 'x'){ // der abajo
												mat[i+1][j+1].etiqueta= mat[i+1][j+1].nMinas + 48;
												if(mat[i+1][j+1].nMinas == 0){
													AbrirNum(mat,f,c,i+1,j+1);
												}
											}
											if(mat[i+1][j].tipo != 'm' && mat[i+1][j].etiqueta == 'x'){ // abajo
												mat[i+1][j].etiqueta= mat[i+1][j].nMinas + 48;
												if(mat[i+1][j].nMinas == 0){
													AbrirNum(mat,f,c,i+1,j);
												}
											}
											if(mat[i+1][j-1].tipo != 'm' && mat[i+1][j-1].etiqueta == 'x'){ // abajo izq
												mat[i+1][j-1].etiqueta= mat[i+1][j-1].nMinas + 48;
												if(mat[i+1][j-1].nMinas == 0){
												 	AbrirNum(mat,f,c,i+1,j-1);
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	
}

void AbrirMin(tipoCasilla **mat, int f, int c, int x , int y){
	int i, j;
	for(i=0;i<f;i++){
		for (j=0;j<c;j++){
			
			if (mat[i][j].tipo == 'm'){
				mat[i][j].etiqueta = 'm';
			}
			if ((i==x) && (j == y)){
				if(mat[i][j].tipo == 'm'){
					mat[i][j].etiqueta = 'M';
				}
				if(mat[i][j].tipo == 'c'){
					mat[i][j].etiqueta = 'x';
				}
				
			}
		}
	}
	imprimir(mat,f,c);
}

void jugar(tipoCasilla **mat,int f,int c,int minas){
	int i,a,b,x,y;
	char z;
	int contM;
	contM = minas;
	printf("contador inicial: %i", contM);

	while (i>0){
		printf("\nIngrese FILA COLUMNA BANDERA \n");
		scanf("%d %d %c",&x,&y,&z);
		if (mat[x][y].tipo == 'm' && z != 'f'){
			AbrirMin(mat,f,c,x,y);
			printf("%s\n", "PERDISTE |(");
			break;
		}else{ 
			if (z == 'f'){
				if (mat[x][y].etiqueta == 'x'){
					mat[x][y].etiqueta ='f';
					if(mat[x][y].tipo == 'c'){
						contM = contM +1;
					}
					if(mat[x][y].tipo == 'm'){
						contM = contM -1;
						if(contM == 0){
							AbrirMin(mat,f,c,x,y);
							printf("%s\n", "GANASTE :)");
							break;
						}
					}
				}else{
					if(mat[x][y].etiqueta == 'f'){
						mat[x][y].etiqueta ='x';
						if(mat[x][y].tipo == 'c'){
							contM = contM -1;
							if(contM == 0){
								AbrirMin(mat,f,c,x,y);
								printf("%s\n", "GANASTE :) ");
								break;
							}
						}
						if(mat[x][y].tipo == 'm'){
							contM = contM +1;
						}
					}
				}	
			}else{
				if (mat[x][y].tipo == 'c'){
					mat[x][y].etiqueta=mat[x][y].nMinas+48;
					if(mat[x][y].nMinas == 0){
						AbrirNum(mat, f,c,x,y);
					}
				}
		    	}
		    
		 }	
		imprimir(mat, f,c);
	}
}


void main(int argc, char *argv[]){
	int f = atoi(argv[1]);
	int c = atoi(argv[2]);
	int min = atoi(argv[3]);
	tipoCasilla **Cuadro;
	tipoCasilla **Cuadro2;
	Cuadro = crearCuadro(f,c);
	Cuadro2 =  llenarCuadro(Cuadro, f,c);
	colocarMinas(f,c,Cuadro2,min);
	colocarNumeros(f,c,Cuadro2);
	imprimir(Cuadro2, f,c);
	jugar(Cuadro2,f,c,min);




}
