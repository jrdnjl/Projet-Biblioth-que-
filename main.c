#include "livres.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//****************************************************
//    Gestion livres
//****************************************************
void actualiserlivres(Livre *tablivres,int *nmblivre){
  affichertablivres(0);
  FILE *fichier = NULL;

  // ouverture du fichier en écriture au début du fichier
  fichier = fopen("livres.txt", "w");
  if (fichier == NULL) {
    printf("Ouverture du fichier impossible\n");
    printf("code d'erreur = %d \n", errno);
    printf("Message d'erreur = %s \n", strerror(errno));
    exit(1);
  }

  *nmblivre = *nmblivre + 1;
  for (int i = 0; i < *nmblivre; i++) {
    fprintf(fichier, "%s  %s  %s  %d  %d\n\n", tablivres[i].titre, tablivres[i].auteur, tablivres[i].categorie, tablivres[i].num_id,
           tablivres[i].disponibilite);
    }
   affichertablivres(0);
  fclose(fichier);
}

// fonction qui lit dans un fichier ascii et retourne un tableau contenant les livres du fichier
Livre *lirefichier(int *nmblivre) {
  Livre *tablivres = NULL;
  FILE *fichier = NULL;

  // ouverture du fichier en lecture
  fichier = fopen("livres.txt", "r");
  if (fichier == NULL) {
    printf("Ouverture du fichier impossible\n");
    printf("code d'erreur = %d \n", errno);
    printf("Message d'erreur = %s \n", strerror(errno));
    exit(1);
  }
  char ligneLivre[400];
  while (fgets(ligneLivre, 399, fichier) != NULL) {
    *nmblivre = *nmblivre + 1;
  }
  // On alloue le tableau
  tablivres = malloc(*nmblivre * sizeof(Livre));
  /*remplissage du tableau en utilisant des fscanf.*/
  rewind(fichier);
  for (int i = 0; i < *nmblivre; i++) {
    // titre
    fscanf(fichier, "%s", tablivres[i].titre);
    // auteur
    fscanf(fichier, "%s", tablivres[i].auteur);
    // catégorie
    fscanf(fichier, "%s", tablivres[i].categorie);
    // numéros d'identification
    fscanf(fichier, "%d", &tablivres[i].num_id);

    fscanf(fichier, "%d", &tablivres[i].disponibilite);
  }

  return tablivres;
}

//fonction qui permet d'afficher livre
int affichertablivres(int nmblivre) {
  Livre *tablivres;
  tablivres = lirefichier(&nmblivre);
  for (int i = 0; i < nmblivre; i++) {
    printf("%d :  %s  %s  %s  %d  %d\n", i + 1, tablivres[i].titre,
           tablivres[i].auteur, tablivres[i].categorie, tablivres[i].num_id,
           tablivres[i].disponibilite);
  }
  printf("\n\n");
  return nmblivre;
}

//fonction qui permet d'ajouter des livres
void ajouterlivres() {
  FILE *fichier = NULL;
  // ouverture du fichier en lecture
  fichier = fopen("livres.txt", "a");
  if (fichier == NULL) {
    printf("Ouverture du fichier impossible\n");
    printf("code d'erreur = %d \n", errno);
    printf("Message d'erreur = %s \n", strerror(errno));
    exit(1);
  }
  char titre[50];
  char auteur[50];
  char categorie[50];
  int num_id = 0;
  int disponibilite = 0;

  puts("Entrer le titre du livre :");
  scanf("%s", titre);

  puts("Entrer l'auteur du livre :");
  scanf("%s", auteur);

  puts("Entrer la catégorie du livre :");
  scanf("%s", categorie);

  srand(time(NULL));
  num_id = rand() % (1000000);

  fprintf(fichier, "\n%s %s %s %d %d", titre, auteur, categorie, num_id,
          disponibilite);

  fclose(fichier);
}

// procédure permettant de modifier la variable "disponibilité" du livre choisi, cependant elle ne fonctionne pas correctement.
void emprunterlivre(Livre *tablivres, int indicelivre, int num_id, int nmblivre) {

   
  printf("vous avez bien emprunter %s\n", tablivres[indicelivre].titre);
  actualiserlivres(tablivres, &nmblivre);
}

