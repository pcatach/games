using namespace std;
#include "vector.h"

double vector::surface()
{
   double s = 0;

   for (double i = 0; i < x; i++)
   {
      s = s + y;
   }

   return s;
}
