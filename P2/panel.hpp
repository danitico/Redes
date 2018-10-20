#ifndef _PANEL_HPP
#define _PANEL_HPP

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

class panel{
	private:
		std::vector<std::vector<int> >matriz1;
		std::vector<std::vector<char> > matriz2;//esta matriz se mostrara por pantalla
		int _banderasA;//las banderas puestas por cada jugador
		int _banderasB;
		int _socket1;
		int _socket2;

	public:

		inline panel(){//constructor de la clase
			//matriz1.resize(10, std::std::vector<int>(10,0));
			matriz1.resize(10, 0);
			for (int i = 0; i < 10; ++i){
				matriz1[i].resize(10, 0);
			}
			//matriz2.resize(10, std::std::vector<int>(10,0));
			matriz2.resize(10, 0);
			for (int i = 0; i < 10; ++i){
				matriz2.resize(10, 0);
			}
			//al principio la matriz esta llenar de -
			for (int i = 0; i < 10; ++i){
				for (int j = 0; j < 10; ++j){
					matriz2[i][j]='-';
				}
			}
			_banderasA=0;
			_banderasB=0;

		}

		inline int getShocket1()const{
			return _socket1;
		}

		inline int getShocket2()const{
			return _socket2;
		}

		inline void setShocket1(int a){
			_socket1=a;
		}

		inline void setShocket2(int a){
			_socket2=a;
		}

		inline int getbanderasA()const{//devuelve el numero de banderas usadas por el jugador A
			return _banderasA; 
		}

		inline int getbanderasB()const{
			return _banderasB;
		}


		inline void mostrarMatrizInicial()const{//muestra la matriz al comienzo del juego, antes de que haya sufrido modificacion alguna
			std::cout<<"Se muestra la matriz inicial:\n";
			for (int i = 0; i < 10; ++i){
				for (int j = 0; j < 10; ++j){
					std::cout<<matriz2[i][j]<<" "<<std::endl;
				}
				std::cout<<"\n";
			}
		}

		void mostrarMatriz() const;//se muestra la matriz actual a los jugadores. 


		void rellenaMatriz(); //funcion que rellena la matriz de numeros y bombas al principio del juego
			

		void ponerBandera(char letra, int j, int ju);//funcion que marca una casilla por parte de un jugador

		void seleccionarCasilla(char letra, int j, int ju);//ejemplo: A 2, 2 (jugador numero 2). un jugador selecciona una casilla para descubrirla


		inline void mostrarMatrizFinal()const{//funcion que muestra la matriz al descubierto. Util para mostrarla al final de la partida
			std::cout<<"ESTA ES LA MATRIZ DE JUEGO:\n";
			for (int i = 0; i < 10; ++i){
				for (int j = 0; j < 10; ++j){
					if(matriz1[i][j]==-1){
						std::cout<<" * ";
					}
					else{
						std::cout<<matriz1[i][j];
					}
				}
				std::cout<<"\n";
			}
		}
























};//FIN DEFINICION CLASE 
#endif