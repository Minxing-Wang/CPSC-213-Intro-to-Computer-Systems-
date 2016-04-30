#include <stdio.h>

int c[4] ; 

int foo(int a, int b, int c){
	 
	if((a>= 10) && (a<=18)){
		switch(a){
			case 10: return b+c;  
			case 11: return 0; 
			case 12: return -c+b; 
			case 13: return 0; 
			case 14: if((-c+b) >= 0 ){
							return 1; 
					 }else {
						return 0; 
					  }
			case 15: return 0; 
			case 16: if((-b + c)>= 0){
						return 1; 
				     }else {
						return 0; 
					  }
			case 17: return 0; 
			case 18: if((-c+b) == 0){
						return 1; 
					 }else {
				return 0; 
					  }
		}	 

	}else{
		return 0; 
	 }
	return 0; 
}

int main() {
	c[3] = foo(c[0], c[1], c[2]); 
}