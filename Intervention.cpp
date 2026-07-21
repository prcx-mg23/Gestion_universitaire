#include <string>

#include "Enseignant.h"
#include "Intervention.h"
#include "UniteEnseignement.h"
#include "Constantes.h"

using namespace std;

Intervention::Intervention(Enseignant* ens, UniteEnseignement* ue,
                           double hCours, double hTD, double hTP)
    : enseignant(ens),
      ue(ue),
      heuresCours(hCours),
      heuresTD(hTD),
      heuresTP(hTP) {}

/*
 * Calcule la charge de l’intervention en ETD.
 */
double Intervention::getETD() const {
    double etd = 0.0;

    etd += heuresCours * COEF_COURS;
    etd += heuresTD * COEF_TD;
    etd += heuresTP * COEF_TP;

    return etd;
}

/*
 * Retourne l’enseignant associé à l’intervention.
 */
Enseignant* Intervention::getEnseignant() const { return enseignant; }

/*
 * Retourne l’UE associée à l’intervention.
 */
UniteEnseignement* Intervention::getUE() const { return ue; }

double Intervention::getHeuresCours() const { return heuresCours; }

double Intervention::getHeuresTD() const { return heuresTD; }

double Intervention::getHeuresTP() const { return heuresTP; }
