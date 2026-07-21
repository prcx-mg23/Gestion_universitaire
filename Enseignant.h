#ifndef ENSEIGNANT_H_INCLUDED
#define ENSEIGNANT_H_INCLUDED

#include <string>
#include <vector>

#include "StatutEnseignant.h"

class Intervention;
class Departement;

/*
 * Classe représentant un enseignant.
 */
class Enseignant {
   private:
    std::string id;       // Identifiant de l’enseignant
    std::string nom;      // Nom de l’enseignant
    std::string prenom;   // Prénom de l’enseignant
    std::string adresse;  // Adresse
    std::string email;    // Email de contact

    StatutEnseignant statut;   // Statut de l’enseignant (MC_PR ou AUTRE)
    Departement* departement;  // Département d’appartenance

    std::vector<Intervention*> interventions;  // Interventions réalisées

   public:
    Enseignant(std::string id, std::string nom, std::string prenom,
               std::string adresse, std::string email, StatutEnseignant statut,
               Departement* departement);

    /*
     * Ajoute une intervention à la liste des interventions
     * réalisées par l’enseignant.
     */
    void ajouterIntervention(Intervention* i);

    /*
     * Retourne le service statutaire de l’enseignant en ETD.
     * Cette valeur dépend du statut de l’enseignant.
     */
    double getServiceStatutaireETD() const;

    /*
     * Calcule la charge réelle de l’enseignant en ETD.
     * La charge correspond à la somme des ETD de toutes
     * les interventions réalisées.
     */
    double getChargeReelleETD() const;

    /*
     * Getters
     */
    std::string getNom() const;
    std::string getPrenom() const;
    std::string getId() const;
    std::string getEmail() const;
    std::string getAdresse() const;
    std::vector<Intervention*> getInterventions() const;
    StatutEnseignant getStatut() const;
    Departement* getDepartement() const;
};

#endif  // ENSEIGNANT_H_INCLUDED
