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

int time1;
int time2;
int min =0;
int min2=0;
int coup =1;
 static char c;
 static char cc;


void chrono(){

   //printf(" ####### this is the board here ####### \n");

    time_t start, end;
    int  count = 0, temp = 0;


    count=time1;

    start = time(NULL);
    //printf("let me out: \n");

    //do{
        while(!kbhit()){

            end = time(NULL);
            if(end-start > temp){

                count--;

                temp = end - start;
                if (-1*count==60){

                    min++;
                    count=0;
                }
                //printf("please choose the char a - ");
                printf("TIME 1 : %02d:%02d", min,-1*count);

                time1=count;
                temp=end-start;

                for(int i = 0; i<100; i++){
                    printf("\x8");
                }
            }
        }
        printf("\n");

        //printf("\n count4 %d",count);
        end = time(NULL);

        c = getch();
        //fflush(stdin);
        printf("\n%c",c);
        //time1=180 - (end-start);
    /*    if(!valid_input(c)){
            printf("\n %c is not a valid input \n", c);
        }

    }while(!valid_input(c));
    //printf("\n you have choosed :  %c\n  in %d seconds\n", c, end-start);

*/



    //printf("\n count1 %d",count);

    //printf("avant time1  %d ",time1);
    //time1=count-end-start;
    //printf("time1   %d",time1);
}

void chrono2(){

   //printf(" ####### this is the board here ####### \n");

    time_t start2, end2;
    int  count2 = 0, temp2 = 0;


    count2=time2;

    start2 = time(NULL);
    //printf("let me out: \n");

   // do{
        while(!kbhit()){

            end2 = time(NULL);
            if(end2-start2 > temp2){

                count2--;

                temp2 = end2 - start2;
                if (-1*count2==60){

                    min2++;
                    count2=0;
                }
                //printf("please choose the char a - ");
                printf("TIME 2 : %02d:%02d", min2,-1*count2);

                time2=count2;
                temp2=end2-start2;

                for(int i = 0; i<100; i++){
                    printf("\x8");
                }
            }
        }
        printf("\n");
        //printf("\n count4 %d",count);
        end2 = time(NULL);
        cc = getch();
                //fflush(stdin);

        printf("\n%c",cc);
        //time1=180 - (end-start);
    /*    if(!valid_input2(cc)){
            printf("\n %c is not a valid input \n", cc);
        }

    }while(!valid_input2(cc));
    //printf("\n you have choosed :  %c\n  in %d seconds\n", c, end-start);
*/




    //printf("\n count1 %d",count);

    //printf("avant time1  %d ",time1);
    //time1=count-end-start;
    //printf("time1   %d",time1);
}


enum boolien{faux,vraie}; //vraie->1,faux->0

int la_case_est_vide(char **grille ,int i, int j) // fonction qui teste si une case est vide
{

          if(grille[i][j]==vide)
          {
               return vraie;
          }
          else
            {
                return faux;
            }

}
int la_case_est_noire(char **grille ,int i, int j) // fonction qui teste si une case est noire
{

          if(grille[i][j]==noir)
          {
               return vraie;
          }
          else
            {
                return faux;
            }

}
int la_case_est_blanche(char **grille ,int i, int j) // fonction qui teste si une case est blanche
{

          if(grille[i][j]==blanc)
          {
               return vraie;
          }
          else
            {
                return faux;
            }

    }


