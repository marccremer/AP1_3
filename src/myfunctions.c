/*myfunctions.c */
#include "myfunctions.h"


int sucheZeichen(const char str[], char c){
	int foundchars = 0;
	for(int i=0; str[i] != '\0'; i++){
		if (str[i] == c )
		{
			foundchars += 1;
		}
	}
	return foundchars;
}

int laengeZeichenkette(const char str[]){
	int length = 0 ;
	for(int i=0; str[i] != '\0'; i++){
		length += 1;
	}
	return length;
}