#ifndef PANEL_HPP
#define PANEL_HPP
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <map>
class Panel{
	private:
		std::vector<std::vector<int> >matriz1;//con esta matriz trabaja el programa internamente
		std::vector<std::vector<std::string> > matriz2;//esta matriz se mostrara por pantalla
		std::vector<std::vector<bool> > visitados;
		int _banderasA;//las banderas puestas por cada jugador
		int _banderasB;
		int _socket1;
		int _socket2;
		int _turno;
	public:
		inline Panel(){//constructor de la clase
			matriz1.resize(10, std::vector<int>(10,0));
			matriz2.resize(10, std::vector<std::string>(10,"-"));
			visitados.resize(10, std::vector<bool>(10, false));
			_banderasA=0;
			_banderasB=0;
			_socket1=-1;
			_socket2=-1;
			_turno=-1;
		}
		inline std::vector<std::vector<int> > getMatrix1(){
			return matriz1;
		}
		inline void setMatrix1(int i, int j, int value){
			matriz1[i][j]=value;
		}
		inline std::vector<std::vector<std::string> > getMatrix2(){
			return matriz2;
		}
		inline int getSocket1()const{
			return _socket1;
		}
		inline int getSocket2()const{
			return _socket2;
		}
		inline void setSocket1(int a){
			_socket1=a;
		}
		inline void setSocket2(int a){
			_socket2=a;
		}
		inline int getbanderasA()const{//devuelve el numero de banderas usadas por el jugador A
			return _banderasA;
		}
		inline int getbanderasB()const{
			return _banderasB;
		}
		inline std::string mostrarMatrizInicial() const{//muestra la matriz al comienzo del juego, antes de que haya sufrido modificacion alguna
			std::string aux;
			for (int i = 0; i < 10; ++i){
				for (int j = 0; j < 10; ++j){
					aux+=" " + matriz2[i][j];
				}
				aux+=";";
			}
		}
		inline std::string mostrarMatrizFinal()const{//funcion que muestra la matriz al descubierto. Util para mostrarla al final de la partida
			std::string aux;
			for (int i = 0; i < 10; ++i){
				for (int j = 0; j < 10; ++j){
					if(matriz1[i][j]==-1){
						aux = aux + " " + "*";
					}
					else{
						aux += " " + matriz1[i][j];
					}
				}
				aux+=";";
			}
		}
		std::string mostrarMatriz() const;//se muestra la matriz actual a los jugadores.
		void obtenerBombas(int i, int j, int r);
		void busquedaBombas();
		int traduccionFila(char fila);
		void comprobacionCeros(int i, int j);
		void rellenaMatriz(); //funcion que rellena la matriz de numeros y bombas al principio del juego
		bool comprobarBanderas(int socket);
		std::string ponerBandera(int fila, char columna_letra, int socket, std::map<int, std::string> & usuarios);//funcion que marca una casilla por parte de un jugador
		std::string seleccionarCasilla(int fila, char columna_letra, int socket, std::map<int, std::string> & usuarios);//ejemplo: A 2, 2 (jugador numero 2). un jugador selecciona una casilla para descubrirla
};
#endif
