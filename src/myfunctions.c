/*myfunctions.c */
int sucheZeichen(const char str[], char c){
	//int length = strlen(str);
	int foundchars = 0;
	for(int i=0; str[i] != '\0'; i++){
		if (str[i] == c )
		{
			//printf("found\n");
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