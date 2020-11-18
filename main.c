#include <stdio.h>
#include <stdlib.h>
typedef struct Date{
int jour;
int mois;
int annee;
};
typedef struct Troupeau{
int boucle;
char name[10];
char sexe[10];
struct Date date_naissance;
char sante[20];

};
void afficher();
void rechercher();
void ajouter_animal(int *nombre_vache,int *nombre_mouton);
void modifier_animal();
void supprimer_animal(int *nombre_vache,int *nombre_mouton);

int main()
{
    int nombre_vache=0,nombre_mouton=0;
    int option;
    do
    {
        printf("1-afficher|2-rechercher|3-ajouter|4-modifier|5-supprimer: ");scanf("%d",&option);
        switch (option)
        {
            case 1 : afficher();break;
            case 2 : rechercher();break;
            case 3 : ajouter_animal(&nombre_vache,&nombre_mouton);break;
            case 4 : modifier_animal();break;
            case 5 : supprimer_animal(&nombre_vache,&nombre_mouton);break;
            default : printf("option doit etre entre 1 et 5\n");break;
        }
    }
    while (1);
}
void afficher()
{
    FILE* f;
    int rech=0;
    char name[20],sexe[20],sante[20];
    int boucle,jour,mois,annee,i=0;
    printf("\nAfficher -----------------------------------------------------\n");
    f=fopen("troupeau.txt","r");
    if (fscanf(f,"%s %d %s %d %d %d %s\n",name,&boucle,sexe,&jour,&mois,&annee,sante)==EOF)
        printf("pas d'animal pour afficher\n");
    else
    {
        while (fscanf(f,"%s %d %s %d %d %d %s\n",name,&boucle,sexe,&jour,&mois,&annee,sante)!=EOF)
        {
                printf("\nAnimal %d\n",i+1);
                printf("    name: %s\n",name);
                printf("    boucle: %d\n",boucle);
                printf("    sexe: %s\n",sexe);
                printf("    date_naissance:\n");
                printf("        jour : %d\n",jour);
                printf("        mois : %d\n",mois);
                printf("        annee : %d\n",annee);
                printf("    sante : %s\n",sante);
                i++;
        }
    }
}
void rechercher()
{
    FILE* f;
    int rech=0;
    char name[20],sexe[20],sante[20];
    int boucle,boucle_rech,jour,mois,annee;
    printf("\nRechercher -----------------------------------------------------\n");
    f=fopen("troupeau.txt","r");
    if (fscanf(f,"%s %d %s %d %d %d %s\n",name,&boucle,sexe,&jour,&mois,&annee,sante)==EOF)
        printf("pas d'animal pour rechercher\n");
    else
    {
        printf("    Boucle : ");scanf("%d",&boucle_rech);
        while (fscanf(f,"%s %d %s %d %d %d %s\n",name,&boucle,sexe,&jour,&mois,&annee,sante)!=EOF)
        {
            if (boucle==boucle_rech)
            {
                printf("    name: %s\n",name);
                printf("    boucle: %d\n",boucle);
                printf("    sexe: %s\n",sexe);
                printf("    date_naissance:\n");
                printf("        jour : %d\n",jour);
                printf("        mois : %d\n",mois);
                printf("        annee : %d\n",annee);
                printf("    sante : %s\n",sante);
                rech=1;
            }
        }
    }
    if (rech==0)
        printf("Impossible de trouver cet animal");
    fclose(f);

}

