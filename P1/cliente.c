#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
int main(int argc, char **argv){
   if(argc!=3){
      printf("Error al llamar al programa. Ejemplo: %s <IP> <TIMEOUT>\n", argv[0]);
   }
   int Socket_Cliente;


   if((Socket_Cliente = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
      printf("Error al crear el descriptor del socket\n");
      exit(-1);
   }

   struct sockaddr_in Servidor;
   socklen_t Longitud_Servidor;

}
