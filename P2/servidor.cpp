#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unistd.h>
#include <ctime>
#include <arpa/inet.h>
#include <map>
#include <vector>
#include <fstream>
#include "panel.hpp"
#define MAX_CLIENTS 30
void salirCliente(int socket, fd_set * readfds, fd_set * ask_password, fd_set * auth, int * numClientes, int arrayClientes[], std::map<int, std::string> & usuarios);
int main(){
	/*----------------------------------------------------
		Descriptor del socket y buffer de datos
	-----------------------------------------------------*/
   std::fstream file;
   int sd, new_sd;
   struct sockaddr_in sockname, from;
   char buffer[250];
   socklen_t from_len;
   fd_set readfds, auxfds, ask_password, auth, playing;
   int salida;
   int arrayClientes[MAX_CLIENTS];
   std::map<int, std::string> usuarios;
   std::vector<panel> partidas;
   int contadorPartidas=0;
   int numClientes=0;
   //contadores
   int i,j,k;
   int recibidos;

   int on, ret;

  	sd = socket (AF_INET, SOCK_STREAM, 0);
	if(sd == -1){
      perror("No se puede abrir el socket cliente\n");
      exit (1);
	}

    // Activaremos una propiedad del socket que permitir· que otros
    // sockets puedan reutilizar cualquier puerto al que nos enlacemos.
    // Esto permitir· en protocolos como el TCP, poder ejecutar un
    // mismo programa varias veces seguidas y enlazarlo siempre al
    // mismo puerto. De lo contrario habrÌa que esperar a que el puerto
    // quedase disponible (TIME_WAIT en el caso de TCP)
   on=1;
   ret = setsockopt( sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

   sockname.sin_family = AF_INET;
   sockname.sin_port = htons(2050);
   sockname.sin_addr.s_addr = INADDR_ANY;

	if (bind (sd, (struct sockaddr *) &sockname, sizeof (sockname)) == -1){
		perror("Error en la operación bind");
		exit(1);
	}
   	/*---------------------------------------------------------------------
		Del las peticiones que vamos a aceptar sólo necesitamos el
		tamaño de su estructura, el resto de información (familia, puerto,
		ip), nos la proporcionará el método que recibe las peticiones.
   	----------------------------------------------------------------------*/
		from_len = sizeof(from);


		if(listen(sd,1) == -1){
			perror("Error en la operación de listen");
			exit(1);
		}

    //Inicializar los conjuntos fd_set
    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_ZERO(&ask_password);
    FD_ZERO(&auth);
    FD_ZERO(&playing);
    FD_SET(sd,&readfds);
    FD_SET(0,&readfds);


	/*-----------------------------------------------------------------------
		El servidor acepta una petición
	------------------------------------------------------------------------ */
   while(1){
      //Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)
      auxfds=readfds;
      salida=select(FD_SETSIZE,&auxfds,NULL,NULL,NULL);
      if(salida > 0){
         for(i=0; i<FD_SETSIZE; i++){
           //Buscamos el socket por el que se ha establecido la comunicación
            if(FD_ISSET(i, &auxfds)){
               if(i==sd){
                  if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len)) == -1){
                     perror("Error aceptando peticiones");
                  }
                  else{
                     if(numClientes < MAX_CLIENTS){
                        arrayClientes[numClientes] = new_sd;
                        numClientes++;
                        bzero(buffer,sizeof(buffer));
                        // std::cout << new_sd << '\n';
                        FD_SET(new_sd,&readfds);
                        strcpy(buffer, "Bienvenidos\0");
                        send(new_sd,buffer,strlen(buffer),0);
                     }
                     else{
                        bzero(buffer,sizeof(buffer));
                        strcpy(buffer,"Demasiados clientes conectados\0");
                        send(new_sd,buffer,strlen(buffer),0);
                        close(new_sd);
                     }
                  }
               }
               else if (i == 0){
                  //Se ha introducido información de teclado
                  bzero(buffer, sizeof(buffer));
                  fgets(buffer, sizeof(buffer),stdin);
                  //Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
                  if(strcmp(buffer,"SALIR\n") == 0){
                     for(j=0; j<numClientes; j++){
                        send(arrayClientes[j], "SALIR\0", strlen("SALIR\0"),0);
                        close(arrayClientes[j]);
                        FD_CLR(arrayClientes[j],&readfds);
                        FD_CLR(arrayClientes[j], &auth);
                        FD_CLR(arrayClientes[j], &playing);
                        FD_CLR(arrayClientes[j], &ask_password);
                     }
                     close(sd);
                     exit(-1);
                  }
               }
               else{
                  bzero(buffer,sizeof(buffer));
                  recibidos = recv(i,buffer,sizeof(buffer),0);
                  if(recibidos>0){
                     if(strcmp(buffer,"SALIR\n") == 0){
                        salirCliente(i,&readfds,&ask_password, &auth, &numClientes,arrayClientes, usuarios);
                     }
                     else{
                        if(strstr(buffer, "REGISTRO")!=NULL){
                           bool anadir=true;
                           char *dummie, *dummie1;
                           char user[20], passwd[20];
                           bzero(user, sizeof(user));
                           bzero(passwd, sizeof(passwd));
                           dummie=strstr(buffer, " -p");
                           dummie1=strstr(buffer, "-p");
                           int lenghtbuffer=strlen(buffer)-1, lenghtdummie=strlen(dummie)-1, lenghtdummie1=strlen(dummie1)-1;
                           strncpy(user, buffer+12, lenghtbuffer-lenghtdummie-12);
                           strncpy(passwd, dummie1+3, lenghtbuffer-lenghtdummie1-3);

                           std::string search;
                           std::string user_to_search;
                           file.open("USUARIOS.txt", std::fstream::in);

                           while(std::getline(file,search)){
                              user_to_search=search.substr(0, strlen(user));
                              if(strcmp(user_to_search.c_str(), user)==0){
                                 anadir=false;
                                 bzero(buffer,sizeof(buffer));
                                 strcpy(buffer,"-Err Ya existe ese usuario\0");
                                 send(i,buffer,strlen(buffer),0);
                                 break;
                              }
                           }
                           file.close();
                           file.open("USUARIOS.txt", std::fstream::app);
                           if(anadir){
                              file << user << " " << passwd;
                              bzero(buffer,sizeof(buffer));
                              strcpy(buffer,"+Ok Usuario Registrado\0");
                              send(i,buffer,strlen(buffer),0);
                           }
                           file.close();
                        }
                        else if(strstr(buffer, "USUARIO")!=NULL){
                           bool ask_for_password=false;
                           char usuario[20];
                           bzero(usuario, sizeof(usuario));
                           std::string search, user_to_search;
                           int lenghtbuffer1=strlen(buffer);

                           strncpy(usuario, buffer+8, lenghtbuffer1-9);
                           file.open("USUARIOS.txt", std::fstream::in);

                           while(std::getline(file,search)){
                              user_to_search=search.substr(0, strlen(usuario));
                              if(strcmp(user_to_search.c_str(), usuario)==0){
                                 ask_for_password=true;
                                 usuarios[i]=usuario;
                                 FD_SET(i, &ask_password);
                                 bzero(buffer,sizeof(buffer));
                                 strcpy(buffer,"+OK El usuario existe. Introduzca la contrasena\0");
                                 send(i,buffer,strlen(buffer),0);
                                 file.close();
                                 break;
                              }
                           }
                           if(!ask_for_password){
                              bzero(buffer,sizeof(buffer));
                              strcpy(buffer,"+Err El usuario no existe\0");
                              send(i,buffer,strlen(buffer),0);
                              file.close();
                           }
                        }
                        else if(strstr(buffer, "PASSWORD")!=NULL){
                           if(FD_ISSET(i, &ask_password)){
                              char contrasena[20];
                              bzero(contrasena,sizeof(contrasena));
                              std::string search, user_to_search, passwd_to_search;

                              strncpy(contrasena, buffer+9, strlen(buffer)-10);

                              file.open("USUARIOS.txt", std::fstream::in);
                              while(std::getline(file,search)){
                                 user_to_search=search.substr(0, strlen(usuarios[i].c_str()));
                                 if(strcmp(user_to_search.c_str(), usuarios[i].c_str())==0){
                                    passwd_to_search=search.substr(strlen(usuarios[i].c_str())+1, strlen(search.c_str())-strlen(usuarios[i].c_str())-1);
                                    if(strcmp(passwd_to_search.c_str(), contrasena)==0){
                                       FD_SET(i, &auth);
                                       FD_CLR(i, &ask_password);
                                       usuarios.erase(i);
                                       bzero(buffer,sizeof(buffer));
                                       strcpy(buffer,"+OK Contrasena Correcta. Log In hecho con éxito\0");
                                       send(i,buffer,strlen(buffer),0);
                                       file.close();
                                       break;
                                    }
                                    else{
                                       bzero(buffer,sizeof(buffer));
                                       strcpy(buffer,"-Err Contraseña equivocada\0");
                                       send(i,buffer,strlen(buffer),0);
                                       file.close();
                                       break;
                                    }
                                 }
                              }
                           }
                           else{
                              bzero(buffer,sizeof(buffer));
                              strcpy(buffer,"-Err Debe de introducir un usuario antes\0");
                              send(i,buffer,strlen(buffer),0);
                           }
                        }
                        else if(strcmp(buffer, "INICIAR-PARTIDA\n")==0){
                           if(FD_ISSET(i, &auth)){
                              for(int j=0; j<partidas.size(); j++){
                                 if(partidas[j].getSocket2()==-1){
                                    partidas[j].setSocket2(i);
                                    FD_SET(partidas[j].getSocket1(), &playing);
                                    FD_SET(i, &playing);
                                 }
                              }
                              // bzero(buffer,sizeof(buffer));
                              // strcpy(buffer,"+OK espera\0");
                              // send(i,buffer,strlen(buffer),0);
                           }
                           else{
                              bzero(buffer,sizeof(buffer));
                              strcpy(buffer,"-Err Debe de autenticarse para jugar\0");
                              send(i,buffer,strlen(buffer),0);
                           }
                        }
                        else if(strstr(buffer, "DESCUBRIR")!=NULL){
                           if(FD_ISSET(i, &auth)){
                              if(/*FD_ISSET(i, &playing)*/1){
                                 //a implementar. Por ahora voy a obtener la fila y la columna
                                 int row=0;
                                 char col[2], *aux;
                                 bzero(col,sizeof(col));

                                 strncpy(col, buffer+10, 1);
                                 aux=strstr(buffer, ",");
                                 strncpy(aux, aux+1, strlen(aux)-1);
                                 row=atoi(aux);
                                 std::cout << row << '\n';
                              }
                              else{
                                 bzero(buffer,sizeof(buffer));
                                 strcpy(buffer,"-Err Debe de inicia una partida para jugar\0");
                                 send(i,buffer,strlen(buffer),0);
                              }
                           }
                           else{
                              bzero(buffer,sizeof(buffer));
                              strcpy(buffer,"-Err Debe de autenticarse para jugar\0");
                              send(i,buffer,strlen(buffer),0);
                           }
                        }
                        else if(strstr(buffer, "PONER-BANDERA")!=NULL){
                           if(FD_ISSET(i, &auth)){
                              if(/*FD_ISSET(i, &playing)*/1){
                                 //a implementar. Por ahora voy a obtener la fila y la columna
                                 int row=0;
                                 char col[2], *aux;
                                 bzero(col,sizeof(col));

                                 strncpy(col, buffer+10, 1);
                                 aux=strstr(buffer, ",");
                                 strncpy(aux, aux+1, strlen(aux)-1);
                                 row=atoi(aux);
                                 std::cout << row << '\n';
                              }
                              else{
                                 bzero(buffer,sizeof(buffer));
                                 strcpy(buffer,"-Err Debe de inicia una partida para jugar\0");
                                 send(i,buffer,strlen(buffer),0);
                              }
                           }
                           else{
                              bzero(buffer,sizeof(buffer));
                              strcpy(buffer,"-Err Debe de autenticarse para jugar\0");
                              send(i,buffer,strlen(buffer),0);
                           }
                        }
                        else{
                           //
                        }
                     }
                  }
                  //Si el cliente introdujo ctrl+c
                  if(recibidos==0){
                     printf("El socket %d, ha introducido ctrl+c\n", i);
                     //Eliminar ese socket
                     salirCliente(i, &readfds, &ask_password, &auth, &numClientes, arrayClientes, usuarios);
                  }
               }
            }
         }
		}
   }
	close(sd);
	return 0;
}
void salirCliente(int socket, fd_set * readfds, fd_set * ask_password, fd_set * auth, int * numClientes, int arrayClientes[], std::map<int, std::string> & usuarios){
   char buffer[250];
   int j;

   bzero(buffer,sizeof(buffer));
   strcpy(buffer, "SALIR\0");
   send(socket,buffer,strlen(buffer),0);

   close(socket);
   FD_CLR(socket,readfds);
   if(FD_ISSET(socket, ask_password)){
      FD_CLR(socket, ask_password);
   }
   if(FD_ISSET(socket, auth)){
      FD_CLR(socket, auth);
   }
   if(usuarios.find(socket)!=usuarios.end()){
      usuarios.erase(socket);
   }


   //Re-estructurar el array de clientes
   for(j=0;j<(*numClientes)-1; j++){
      if(arrayClientes[j]==socket){
         break;
      }
   }

   for(;j<(*numClientes)-1;j++){
      (arrayClientes[j] = arrayClientes[j+1]);
   }

   (*numClientes)--;
}
