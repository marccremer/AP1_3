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




struct Artikel createartikel(int id,char *str) ;		//returns a Artikel struct with anzahl 0
void artikelentnehmen(int id);							//reduces anzahl by 1 for Artikel with id "id"
int artikel_exists(char name[],struct Artikel lagere[],int size);	//checks if the Artikel mit name "name" exists in "lagere"
int findeartikelid(char name[],struct Artikel lagerf[],int size);	// returns the id  of Artikel with "name" or -1 if the article doesnt exists 
int anzahlartikel(int id);									//returns the anzahl of artikel mit id "id"
void clearstructin(struct Artikel lagerc[],int pos);	//sets a struct in lager to 0 in each field
int artikelindex(int id,struct Artikel lager[],int saturation); //returns the index of the Artikel with id "id"

void printlagertabelle(struct Artikel art);					//print the lagertable formated
void printmenues(int menueid);								//print a selection of menues
void clearscreen();										//prints enough newline chars to clear the console
int readoption();										//reads the input for the menues

int loadsaturation();									//loads the number of diffrent Artikels
void savesaturation(int sat);							//saves the number of diffrent Artikels
void write_lager_to_file(struct Artikel lager[],int size); //write the array to a binfile
void read_lager_from_file(struct Artikel lager[],int size); //load data from a binfile into the array

int main(int argc, char const *argv[])
{

	const int lagergroese = 200; /* variable size requires memory alloc */
	struct Artikel lager[lagergroese] ;
	int saturation = loadsaturation();
	int next_free_id = saturation-1;
	int optionpicked;
	int finished = 0;
	char newname[10];
	int newanzahl;
	int newid;
	int submenu = 0;
	char lasterror[60] = "";
	char spalteid[3] = "id";
	char spalteArtikelname[12] = "Artikelname";
	char spalteAnzahl[] = "Anzahl";

	printf("Willkommen zum Lagersystem Cremer\n");
	//load from file
	read_lager_from_file(lager,lagergroese);
	//read staturation
	for (int i = saturation; i < lagergroese; ++i)
	{
		clearstructin(lager,i);
	}

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

					printf("|%4s|%13s|%6s|\n",spalteid,spalteArtikelname,spalteAnzahl);				
					for (int i = 0; i < saturation; ++i)
						{
							printlagertabelle(lager[i]);
						}
					break;
				case 3:
					/*Programm beenden*/
					write_lager_to_file(lager,lagergroese);
					savesaturation(saturation);
					printf("Auf Wiedersehen sat:%i\n",saturation);
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
					printf("Name des Artikels?:");
					fflush(NULL);
					scanf("%s",newname);
					printf("\n");
					printf("Wieviel verlassen das lager?\n");
					fflush(NULL);
					scanf("%i",&newanzahl);
					newid = findeartikelid(newname,lager,saturation);
					if (newid < 0)
					{
						printf("Dieser Artikel existiert leider nicht\n" );
					}else{
						if (lager[ artikelindex(newid,lager,saturation) ].anzahl == 0 )
						{
							printf("0 artikel take\n");
						}
					}
					break;
				case 3:
					/*Artikel hinzufügen*/
					if (saturation >= lagergroese )
					{
						printf("Leider ist das Lager voll\n");
						break;
					}
					printf("Name des neuen Artikels?:");
					fflush(NULL);
					scanf("%s",newname);
					printf("\n");
					printf("Wieviel kommen ins lager?\n");
					fflush(NULL);
					scanf("%i",&newanzahl);
					newid = findeartikelid(newname,lager,saturation) ;
					if (newid < 0) //komplett neuer Aritkel
					{
						lager[next_free_id] = createartikel(next_free_id,newname);
						lager[next_free_id].anzahl = newanzahl;
						next_free_id++ ;
						printf("Artikel erstellst mit id:%i name:%s anzahl:%i\n\n",lager[next_free_id].id,lager[next_free_id].name,lager[next_free_id].anzahl);
						next_free_id++;
						saturation++;
					}else{
						lager[newid].anzahl += newanzahl;
						printf("Artikel hinzufügt\nNeue Anzahl an \"%s\": %i Stück\n",newname,lager[newid].anzahl);
					}
					break;
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

struct Artikel createartikel(int id,char *str){
	struct Artikel newartikel;
	newartikel.id = id;
	strcpy(newartikel.name,str);
	newartikel.anzahl = 0;
	return newartikel;
}

void artikelentnehmen(int id){
	/*TODO */
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

int findeartikelid(char name[],struct Artikel lagerf[],int size){
	/* returns the id or -1 if the article doesnt exists */
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

int anzahlartikel(int id){
	/*TODO*/
}

void clearstructin(struct Artikel lagerc[],int pos){
	lagerc[pos].id = 0;
	lagerc[pos].name[0] = '\0';
	lagerc[pos].anzahl = 0;
}

int artikelindex(int id,struct Artikel lager[],int saturation){
	int i;
	for ( i = 0; i < saturation; ++i)
	{
		if(lager[i].id == id)
		{
			return i;
		}
	}
}								

void printlagertabelle(struct Artikel art){
	printf("|  %*i|%*s|  %*i|\n",2,art.id,10,art.name,4,art.anzahl );
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

void clearscreen(){
	struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    for (int i = 0; i < w.ws_row; ++i)
    {
    	printf("\n");
    }
}

int readoption(){
	int option;
	fflush(stdin);
	scanf("%i",&option);
	return option;
}

int loadsaturation (){
  FILE *fptr; //open a file buffer 
	if ((fptr = fopen("./lagereigenschaften.txt","r")) == NULL){
		printf("Error! opening file");
		// Program exits if the file pointer returns NULL.
		exit(1);
		}
  int i = 0;

  fscanf (fptr, "%d", &i);    
  fclose (fptr);   
  return i;     
}
 
 void savesaturation(int sat){
 	FILE *fptr ; //open a file buffer
	if ((fptr = fopen("./lagereigenschaften.txt","w+")) == NULL){
		printf("Error! opening file");
		// Program exits if the file pointer returns NULL.
		exit(1);
		}

  fprintf (fptr, "%d", sat);    
  fclose (fptr);   
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