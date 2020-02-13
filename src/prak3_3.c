/*prak3_3.c
Ein Lagerverwaltungsprogramm.
Artikel werden mit ID,NAME und ANZAHL abgepeichert.
Zum Programm gehoeren auch lagereigenschaften.txt und lager.bin.
Wenn nicht vorhanden muessen vom user erstellt werden
Marc Cremer 2019 */

#include <stdlib.h>		//exit()
#include <stdio.h>		//printf and scanf
#include <string.h>		//strcmp
#include <sys/ioctl.h>	//file open



 struct Artikel {
	int id;
	char name[20];
	int anzahl;
};




struct Artikel createartikel(int id,char *str) ;		//returns a Artikel struct with anzahl 0
void artikelentnehmen(int pos,struct Artikel lager[],int anzahl);	//reduces anzahl by "anzahl" for Artikel at index pos
int artikel_exists(char name[],struct Artikel lagere[],int size);	//checks if the Artikel mit name "name" exists in "lagere" returns 1 or 0
int findeartikelid(char name[],struct Artikel lagerf[],int size);	// returns the id  of Artikel with "name" or -1 if the article doesnt exists 
void clearstructin(struct Artikel lagerc[],int pos);	//sets a struct in lager to 0 in each field
int index_by_id(int id,struct Artikel lager[],int saturation); //returns the index of the Artikel with id "id"
int fuzzy_search(int modi,char name[],struct Artikel lager[],int saturation);
/*searches the lager for either the artikel with the id "modi" or for the name "name" if the modi is -1
  returns the index of the artikel or -1 if not found*/

void printlagertabelle(struct Artikel art);					//print the lagertable formated
void printmenues(int menueid);								//print a selection of menues
void clearscreen();										//prints enough newline chars to clear the console
int readoption();										//reads the input for the menues

int loadsaturation();									//loads the number of diffrent Artikels
void savesaturation(int sat);							//saves the number of diffrent Artikels
int resizefactor(int saturation);						//lager size  dependend on saturation calculated with less growth with larger numbers
void write_lager_to_file(struct Artikel lager[],int size); //write the array to a binfile
void read_lager_from_file(struct Artikel lager[],int size); //load data from a binfile into the array

