#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void afficherPath() {
    char cwd[1000];
    getcwd(cwd, sizeof(cwd));
    printf("Dossier actuel: %s\n", cwd);
}

// ================== DATE ==================
typedef struct Date {
    int jour;
    int mois;
    int annee;
} Date;

// ================== ETUDIANT ==================
typedef struct Etudiant {
    int id;
    char nom[50];
    char prenom[50];
    Date dateNaissance;
    struct Etudiant* suivant;
} Etudiant;

// ================== FORMATION ==================
typedef struct Formation {
    int id;
    char titre[50];
    float prix;
    int duree;
    struct Formation* suivant;
} Formation;

// ================== INSCRIPTION ==================
typedef struct Inscription {
    int idEtud;
    int idForm;
    float prix;
    struct Inscription* suivant;
} Inscription;

// ================== PAIEMENT ==================
typedef struct Paiement {
    int idEtud;
    float montant;
    struct Paiement* suivant;
} Paiement;

// ================== LISTES ==================
Etudiant *lEtud = NULL;
Formation *lForm = NULL;
Inscription *lIns = NULL;
Paiement *lPay = NULL;

// ================== INPUT SAFE ==================
void readString(char *s, int size) {
    fgets(s, size, stdin);
    s[strcspn(s, "\n")] = 0;
}

void initFormations() {

    Formation* f1 = malloc(sizeof(Formation));
    f1->id = 1;
    strcpy(f1->titre, "Language C");
    f1->prix = 500;
    f1->duree = 6;

    Formation* f2 = malloc(sizeof(Formation));
    f2->id = 2;
    strcpy(f2->titre, "Language Python");
    f2->prix = 250;
    f2->duree = 3;

    Formation* f3 = malloc(sizeof(Formation));
    f3->id = 3;
    strcpy(f3->titre, "Francais");
    f3->prix = 300;
    f3->duree = 4;

    Formation* f4 = malloc(sizeof(Formation));
    f4->id = 4;
    strcpy(f4->titre, "Anglais");
    f4->prix = 600;
    f4->duree = 12;

    Formation* f5 = malloc(sizeof(Formation));
    f5->id = 5;
    strcpy(f5->titre, "Italien");
    f5->prix = 360;
    f5->duree = 3;

    Formation* f6 = malloc(sizeof(Formation));
    f6->id = 6;
    strcpy(f6->titre, "Marketing");
    f6->prix = 600;
    f6->duree = 6;

    // الربط (linked list)
    f6->suivant = f5;
    f5->suivant = f4;
    f4->suivant = f3;
    f3->suivant = f2;
    f2->suivant = f1;
    f1->suivant = NULL;

    lForm = f6;
}

// ================== FORMATION ==================
Formation* chercherForm(int id) {
    Formation* t = lForm;
    while(t) {
        if(t->id == id) return t;
        t = t->suivant;
    }
    return NULL;
}

void afficherForm() {
    Formation* t = lForm;

    printf("\n===== FORMATIONS =====\n");

    while(t) {
        printf("%d | %s | %.2f DT | %d mois\n",
            t->id, t->titre, t->prix, t->duree);
        t = t->suivant;
    }
}

// ================== ETUDIANT ==================
void ajouterEtud() {
    Etudiant* e = malloc(sizeof(Etudiant));

    printf("ID: "); scanf("%d", &e->id);

    getchar();
    printf("Nom: ");
    readString(e->nom, 50);

    printf("Prenom: ");
    readString(e->prenom, 50);

    printf("Date (jj mm aaaa): ");
    scanf("%d %d %d",
        &e->dateNaissance.jour,
        &e->dateNaissance.mois,
        &e->dateNaissance.annee);

    e->suivant = lEtud;
    lEtud = e;
}

void afficherEtud() {
    Etudiant* t = lEtud;

    printf("\n===== ETUDIANTS =====\n");

    while(t) {
        printf("%d | %s %s | %02d/%02d/%04d\n",
            t->id, t->nom, t->prenom,
            t->dateNaissance.jour,
            t->dateNaissance.mois,
            t->dateNaissance.annee);
        t = t->suivant;
    }
}

void modifierEtud() {
    int id;
    printf("ID Etudiant a modifier: ");
    scanf("%d", &id);

    Etudiant* t = lEtud;

    while(t && t->id != id)
        t = t->suivant;

    if(!t) {
        printf("Etudiant introuvable!\n");
        return;
    }

    getchar();
    printf("Nouveau nom: ");
    readString(t->nom, 50);

    printf("Nouveau prenom: ");
    readString(t->prenom, 50);

    printf("Date (jj mm aaaa): ");
    scanf("%d %d %d",
        &t->dateNaissance.jour,
        &t->dateNaissance.mois,
        &t->dateNaissance.annee);

    printf("Modification terminee!\n");
}

