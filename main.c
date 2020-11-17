#include <stdio.h>
#include <stdlib.h>
typedef struct Date{
int jour;
int mois;
int annee;
};
typedef struct Troupeau{
char identifiant[5];
char name[10];
char sexe[10];
struct Date date_naissance;
char sante[20];

};
void ajouter_animal(int *nombre_vache,int *nombre_mouton);
void modifier_animal();
void supprimer_animal(int *nombre_vache,int *nombre_mouton);

int main()
{
    int nombre_vache=0,nombre_mouton=0;
    int option;
    do
    {
        printf("1-ajouter|2-modifier|3-supprimer: ");scanf("%d",&option);
        switch (option)
        {
            case 1 : ajouter_animal(&nombre_vache,&nombre_mouton);break;
            case 2 : modifier_animal();break;
                break;
            case 3 :supprimer_animal(&nombre_vache,&nombre_mouton);
                break;
            default : printf("option doit etre entre 1 et 3");
        }
    }
    while (1);
}
void ajouter_animal(int *nombre_vache,int *nombre_mouton)
{
    FILE* f;
    struct Troupeau animal;
    printf("\nAjouter -----------------------------------------------------\n");
    fflush(stdin);
    printf("    name : ");gets(animal.name);
    fflush(stdin);
    printf("    identifiant : ");gets(animal.identifiant);
    printf("    sexe : ");gets(animal.sexe);
    fflush(stdin);
    printf("    date_naissance:\n");
    printf("        jour : ");scanf("%d",&animal.date_naissance.jour);
    printf("        mois : ");scanf("%d",&animal.date_naissance.mois);
    printf("        annee : ");scanf("%d",&animal.date_naissance.annee);
    printf("    sante : ");gets(animal.sante);
    f=fopen("troupeau.txt","a+");
    fprintf(f,"%s %s %s %d %d %d\n",animal.name,animal.identifiant,animal.sexe,animal.date_naissance.jour,animal.date_naissance.mois,animal.date_naissance.annee);
    fclose(f);
    if (strcmp(animal.name,"vache")==0)
        *nombre_vache++;
    else *nombre_mouton++;
}

void modifier_animal()
{
    FILE* f ;
    FILE* f2;
    char identifiant_animal[20],name[20],identifiant[20],sexe[20],sante[20];
    int jour,mois,annee;
    printf("\nModifier -----------------------------------------------------\n");
    fflush(stdin);
    printf("identifiant : ");gets(identifiant_animal);
    f=fopen("troupeau.txt","r+");
    f2=fopen("tmp.txt","a+");
    while (fscanf(f,"%s %s %s %d %d %d %s\n",name,identifiant,sexe,&jour,&mois,&annee,sante)!=EOF)
    {
            if (strcmp(identifiant,identifiant_animal)==0)
            {
                fflush(stdin);
                printf("    name: %s  --->",name);gets(name);
                fflush(stdin);
                printf("    identifiant: %s  --->",identifiant);gets(identifiant);
                printf("    sexe: %s  --->",sexe);gets(sexe);
                fflush(stdin);
                printf("    date_naissance:\n");
                printf("        jour : %d  --->",jour);scanf("%d",&jour);
                printf("        mois : %d  --->",annee);scanf("%d",&mois);
                printf("        annee : %d  --->",annee);scanf("%d",&annee);
                printf("        sante : %s  --->",sante);gets(sante);
                fprintf(f2,"%s %s %s %d %d %d %s\n",name,identifiant,sexe,jour,mois,annee,sante);
            }
            else
            {
               fprintf(f2,"%s %s %s %d %d %d %s\n",name,identifiant,sexe,jour,mois,annee,sante);
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
    char identifiant_animal[20],name[20],identifiant[20],sexe[20],sante[20];
    int jour,mois,annee;
    printf("\nModifier -----------------------------------------------------\n");
    fflush(stdin);
    printf("identifiant : ");gets(identifiant_animal);
    f=fopen("troupeau.txt","r+");
    f2=fopen("tmp.txt","a+");
    while (fscanf(f,"%s %s %s %d %d %d %s\n",name,identifiant,sexe,&jour,&mois,&annee,sante)!=EOF)
    {
            if (strcmp(identifiant,identifiant_animal)!=0)
               fprintf(f2,"%s %s %s %d %d %d %s\n",name,identifiant,sexe,jour,mois,annee,sante);

    }
    fclose(f);
    fclose(f2);
    remove("troupeau.txt");
    rename("tmp.txt","troupeau.txt");
    if (strcmp(name,"vache")==0)
        *nombre_vache--;
    else *nombre_mouton--;
}
