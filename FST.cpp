#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "Departement.h"
#include "Diplome.h"
#include "Enseignant.h"
#include "FST.h"
#include "InscriptionUE.h"
#include "Intervention.h"
#include "Semestre.h"
#include "StatutEnseignant.h"
#include "UniteEnseignement.h"
#include "Utils.cpp"

using namespace std;

void FST::editerChargeEnseignant(Enseignant* e) const {
    if (e == nullptr) return;

    cout << "\n------------------ ENSEIGNANT ------------------\n";
    cout << "ID      : " << e->getId() << "\n";
    cout << "Nom     : " << e->getNom() << "\n";
    cout << "Prenom  : " << e->getPrenom() << "\n";
    cout << "Adresse : " << e->getAdresse() << "\n";
    cout << "Email   : " << e->getEmail() << "\n";
    cout << "Statut  : " << statutToStr(e->getStatut()) << "\n";

    // Département (si dispo)
    if (e->getDepartement() != nullptr) {
        cout << "Departement : " << e->getDepartement()->getNom() << " ("
             << e->getDepartement()->getCode() << ")\n";
    }

    cout << "Charge reelle (ETD) : " << dbl(e->getChargeReelleETD(), 2) << "\n";

    cout << "\n------------------ Interventions -------------------\n";

    const vector<Intervention*>& inters = e->getInterventions();
    if (inters.empty()) {
        cout << "(Aucune intervention)\n";
    } else {
        cout << left << setw(8) << "UE" << setw(22) << "Libelle" << setw(10)
             << "hCours" << setw(10) << "hTD" << setw(10) << "hTP" << setw(10)
             << "ETD" << "\n";

        for (vector<Intervention*>::const_iterator it = inters.begin();
             it != inters.end(); ++it) {
            Intervention* inter = *it;
            UniteEnseignement* ue = inter->getUE();

            cout << left << setw(8) << (ue ? ue->getCode() : "??") << setw(22)
                 << (ue ? ue->getLibelle() : "??") << setw(10)
                 << dbl(inter->getHeuresCours(), 2) << setw(10)
                 << dbl(inter->getHeuresTD(), 2) << setw(10)
                 << dbl(inter->getHeuresTP(), 2) << setw(10)
                 << dbl(inter->getETD(), 2) << "\n";
        }
    }
    cout << "\n\n";
}

void FST::editerChargeDepartement(Departement* d) const {
    if (d == nullptr) return;

    cout << "\n------------------ DEPARTEMENT ------------------\n";
    cout << "Code : " << d->getCode() << "\n";
    cout << "Nom  : " << d->getNom() << "\n";
    cout << "Charge totale (ETD) : " << dbl(d->getChargeETD(), 2) << "\n";
    cout << "\n\n";
}

/*
 * Affiche le taux d’encadrement d’un département.
 */
void FST::editerTauxEncadrementDepartement(Departement* d) const {
    if (d == nullptr) return;

    cout << "\n------------------ DEPARTEMENT ------------------\n";
    cout << "Code : " << d->getCode() << "\n";
    cout << "Nom  : " << d->getNom() << "\n";

    cout << "Taux d'encadrement : " << dbl(d->getTauxEncadrement(), 2) << "\n";
    cout << "\n\n";
}

/*
 * Affiche le coût horaire total d’un diplôme en ETD.
 */
void FST::editerCoutDiplome(Diplome* d) const {
    if (d == nullptr) return;

    cout << "\n------------------ DIPLOME ------------------\n";
    cout << "Code : " << d->getCode() << "\n";
    cout << "Nom  : " << d->getNom() << "\n";
    cout << "Cout horaire total (ETD) : " << dbl(d->getCoutHoraireETD(), 2)
         << "\n";

    // Semestres (détail)
    const vector<Semestre*>& sems = d->getSemestres();
    cout << "Semestres : ";
    if (sems.empty())
        cout << "(aucun)\n";
    else {
        for (vector<Semestre*>::const_iterator it = sems.begin();
             it != sems.end(); ++it) {
            cout << (*it)->getNumero();
            if (it + 1 != sems.end()) cout << ", ";
        }
        cout << "\n";
    }

    cout << "\n\n";
}

