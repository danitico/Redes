#ifndef _PANEL_HPP_
#define _PANEL_HPP_

#include <iostream>
#include <cassert>
#include <stdlib.h>
#include <time.h>

class panel{
	private:
		std::vector<std::vector<int> >matriz1;
		std::vector<std::vector<char> > matriz2;//esta matriz se mostrara por pantalla
		int banderasA;//las banderas puestas por cada jugador
		int banderasB;

	public:

		inline panel(){//constructor de la clase
			matriz1.resize(10, std::std::vector<int>(10,0));
			matriz2.resize(10, std::std::vector<int>(10,0));
			//al principio la matriz esta llenar de -
			for (int i = 0; i < 10; ++i){
				for (int j = 0; j < 10; ++j){
					matriz2[i][j]='-'
				}
			}
			banderasA=0;
			banderasB=0;

		}

		inline void mostrarMatrizInicial()const{//muestra la matriz al comienzo del juego, antes de que haya sufrido modificacion alguna
			std::cout<<"Se muestra la matriz inicial:\n";
			for (int i = 0; i < 10; ++i){
				for (int j = 0; j < 10; ++j){
					std::cout<<matriz2[i][j]<<std::endl;
				}
				std::cout<<"\n";
			}
		}

		void mostrarMatriz() const;//se muestra la matriz actual a los jugadores. 








		void rellenaMatriz(); //funcion que rellena la matriz de numeros al principio del juego
			

		void ponerBandera(char letra, int j, int ju);//funcion que marca una casilla por parte de un jugador

		void seleccionarCasilla(char letra, int j)

























};