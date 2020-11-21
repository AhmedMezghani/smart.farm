#include <stdio.h>
#include <stdlib.h>

typedef struct client{
char nom[10];
char prenom[10];
char CIN[10];
char mail[40];
char num[10];
};

void afficher();
void rechercher();
void ajouter_client(int *nombre_client);
void modifier_client();
void supprimer_client(int *nombre_client);

int main()
{
    int nombre_client=0;
    int option;
    do
    {
        printf("1-afficher|2-rechercher|3-ajouter|4-modifier|5-supprimer: ");scanf("%d",&option);
        switch (option)
        {
            case 1 : afficher();break;
            case 2 : rechercher();break;
            case 3 : ajouter_client(&nombre_client);break;
            case 4 : modifier_client();break;
            case 5 : supprimer_client(&nombre_client);break;
            default : printf("option doit etre entre 1 et 5\n");break;
        }
    }
    while (1);
}
void afficher()
{
    FILE* f;
    int rech=0;
    char nom[20],prenom[20],mail[20],num[10],CIN[20];
    int i=0;
    printf("\nAfficher -----------------------------------------------------\n");
    f=fopen("client.txt","r");
    if (f==EOF)
        printf("pas d'client pour afficher\n");
    else
    {
        printf("1");
        while (fscanf(f,"%s %s %s %s %s\n",nom,prenom,CIN,mail,num)!=EOF)
        {
                printf("\nclient %d\n",i+1);
                printf("    nom: %s\n",nom);
                printf("    prenom: %s\n",prenom);
                printf("    CIN: %s\n",CIN);
                printf("    mail : %s\n",mail);
                printf("    num telephone: %s\n",num);
                i++;
        }
    }
    fclose(f);
}
void rechercher()
{
    FILE* f;
    int rech=0;
    char nom[20],prenom[20],mail[20],num[10],CIN[20],CIN_rech[20];
    printf("\nRechercher -----------------------------------------------------\n");
    f=fopen("client.txt","r");
    if (f==EOF)
        printf("pas d'client pour rechercher\n");
    else
    {
        fflush(stdin);
        printf("    CIN : ");gets(CIN_rech);
        while (fscanf(f,"%s %s %s %s %s\n",nom,prenom,CIN,mail,num)!=EOF)
        {
            if (strcmp(CIN,CIN_rech)==0)
            {
                printf("    nom: %s\n",nom);
                printf("    CIN: %d\n",CIN);
                printf("    prenom: %s\n",prenom);
                printf("    mail : %s\n",mail);
                printf("    num telephone: %s\n",num);
                rech=1;
            }
        }
    }
    if (rech==0)
        printf("Impossible de trouver cet client");
    fclose(f);

}

void ajouter_client(int *nombre_client)
{
    FILE* f;
    struct client client;
    printf("\nAjouter -----------------------------------------------------\n");
    fflush(stdin);
    printf("    nom : ");gets(client.nom);
    fflush(stdin);
    printf("    prenom : ");gets(client.prenom);
    fflush(stdin);
    printf("    CIN : ");gets(client.CIN);
    fflush(stdin);
    printf("    mail : ");gets(client.mail);
    printf("    num telephone : ");gets(client.num);
    f=fopen("client.txt","a+");
    fprintf(f,"%s %s %s %s %s\n",client.nom,client.prenom,client.CIN,client.mail,client.num);
    fclose(f);
    *nombre_client++;

}

void modifier_client()
{
    FILE* f ;
    FILE* f2;
    char nom[20],prenom[20],mail[20],num[10],CIN[10];
    int CIN_rech;
    printf("\nModifier -----------------------------------------------------\n");
    fflush(stdin);
    f=fopen("client.txt","r+");
    f2=fopen("tmp.txt","a+");
    if (fscanf(f,"%s %s %s %s %s\n",nom,prenom,CIN,mail,num)==EOF)
        printf("pas d'client pour modifier\n");
    else
    {
        printf("CIN : ");scanf("%d",&CIN_rech);
        while (fscanf(f,"%s %s %s %s %s\n",nom,prenom,CIN,mail,num)!=EOF)
        {
                if (CIN==CIN_rech)
                {
                    fflush(stdin);
                    printf("    nom: %s  --->",nom);gets(nom);
                    fflush(stdin);
                    printf("    prenom: %s  --->",prenom);gets(prenom);
                    fflush(stdin);
                    printf("    CIN: %s  --->",CIN);gets(CIN);
                    fflush(stdin);
                    printf("    mail : %s  --->",mail);gets(mail);
                    fflush(stdin);
                    printf("    num telephone : %s  --->",num);gets(num);
                    fprintf(f2,"%s %s %s %s %s\n",nom,prenom,CIN,mail,num);
                }
                else
                   fprintf(f2,"%s %s %s %s %s\n",nom,prenom,CIN,mail,num);
        }
    }
    fclose(f);
    fclose(f2);
    remove("client.txt");
    rename("tmp.txt","client.txt");
}
void supprimer_client(int *nombre_client)
{
    FILE* f ;
    FILE* f2;
    char nom[20],prenom[20],mail[20],num[10],CIN[10];
    int CIN_rech;
    printf("\nSupprimer -----------------------------------------------------\n");
    f=fopen("client.txt","r+");
    f2=fopen("tmp.txt","a+");
    if (fscanf(f,"%s %s %s %s %s\n",nom,prenom,CIN,mail,num)==EOF)
        printf("pas d'client pour supprimer\n");
    else
    {
        printf("CIN : ");scanf("%d",&CIN_rech);
        while (fscanf(f,"%s %s %s %s %s\n",nom,prenom,CIN,mail,num)!=EOF)
        {
                if (CIN!=CIN_rech)
                   fprintf(f2,"%s %s %s %s %s\n",nom,prenom,CIN,mail,num);
        }
    }
    fclose(f);
    fclose(f2);
    remove("client.txt");
    rename("tmp.txt","client.txt");
    *nombre_client--;
}
