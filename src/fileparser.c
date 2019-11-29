#include <stdio.h>
#include <stdlib.h>
struct Artikel
{
  int id;
  char name[10];
  int anzahl;
};

void get_data_from_file(){
  FILE *fptr;
  if ((fptr = fopen("./test.txt","rb")) == NULL){
    printf("Error! opening file");
    // Program exits if the file pointer returns NULL.
    exit(1);
  }
  struct Artikel newartikel;
  struct Artikel lager[3];
  while(fread(&newartikel, sizeof(struct Artikel), 1, fptr)){ 
        printf ("reading");
        printf("read id : %i \n",newartikel.id ); 
  }
  fclose(fptr); 
  for (int i = 0; i < 2; ++i)
  {
    fread(&lager[i],sizeof(struct Artikel),1,fptr);
    printf("here is the id in array: %i\n",lager[i].id );
  }
  fclose(fptr);
}

void write_data(){
    FILE *fptr;
    int n;
    int nextfreeid = 0;
    if ((fptr = fopen("./test.txt","wb")) == NULL){
    printf("Error! opening file");
    // Program exits if the file pointer returns NULL.
    exit(1);
  }
  for(n = 0; n < 5; ++n)
  {
   struct Artikel  newartikel = { nextfreeid,"marc",n};
   nextfreeid++;
    fwrite(&newartikel, sizeof(struct Artikel), 1, fptr); 
    printf("writing\n");
  }
  fclose(fptr); 
}

int main()
{

  struct Artikel lager[5];
  /*print */
  write_data();
  get_data_from_file(5);

  return 0;
}


  
