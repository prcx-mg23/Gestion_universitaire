#ifndef DIPLOME_H_INCLUDED
#define DIPLOME_H_INCLUDED

#include <string>
#include <vector>

class Semestre;

/*
 * Classe représentant un diplôme universitaire.
 * Un diplôme est identifié par un code et un nom,
 * et il est composé de plusieurs semestres.
 */
class Diplome {
   private:
    std::string code;                  // Code du diplôme
    std::string nom;                   // Nom du diplôme
    Departement* departement;           // Departement d'appartenance
    std::vector<Semestre*> semestres;  // Liste des semestres du diplôme

   public:
    Diplome(std::string code, std::string nom, Departement* d);

    /*
     * Ajoute un semestre au diplôme.
     */
    void ajouterSemestre(Semestre* s);

    /*
     * Calcule le coût horaire total du diplôme en ETD.
     * Ce coût correspond à la somme des coûts ETD
     * de chacun de ses semestres.
     */
    double getCoutHoraireETD() const;

    /*
     * Getters
     */
    std::string getCode() const;
    std::string getNom() const;
    Departement* getDepartement() const;
    std::vector<Semestre*> getSemestres() const;

    /*
     * Affiche les informations du diplôme.
     */
    void afficher() const;
};

#endif  // DIPLOME_H_INCLUDED