/*
 * Affiche le détail d’un département
 */
void FST::editerDepartement(Departement* d) const {
    if (d == nullptr) return;

    cout << "\n------------------ DEPARTEMENT ------------------\n";
    cout << "Code : " << d->getCode() << "\n";
    cout << "Nom  : " << d->getNom() << "\n";
    cout << "Charge totale ETD     : " << dbl(d->getChargeETD(), 2) << "\n";
    cout << "Potentiel total ETD   : " << dbl(d->getPotentielETD(), 2) << "\n";
    cout << "Taux d'encadrement    : " << dbl(d->getTauxEncadrement(), 2)
         << "\n";
    cout << "Nombre enseignants        : " << d->getEnseignants().size()
         << "\n";
    cout << "Nombre UE                 : " << d->getUEs().size() << "\n";

    cout << "\n------------------ ENSEIGNANTS ------------------\n";
    cout << left
         << setw(10) << "ID"
         << setw(15) << "Nom"
         << setw(15) << "Prenom"
         << setw(10) << "Statut"
         << setw(25) << "Email"
         << setw(10) << "Charge"
         << "\n";

    const vector<Enseignant*>& ens = d->getEnseignants();
    for (vector<Enseignant*>::const_iterator it = ens.begin(); it != ens.end(); ++it) {
        Enseignant* e = *it;
        if (e == nullptr) continue;

        string statutStr = (e->getStatut() == StatutEnseignant::MC_PR) ? "MC/PR" : "AUTRE";

        cout << left
             << setw(10) << e->getId()
             << setw(15) << e->getNom()
             << setw(15) << e->getPrenom()
             << setw(10) << statutStr
             << setw(25) << e->getEmail()
             << setw(10) << dbl(e->getChargeReelleETD(), 2)
             << "\n";
    }


    cout << "\n------------------ UNITES D'ENSEIGNEMENT ------------------\n";
    cout << left
         << setw(10) << "Code"
         << setw(30) << "Libelle"
         << setw(10) << "hC"
         << setw(10) << "hTD"
         << setw(10) << "hTP"
         << setw(6)  << "gC"
         << setw(6)  << "gTD"
         << setw(6)  << "gTP"
         << setw(20) << "Responsable"
         << setw(10) << "CoutETD"
         << "\n";

    const vector<UniteEnseignement*>& ues = d->getUEs();
    for (vector<UniteEnseignement*>::const_iterator it = ues.begin(); it != ues.end(); ++it) {
        UniteEnseignement* ue = *it;
        if (ue == nullptr) continue;

        string respStr = "N/A";
        Enseignant* resp = ue->getResponsable();
        if (resp != nullptr) {
            respStr = resp->getNom() + " " + resp->getPrenom();
        }

        cout << left
             << setw(10) << ue->getCode()
             << setw(30) << ue->getLibelle()
             << setw(10) << dbl(ue->getHeuresCours(), 2)
             << setw(10) << dbl(ue->getHeuresTD(), 2)
             << setw(10) << dbl(ue->getHeuresTP(), 2)
             << setw(6)  << ue->getNbGroupesCours()
             << setw(6)  << ue->getNbGroupesTD()
             << setw(6)  << ue->getNbGroupesTP()
             << setw(20) << respStr
             << setw(10) << dbl(ue->getCoutBrutETD(), 2)
             << "\n";
    }

    cout << "\n";
}

/*
 * Affiche les enseignants d’un département
 */
