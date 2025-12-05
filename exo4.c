#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Client { 
int id; 
char nom[30]; 
char oper[50]; 
} Client;
typedef struct ElementRepere{
    Client c;
    struct ElementRepere * suivant;
}Element;
 typedef struct ElementHistorique {
    char hist[100];
    struct ElementHistorique* suivant;
} Historique;

#define MAX 50 
typedef struct {
   Historique*tete;
   int taille;
} PileHistorique;

typedef struct {
   Element* tete;
   Element* queue;
   int taille;
} FileClients;

FileClients * initialiserFile(){
    FileClients*f=(FileClients*)malloc(sizeof(FileClients));
    if(f==NULL){
        printf("l'allocation est impossible");
        exit(1);
    }
    f->tete=NULL;
    f->queue=NULL;
    f->taille=0;  
    return f;
}
  int estVideFile(FileClients *f){
    return f->taille==0;
 }
 Client saisirClient(){
    Client c;
    printf("Entrer l'ID du client: ");
    scanf("%d",&c.id);
    printf("Entrer le nom du client: ");
    scanf("%s",c.nom);
    printf("Entrer l'operation a effectuer: ");
    scanf("%s",c.oper);
    return c;
 }
 Element*creerElementClient(Client c){
    Element*E=(Element*)malloc(sizeof(Element));
    if(E==NULL){
        printf("l'allocation est impossible");
        exit(1);
    }
    E->c=c;
    E->suivant=NULL;
    return E;
 }
 void enfiler(FileClients *f,Client c){
    Element*E=creerElementClient(c);
    if(estVideFile(f)){
        f->tete=E;
        f->queue=E;
    }else{
        f->queue->suivant=E;
        f->queue=E;
    }
    f->taille++;
 }
Client defiler(FileClients *f){
    if(estVideFile(f)){
        printf("file vide");
        return (Client){-1,"",""};
    }
    Element*E=f->tete;
    Client c=E->c;
    f->tete=f->tete->suivant;
    if(f->tete==NULL){
        f->queue=NULL;
    }
    free(E);
    f->taille--;
    return c;
}
void afficherFile(FileClients *f){
    if(estVideFile(f)){
        printf("file vide");
        return;
    }
    Element*E=f->tete;
    while(E!=NULL){
        printf("ID: %d, Nom: %s, Oper: %s\n",E->c.id,E->c.nom,E->c.oper);
        E=E->suivant;
    }
    return;
}
PileHistorique*initialiserPile(){
PileHistorique*p=(PileHistorique*)malloc(sizeof(PileHistorique));
if(p==NULL){
    printf("l'allocation est impossible");
    exit(1);
}
p->tete=NULL;
p->taille=0;
return p;
}
Historique*creerElementHistorique(const char *hist){
    Historique*H=(Historique*)malloc(sizeof(Historique));
    if(H==NULL){
        printf("l'allocation est impossible");
        exit(1);
    }
    strcpy (H->hist,hist);
    H->suivant=NULL;
    return H;
}   
void empiler(PileHistorique*p,const char *hist){
    Historique*H=creerElementHistorique(hist);
    H->suivant=p->tete;
    p->tete=H;
    p->taille++;
}
char* depiler(PileHistorique*p){
    if(p->taille==0){
        printf("pile vide");
        return NULL;
    }
    Historique*H=p->tete;
    char* hist=(char*)malloc(MAX*sizeof(char));
    strcpy(hist,H->hist);
    p->tete=p->tete->suivant;
    free(H);
    p->taille--;
    return hist;
}
void afficherPile(PileHistorique*p){
    if(p->taille==0){
        printf("pile vide");
        return;
    }
    Historique*H=p->tete;
    while(H!=NULL){
        printf("Historique: %s\n",H->hist);
        H=H->suivant;
    }
}
void ajouterClient(FileClients *f, PileHistorique *p){
    Client c=saisirClient();
    enfiler(f,c);
    printf("Ajout du client à la file d'attente ID: %d, Nom: %s, Oper: %s a la file.",c.id,c.nom,c.oper);
    printf("✓ Client ajouté avec succès:\n");
    char hist[MAX];
    sprintf(hist,"Ajout du client ID: %d, Nom: %s, Oper: %s a la file.",c.id,c.nom,c.oper);
    empiler(p,hist);
}
void traiterClient(FileClients *f, PileHistorique *p){
    if(estVideFile(f)){
        printf("file vide, aucun client a traiter\n");
        return;
    }
    Client c=defiler(f);
    printf("Traitement du client ID: %d, Nom: %s, Oper: %s\n",c.id,c.nom,c.oper);
    char hist[MAX];
    sprintf(hist,"Client ID: %d, Nom: %s, Oper: %s traite.",c.id,c.nom,c.oper);
    empiler(p,hist);
    printf("✓ Client traité avec succès:\n");
}
void annulerDerniereOperation(FileClients *f, PileHistorique *p){
    if(p->taille==0){
        printf("Aucune operation a annuler\n");
        return;
    }
    char* hist=depiler(p);
    if(hist!=NULL){
    printf("Annulation de l'operation: %s\n",hist);
    free(hist);
    }
}
void afficherMenu() {
    printf("\n=== CENTRE DE SERVICE CLIENT ===\n");
    printf("1. Ajouter un client à la file d'attente\n");
    printf("2. Traiter le prochain client\n");
    printf("3. Annuler la dernière opération\n");
    printf("4. Afficher les clients en attente\n");
    printf("5. Afficher l'historique des opérations\n");
    printf("0. Quitter le programme\n");
    printf("Choix: ");
}
void libererFile(FileClients *f){
    while(!estVideFile(f)){
        defiler(f);
    }
    free(f);
}
void libererPile(PileHistorique *p){
    while(p->taille>0){
        char *hist=depiler(p);
        if(hist!=NULL){
            free(hist);
        }
    }
    free(p);
}


int main(){
 FileClients* file = initialiserFile();
   PileHistorique* historique = initialiserPile();
    int choix;
    
    printf("Simulation Centre de Service Client\n");
    
    do {
        afficherMenu();
        scanf("%d", &choix);
        
        switch(choix) {
            case 1:
                ajouterClient(file, historique);
                break;
                
            case 2:
                traiterClient(file, historique);
                break;
                
            case 3:
                annulerDerniereOperation(file, historique);
                break;
                
            case 4:
                printf("\n--- Clients en attente ---\n");
                if (estVideFile(file)) {
                    printf("Aucun client en attente\n");
                } else {
                    afficherFile(file);
                }
                break;
                
            case 5:
                printf("\n--- Historique des opérations ---\n");
                 if(historique->taille==0){
                     printf("pile vide");
                } else {
                    afficherPile(historique);
                }
                break;
                
            case 0:
                printf("Au revoir!\n");
                break;
                
            default:
                printf("Choix invalide! Veuillez réessayer.\n");
        }
        
    } while(choix != 0);
    libererFile(file);
    libererPile(historique);
    
    
    
    return 0;
}