void ajouter_animal(int *nombre_vache,int *nombre_mouton)
{
    FILE* f;
    struct Troupeau animal;
    printf("\nAjouter -----------------------------------------------------\n");
    fflush(stdin);
    printf("    name : ");gets(animal.name);
    fflush(stdin);
    printf("    boucle : ");scanf("%d",&animal.boucle);
    fflush(stdin);
    printf("    sexe : ");gets(animal.sexe);
    fflush(stdin);
    printf("    date_naissance:\n");
    printf("        jour : ");scanf("%d",&animal.date_naissance.jour);
    printf("        mois : ");scanf("%d",&animal.date_naissance.mois);
    printf("        annee : ");scanf("%d",&animal.date_naissance.annee);
    fflush(stdin);
    printf("    sante : ");gets(animal.sante);
    f=fopen("troupeau.txt","a+");
    fprintf(f,"%s %d %s %d %d %d %s\n",animal.name,animal.boucle,animal.sexe,animal.date_naissance.jour,animal.date_naissance.mois,animal.date_naissance.annee,animal.sante);
    fclose(f);
    if (strcmp(animal.name,"vache")==0)
        *nombre_vache++;
    else *nombre_mouton++;
}

void modifier_animal()
{
    FILE* f ;
    FILE* f2;
    char name[20],sexe[20],sante[20];
    int boucle,boucle_rech,jour,mois,annee;
    printf("\nModifier -----------------------------------------------------\n");
    fflush(stdin);
    f=fopen("troupeau.txt","r+");
    f2=fopen("tmp.txt","a+");
    if (fscanf(f,"%s %d %s %d %d %d %s\n",name,&boucle,sexe,&jour,&mois,&annee,sante)==EOF)
        printf("pas d'animal pour modifier\n");
    else
    {
        printf("boucle : ");scanf("%d",&boucle_rech);
        while (fscanf(f,"%s %d %s %d %d %d %s\n",name,&boucle,sexe,&jour,&mois,&annee,sante)!=EOF)
        {
                if (boucle==boucle_rech)
                {
                    fflush(stdin);
                    printf("    name: %s  --->",name);gets(name);
                    fflush(stdin);
                    printf("    boucle: %d  --->",boucle);scanf("%d",&boucle);
                    fflush(stdin);
                    printf("    sexe: %s  --->",sexe);gets(sexe);
                    fflush(stdin);
                    printf("    date_naissance:\n");
                    printf("        jour : %d  --->",jour);scanf("%d",&jour);
                    printf("        mois : %d  --->",mois);scanf("%d",&mois);
                    printf("        annee : %d  --->",annee);scanf("%d",&annee);
                    fflush(stdin);
                    printf("        sante : %s  --->",sante);gets(sante);
                    fprintf(f2,"%s %d %s %d %d %d %s\n",name,boucle,sexe,jour,mois,annee,sante);
                }
                else
                   fprintf(f2,"%s %d %s %d %d %d %s\n",name,boucle,sexe,jour,mois,annee,sante);
        }
    }
    fclose(f);
    fclose(f2);
    remove("troupeau.txt");
    rename("tmp.txt","troupeau.txt");
}
void supprimer_animal(int *nombre_vache,int *nombre_mouton)
{
    FILE* f ;
    FILE* f2;
    char name[20],sexe[20],sante[20];
    int boucle,boucle_rech,jour,mois,annee;
    printf("\nSupprimer -----------------------------------------------------\n");
    f=fopen("troupeau.txt","r+");
    f2=fopen("tmp.txt","a+");
    if (fscanf(f,"%s %d %s %d %d %d %s\n",name,&boucle,sexe,&jour,&mois,&annee,sante)==EOF)
        printf("pas d'animal pour supprimer\n");
    else
    {
        printf("boucle : ");scanf("%d",&boucle_rech);
        while (fscanf(f,"%s %d %s %d %d %d %s\n",name,&boucle,sexe,&jour,&mois,&annee,sante)!=EOF)
        {
                if (boucle!=boucle_rech)
                   fprintf(f2,"%s %d %s %d %d %d %s\n",name,boucle,sexe,jour,mois,annee,sante);
        }
    }
    fclose(f);
    fclose(f2);
    remove("troupeau.txt");
    rename("tmp.txt","troupeau.txt");
    if (strcmp(name,"vache")==0)
        *nombre_vache--;
    else *nombre_mouton--;
}