void FST::editerEnseignant(Enseignant* e) const {
    if (e == nullptr) return;

    cout << "\n------------------ ENSEIGNANT ------------------\n";
    cout << "ID       : " << e->getId() << "\n";
    cout << "Nom      : " << e->getNom() << "\n";
    cout << "Prenom   : " << e->getPrenom() << "\n";
    cout << "Adresse  : " << e->getAdresse() << "\n";
    cout << "Email    : " << e->getEmail() << "\n";
    cout << "Statut   : " << statutToStr(e->getStatut()) << "\n";
    cout << "Charge ETD totale : "
         << dbl(e->getChargeReelleETD(), 2) << "\n";


    cout << "\nUE dont il est responsable :\n";

    bool aResponsabilite = false;
    const vector<Departement*>& deps = getDepartements();

    for (vector<Departement*>::const_iterator d = deps.begin();
         d != deps.end(); ++d) {

        const vector<UniteEnseignement*>& ues = (*d)->getUEs();
        for (vector<UniteEnseignement*>::const_iterator u = ues.begin();
             u != ues.end(); ++u) {

            if ((*u)->getResponsable() == e) {
                cout << " - " << (*u)->getCode()
                     << " : " << (*u)->getLibelle() << "\n";
                aResponsabilite = true;
            }
        }
    }

    if (!aResponsabilite) {
        cout << " (Aucune UE)\n";
    }

    cout << "\nInterventions :\n";

    const vector<Intervention*>& inters = e->getInterventions();
    if (inters.empty()) {
        cout << " (Aucune intervention)\n";
    } else {
        cout << left
             << setw(10) << "UE"
             << setw(10) << "Cours"
             << setw(10) << "TD"
             << setw(10) << "TP"
             << "\n";

        for (vector<Intervention*>::const_iterator it = inters.begin();
             it != inters.end(); ++it) {

            Intervention* inter = *it;
            cout << left
                 << setw(10) << inter->getUE()->getCode()
                 << setw(10) << dbl(inter->getHeuresCours(), 2)
                 << setw(10) << dbl(inter->getHeuresTD(), 2)
                 << setw(10) << dbl(inter->getHeuresTP(), 2)
                 << "\n";
        }
    }

    cout << "\n";
}

/*
 * Enseignants triés par charge (desc)
 */
void FST::editerEnseignantsTriesParCharge(Departement* d) const {
    if (d == nullptr) return;

    vector<Enseignant*> ens = d->getEnseignants();
    sort(ens.begin(), ens.end(), [](Enseignant* e1, Enseignant* e2) {
        return e1->getChargeReelleETD() > e2->getChargeReelleETD();
    });

    cout << "\n------------------ ENSEIGNANTS (tries par ETD) "
            "------------------\n";
    cout << "Departement : " << d->getNom() << " (" << d->getCode() << ")\n\n";

    cout << left << setw(8) << "ID" << setw(14) << "Nom" << setw(14) << "Prenom"
         << setw(8) << "Statut" << setw(10) << "ETD" << "\n";

    for (vector<Enseignant*>::const_iterator it = ens.begin(); it != ens.end();
         ++it) {
        cout << left << setw(8) << (*it)->getId() << setw(14) << (*it)->getNom()
             << setw(14) << (*it)->getPrenom() << setw(8)
             << statutToStr((*it)->getStatut()) << setw(10)
             << dbl((*it)->getChargeReelleETD(), 2) << "\n";
    }

    cout << "\n\n";
}

/*
 * UE d’un département triées par cout brut ETD (desc)
 */
