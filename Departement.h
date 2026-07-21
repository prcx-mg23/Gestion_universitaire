#ifndef DEPARTEMENT_H_INCLUDED
#define DEPARTEMENT_H_INCLUDED

#include <string>
#include <vector>

class Enseignant;
class UniteEnseignement;
class Diplome;
/*
 * Classe représentant un département universitaire.
 * Un département regroupe des enseignants et gère
 * plusieurs unités d’enseignement.
 */
class Departement {
   private:
    std::string code;         // Code du département
    std::string nom;          // Nom du département
    std::vector<Enseignant*> enseignants;  // Enseignants du département
    std::vector<UniteEnseignement*> ues;   // UE gérées par le département
    std::vector<Diplome*> diplomes;   // Diplome du département

   public:
    Departement(std::string code, std::string nom);

    /*
     * Ajoute un enseignant au département.
     */
    void ajouterEnseignant(Enseignant* e);

    /*
     * Ajoute une UE au département.
     */
    void ajouterUE(UniteEnseignement* ue);

    /*
     * Ajoute un diplome.
     */
    void ajouterDiplome(Diplome* d);

    /*
     * Calcule la charge totale du département en ETD.
     * La charge correspond à la somme des charges
     * réelles de tous les enseignants du département.
     */
    double getChargeETD() const;

    /*
     * Calcule le potentiel total du département en ETD.
     * Le potentiel correspond à la somme des services
     * statutaires de tous les enseignants.
     */
    double getPotentielETD() const;

    /*
     * Calcule le taux d’encadrement du département.
     * Le taux est le rapport entre la charge et le potentiel.
     */
    double getTauxEncadrement() const;

    /*
     * Getters
     */
    std::string getCode() const;
    std::string getNom() const;
    std::vector<Enseignant*> getEnseignants() const;
    std::vector<Diplome*> getDiplomes() const;
    std::vector<UniteEnseignement*> getUEs() const;

    /*
     * Affiche les informations du département.
     */
    void afficher() const;
};

#endif  // DEPARTEMENT_H_INCLUDED