void supprimerEtud() {
    int id;
    printf("ID Etudiant a supprimer: ");
    scanf("%d", &id);

    Etudiant *t = lEtud, *prev = NULL;

    while(t && t->id != id) {
        prev = t;
        t = t->suivant;
    }

    if(!t) {
        printf("Etudiant introuvable!\n");
        return;
    }

    if(!prev) lEtud = t->suivant;
    else prev->suivant = t->suivant;

    free(t);

    printf("Etudiant supprime!\n");
}

// ================== INSCRIPTION ==================
void ajouterIns() {
    Inscription* i = malloc(sizeof(Inscription));

    printf("ID Etudiant: "); scanf("%d", &i->idEtud);
    printf("ID Formation: "); scanf("%d", &i->idForm);

    Formation* f = chercherForm(i->idForm);

    i->prix = (f) ? f->prix : 0;

    i->suivant = lIns;
    lIns = i;
}

void afficherIns() {
    Inscription* t = lIns;

    printf("\n===== INSCRIPTIONS =====\n");

    while(t) {
        Etudiant* e = lEtud;
        while(e && e->id != t->idEtud)
            e = e->suivant;

        Formation* f = lForm;
        while(f && f->id != t->idForm)
            f = f->suivant;

        char nom[100] = "Inconnu";
        char form[100] = "Inconnu";

        if(e) sprintf(nom, "%s %s", e->nom, e->prenom);
        if(f) strcpy(form, f->titre);

        printf("%-15s | %-12s | %.2f DT\n",
            nom, form, t->prix);

        t = t->suivant;
    }
}

// ================== PAIEMENT ==================
void verifierPaiement(int idEtud, float montant) {
    Inscription* t = lIns;

    while(t) {
        if(t->idEtud == idEtud) {
            float reste = t->prix - montant;

            printf("\n===== RESULTAT =====\n");
            printf("Total: %.2f | Paye: %.2f\n", t->prix, montant);

            if(reste > 0) printf("Reste: %.2f\n", reste);
            else if(reste == 0) printf("Paiement complet\n");
            else printf("Trop paye: %.2f\n", -reste);

            return;
        }
        t = t->suivant;
    }
}

void ajouterPay() {
    int id; float m;

    printf("ID Etudiant: "); scanf("%d", &id);
    printf("Montant: "); scanf("%f", &m);

    verifierPaiement(id, m);

    Paiement* p = malloc(sizeof(Paiement));
    p->idEtud = id;
    p->montant = m;
    p->suivant = lPay;
    lPay = p;
}

// ================== MENU ==================
void menu() {
    printf("\CENTRE DE FORMATION: FROM ACCESS \n");
    printf("1 Etudiants\n");
    printf("2 Formations\n");
    printf("3 Inscriptions\n");
    printf("4 Paiements\n");
    printf("0 Quitter\n");
    printf("Choix: ");
}

// ================== FICHIERS ==================
void sauvegarderTout() {
    FILE *f;

    f = fopen("etudiants.txt", "w");
    Etudiant *e = lEtud;
    while(e) {
        fprintf(f,"%d %s %s %d %d %d\n",
            e->id,e->nom,e->prenom,
            e->dateNaissance.jour,
            e->dateNaissance.mois,
            e->dateNaissance.annee);
        e = e->suivant;
    }
    fclose(f);

    f = fopen("formations.txt", "w");
    Formation *f1 = lForm;
    while(f1) {
        fprintf(f,"%d %s %.2f %d\n",
            f1->id,f1->titre,f1->prix,f1->duree);
        f1 = f1->suivant;
    }
    fclose(f);

    f = fopen("inscriptions.txt", "w");
    Inscription *i = lIns;
    while(i) {
        fprintf(f,"%d %d %.2f\n",
            i->idEtud,i->idForm,i->prix);
        i = i->suivant;
    }
    fclose(f);

    f = fopen("paiements.txt", "w");
    Paiement *p = lPay;
    while(p) {
        fprintf(f,"%d %.2f\n",
            p->idEtud,p->montant);
        p = p->suivant;
    }
    fclose(f);
}

// ================== MAIN ==================
int main() {

    initFormations();

    int ch, sous;

    do {
        menu();
        scanf("%d", &ch);

        switch(ch) {

            case 1:
                printf("1-Ajouter 2-Afficher 3-Modifier 4-Supprimer: ");
                scanf("%d", &sous);

                if(sous==1) ajouterEtud();
                else if(sous==2) afficherEtud();
                else if(sous==3) modifierEtud();
                else if(sous==4) supprimerEtud();
                break;

            case 2:
                afficherForm();
                break;

            case 3:
                printf("1-Ajouter 2-Afficher: ");
                scanf("%d", &sous);

                if(sous==1) ajouterIns();
                else if(sous==2) afficherIns();
                break;

            case 4:
                ajouterPay();
                break;

            case 0:
                sauvegarderTout();
                printf("Au revoir!\n");
                break;
        }

    } while(ch != 0);
    afficherPath();

    return 0;
}
