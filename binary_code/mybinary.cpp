#include <cstdio>

void print_hello(){
  printf("Hello\n");
}

void AccessAcc(){
  printf("AccessAcc\n");
}

void AccessMag(){
  printf("AccessMag\n");
}

void AccessProx(){
  printf("AccessProx\n");
}

void AccessLight(){
  printf("AccessLight\n");
}

void AccessImage(){
  printf("AccessImage\n");
}

int main(){
	printf("Before Call\n");
 // print_hello();
 // AccessAcc();
//  AccessMag();
//  AccessProx();
  AccessImage();
  
  printf("After Call\n");
	return 0;
}
