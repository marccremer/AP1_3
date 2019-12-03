/* Aufgabe 1: Programmieren in C
▪ Schreiben Sie eine Funktion int sucheZeichen(const char s[], char c), wobei der
Rückgabewert der Häufigkeit des Characters c im Char-Array s entspricht.
▪ Schreiben Sie eine Funktion int laengeZeichenkette(const char s[]), die die Anzahl
der Zeichen (die Länge der Zeichenkette) als Rückgabewert liefert.
▪ Schreiben Sie dann ein Hauptprogramm, das eine kleine Menüsteuerung enthält, um nach
einem Buchstaben in einem Namen zu suchen.
Der Ablauf soll dann so aussehen:
Bitte Namen eingeben: Isabella
Isabella hat 8 Zeichen.
Möchtest Du nach einem Buchstaben in Isabella suchen (j / n)? j
Bitte Buchstaben eingeben: a
Der Buchstabe a kommt 2-mal vor.
Möchtest Du nach einem Buchstaben in Isabella suchen (j / n)? j
Bitte Buchstaben eingeben: k
Der Buchstabe k kommt 0-mal vor.
Möchtest Du nach einem Buchstaben in Isabella suchen (j / n)? n
Auf Wiedersehen!
Hinweise:
▪ Verwenden Sie aus Übungsgründen im Menü die switch Anweisung, die in den Case
Labels die Character j und n auswertet.
▪ Verwenden Sie fflush(stdin) aus der Bibliothek <stdio.h> , um Probleme mit dem
Tastaturpuffer bei der Eingabe zu */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

int sucheZeichen(const char str[], char c);
int laengeZeichenkette(const char str[]);

int main(int argc, char const *argv[])
{
	char name[40];
	char csuche;
	printf("Bitte Namen eingeben:");
	scanf("%s",name);
	printf("\n");
	char answer;
	int notfinished = 0;
	int runs = 0;
	while(notfinished == 0){
		printf("Möchtest Du nach einem Buchstaben in \"%s\" suchen (j / n)?:\0",name);
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