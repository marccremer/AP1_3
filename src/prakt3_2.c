/*Organisieren Sie den Code aus Aufgabe 1 um. Verwenden Sie Funktionsdeklarationen für
sucheZeichen(...) und laengeZeichenkette(...) und schreiben Sie diese in die Headerdatei
myfunctions.h . Verschieben Sie den Code der beiden Funktionen in die Datei
myfunctions.c . Verschieben Sie das Mainprogramm in die Datei mymain.c . Schreiben Sie ein
make -File mymake.mak , das das Programm myprogram generiert.
Marc Cremer */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "myfunctions.h"


int main(int argc, char const *argv[])
{
	char name[40];
	char csuche;
	printf("Bitte Namen eingeben:");
	scanf("%s",&name[0]);
	printf("\n");
	char answer;
	int notfinished = 0;
	int runs = 0;
	while(notfinished == 0){
		printf("Möchtest Du nach einem Buchstaben in Isabella suchen (j / n)?:\0");
		fflush(NULL);
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
			default :
			printf("Entschuldigung das habe ich nicht versttanden\n");
			break;
		}
	}
return 0;
}
