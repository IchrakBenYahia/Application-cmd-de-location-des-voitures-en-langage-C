#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define VOITURES_FILE "voitures.txt"
#define HISTORIQUE_FILE "historique.txt"
#define LOCATAIRES_FILE "locataire.txt"

#define MAX_VOITURES 100
#define MAX_HISTORIQUE 100
#define MAX_LOCATAIRES 100
#define MAX_DATE_SIZE 11

// Structure pour représenter une voiture
typedef struct Voiture {
    int id;
    char marque[50];
    int immatricule;
    char couleur[50];
    char etat; // 'B' pour bon etat et 'M' pour etat moyen
    char status; // 'D' pour disponible, 'R' pour réservée, 'P' pour en panne
    struct Voiture* next; // Pointeur vers la voiture suivante dans la liste
} Voiture;

// Structure pour représenter l'historique de location
typedef struct Historique {
    int voitureId;
    char marqueVoiture[50];
    int locataireId;
    char date[20];
    struct Historique* next; // Pointeur vers l'entrée d'historique suivante
} Historique;

// Structure pour représenter un locataire
typedef struct Locataire {
    int id;
    char nom[50];
    char prenom[50];
    char email[100];
    char dateDebutLocation[20];
    char dateFinLocation[20];
    struct Locataire* next; // Pointeur vers le locataire suivant dans la liste
} Locataire;

// Fonction pour sauvegarder les locataires dans un fichier text
void sauvegarderLocataires(Locataire* head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        Locataire* current = head;
        while (current != NULL) {
            fprintf(file, "%d %s %s %s %s %s\n",
                    current->id, current->nom, current->prenom,
                    current->email, current->dateDebutLocation, current->dateFinLocation);
            current = current->next;
        }
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier %s pour sauvegarder les locataires.\n", filename);
    }
}

// Fonction pour charger les locataires depuis un fichier text
void chargerLocataires(Locataire** head, int *numTenants, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        Locataire* current = NULL;
        while (!feof(file)) {
            Locataire* newTenant = (Locataire*)malloc(sizeof(Locataire));
            if (fscanf(file, "%d %s %s %s %s %s",
                       &newTenant->id, newTenant->nom, newTenant->prenom,
                       newTenant->email, newTenant->dateDebutLocation, newTenant->dateFinLocation) == 6) {
                newTenant->next = current;
                current = newTenant;
                (*numTenants)++;
            } else {
                free(newTenant);
                break;
            }
        }
        *head = current;
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier %s pour charger les locataires.\n", filename);
    }
}

// Fonction pour sauvegarder les voitures dans un fichier texte
void sauvegarderVoitures(Voiture* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file != NULL) {
        Voiture* current = head;
        while (current != NULL) {
            fprintf(file, "%d %s %d %s %c %c\n",
                    current->id, current->marque, current->immatricule,
                    current->couleur, current->etat, current->status);
            current = current->next;
        }
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier %s pour sauvegarder les voitures.\n", filename);
    }
}

// Fonction pour charger les voitures depuis un fichier texte
void chargerVoitures(Voiture** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        Voiture* current = NULL;
        while (!feof(file)) {
            Voiture* newCar = (Voiture*)malloc(sizeof(Voiture));
            if (fscanf(file, "%d %s %d %s %c %c",
                       &newCar->id, newCar->marque, &newCar->immatricule,
                       newCar->couleur, &newCar->etat, &newCar->status) == 6) {
                newCar->next = current;
                current = newCar;
            } else {
                free(newCar);
                break;
            }
        }
        *head = current;
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier %s pour charger les voitures.\n", filename);
    }
}

// Fonction pour sauvegarder l'historique dans un fichier texte
void sauvegarderHistorique(Historique** head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file != NULL) {
        Historique* current = *head;
        while (current != NULL) {
            fprintf(file, "%d %s %d %s\n",
                    current->voitureId, current->marqueVoiture, current->locataireId, current->date);
            current = current->next;
        }
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier %s pour sauvegarder l'historique.\n", filename);
    }
}

