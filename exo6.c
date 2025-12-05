#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Produit
{
    char nom[50];
    int id;
    int quantite;
    int est_occupe;
} Produit;
Produit table[13];
int hachage1(int id) { 
return id %13;
} 
int hachage2(int id) { 
return 7 - (id % 7);  // 7 < TAILLE et premier avec TAILLE 
} 
void initialiser_table() {
    for (int i = 0; i < 13; i++) {
        table[i].est_occupe = 0; // Marquer toutes les entrées comme libres
    }
}
void inserer_produit(int id, char nom[], int quantite) {
    int h1=hachage1(id);
    int h2=hachage2(id);
    int index,i=0;
    while(i<13){
        index=(h1 + i * h2) % 13;
        if(table[index].est_occupe!=1){
            table[index].id=id;
            strcpy(table[index].nom,nom);
            table[index].quantite=quantite;
            table[index].est_occupe=1;
            printf("Produit insere a l'index %d\n",index);
            return;
        }
        i++;
    }
    printf("Table de hachage pleine, impossible d'inserer le produit\n");
}
    int rechercher_produit(int id) {
    int h1 = hachage1(id);
    int h2 = hachage2(id);
    int index, i = 0;
    while (i < 13) {
        index = (h1 + i * h2) % 13;
        if (table[index].est_occupe == 0) {
            // Entrée libre, le produit n'est pas dans la table
            return -1;
        }
        if (table[index].est_occupe == 1 && table[index].id == id) {
            // Produit trouvé
            return index;
            i++;
        }
      return -1; // Produit non trouvé après avoir vérifié toute la table
    }
}
void supprimer_produit(int id){
    int index=rechercher_produit(id);
    if(index==-1){
        printf("Produit non trouve, suppression impossible\n");
        return;
    }
    table[index].est_occupe=-1; // Marquer l'entrée comme supprimée
    printf("Produit supprime a l'index %d\n",index);
}
void afficher_stock(){
    printf("=== Stock des Produits ===\n");
    for(int i=0;i<13;i++){
        if(table[i].est_occupe==1){
            printf("Index %d: ID=%d, Nom=%s, Quantite=%d\n",i,table[i].id,table[i].nom,table[i].quantite);
        }
        else if(table[i].est_occupe==-1){
            printf("Index %d: [Supprime]\n",i);
        }
        else{
            printf("Index %d: [Libre]\n",i);
        }
    }

}
void menu(){
    int choix,id,quantite;
    char nom[50];
    do{
        printf("\n=== Gestion de Stock ===\n");
        printf("1. Inserer un produit\n");
        printf("2. Rechercher un produit\n");
        printf("3. Supprimer un produit\n");
        printf("4. Afficher le stock\n");
        printf("5. Quitter\n");
        printf("Choix: ");
        scanf("%d",&choix);
        switch(choix){
            case 1:
                printf("Entrez l'ID du produit: ");
                scanf("%d",&id);
                printf("Entrez le nom du produit: ");
                scanf("%s",nom);
                printf("Entrez la quantite du produit: ");
                scanf("%d",&quantite);
                inserer_produit(id,nom,quantite);
                break;
            case 2:
                printf("Entrez l'ID du produit a rechercher: ");
                scanf("%d",&id);
                int index=rechercher_produit(id);
                if(index!=-1){
                    printf("Produit trouve a l'index %d: Nom=%s, Quantite=%d\n",index,table[index].nom,table[index].quantite);
                } else{
                    printf("Produit non trouve\n");
                }
                break;
            case 3:
                printf("Entrez l'ID du produit a supprimer: ");
                scanf("%d",&id);
                supprimer_produit(id);
                break;
            case 4:
                afficher_stock();
                break;
            case 5:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide, veuillez reessayer.\n");
        }
}while(choix!=5);
}
int main(){
    initialiser_table();
    menu();
    return 0;
}