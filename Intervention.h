#ifndef INTERVENTION_H_INCLUDED
#define INTERVENTION_H_INCLUDED

class Enseignant;
class UniteEnseignement;

/*
 * Classe représentant une intervention.
 * Une intervention correspond aux heures effectuées
 * par un enseignant dans une UE donnée.
 */
class Intervention {
   private:
    Enseignant* enseignant;  // Enseignant qui intervient
    UniteEnseignement* ue;   // UE concernée par l’intervention

    double heuresCours;  // Heures de cours effectuées
    double heuresTD;     // Heures de TD effectuées
    double heuresTP;     // Heures de TP effectuées

   public:
    Intervention(Enseignant* ens, UniteEnseignement* ue, double hCours,
                 double hTD, double hTP);

    /*
     * Calcule la charge de l’intervention en ETD.
     */
    double getETD() const;

    /*
     * Retourne l’enseignant associé à l’intervention.
     */
    Enseignant* getEnseignant() const;

    /*
     * Retourne l’UE associée à l’intervention.
     */
    UniteEnseignement* getUE() const;

    double getHeuresCours() const;
    double getHeuresTD() const;
    double getHeuresTP() const;
};

#endif  // INTERVENTION_H_INCLUDED