int **cases_legaux_noir(char **grille) //cette fonction determine les cordonees des cases legaux pour le joueur qui a les pions noires
{
    int c=0,i,j,k,l,nombre_couple=0;//c va nous permettre de parcourir le tableau qui va contenir les cordoonees des cases legaux,
     int **les_cordonnees=matrice_int(64,2); //ce tableau va contenir les cordoonees des cases legaux,


    for(i=0;i<=7;i++)
    {
       for(j=0;j<=7;j++)

      {
          if(la_case_est_noire(grille ,i, j)==vraie)  //si la case est noire
          {
               k=i;
               l=j;
               while(l<6)  //on fait le test a droite
               {
                   l++;
                   if(la_case_est_vide(grille,i,j+1)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie)// s'il y a une case noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k,l+1)==vraie)
                       {
                           les_cordonnees[c][0]=k;
                           les_cordonnees[c][1]=l+1;
                           c++;
                           nombre_couple++;
                           break;

                       }
                   }



               }
               k=i;
               l=j;

                 while(l>1)  //on fait le test a gauche
               {
                   l--;
                   if(la_case_est_vide(grille,i,j-1)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie)// s'il y a une case noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k,l-1)==vraie)
                       {
                           les_cordonnees[c][0]=k;
                           les_cordonnees[c][1]=l-1;
                           c++;
                           nombre_couple++;
                           break;

                       }
                   }



               }
               k=i;
               l=j;
                      while(k>1)  //on fait le test en haut
               {
                   k--;
                   if(la_case_est_vide(grille,i-1,j)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie)// s'il y a une case noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k-1,l)==vraie)
                       {
                           les_cordonnees[c][0]=k-1;
                           les_cordonnees[c][1]=l;
                           c++;
                           nombre_couple++;
                           break;


                       }
                   }



               }
               k=i;
               l=j;

                 while(k<6)  //on fait le test en bas
               {
                   k++;
                   if(la_case_est_vide(grille,i+1,j)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie)// s'il y a une case noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k+1,l)==vraie)
                       {
                           les_cordonnees[c][0]=k+1;
                           les_cordonnees[c][1]=l;
                           c++;
                           nombre_couple++;
                           break;


                       }
                   }



               }
               k=i;
               l=j;

                while(k>1 && l<6)  //on fait le test en haut a droite
               {
                   k--;
                   l++;
                   if(la_case_est_vide(grille,i-1,j+1)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie)// s'il y a une case noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k-1,l+1)==vraie)
                       {
                           les_cordonnees[c][0]=k-1;
                           les_cordonnees[c][1]=l+1;
                           c++;
                           nombre_couple++;
                           break;

                       }
                   }

               }
               k=i;
               l=j;
               while(k>1 && l>1)  //on fait le test en haut a gauche
               {
                   k--;
                   l--;
                   if(la_case_est_vide(grille,i-1,j-1)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie)// s'il y a une case noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k-1,l-1)==vraie)
                       {
                           les_cordonnees[c][0]=k-1;
                           les_cordonnees[c][1]=l-1;
                           c++;
                           nombre_couple++;
                           break;

                       }
                   }

               }
               k=i;
               l=j;
               while(k<6 && l<6)  //on fait le test en bas a droite
               {
                   k++;
                   l++;
                   if(la_case_est_vide(grille,i+1,j+1)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie)// s'il y a une case noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k+1,l+1)==vraie)
                       {
                           les_cordonnees[c][0]=k+1;
                           les_cordonnees[c][1]=l+1;
                           c++;
                           nombre_couple++;
                           break;

                       }
                   }

               }
               k=i;
               l=j;
               while(k<6 && l>1)  //on fait le test en bas a gauche
               {
                   k++;
                   l--;
                   if(la_case_est_vide(grille,i+1,j-1)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie)// s'il y a une case noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k+1,l-1)==vraie)
                       {
                           les_cordonnees[c][0]=k+1;
                           les_cordonnees[c][1]=l-1;
                           c++;
                           nombre_couple++;
                           break;

                       }
                   }

               }


          }
      }
    }
    les_cordonnees[63][0]=nombre_couple;// on met le nombre des couples dans l'avant derniere case
    return les_cordonnees;

}
int **cases_legaux_blanches(char **grille) //cette fonction determine les cordonees des cases legaux por le joueur qui a les pions blanches
{
    int c=0,i,j,k,l,nombre_couple=0;// c va nous permettre de parcourir le tableau qui va contenir les cordoonees des cases legaux
     int **les_cordonnees=matrice_int(64,2); //ce tableau va contenir les cordoonees des cases legaux


    for(i=0;i<=7;i++)
    {
       for(j=0;j<=7;j++)

      {
          if(la_case_est_blanche(grille ,i, j)==vraie)  //si la case est blanche
          {
               k=i;
               l=j;
               while(l<6)  //on fait le test a droite
               {
                   l++;
                   if(la_case_est_vide(grille,i,j+1)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie)// s'il y a une case blanche on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est noire : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k,l+1)==vraie)
                       {
                           les_cordonnees[c][0]=k;
                           les_cordonnees[c][1]=l+1;
                           c++;
                           nombre_couple++;
                           break;

                       }
                   }



               }
               k=i;
               l=j;

                 while(l>1)  //on fait le test a gauche
               {
                   l--;
                   if(la_case_est_vide(grille,i,j-1)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie)// s'il y a une case noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k,l-1)==vraie)
                       {
                           les_cordonnees[c][0]=k;
                           les_cordonnees[c][1]=l-1;
                           c++;
                           nombre_couple++;
                           break;

                       }
                   }



               }
               k=i;
               l=j;
                      while(k>1)  //on fait le test en haut
               {
                   k--;
                   if(la_case_est_vide(grille,i-1,j)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie)// s'il y a une case blanche on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est noire : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k-1,l)==vraie)
                       {
                           les_cordonnees[c][0]=k-1;
                           les_cordonnees[c][1]=l;
                           c++;
                           nombre_couple++;
                           break;


                       }
                   }



               }
               k=i;
               l=j;

                 while(k<6)  //on fait le test en bas
               {
                   k++;
                   if(la_case_est_vide(grille,i+1,j)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie)// s'il y a une case blanche on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est noire : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k+1,l)==vraie)
                       {
                           les_cordonnees[c][0]=k+1;
                           les_cordonnees[c][1]=l;
                           c++;
                           nombre_couple++;
                           break;


                       }
                   }



               }
               k=i;
               l=j;

                while(k>1 && l<6)  //on fait le test en haut a droite
               {
                   k--;
                   l++;
                   if(la_case_est_vide(grille,i-1,j+1)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie)// s'il y a une case blanche on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est noire : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k-1,l+1)==vraie)
                       {
                           les_cordonnees[c][0]=k-1;
                           les_cordonnees[c][1]=l+1;
                           c++;
                           nombre_couple++;
                           break;

                       }
                   }

               }
               k=i;
               l=j;
               while(k>1 && l>1)  //on fait le test en haut a gauche
               {
                   k--;
                   l--;
                   if(la_case_est_vide(grille,i-1,j-1)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie)// s'il y a une case blanche on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est noire : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k-1,l-1)==vraie)
                       {
                           les_cordonnees[c][0]=k-1;
                           les_cordonnees[c][1]=l-1;
                           c++;
                           nombre_couple++;
                           break;

                       }
                   }

               }
               k=i;
               l=j;
               while(k<6 && l<6)  //on fait le test en bas a droite
               {
                   k++;
                   l++;
                   if(la_case_est_vide(grille,i+1,j+1)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie)// s'il y a une case blannche on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est noire : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k+1,l+1)==vraie)
                       {
                           les_cordonnees[c][0]=k+1;
                           les_cordonnees[c][1]=l+1;
                           c++;
                           nombre_couple++;
                           break;

                       }
                   }

               }
               k=i;
               l=j;
               while(k<6 && l>1)  //on fait le test en bas a gauche
               {
                   k++;
                   l--;
                   if(la_case_est_vide(grille,i+1,j-1)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie)// s'il y a une case blanche on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est noire : si la prochaine case est vide alors cette derniere est une case legale
                   {
                       if(la_case_est_vide(grille,k+1,l-1)==vraie)
                       {
                           les_cordonnees[c][0]=k+1;
                           les_cordonnees[c][1]=l-1;
                           c++;
                           nombre_couple++;
                           break;

                       }
                   }

               }


          }
      }
    }
    les_cordonnees[63][0]=nombre_couple;// on met le nombre des couples dans l'avant derniere case
    return les_cordonnees;

}

