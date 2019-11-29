#include <stdio.h>
#include <stdlib.h>
struct Artikel
{
  int id;
  char name[10];
  int anzahl;
};

void get_data_from_file(struct Artikel lager[],int size){
  FILE *fptr;
  if ((fptr = fopen("./test.txt","rb")) == NULL){
    printf("Error! opening file");
    // Program exits if the file pointer returns NULL.
    exit(1);
  }

    fread(&lager, sizeof(struct Artikel), 5, fptr); 
    //printf("n1: %d\tn2: %d\tn3: %d", num.n1, num.n2, num.n3);
    printf("reading\n");
    for (int i = 0; i < size; ++i)
    {     
          printf("reading lager[%i]\n",i );
          printf("%s\n",lager[0].id);
          //printf("the srtucts are id: %i name: %s anzahl: %i\n",lager[i].id,lager[i].name,lager[i].anzahl );

    }
  
  fclose(fptr); 
}

int main()
{
  int n;
  int nextfreeid = 0;
  struct Artikel newartikel;
  struct Artikel lager[5];
  FILE *fptr;
  /*print */
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
  get_data_from_file(lager,5);

  return 0;
}


  
