#include <stdio.h>
#include <stdlib.h>

// Définition de la structure d'un nœud de la liste doublement chaînée circulaire
typedef struct noeud{
    int data;               // Donnée stockée dans le nœud
    struct noeud* suivant;  // Pointeur vers le nœud suivant
    struct noeud* precedent;// Pointeur vers le nœud précédent
} noeud;

// Définition de la structure de la liste
typedef struct liste{
    noeud *head;    // Pointeur vers le premier nœud
    noeud *tail;    // Pointeur vers le dernier nœud
    int taille;     // Nombre d'éléments dans la liste
} liste;

// Fonction pour créer une liste vide
liste* creer_liste(){
    liste* l = (liste*) malloc (sizeof(liste));
    l->head = NULL;     // Initialise la tête à NULL
    l->tail = NULL;     // Initialise la queue à NULL
    l->taille = 0;      // Initialise la taille à 0
    return l;
}

// Fonction pour créer un nœud vide
noeud* creer_noeud(){
    noeud* n = (noeud*) malloc (sizeof(noeud));
    n->data = 0;        // Initialise la donnée à 0
    n->suivant = NULL;  // Initialise le pointeur suivant à NULL
    n->precedent = NULL;// Initialise le pointeur précédent à NULL
    return n;
}


// Fonction pour insérer un élément au début de la liste
void insertDebut(liste* l, int val){
    noeud *n = creer_noeud();
    if(l == NULL || n == NULL){
        exit(EXIT_FAILURE); // Arrêt du programme en cas d'erreur
    }
    n->data = val;
    
    // Cas où la liste est vide
    if (l->head == NULL) {
        l->head = n;
        l->tail = n;
        n->suivant = n;     // Le nœud pointe vers lui-même
        n->precedent = n;   // Le nœud pointe vers lui-même
    }
    // Cas où la liste n'est pas vide
    else {
        n->suivant = l->head;
        l->head->precedent = n;
        l->tail->suivant = n;   // La queue pointe vers le nouveau nœud
        n->precedent = l->tail; // Le nouveau nœud pointe vers la queue
        l->head = n;            // Mise à jour de la tête
    }
    l->taille++; // Incrémentation de la taille
}

// Fonction pour insérer un élément à la fin de la liste
void insertFin(liste * l, int val) {
    noeud *n = creer_noeud();
    if (l == NULL || n == NULL) {
        exit(EXIT_FAILURE);
    }
    n->data = val;
    
    // Cas où la liste est vide
    if (l->head == NULL) {
        l->head = n;  
        l->tail = n;
        n->suivant = n;
        n->precedent = n;
    }
    // Cas où la liste n'est pas vide
    else {
        l->tail->suivant = n;
        n->precedent = l->tail;
        n->suivant = l->head;   // Le nouveau nœud pointe vers la tête
        l->head->precedent = n; // La tête pointe vers le nouveau nœud
        l->tail = n;            // Mise à jour de la queue
    }
    l->taille++; // Incrémentation de la taille
}

// Fonction pour insérer un élément à une position spécifique
void insertPos(liste* l, int val, int pos){
    // Vérification de la validité de la position
    if (pos < 0 || pos > l->taille) {
        printf("Position invalide\n");
        return;
    }
    if(l == NULL){
        printf("Liste invalide\n");
        return;
    }
    
    // Insertion au début si position = 0
    if(pos == 0){
        insertDebut(l, val);
        return;
    }
    // Insertion à la fin si position = taille
    if(pos == l->taille){
        insertFin(l, val);
        return;
    }
    
    noeud* n = creer_noeud();
    if(n == NULL){
        exit(EXIT_FAILURE);
    }
    n->data = val;
    
    // Recherche de la position d'insertion
    noeud* temp = l->head;
    for(int i = 0; i < pos - 1; i++){
        temp = temp->suivant;
    }
    
    // Insertion du nœud
    n->suivant = temp->suivant;
    n->precedent = temp;
    temp->suivant->precedent = n;
    temp->suivant = n;
    
    l->taille++; // Incrémentation de la taille
}

// Fonction pour supprimer le premier élément
void deleteDebut(liste* l){
    if (l == NULL || l->head == NULL) {
        printf("Liste vide ou invalide\n");
        return;
    }
    
    noeud* temp = l->head;
    
    // Cas où il n'y a qu'un seul élément
    if (l->head == l->tail) {
        l->head = NULL;
        l->tail = NULL;
    }
    // Cas où il y a plusieurs éléments
    else {
        l->head = l->head->suivant;
        l->head->precedent = l->tail;
        l->tail->suivant = l->head;
    }
    
    free(temp); // Libération de la mémoire
    l->taille--; // Décrémentation de la taille
}