void modifier(char **grille,int **les_cordonnees) //on va poser des * dans les cases légaux
{
    int i,j;

    for(i=0;i<les_cordonnees[63][0];i++)
    {


            grille[les_cordonnees[i][0]][les_cordonnees[i][1]]= '*' ;

    }

}
void afficherN(char **m){
	int i,j;
	char a='A'; //

	printf("\n");
	for (int i = 0; i < r; i++)
	{

		printf("  %c ", a);
		Color(FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_GREEN);// 2 espaces puis %c puis espace
		a++; //, on va afficher les lettres A B C D E F G H
	}
     printf("  ");//modification
    //voilà l'affichage de la grille
    printf("\n+");
    for (int i = 0; i < r; i++)
        printf("---+");
    printf(" \n");//modification
    for (int i = 0; i < r; i++){
    	printf("|");
        for (int j = 0; j < r; j++){


             if(m[i][j]==noir || m[i][j]==etoile){
                printf("\ ");
            Color(BACKGROUND_GREEN);
          	printf("%c",m[i][j]);//printf("\ %c \|",m[i][j] );
          	Color(FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_GREEN);// 2 espaces puis %c puis espace
            printf(" \|");
             }else{

                printf("\ %c \|",m[i][j] );
             }

          	}


        printf("%d\n+", i+1 );
        for (int j = 0; j < r; j++)
           printf("---+");
        printf(" \n");//modification
    }
}

