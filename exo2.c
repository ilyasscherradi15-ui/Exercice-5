#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct Produit{
    char nom[50];
   int prix;
  int quantite;
  struct Produit* suivant;
  struct Produit* precedent;
}Produit;
Produit * creer_produit(){
    Produit* p = (Produit*) malloc (sizeof(Produit));
    p->nom[0]='\0';
    p->prix = 0;
    p->quantite = 0;
    p->suivant = NULL;
    p->precedent = NULL;
    return p;
   }
   typedef struct ListeRepere{
    Produit* tete;
    Produit* queue; 
    int account;
}Liste;
Liste* creer_liste(){
    Liste* l = (Liste*) malloc (sizeof(Liste));
    l->tete = NULL;
    l->queue = NULL;
    l->account = 0;
    return l;
   }
   //fct pour saisir un produit
   Produit*saisir_produit(){
    Produit* p= creer_produit();
    printf("Entrer le nom du produit: ");
    scanf("%s",p->nom);
    printf("Entrer le prix du produit: ");
    scanf("%d",&p->prix);
    printf("Entrer la quantite du produit: ");
    scanf("%d",&p->quantite);
    return p;
   }
   void  ajouter_produit_liste_fin(Liste* l){
    Produit* p=saisir_produit();
    if(l==NULL||p==NULL){
        exit(EXIT_FAILURE);
    }
    if(l->tete==NULL){
        l->tete=p;
        l->queue=p;
    } else{
        p->precedent=l->queue;
        l->queue->suivant=p;
        l->queue=p;
        
    }
     l->account++;
}
void  ajouter_produit_liste_debut (Liste* l){
    Produit* p= saisir_produit();
    if(l==NULL||p==NULL){
        exit(EXIT_FAILURE);
    }
    if(l->tete==NULL){
        l->tete=p;
        l->queue=p;
    } else{
        p->suivant=l->tete;
        l->tete->precedent=p;
        l->tete=p;
    }
    l->account++;
   }
    int ajouter_produit_liste_milieu(Liste* l){
    if (l == NULL) {
        printf("Liste invalide\n");
        return 0;
    }
    if(l->account == 0){
        printf("Liste vide - ajout au debut\n");
        // Appeler ajouter_produit_liste_debut(l) ou ajouter_produit_liste_fin(l)
         ajouter_produit_liste_debut(l); // À adapter selon ta fonction
      return 1;
    }
    else if(l->account == 1){
        printf("Un seul element - ajout a la fin\n");
        ajouter_produit_liste_fin(l);
       return 1;
    }
    
    // Calcul du milieu correct
    int milieu = l->account / 2;
    Produit* courant = l->tete;
    
    // Aller à la position juste avant l'insertion
    for (int i = 0; i < milieu - 1; i++){
        courant = courant->suivant;
    }
    
    // Créer le nouveau produit
    Produit* temp = saisir_produit();
    if (temp == NULL) {
        printf("Erreur creation produit\n");
        return 0;
    }
    
    // Insertion correcte
    temp->suivant = courant->suivant;
    temp->precedent = courant;
    
    if (courant->suivant != NULL) {
        courant->suivant->precedent = temp;
    }
    courant->suivant = temp;
    // Mettre à jour la queue si on insère à la fin
    if (temp->suivant == NULL) {
        l->queue = temp;
    }
    l->account++;
    printf("Element ajoute avec succes au milieu\n");
    return 1;
}
void afficher_liste_produits_direct (Liste* l){
    if(l==NULL){
        printf("La liste est vide\n");
        return;
    }
    Produit* temp=l->tete;
    while(temp!=NULL){
        printf("Nom: %s, Prix: %d, Quantite: %d\n", temp->nom, temp->prix, temp->quantite);
        temp=temp->suivant;
    }
   }