// Fonction pour charger l'historique depuis un fichier texte
void chargerHistorique(Historique** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        Historique* current = NULL;
        while (!feof(file)) {
            Historique* newEntry = (Historique*)malloc(sizeof(Historique));
            if (fscanf(file, "%d %s %d %s",
                       &newEntry->voitureId, newEntry->marqueVoiture, &newEntry->locataireId, newEntry->date) == 4) {
                newEntry->next = current;
                current = newEntry;
            } else {
                free(newEntry);
                break;
            }
        }
        *head = current;
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier %s pour charger l'historique.\n", filename);
    }
}

// Fonction pour afficher la liste des locataires
void afficherLocataires(Locataire* head) {
    Locataire* current = head;
    printf("\nListe des locataires :\n");
    while (current != NULL) {
        printf("Locataire %d : %s %s email: %s, location De: %s, A: %s\n", current->id, current->prenom, current->nom, current->email, current->dateDebutLocation, current->dateFinLocation);
        current = current->next;
    }
}

// Fonction pour consulter l'état des voitures disponibles
void consulterEtatVoituresDisponibles(Voiture* head) {
    printf("\nListe des voitures disponibles \n NB:'B' pour bon etat,'M' pour etat moyen, 'P' pour en panne , 'D' pour disponnible et 'R' pour réservé:\n");
    Voiture* current = head;
    while (current != NULL) {
        if (current->status == 'D') {
            printf("L'etat de la voiture %d de la marque %s est : %c\n", current->id, current->marque, current->etat);
        }
        current = current->next;
    }
}

// Fonction pour consulter l'état des voitures reservé
void consulterEtatVoituresReserve(Voiture* head) {
    printf("\nListe des voitures reservées \n NB:'B' pour bon etat,'M' pour etat moyen, 'P' pour en panne , 'D' pour disponnible et 'R' pour réservé:\n");
    Voiture* current = head;
    while (current != NULL) {
        if (current->status == 'R') {
            printf("L'etat de la voiture %d de la marque %s est : %c\n", current->id, current->marque, current->etat);
        }
        current = current->next;
    }
}

// Fonction pour consulter l'état des voitures en panne
void consulterEtatVoituresPanne(Voiture* head) {
    printf("\nListe des voitures en panne \n NB:'B' pour bon etat,'M' pour etat moyen, 'P' pour en panne , 'D' pour disponnible et 'R' pour réservé:\n");
    Voiture* current = head;
    while (current != NULL) {
        if (current->status == 'P') {
            printf("L'etat de la voiture %d de la marque %s est : %c\n", current->id, current->marque, current->etat);
        }
        current = current->next;
    }
}

// Fonction pour obtenir la date actuelle sous forme de chaîne de caractères
void getCurrentDate(char *dateString, size_t maxSize) {
    time_t t = time(NULL);
    if (t != -1) {
        struct tm *tm_info = localtime(&t);
        if (tm_info != NULL) {
            strftime(dateString, maxSize, "%d/%m/%Y", tm_info);
        } else {
            fprintf(stderr, "Erreur lors de la conversion de l'heure locale.\n");
        }
    } else {
        fprintf(stderr, "Erreur lors de l'obtention du temps actuel.\n");
    }
}

// Fonction pour trouver une voiture par ID dans la liste de voitures
Voiture* trouverVoitureParID(Voiture* head, int id) {
    Voiture* current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;  // La voiture est inexistante
}

