/* to compile
   g++ -c vector.cpp
   g++ main.cpp vector.o -o test

   this way, the source code of vector.cpp only need be compiled once
   you can distribute .h and .o

   you can also do this with a makefile
   write

test20: main.o vector.o
   g++ main.o vector.o -o test20

main.o: main.cpp vector.h
   g++ -c main.cpp

vector.o: vector.cpp vector.h
   g++ -c vector.cpp

   and use: make test
 */

using namespace std;
#include <iostream>
#include "vector.h"

int main ()
{
   vector k;

   k.x = 4;
   k.y = 5;

   cout << "Surface: " << k.surface() << endl;

   return 0;
}