int main(int argc, char const *argv[])
{
	int saturation =loadsaturation();
	const int lagergroese = resizefactor(saturation);  /* variable size requires memory alloc  wich i want to avoid by rezizing at program start*/
	struct Artikel lager[lagergroese] ;

	int next_free_index;
	int optionpicked;
	int finished = 0;
	char newname[20];
	int newanzahl;
	int newid;
	int newindex;
	int submenu = 0;
	int searchresult;
	char lastmsg[60] = "";
	char spalteid[3] = "id";
	char spalteArtikelname[12] = "Artikelname";
	char spalteAnzahl[] = "Anzahl";
	struct Artikel newartikel;

	clearscreen();
	printf("Willkommen zum Lagersystem Cremer\n");
	//load from file
	read_lager_from_file(lager,lagergroese);
	//read staturation
	saturation = loadsaturation();
	//clear empty space
	for (int i = saturation; i < lagergroese; ++i)
	{
		clearstructin(lager,i);
	}
	// set next free space in array
	next_free_index = saturation;

	while (finished != 1){
		//clearscreen();
		printf("%s \n",lastmsg );
		strcpy(lastmsg,"");
		if (submenu == 0){
			printmenues(1);
			optionpicked = readoption();
			switch(optionpicked){
				case 1:
					/*submenu Artikelverwaltung*/	
					submenu = 1;
					clearscreen();
					break;
				case 2:
					/*Lager table*/
					clearscreen();
					printf("|%4s|%20s|%8s|\n",spalteid,spalteArtikelname,spalteAnzahl);				
					for (int i = 1; i <= saturation; ++i)
						{
							printlagertabelle(lager[i-1]);
						}
					break;
				case 3:
					/*Programm closing und lager saving*/
					write_lager_to_file(lager,lagergroese);
					savesaturation(saturation);
					printf("Auf Wiedersehen \n");
					finished =1;
					break;
				default:
					strcpy(lastmsg,"->>>>>Tut mir leid das habe ich leider nicht verstanden\n");
					break;
				}
		}else{
			printmenues(2);
			optionpicked = readoption();
			switch(optionpicked){
				case 1: //suchen
					printf("Wollen sie anhand des Namens(0) oder anhand der ID suchen(1) (0-1):");
					optionpicked = readoption();
					switch(optionpicked){
						case 0: //namen suchen
							printf("Namen des Artikels bitte:");
							scanf("%s",newname);
							searchresult = fuzzy_search(-1,newname,lager,saturation);
							if (searchresult == -1)
							{
								printf("Nichts gefunden\n");
							}else{
								clearscreen();
								printf("Gefunden(\"%s\") mit ID:%i und anzahl:%i\n",lager[searchresult].name,lager[searchresult].id,lager[searchresult].anzahl );
							}
							break;
						case 1:
							printf("ID des Artikels bitte:");
							newid = readoption();
							searchresult = fuzzy_search(newid,lastmsg,lager,saturation); //just throw in some random string we dont use it anyway
							if (searchresult == -1)
							{	
								clearscreen();
								printf("Nichts gefunden\n");
							}else{
								clearscreen();
								printf("Gefunden(\"%s\") mit ID:%i und anzahl:%i\n",lager[searchresult].name,lager[searchresult].id,lager[searchresult].anzahl );
							}
							break;
						default:
							break;
					}
					break;
				case 2: //entnehmen
					printf("Name des Artikels?:");
					fflush(NULL);
					scanf("%s",newname);
					printf("\n");
					printf("Wieviel verlassen das lager? :");
					fflush(NULL);
					scanf("%i",&newanzahl);
					newid = findeartikelid(newname,lager,saturation);

					if (newid < 0)
					{	
						clearscreen();
						printf("Dieser Artikel existiert leider nicht\n" );
					}else{
						clearscreen();
						artikelentnehmen(index_by_id(newid,lager,saturation),lager,newanzahl);
					}
					break;
				case 3:
					/*Artikel hinzufügen*/
					if (saturation >= lagergroese )
					{
						printf("Leider ist das Lager voll\n");
						printf("Neustarten für Lager Vergrößerung\n");
						break;
					}
					printf("Name des neuen Artikels?:");
					fflush(NULL);
					scanf("%s",newname);
					printf("\n");
					printf("Wieviel kommen ins lager? :");
					fflush(NULL);
					scanf("%i",&newanzahl);
					newid = findeartikelid(newname,lager,saturation) ;
					if (newid < 0) //komplett neuer Aritkel
					{
						lager[next_free_index].id = next_free_index;
						lager[next_free_index].anzahl = newanzahl;
						strcpy(lager[next_free_index].name,newname);
						clearscreen();
						printf("Artikel erstellst mit id:%i name:%s anzahl:%i\n\n",lager[next_free_index].id,lager[next_free_index].name,lager[next_free_index].anzahl);
						saturation++;
						next_free_index++ ;
					}else{
						lager[newid].anzahl += newanzahl;
						clearscreen();
						printf("Artikel hinzufügt\nNeue Anzahl an \"%s\": %i Stück\n",newname,lager[newid].anzahl);
					}
					break;
				case 4:
					submenu = 0; //Hauptmenü
					clearscreen();
					break;
				default:
					strcpy(lastmsg,"->>>>>Tut mir leid das habe ich leider nicht verstanden:\n");
					break;
			}
		}	
	}
	return 0;
}

struct Artikel createartikel(int id,char str[]){
	struct Artikel newartikel;
	newartikel.id = id;
	strcpy(newartikel.name,str);
	newartikel.anzahl = 0;
	return newartikel;
}