// Fonction pour trouver une entrée d'historique par ID dans la liste d'historique
Historique* trouverHistoriqueParID(Historique* head, int id) {
    Historique* current = head;
    while (current != NULL) {
        if (current->voitureId == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;  // L'entrée d'historique est inexistante
}

// Fonction pour trouver un locataire par ID dans la liste de locataires
Locataire* trouverLocataireParID(Locataire* head, int id) {
    Locataire* current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next; 
    }
    return NULL;  // Le locataire est inexistant
}

// Fonction pour ajouter une entrée à l'historique
void ajouterHistorique(Historique** head, int voitureId, const char* marque, int locataireId, const char* date) {
    Historique* newEntry = (Historique*)malloc(sizeof(Historique));
    newEntry->voitureId = voitureId;
    strcpy(newEntry->marqueVoiture, marque);
    newEntry->locataireId = locataireId;
    strcpy(newEntry->date, date);

    newEntry->next = *head;
    *head = newEntry;
}

// Fonction pour louer une voiture
void louerUneVoiture(Voiture* head, Historique** history, int *numHistoryEntries, Locataire* tenants, int *numTenants) {
    int voitureId, locataireId;

	consulterEtatVoituresDisponibles(head);
	printf("\n");
    printf("Entrez l'ID de la voiture que vous souhaitez louer : ");
    scanf("%d", &voitureId);

    Voiture *selectedCar = trouverVoitureParID(head, voitureId);

    if (selectedCar == NULL || selectedCar->status != 'D') {
        printf("ID de voiture invalide ou la voiture n'est pas disponible.\n");
        return;
    }

    afficherLocataires(tenants);

    printf("Entrez l'ID du locataire qui loue la voiture : ");
    scanf("%d", &locataireId);

    Locataire *selectedTenant = trouverLocataireParID(tenants, locataireId);

    if (selectedTenant == NULL) {
        printf("ID de locataire invalide.\n");
        return;
    }

    selectedCar->status = 'R';

    char currentDate[MAX_DATE_SIZE];  
    getCurrentDate(currentDate, sizeof(currentDate));

    ajouterHistorique(history, selectedCar->id, selectedCar->marque, selectedTenant->id, currentDate);
    (*numHistoryEntries)++;

    printf("Voiture louée avec succès.\n");
    sauvegarderVoitures(head, VOITURES_FILE);
    sauvegarderHistorique(history, HISTORIQUE_FILE);
}

// Fonction pour afficher la description d'une voiture
void afficherDescriptionVoiture(Voiture* head) {
    int voitureId;
    printf("Entrez l'ID de la voiture dont vous souhaitez afficher la description : ");
    scanf("%d", &voitureId);

    Voiture* selectedCar = trouverVoitureParID(head, voitureId);

    if (selectedCar != NULL) {
        printf("Description de la voiture %d :\n NB: 'B' pour bon etat,'M' pour etat moyen,'D' pour disponnible 'R' pour reserve et 'P' pour en panne\n", selectedCar->id);
        printf("Marque : %s\n", selectedCar->marque);
        printf("Immatricule : %d\n", selectedCar->immatricule);
        printf("Couleur : %s\n", selectedCar->couleur);
        printf("Etat : %c\n", selectedCar->etat);
        printf("Statut : %c\n", selectedCar->status);
    } else {
        printf("ID de voiture invalide.\n");
    }
}

// Fonction pour supprimer une voiture en panne dans une liste chaînée
void supprimerVoitureEnPanne(Voiture** head) {
    int voitureId;
    consulterEtatVoituresPanne(*head);
    printf("\n");
    printf("Entrez l'ID de la voiture en panne que vous souhaitez supprimer : ");
    scanf("%d", &voitureId);

    Voiture* current = *head;
    Voiture* previous = NULL;

    while (current != NULL && current->id != voitureId) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("ID de voiture invalide.\n");
        return;
    }

    if (current->status == 'P') {
        // Supprimer la voiture en panne revient à la marquer comme disponible
        current->status = 'D';
        printf("Voiture en panne supprimée avec succès.\n");
        sauvegarderVoitures(*head, VOITURES_FILE); 
    } else {
        printf("La voiture n'est pas en panne.\n");
    }
}

// Fonction pour afficher un menu de modification des information d'une voiture
void afficherMenuModification(Voiture *car) {
    printf("\nMenu de modification :\n");
    printf("1. Marque (actuel: %s)\n", car->marque);
    printf("2. Immatricule (actuel: %d)\n", car->immatricule);
    printf("3. Couleur (actuelle: %s)\n", car->couleur);
    printf("4. Etat (actuel: %c)\n", car->etat);
    printf("5. Status (actuel: %c)\n", car->status);
    printf("0. Quitter la modification\n");
}

