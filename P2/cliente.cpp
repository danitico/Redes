#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <cstdio>
// void partida(int const & sd);
int main(int argc, char **argv){
   int sd;
   struct sockaddr_in sockname;
   char buffer[250];
   std::memset (buffer,'\0',250);
   char buffer1[250];
   std::memset (buffer1,'\0',250);
   socklen_t len_sockname;

   sd = socket (AF_INET, SOCK_STREAM, 0);
   if (sd == -1){
      perror("No se puede abrir el socket cliente\n");
      exit (1);
   }

   sockname.sin_family = AF_INET;
   sockname.sin_port = htons(2050);
   sockname.sin_addr.s_addr =  inet_addr("127.0.0.1");

   len_sockname = sizeof(sockname);

	if (connect(sd, (struct sockaddr *)&sockname, len_sockname) == -1){
		perror ("Error de conexión");
		exit(1);
	}

   int opcion;
   std::string cadena, usuario, passwd, registro, bienvenida;
   recv(sd, buffer, 250, 0);

   if(strcmp("Demasiados clientes conectados\0", buffer)==0){
      std::cout << buffer << std::endl;
      return -1;
   }
   else{
      std::cout << buffer << "\n";//mensaje conexión correcta
   }

   bzero(buffer,sizeof(buffer));
   bzero(buffer1, sizeof(buffer1));

   while(1){
      bzero(buffer,sizeof(buffer));
      bzero(buffer1, sizeof(buffer1));
      fgets(buffer,sizeof(buffer),stdin);

      send(sd, buffer, sizeof(buffer), 0);
      recv(sd, buffer1, sizeof(buffer1), 0);

      if(strcmp(buffer1, "+OK Waiting for a player\0")==0){
         std::cout << buffer1 << '\n';
         bzero(buffer1, sizeof(buffer1));
         recv(sd, buffer1, sizeof(buffer1), 0);
      }

      if(strcmp(buffer1, "SALIR\0")==0)
         break;

      else{
         std::cout << buffer1 << '\n';
      }
   }

}
