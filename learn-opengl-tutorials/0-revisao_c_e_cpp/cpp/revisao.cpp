/* compile with:
   g++ revisao.cpp -o revisao
 */

using namespace std; /* .h is not used anymore, need this to use C libs*/
#include <iostream>
#include <cmath> /* c libs start with c */
#include <fstream>

// comment

int a = 17;

int main(){
   double a;

   a = 1.2;
   a = sin (a);

   cout << a << endl; // endl is end of line
   cout << "Type your favorite number: ";
   cin >> a;

   cout << "Your favorite number is " << a << endl;

   int x; // variables can be declared anywhere

   {
     int a = 1;
     // a is 1 only inside here!
     cout << a << endl;
   }

   for (int a = 0; a < 3; a++) // local declaration of a
     cout << a << endl;

   cout << a << endl;

   // global variables can be accessed even with locals with the same name
   cout << ::a << endl;

   double &b = a; //this means that b IS a

   return 0;
}

/* declaration of namespaces */
namespace first{
  int a;
  int b;
}

namespace second {
  double a;
  double b;
}

void func(){
  first::a = 1;

  second::a = 6.4516;

  /* exceptions */

  try{
    if (a > 100) throw 100;
    if (a < 100) throw 10;
  }
  catch (int result){
    cout << "result is " << result << endl;
  }
}

// default parameters
void func2(double a = 3){

}

// operator overloading (redefine operators)
char operator * (char a, char b){
  return strcat(a, b);
}

// template functions
template <class ttype>
ttype minimum(ttype a, ttype b){
  ttype r;
  r = a;
  if (b<a) r = b;
  return r;
}
// now we can use minimum with int double or whatever arguments!
// minimum(3.7, 2.353);
// minimum(1, 5);
// we can also use different types with template< <class type1, class type2>

// new and delete instead of malloc and free
void func3(){
  double *d;
  d = new double;
  *d = 3.5;
  delete d;

  d = new double[15];
  delete [] d;
}

// halelluia! structs can contain functions
struct vector1{
  double x;
  double y;

  struct vector1 dot(vector1 b){
    struct vector1 r;
    r.x = x*b.x;
    r.y = y*b.y;
    return r;
  }
};

// a class is a struct that keeps its data hidden

class vector2{
  public: // allows data to be accessed and modified

  double x;
  double y;
  static int count; //this variable will have only one instance, shared by all instances of the class. Must be initialized outside the class (int vector2::count = 0;)

  // constructor methods are called automatically when an instance is created
  vector2(){
    x = 0;
    y = 0;
  }

  // destructor
  ~vector2(){
    // delete stuff...
  }

  void be_opposited(){
      x = -x;
      y = -y;
   }

  void func(){
    this->be_opposited();
  }

};

void func4(){
  vector2 a;
  a.be_opposited();
}

// class derivation
class trivector: public vector2{
  public:
  double z;
  protected: // accessible only to methods of the class and derived classes
  char password;
  private: // accessible only to methods of the class
  char secret;
};

//files

void func5(){
  fstream f;
  f.open("test.txt", ios::out);
  f << "text" << endl;
  f.close();

  fstream g;
  g.open("test2.txt", ios::in);
  f.close();
}