void afficherB(char **m){
	int i,j;
	char a='A'; //

	printf("\n");
	for (int i = 0; i < r; i++)
	{

		printf("  %c ", a);
		Color(FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_GREEN);// 2 espaces puis %c puis espace
		a++; //, on va afficher les lettres A B C D E F G H
	}
     printf("  ");//modification
    //voilà l'affichage de la grille
    printf("\n+");
    for (int i = 0; i < r; i++)
        printf("---+");
    printf(" \n");//modification
    for (int i = 0; i < r; i++){
    	printf("|");
        for (int j = 0; j < r; j++){


             if(m[i][j]==blanc || m[i][j]==etoile){
                printf("\ ");
            Color(FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_GREEN);// 2 espaces puis %c puis espace

          	printf("%c",m[i][j]);//printf("\ %c \|",m[i][j] );
          	Color(FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_GREEN);// 2 espaces puis %c puis espace
            printf(" \|");
             }else{
                 printf("\ ");
                Color(BACKGROUND_GREEN);
                printf("%c",m[i][j]);//
                Color(FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_GREEN);// 2 espaces puis %c puis espace
                printf(" \|");
             }

          	}


        printf("%d\n+", i+1 );
        for (int j = 0; j < r; j++)
           printf("---+");
        printf(" \n");//modification
    }
}

