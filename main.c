#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct { int jour, mois, annee; } Date;

typedef struct {
    int id;
    char nom[100];
    char prenom[100];
    int age;
    Date naissance;
    struct {
        char type[50];
        int duree;
    } ab;
    struct {
        int CIN_etudiant;
        float montant;
        Date date_paiement;
    } pay;
} Etudiant;

Etudiant tabEt[MAX];
int n=0;

int rechercherEt(int id){
    int i;
    for(i=0;i<n;i++) if(tabEt[i].id==id) return i;
    return -1;
}

void enlever_saut_ligne(char *str){
    size_t len=strlen(str);
    if(len>0 && str[len-1]=='\n') str[len-1]='\0';
}


void ajouterEtudiant(){
    if(n>=MAX){ printf("Tableau plein !\n"); return; }
    printf("ID: "); scanf("%d",&tabEt[n].id); getchar();
    printf("Nom: "); fgets(tabEt[n].nom,sizeof(tabEt[n].nom),stdin); enlever_saut_ligne(tabEt[n].nom);
    printf("Prenom: "); fgets(tabEt[n].prenom,sizeof(tabEt[n].prenom),stdin); enlever_saut_ligne(tabEt[n].prenom);
    printf("Age: "); scanf("%d",&tabEt[n].age); getchar();
    printf("Date naissance (j m a): "); scanf("%d %d %d",&tabEt[n].naissance.jour,&tabEt[n].naissance.mois,&tabEt[n].naissance.annee); getchar();
    printf("Type abonnement: "); fgets(tabEt[n].ab.type,sizeof(tabEt[n].ab.type),stdin); enlever_saut_ligne(tabEt[n].ab.type);
    printf("Duree (mois): "); scanf("%d",&tabEt[n].ab.duree); getchar();
    printf("CIN etudiant (paiement): "); scanf("%d",&tabEt[n].pay.CIN_etudiant); getchar();
    printf("Montant: "); scanf("%f",&tabEt[n].pay.montant); getchar();
    printf("Date paiement (j m a): "); scanf("%d %d %d",&tabEt[n].pay.date_paiement.jour,&tabEt[n].pay.date_paiement.mois,&tabEt[n].pay.date_paiement.annee); getchar();
    n++;
    printf("Etudiant ajouté !\n");
}

void afficherEtudiants(){
    if(n==0){ printf("Aucun etudiant.\n"); return; }
    int i;
    for(i=0;i<n;i++){
        printf("\nEtudiant %d\n", i+1);
        printf("ID: %d\n", tabEt[i].id);
        printf("Nom: %s %s\n", tabEt[i].nom, tabEt[i].prenom);
        printf("Age: %d\n", tabEt[i].age);
        printf("Naissance: %d/%d/%d\n", tabEt[i].naissance.jour, tabEt[i].naissance.mois, tabEt[i].naissance.annee);
        printf("Abonnement: %s (%d mois)\n", tabEt[i].ab.type, tabEt[i].ab.duree);
        printf("Paiement: CIN=%d, %.2f DT\n", tabEt[i].pay.CIN_etudiant, tabEt[i].pay.montant);
        printf("Date paiement: %d/%d/%d\n", tabEt[i].pay.date_paiement.jour, tabEt[i].pay.date_paiement.mois, tabEt[i].pay.date_paiement.annee);
    }
}

void rechercherEtudiant(){
    int id; printf("ID a chercher: "); scanf("%d",&id); getchar();
    int pos = rechercherEt(id);
    if(pos==-1) printf("Non trouve.\n");
    else printf("Trouve: %s %s\n",tabEt[pos].nom,tabEt[pos].prenom);
}