void FST::editerUETriesParCout(Departement* d) const {
    if (d == nullptr) return;

    vector<UniteEnseignement*> ues = d->getUEs();
    sort(ues.begin(), ues.end(),
         [](UniteEnseignement* u1, UniteEnseignement* u2) {
             return u1->getCoutBrutETD() > u2->getCoutBrutETD();
         });

    cout << "\n------------------ UNITE D'ENSEIGNEMENT ------------------\n";
    cout << "Code     : " << ue->getCode() << "\n";
    cout << "Libelle  : " << ue->getLibelle() << "\n";
    cout << "Cout ETD : " << dbl(ue->getCoutBrutETD(), 2) << "\n";

    cout << "\nVolumes horaires :\n";
    cout << "  Cours : " << ue->getHeuresCours() << " h\n";
    cout << "  TD    : " << ue->getHeuresTD() << " h\n";
    cout << "  TP    : " << ue->getHeuresTP() << " h\n";

    cout << "\nGroupes :\n";
    cout << "  Cours : " << ue->getNbGroupesCours() << "\n";
    cout << "  TD    : " << ue->getNbGroupesTD() << "\n";
    cout << "  TP    : " << ue->getNbGroupesTP() << "\n";

    cout << "\nResponsable : ";
    if (ue->getResponsable()) {
        cout << ue->getResponsable()->getNom()
             << " " << ue->getResponsable()->getPrenom();
    } else {
        cout << "Aucun";
    }
    cout << "\n";

    cout << "\nInterventions :\n";

    const vector<Intervention*>& inters = ue->getInterventions();
    if (inters.empty()) {
        cout << " (Aucune intervention)\n";
    } else {
        cout << left
             << setw(14) << "Enseignant"
             << setw(8)  << "Cours"
             << setw(8)  << "TD"
             << setw(8)  << "TP"
             << "\n";

        for (auto it = inters.begin(); it != inters.end(); ++it) {
            Intervention* inter = *it;
            Enseignant* e = inter->getEnseignant();

            cout << left
                 << setw(14)
                 << (e ? e->getNom() + " " + e->getPrenom() : "??")
                 << setw(8) << dbl(inter->getHeuresCours(), 2)
                 << setw(8) << dbl(inter->getHeuresTD(), 2)
                 << setw(8) << dbl(inter->getHeuresTP(), 2)
                 << "\n";
        }
    }

    cout << "\nInscriptions par semestre :\n";

    const vector<InscriptionUE*>& ins = ue->getInscriptions();
    if (ins.empty()) {
        cout << " (Aucune inscription)\n";
    } else {
        cout << left
             << setw(10) << "Diplome"
             << setw(10) << "Semestre"
             << setw(10) << "Inscrits"
             << "\n";

        for (auto it = ins.begin(); it != ins.end(); ++it) {
            InscriptionUE* i = *it;
            Semestre* s = i->getSemestre();
            Diplome* d = s ? s->getDiplome() : nullptr;

            cout << left
                 << setw(10) << (d ? d->getCode() : "??")
                 << setw(10) << (s ? s->getNumero() : -1)
                 << setw(10) << i->getNbInscrits()
                 << "\n";
        }
    }

    cout << "\n";
}

Departement* FST::chercherDepartement(string code) const {
    for (vector<Departement*>::const_iterator it = departements.begin();
         it != departements.end(); ++it) {
        if ((*it)->getCode() == code) return *it;
    }
    return nullptr;
}

Enseignant* FST::chercherEnseignant(string id) const {
    for (vector<Departement*>::const_iterator it = departements.begin();
         it != departements.end(); ++it) {
        const vector<Enseignant*>& ens = (*it)->getEnseignants();
        for (vector<Enseignant*>::const_iterator e = ens.begin();
             e != ens.end(); ++e) {
            if ((*e)->getId() == id) return *e;
        }
    }
    return nullptr;
}

Diplome* FST::chercherDiplome(string code) const {
    for (vector<Diplome*>::const_iterator it = diplomes.begin();
         it != diplomes.end(); ++it) {
        if ((*it)->getCode() == code) return *it;
    }
    return nullptr;
}

UniteEnseignement* FST::chercherUE(string codeUE) const {
    for (vector<Departement*>::const_iterator itDep = departements.begin();
         itDep != departements.end(); ++itDep) {
        const vector<UniteEnseignement*>& ues = (*itDep)->getUEs();
        for (vector<UniteEnseignement*>::const_iterator itUE = ues.begin();
             itUE != ues.end(); ++itUE) {
            if ((*itUE)->getCode() == codeUE) return *itUE;
        }
    }
    return nullptr;
}

void FST::ajouterDepartement(Departement* d) { departements.push_back(d); }

void FST::chargerDepartements(string nomFichier) {
    ifstream fichier(nomFichier.c_str());
    if (!fichier) {
        cout << "Erreur ouverture fichier : " << nomFichier << endl;
        return;
    }

    string ligne;
    while (getline(fichier, ligne)) {
        ligne = trimCopy(ligne);
        if (ligne.empty()) continue;

        stringstream ss(ligne);
        string code, nom;
        getline(ss, code, ';');
        getline(ss, nom, ';');

        if (chercherDepartement(code) != nullptr) continue;

        Departement* d = new Departement(code, nom);
        departements.push_back(d);
    }

    fichier.close();
}

