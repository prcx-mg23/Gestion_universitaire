#ifndef UNITEENSEIGNEMENT_H_INCLUDED
#define UNITEENSEIGNEMENT_H_INCLUDED

#include <string>
#include <vector>

class Departement;
class Enseignant;
class InscriptionUE;
class Semestre;
class Intervention;

/*
 * Classe représentant une Unité d’Enseignement.
 * Une UE contient des heures (cours, TD, TP), des groupes
 * et permet de calculer son coût en ETD.
 */
class UniteEnseignement {
   private:
    std::string code;     // Code de l’UE
    std::string libelle;  // Libellé de l’UE

    double heuresCours;  // Heures de cours
    double heuresTD;     // Heures de TD
    double heuresTP;     // Heures de TP

    int nbGroupesCours;  // Nombre de groupes de cours
    int nbGroupesTD;     // Nombre de groupes de TD
    int nbGroupesTP;     // Nombre de groupes de TP

    Departement* departement;                  // Département responsable
    Enseignant* responsable;                   // Responsable pédagogique
    std::vector<InscriptionUE*> inscriptions;  // Inscriptions de l’UE
    std::vector<Intervention*> interventions;  // Les interventions de l'UE assurée par des enseignants

   public:
    UniteEnseignement(std::string code, std::string libelle, double hCours,
                      double hTD, double hTP, int gCours, int gTD, int gTP,
                      Departement* dep, Enseignant* resp);

    /*
     * Ajoute une inscription UE.
     */
    void ajouterInscription(InscriptionUE* insc);

    /*
     * Ajoute une inscription UE.
     */
    void ajouterIntervention(Intervention* inter);

    /*
     * Calcule le coût brut total de l’UE en ETD.
     */
    double getCoutBrutETD() const;

    /*
     * Retourne le nombre total d’étudiants inscrits à l’UE
     * (tous semestres confondus).
     */
    int getTotalInscrits() const;

    /*
     * Calcule la part du coût de l’UE correspondant
     * à un semestre donné.
     */
    double getPartPourSemestre(const Semestre* s) const;

    /*
     * Getters
     */
    std::string getCode() const;
    std::string getLibelle() const;
    double getHeuresCours() const;
    double getHeuresTD() const;
    double getHeuresTP() const;
    int getNbGroupesCours() const;
    int getNbGroupesTD() const;
    int getNbGroupesTP() const;
    Enseignant* getResponsable() const;
    std::vector<InscriptionUE*> getInscriptions() const;
    std::vector<Intervention*> getInterventions() const;
    Departement* getDepartement() const;

    void afficher() const;
};

#endif  // UNITEENSEIGNEMENT_H_INCLUDED
