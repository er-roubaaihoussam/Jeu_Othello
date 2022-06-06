#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <windows.h>
#include <tchar.h>


#define etoile '*'

#define r 8 // r represente la largeur de la grille

#define inf 9999
#define vide ' ' // pour les cases vides
#define blanc 'B' // pour les pions du 2éme joueur
#define noir 'N' //pour les pions du 1ère  joueur



int profondeur=3;

void copierGrille(char** de, char** a){
    int i,j;
    for(i=0;i<8;i++){
        for(j=0;j<9;j++){
            a[i][j]=de[i][j];

        }
    }
}

int evaluerGrille(char** grille, char joueur_couleur){
    char mon_coup,coup_adv;
    if (joueur_couleur=noir){
        mon_coup=noir;
        coup_adv=blanc;
    }else{
        mon_coup=blanc;
        coup_adv=noir;
    }
    int i,j;
    int mon_score=0;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++){
            if (grille[i][j]== mon_coup){
                mon_score+= 1;
            }else if(grille[i][j]== coup_adv){
                mon_score-= 1;
            }
        }
    }
    return mon_score;
}

int alpha=-inf,beta=inf;

int** matrice_int(int ligne,int colonne){
    int i;
    int **matrice=NULL;
    matrice=malloc(ligne * sizeof(int*));
    if (matrice==NULL) exit(1);
    for (i=0;i<ligne;i++){
        matrice[i]=malloc(colonne * sizeof(int));
        if (matrice[i]==NULL) exit(1);
    }
    return matrice;
}
char** matrice_char(int ligne,int colonne){
    int i;
    char **matrice=NULL;
    matrice=malloc(ligne * sizeof(char*));
    if (matrice==NULL) exit(1);
    for (i=0;i<ligne;i++){
        matrice[i]=malloc(colonne * sizeof(char));
        if (matrice[i]==NULL) exit(1);
    }
    return matrice;
}
void liberation_matrice_int(int** matrice,int ligne){
    int i;
    for (i=0;i<ligne;i++){
        free(matrice[i]);
        matrice[i]=NULL;
    }
    free(matrice);
    matrice=NULL;
}
void liberation_matrice_char(char** matrice,int ligne){
    int i;
    for (i=0;i<ligne;i++){
        free(matrice[i]);
        matrice[i]=NULL;
    }
    free(matrice);
    matrice=NULL;
}
int alphaBeta(char** grille,int profondeur,int alpha,int beta,int *p)
{

    if (profondeur==0){
        return evaluerGrille(grille,noir);
    }
    else if (profondeur%2==1){
        int **les_cordonnees_noires=matrice_int(64,2);
        int n;
        les_cordonnees_noires=cases_legaux_noir(grille);
        n=les_cordonnees_noires[63][0];
        int i,max=-inf;
        for (i=0;i<n;i++){//n=nombre des coups possibles
            char** copie_grille=matrice_char(8,9);
            copierGrille(grille,copie_grille);
            sandwich_noir(copie_grille,les_cordonnees_noires[i][0],les_cordonnees_noires[i][1],les_cordonnees_noires);
            alpha=alphaBeta(copie_grille,profondeur-1,alpha,beta,p);
            liberation_matrice_char(copie_grille,8);
            if (alpha>=max){
                max=alpha;
                p[0]=les_cordonnees_noires[i][0];
                p[1]=les_cordonnees_noires[i][1];
            }
            if (beta<=alpha) break;
        }
        liberation_matrice_int(les_cordonnees_noires,64);
            return max;
    }
    else if (profondeur%2==0){
        int** les_cordonnees_blanches=matrice_int(64,2);
        int n;
        les_cordonnees_blanches=cases_legaux_blanches(grille);
        n=les_cordonnees_blanches[63][0];
        int i,min=inf;
        for (i=0;i<n;i++){//n=nombre des coups possibles
            char** copie_grille=matrice_char(8,9);
            copierGrille(grille,copie_grille);
            sandwich_blanc(copie_grille,les_cordonnees_blanches[i][0],les_cordonnees_blanches[i][1],les_cordonnees_blanches);
            beta=alphaBeta(copie_grille,profondeur-1,alpha,beta,p);
            liberation_matrice_char(copie_grille,8);
            if (beta<=min){
                min=beta;
                p[0]=les_cordonnees_blanches[i][0];
                p[1]=les_cordonnees_blanches[i][1];
            }
            if (beta<=alpha) break;
        }
                liberation_matrice_int(les_cordonnees_blanches,64);

        return min;
        }
}


int* choisir_position_machine_moyenne(char** grille, int** les_cordonnees){
    int* choix=malloc(2 * sizeof(int));

        alphaBeta(grille,profondeur,alpha,beta,choix);

    return choix;

}



int machine_moyenne()
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
    int *meilleur_choix=malloc(2 * sizeof(int));
    int *choix_de_position_blanche=malloc(2 * sizeof(int));

    srand(time(NULL));
    while(play==1)
    {

    les_cordonnees_noires=cases_legaux_noir(grille);
    if(position_de_jeu(les_cordonnees_noires)==1) // si le joueur ne peut pas continuer a jouer
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
        break;
    }
    else if(fin==0)
        {
    Color(FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);//blanc vert

    printf("=======>tour du noir\n\n");

    meilleur_choix=choisir_position_machine_moyenne(grille,les_cordonnees_noires);

    strcpy(grille,sandwich_noir(grille,meilleur_choix[0],meilleur_choix[1],les_cordonnees_noires));
    score(grille);
    Color(FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_GREEN);//blanc vert

    afficherN(grille);
    Color(FOREGROUND_RED  |FOREGROUND_GREEN|FOREGROUND_INTENSITY   ); // jaune noir




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


    choix_de_position_blanche=choisir_position(les_cordonnees_blanches);
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

