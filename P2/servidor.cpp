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
#include <fstream>
#define MAX_CLIENTS 2
void salirCliente(int socket, fd_set * readfds, int * numClientes, int arrayClientes[]);
int main(){
	/*----------------------------------------------------
		Descriptor del socket y buffer de datos
	-----------------------------------------------------*/
   std::fstream file;
   int sd, new_sd;
   struct sockaddr_in sockname, from;
   char buffer[100];
   socklen_t from_len;
   fd_set readfds, auxfds;
   int salida;
   int arrayClientes[MAX_CLIENTS];
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
   sockname.sin_port = htons(2000);
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
    FD_SET(sd,&readfds);
    FD_SET(0,&readfds);


    //Capturamos la señal SIGINT (Ctrl+c)
    // signal(SIGINT,manejador);

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
                        send(arrayClientes[j], "Desconexion servidor\n", strlen("Desconexion servidor\n"),0);
                        close(arrayClientes[j]);
                        FD_CLR(arrayClientes[j],&readfds);
                     }
                     close(sd);
                     exit(-1);
                  }
                            //Mensajes que se quieran mandar a los clientes (implementar)
               }
               else{
                  bzero(buffer,sizeof(buffer));
                  recibidos = recv(i,buffer,sizeof(buffer),0);
                  // std::cout << buffer << '\n';
                  if(recibidos>0){
                     if(strcmp(buffer,"SALIR\n") == 0){
                        salirCliente(i,&readfds,&numClientes,arrayClientes);
                     }
                     else{
                        // if(strstr(buffer, "USUARIO")!=NULL){
                        //    std::cout << "cat" << '\n';
                        //    send(i,buffer,strlen(buffer),0);
                        // }
                        // else if(strstr(buffer, "PASSWORD")!=NULL){
                        //    std::cout << "meow" << '\n';
                        //    send(i,buffer,strlen(buffer),0);
                        // }
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
                           char usuario[20], contrasena[20];
                           std::string search, user_to_search;
                           int lenghtbuffer1=strlen(buffer);
                           bzero(usuario, sizeof(usuario));
                           bzero(contrasena, sizeof(contrasena));

                           strncpy(usuario, buffer+8, lenghtbuffer1-9);
                           file.open("USUARIOS.txt", std::fstream::in);

                           while(std::getline(file,search)){
                              user_to_search=search.substr(0, strlen(usuario));
                              std::cout << user_to_search << '\n';
                              if(strcmp(user_to_search.c_str(), usuario)==0){
                                 ask_for_password=true;
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
                           else{
                              bzero(buffer,sizeof(buffer));
                              recv(i,buffer,sizeof(buffer),0);
                              std::string search, user_to_search, passwd_to_search;
                              bool authentication=false;

                              strncpy(contrasena, buffer+9, strlen(buffer)-10);

                              file.open("USUARIOS.txt", std::fstream::in);
                              while(std::getline(file,search)){
                                 user_to_search=search.substr(0, strlen(usuario));
                                 if(strcmp(user_to_search.c_str(), usuario)==0){
                                    passwd_to_search=search.substr(strlen(usuario)+1, strlen(search.c_str())-strlen(usuario)-1);
                                    if(strcmp(passwd_to_search.c_str(), contrasena)==0){
                                       std::cout << "Contrasena correcta" << '\n';
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
                        }
                     }
                  }
                  //Si el cliente introdujo ctrl+c
                  if(recibidos==0){
                     printf("El socket %d, ha introducido ctrl+c\n", i);
                     //Eliminar ese socket
                     salirCliente(i,&readfds,&numClientes,arrayClientes);
                  }
               }
            }
         }
		}
   }
	close(sd);
	return 0;
}
void salirCliente(int socket, fd_set * readfds, int * numClientes, int arrayClientes[]){

    char buffer[250];
    int j;

    close(socket);
    FD_CLR(socket,readfds);

    //Re-estructurar el array de clientes
    for (j = 0; j < (*numClientes) - 1; j++)
        if (arrayClientes[j] == socket)
            break;
    for (; j < (*numClientes) - 1; j++)
        (arrayClientes[j] = arrayClientes[j+1]);

    (*numClientes)--;

    bzero(buffer,sizeof(buffer));
    sprintf(buffer,"Desconexión del cliente: %d\n",socket);

    for(j=0; j<(*numClientes); j++)
        if(arrayClientes[j] != socket)
            send(arrayClientes[j],buffer,strlen(buffer),0);
}
