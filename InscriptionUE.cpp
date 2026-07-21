#include <iostream>
#include <string>

#include "InscriptionUE.h"
#include "Semestre.h"
#include "UniteEnseignement.h"

using namespace std;
InscriptionUE::InscriptionUE(UniteEnseignement* ue, Semestre* semestre,
                             int nbInscrits)
    : ue(ue), semestre(semestre), nbInscrits(nbInscrits) {}

/*
 * Retourne l’UE associée à cette inscription.
 */
UniteEnseignement* InscriptionUE::getUE() const { return ue; }

/*
 * Retourne l’UE associée à cette inscription.
 */
Semestre* InscriptionUE::getSemestre() const { return semestre; }

/*
 * Retourne le nombre d’étudiants inscrits à cette UE.
 */
int InscriptionUE::getNbInscrits() const { return nbInscrits; }
