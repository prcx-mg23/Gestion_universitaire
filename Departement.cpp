#include <iterator>
#include <string>
#include <vector>

#include "Departement.h"
#include "Enseignant.h"
#include "UniteEnseignement.h"
#include "Diplome.h"

using namespace std;

Departement::Departement(string code, string nom)
    : code(code), nom(nom) {}

/*
 * Ajoute un enseignant à la liste des enseignants du département.
 */
void Departement::ajouterEnseignant(Enseignant* e) { enseignants.push_back(e); }

/*
 * Ajoute une UE à la liste des UE gérées par le département.
 */
void Departement::ajouterUE(UniteEnseignement* ue) { ues.push_back(ue); }

void Departement::ajouterDiplome(Diplome* d) { diplomes.push_back(d); }

/*
 * Calcule la charge totale du département en ETD.
 *
 * La charge totale correspond à la somme des charges
 * réelles de tous les enseignants du département.
 *
 */
double Departement::getChargeETD() const {
    double total = 0.0;
    vector<Enseignant*>::const_iterator it;
    for (it = enseignants.begin(); it != enseignants.end(); it++) {
        total += (*it)->getChargeReelleETD();
    }

    return total;
}

/*
 * Calcule le potentiel total du département en ETD.
 *
 * Le potentiel correspond à la somme des services
 * statutaires de tous les enseignants du département.
 */
double Departement::getPotentielETD() const {
    double total = 0.0;
    vector<Enseignant*>::const_iterator it;
    for (it = enseignants.begin(); it != enseignants.end(); ++it) {
        total += (*it)->getServiceStatutaireETD();
    }

    return total;
}

/*
 * Calcule le taux d’encadrement du département.
 *
 * Le taux d’encadrement est défini comme le rapport
 * entre la charge totale et le potentiel total.
 */
double Departement::getTauxEncadrement() const {
    double potentiel = getPotentielETD();

    if (potentiel == 0.0) {
        return 0.0;
    }

    return getChargeETD() / potentiel;
}

string Departement::getCode() const { return code; }

string Departement::getNom() const { return nom; }

vector<Enseignant*> Departement::getEnseignants() const { return enseignants; }

vector<UniteEnseignement*> Departement::getUEs() const { return ues; }

vector<Diplome*> Departement::getDiplomes() const { return diplomes; }

void Departement::afficher() const {
    cout << "Departement : " << nom << " (" << code << ")" << endl;
    cout << "  Nombre d'enseignants : " << enseignants.size() << endl;

    cout << "  Nombre d'UE : " << ues.size() << endl;
}
