#include <stdio.h>
#include <string.h> /* use strings */
#include <stdlib.h> /* stuff like malloc */
#define NUMBER 3

/* header files */
#include "revisao.h"

/* int main(int argc, char *argv[]) */

int main(){
  const int OTHER = 5;
  int x, i;

  printf("Storage size for int: %ld \n", sizeof(int));
  printf("Storage size for float: %ld \n", sizeof(float));
  printf("My favorite number is: %d \n", NUMBER);
  printf("I also like %d \n", OTHER);

  printf ("Entre com um inteiro: ");
  scanf ("%d", &x);
  printf ("Numero digitado: %d\n", x);

  /* conditionals and loops */

  if (x == 3)
  {
    printf("yay\n");
  }
  else if(x == 4)
  {
    printf("odear\n");
  }
  else
  {
    printf("Not this time \n");
  }

  x == 3 ? printf("good one \n") : printf("bad one \n");

  switch( x ){
  case 3:
    printf("ohaimark\n");
    break;
  case 4:
    printf("ohaidenny\n");
    break;
  default :
    printf("ohailisa\n");
    break;
  }

  while ( x == 3 ){
    printf("enter new x: ");
    scanf("%d", &x);
  }

  for(i=0 ; i<x; i++){
    printf("%d ", i);
  }


  do{
    printf("OUHAIE\n");
    i--;
  }while(i > 0);

  /* arrays and pointers */

  char n[10];
  n[3] = 'b';

  printf("Adress of n variable: %x \n", &n);
  int var = 20;
  int *p;
  p = &var;
  printf("Adress of var variable: %x\n", &var);
  printf("Adress stored in p variable: %x\n", p);
  printf("Value of *p variable: %d\n", *p);

  char *ptr = NULL; /* assign null to pointer when you don't have an exact address to asign*/

  /* the array name is a constant pointer to the first element of the array*/
  ptr = n;
  /* n is a pointer to &n[0] */

  /* strings */

  char str[5] = "ohai";
  char str2[5];
  strcpy(str2, str);
  strcat(str, str2); /*concat*/

  return 0;
}

/* function returning the max between two numbers */
/* parameters of functions take precedence over global variables */
int max(int num1, int num2) {

   /* local variable declaration */
   int result;

   if (num1 > num2)
      result = num1;
   else
      result = num2;

   return result;
}

/* to pass an array as argument: */
void func(int *param){}

void func2(int param[10]){}

void func3(int param[]){}

/* you can't return arrays from functions, but you can return its pointer*/

int * func4(){}

/* structures */

struct Gaem {
  char title[50];
  int id;
};

/* or */

typedef struct Game{
  char title[50];
  int id;
} Game;

int func5(){
  struct Gaem Mario;

  strcpy(Mario.title, "Super Mario World");
  Mario.id = 1;

  /* pointers to structures */

  struct Gaem* ptr;
  ptr = &Mario;
  printf("Gaem Title: %s\n", ptr->title);

  return Mario.id;
}

/* structs as arguments */
int func6(struct Gaem gaem){

}

/* files */
int func7(){
  FILE * fp;

  fp = fopen("path", "w+");
  fprintf(fp, "This is testing for fprintf...\n");
  fputs("This is testing for fputs...\n", fp);
  fclose(fp);

  return 1;
}

/* memory */

void func8(){
  char name[100];
  char *description;

  strcpy(name, "Patrick");
  description = malloc(30*sizeof(char));

  description = realloc(description, 100*sizeof(char));

  free(description);
}
