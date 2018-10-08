#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
int main(int argc, char **argv){
   int sd;
   struct sockaddr_in sockname;
   char buffer[100];
   socklen_t len_sockname;

   sd = socket (AF_INET, SOCK_STREAM, 0);
   if (sd == -1){
      perror("No se puede abrir el socket cliente\n");
      exit (1);
   }

   sockname.sin_family = AF_INET;
   sockname.sin_port = htons(2000);
   sockname.sin_addr.s_addr =  inet_addr("127.0.0.1");

   len_sockname = sizeof(sockname);

	if (connect(sd, (struct sockaddr *)&sockname, len_sockname) == -1)
	{
		perror ("Error de conexión");
		exit(1);
	}

   int opcion;
   std::string cadena, usuario, passwd, registro;

   while(buffer=="error"){
      std::cout << "Introduzca que quiere hacer" << '\n';
      std::cout << "1. Logearse" << '\n';
      std::cout << "2. Registrase" << '\n';
      if(opcion!=0){
         switch (opcion) {
            case 1:
               std::cout << "Introduzca el usuario" << '\n';
               std::cin>>usuario;
               usuario = "USUARIO " + usuario;
               send(sd, usuario.c_str(), sizeof(usuario), 0);
               recv(sd, cadena.c_str(), sizeof(cadena), 0);
               if(cadena=="error"){
                  std::cout << "no existe" << '\n';
                  break;
               }

               std::cout << "Introduzca passwd" << '\n';
               std::cin >> passwd;
               passwd = "PASSWORD " + passwd;
               send(sd, passwd.c_str(), sizeof(passwd), 0);
               cadena="";
               recv(sd, cadena.c_str(), sizeof(cadena), 0);
               if(cadena=="error"){
                  std::cout << "contraseña equivocada" << '\n';
                  break;
               }
               break;
            case 2:
               std::cout << "Introduzca el usuario" << '\n';
               std::cin>>usuario;
               std::cout << "Introduzca passwd" << '\n';
               std::cin >> passwd;

               registro="REGISTRO -u " + usuario + " -p " + passwd;
               send(sd, registro.c_str(), sizeof(registro), 0);
               cadena="";
               recv(sd, cadena.c_str(), sizeof(cadena), 0);
               if(cadena=="error"){
                  std::cout << "El usuario existe" << '\n';
               }
               break;

            default:
               std::cout << "opcion equivocada" << '\n';
            break;
         }
      }
      else{
         close(sd);
         std::cout << "salir" << '\n';
         return 0;
      }
   }

   if(cadena=="OK"){
      std::cout << "Introduzca que quiere hacer" << '\n';
      std::cout << "1. Iniciar partido" << '\n';
      std::cout << "2. salir" << '\n';
      std::cin >> opcion2;

      if(opcion2==1){
         //iniciar partida
      }
      else{
         close(sd);
         std::cout << "salir" << '\n';
         return 0;
      }
   }
}