char ** sandwich_noir(char **grille,int i,int j,int **les_cordonnees ) // i,j les coordonees de la position legale choisie
{
               int k=i,l=j,n,m,a;

               while(l<6 )  //on fait le test a droite
               {
                   l++;
                   if(la_case_est_noire(grille,i,j+1)==vraie) //si la premiere case est noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// si la position correspond a une position legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est noire alors on va remplir les cases precedantes par le noir
                   {
                       if(la_case_est_noire(grille,k,l+1)==vraie)
                       {
                            for(m=j+1;m<=l;m++)
                           {
                               grille[k][m]=noir;
                           }
                           break;

                       }
                   }



               }
               k=i;
               l=j;

                 while(l>1)  //on fait le test a gauche
               {
                   l--;
                   if(la_case_est_noire(grille,i,j-1)==vraie) //si la premiere case est noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// si la case correspond a une case legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est noire alors on va remplir les cases precedantes par le noir
                   {
                       if(la_case_est_noire(grille,k,l-1)==vraie)
                       {
                            for(m=j-1;m>=l;m--)
                           {
                               grille[k][m]=noir;
                           }

                       }
                   }



               }
               k=i;
               l=j;
                      while(k>1)  //on fait le test en haut
               {
                   k--;
                   if(la_case_est_noire(grille,i-1,j)==vraie) //si la premiere case est nooire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// s'il y a une case legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est noire alors on va remplir les cases precedantes par le noir
                   {
                       if(la_case_est_noire(grille,k-1,l)==vraie)
                       {
                           for(n=i-1;n>=k;n--)
                           {
                               grille[n][l]=noir;
                           }
                           break;


                       }
                   }



               }
               k=i;
               l=j;

                 while(k<6)  //on fait le test en bas
               {
                   k++;
                   if(la_case_est_noire(grille,i+1,j)==vraie) //si la premiere case est noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// s'il y a une case legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est noire alors on va remplir les cases precedantes par le noir
                   {
                       if(la_case_est_noire(grille,k+1,l)==vraie)
                       {

                           for(n=i+1;n<=k;n++)
                           {
                               grille[n][l]=noir;
                           }
                           break;



                   }
                   }



               }
               k=i;
               l=j;

                while(k>1 && l<6)  //on fait le test en haut a droite
               {
                   k--;
                   l++;
                   if(la_case_est_noire(grille,i-1,j+1)==vraie) //si la premiere case est noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// s'il y a une case legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est noire alors on va remplir les cases precedantes par le noir
                   {
                       if(la_case_est_noire(grille,k-1,l+1)==vraie)
                       {
                          n=i-1;
                          m=j+1;
                          while(n>=k && m<=l)
                          {
                              grille[n][m]=noir;
                              n--;
                              m++;

                          }
                          break;


                       }
                   }

               }
               k=i;
               l=j;
               while(k>1 && l>1)  //on fait le test en haut a gauche
               {
                   k--;
                   l--;
                   if(la_case_est_noire(grille,i-1,j-1)==vraie) //si la premiere case est noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// s'il y a une case legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est noire alors on va remplir les cases precedantes par le noir
                   {
                       if(la_case_est_noire(grille,k-1,l-1)==vraie)
                       {
                           n=i-1;
                          m=j-1;
                          while(n>=k && m>=l)
                          {
                              grille[n][m]=noir;
                              n--;
                              m--;

                          }
                          break;

                       }
                   }

               }
               k=i;
               l=j;
               while(k<6 && l<6)  //on fait le test en bas a droite
               {
                   k++;
                   l++;
                   if(la_case_est_noire(grille,i+1,j+1)==vraie) //si la premiere case est noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// s'il y a une case legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est noire alors on va remplir les cases precedantes par le noir
                   {
                       if(la_case_est_noire(grille,k+1,l+1)==vraie)
                       {
                          n=i+1;
                          m=j+1;
                          while(n<=k && m<=l)
                          {
                              grille[n][m]=noir;
                              n++;
                              m++;

                          }
                          break;
                       }
                   }

               }
               k=i;
               l=j;
               while(k<6 && l>1)  //on fait le test en bas a gauche
               {
                   k++;
                   l--;
                   if(la_case_est_noire(grille,i+1,j-1)==vraie) //si la premiere case est noire on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// s'il y a une case legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_blanche(grille,k,l)==vraie) //si la case est blanche : si la prochaine case est noire alors on va remplir les cases precedantes par le noir
                   {
                       if(la_case_est_noire(grille,k+1,l-1)==vraie)
                       {
                           n=i+1;
                          m=j-1;
                          while(n<=k && m>=l)
                          {
                              grille[n][m]=noir;
                              n++;
                              m--;

                          }
                          break;

                       }
                   }

               }



               for(a=0;a<les_cordonnees[63][0];a++)             // on remplie les autres cases legaux en vides
    {


            grille[les_cordonnees[a][0]][les_cordonnees[a][1]]=vide;




    }
    grille[i][j]=noir; // on change la position légale en noire




    return grille;


}
char ** sandwich_blanc(char **grille,int i,int j,int **les_cordonnees ) // i,j les coordonees de la position legale choisie
{
               int k=i,l=j,n,m,a;

               while(l<6)  //on fait le test a droite
               {
                   l++;
                   if(la_case_est_blanche(grille,i,j+1)==vraie) //si la premiere case est blanche on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// s'il y a une case legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est noire : si la prochaine case est blanche alors on va remplir les cases precedantes par le blanc
                   {
                       if(la_case_est_blanche(grille,k,l+1)==vraie)
                       {
                            for(m=j+1;m<=l;m++)
                           {
                               grille[k][m]=blanc;
                           }
                           break;

                       }
                   }



               }
               k=i;
               l=j;

                 while(l>1)  //on fait le test a gauche
               {
                   l--;
                   if(la_case_est_blanche(grille,i,j-1)==vraie) //si la premiere case est blanche on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// s'il y a une case legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est noire : si la prochaine case est blanche alors on va remplir les cases precedantes par le blanc
                   {
                       if(la_case_est_blanche(grille,k,l-1)==vraie)
                       {
                            for(m=j-1;m>=l;m--)
                           {
                               grille[k][m]=blanc;
                           }

                       }
                   }



               }
               k=i;
               l=j;
                      while(k>1)  //on fait le test en haut
               {
                   k--;
                   if(la_case_est_blanche(grille,i-1,j)==vraie) //si la premiere case est vide on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// s'il y a une case legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est noire : si la prochaine case est blanche alors on va remplir les cases precedantes par le blanc
                   {
                       if(la_case_est_blanche(grille,k-1,l)==vraie)
                       {
                           for(n=i-1;n>=k;n--)
                           {
                               grille[n][l]=blanc;
                           }
                           break;


                       }
                   }



               }
               k=i;
               l=j;

                 while(k<6)  //on fait le test en bas
               {
                   k++;
                   if(la_case_est_blanche(grille,i+1,j)==vraie) //si la premiere case est blanche on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// s'il y a une case legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est noire : si la prochaine case est blanche alors on va remplir les cases precedantes par le blanc
                   {
                       if(la_case_est_blanche(grille,k+1,l)==vraie)
                       {

                           for(n=i+1;n<=k;n++)
                           {
                               grille[n][l]=blanc;
                           }
                           break;



                   }
                   }



               }
               k=i;
               l=j;

                while(k>1 && l<6)  //on fait le test en haut a droite
               {
                   k--;
                   l++;
                   if(la_case_est_blanche(grille,i-1,j+1)==vraie) //si la premiere case est blanche on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// s'il y a une case legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est noire : si la prochaine case est blanche alors on va remplir les cases precedantes par le blanc
                   {
                       if(la_case_est_blanche(grille,k-1,l+1)==vraie)
                       {
                          n=i-1;
                          m=j+1;
                          while(n>=k && m<=l)
                          {
                              grille[n][m]=blanc;
                              n--;
                              m++;

                          }
                          break;


                       }
                   }

               }
               k=i;
               l=j;
               while(k>1 && l>1)  //on fait le test en haut a gauche
               {
                   k--;
                   l--;
                   if(la_case_est_blanche(grille,i-1,j-1)==vraie) //si la premiere case est blanche on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// s'il y a une case legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est noire : si la prochaine case est blanche alors on va remplir les cases precedantes par le blanc
                   {
                       if(la_case_est_blanche(grille,k-1,l-1)==vraie)
                       {
                           n=i-1;
                          m=j-1;
                          while(n>=k && m>=l)
                          {
                              grille[n][m]=blanc;
                              n--;
                              m--;

                          }
                          break;

                       }
                   }

               }
               k=i;
               l=j;
               while(k<6 && l<6)  //on fait le test en bas a droite
               {
                   k++;
                   l++;
                   if(la_case_est_blanche(grille,i+1,j+1)==vraie) //si la premiere case est blanche on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// s'il y a une case legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est noire : si la prochaine case est blanche alors on va remplir les cases precedantes par le blanc
                   {
                       if(la_case_est_blanche(grille,k+1,l+1)==vraie)
                       {
                          n=i+1;
                          m=j+1;
                          while(n<=k && m<=l)
                          {
                              grille[n][m]=blanc;
                              n++;
                              m++;

                          }
                          break;
                       }
                   }

               }
               k=i;
               l=j;
               while(k<6 && l>1)  //on fait le test en bas a gauche
               {
                   k++;
                   l--;
                   if(la_case_est_blanche(grille,i+1,j-1)==vraie) //si la premiere case est blanche on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_vide(grille,k,l)==vraie)// s'il y a une case vide on arrete la boucle
                   {
                       break;
                   }
                   else if(grille[k][l]=='*')// s'il y a une case legale on arrete la boucle
                   {
                       break;
                   }
                   else if(la_case_est_noire(grille,k,l)==vraie) //si la case est noire : si la prochaine case est blanche alors on va remplir les cases precedantes par le blanc
                   {
                       if(la_case_est_blanche(grille,k+1,l-1)==vraie)
                       {
                           n=i+1;
                          m=j-1;
                          while(n<=k && m>=l)
                          {
                              grille[n][m]=blanc;
                              n++;
                              m--;

                          }
                          break;

                       }
                   }

               }



               for(a=0;a<les_cordonnees[63][0];a++)             // on remplie les autres cases legaux en vides
    {


            grille[les_cordonnees[a][0]][les_cordonnees[a][1]]=vide;




    }
    grille[i][j]=blanc; // on change la position légale en noire

    return grille;


}
int *choisir_position(int **les_cordonnees )
{   int test=0,vraie=1,i,choixi,choixj;
char lettre;
/*
int *A=1;
char *B='&';


printf("A est %d et B est %c",A,B);
PERMUTER(&A,&B);
printf(" NEW A est %d et B est %c",A,B);
*/
 int *choix=malloc(2 * sizeof(int)); //?
    while(vraie==1)
    {
    if (coup==1){
        chrono();
         lettre=c;
        }else{

        chrono2();
        lettre=cc;
        }

    //printf("\nchoisir D puis 3 par exemple\n");
    //scanf("\n%c",&lettre);


    /* On change les minuscules en majuscules */
    if ((lettre>='a')&&(lettre<'a'+r))
        lettre=lettre+'A'-'a';
    //--------------
    choixj=lettre-'A';
    scanf("\n%d",&choixi);

   fflush(stdin);

        switch(choixi){
        case '1':case '&': choixi=1;
           break;
        case '2':case 'é': choixi=2;
           break;
           case '3':case '"': choixi=3;
           break;
           case '4':case '\'': choixi=4;
           break;
           case '5':case '\(': choixi=5;
           break;
           case '6':case '-': choixi=6;
           break;
           case '7':case 'è': choixi=7;
           break;
           case '8':case '_': choixi=8;


        }

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

     printf("la position est fausse veuillez rechoisir une autre position\n");

}

}
//pour le "SCORE"
int score(char **grille){
   int NpionsN=0;
   int NpionsB=0;
   for(int i=0;i<r;i++){
    for(int j=0;j<r;j++){
        if (grille[i][j]==vide){
            NpionsB+=0;
            NpionsN+=0;
        }else{
            if (grille[i][j]==blanc)
               NpionsB++;
            else if(grille[i][j]==noir)
               NpionsN++;
        }


    }
   }




  /* printf("             OTHELLO\n\n");
    //printf("--------------SCORE--------------\n|      NOIR     |     BLANC     |\n|        %d      |       %d       |\n---------------------------------\n",p,q);
    printf("--------------SCORE--------------\n      NOIR           BLANC     \n        %d              %d       \n---------------------------------\n",NpionsN,NpionsB);
     */

     printf("             OTHELLO              \n                                  \n");
    //printf("--------------SCORE--------------\n|      NOIR     |     BLANC     |\n|        %d      |       %d       |\n---------------------------------\n",p,q);
    printf("--------------SCORE---------------\n      NOIR           BLANC        \n        %d              %d          \n----------------------------------\n",NpionsN,NpionsB);


   /*afficher(m);
   printf("----------------------------------\n");
    */    //il faut corriger ça


}