void afficher_liste_produits_inverse (Liste* l){
    if(l==NULL){
        printf("La liste est vide\n");
        return;
    }
    Produit* temp=l->queue;
    while(temp!=NULL){
        printf("Nom: %s, Prix: %d, Quantite: %d\n", temp->nom, temp->prix, temp->quantite);
        temp=temp->precedent;
    }
   }
   void  enregistrer_liste_produits (Liste* l){
    FILE* file = fopen ("produits.txt", "w");
    if(file==NULL){
        perror("Erreur d'ouverture de fichier\n");
        exit(EXIT_FAILURE);
    }
    Produit* temp=l->tete;
    while(temp!=NULL){
        fprintf(file, "%s %d %d\n", temp->nom, temp->prix, temp->quantite);
        temp=temp->suivant;
    }
    fclose(file);
   }
    void  enregistrer_liste_produit(Liste* l){
    FILE* file = fopen ("produits.txt", "r");
    if(file==NULL){
        perror("Erreur d'ouverture de fichier\n");
        exit(EXIT_FAILURE);
    }
    if(l == NULL) {
        printf("Erreur: Liste non initialisée\n");
        return;
    }
    int compteur = 0;
    char nom[50];
    int prix, quantite;
    
   while( fscanf(file, "%s %d %d\n", nom, &prix, &quantite)==3){
        Produit* nouveau= creer_produit();
        if(nouveau == NULL) {
            printf("Erreur de création de produit\n");
            continue; // ou gérer l'erreur comme approprié
        }
        strcpy(nouveau->nom, nom);
        nouveau->prix = prix;
        nouveau->quantite = quantite;
        if(l->tete == NULL){
            l->tete = nouveau;
            l->queue = nouveau;
        }else{
            l->queue->suivant = nouveau;
            nouveau->precedent = l->queue;
            l->queue = nouveau;
            
        }
        l->account++;
         compteur++;
        printf("Produit lu: %s (%d MAD, %d unités)\n", nom, prix, quantite);
        }
 
        fclose(file);
        if(compteur == 0) {
        printf("Aucun produit trouvé dans le fichier\n");
    } else {
        printf("%d produits chargés depuis le fichier\n", compteur);
    }

    }
    void trier_liste_produits_selection(Liste* l) {
    if(l == NULL || l->tete == NULL) {
        printf("La liste est vide ou non initialisée\n");
        return;
    }
    
    Produit* courant = l->tete;
    
    while(courant != NULL) {
        // Trouver le produit avec le prix minimum dans la sous-liste non triée
        Produit* min = courant;
        Produit* temp = courant->suivant;
        
        while(temp != NULL) {
            if(temp->prix < min->prix) {
                min = temp;
            }
            temp = temp->suivant;
        }
        
        // Échanger les données entre courant et min
        if(min != courant) {
            // Échanger les données (plus simple que d'échanger les pointeurs)
            char nom_temp[50];
            int prix_temp, quantite_temp;
            
            // Sauvegarder les données de courant
            strcpy(nom_temp, courant->nom);
            prix_temp = courant->prix;
            quantite_temp = courant->quantite;
            
            // Copier les données de min vers courant
            strcpy(courant->nom, min->nom);
            courant->prix = min->prix;
            courant->quantite = min->quantite;
            
            // Copier les données sauvegardées vers min
            strcpy(min->nom, nom_temp);
            min->prix = prix_temp;
            min->quantite = quantite_temp;
        }
        
        courant = courant->suivant;
    }
    
    printf("Liste triée par sélection avec succès\n");
}

Produit*  trouver_produit_cher(Liste* l){
    if(l==NULL || l->tete==NULL){
        printf("la liste est vide ou nom initialisee\n");
        return NULL;
    }
     Produit* courant=l->tete;
    Produit* produit_cher=courant;
    int prix_max=courant->prix;
    while(courant!=NULL){
        if(courant->prix > prix_max){
            prix_max=courant->prix;
            produit_cher=courant;
        }
        courant=courant->suivant;
    }
    return produit_cher;
}

    

int main() {
    Liste* maListe = creer_liste();
    int choix;
    
    printf("=== GESTION PRODUITS ===\n");
    
    do {
        printf("\n1. Ajouter debut\n2. Ajouter fin\n3. Ajouter milieu\n");
        printf("4. Afficher\n5. Trier\n6. Produit cher\n7. Sauvegarder\n8. Charger\n0. Quitter\n");
        printf("Choix: ");
        scanf("%d", &choix);
        
        switch(choix) {
            case 1: ajouter_produit_liste_debut(maListe); break;
            case 2: ajouter_produit_liste_fin(maListe); break;
            case 3: ajouter_produit_liste_milieu(maListe); break;
            case 4: afficher_liste_produits_direct(maListe); break;
            case 5: trier_liste_produits_selection(maListe); break;
            case 6: {
                Produit* cher = trouver_produit_cher(maListe);
                if(cher) printf("Plus cher: %s (%d MAD)\n", cher->nom, cher->prix);
                break;
            }
            case 7: enregistrer_liste_produits(maListe); break;
            case 8: enregistrer_liste_produit(maListe); break;
            case 0: printf("Au revoir!\n"); break;
            default: printf("Choix invalide!\n");
        }
    } while(choix != 0);
    
    // Libération mémoire
    if(maListe) {
        Produit* courant = maListe->tete;
        while(courant) {
            Produit* temp = courant;
            courant = courant->suivant;
            free(temp);
        }
        free(maListe);
    }
    
    return 0;
}