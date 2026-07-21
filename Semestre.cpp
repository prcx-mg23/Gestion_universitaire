#include <iterator>
#include <string>
#include <vector>

#include "InscriptionUE.h"
#include "Semestre.h"

using namespace std;

Semestre::Semestre(int numero, Diplome* diplome)
    : numero(numero), diplome(diplome) {}

/*
 * Ajoute une inscription UE au semestre.
 */
void Semestre::ajouterInscription(InscriptionUE* insc) {
    inscriptions.push_back(insc);
}

/*
 * Calcule le coût total du semestre en ETD.
 */
double Semestre::getCoutETD() const {
    double somme = 0.0;
    vector<InscriptionUE*>::const_iterator it;
    for (it = inscriptions.begin(); it != inscriptions.end(); ++it) {
        somme += (*it)->getUE()->getPartPourSemestre(this);
    }

    return somme;
}

void Semestre::afficher() const { cout << "  Semestre " << numero << endl; }

int Semestre::getNumero() const { return numero; }

Diplome* Semestre::getDiplome() const { return diplome; };

vector<InscriptionUE*> Semestre::getInscriptions() const {
    return inscriptions;
}