void FST::chargerEnseignants(string nomFichier) {
    ifstream fichier(nomFichier.c_str());
    if (!fichier) {
        cout << "Erreur ouverture fichier : " << nomFichier << endl;
        return;
    }

    string ligne;
    while (getline(fichier, ligne)) {
        ligne = trimCopy(ligne);
        if (ligne.empty()) continue;

        stringstream ss(ligne);
        string id, nom, prenom, adresse, email, statutStr, codeDep;

        getline(ss, id, ';');
        getline(ss, nom, ';');
        getline(ss, prenom, ';');
        getline(ss, adresse, ';');
        getline(ss, email, ';');
        getline(ss, statutStr, ';');
        getline(ss, codeDep, ';');

        if (chercherEnseignant(id) != nullptr) continue;

        StatutEnseignant statut = (statutStr == "MC_PR")
                                      ? StatutEnseignant::MC_PR
                                      : StatutEnseignant::AUTRE;

        Departement* dep = chercherDepartement(codeDep);
        if (dep == nullptr) continue;

        Enseignant* e =
            new Enseignant(id, nom, prenom, adresse, email, statut, dep);
        dep->ajouterEnseignant(e);
    }

    fichier.close();
}

void FST::chargerDiplomes(string nomFichier) {
    ifstream fichier(nomFichier.c_str());
    if (!fichier) {
        cout << "Erreur ouverture fichier : " << nomFichier << endl;
        return;
    }

    string ligne;
    while (getline(fichier, ligne)) {
        ligne = trimCopy(ligne);
        if (ligne.empty()) continue;

        stringstream ss(ligne);
        string code, nom;

        getline(ss, code, ';');
        getline(ss, nom, ';');

        if (chercherDiplome(code) != nullptr) continue;

        Diplome* d = new Diplome(code, nom);
        diplomes.push_back(d);
    }

    fichier.close();
}

void FST::chargerSemestres(string nomFichier) {
    ifstream fichier(nomFichier.c_str());
    if (!fichier) {
        cout << "Erreur ouverture fichier : " << nomFichier << endl;
        return;
    }

    string ligne;
    while (getline(fichier, ligne)) {
        ligne = trimCopy(ligne);
        if (ligne.empty()) continue;

        stringstream ss(ligne);
        string numeroStr, codeDiplome;

        getline(ss, numeroStr, ';');
        getline(ss, codeDiplome, ';');

        int numero = stoi(numeroStr);
        Diplome* d = chercherDiplome(codeDiplome);
        if (d == nullptr) continue;

        bool existe = false;
        const vector<Semestre*>& sems = d->getSemestres();
        for (vector<Semestre*>::const_iterator it = sems.begin();
             it != sems.end(); ++it) {
            if ((*it)->getNumero() == numero) {
                existe = true;
                break;
            }
        }
        if (existe) continue;

        Semestre* s = new Semestre(numero, d);
        d->ajouterSemestre(s);
    }

    fichier.close();
}

void FST::chargerUEs(string nomFichier) {
    ifstream fichier(nomFichier.c_str());
    if (!fichier) {
        cout << "Erreur ouverture fichier : " << nomFichier << endl;
        return;
    }

    string ligne;
    while (getline(fichier, ligne)) {
        ligne = trimCopy(ligne);
        if (ligne.empty()) continue;

        stringstream ss(ligne);

        string code, libelle;
        string hCoursStr, hTDStr, hTPStr;
        string gCoursStr, gTDStr, gTPStr;
        string codeDep, idResp;

        getline(ss, code, ';');
        getline(ss, libelle, ';');
        getline(ss, hCoursStr, ';');
        getline(ss, hTDStr, ';');
        getline(ss, hTPStr, ';');
        getline(ss, gCoursStr, ';');
        getline(ss, gTDStr, ';');
        getline(ss, gTPStr, ';');
        getline(ss, codeDep, ';');
        getline(ss, idResp, ';');

        if (chercherUE(code) != nullptr) continue;

        double hCours = stod(hCoursStr);
        double hTD = stod(hTDStr);
        double hTP = stod(hTPStr);

        int gCours = stoi(gCoursStr);
        int gTD = stoi(gTDStr);
        int gTP = stoi(gTPStr);

        Departement* dep = chercherDepartement(codeDep);
        Enseignant* resp = chercherEnseignant(idResp);
        if (dep == nullptr || resp == nullptr) continue;

        UniteEnseignement* ue = new UniteEnseignement(
            code, libelle, hCours, hTD, hTP, gCours, gTD, gTP, dep, resp);
        dep->ajouterUE(ue);
    }

    fichier.close();
}

