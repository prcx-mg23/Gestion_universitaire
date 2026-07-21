#include <iterator>
#include <string>
#include <vector>

#include "InscriptionUE.h"
#include "Intervention.h"
#include "Semestre.h"
#include "UniteEnseignement.h"

using namespace std;

UniteEnseignement::UniteEnseignement(string code, string libelle, double hCours,
                                     double hTD, double hTP, int gCours,
                                     int gTD, int gTP, Departement* dep,
                                     Enseignant* resp)
    : code(code),
      libelle(libelle),
      heuresCours(hCours),
      heuresTD(hTD),
      heuresTP(hTP),
      nbGroupesCours(gCours),
      nbGroupesTD(gTD),
      nbGroupesTP(gTP),
      departement(dep),
      responsable(resp) {}

/*
 * Ajoute une inscription UE   la liste des inscriptions.
 */
void UniteEnseignement::ajouterInscription(InscriptionUE* insc) {
    inscriptions.push_back(insc);
}

/*
 * Ajoute une intervention   l UE.
 */
void UniteEnseignement::ajouterIntervention(Intervention* inter) {
    interventions.push_back(inter);
}

/*
 * Calcule le co t brut total de l UE en ETD.
 *
 * Le cout brut correspond au volume horaire total
 * multiplie  par le nombre de groupes et les coefficients ETD.
 */
    double UniteEnseignement::getCoutBrutETD() const {
        double coutETD = 0.0;

        coutETD += nbGroupesCours * heuresCours * COEF_COURS;
        coutETD += nbGroupesTD * heuresTD * COEF_TD;
        coutETD += nbGroupesTP * heuresTP * COEF_TP;

        return coutETD;
    }

/*
 * Calcule le nombre total d'etudiants inscrits   l'UE.
 * On additionne le nombre d'inscrits pour chaque inscription.
 */
int UniteEnseignement::getTotalInscrits() const {
    int total = 0;
    vector<InscriptionUE*>::const_iterator it;
    for (it = inscriptions.begin(); it != inscriptions.end(); ++it) {
        total += (*it)->getNbInscrits();
    }

    return total;
}

/*
 * Calcule la part du cout de l'UE correspondant   un semestre donn .
 *
 * La part est proportionnelle au nombre d'etudiants inscrits
 *   cette UE pour le semestre par rapport au total des inscrits.
 */
double UniteEnseignement::getPartPourSemestre(const Semestre* s) const {
    int totalInscrits = getTotalInscrits();
    int inscritsSemestre = 0;
    vector<InscriptionUE*>::const_iterator it;
    // Recherche du nombre d inscrits pour le semestre donne
    for (it = inscriptions.begin(); it != inscriptions.end(); ++it) {
        if ((*it)->getSemestre() == s) {
            inscritsSemestre = (*it)->getNbInscrits();
            break;
        }
    }
    if (totalInscrits == 0) return 0.0;

    return getCoutBrutETD() * inscritsSemestre / totalInscrits;
}

string UniteEnseignement::getCode() const { return code; }

void UniteEnseignement::afficher() const {
    cout << "UE : " << libelle << " (" << code << ")" << endl;

    cout << "  Volumes horaires :" << endl;
    cout << "    Cours : " << heuresCours << " h" << endl;
    cout << "    TD    : " << heuresTD << " h" << endl;
    cout << "    TP    : " << heuresTP << " h" << endl;

    cout << "  Groupes :" << endl;
    cout << "    Cours : " << nbGroupesCours << endl;
    cout << "    TD    : " << nbGroupesTD << endl;
    cout << "    TP    : " << nbGroupesTP << endl;

    if (responsable != nullptr) {
        cout << "  Responsable : " << responsable->getId() << " - "
             << responsable->getNom() << " " << responsable->getPrenom()
             << endl;
    }

    // INSCRIPTIONS
    if (!inscriptions.empty()) {
        cout << "  Inscriptions :" << endl;

        for (auto ins : inscriptions) {
            Semestre* s = ins->getSemestre();
            Diplome* d = s->getDiplome();

            cout << "    Diplome : " << d->getCode() << " - " << d->getNom()
                 << " | Semestre " << s->getNumero()
                 << " | Inscrits : " << ins->getNbInscrits() << endl;
        }
    } else {
        cout << "  Aucun inscrit pour cette UE." << endl;
    }

    cout << endl;
}

std::string UniteEnseignement::getLibelle() const { return libelle; }

double UniteEnseignement::getHeuresCours() const { return heuresCours; }

double UniteEnseignement::getHeuresTD() const { return heuresTD; }

double UniteEnseignement::getHeuresTP() const { return heuresTP; }

int UniteEnseignement::getNbGroupesCours() const { return nbGroupesCours; }

int UniteEnseignement::getNbGroupesTD() const { return nbGroupesTD; }

int UniteEnseignement::getNbGroupesTP() const { return nbGroupesTP; }

Enseignant* UniteEnseignement::getResponsable() const { return responsable; }

Departement* UniteEnseignement::getDepartement() const { return departement; }

vector<InscriptionUE*> UniteEnseignement::getInscriptions() const {
    return inscriptions;
};

vector<Intervention*> UniteEnseignement::getInterventions() const {
    return interventions;
};
