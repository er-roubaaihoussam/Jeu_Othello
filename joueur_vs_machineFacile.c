#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <windows.h>
#include <tchar.h>


#define etoile '*'

#define r 8 // r represente la largeur de la grille

#define vide ' ' // pour les cases vides
#define blanc 'B' // pour les pions du 2éme joueur
#define noir 'N' //pour les pions du 1ère  joueur


enum boolien{faux,vraie}; //vraie->1,faux->0

int *choisir_position_machine(int** les_cordonnees ) // pour le choix de la machine
{   int test=0,vraie=1,i,choixi,choixj;
char lettre;
int* choix=malloc(2*sizeof(int));
    while(vraie==1)
    {


    lettre=random_entre_deux_int(65,72);
    choixj=lettre-'A';
    choixi=random_entre_deux_int(1,8);
    choixi--;//on diminue 1 parce que la matrice commence par 0 pas par 1


    for(i=0;i<les_cordonnees[63][0];i++)
    {



            if(choixi==les_cordonnees[i][0] && choixj==les_cordonnees[i][1] )
            {
                choix[0]=choixi;
choix[1]=choixj;
return choix;
vraie=0;
            }







    }



}

}
int random_entre_deux_int(int min, int max)
{
 return (rand())%(max - min) + min + 1;
}


