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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>



 struct Artikel {
	int id;
	char name[10];
	int anzahl;
};



void write_lager_to_file(struct Artikel lager[],int size);
void read_lager_from_file(struct Artikel lager[],int size);
struct Artikel createartikel(int id,char *str) ;
void artikelhinzufuegen(int anzahl,char name[]);
void artikelentnehmen(int id);
int artikel_exists(char name[],struct Artikel lagere[],int size);
int findeartikelid(char name[],struct Artikel lagerf[],int size);
int anzahlartikel(int id);
void printlagertabelle(struct Artikel art);
void printmenues(int menueid);
void clearscreen();
int readoption();

int main(int argc, char const *argv[])
{

	const int lagergroese = 200; /* variable size requiers memory alloc */
	struct Artikel lager[lagergroese] ;
	int next_free_id = 0;
	int saturation = 0;
	int optionpicked;
	int finished = 0;
	char newname[10];
	int newanzahl;
	int submenu = 0;
	char lasterror[60] = "";

	printf("Willkommen zum Lagersystem Cremer\n");
	//load from file
	read_lager_from_file(lager,lagergroese);

	while (finished != 1){
		//clearscreen();
		printf("%s\n",lasterror );
		strcpy(lasterror,"");
		if (submenu == 0){
			printmenues(1);
			fflush(stdin);
			scanf("%i",&optionpicked);
			switch(optionpicked){
				case 1:
					/*submenu Artikelverwaltung*/	
					submenu = 1;
					break;
				case 2:
					/*Lager tabelle*/
					printf("|  id|      name|Anzahl|\n");				
					for (int i = 0; i < saturation; ++i)
						{
							printlagertabelle(lager[i]);
							printf("lager[%i] id:%i\n",i,lager[i].id );
						}
					break;
				case 3:
					/*Programm beenden*/
					write_lager_to_file(lager,lagergroese);
					printf("Auf Wiedersehen\n");
					finished =1;
					break;
				default:
					strcpy(lasterror,"->>>>>Tut mir leid das habe ich leider nicht verstanden\n");
					break;
				}
		}else{
			printmenues(2);
			optionpicked = readoption();
			printf("debub66\n");
			switch(optionpicked){
				case 1: //suchen
					printf("Wie heist der Artikel den sie suchen:");
					fflush(NULL);
					scanf("%s",newname);

					break;
				case 2: //entnehmen
					printf("debug4\n");
					break;
				case 3:
					/*Artikel hinzufügen*/
					if (saturation >= lagergroese )
					{
						printf("Leider ist das Lager voll\n");
						break;
					}
					printf("Name des neuen Artikels?:");
					scanf("%s",newname);
					printf("\n");
					printf("Wieviel kommen ins lager?\n");
					scanf("%i",&newanzahl);
					if (findeartikelid >= 0)
					{
						printf("Der Artikel:%s  wurde erstellt\n", newname);
					}
					lager[next_free_id] = createartikel(next_free_id,newname);
					printf("Artikel erstellst mit id:%i name:%s anzahl:%i\n\n",lager[next_free_id].id,lager[next_free_id].name,lager[next_free_id].anzahl);
					next_free_id+=1;
					saturation+=1;
				case 4:
					submenu = 0;
					break;
				default:
					strcpy(lasterror,"->>>>>Tut mir leid das habe ich leider nicht verstanden\n");
					break;
			}
		}
		
	}
	return 0;
}

void clearscreen(){
	struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    for (int i = 0; i < w.ws_row; ++i)
    {
    	printf("\n");
    }
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

struct Artikel createartikel(int id,char *str){
	struct Artikel newartikel;
	newartikel.id = id;
	strcpy(newartikel.name,str);
	newartikel.anzahl = 0;
	return newartikel;
}

int readoption(){
	int option;
	fflush(stdin);
	scanf("%i",&option);
	return option;
}

void printlagertabelle(struct Artikel art){
	printf("|  %*i|  %*s|  %*i|\n",2,art.id,8,art.name,4,art.anzahl );
}

void read_lager_from_file(struct Artikel lager[],int size){
  FILE *fptr; //open a file buffer
  if ((fptr = fopen("./lager.bin","rb")) == NULL){
    printf("Error! opening file");
    // Program exits if the file pointer returns NULL.
    exit(1);
  }
  struct Artikel newartikel;
  if(fptr != NULL){
    
    fread(lager,sizeof(struct Artikel),size,fptr);
    fclose(fptr);}
  
}

void write_lager_to_file(struct Artikel lagerw[],int size){
    FILE *fptr; //open a file buffer
    int n;
    if ((fptr = fopen("./lager.bin","wb")) == NULL){
    printf("Error! opening file");
    // Program exits if the file pointer returns NULL.
    exit(1);
  }

    fwrite(lagerw, sizeof(struct Artikel), size, fptr);

  fclose(fptr);
}

int artikel_exists(char name[],struct Artikel lagere[],int size){
	int returnvalue = 0;
	for (int i = 0; i < size; ++i)
	{
		if(strcmp (lagere[i].name,name) == 0)
			returnvalue = 1;
	}
	return returnvalue;
}

void clearstructin(struct Artikel lagerc[],int pos){
	lagerc[pos].id = 0;
	lagerc[pos].name[0] = '\0';
	lagerc[pos].anzahl = 0;
}

int findeartikelid(char name[],struct Artikel lagerf[],int size){
	int returnvalue;
	for (int i = 0; i < size; ++i)
	{
			if(strcmp (lagerf[i].name,name) == 0){
				returnvalue = i;
				break;
			}else
			{returnvalue = -1;
			}
	}
	return returnvalue;

}