int position_de_jeu(int **les_cordonnees)
{

    if(les_cordonnees[63][0]==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void le_gagnant_est(char **grille)
{
    int i,j,nombre_de_cases_noires=0,nombre_de_cases_blanches=0;
    for(i=0;i<=7;i++)
   {
       for(j=0;j<=7;j++)
       {
           if(grille[i][j]==noir)
           {
               nombre_de_cases_noires++;
           }
           else if(grille[i][j]==blanc)
           {
               nombre_de_cases_blanches++;
           }
       }
   }
   if(nombre_de_cases_noires>nombre_de_cases_blanches)
   {
       printf("fin du jeu le gagnant est :\nle joueur noir\n");
   }
   else if(nombre_de_cases_noires<nombre_de_cases_blanches)
   {
        printf("fin du jeu le gagnant est :\nle joueur blanc\n");
   }
   else
    {
        printf("match nul");
    }
}
void init(char **m){
	int i,j;
    //on remplie premierement toutes les cases par X
	for(i=0;i<r;i++)
		for(j=0;j<r;j++)
			m[i][j]=vide;
    //les 4 1ere pions au centre

    m[(r/2)][(r/2)]=blanc;

    m[(r/2)][(r/2)-1]=noir;

    m[(r/2)-1][(r/2)-1]=blanc;

    m[(r/2)-1][(r/2)]=noir;
}
void Color(int flags)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,(WORD)flags);
}
int higt_score(void)
{
    FILE *f;
    f=fopen("fichier_de_scores.txt","r");
    char lire_les_char[20];
    int lire_les_int;
    int t[20];
    int c=0,imax=0;
    fscanf(f,"%s",lire_les_char);
    fscanf(f,"%s",lire_les_char);
    while(!feof(f))
    {
        fscanf(f,"%s",lire_les_char);
        fscanf(f,"%d",&lire_les_int);
        t[c]=lire_les_int;
        c++;
    }
    fclose(f);
    for(int i=1;i<c;i++)
    {
        if(t[i]>t[imax])
        {
            imax=i;
        }
    }
    return t[imax];
}
void afficher_fichier_score(void)
{
    printf("les meilleurs resultats des joueurs :\n");
    printf("------------------------------------\n");
    FILE *f;
    f=fopen("fichier_de_scores.txt","r");
    char lire_les_char[20];
    int lire_les_int;
    fscanf(f,"%s",lire_les_char);// lire name
    printf("%s\t\t",lire_les_char); // afficher name
    fscanf(f,"%s",lire_les_char); // lire score
    printf("%s\n",lire_les_char); // afficher score
    while(!feof(f))
    {
        fscanf(f,"%s",lire_les_char);
    printf("\n%s\t\t",lire_les_char);
    fscanf(f,"%d",&lire_les_int);
    printf("%d",lire_les_int);
    }
    fclose(f);

}