int machine_facile(int argc, char** argv)
{

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)!=0)
   {
       SDL_Log("Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());

        exit(EXIT_FAILURE);
   }
    SDL_Window *window=NULL;



   window=SDL_CreateWindow("fenetre",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_HIDDEN);

   if(window==NULL)
   {
       SDL_Log("Échec de creation(%s)\n",SDL_GetError());

        exit(EXIT_FAILURE);
   }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) //Initialisation de l'API Mixer
   {
       SDL_Log("Échec de creation musique(%s)\n",SDL_GetError());

        exit(EXIT_FAILURE);
   }
   Mix_Music *musique; //Création du pointeur de type Mix_Music
   Mix_Chunk *son;//Créer un pointeur pour stocker un .WAV
   Mix_Chunk *victoire;
   victoire=Mix_LoadWAV("rak_rbahti.wav");
   son = Mix_LoadWAV("wavfil.wav"); //Charger un wav dans un pointeur
   musique = Mix_LoadMUS("music_jeu.mp3");//Chargement de la musique
   Mix_PlayMusic(musique, -1); //Jouer infiniment la musique



    char** grille=matrice_char(8,9);
    int i,j,choix_de_i,choix_de_j,play=1,fin=0; // choix_de_i : position légale pour i, choix_de_j : position légale pour j
   for(i=0;i<=7;i++)
   {
       for(j=0;j<=7;j++)
       {
           grille[i][j]=vide;
       }
   }
   init(grille);
    int **les_cordonnees_noires=matrice_int(64,2);
    int **les_cordonnees_blanches=matrice_int(64,2);
    int *choix_de_position_noire=malloc(sizeof(int));
    int *choix_de_position_blanche=malloc(sizeof(int));
    srand(time(NULL));
    int choix_du_couleur;
    printf("voulez vous jouer en: \n1-noir\n2-blanc\nvotre choix : \n");
    scanf("%d",&choix_du_couleur);
    while(play)
    {

    les_cordonnees_noires=cases_legaux_noir(grille);
    if(position_de_jeu(les_cordonnees_noires)==1) // si le joueuer ne peut pas continuer a jouer
    {
        fin++;
    }
    else
        {
            fin=0; // fin=0:jouer fin=1:passer son tour fin=2:fin du jeu
        }
    if(fin==2)
    {
        le_gagnant_est(grille);
        Mix_PlayChannel(2, victoire, 0);
        int *score_du_jeu;// tableau qui contient le score des deux deux joueur
        score_du_jeu=score_des_joueurs(grille);
        char nom_du_joueur[20];
        printf("vous etes gagnant entrer votre nom :\n");
        scanf("%s",nom_du_joueur);
        ajouter_joueur(nom_du_joueur,score_du_jeu[0]);
        if(score_du_jeu[0]==higt_score())
        {
            printf("felicitation vous avez realisé un nouveau hight score\n");

            afficher_fichier_score();

        }
        else
            {

            afficher_fichier_score();
            }

        break;
    }
    else if(fin==0)
        {



    Color(FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);//blanc vert

    printf("=======>tour du noir\n\n");


    modifier(grille,les_cordonnees_noires);


    score(grille);
    Color(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_GREEN);//blanc vert
    afficherN(grille);



    Color(FOREGROUND_RED  |FOREGROUND_GREEN|FOREGROUND_INTENSITY   ); // jaune noir
    if(choix_du_couleur==2)
     {
         choix_de_position_noire=choisir_position_machine(les_cordonnees_noires);
     }
    else
        {
             choix_de_position_noire=choisir_position(les_cordonnees_noires);
        }

    strcpy(grille,sandwich_noir(grille,choix_de_position_noire[0],choix_de_position_noire[1],les_cordonnees_noires));

    Color(FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);//blanc vert


    score(grille);
    Mix_PlayChannel(1, son, 0);
    Color(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_GREEN); //blanc vert
    afficherN(grille);
    Color(FOREGROUND_RED  |FOREGROUND_GREEN|FOREGROUND_INTENSITY   ); // jaune  noir
    system("@cls||clear");
        }


     les_cordonnees_blanches=cases_legaux_blanches(grille);
    if(position_de_jeu(les_cordonnees_blanches)==1) // si le joueuer ne peut pas continuer a jouer
    {
        fin++;
    }
    else
        {
            fin=0;
        }
    if(fin==2)
    {
        le_gagnant_est(grille);
        Mix_PlayChannel(2, victoire, 0);
        int *score_du_jeu;// tableau qui contient le score des deux deux joueur
        score_du_jeu=score_des_joueurs(grille);
        char nom_du_joueur[20];
        printf("vous etes gangnant entrer votre nom :\n");
        scanf("%s",nom_du_joueur);
        ajouter_joueur(nom_du_joueur,score_du_jeu[1]);
        if(score_du_jeu[1]==higt_score())
        {
            printf("felicitation vous avez realisé un nouveau hight score\n");

            afficher_fichier_score();

        }
        else
            {

            afficher_fichier_score();
            }
        break;
    }
    else if(fin==0)
        {

    Color(FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);//blanc vert

    printf("----------------------------------\n");
     printf("=======>tour du blanc\n\n");
     printf("----------------------------------\n");//modification
    modifier(grille,les_cordonnees_blanches);

    score(grille);
    Color(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_GREEN);  //blanc green
    afficherB(grille);
    Color(FOREGROUND_RED  |FOREGROUND_GREEN|FOREGROUND_INTENSITY   ); //jaune noir


   if(choix_du_couleur==2)
     {
         choix_de_position_blanche=choisir_position(les_cordonnees_blanches);
     }
     else
     {
         choix_de_position_blanche=choisir_position_machine(les_cordonnees_blanches);
     }
    strcpy(grille,sandwich_blanc(grille,choix_de_position_blanche[0],choix_de_position_blanche[1],les_cordonnees_blanches));
    score(grille);
    Mix_PlayChannel(1, son, 0);
    Color(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_GREEN);// blanc vert
    afficherB(grille);
    Color(FOREGROUND_RED  |FOREGROUND_GREEN|FOREGROUND_INTENSITY   );//jaune noir
    system("@cls||clear");


    }
    }

          Mix_FreeChunk(son);//Libération du son 1
      Mix_FreeMusic(musique); //Libération de la musique
   Mix_CloseAudio(); //Fermeture de l'API


   SDL_DestroyWindow(window);




   SDL_Quit();


    return 0;
}
