#include <stdio.h>
#include <stdlib.h>

char texte[50];

typedef struct Livre{
char titre[50];
char auteur[50];
char categorie[50];
int num_id;
char disponibilite[50];
}Livre;

int compterlivres(); 
void creertablivres();