#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>



typedef struct Utilisateur
{
char login[50];
char password[50];
int role;
int num_id;
}Utilisateur;

void interface(Utilisateur *tabusers, int nb_users);
void connexion(Utilisateur* tabusers, int nb_users);
void menu_eleve(Utilisateur *tabusers, int nb_users, int num_id);
void menu_prof(Utilisateur* tab, int nb_users, int num_id);
void ajouteruser();
void affichertabusers(int nb_users);
void recscanf();