void modifierEtudiant(){
    int id; printf("ID a modifier: "); scanf("%d",&id); getchar();
    int pos=rechercherEt(id);
    if(pos==-1){ printf("Non trouve.\n"); return; }
    printf("Nouveau nom: "); fgets(tabEt[pos].nom,sizeof(tabEt[pos].nom),stdin); enlever_saut_ligne(tabEt[pos].nom);
    printf("Nouveau prenom: "); fgets(tabEt[pos].prenom,sizeof(tabEt[pos].prenom),stdin); enlever_saut_ligne(tabEt[pos].prenom);
    printf("Nouveau age: "); scanf("%d",&tabEt[pos].age); getchar();
    printf("Modification reussie !\n");
}

void supprimerEtudiant(){
    int id; printf("ID a supprimer: "); scanf("%d",&id); getchar();
    int pos=rechercherEt(id);
    if(pos==-1){ printf("Non trouve.\n"); return; }
    int i;
    for(i=pos;i<n-1;i++) tabEt[i]=tabEt[i+1];
    n--;
    printf("Etudiant supprime !\n");
}

void menuEtudiants(){
    int choix;
    do{
        printf("Gestion des etudiants \n1) Ajouter\n2) Modifier\n3) Supprimer\n4) Rechercher\n5) Afficher\n0) Retour\nChoix: ");
        scanf("%d",&choix); getchar();
        switch(choix){
            case 1: ajouterEtudiant(); break;
            case 2: modifierEtudiant(); break;
            case 3: supprimerEtudiant(); break;
            case 4: rechercherEtudiant(); break;
            case 5: afficherEtudiants(); break;
        }
    }while(choix!=0);
}

void menuAbonnements(){
    int choix;
    do{
        printf("Gestion des abonnements \n");
        printf("1) Afficher nombre d'etudiants par type\n0) Retour\n");
        printf("Choix: ");
        scanf("%d",&choix);
        int c; while((c=getchar()) != '\n' && c != EOF);

        switch(choix){
            case 1:
                {
                    if(n==0){ printf("Aucun etudiant.\n"); break; }
                    char typeRecherche[50];
                    printf("Donner le type d'abonnement: ");
                    fgets(typeRecherche,sizeof(typeRecherche),stdin);
                    enlever_saut_ligne(typeRecherche);

                    int i, compteur=0;
                    for(i=0;i<n;i++){
                        if(strcmp(tabEt[i].ab.type,typeRecherche)==0)
                            compteur++;
                    }

                    printf("Nombre d'etudiants avec l'abonnement '%s': %d\n", typeRecherche, compteur);
                }
                break;
            case 0: break;
            default: printf("Erreur !\n");
        }
    }while(choix!=0);
}

void afficherPaiements(){
    if(n==0){ printf("Aucun paiement.\n"); return; }
    int i;
    for(i=0;i<n;i++)
        printf("Paiement %d: CIN=%d, %.2f DT, Date=%d/%d/%d, Etudiant: %s %s\n",
               i+1, tabEt[i].pay.CIN_etudiant, tabEt[i].pay.montant,
               tabEt[i].pay.date_paiement.jour, tabEt[i].pay.date_paiement.mois, tabEt[i].pay.date_paiement.annee,
               tabEt[i].nom, tabEt[i].prenom);
}

void menuPaiements(){
    int choix;
    do{
        printf("Gestion des paiements \n) Afficher\n0) Retour\nChoix: ");
        scanf("%d",&choix); getchar();
        switch(choix){
            case 1: afficherPaiements(); break;
        }
    }while(choix!=0);
}


void menuPrincipal(){
    int choix;
    do{
        printf("CENTRE DE FORMATION  'FROM ACCESS ' \n");
        printf("1) Gestion des etudiants\n2) Gestion des abonnements\n3) Gestion des paiements\n0) Quitter\nChoix: ");
        scanf("%d",&choix); getchar();
        switch(choix){
            case 1: menuEtudiants(); break;
            case 2: menuAbonnements(); break;
            case 3: menuPaiements(); break;
            case 0: printf("Bye !\n"); break;
            default: printf("Erreur !\n");
        }
    }while(choix!=0);
}

int main(){ menuPrincipal(); return 0; }
