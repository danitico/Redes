#include "Panel.hpp"
#include "gtest/gtest.h"

TEST(Panel, Constructor){
   Panel prueba;

   EXPECT_EQ(0, prueba.getbanderasA());
   EXPECT_EQ(0, prueba.getbanderasB());
   EXPECT_EQ(-1, prueba.getSocket1());
   EXPECT_EQ(-1, prueba.getSocket2());

   EXPECT_EQ(10, prueba.getMatrix1().size());
   for(int i=0; i<10; i++){
      EXPECT_EQ(10, prueba.getMatrix1()[i].size());
   }

   EXPECT_EQ(10, prueba.getMatrix2().size());
   for(int i=0; i<10; i++){
      EXPECT_EQ(10, prueba.getMatrix2()[i].size());
   }

   for (int i = 0; i < 10; ++i){
      for (int j = 0; j < 10; ++j){
         EXPECT_EQ(prueba.getMatrix2()[i][j], "-");
      }
   }
}
TEST(Panel, BusquedaBomba){
   Panel prueba;
   for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
         prueba.setMatrix1(i, j, 0);
      }
   }
   std::vector<std::vector <int> > objetivo(10, std::vector<int>(10, 0));

   for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
         if(i==j){
            prueba.setMatrix1(i, j, -1);
            objetivo[i][j]=-1;
         }
      }
   }
   prueba.setMatrix1(0, 9, -1);
   prueba.setMatrix1(9, 0, -1);
   prueba.busquedaBombas();

   int j=0;
   for(int i=2; i<10; i++){
      objetivo[i][j]=objetivo[j][i]=1;
      j++;
   }

   j=0;
   for(int i=1; i<10; i++){
      objetivo[i][j]=objetivo[j][i]=2;
      j++;
   }
   objetivo[0][9]=objetivo[9][0]=-1;
   objetivo[0][8]=objetivo[1][8]=objetivo[1][9]=objetivo[8][0]=objetivo[8][1]=objetivo[9][1]=1;


   EXPECT_EQ(objetivo, prueba.getMatrix1());

   // for(int i=0; i<10; i++){
   //    for(int j=0; j<10; j++){
   //       std::cout << objetivo[i][j] << " ";
   //    }
   //    std::cout << std::endl;
   // }

   //esta es la matriz que he montado. busquedaBombas nos deberia de dar esta misma.
   /*
      -1  2  1  0  0  0  0  0  1 -1
       2 -1  2  1  0  0  0  0  1  1
       1  2 -1  2  1  0  0  0  0  0
       0  1  2 -1  2  1  0  0  0  0
       0  0  1  2 -1  2  1  0  0  0
       0  0  0  1  2 -1  2  1  0  0
       0  0  0  0  1  2 -1  2  1  0
       0  0  0  0  0  1  2 -1  2  1
       1  1  0  0  0  0  1  2 -1  2
      -1  1  0  0  0  0  0  1  2  -1
   */
}
TEST(Panel, CompruebaCeros){
   Panel prueba;
   for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
         prueba.setMatrix1(i, j, 0);
      }
   }
   prueba.setMatrix1(0, 0, -1);
   prueba.setMatrix1(4, 0, -1);
   prueba.setMatrix1(7, 7, -1);
   for(int i=0; i<10; i++){
      prueba.setMatrix1(i, 4, -1);
   }
   prueba.busquedaBombas();


   // prueba.comprobacionCeros(2, 2);
   prueba.comprobacionCeros(5, 7);
   for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
         std::cout << prueba.getMatrix2()[i][j] << " ";
      }
      std::cout << std::endl;
   }
}
TEST(Panel, diez_banderas){
   Panel prueba, prueba1;
   for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
         prueba.setMatrix1(i, j, 0);
         prueba1.setMatrix1(i, j, 0);
      }
   }
   std::map<int, std::string> usuarios;
   usuarios[1]="pipo";
   usuarios[2]="pipo1";

   prueba.setSocket1(1);
   prueba.setSocket2(2);
   prueba1.setSocket1(1);
   prueba1.setSocket2(2);

   prueba.setMatrix1(1, 1, -1);
   prueba.setMatrix1(4, 9, -1);
   prueba.setMatrix1(3, 5, -1);
   prueba.setMatrix1(2, 5, -1);
   prueba.setMatrix1(1, 2, -1);
   prueba.setMatrix1(7, 7, -1);
   prueba.setMatrix1(4, 5, -1);
   prueba.setMatrix1(4, 0, -1);
   prueba.setMatrix1(1, 5, -1);
   prueba.setMatrix1(3, 2, -1);

   EXPECT_EQ(prueba.ponerBandera(1, (char*)"B", 1, usuarios), "");
   EXPECT_EQ(prueba.ponerBandera(4, (char*)"J", 1, usuarios), "");
   EXPECT_EQ(prueba.ponerBandera(3, (char*)"F", 1, usuarios), "");
   EXPECT_EQ(prueba.ponerBandera(2, (char*)"F", 1, usuarios), "");
   EXPECT_EQ(prueba.ponerBandera(1, (char*)"C", 1, usuarios), "");
   EXPECT_EQ(prueba.ponerBandera(7, (char*)"H", 1, usuarios), "");
   EXPECT_EQ(prueba.ponerBandera(4, (char*)"F", 1, usuarios), "");
   EXPECT_EQ(prueba.ponerBandera(4, (char*)"A", 1, usuarios), "");
   EXPECT_EQ(prueba.ponerBandera(1, (char*)"F", 1, usuarios), "");
   EXPECT_EQ(prueba.ponerBandera(3, (char*)"C", 1, usuarios), "+Ok. " + usuarios[1] + " ha ganado.\n");

   prueba1.setMatrix1(1, 1, -1);
   prueba1.setMatrix1(4, 9, -1);
   prueba1.setMatrix1(3, 5, -1);
   prueba1.setMatrix1(2, 5, -1);
   prueba1.setMatrix1(1, 2, -1);
   prueba1.setMatrix1(7, 7, -1);
   prueba1.setMatrix1(4, 5, -1);
   prueba1.setMatrix1(4, 0, -1);
   prueba1.setMatrix1(1, 5, -1);
   prueba1.setMatrix1(3, 2, -1);

   EXPECT_EQ(prueba1.ponerBandera(1, (char*)"B", 2, usuarios), "");
   EXPECT_EQ(prueba1.ponerBandera(4, (char*)"J", 2, usuarios), "");
   EXPECT_EQ(prueba1.ponerBandera(3, (char*)"F", 2, usuarios), "");
   EXPECT_EQ(prueba1.ponerBandera(2, (char*)"F", 2, usuarios), "");
   EXPECT_EQ(prueba1.ponerBandera(1, (char*)"C", 2, usuarios), "");
   EXPECT_EQ(prueba1.ponerBandera(7, (char*)"H", 2, usuarios), "");
   EXPECT_EQ(prueba1.ponerBandera(4, (char*)"F", 2, usuarios), "");
   EXPECT_EQ(prueba1.ponerBandera(4, (char*)"A", 2, usuarios), "");
   EXPECT_EQ(prueba1.ponerBandera(1, (char*)"F", 2, usuarios), "");
   EXPECT_EQ(prueba1.ponerBandera(9, (char*)"C", 2, usuarios), "+Ok. " + usuarios[2] + " ha perdido.\n");
}
TEST(Panel, ver_banderas_matrix){
   Panel prueba, prueba1;
   for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
         prueba.setMatrix1(i, j, 0);
         prueba1.setMatrix1(i, j, 0);
      }
   }
   std::map<int, std::string> usuarios;
   usuarios[1]="pipo";
   usuarios[2]="pipo1";

   prueba.setSocket1(1);
   prueba.setSocket2(2);

   prueba.ponerBandera(0, (char*)"A", 1, usuarios);
   prueba.ponerBandera(0, (char*)"A", 2, usuarios);
   prueba.ponerBandera(3, (char*)"A", 2, usuarios);
   prueba.ponerBandera(3, (char*)"A", 1, usuarios);
   prueba.ponerBandera(1, (char*)"C", 1, usuarios);
   prueba.ponerBandera(8, (char*)"C", 2, usuarios);

   EXPECT_EQ(prueba.getMatrix2()[0][0], "AB");
   EXPECT_EQ(prueba.getMatrix2()[3][0], "AB");
   EXPECT_EQ(prueba.getMatrix2()[1][2], "A");
   EXPECT_EQ(prueba.getMatrix2()[8][2], "B");
}
TEST(Panel, seleccionar_casilla){
   Panel prueba, prueba1;
   for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
         prueba.setMatrix1(i, j, 0);
         prueba1.setMatrix1(i, j, 0);
      }
   }
   std::map<int, std::string> usuarios;
   usuarios[1]="pipo";
   usuarios[2]="pipo1";

   prueba.setSocket1(1);
   prueba.setSocket2(2);

   prueba.setMatrix1(1, 1, -1);
   prueba.setMatrix1(4, 9, -1);
   prueba.setMatrix1(3, 5, -1);
   prueba.setMatrix1(2, 5, -1);

   prueba.busquedaBombas();
   EXPECT_EQ(prueba.seleccionarCasilla(1, (char*)"B", 1, usuarios), "Jugador " + usuarios[1] + " ha perdido la partida\n");

   prueba.seleccionarCasilla(1, (char*)"C", 1, usuarios);
   EXPECT_EQ(prueba.getMatrix2()[1][2], "1");
}
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