// procédure qui demande à l'utilisateur de choisir le livre qu'il souhaite emprunter et envoie ce choix à la procédure emprunter.
void choixlivre(Utilisateur *tabusers, int nb_users, Livre *tablivres, int nmblivre, int num_id) {
  Livre *tab;
  char titre[50];

  printf("Entrer le titre du livre que vous voulez emprunter :\n");
  scanf("%s", titre);

  for (int i = 0; i < nmblivre; i++) {
    //printf("%s, %s\n" tablivres[i].titre, titre);
    if (strcmp(tablivres[i].titre, titre) == 0) {
      emprunterlivre(tablivres, i, num_id, nmblivre);
      connexion(tabusers, nb_users);
    } 
  }choixlivre(tabusers, nb_users, tablivres, nmblivre, num_id);
}


//*****************************************************
//  Gestion utilisateurs
//*****************************************************

// fonction qui lit dans un fichier ascii et retourne un tableau contenant les utilisateurs du fichier
Utilisateur *creertabusers(int *nb_users) {
  Utilisateur *tabusers = NULL;
  FILE *fichier = NULL;

  // ouverture du fichier en lecture
  fichier = fopen("utilisateurs.txt", "r");
  if (fichier == NULL) {
    printf("Ouverture du fichier impossible\n");
    printf("code d'erreur = %d \n", errno);
    printf("Message d'erreur = %s \n", strerror(errno));
    exit(1);
  }
  char ligneEtu[400];
  while (fgets(ligneEtu, 399, fichier) != NULL) {
    *nb_users = *nb_users + 1;
  }

  // On alloue le tableau
  tabusers = malloc((*nb_users) * sizeof(Utilisateur));
  /*remplissage du tableau en utilisant des fscanf.*/
  rewind(fichier);
  for (int i = 0; i < *nb_users; i++) {
    // login
    fscanf(fichier, "%s", tabusers[i].login);
    // password
    fscanf(fichier, "%s", tabusers[i].password);
    // role
    fscanf(fichier, "%d", &tabusers[i].role);
    // numéros d'identification
    fscanf(fichier, "%d", &tabusers[i].num_id);
  }

  return tabusers;
}

//procédure permettant à l'utilisateur de créer un nouveau profile.
void ajouteruser() {
  FILE *fichieruser = NULL;
  // ouverture du fichier en lecture
  fichieruser = fopen("utilisateurs.txt", "a");
  if (fichieruser == NULL) {
    printf("Ouverture du fichier impossible\n");
    printf("code d'erreur = %d \n", errno);
    printf("Message d'erreur = %s \n", strerror(errno));
    exit(1);
  }
  char login[50];
  char password[50];
  int role;
  int num_id = 0;

  puts("Entrer votre login :");
  scanf("%s", login);

  puts("Entrer votre mot de passe :");
  scanf("%s", password);

  puts("Entrer 1 pour créer un profile d'élève :");
  puts("Entrer 2 pour créer un profile de professeur :");
  scanf("%d", &role);

  srand(time(NULL));
  num_id = rand() % (1000000 + 1);

  fprintf(fichieruser, "\n%s %s %d %d", login, password, role, num_id);

  printf("votre profil a été créer ! \n");

  fclose(fichieruser);
}

// on utilise cette fonction pour vérifier que le tableau d'utilsateurs est rempli correctement
void affichertabusers(int nb_users) {
  Utilisateur *tabusers;
  tabusers = creertabusers(&nb_users);
  for (int i = 0; i < nb_users; i++)
    printf("%d :  %s  %s  %d  %d\n", i + 1, tabusers[i].login,
           tabusers[i].password, tabusers[i].role, tabusers[i].num_id);
}

//procédure servant d'interface pour se connecter, elle vérifie le login et le mot de passe de l'utilisateur.
void connexion(Utilisateur *tabusers, int nb_users) {

  char password[50];
  char login[50];
  FILE *fic = fopen("utilisateurs.txt", "r");
  if (fic == NULL) {
    exit(1);
  }

  printf("entrez votre login\n");
  scanf("%s", login);

  printf("entrez votre mot de passe\n");
  scanf("%s", password);

  for (int i = 0; i < nb_users; i++) {
    if (strcmp(tabusers[i].login, login) == 0) {
      if (strcmp(tabusers[i].password, password) == 0) {
        switch (tabusers[i].role) {

        case 1:
          printf("\nvous êtes connectés en tant qu'élève\n\n");
          menu_eleve(tabusers, nb_users, tabusers[i].num_id);
          break;
        case 2:
          printf("\nvous êtes connectés en tant que professeur\n\n");
          menu_prof(tabusers, nb_users, tabusers[i].num_id);
          break;
        default:
          printf("\nvotre profile n'est pas correct veuillez en créer un "
                 "nouveau de type professeur ou de type élève\n\n");
          break;
        }
      }
    }
  }
  printf("vos identifiants ne sont pas corrects\n\n");
  interface(tabusers, nb_users);
}


