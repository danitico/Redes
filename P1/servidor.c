#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
int main(int argc, char **argv){
   int Socket_Servidor;
   Socket_Servidor=socket(AF_INET, SOCK_DGRAM, 0);

   if(Socket_Servidor < 0){
      printf("Error al crear el descriptor del socket\n");
      exit(-1);
   }

   struct sockaddr_in direccion, cliente;
   socklen_t Longitud_direccion, Longitud_Cliente;
   Longitud_direccion=sizeof(direccion);

   direccion.sin_family=AF_INET;
   direccion.sin_port=htons(2000);
   direccion.sin_addr.s_addr=INADDR_ANY;

   int result = 0;
   result=bind(Socket_Servidor, (struct sockaddr *)&direccion, Longitud_direccion);

   if(result < 0){
      printf("Error al asociar el socket con el puerto\n");
      exit(-1);
   }

   char paquete[10];
   char datos[100];
   int recibido;
   time_t tiempo;
   time(&tiempo);
   struct tm * stTm;
   stTm = localtime(&tiempo);

   while(1){
      recibido=recvfrom(Socket_Servidor, paquete, sizeof(paquete), 0, (struct sockaddr *)&cliente, &Longitud_Cliente);
      printf("%s\n", paquete);
      if(recibido > 0){
         if(strcmp(paquete, "DAY")==0){
            strftime(datos,100,"%A, %d de %B de %Y", stTm);
            sendto(Socket_Servidor, datos, sizeof(datos), 0, (struct sockaddr *) &cliente, Longitud_Cliente);
         }
         else if(strcmp(paquete, "TIME")==0){
            strftime(datos,100,"%H:%M:%S", stTm);
            sendto(Socket_Servidor, datos, sizeof(datos), 0, (struct sockaddr *) &cliente, Longitud_Cliente);
         }
         else if(strcmp(paquete, "DAYTIME")==0){
            strftime(datos,100,"%A, %d de %B de %Y; %H:%M:%S", stTm);
            sendto(Socket_Servidor, datos, sizeof(datos), 0, (struct sockaddr *) &cliente, Longitud_Cliente);
         }
         else{
            sprintf(datos, "ERROR");
            sendto(Socket_Servidor, datos, sizeof(datos), 0, (struct sockaddr *) &cliente, Longitud_Cliente);
         }
      }
   }
}
