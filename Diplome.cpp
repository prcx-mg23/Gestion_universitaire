#include <iterator>
#include <string>
#include <vector>

#include "Diplome.h"
#include "Semestre.h"

using namespace std;

Diplome::Diplome(string code, string nom, Departement* d) : code(code), nom(nom), departement(d) {}

/*
 * Ajoute un semestre au diplôme.
 * Le semestre est simplement ajouté à la liste
 * des semestres composant ce diplôme.
 */
void Diplome::ajouterSemestre(Semestre* s) { semestres.push_back(s); }

/*
 * Calcule le coût horaire total du diplôme en ETD.
 *
 * Le coût du diplôme est obtenu en parcourant
 * tous les semestres et en additionnant leurs coûts ETD.
 */
double Diplome::getCoutHoraireETD() const {
    double somme = 0.0;
    vector<Semestre*>::const_iterator it;
    for (it = semestres.begin(); it != semestres.end(); ++it) {
        somme += (*it)->getCoutETD();
    }
    return somme;
}

void Diplome::afficher() const {
    cout << "Diplome : " << nom << " (" << code << ")" << endl;

    cout << "  Nombre de semestres : " << semestres.size() << endl;
}

string Diplome::getCode() const { return code; }

string Diplome::getNom() const { return nom; }

Departement* Diplome::getDepartement() const { return departement; }

vector<Semestre*> Diplome::getSemestres() const { return semestres; }
