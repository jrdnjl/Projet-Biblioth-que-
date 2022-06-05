#include <stdio.h>
#include <stdlib.h>
#include "utilisateurs.h"
char texte[50];

typedef struct Livre{
char titre[50];
char auteur[50];
char categorie[50];
int num_id;
int disponibilite;
}Livre;

int compterlivres(); 
void creertablivres();
void choixlivre(Utilisateur *tabusers, int nb_users, Livre *tablivres, int nmblivre, int num_id);
void emprunterlivre(Livre *tablivres, int indicelivre, int num_id, int nmblivre);
int affichertablivres(int nmblivre);
void actualiserlivres(Livre *tablivres,int *nmblivre);