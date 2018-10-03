#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
int main(int argc, char **argv){
   if(argc!=3){
      printf("Error al llamar al programa. Ejemplo: %s <IP> <TIMEOUT>\n", argv[0]);
      exit(-1);
   }
   int Socket_Cliente;

   if((Socket_Cliente = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
      printf("Error al crear el descriptor del socket\n");
      exit(-1);
   }

   struct sockaddr_in Servidor;
   socklen_t Longitud_Servidor;

   Servidor.sin_family=AF_INET;
   Servidor.sin_port=htons(2000);
   Servidor.sin_addr.s_addr=inet_addr(argv[1]);
   Longitud_Servidor=sizeof(Servidor);

   char paquete[10];
   char datos[100];

   printf("Introduzca lo que quiere pedir al servidor\n");
   printf("Las opciones son DAY, TIME, y DAYTIME\n");
   scanf("%s", paquete);


   int bytes;
   int bytesrecibidos;
   int retries=0;
   int resultado=0;
   struct timeval timeout;
   fd_set lectura;

   FD_ZERO(&lectura);


   while(bytesrecibidos<=0 || retries < 3){
      timeout.tv_sec = atoi(argv[2]);
      timeout.tv_usec = 0;

      bytes=0;
      bytes=sendto(Socket_Cliente, paquete, sizeof(paquete), 0, (struct sockaddr *)&Servidor, Longitud_Servidor);
      if(bytes < 0){
         printf("Error al enviar el mensaje al servidor\n");
      }
      FD_SET(Socket_Cliente, &lectura);

      resultado=select(Socket_Cliente+1, &lectura, NULL, NULL, &timeout);
      if(resultado < 0){
         printf("error\n");
      }
      else{
         if(resultado==0){
            printf("Timeout");
            retries++;
         }
         else{
            bytesrecibidos=0;
            bytesrecibidos=recvfrom(Socket_Cliente, datos, sizeof(datos), 0, (struct sockaddr *)&Servidor, &Longitud_Servidor);
            if(bytesrecibidos < 0){
               printf("Error al recibir los datos del servidor\n");
            }
            else{
               printf("%s\n", datos);
               break;
            }
         }
      }
   }
   close(Socket_Cliente);
}
