#include<unistd.h>
#include<stdio.h>

int main(void) {
	char mem[20];
	read(0,mem,10);
	write(1,mem,10);
	printf("\n");
}