void FST::chargerInscriptions(string nomFichier) {
    ifstream fichier(nomFichier.c_str());
    if (!fichier) {
        cout << "Erreur ouverture fichier : " << nomFichier << endl;
        return;
    }

    string ligne;
    while (getline(fichier, ligne)) {
        ligne = trimCopy(ligne);
        if (ligne.empty()) continue;

        stringstream ss(ligne);
        string codeUE, numSemStr, nbInsStr, codeDip;

        getline(ss, codeUE, ';');
        getline(ss, numSemStr, ';');
        getline(ss, codeDip, ';');
        getline(ss, nbInsStr, ';');

        int numeroSem = stoi(numSemStr);
        int nbIns = stoi(nbInsStr);

        UniteEnseignement* ue = chercherUE(codeUE);
        Diplome* dip = chercherDiplome(codeDip);
        if (ue == nullptr || dip == nullptr) continue;

        Semestre* sem = nullptr;
        for (auto s : dip->getSemestres()) {
            if (s->getNumero() == numeroSem) {
                sem = s;
                break;
            }
        }

        if (sem == nullptr) continue;

        bool existe = false;
        const vector<InscriptionUE*>& insSem = sem->getInscriptions();
        for (vector<InscriptionUE*>::const_iterator it = insSem.begin();
             it != insSem.end(); ++it) {
            if ((*it)->getUE() == ue) {
                existe = true;
                break;
            }
        }
        if (existe) continue;

        InscriptionUE* ins = new InscriptionUE(ue, sem, nbIns);
        ue->ajouterInscription(ins);
        sem->ajouterInscription(ins);
    }

    fichier.close();
}

void FST::chargerInterventions(string nomFichier) {
    ifstream fichier(nomFichier.c_str());
    if (!fichier) {
        cout << "Erreur ouverture fichier : " << nomFichier << endl;
        return;
    }

    string ligne;
    while (getline(fichier, ligne)) {
        ligne = trimCopy(ligne);
        if (ligne.empty()) continue;

        stringstream ss(ligne);
        string idEns, codeUE;
        string hCoursStr, hTDStr, hTPStr;

        getline(ss, idEns, ';');
        getline(ss, codeUE, ';');
        getline(ss, hCoursStr, ';');
        getline(ss, hTDStr, ';');
        getline(ss, hTPStr, ';');

        double hCours = stod(hCoursStr);
        double hTD = stod(hTDStr);
        double hTP = stod(hTPStr);

        Enseignant* e = chercherEnseignant(idEns);
        UniteEnseignement* ue = chercherUE(codeUE);
        if (e == nullptr || ue == nullptr) continue;

        bool existe = false;
        const vector<Intervention*>& inters = e->getInterventions();
        for (vector<Intervention*>::const_iterator it = inters.begin();
             it != inters.end(); ++it) {
            if ((*it)->getUE() == ue && (*it)->getHeuresCours() == hCours &&
                (*it)->getHeuresTD() == hTD && (*it)->getHeuresTP() == hTP) {
                existe = true;
                break;
            }
        }
        if (existe) continue;

        Intervention* inter = new Intervention(e, ue, hCours, hTD, hTP);
        e->ajouterIntervention(inter);
        ue->ajouterIntervention(inter);
    }

    fichier.close();
}

void FST::sauvegarderDepartements(string nomFichier) const {
    set<string> unionLignes;
    lireLignesExistantes(nomFichier, unionLignes);

    for (vector<Departement*>::const_iterator it = departements.begin();
         it != departements.end(); ++it) {
        unionLignes.insert((*it)->getCode() + ";" + (*it)->getNom());
    }

    ecrireLignesUnion(nomFichier, unionLignes);
}

