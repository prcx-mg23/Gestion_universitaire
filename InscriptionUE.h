#ifndef INSCRIPTIONUE_H_INCLUDED
#define INSCRIPTIONUE_H_INCLUDED

class Semestre;
class UniteEnseignement;

/*
 * Classe représentant l’inscription d’une UE à un semestre.
 * Elle associe une UE, un semestre de diplome et un nombre d’étudiants inscrits.
 */
class InscriptionUE {
   private:
    UniteEnseignement* ue;  // UE concernée par l’inscription
    Semestre* semestre;     // Semestre dans lequel l’UE est suivie
    int nbInscrits;         // Nombre d’étudiants inscrits à cette UE

   public:
    InscriptionUE(UniteEnseignement* ue, Semestre* semestre, int nbInscrits);

    /*
     * Retourne l’UE associée à cette inscription.
     */
    UniteEnseignement* getUE() const;
    Semestre* getSemestre() const;

    /*
     * Retourne le nombre d’étudiants inscrits.
     */
    int getNbInscrits() const;
};

#endif  // INSCRIPTIONUE_H_INCLUDED
