#include <stdio.h>
#include <stdlib.h>
struct Artikel
{
  int id;
  char name[10];
  int anzahl;
};

void read_lager_from_file(struct Artikel lager[],int size){
  FILE *fptr;
  if ((fptr = fopen("./test.txt","rb")) == NULL){
    printf("Error! opening file");
    // Program exits if the file pointer returns NULL.
    exit(1);
  }
  struct Artikel newartikel;
  int count = 0;
  while(fread(&lager[2], sizeof(struct Artikel), 1, fptr)){ 
        printf ("reading");
        printf("read id : %i \n",newartikel.id ); 
        count++;
  }
  fclose(fptr); 

    fread(&lager,sizeof(struct Artikel),3,fptr);
    for (int i = 0; i < 3; ++i)
    {
      printf("here is the id in array[%i]: %i\n",i,lager[i].id );
    }
    
  fclose(fptr);
}

void write_lager_to_file(){
    FILE *fptr;
    int n;
    int nextfreeid = 0;
    struct Artikel lagers[3];

    if ((fptr = fopen("./test.txt","wb")) == NULL){
    printf("Error! opening file");
    // Program exits if the file pointer returns NULL.
    exit(1);
  }
  for (int i = 0; i < 3; ++i)
  {
    lagers[i].id = i+1;
    printf("creating buffer with id: %i\n",i+1 );
  }

   nextfreeid++;
    fwrite(&lagers, sizeof(struct Artikel), 3, fptr); 
    printf("writing with id:%i\n",lagers[0].id);
  
  fclose(fptr); 
}

int main()
{

  /*print */
  /* careful with edianess */
  write_lager_to_file();
  struct Artikel lager[3];

  read_lager_from_file(lager,3);

  return 0;
}


  