void FST::sauvegarderEnseignants(string nomFichier) const {
    set<string> unionLignes;
    lireLignesExistantes(nomFichier, unionLignes);

    for (vector<Departement*>::const_iterator d = departements.begin();
         d != departements.end(); ++d) {
        const vector<Enseignant*>& ens = (*d)->getEnseignants();
        for (vector<Enseignant*>::const_iterator e = ens.begin();
             e != ens.end(); ++e) {
            string ligne =
                (*e)->getId() + ";" + (*e)->getNom() + ";" + (*e)->getPrenom() +
                ";" + (*e)->getAdresse() + ";" + (*e)->getEmail() + ";" +
                string(statutToStr((*e)->getStatut())) + ";" + (*d)->getCode();

            unionLignes.insert(ligne);
        }
    }

    ecrireLignesUnion(nomFichier, unionLignes);
}

void FST::sauvegarderDiplomes(string nomFichier) const {
    set<string> unionLignes;
    lireLignesExistantes(nomFichier, unionLignes);

    for (vector<Diplome*>::const_iterator it = diplomes.begin();
         it != diplomes.end(); ++it) {
        unionLignes.insert((*it)->getCode() + ";" + (*it)->getNom());
    }

    ecrireLignesUnion(nomFichier, unionLignes);
}

void FST::sauvegarderSemestres(string nomFichier) const {
    set<string> unionLignes;
    lireLignesExistantes(nomFichier, unionLignes);

    for (vector<Diplome*>::const_iterator d = diplomes.begin();
         d != diplomes.end(); ++d) {
        const vector<Semestre*>& sems = (*d)->getSemestres();
        for (vector<Semestre*>::const_iterator s = sems.begin();
             s != sems.end(); ++s) {
            unionLignes.insert(to_string((*s)->getNumero()) + ";" +
                               (*d)->getCode());
        }
    }

    ecrireLignesUnion(nomFichier, unionLignes);
}

void FST::sauvegarderUE(string nomFichier) const {
    set<string> unionLignes;
    lireLignesExistantes(nomFichier, unionLignes);

    for (vector<Departement*>::const_iterator d = departements.begin();
         d != departements.end(); ++d) {
        const vector<UniteEnseignement*>& ues = (*d)->getUEs();
        for (vector<UniteEnseignement*>::const_iterator it = ues.begin();
             it != ues.end(); ++it) {
            UniteEnseignement* ue = *it;

            string ligne =
                ue->getCode() + ";" + ue->getLibelle() + ";" +
                dbl(ue->getHeuresCours(), 2) + ";" + dbl(ue->getHeuresTD(), 2) +
                ";" + dbl(ue->getHeuresTP(), 2) + ";" +
                to_string(ue->getNbGroupesCours()) + ";" +
                to_string(ue->getNbGroupesTD()) + ";" +
                to_string(ue->getNbGroupesTP()) + ";" + (*d)->getCode() + ";" +
                (ue->getResponsable() ? ue->getResponsable()->getId() : "");

            unionLignes.insert(ligne);
        }
    }

    ecrireLignesUnion(nomFichier, unionLignes);
}

void FST::sauvegarderInscriptions(string nomFichier) const {
    set<string> unionLignes;
    lireLignesExistantes(nomFichier, unionLignes);

    for (vector<Diplome*>::const_iterator d = diplomes.begin();
         d != diplomes.end(); ++d) {
        const vector<Semestre*>& sems = (*d)->getSemestres();
        for (vector<Semestre*>::const_iterator s = sems.begin();
             s != sems.end(); ++s) {
            const vector<InscriptionUE*>& ins = (*s)->getInscriptions();
            for (vector<InscriptionUE*>::const_iterator i = ins.begin();
                 i != ins.end(); ++i) {
                InscriptionUE* in = *i;
                UniteEnseignement* ue = in->getUE();
                if (ue == nullptr) continue;

                string ligne = ue->getCode() + ";" +
                               to_string((*s)->getNumero()) + ";" +
                               to_string(in->getNbInscrits());

                unionLignes.insert(ligne);
            }
        }
    }

    ecrireLignesUnion(nomFichier, unionLignes);
}

