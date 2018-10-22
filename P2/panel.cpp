#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "panel.hpp"


std::string panel::mostrarMatriz()const{
	//std::cout<<"ESTA ES LA MATRIZ EN SU ESTADO ACTUAL: \n";
	std::string aux;
	for (int i = 0; i < 10; ++i){
		for (int j = 0; j < 10; ++j){
			aux+=" "+matriz2[i][j];
			//std::cout<<matriz2[i][j]<<" ";
		}
		aux+=";";
	}
}





void panel::rellenaMatriz(){
	srand(time(NULL));//semilla del generador de numeros aleatorios
			int k, l;
			int nbombas=20;//colocamos 20 bombas;
			while(nbombas!=0){
				k=rand()%10; //posiciones para la bomba
				l=rand()%10;
				matriz1[k][l]=-1;
				nbombas--;
			}	
			
			//ahora rellenamos los numeros de las casillas (0 incluido). Si la casilla vale 0, no hay bomba alrededor
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


std::string panel::ponerBandera(char fila, int columna, int ju){//por ejemplo, pos. A 3, jugador A
	char jugador;
	std::string aux;
	if(ju=1){
		jugador="A";
		if(_banderasA==10){
			aux="JUGADOR A: ya has puesto tu maximo de banderas.\n"

			for(int i=0;i<20<i++)
			{
				for(int k=0;k<20;k++)
				{
					if((matriz2[i][k]=="A" || matriz2[i][k]=="AB") && matriz1[i][k]!=-1)
					{
						aux=aux+"Has puesto una o varias banderas equivocadas.\n"
						aux+="HAS PERDIDO\n";
						return aux;
					}
				}
			}
			return aux;
		}
	}else{
		jugador="B";
		if(_banderasB==10){
			aux="JUGADOR B: ya has puesto tu maximo de banderas.\n"
			for(int i=0;i<20<i++)
			{
				for(int k=0;k<20;k++)
				{
					if((matriz2[i][k]=="B" || matriz2[i][k]=="AB") && matriz1[i][k]!=-1)
					{
						aux=aux+"Has puesto una o varias banderas equivocadas.\n"
						aux+="HAS PERDIDO\n";
						return aux;
					}
				}
			}
			return aux;
		}
	}

	int i;
	switch (fila){//Sacamos las coordenadas de la bandera
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
	if(matriz2[i][columna]==jugador){
		std::cout<<"Ya habias marcado esa casilla\n";
		return;
	}

	if( (matriz2[i][columna]=="A") && (jugador="B") ){
		matriz2[i][columna]="AB";
		_banderasB++;
	}

	else if((matriz2[i][columna]=="B") && (jugador="A") ){
		matriz2[i][columna]="AB";
		_banderasA++;
	}

	else{
		matriz2[i][columna]=jugador;
		if(jugador=="A"){
			_banderasA++;
		}else{
			_banderasB++;
		}
	}

}


void comprobacionCeros(int i, int j){//FUNCION AUXILIAR DE LA CLASE
	//for (int i = 0; i < 10; ++i){
	//	for (int j = 0; j < 10; ++j){
				
			if(matriz1[i-1][j]==0){
				matriz2[i-1][j]=0;
				comprobacionCeros(i-1, j);
			}else{
				matriz2[i-1][j]==matriz1[i-1][j];
			}
			if(matriz1[i-1][j-1]==0){
				matriz2[i-1][j-1]=0;
				comprobacionCeros(i-1, j-1);
			}else{
				matriz2[i-1][j-1]==matriz1[i-1][j-1];
			}
			if(matriz1[i][j-1]==0){
				matriz2[i][j-1]=0;
				comprobacionCeros(i, j-1);
			}else{
				matriz2[i][j-1]==matriz1[i][j-1];
			}
			if(matriz1[i+1][j-1]==0){
				matriz2[i+1][j-1]=0;
				comprobacionCeros(i+1, j-1);
			}else{
				matriz2[i+1][j-1]==matriz1[i+1][j-1];
			}
			if(matriz1[i+1][j]==0){
				matriz2[i+1][j]=0;
				comprobacionCeros(i+1, j);
			}else{
				matriz2[i+1][j]==matriz1[i+1][j];
			}
			if(matriz1[i+1][j+1]==0){
				matriz2[i+1][j+1]=0;
				comprobacionCeros(i+1, j+1);
			}else{
				matriz2[i+1][j+1]==matriz1[i+1][j+1];
			}
			if(matriz1[i][j+1]==0){
				matriz2[i][j+1]=0;
				comprobacionCeros(i, j+1);
			}else{
				matriz2[i][j+1]==matriz1[i][j+1];
			}
			if(matriz1[i-1][j+1]==0){
				matriz2[i-1][j-1]=0;
				comprobacionCeros(i-1, j+1);
			}else{
				matriz2[i-1][j+1]==matriz1[i-1][j+1];
			}
					
					
		//}
	//}


}

std::string panel::seleccionarCasilla(char fila, int j, int ju){
	std::string aux;
	int i;
	switch (fila){//Sacamos las coordenadas de la casilla
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


	//sacamos el numero de jugador
	char jugador;
	if(ju=1){
		jugador="A";
	}else{
		jugador="B";
	}

	//comprobamos que la casilla no ha sido ya seleccionada
	if(matriz1[i][j]!="-"){
		//std::cout<<"Esa casilla ya ha sido seleccionada antes\n";
		aux="Esa casilla ya ha sido seleccionada antes\n";
		return aux;
	}

	//Si en la casilla seleccionada hay una bomba
	if(matriz1[i][j]==-1){
		//std::cout<<"BOOOOOOMM!!!!!\n";
		aux<<"Al jugador "<<jugador<<" le ha explotado una bomba\n";
		aux+=jugador+" Ha perdido\n";
		aux+="FIN DEL JUEGO\n";
		this->mostrarMatrizFinal();//se muestra la matriz al final del juego
		return aux;
	}


	//Si en la casilla no hay bomba
	if(matriz1[i][j]!=-1){
		int casilla=matriz1[i][j];
		switch(casilla){
			case 0://espacio vacio
				matriz2[i][j]==0;
				//buscamos hasta donde llega el espacio vacio
				//for (int i = 0; i < 10; ++i){
				//	for (int j = 0; j < 10; ++j){
						
						comprobacionCeros(i, j);

						/*
							if(matriz1[i-1][j]==0){
								matriz2[i-1][j]=0;
								comprobacionCeros(i-1, j);
							}else{
								matriz2[i-1][j]==matriz1[i-1][j];
							}
							if(matriz1[i-1][j-1]==0){
								matriz2[i-1][j-1]=0;
								comprobacionCeros(i-1, j-1);
							}else{
								matriz2[i-1][j-1]==matriz1[i-1][j-1];
							}
							if(matriz1[i][j-1]==0){
								matriz2[i][j-1]=0;
								comprobacionCeros(i, j-1);
							}else{
								matriz2[i][j-1]==matriz1[i][j-1];
							}
							if(matriz1[i+1][j-1]==0){
								matriz2[i+1][j-1]=0;
								comprobacionCeros(i+1, j-1);
							}else{
								matriz2[i+1][j-1]==matriz1[i+1][j-1];
							}
							if(matriz1[i+1][j]==0){
								matriz2[i+1][j]=0;
								comprobacionCeros(i+1, j);
							}else{
								matriz2[i+1][j]==matriz1[i+1][j];
							}
							if(matriz1[i+1][j+1]==0){
								matriz2[i+1][j+1]=0;
								comprobacionCeros(i+1, j+1);
							}else{
								matriz2[i+1][j+1]==matriz1[i+1][j+1];
							}
							if(matriz1[i][j+1]==0){
								matriz2[i][j+1]=0;
								comprobacionCeros(i, j+1);
							}else{
								matriz2[i][j+1]==matriz1[i][j+1];
							}
							if(matriz1[i-1][j+1]==0){
								matriz2[i-1][j-1]=0;
								comprobacionCeros(i-1, j+1);
							}else{
								matriz2[i-1][j+1]==matriz1[i-1][j+1];
							}
							*/
						
						
				//	}
				//}
			break;

			default://si hay un numero en la casilla
				matriz2[i][j]=casilla;
			break;
		}//fin switch

	}
	
}