//****************************************************
//    Gestion application
//****************************************************

// fonction qui va "corriger" l'utilisateur en cas de faute de frappe
void recscanf() {
  int choix;
  char c;
  do {
    choix = scanf("%c", &c);
  } while (choix == 0 && c != '\n');
}

// ACCUEIL
void interface(Utilisateur *tabusers, int nb_users) {
  int A = 0;
  int choix = 0;
  do {
    printf("0 - quitter la bibliothèque\n");
    printf("1 - se connecter à votre compte\n");
    printf("2 - créer un nouveau profile\n");
    A = scanf("%d", &choix);
    recscanf();

    if (A == 1) {
      switch (choix) {

      case 0:
        printf("merci de votre visite\n");
        printf("n'oubliez pas de rendre les livres emprunter\n");
        exit(1);
      case 1:
        printf("connectez-vous\n");

        connexion(tabusers, nb_users);

        break;
      case 2:
        printf("créer un nouveau profile\n");
        free(tabusers);
        ajouteruser();
        tabusers = creertabusers(&nb_users);
        interface(tabusers, nb_users);
        break;
      default:
        printf("veuill_ez selectionner une interface\n");
        interface(tabusers, nb_users);

        break;
      }
    } else {
      interface(tabusers, nb_users);
    }
  } while (choix > 2 || choix <= 0);
}

// interface d'un compte élève
void menu_eleve(Utilisateur *tabusers, int nb_users, int num_id) {
  int indicelivre = 0;
  int nmblivre = 0;
  Livre *tablivres;
  int choix = 0;
  int A = 0;
  do {
    puts("Quelle actions voulez-vous faire ?\n");
    printf("1- emprunter un livre\n");
    printf("2- rendre un livre\n");
    printf("0- se deconnecter\n");
    A = scanf("%d", &choix);
    recscanf();
    if (A == 1) {
      switch (choix) {

      case 0:
        puts("vous êtes deconnecter");
        interface(tabusers, nb_users);

      case 1:
        puts("les livres disponibles sont les suivants :");
        tablivres = lirefichier(&nmblivre);
        nmblivre = affichertablivres(0);
        choixlivre(tabusers, nb_users, tablivres, nmblivre, num_id );
        // puts("fonction indisponible\n");
        tablivres = lirefichier(&nmblivre);
        

        break;
      case 2:
        puts("fonction indisponible\n");
        menu_eleve(tabusers, nb_users, num_id);

        break;
      }
    } else {
      printf("cette commande n'existe pas");
      menu_eleve(tabusers, nb_users, num_id);
    }
  } while (choix > 2 || choix <= 0);
}

// interface d'un compte professeur
void menu_prof(Utilisateur *tabusers, int nb_users, int num_id) {
  int nmblivre = 0;
  Livre *tablivres;
  int indicelivre = 0;
  int choix = 0;
  int A = 0;
  do {
    puts("Quelle actions voulez-vous faire ?\n");
    printf("1- emprunter un livre\n");
    printf("2- rendre un livre\n");
    printf("3- rajouter un livre\n");
    printf("0- se deconnecter\n");
    A = scanf("%d", &choix);
    recscanf();
    if (A == 1) {
      switch (choix) {

      case 0:
        puts("vous êtes deconnecter");
        interface(tabusers, nb_users);

      case 1:
       puts("les livres disponibles sont les suivants :");
        tablivres = lirefichier(&nmblivre);
        nmblivre = affichertablivres(0);
        choixlivre(tabusers, nb_users, tablivres, nmblivre, num_id );
        // puts("fonction indisponible\n");
        tablivres = lirefichier(&nmblivre);
        menu_prof(tabusers, nb_users, num_id);
        break;
      case 2:

        puts("fonction indisponible\n");
        menu_prof(tabusers, nb_users, num_id);
        break;
      case 3:
        ajouterlivres();
        puts("******************************************\n");
        puts("liste des livres disponibles mis à jour :\n");
        affichertablivres(0);
        puts("******************************************");
        menu_prof(tabusers, nb_users, num_id);
      }
    } else {
      printf("cette commande n'existe pas");
      menu_prof(tabusers, nb_users, num_id);
    }
  } while (choix > 3 || choix <= 0);
}

//*************************************************
//     Programme principale
//*************************************************
int main() {
  puts("*************************************************\n               "
       "Bibliotèque "
       "CY-TECH\n*************************************************");

  Utilisateur *tabusers;
  int nb_users = 0;
  tabusers = creertabusers(&nb_users);
  interface(tabusers, nb_users);
  ;

  free(tabusers);
  return 0;
}