/* Marc Cremer 2019
Nimmt einen String und einen Char und gibt die Haeufigkeit
des Chars's im String aus */

#include <stdio.h> //printf,scanf,fflush

int sucheZeichen(const char str[], char c);
int laengeZeichenkette(const char str[]); //wird nicht benutz wurde aber verlangt

int main(int argc, char const *argv[])
{
	char name[40];			//der string der durchsucht wird
	char csuche; 			//der gesuchte char
	char answer;			//menuesteuerung
	int notfinished = 0;	//menuesteuerung

	printf("Bitte Namen eingeben:");
	scanf("%s",name);
	printf("\n");

	while(notfinished == 0){
		printf("Möchtest Du nach einem Buchstaben in \"%s\" suchen (j / n)?:\0",name); // das \0 schneidet die newline ab
		fflush(NULL);//buffer clear
		scanf(" %c",&answer);
		fflush(NULL);
		printf("\n");
		switch(answer){
			case 'j':
				printf("Bitte Buchstaben eingeben:\0");
				scanf(" %c",&csuche);
				fflush(NULL);
				printf("Der Buchstabe %c kommt %i-mal vor.\n",csuche,sucheZeichen(name,csuche));
				break;
			case 'n':
				printf("Auf Wiedersehen!\n");
				notfinished = 1;
				break;
			default : //falls etwas unerwartetes eingegeben wurde
			printf("Entschuldigung das habe ich nicht versttanden\n");
			break;
		}
	}
return 0;
}

int sucheZeichen(const char str[], char c){
	//iteriert ueber den charrarray str bis zu einem 0-byte und zaelt Haufigkeit von c
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
	//iteriert ueber den charrarray str bis zu einem 0-byte und gibt die array laenge aus
	int length = 0 ;
	for(int i=0; str[i] != '\0'; i++){
		length += 1;
	}
	return length;
}