/*prak3_3.c
Schreiben Sie ein Programm zur Lagerverwaltung. Wir wollen hierzu ein struct verwenden,
das die folgenden Komponenten hat:
char artikel[laengeArtikel];
int anzahl;
Das Array lager[anzahlEintraege] enthält dann als Array-Elemente die Informationen zu
Artikeln gemäß der obigen Struktur.
Folgende Funktionen sollen geschrieben werden:
▪ Artikel hinzufügen.
Ein Artikel mit Anzahl soll in die Lagerliste eingetragen werden, falls noch Platz ist
und falls der Artikel noch nicht existiert. Falls der Artikel bereits vorhanden ist, soll
die Anzahl entsprechend erhöht werden.
▪ Artikel entnehmen.
Geben Sie einen Artikel ein und geben Sie an, wie viele Exemplare aus dem Lager
entnommen werden. Aktualisieren Sie die Anzahl. Beachten Sie den Fall, dass der
Artikel nicht existiert, und den Fall, wo nicht genügend Exemplare auf Lager sind.
Erzeugen Sie dann entsprechende Meldungen für den Anwender.
▪ Eintrag suchen.
Für einen Artikel soll ausgegeben werden, welche Anzahl noch im Lager ist.
Formulieren Sie auch hier alle möglichen Meldungen an den Anwender.
▪ Lager als Tabelle ausgeben.
Hier soll eine Tabelle mit den Spalten Artikel und Anzahl ausgegeben werden. Am
Ende der Tabelle sollen die Anzahlen addiert werden, damit man weiß, wie viele
Artikel insgesamt im Lager sind.
▪ Schreiben Sie eine Menüsteuerung, durch die sich die einzelnen Funktionen aufrufen
lassen.
Hinweise:
▪ Sie werden in der Aufgabe Zeichenketten vergleichen müssen. Verwenden Sie hierzu
die Bibliotheksfunktion int strcmp(const char *s1, const char *s2) .
▪ Schreiben Sie alle Funktionen in das main -Programm. Sie sollen für dieses Beispiel
kein make und keine separate Übersetzung verwenden.
Marc Cremer 2019 */

#include <stdio.h>

 struct Artikel {
	int id;
	char name[10];
	int anzahl;
};

struct Artikel createartikel(int id);
void artikelhinzufuegen(int anzahl,char name[]);
void artikelentnehmen(int id);
int findeartikelid(char name[]);
int anzahlartikel(int id);
void printlagertabelle();
void printmenues(int menueid);

int main(int argc, char const *argv[])
{

	const int lagergroese = 200; /* variable size requiers memory alloc */
	struct Artikel lager[lagergroese];
	int next_free_id = 0;
	int optionpicked;
	int finished = 0;
	while (finished != 1){
		int submenu = 0;
		printf("Willkommen zum Lagersystem Cremer\n");
		printmenues(1);
		fflush(stdin);
		scanf("%i",&optionpicked);
		switch(optionpicked){
			case 1:
				/*submenu Artikelverwaltung*/
				printmenues(2);
				submenu = 1;
				scanf("%i",&optionpicked);
				break;
			case 2:
				/*Lager tabelle*/
				printf("debug1\n");
				break;
			case 3:
				/*Programm beenden*/
				printf("debug2\n");
				finished =1;
				break;
			default:
				printf("Das habe ich leider nicht verstanden\n\n");
				break;
		}
		if (submenu == 1)
		{
			switch(optionpicked){
				case 1:
					printf("debug3\n");
				case 2:
					printf("debug4\n");
				case 3:
					/*Artikel hinzufügen*/
					if (next_free_id > lagergroese )
					{
						printf("Leider ist das Lager voll\n");
						break;
					}
					lager[next_free_id] = createartikel(next_free_id);
					printf("Artikel erstellst mit id:%i\n",lager[next_free_id].id );
					next_free_id+=1;
				case 4:
					submenu = 0;
					break;
				default:
					printf("Das habe ich leider nicht verstanden\n");
			}
		}

		
	}
	return 0;
}

void printmenues(int menueid){
	int succes;
	switch(menueid){
		case 1:
			printf("Hauptmenü\n");
			printf("Bitte wählen sie option (1-3)\n");
			printf("1 :Artikelverwaltung\n");;
			printf("2 :Lager komplett als Tabelle ausgeben\n");
			printf("3 :Programm beenden\n");
		break;
		case 2:
			printf("Arikelverwaltung\n");
			printf("Bitte wählen sie option (1-4)\n" );
			printf("1 :Arikel suchen\n");
			printf("2 :Artikel entnehmen\n");
			printf("3 :Artikel hinzufügen\n");
			printf("4 :Zurück zum Hauptmenü\n");
			break;
		default:
			printf("wrong function argument\n");
			break;
	}
}

struct Artikel createartikel(int id){
	struct Artikel newartikel = { id,"marc",0};
	return newartikel;
}
