#include <stdlib.h>#include <stdio.h>#include <SIOUX.h>void main(void){	tSIOUXSettings mySIOUXSettings={TRUE,TRUE,TRUE,FALSE,FALSE,0,0,80,24,0,0,monaco,9,normal};	SIOUXSettings=mySIOUXSettings;	printf("char -> %d bytes\n",sizeof(char));	printf("int -> %d bytes\n",sizeof(int));	printf("short -> %d bytes\n",sizeof(short));	printf("long -> %d bytes\n",sizeof(long));	printf("float -> %d bytes\n",sizeof(float));	printf("double -> %d bytes\n",sizeof(double));	printf("long double -> %d bytes\n",sizeof(long double));}