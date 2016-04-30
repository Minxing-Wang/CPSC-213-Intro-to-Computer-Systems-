#include <stdio.h>
#include <stdlib.h>

int x[] = {1,2,3,0xffffffff,0xfffffffe,0,184,340057058}; 
int y[8]; 

void foo(){	
	int l0; 
	int i ; 
	for(i=8; i>=0; i--){
		y[i-1] = bar(x[i-1]);
	}
}

int bar(int z) {
	int x=0; 
	while (z != 0 ){
		if ((z & 0x80000000) != 0 ) {
			z=z<<1;
			x++;
		} else {
			z=z<<1;	
		  }
	}
 return x;
}


int main() {
	foo();
	int a; 
	int b; 
	for(a = 0; a < 8 ; a ++){
		printf("%d", x[a]);
		printf("\n");
	}

	for(b=0;b<8;b++){
		printf("%d",y[b]);
		printf("\n");	
	}

	return 0; 
}