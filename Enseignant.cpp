#include <iterator>
#include <string>
#include <vector>

#include "Departement.h"
#include "Enseignant.h"
#include "Intervention.h"

using namespace std;

Enseignant::Enseignant(string id, string nom, string prenom, string adresse,
                       string email, StatutEnseignant statut,
                       Departement* departement)
    : id(id),
      nom(nom),
      prenom(prenom),
      adresse(adresse),
      email(email),
      statut(statut),
      departement(departement) {}

/*
 * Ajoute une intervention à l’enseignant.
 * Cette méthode permet d’associer une nouvelle
 * intervention à l’enseignant.
 */
void Enseignant::ajouterIntervention(Intervention* i) {
    interventions.push_back(i);
}

/*
 * Retourne le service statutaire de l’enseignant en ETD.
 *
 * Le service statutaire dépend du statut :
 *  - MC_PR  : 192 ETD
 *  - AUTRE  : 384 ETD
 */
double Enseignant::getServiceStatutaireETD() const {
    if (statut == StatutEnseignant::MC_PR) {
        return 192.0;
    }
    return 384.0;
}

/*
 * Calcule la charge réelle de l’enseignant en ETD.
 *
 * La charge réelle correspond à la somme des charges ETD
 * de toutes les interventions réalisées par l’enseignant.
 *
 */
double Enseignant::getChargeReelleETD() const {
    double total = 0.0;
    vector<Intervention*>::const_iterator it;
    for (it = interventions.begin(); it != interventions.end(); ++it) {
        total += (*it)->getETD();
    }

    return total;
}

string Enseignant::getNom() const { return nom; }

string Enseignant::getPrenom() const { return prenom; }

string Enseignant::getId() const { return id; }

string Enseignant::getEmail() const { return email; }

string Enseignant::getAdresse() const { return adresse; }

vector<Intervention*> Enseignant::getInterventions() const {
    return interventions;
}

StatutEnseignant Enseignant::getStatut() const { return statut; }

Departement* Enseignant::getDepartement() const { return departement; };
