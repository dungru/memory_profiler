#include <stdio.h>

int main(int argc, char const *argv[])
{
	malloc(100);
	malloc(20);
	malloc(30);
	malloc(40);
	printf("hello malloc\n");
	return 0;
}