// Fonction pour modifier la description et l'état d'une voiture
void modifierDescriptionEtatVoiture(Voiture* head, int numCars) {
    int voitureId;
    printf("Entrez l'ID de la voiture que vous souhaitez modifier : ");
    scanf("%d", &voitureId);

    Voiture* current = head;
    while (current != NULL && current->id != voitureId) {
        current = current->next;
    }

    if (current == NULL) {
        printf("ID de voiture invalide.\n");
        return;
    }

    int choix;
    do {
        afficherMenuModification(current);

        printf("\nChoisissez un élément à modifier (0-5) : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez la nouvelle marque : ");
                scanf("%s", current->marque);
                break;
            case 2:
                printf("Entrez le nouvel immatricule : ");
                scanf("%d", &current->immatricule);
                break;
            case 3:
                printf("Entrez la nouvelle couleur : ");
                scanf("%s", current->couleur);
                break;
            case 4:
                printf("Entrez le nouvel état : ");
                scanf(" %c", &current->etat);
                break;
            case 5:
                printf("Entrez le nouveau status (A/R/P) : ");
                scanf(" %c", &current->status);
                break;
            case 0:
                printf("Modification terminée.\n");
                break;
            default:
                printf("Choix invalide. Veuillez choisir une option valide.\n");
        }
    } while (choix != 0);

    printf("Description et état de la voiture modifiés avec succès.\n");
    sauvegarderVoitures(head, VOITURES_FILE);  
}
// Fonction pour afficher l'historique des locations par jour
void afficherHistoriqueParJour(Historique* head) {
    char dateRecherche[11];
    printf("Entrez la date (JJ/MM/AAAA) pour afficher l'historique par jour : ");
    scanf("%s", dateRecherche);

    Historique* current = head;
    int historiqueTrouve = 0;

    printf("\nHistorique des locations pour le %s :\n", dateRecherche);
    
    while (current != NULL) {
        if (strcmp(current->date, dateRecherche) == 0) {
            printf("La voiture %s avec l'id %d a été louée le %s\n", current->marqueVoiture, current->voitureId, current->date);
            historiqueTrouve = 1;
        }
        current = current->next;
    }

    if (historiqueTrouve==0) {
        printf("Aucune entrée trouvée pour la date spécifiée.\n");
    }
}

// Fonction pour afficher l'historique des locations par mois
void afficherHistoriqueParMois(Historique* head) {
    char moisRecherche[8];
    printf("Entrez le mois et l'année (MM/AAAA) pour afficher l'historique par mois : ");
    scanf("%s", moisRecherche);

    Historique* current = head;
    int historiqueTrouve = 0;

    printf("\nHistorique des locations pour le mois de %s :\n", moisRecherche);

    while (current != NULL) {
        // Extraire le mois de la date de l'historique
        char moisHistorique[8];
        strncpy(moisHistorique, current->date + 3, 7);
        moisHistorique[7] = '\0';

        if (strcmp(moisHistorique, moisRecherche) == 0) {
            printf("La voiture %s avec l'id %d a été louée le %s\n", current->marqueVoiture, current->voitureId, current->date);
            historiqueTrouve = 1;
        }
        current = current->next;
    }

    if (historiqueTrouve==0) {
        printf("Aucune entrée trouvée pour le mois spécifié.\n");
    }
}

// Fonction pour afficher l'historique des locations
void afficherHistoriqueLocations(Historique* head) {
    int choix;
    printf("\nChoisissez le mode de consultation de l'historique :\n");
    printf("1. Par jour\n");
    printf("2. Par mois\n");
    printf("0. Retour\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    switch (choix) {
    case 1:
        afficherHistoriqueParJour(head);
        break;
    case 2:
        afficherHistoriqueParMois(head);
        break;
    case 0:
        printf("Retour au menu principal.\n");
        break;
    default:
        printf("Choix invalide.\n");
    }
}

