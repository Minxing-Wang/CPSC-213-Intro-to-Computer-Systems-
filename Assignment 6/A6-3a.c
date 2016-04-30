#include <stdio.h>
#include <stdlib.h>

int a[10]; 
int* z = a; 

void foo (int b, int c){
	*(z+c) = *(z+c) + b ;
}

void bar (){
	int l0 = 1; 
	int l1 = 2;
	foo(3,4); 
	foo(l0,l1); 
}

int main (){ 
	bar(); 
	int i;
	for(i = 0 ; i<=9 ; i++){
		printf("%d", *(z+i)); 
		printf("\n");
	}
	return 0;
}
