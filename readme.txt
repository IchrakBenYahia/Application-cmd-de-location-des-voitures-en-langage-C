Documentation du Code d'un programme en langage C qui gère la location de voitures

 1. Définition des constantes

- VOITURES_FILE, HISTORIQUE_FILE, LOCATAIRES_FILE: Noms des fichiers de sauvegarde pour les données des voitures, de l'historique et des locataires.
- MAX_VOITURES, MAX_HISTORIQUE, MAX_LOCATAIRES: Limites maximales pour le nombre de voitures, d'entrées d'historique et de locataires.
- MAX_DATE_SIZE: Taille maximale d'une chaîne de caractères pour représenter une date.

 2. Structures de données

- Voiture: Représente une voiture avec des propriétés telles que l'ID, la marque, l'immatriculation, la couleur, l'état et le statut.

- Historique: Représente une entrée d'historique de location avec des informations telles que l'ID de la voiture, la marque, l'ID du locataire et la date.

- Locataire: Représente un locataire avec des informations telles que l'ID, le nom, le prénom, l'email et les dates de début et de fin de location.

 3. Fonctions de gestion des fichiers

- sauvegarderLocataires: Sauvegarde les informations des locataires dans un fichier texte.

- chargerLocataires: Charge les informations des locataires depuis un fichier texte.

- sauvegarderVoitures: Sauvegarde les informations des voitures dans un fichier texte.

- chargerVoitures: Charge les informations des voitures depuis un fichier texte.

- sauvegarderHistorique: Sauvegarde l'historique des locations dans un fichier texte.

- chargerHistorique: Charge l'historique des locations depuis un fichier texte.

 4. Fonctions utilitaires

- getCurrentDate: Obtient la date actuelle sous forme de chaîne de caractères.

- toLowerCaseString: Convertit une chaîne en minuscules.

 5. Fonctions de recherche

- trouverVoitureParID: Recherche une voiture par ID dans la liste de voitures.

- trouverHistoriqueParID: Recherche une entrée d'historique par ID dans la liste d'historique.

- trouverLocataireParID: Recherche un locataire par ID dans la liste de locataires.

- rechercherVoitures : Permet de rechercher des voitures en fonction de certains critères (marque, couleur, état).

 6. Fonctions d'affichage

- consulterEtatVoituresDisponibles: Affiche l'état des voitures disponibles.

- consulterEtatVoituresReserve: Affiche l'état des voitures réservées.

- consulterEtatVoituresPanne: Affiche l'état des voitures en panne.

- afficherDescriptionVoiture: Affiche la description d'une voiture.

- afficherHistoriqueLocations: Affiche l'historique des locations.

- afficherLocataires: Affiche la liste des locataires.

- afficherMenuModification: Affiche le menu de modification pour une voiture.

- afficherStatistiques: Affiche des statistiques sur les voitures (disponibles, réservées, en panne).

 7. Fonctions d'interaction utilisateur

- louerUneVoiture: Permet à un utilisateur de louer une voiture.

- modifierDescriptionEtatVoiture: Permet à un utilisateur de modifier la description et l'état d'une voiture.

- retourVoitureReclamation: Permet à un utilisateur de signaler un problème avec une voiture réservée.

- ajouterLocataire: Permet d'ajouter un locataire à la liste.

- supprimerLocataire: Permet de supprimer un locataire de la liste.

 8. Fonction principale `main`

La fonction principale initialise les données, charge les informations depuis les fichiers, puis propose un menu interactif permettant à l'utilisateur d'effectuer diverses opérations liées à la gestion du système de location de voitures. Le menu offre des options telles que la consultation de l'état des voitures disponibles, la location d'une voiture, la modification des informations des voitures, l'affichage de l'historique des locations, etc.

La boucle principale s'exécute tant que l'utilisateur ne choisit pas l'option "Quitter (0)". À la sortie, les données sont sauvegardées dans les fichiers correspondants.

NB:
- pour l'etat des voiture: 'B' pour bon etat et 'M' pour etat moyen.
- pour le statut des voitures : 'D' pour disponible, 'R' pour réservée, 'P' pour en panne.
- Supprimer une voiture en panne revient à la marquer comme disponible.
- Retourner une voiture revient à la marquer en panne.