// Fonction pour le retour d'une voiture en cas de réclamation
void retourVoitureReclamation(Voiture* head) {
    int voitureId;
    
    consulterEtatVoituresReserve(head);
    printf("\n");
    
    printf("Entrez l'ID de la voiture que vous souhaitez reclamer : ");
    scanf("%d", &voitureId);

    Voiture* current = head;
    while (current != NULL && current->id != voitureId) {
        current = current->next;
    }

    if (current == NULL) {
        printf("ID de voiture invalide.\n");
        return;
    }

    if (current->status == 'R') {
        // Retourner une voiture revient à la marquer en panne
        current->status = 'P';
        printf("Réclamation effectuée avec succès.\n");
        sauvegarderVoitures(head, VOITURES_FILE);  
    } else {
        printf("La voiture n'est pas réservée.\n");
    }
}

// Fonction pour afficher des statistiques des voitures
void afficherStatistiques(Voiture* head) {
    int totalVoitures = 0;
    int voituresDisponibles = 0;
    int voituresReservees = 0;
    int voituresEnPanne = 0;

    Voiture* current = head;
    while (current != NULL) {
        totalVoitures++;

        if (current->status == 'D') {
            voituresDisponibles++;
        } else if (current->status == 'R') {
            voituresReservees++;
        } else if (current->status == 'P') {
            voituresEnPanne++;
        }

        current = current->next;
    }

    printf("\nStatistiques sur les voitures :\n");
    printf("Nombre total de voitures : %d\n", totalVoitures);
    printf("Voitures disponibles : %d\n", voituresDisponibles);
    printf("Voitures réservées : %d\n", voituresReservees);
    printf("Voitures en panne : %d\n", voituresEnPanne);
}

// Fonction pour convertir une chaîne en minuscules
void toLowerCaseString(char *str) {
    int i;
    for (i = 0; str[i]; ++i) {
        str[i] = tolower(str[i]);
    }
}

// Fonction pour rechercher des voitures par critères 
void rechercherVoitures(Voiture* head) {
    char critereRecherche[50];
    char champRecherche[20];

    printf("Entrez le champ de recherche (marque, couleur, état, etc.) : ");
    scanf("%s", champRecherche);

    printf("Entrez le critère de recherche pour le champ '%s' : ", champRecherche);
    scanf("%s", critereRecherche);

    printf("\nRésultats de la recherche pour '%s' dans le champ '%s' :\n", critereRecherche, champRecherche);
    toLowerCaseString(critereRecherche);

    Voiture* current = head;
    while (current != NULL) {
        char champLowerCase[50];
        toLowerCaseString(champRecherche);
        toLowerCaseString(current->marque);
        toLowerCaseString(current->couleur);

        if ((strcmp(champRecherche, "marque") == 0 && strcmp(current->marque, critereRecherche) == 0) ||
            (strcmp(champRecherche, "couleur") == 0 && strcmp(current->couleur, critereRecherche) == 0) ||
            (strcmp(champRecherche, "etat") == 0 && tolower(current->etat) == critereRecherche[0])) {
            printf("Voiture %d : %s %d %s %c %c\n", current->id, current->marque, current->immatricule, current->couleur, current->etat, current->status);
        }

        current = current->next;
    }
}

// Fonction pour ajouter un locataire 
void ajouterLocataire(Locataire** head, int *numTenants) {
    if (*numTenants < 100) {
        Locataire* newTenant = (Locataire*)malloc(sizeof(Locataire));
        newTenant->id = *numTenants + 1;
        printf("Entrez le nom du locataire : ");
        scanf("%s", newTenant->nom);
        printf("Entrez le prénom du locataire : ");
        scanf("%s", newTenant->prenom);
        printf("Entrez l'adresse e-mail du locataire : ");
        scanf("%s", newTenant->email);
        printf("Entrez la date de début de location (DD/MM/YYYY) : ");
        scanf("%s", newTenant->dateDebutLocation);
        printf("Entrez la date de fin de location (DD/MM/YYYY) : ");
        scanf("%s", newTenant->dateFinLocation);

        newTenant->next = *head;
        *head = newTenant;

        (*numTenants)++;
        printf("Locataire ajouté avec succès.\n");
        sauvegarderLocataires(*head, LOCATAIRES_FILE);
    } else {
        printf("Nombre maximal de locataires atteint.\n");
    }
}

