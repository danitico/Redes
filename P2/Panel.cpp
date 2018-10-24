#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <stdio.h>
#include "Panel.hpp"
std::string Panel::mostrarMatriz()const{
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
void Panel::rellenaMatriz(){
	srand(time(NULL));//semilla del generador de numeros aleatorios
	int k, l;
	int nbombas=20;//colocamos 20 bombas;
	while(nbombas!=0){
		k=rand()%10; //posiciones para la bomba
		l=rand()%10;
		matriz1[k][l]=-1;
		nbombas--;
	}

	int bombasalrededor=0;
	//ahora rellenamos los numeros de las casillas (0 incluido). Si la casilla vale 0, no hay bomba alrededor
	for (int i = 0; i < 10; ++i){
		for (int j = 0; j < 10; ++j){
			if(matriz1[i][j]!=-1){//no hay una bomba
				bombasalrededor=0;
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
std::string Panel::ponerBandera(char fila, int columna, int ju){//por ejemplo, pos. A 3, jugador A
	char *jugador;
	std::string aux;
	if(ju=1){
		strcpy(jugador, "A");
		// jugador="A";
		if(_banderasA==10){
			aux="JUGADOR A: ya has puesto tu maximo de banderas.\n";
			for(int i=0;i<10;i++){//cambio el 20 del for por un 10
				for(int k=0;k<10;k++){
					//if( (strcmp(matriz2[i][k], "A")) || ( strcmp(matriz2[i][k], "AB") )    && (matriz1[i][k]!=-1) ){
					if(  (matriz2[i][k].compare("A")==0) || (matriz2[i][k].compare("AB")==0) && (matriz1[i][k]!=-1)   ){//para comparar string y que no de error al compilar	
						aux=aux + "Has puesto una o varias banderas equivocadas.\n";
						aux+="HAS PERDIDO\n";
						return aux;
					}
				}
			}
			aux+="Has colocado correctamente las 10 banderas.\n";
			aux+="Felicidades\nHAS GANADO\n";
			return aux;
		}
	}
	else{
		strcpy(jugador, "B");
		// jugador="B";
		if(_banderasB==10){
			aux="JUGADOR B: ya has puesto tu maximo de banderas.\n";
			for(int i=0;i<10;i++){//cambio el 20 del for por un 10
				for(int k=0;k<10;k++){
					//if((matriz2[i][k]=="B" || matriz2[i][k]=="AB") && matriz1[i][k]!=-1){
					if(  (matriz2[i][k].compare("B")==0) || (matriz2[i][k].compare("AB")==0) && (matriz1[i][k]!=-1)   ){
						aux= aux + "Has puesto una o varias banderas equivocadas.\n";
						aux+="HAS PERDIDO\n";
						return aux;
					}
				}
			}
			aux+="Has colocado correctamente las 10 banderas.\n";
			aux+="Felicidades\nHAS GANADO\n";
			return aux;
		}
	}

	int i;
	switch (fila){//Sacamos las coordenadas de la bandera
		case 'A':
			i=0;
		break;
		case 'B':
			i=1;
		break;
		case 'C':
			i=2;
		break;
		case 'D':
			i=3;
		break;
		case 'E':
			i=4;
		break;
		case 'F':
			i=5;
		break;
		case 'G':
			i=6;
		break;
		case 'H':
			i=7;
		break;
		case 'I':
			i=8;
		break;
		case 'J':
			i=9;
		break;
	}
	//ponemos la bandera
	if(matriz2[i][columna]==jugador){
		aux="Ya habias marcado esa casilla\n";
		//std::cout<<"Ya habias marcado esa casilla\n";
		return aux;
		
	}

	if( (matriz2[i][columna]=="A") && (jugador=="B") ){
		matriz2[i][columna]="AB";
		_banderasB++;
	}

	else if((matriz2[i][columna]=="B") && (jugador=="A") ){
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


void Panel::comprobacionCeros(int i, int j){//FUNCION AUXILIAR DE LA CLASE
	int aux;
			if(matriz1[i-1][j]==0){
				matriz2[i-1][j]=(std::string)0;
				comprobacionCeros(i-1, j);
			}else{
				aux=matriz1[i-1][j];
				matriz2[i-1][j]=aux;
				//matriz2[i-1][j]=matriz1[i-1][j];
			}
			if(matriz1[i-1][j-1]==0){
				matriz2[i-1][j-1]=(std::string)0;
				comprobacionCeros(i-1, j-1);
			}else{
				aux=matriz1[i-1][j-1];
				matriz2[i-1][j-1]=aux;
				//matriz2[i-1][j-1]=(std::string)matriz1[i-1][j-1];
			}
			if(matriz1[i][j-1]==0){
				matriz2[i][j-1]=(std::string)0;
				comprobacionCeros(i, j-1);
			}else{
				aux=matriz1[i][j-1];
				matriz2[i][j-1]=aux;
				//matriz2[i][j-1]=(std::string)matriz1[i][j-1];
			}
			if(matriz1[i+1][j-1]==0){
				matriz2[i+1][j-1]=(std::string)0;
				comprobacionCeros(i+1, j-1);
			}else{
				aux=matriz1[i+1][j-1];
				matriz2[i+1][j-1]=aux;
				//matriz2[i+1][j-1]=(std::string)matriz1[i+1][j-1];
			}
			if(matriz1[i+1][j]==0){
				matriz2[i+1][j]=(std::string)0;
				comprobacionCeros(i+1, j);
			}else{
				aux=matriz1[i+1][j];
				matriz2[i+1][j]=aux;
				//matriz2[i+1][j]=(std::string)matriz1[i+1][j];
			}
			if(matriz1[i+1][j+1]==0){
				matriz2[i+1][j+1]=(std::string)0;
				comprobacionCeros(i+1, j+1);
			}else{
				aux=matriz1[i+1][j+1];
				matriz2[i+1][j+1]=aux;
				//matriz2[i+1][j+1]=(std::string)matriz1[i+1][j+1];
			}
			if(matriz1[i][j+1]==0){
				matriz2[i][j+1]=(std::string)0;
				comprobacionCeros(i, j+1);
			}else{
				aux=matriz1[i][j+1];
				matriz2[i][j+1]=aux;
				//matriz2[i][j+1]=(std::string)matriz1[i][j+1];
			}
			if(matriz1[i-1][j+1]==0){
				matriz2[i-1][j+1]=(std::string)0;
				comprobacionCeros(i-1, j+1);
			}else{
				aux=matriz1[i-1][j+1];
				matriz2[i-1][j+1]=aux;
				//matriz2[i-1][j+1]=(std::string)matriz1[i-1][j+1];
			}


		//}
	//}


}

std::string Panel::seleccionarCasilla(char fila, int j, int ju){
	std::string aux;
	int i;
	switch (fila){//Sacamos las coordenadas de la bandera
		case 'A':
			i=0;
		break;
		case 'B':
			i=1;
		break;
		case 'C':
			i=2;
		break;
		case 'D':
			i=3;
		break;
		case 'E':
			i=4;
		break;
		case 'F':
			i=5;
		break;
		case 'G':
			i=6;
		break;
		case 'H':
			i=7;
		break;
		case 'I':
			i=8;
		break;
		case 'J':
			i=9;
		break;
	}


	//sacamos el numero de jugador
	std::string jugador;
	if(ju=1){
		jugador="A";
	}else{
		jugador="B";
	}

	//comprobamos que la casilla no ha sido ya seleccionada
	if(matriz2[i][j]!="-"){
		//std::cout<<"Esa casilla ya ha sido seleccionada antes\n";
		aux="Esa casilla ya ha sido seleccionada antes\n";
		return aux;
	}

	//Si en la casilla seleccionada hay una bomba
	if(matriz1[i][j]==-1){
		//std::cout<<"BOOOOOOMM!!!!!\n";
		aux="Al jugador " + jugador + " le ha explotado una bomba\n";
		aux+= jugador + " Ha perdido\n";
		aux+="FIN DEL JUEGO\n";
		this->mostrarMatrizFinal();//se muestra la matriz al final del juego
		return aux;
	}


	//Si en la casilla no hay bomba
	if(matriz1[i][j]!=-1){
		int casilla=matriz1[i][j];
		switch(casilla){
			case 0://espacio vacio
				matriz2[i][j]=(std::string)0;
				comprobacionCeros(i, j);
				break;

			default://si hay un numero en la casilla
				matriz2[i][j]=casilla;
				break;
		}//fin switch
	}
}