// Fonction pour supprimer le dernier élément
void deleteFin(liste* l){
    if (l == NULL || l->head == NULL) {
        printf("Liste vide ou invalide\n");
        return;
    }
    
    noeud* temp = l->tail;
    
    // Cas où il n'y a qu'un seul élément
    if (l->head == l->tail) {
        l->head = NULL;
        l->tail = NULL;
    }
    // Cas où il y a plusieurs éléments
    else {
        l->tail = l->tail->precedent;
        l->tail->suivant = l->head;
        l->head->precedent = l->tail;
    }
    
    free(temp); // Libération de la mémoire
    l->taille--; // Décrémentation de la taille
}

// Fonction pour supprimer un élément à une position spécifique
void deletePos(liste* l, int pos){
    if (l == NULL || l->head == NULL) {
        printf("Liste vide ou invalide\n");
        return;
    }
    // Vérification de la validité de la position
    if (pos < 0 || pos >= l->taille) {
        printf("Position invalide\n");
        return;
    }
    
    // Suppression au début si position = 0
    if(pos == 0){
        deleteDebut(l);
        return;
    }
    // Suppression à la fin si position = taille-1
    if(pos == l->taille - 1){
        deleteFin(l);
        return;
    }
    
    // Recherche du nœud à supprimer
    noeud* temp = l->head;
    for(int i = 0; i < pos; i++){
        temp = temp->suivant;
    }
    
    // Réorganisation des pointeurs
    temp->precedent->suivant = temp->suivant;
    temp->suivant->precedent = temp->precedent;
    
    free(temp); // Libération de la mémoire
    l->taille--; // Décrémentation de la taille
}

// Fonction pour afficher tous les éléments de la liste
void afficherListe(liste* l){
    if(l == NULL || l->head == NULL){
        printf("Liste vide ou invalide\n");
        return;
    }
    
    noeud* temp = l->head;
    // Parcours de tous les éléments
    for(int i = 0; i < l->taille; i++){
        printf("%d ", temp->data);
        temp = temp->suivant;
    }
    printf("\n");
}

// Fonction pour vider complètement la liste
void ViderListe(liste* Li) {
    if (Li == NULL || Li->head == NULL) {
        return;
    }
    
    noeud* ptr = Li->head;
    noeud* succ = NULL;
    
    // Parcours et libération de tous les nœuds
    do {
        succ = ptr->suivant;
        free(ptr);
        ptr = succ;
    } while (ptr != Li->head && succ != Li->head);
    
    // Réinitialisation de la liste
    Li->head = NULL;
    Li->tail = NULL;
    Li->taille = 0;
}

// Fonction pour afficher le menu interactif
void afficherMenu() {
    printf("\n=== MENU LISTE DOUBLEMENT CHAINEE CIRCULAIRE ===\n");
    printf("1. Ajouter au debut\n");
    printf("2. Ajouter a la fin\n");
    printf("3. Ajouter a une position\n");
    printf("4. Supprimer au debut\n");
    printf("5. Supprimer a la fin\n");
    printf("6. Supprimer a une position\n");
    printf("7. Afficher la liste\n");
    printf("8. Vider la liste\n");
    printf("9. Quitter\n");
    printf("Choix : ");
}

// Fonction principale avec menu interactif
void main() {
    liste* maListe = creer_liste();
    int choix, valeur, position;
    
    printf("Creation d'une liste doublement chainee circulaire vide.\n");
    
    do {
        afficherMenu();
        scanf("%d", &choix);
        
        switch(choix) {
            case 1:
                printf("Entrez la valeur a ajouter au debut : ");
                scanf("%d", &valeur);
                insertDebut(maListe, valeur);
                break;
                
            case 2:
                printf("Entrez la valeur a ajouter a la fin : ");
                scanf("%d", &valeur);
                insertFin(maListe, valeur);
                break;
                
            case 3:
                printf("Entrez la valeur a ajouter : ");
                scanf("%d", &valeur);
                printf("Entrez la position : ");
                scanf("%d", &position);
                insertPos(maListe, valeur, position);
                break;
                
            case 4:
                deleteDebut(maListe);
                break;
                
            case 5:
                deleteFin(maListe);
                break;
                
            case 6:
                printf("Entrez la position a supprimer : ");
                scanf("%d", &position);
                deletePos(maListe, position);
                break;
                
            case 7:
                afficherListe(maListe);
                break;
                
            case 8:
                ViderListe(maListe);
                break;
                
            case 9:
                printf("Au revoir!\n");
                break;
                
            default:
                printf("Choix invalide! Veuillez choisir entre 1 et 9.\n");
                break;
        }
        
        // Pause pour voir les résultats
        if(choix != 9) {
            printf("\nAppuyez sur Entree pour continuer...");
            getchar(); // Pour consommer le \n restant
            getchar(); // Pour attendre l'appui sur Entree
        }
        
    } while(choix != 9);
    
    // Libération finale de la mémoire
    ViderListe(maListe);
    free(maListe);
}