// Fonction pour supprimer un locataire 
void supprimerLocataire(Locataire** head, int *numTenants) {
    int tenantId;
    printf("Entrez l'ID du locataire que vous souhaitez supprimer : ");
    scanf("%d", &tenantId);

    Locataire* current = *head;
    Locataire* prev = NULL;

    while (current != NULL && current->id != tenantId) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev != NULL) {
            prev->next = current->next;
        } else {
            *head = current->next;
        }

        free(current);
        (*numTenants)--;
        printf("Locataire supprimé avec succès.\n");
        sauvegarderLocataires(*head, LOCATAIRES_FILE);
    } else {
        printf("ID de locataire invalide.\n");
    }
}

// Fonction pour afficher le menu
void afficherMenu() {
    printf("\nMenu :\n");
    printf("1. Consulter l'etat des voitures disponibles\n");
    printf("2. Louer une voiture\n");
    printf("3. Afficher la description d'une voiture\n");
    printf("4. Supprimer une voiture en panne\n");
    printf("5. Modifier la description et l'etat d'une voiture\n");
    printf("6. Afficher l'historique des locations\n");
    printf("7. Retour d'une voiture en cas de reclamation\n");
    printf("8. Afficher les statistiques sur les voitures\n");
    printf("9. Rechercher des voitures par critères\n");
    printf("10. Afficher tous les locataires\n");
    printf("11. Ajouter un locataire\n");
    printf("12. Supprimer un locataire\n");
    printf("0. Quitter\n");
}

// Fonction pour libérer la mémoire d'une liste de voitures
void libererListeVoitures(Voiture* head) {
    while (head != NULL) {
        Voiture* temp = head;
        head = head->next;
        free(temp);
    }
}

// Fonction pour libérer la mémoire d'une liste d'historique
void libererListeHistorique(Historique* head) {
    while (head != NULL) {
        Historique* temp = head;
        head = head->next;
        free(temp);
    }
}

// Fonction pour libérer la mémoire d'une liste de locataires
void libererListeLocataires(Locataire* head) {
    while (head != NULL) {
        Locataire* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    // Initialisation des variables
    int numCars = 0;  
    int numHistoryEntries = 0;  
    int numTenants = 0;  
    Voiture* cars = NULL;  
    Historique* history = NULL;  
    Locataire* tenants = NULL;  

    // Charger les données depuis les fichiers
    chargerVoitures(&cars, VOITURES_FILE);
    chargerHistorique(&history, HISTORIQUE_FILE);
    chargerLocataires(&tenants, &numTenants, LOCATAIRES_FILE);

    int choix;
    do {
        afficherMenu();
        printf("\nChoisissez une option (0-12) : ");
        scanf("%d", &choix);
        switch (choix) {
        case 1:
            consulterEtatVoituresDisponibles(cars);
            break;
        case 2:
            louerUneVoiture(cars, &history, &numHistoryEntries, tenants, &numTenants);
            break;
        case 3:
            afficherDescriptionVoiture(cars);
            break;
        case 4:
            supprimerVoitureEnPanne(&cars);
            break;
        case 5:
            modifierDescriptionEtatVoiture(cars, numCars);
            break;
        case 6:
            afficherHistoriqueLocations(history);
            break;
        case 7:
            retourVoitureReclamation(cars);
            break;
        case 8:
            afficherStatistiques(cars);
            break;
        case 9:
            rechercherVoitures(cars);
            break;
        case 10:
            afficherLocataires(tenants);
            break;
        case 11:
            ajouterLocataire(&tenants, &numTenants);
            break;
        case 12:
            supprimerLocataire(&tenants, &numTenants);
            break;
        case 0:
            printf("Au revoir !\n");
            sauvegarderVoitures(cars, VOITURES_FILE);
            sauvegarderHistorique(&history, HISTORIQUE_FILE);
            sauvegarderLocataires(tenants, LOCATAIRES_FILE);
            // Libérer la mémoire allouée pour les listes 
            libererListeVoitures(cars);
            libererListeHistorique(history);
            libererListeLocataires(tenants);
            break;
        default:
            printf("Choix invalide. Veuillez choisir une option valide.\n");
        }
    } while (choix != 0);

    return 0;
}
