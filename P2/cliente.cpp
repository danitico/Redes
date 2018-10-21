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
      if(strcmp(buffer1, "SALIR\0")==0){
         break;
      }
      else{
         std::cout << buffer1 << '\n';
      }
   }
   // while(1){
   //    std::cout << "Introduzca que quiere hacer" << '\n';
   //    std::cout << "1. Logearse" << '\n';
   //    std::cout << "2. Registrase" << '\n';
   //    std::cin >> opcion;
   //
   //    if(opcion!=0){
   //       switch (opcion) {
   //          case 1:
   //             std::cout << "Introduzca el usuario" << '\n';
   //             std::cin>>buffer1;
   //             strcat(a, buffer1);
   //             std::cout << a << '\n';
   //             // buffer1 = "USUARIO " + buffer1;
   //             send(sd, a, sizeof(a), 0);
   //             recv(sd, buffer, sizeof(buffer), 0);
   //
   //             if(buffer=="error"){
   //                std::cout << "no existe" << '\n';
   //                break;
   //             }
   //
   //             strcpy(buffer1, "");
   //             std::cout << "Introduzca passwd" << '\n';
   //             std::cin >> buffer1;
   //
   //             strcat(b, buffer1);
   //             std::cout << b << '\n';
   //             strcpy(buffer, "");
   //             send(sd, b, sizeof(b), 0);
   //             recv(sd, buffer, sizeof(buffer), 0);
   //             if(buffer=="error"){
   //                std::cout << "contraseña equivocada" << '\n';
   //                break;
   //             }
   //             break;
   //          case 2:
   //             // std::cout << "Introduzca el usuario" << '\n';
   //             // std::cin>>usuario;
   //             // std::cout << "Introduzca passwd" << '\n';
   //             // std::cin >> passwd;
   //             //
   //             // registro="REGISTRO -u " + usuario + " -p " + passwd;
   //             // send(sd, registro.c_str(), sizeof(registro), 0);
   //             // cadena="";
   //             // recv(sd, cadena.c_str(), sizeof(cadena), 0);
   //             // if(cadena=="error"){
   //             //    std::cout << "El usuario existe" << '\n';
   //             // }
   //             break;
   //
   //          default:
   //             std::cout << "opcion equivocada" << '\n';
   //          break;
   //       }
   //    }
   //    else{
   //       close(sd);
   //       std::cout << "salir" << '\n';
   //       return 0;
   //    }
   // }

   // if(cadena=="OK"){
   //    int opcion2=0;
   //    std::cout << "Introduzca que quiere hacer" << '\n';
   //    std::cout << "1. Iniciar partido" << '\n';
   //    std::cout << "2. salir" << '\n';
   //    std::cin >> opcion2;
   //
   //    if(opcion2==1){
   //       // partida(sd);
   //    }
   //    else{
   //       close(sd);
   //       std::cout << "salir" << '\n';
   //       return 0;
   //    }
   // }
}
// void partida(int const & sd){
//    std::string mensaje="JUGAR", confirmacion;
//    send(sd, mensaje.c_str(), sizeof(mensaje), 0);
//    std::cout << "Espere....." << '\n';
//    recv(sd, confirmacion.c_str(), sizeof(confirmacion), 0);
// }
