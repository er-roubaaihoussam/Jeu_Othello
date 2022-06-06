#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define vide ' ' // pour les cases vides
#define blanc 'B' // pour les pions du 2éme joueur
#define noir 'N'


//cette fonction permet de changer la couleur du console
void color(int t, int f)
{
HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(H, f * 16 + t);
}
//cette fonction permet d'afficher le contenu d'un fichier texte
void afficher_fichier(char *nom){
    char *nom_du_fichier = nom;
    char lire_chaine[50];
    FILE *fichier = NULL;
    if((fichier = fopen(nom_du_fichier,"r")) == NULL)                       //au cas où un erreur d'ouverture du fichier
    {
        fprintf(stderr,"erreur d'ouvrir le fichier %s\n",nom_du_fichier);
        return -1;
    }
    while(fgets(lire_chaine,sizeof(lire_chaine),fichier) != NULL)            //lecture du contenu du fichier
        printf("%s",lire_chaine);
    fclose(fichier);
}


//cette fonction permet d'afficher les regles du jeu à partir d'un fichier texte 'regles.txt'
void regles()
{
    int choix;
    system("cls");
    color(11,0);
    afficher_fichier("regles.txt");
    color(15,0);
    printf("\n\n\t\t\t Tapez sur 0 pour retourner a l'accueil : ");
    scanf("%d",&choix);
    system("cls");
}

void jouer()
{
    int choix;
    system("cls");
    color(11,0);
    afficher_fichier("jouer.txt");
    color(15,0);
    printf("\n\n\t\t\t Veuillez choisir un nombre pour continuer : ");
    scanf("%d",&choix);
    system("cls");
    if (choix==1){
        joueur_vs_joueur();
        system("cls");
        main();
    }
    if (choix==2){
        joueur_vs_machine();
        system("cls");
        main();
    }
    if (choix==0){
        system("cls");
        main();
    }
}

void joueur_vs_machine()
{
    int choix;
    system("cls");
    color(11,0);
    afficher_fichier("joueur_vs_machine.txt");
    color(15,0);
    printf("\n\n\t\t\t Veuillez choisir un nombre pour continuer : ");
    scanf("%d",&choix);
    system("cls");
    if (choix==1){
        machine_facile();
        system("cls");
        main();
    }
    else if (choix==2){
        machine_moyenne();
        main();
    }
    if (choix==0){
        system("cls");
        jouer();
    }
}

int main()
{
    int choix;
    do{
    color(11,0);
    afficher_fichier("accueil.txt");
    color(15,0);
    printf("\n\n\t\t\tVeuillez choisir un nombre pour continuer : ");
    scanf("%d",&choix);
    switch(choix){
    case 1:jouer();
        break;
    case 2:regles();
        break;
    }
    }
    while (choix!=3);
    system("cls");
    return 0;
}
