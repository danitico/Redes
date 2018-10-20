#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "panel.hpp"


void panel::mostrarMatriz()const{
	std::cout<<"ESTA ES LA MATRIZ EN SU ESTADO ACTUAL: \n";
	for (int i = 0; i < 10; ++i){
		for (int j = 0; j < 10; ++j){
			std::cout<<matriz2[i][j]<<" ";
		}
		std::cont<<"\n";
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


void panel::ponerBandera(char letra, int j, int ju){//por ejemplo, pos. A 3, jugador A
	char jugador;
	if(ju=1){
		jugador="A";
		if(_banderasA==20){
			std::cout<<"JUGADOR A: ya has puesto tu maximo de banderas.\n"
			return;
		}
	}else{
		jugador="B";
		if(_banderasB==20){
			std::cout<<"JUGADOR B: ya has puesto tu maximo de banderas.\n"
			return;
		}
	}

	int i;
	switch (letra){//Sacamos las coordenadas de la bandera
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
		_banderasB++;
	}

	else if((matriz2[i][j]=="B") && (jugador="A") ){
		matriz2[i][j]="AB";
		_banderasA++;
	}

	else{
		matriz2[i][j]=jugador;
		if(jugador=="A"){
			_banderasA++;
		}else{
			_banderasB++;
		}
	}

}


void panel::comprobacionCeros(int i, int j){//FUNCION AUXILIAR DE LA CLASE
	for (int i = 0; i < 10; ++i){
		for (int j = 0; j < 10; ++j){
				
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
					
					
		}
	}


}

void panel::seleccionarCasilla(char letra, int j, int ju){
	int i;
	switch (letra){//Sacamos las coordenadas de la casilla
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
		std::cout<<"Esa casilla ya ha sido seleccionada antes\n";
		return;
	}

	//Si en la casilla seleccionada hay una bomba
	if(matriz1[i][j]==-1){
		std::cout<<"BOOOOOOMM!!!!!\n";
		std::cout<<"Al jugador "<<jugador<<" le ha explotado una bomba\n";
		std::cout<<"FIN DEL JUEGO\n";
		this->mostrarMatrizFinal();//se muestra la matriz al final del juego
		return;
	}


	//Si en la casilla no hay bomba
	if(matriz1[i][j]!=-1){
		int casilla=matriz1[i][j];
		switch(casilla){
			case 0://espacio vacio
				matriz2[i][j]==0;
				//buscamos hasta donde llega el espacio vacio
				for (int i = 0; i < 10; ++i){
					for (int j = 0; j < 10; ++j){
						
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
						
						
					}
				}
			break;

			default://si hay un numero en la casilla
				matriz2[i][j]=casilla;
			break;
		}//fin switch

	}
	
}