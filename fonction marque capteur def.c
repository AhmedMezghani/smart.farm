#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void lireCapteurs(char *nomFichierCapteurs);
int calculer_nbre_capteurs_defectueux(char *token);
int main()
{
    lireCapteurs("capteurs.txt");
    return 0;
}

void lireCapteurs(char *nomFichierCapteurs){

    char buffer[30];

    FILE * fichierCapteurs;

    char delim[] = ",";

    char *marquesAyantNombreMaxCapteursDefectueux = malloc(sizeof(char) * 1024);

    fichierCapteurs = fopen(nomFichierCapteurs, "r");

    if (NULL == fichierCapteurs)
    {
         perror("opening fichierCapteurs");
         return (-1);
    }

    char *marqueAyantNombreMaxCapteursDefectueux = malloc(sizeof(char) * 1024);
    int nbre_max_capteurs_defectueux = -1;

    while (EOF != fscanf(fichierCapteurs, "%[^\n]\n", buffer))
    {
         char *token = strtok(buffer, delim);

         char *marque = token;

         int nbre_capteurs_defectueux = calculer_nbre_capteurs_defectueux(token);

         if((nbre_capteurs_defectueux >= nbre_max_capteurs_defectueux) && marque != NULL){

            if(nbre_capteurs_defectueux == nbre_max_capteurs_defectueux){
              char temp[1000]= ",";
              strcat(temp,marque);
              marqueAyantNombreMaxCapteursDefectueux = strcat(marqueAyantNombreMaxCapteursDefectueux, temp);
            }
            else{
                nbre_max_capteurs_defectueux = nbre_capteurs_defectueux;
                strcpy(marqueAyantNombreMaxCapteursDefectueux,marque);
            }

         }
    }

    printf("La marque [%s] a le nombre max de capteurs defectueux: %i\n", marqueAyantNombreMaxCapteursDefectueux, nbre_max_capteurs_defectueux);

    fclose(fichierCapteurs);
    return (0);
}

int calculer_nbre_capteurs_defectueux(char *token){
    int i = 0;
    int nbre_capteurs_defectueux=0;
    char *marqueCapteur=malloc(sizeof(char) * 1024);
    while (token != NULL)
    {
        if (i == 0){
            marqueCapteur = token;
        }

        else if(i > 0){
            if((token != NULL) && ((atoi(token) < 10) || (atoi(token) >40))){
                printf("capteur defectueux : %s\n", token);
                nbre_capteurs_defectueux++;
            }
        }

        token = strtok(NULL, ",");

        i++;
    }

    printf("Nombre de capteurs defectueux de la marque [%s]: %i\n", marqueCapteur, nbre_capteurs_defectueux);
    return nbre_capteurs_defectueux;
}