void ajouter_joueur(char *c,int score)
{
    FILE *f;
    f=fopen("fichier_de_scores.txt","a");
    fprintf(f,"\n%s\t\t",c);
    fprintf(f,"%d",score);
    fclose(f);
}
int *score_des_joueurs(char **grille)
{
     int i,j,nombre_de_cases_noires=0,nombre_de_cases_blanches=0;
     int *t=malloc(2 * sizeof(int)); // tableau qui contient le score des deux joueurs
    for(i=0;i<=7;i++)
   {
       for(j=0;j<=7;j++)
       {
           if(grille[i][j]==noir)
           {
               nombre_de_cases_noires++;
           }
           else if(grille[i][j]==blanc)
           {
               nombre_de_cases_blanches++;
           }
       }
   }
   t[0]=nombre_de_cases_noires; // score du noir
   t[1]=nombre_de_cases_blanches; // score du blanc
   return t;
}
int joueur_vs_joueur(int argc, char** argv)
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



    char** grille=matrice_char(8,9);//?
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
    int *choix_de_position_noire=malloc(2*sizeof(int));
    int *choix_de_position_blanche=malloc(2*sizeof(int));
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
        printf("vous etes gangnant entrer votre nom :\n");
        scanf("%s",nom_du_joueur);
        if(score_du_jeu[0]>score_du_jeu[1]) // si le noir gagne on ajoute son score
        {
        ajouter_joueur(nom_du_joueur,score_du_jeu[0]);
        }
        else
        {
            ajouter_joueur(nom_du_joueur,score_du_jeu[1]);
        }
        if(score_du_jeu[0]==higt_score() || score_du_jeu[1]==higt_score() )
        {
            printf("felicitation vous avez realisé un nouveau hight score\n");

            afficher_fichier();

        }
        else
            {

            afficher_fichier();
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
    choix_de_position_noire=choisir_position(les_cordonnees_noires);
    coup--;
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
        if(score_du_jeu[0]>score_du_jeu[1]) // si le noir gagne on ajoute son score
        {
        ajouter_joueur(nom_du_joueur,score_du_jeu[0]);
        }
        else
        {
            ajouter_joueur(nom_du_joueur,score_du_jeu[1]);
        }
        if(score_du_jeu[0]==higt_score() || score_du_jeu[1]==higt_score() )
        {
            printf("felicitation vous avez realisé un nouveau hight score\n");

            afficher_fichier();

        }
        else
            {

            afficher_fichier();
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


    choix_de_position_blanche=choisir_position(les_cordonnees_blanches);
    coup++;
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