void FST::sauvegarderInterventions(string nomFichier) const {
    set<string> unionLignes;
    lireLignesExistantes(nomFichier, unionLignes);

    for (vector<Departement*>::const_iterator d = departements.begin();
         d != departements.end(); ++d) {
        const vector<Enseignant*>& ens = (*d)->getEnseignants();
        for (vector<Enseignant*>::const_iterator e = ens.begin();
             e != ens.end(); ++e) {
            const vector<Intervention*>& inters = (*e)->getInterventions();
            for (vector<Intervention*>::const_iterator it = inters.begin();
                 it != inters.end(); ++it) {
                Intervention* inter = *it;
                UniteEnseignement* ue = inter->getUE();
                if (ue == nullptr) continue;

                string ligne = (*e)->getId() + ";" + ue->getCode() + ";" +
                               dbl(inter->getHeuresCours(), 2) + ";" +
                               dbl(inter->getHeuresTD(), 2) + ";" +
                               dbl(inter->getHeuresTP(), 2);

                unionLignes.insert(ligne);
            }
        }
    }

    ecrireLignesUnion(nomFichier, unionLignes);
}

vector<Departement*> FST::getDepartements() const { return departements; }
vector<Diplome*> FST::getDiplomes() const { return diplomes; }

bool FST::ajouterDepartement(string code, string nom) {
    if (chercherDepartement(code) != nullptr) return false;
    Departement* d = new Departement(code, nom);
    departements.push_back(d);
    return true;
}

bool FST::ajouterEnseignant(string id, string nom, string prenom,
                            string adresse, string email,
                            StatutEnseignant statut, string codeDepartement) {
    if (chercherEnseignant(id) != nullptr) return false;

    Departement* dep = chercherDepartement(codeDepartement);
    if (dep == nullptr) return false;

    Enseignant* e =
        new Enseignant(id, nom, prenom, adresse, email, statut, dep);
    dep->ajouterEnseignant(e);
    return true;
}

bool FST::ajouterUE(string code, string libelle, double hCours, double hTD,
                    double hTP, int gCours, int gTD, int gTP,
                    string codeDepartement, string idResponsable) {
    if (chercherUE(code) != nullptr) return false;

    Departement* dep = chercherDepartement(codeDepartement);
    Enseignant* resp = chercherEnseignant(idResponsable);
    if (dep == nullptr || resp == nullptr) return false;

    UniteEnseignement* ue = new UniteEnseignement(
        code, libelle, hCours, hTD, hTP, gCours, gTD, gTP, dep, resp);
    dep->ajouterUE(ue);
    return true;
}

bool FST::ajouterInscription(string codeUE, int numeroSemestre,
                             string codeDiplome, int nbInscrits) {
    UniteEnseignement* ue = chercherUE(codeUE);
    if (ue == nullptr) return false;

    Diplome* dip = chercherDiplome(codeDiplome);
    if (dip == nullptr) return false;

    Semestre* sem = nullptr;
    for (auto s : dip->getSemestres()) {
        if (s->getNumero() == numeroSemestre) {
            sem = s;
            break;
        }
    }

    if (sem == nullptr) return false;

    // Vérifier qu'on ne duplique pas
    for (auto ins : ue->getInscriptions()) {
        if (ins->getSemestre() == sem) {
            return false;  // inscription déjà existante
        }
    }

    InscriptionUE* ins = new InscriptionUE(ue, sem, nbInscrits);
    ue->ajouterInscription(ins);
    sem->ajouterInscription(ins);

    return true;
}

bool FST::ajouterIntervention(string idEnseignant, string codeUE, double hCours,
                              double hTD, double hTP) {
    Enseignant* e = chercherEnseignant(idEnseignant);
    UniteEnseignement* ue = chercherUE(codeUE);
    if (e == nullptr || ue == nullptr) return false;

    const vector<Intervention*>& inters = e->getInterventions();
    for (vector<Intervention*>::const_iterator it = inters.begin();
         it != inters.end(); ++it) {
        if ((*it)->getUE() == ue && (*it)->getHeuresCours() == hCours &&
            (*it)->getHeuresTD() == hTD && (*it)->getHeuresTP() == hTP) {
            return false;
        }
    }

    Intervention* inter = new Intervention(e, ue, hCours, hTD, hTP);
    e->ajouterIntervention(inter);
    ue->ajouterIntervention(inter);
    return true;
}