void artikelentnehmen(int pos,struct Artikel lager[],int anzahl){
		if ( (lager[pos].anzahl - anzahl) >= 0 )
		{
			lager[pos].anzahl-=anzahl;
			clearscreen();
			printf("%i Stück aus dem Lager entnommen.\nNoch %i im Lager\n",anzahl,(lager[pos].anzahl) );
		}else{
			clearscreen();
			printf("Leider nicht genug im Lager\nVorgang abgebrochen\n");
		}
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
	int returnvalue = -1;
	for (int i = 0; i < size; ++i)
	{
			if(strcmp (lagerf[i].name,name) == 0){
				return i;
				break;
			}
			
	}
	return returnvalue;
}

void clearstructin(struct Artikel lagerc[],int pos){
	lagerc[pos].id = 0;
	lagerc[pos].name[0] = '\0';
	lagerc[pos].anzahl = 0;
}

int index_by_id(int id,struct Artikel lager[],int saturation){
	int i;
	for ( i = 0; i < saturation; ++i)
	{
		if(lager[i].id == id)
		{
			return i;
		}
	}
}	

int fuzzy_search(int modi,char name[],struct Artikel lager[],int saturation){
	int returnvalue = -1;
	if (modi == -1)
	{
		for (int i = 0; i < saturation+1; ++i)
		{
			for(int j=0; lager[i].name[j] != '\0'; ++j){
				if ( lager[i].name[j] != name[j] || lager[i].name[j] != (name[j]+32) ) //checks for lower and uppercase with ASCI values
				{
					returnvalue = i;
				}else{
					++i; //word doesnt match in position j ,move on
				}
			}	
		}
	}else{
		for (int i = 0; i < saturation+1; ++i)
		{
			if (lager[i].id == modi)
			{
				returnvalue = i;
			}
		}
	}
	return returnvalue;
}							

void printlagertabelle(struct Artikel art){
	printf("|%*i|%*s|%*i|\n",4,art.id,20,art.name,8,art.anzahl );
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
	int option =0;
	fflush(NULL);
	if(scanf(" %i",&option) == 0){
		option = 10;
	}
	while (getchar() != '\n');
	// discard any extra (unexpected) character 
	return option;
}

int loadsaturation (){
  FILE *fptr; //open a file buffer 
	if ((fptr = fopen("./lagereigenschaften.txt","r")) == NULL){
		printf("Error! opening file:lagereigenschaften.txt\0");
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
		printf("Error! opening file:lagereigenschaften.txt\0");
		// Program exits if the file pointer returns NULL.
		exit(1);
		}

  fprintf (fptr, "%d", sat);    
  fclose (fptr);   
 }

 int resizefactor(int saturation){
 	int tmp;
 	for (int i = 0; i < saturation-100; ++i)
 	{
 		tmp+=1;
 	}
 	for (int i = 0; i < saturation-300; ++i)
 	{
 		tmp+=1;
 	}
 	tmp = tmp + 50 +saturation ;
 	return tmp;
 }

void write_lager_to_file(struct Artikel lagerw[],int size){
    FILE *fptr; //open a file buffer
    int n;
    if ((fptr = fopen("./lager.bin","wb")) == NULL){
    printf("Error! opening file:lager.bin\0");
    // Program exits if the file pointer returns NULL.
    exit(1);
  }

    fwrite(lagerw, sizeof(struct Artikel), size, fptr);

  fclose(fptr);
}

void read_lager_from_file(struct Artikel lager[],int size){
  FILE *fptr; //open a file buffer
  if ((fptr = fopen("./lager.bin","rb")) == NULL){
    printf("Error! opening file:lager.bin\0");
    // Program exits if the file pointer returns NULL.
    exit(1);
  }
  struct Artikel newartikel;
  if(fptr != NULL){
    
    fread(lager,sizeof(struct Artikel),size,fptr);
    fclose(fptr);}
  
}