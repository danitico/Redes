#include <iostream>
#include <cassert>
#include <stdlib.h>
#include <time.h>


void mostrarMatriz()const{
	for (int i = 0; i < 10; ++i){
		for (int j = 0; j < 10; ++j){
			
		}
	}
}





void rellenaMatriz(){
	srand(time(NULL));//semilla del generador de numeros aleatorios
			int nbombas=20;//colocamos 20 bombas;
			while(nbombas!=0){
				int k=rand()%10; //posiciones para la bomba
				int l=rand()%10;
				matriz1[k][l]=-1;
				nbombas--;
			}	
			
			//ahora rellenamos los numeros de las casillas (0 incluido)
			for (int i = 0; i < 10; ++i){
				for (int j = 0; j < 10; ++j){
					if(matriz1[i][j]!=-1){//no hay una bomba
						int bombasalrededor=0;
						if(matriz1[i-1][j]==-1){
							bombasalrededor++;
						}
						if(matriz1[i-1][j-1]==-1){
							bombasalrededor++;
						}
						if(matriz1[i][j-1]==-1){
							bombasalrededor++;
						}
						if(matriz1[i+1][j-1]==-1){
							bombasalrededor++;
						}
						if(matriz1[i+1][j]==-1){
							bombasalrededor++;
						}
						if(matriz1[i+1][j+1]==-1){
							bombasalrededor++;
						}
						if(matriz1[i][j+1]==-1){
							bombasalrededor++;
						}
						if(matriz1[i-1][j+1]==-1){
							bombasalrededor++;
						}
					}
					matriz1[i][j]=bombasalrededor;//establezco el numero de bombas alrededor
				}


			}
}


void ponerBandera(char letra, int j, int ju){
	char jugador;
	if(ju=1){
		jugador="A";
		if(banderasA==20){
			std::cout<<"JUGADOR A: ya has puesto tu maximo de banderas"
			return;
		}
	}else{
		jugador="B";
		if(banderasB==20){
			std::cout<<"JUGADOR B: ya has puesto tu maximo de banderas"
			return;
		}
	}

	int i;
	switch (i){//Sacamos las coordenadas de la bandera
		case "A":
			i=0;
		break;
		case "B":
			i=1;
		break;
		case "C":
			i=2;
		break;
		case "D":
			i=3;
		break;
		case "E":
			i=4;
		break;
		case "F":
			i=5;
		break;
		case "G":
			i=6;
		break;
		case "H":
			i=7;
		break;
		case "I":
			i=8;
		break;
		case "J":
			i=9;
		break;
	}
	//ponemos la bandera
	if(matriz2[i][j]==jugador){
		std::cout<<"Ya habias marcado esa casilla\n";
		return;
	}
	if( (matriz2[i][j]=="A") && (jugador="B") ){
		matriz2[i][j]="AB";
	}else{
		matriz2[i][j]=jugador;
	}



}