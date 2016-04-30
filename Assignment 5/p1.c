#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 

struct p* s; 

struct p{ 
int* a; 
int* b; 
};


int main() { 
s = malloc (sizeof(struct p));

s->a = malloc (sizeof(8)); 
s->b = malloc (sizeof(8)); 

s->a[0] = 1; 
s->a[1] = 2; 
s->b[0] = 3; 
s->b[1] = 4; 
s->b[0] = s->a[1];
s->a[0] = s->b[1]; 
 

printf( "%d\n%d\n%d\n%d\n", s->a[0],s->a[1],s->b[0],s->b[1]); 




return 0; 
}