#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <stdio.h>
#include "Panel.hpp"
std::string Panel::mostrarMatriz()const
{
	std::string aux;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
			aux+=" "+matriz2[i][j];
		
		aux+="\n";
	}

	return aux;
}
void Panel::rellenaMatriz(){
	srand(time(NULL));//semilla del generador de numeros aleatorios
	int k, l;
	int nbombas=20;//colocamos 20 bombas;
	while(nbombas!=0){
		k=rand()%10; //posiciones para la bomba
		l=rand()%10;

		if(matriz1[k][l]!=-1) //solo se puede poner una bomba en cada casilla
		{
			matriz1[k][l]=-1;
			nbombas--;
		}
	}
	busquedaBombas();
}
void Panel::obtenerBombas(int i, int j, int r=1){
   int j_izquierda=j-1;
   int j_derecha=j+1;
   int contador1=-1;
   int contador2=0;
   int contador3=0;
   int contador4=0;

   for(int inicio=i; inicio>=0; inicio--){
      if(contador1 < r){
			if(inicio != i && matriz1[inicio][j]==-1){
				matriz1[i][j]+=1;
			}

         contador2=0;
         j_izquierda=j-1;
         while(contador2 < r && j_izquierda>=0){
				if(matriz1[inicio][j_izquierda]==-1){
					matriz1[i][j]+=1;
				}
				j_izquierda--;
            contador2++;
         }
         contador3=0;
         j_derecha=j+1;

         while(contador3 < r && j<10){
				if(matriz1[inicio][j_derecha]==-1){
					matriz1[i][j]+=1;
				}
            j_derecha++;
            contador3++;
         }
         contador1++;
      }
      else{
         break;
      }
   }

   for(int inicio=i+1; inicio < 10; inicio++){
      if(contador4 < r){
			if(matriz1[inicio][j]==-1){
				matriz1[i][j]+=1;
			}

         contador2=0;
         j_izquierda=j-1;
         while(contador2 < r && j_izquierda>=0){
				if(matriz1[inicio][j_izquierda]==-1){
					matriz1[i][j]+=1;
				}
            j_izquierda--;
            contador2++;
         }
         contador3=0;
         j_derecha=j+1;

         while(contador3 < r && j_derecha < 10){
				if(matriz1[inicio][j_derecha]==-1){
					matriz1[i][j]+=1;
				}
            j_derecha++;
            contador3++;
         }
         contador4++;
      }
      else{
         break;
      }
   }
}
void Panel::busquedaBombas()
{
	//ahora rellenamos los numeros de las casillas (0 incluido). Si la casilla vale 0, no hay bomba alrededor
	for(int i=0; i<10; i++)
		for(int j=0; j<10; j++)
			if(matriz1[i][j]!=-1)
				obtenerBombas(i, j);
}
int Panel::traduccionFila(char fila){
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
	return i;
}
bool Panel::comprobarBanderas(int socket){
	if(getSocket1()==socket)
	{
		for(int i=0;i<10;i++)
		{
			for(int k=0;k<10;k++)
			{
				if((matriz2[i][k].compare("A")==0 || matriz2[i][k].compare("AB")==0) && matriz1[i][k]!=-1)//para comparar string y que no de error al compilar
					return false;
			}
		}
		return true;
	}
	else
	{
		for(int i=0;i<10;i++)
		{
			for(int k=0;k<10;k++)
			{
				if((matriz2[i][k].compare("B")==0 || matriz2[i][k].compare("AB")==0) && (matriz1[i][k]!=-1))
					return false;
			}
		}
		return true;
	}
}
std::string Panel::ponerBandera(int fila, char * columna_letra, int socket, std::map<int, std::string> & usuarios){//por ejemplo, pos. A 3, jugador A
	std::string jugador;
	std::string aux="";
	int columna=traduccionFila(columna_letra[0]);

	if(getSocket1()==socket){
		jugador='A';
	}
	else{
		jugador='B';
	}

	//ponemos la bandera
	// if(matriz2[fila][columna]==jugador){
	// 	aux="Ya habias marcado esa casilla\n";
	// 	return aux;
	// }

	if(matriz2[fila][columna]=="A" && jugador=="B"){
		matriz2[fila][columna]="AB";
		_banderasB++;
	}
	else if(matriz2[fila][columna]=="B" && jugador=="A"){
		matriz2[fila][columna]="AB";
		_banderasA++;
	}
	else{
		matriz2[fila][columna]=jugador;
		if(getSocket1()==socket){
			_banderasA++;
		}
		else{
			_banderasB++;
		}
	}

	if(getbanderasA()==10 || getbanderasB()==10){
		if(comprobarBanderas(socket)){
			aux="+Ok. " + usuarios[socket] + " ha ganado.\n";
		}
		else{
			aux="+Ok. " + usuarios[socket] + " ha perdido.\n";
		}
	}

	return aux;
}
void Panel::comprobacionCeros(int i, int j){//FUNCION AUXILIAR DE LA CLASE
	visitados[i][j]=true;
	if(i!=0 && matriz1[i-1][j]==0 && !visitados[i-1][j]){
		//Si en esa casilla hay un cero, lo descubro y si la i ya es cero, no puedo entrar, me saldria de la matriz
		matriz2[i-1][j]='0';
		//llamo otra vez a la funcion para ver si hay mas ceros
		comprobacionCeros(i-1, j);
	}
	else{
		//Si no hay un cero, le pongo el numero correspondiente a la matriz de juego (matriz2) segun la matriz interna del programa (matriz1)
		//para no salirme de la matriz
		if(i!=0){
			matriz2[i-1][j]=std::to_string(matriz1[i-1][j]);
		}//POR DIOS, NO ME QUITES LOS CORCHETES, QUE ME LIO :D
	}

	if(i!=0 && j!=0 && matriz1[i-1][j-1]==0 && !visitados[i-1][j-1]){
		matriz2[i-1][j-1]='0';
		comprobacionCeros(i-1, j-1);
	}
	else{
		if(i!=0 && j!=0){
			matriz2[i-1][j-1]=std::to_string(matriz1[i-1][j-1]);
		}
	}
	if(j!=0 && matriz1[i][j-1]==0 && !visitados[i][j-1]){
		matriz2[i][j-1]='0';
		comprobacionCeros(i, j-1);
	}
	else{
		if(j!=0){
			matriz2[i][j-1]=std::to_string(matriz1[i][j-1]);
		}
	}
	if(j!=0 && i!=9 && matriz1[i+1][j-1]==0 && !visitados[i+1][j-1]){
		matriz2[i+1][j-1]='0';
		comprobacionCeros(i+1, j-1);
	}
	else{
		if((j!=0)&&(i!=9)){
			matriz2[i+1][j-1]=std::to_string(matriz1[i+1][j-1]);
		}
	}
	if(i!=9 && matriz1[i+1][j]==0 && !visitados[i+1][j]){
		matriz2[i+1][j]='0';
		comprobacionCeros(i+1, j);
	}
	else{
		if(i!=9){
			matriz2[i+1][j]=std::to_string(matriz1[i+1][j]);
		}
	}
	if(i!=9 && j!=9 && matriz1[i+1][j+1]==0 && !visitados[i+1][j+1]){
		matriz2[i+1][j+1]='0';
		comprobacionCeros(i+1, j+1);
	}
	else{
		if(i!=9 && j!=9){
			matriz2[i+1][j+1]=std::to_string(matriz1[i+1][j+1]);
		}
	}
	if(j!=9 && matriz1[i][j+1]==0 && !visitados[i][j+1]){
		matriz2[i][j+1]='0';
		comprobacionCeros(i, j+1);
	}
	else{
		if(j!=9){
			matriz2[i][j+1]=std::to_string(matriz1[i][j+1]);
		}
	}
	if(i!=0 && j!=9 && matriz1[i-1][j+1]==0 && !visitados[i-1][j+1]){
		matriz2[i-1][j+1]='0';
		comprobacionCeros(i-1, j+1);
	}
	else{
		if(i!=0 && j!=9){
			matriz2[i-1][j+1]=std::to_string(matriz1[i-1][j+1]);
		}
	}
}
std::string Panel::seleccionarCasilla(int fila, char * columna_letra, int socket, std::map<int, std::string> & usuarios){
	std::string aux="";
	int columna=traduccionFila(columna_letra[0]);

	//comprobamos que la casilla no ha sido ya seleccionada
	// if(matriz2[fila][columna]!="-"){
	// 	aux="Esa casilla ya ha sido seleccionada antes\n";
	// 	return aux;
	// }

	//Si en la casilla seleccionada hay una bomba
	if(matriz1[fila][columna]==-1){
		aux="Jugador " + usuarios[socket] + " ha perdido la partida\n";
	}
	else{
		//Si en la casilla no hay bomba
		int casilla=matriz1[fila][columna];
		if(casilla==0){
			matriz2[fila][columna]='0';
			comprobacionCeros(fila, columna);
		}
		else{
			matriz2[fila][columna]=std::to_string(casilla);
		}
	}

	return aux;
}
