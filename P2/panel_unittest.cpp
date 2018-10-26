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
TEST(Panel, BusquedaBombas){
   Panel prueba;
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
   prueba.setMatrix1(0, 0, -1);
   prueba.setMatrix1(0, 9, -1);
   prueba.setMatrix1(9, 0, -1);
   prueba.setMatrix1(9, 9, -1);
   prueba.busquedaBombas();

   prueba.comprobacionCeros(4, 4);
   for(int i=0; i<10; i++){
      for(int j=0; j<10; j++){
         std::cout << prueba.getMatrix2()[i][j] << " ";
      }
      std::cout << std::endl;
   }
}
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
