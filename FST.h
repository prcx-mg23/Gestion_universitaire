#ifndef FST_H_INCLUDED
#define FST_H_INCLUDED

#include <vector>

#include "StatutEnseignant.h"

class Departement;
class Enseignant;
class Diplome;
class UniteEnseignement;

/*
 * Classe FST.
 * Cette classe centralise les différentes fonctions du système.
 */
class FST {
    std::vector<Departement*> departements;
    std::vector<Diplome*> diplomes;

   public:
    void ajouterDepartement(Departement* d);

    /*
    * Editions
    */
    void editerDepartement(Departement* d) const;
    void editerEnseignantsTriesParCharge(Departement* d) const;
    void editerUETriesParCout(Departement* d) const;
    void editerEnseignant(Departement* d) const;
    void editerUETriesParCout(Departement* d) const;

    /*
     * Recherche un département par son code.
     */
    Departement* chercherDepartement(std::string code) const;

    /*
     * Recherche un enseignant par son identifiant.
     */
    Enseignant* chercherEnseignant(std::string id) const;

    /*
     * Charge les départements depuis un fichier texte.
     */
    void chargerDepartements(std::string nomFichier);

    /*
     * Charge les enseignants depuis un fichier texte.
     */
    void chargerEnseignants(std::string nomFichier);

    /*
     * Charge les diplômes depuis un fichier texte.
     */
    void chargerDiplomes(std::string nomFichier);

    /*
     * Recherche un diplôme par son code.
     */
    Diplome* chercherDiplome(std::string code) const;

    /*
     * Charge les semestres depuis un fichier texte.
     */
    void chargerSemestres(std::string nomFichier);

    /*
     * Charge les UE depuis un fichier texte.
     */
    void chargerUEs(std::string nomFichier);

    /*
     * Charge les interventions depuis un fichier texte.
     */
    void chargerInterventions(std::string nomFichier);

    /*
     * Charge les inscriptions depuis un fichier texte.
     */
    void chargerInscriptions(std::string nomFichier);

    /*
     * Recherche une UE par son code.
     */
    UniteEnseignement* chercherUE(std::string codeUE) const;

    /*
     * Getters
     */
    std::vector<Departement*> getDepartements() const;
    std::vector<Diplome*> getDiplomes() const;

    /*
     * Ajouts
     */
    bool ajouterDepartement(std::string code, std::string nom);
    bool ajouterEnseignant(std::string id, std::string nom, std::string prenom,
                           std::string adresse, std::string email,
                           StatutEnseignant statut,
                           std::string codeDepartement);

    bool ajouterUE(std::string code, std::string libelle, double hCours,
                   double hTD, double hTP, int gCours, int gTD, int gTP,
                   std::string codeDepartement, std::string idResponsable);

    bool ajouterInscription(std::string codeUE, int numeroSemestre,
                            std::string codeDiplome, int nbInscrits);

    bool ajouterIntervention(std::string idEnseignant, std::string codeUE,
                             double hCours, double hTD, double hTP);

    /*
     * Sauvegarde des données
     */
    void sauvegarderDepartements(std::string fichier) const;
    void sauvegarderEnseignants(std::string fichier) const;
    void sauvegarderDiplomes(std::string fichier) const;
    void sauvegarderSemestres(std::string fichier) const;
    void sauvegarderUE(std::string fichier) const;
    void sauvegarderInscriptions(std::string fichier) const;
    void sauvegarderInterventions(std::string fichier) const;
};

#endif  // FST_H_INCLUDED
