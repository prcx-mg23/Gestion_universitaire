#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "Departement.cpp"
#include "Diplome.cpp"
#include "Enseignant.cpp"
#include "InscriptionUE.cpp"
#include "Intervention.cpp"
#include "Semestre.cpp"
#include "StatutEnseignant.h"
#include "UniteEnseignement.cpp"
#include "Constantes.h"

using namespace std;



static vector<Departement*> g_departements;
static vector<Diplome*>     g_diplomes;


string trimCopy(string s) {
    size_t a = 0;
    while (a < s.size() && (s[a] == ' ' || s[a] == '\t' || s[a] == '\r' || s[a] == '\n')) a++;
    size_t b = s.size();
    while (b > a && (s[b - 1] == ' ' || s[b - 1] == '\t' || s[b - 1] == '\r' || s[b - 1] == '\n')) b--;
    return s.substr(a, b - a);
}

string dbl(double x, int prec = 2) {
    ostringstream oss;
    oss << fixed << setprecision(prec) << x;
    return oss.str();
}

string statutToStr(StatutEnseignant s) {
    return (s == StatutEnseignant::MC_PR) ? "MC_PR" : "AUTRE";
}

string tronquer(const string& s, size_t largeur) {
    if (s.length() <= largeur) {
        return s;
    }
    if (largeur <= 3) {
        return s.substr(0, largeur);
    }
    return s.substr(0, largeur - 3) + "...";
}

StatutEnseignant strToStatut(string s) {
    return (s == "MC_PR") ? StatutEnseignant::MC_PR : StatutEnseignant::AUTRE;
}

void separateur(char c = '-', int largeur = 70) {
    cout << string(largeur, c) << "\n";
}

// Recherches
Departement* chercherDepartement(string code) {
    for (auto d : g_departements) {
        if (d && d->getCode() == code) return d;
    }
    return nullptr;
}

Enseignant* chercherEnseignant(string id) {
    for (auto d : g_departements) {
        if (!d) continue;
        const auto& ens = d->getEnseignants();
        for (auto e : ens) {
            if (e && e->getId() == id) return e;
        }
    }
    return nullptr;
}

Diplome* chercherDiplome(string code) {
    for (auto d : g_diplomes) {
        if (d && d->getCode() == code) return d;
    }
    return nullptr;
}

UniteEnseignement* chercherUE(string codeUE) {
    for (auto d : g_departements) {
        if (!d) continue;
        const auto& ues = d->getUEs();
        for (auto ue : ues) {
            if (ue && ue->getCode() == codeUE) return ue;
        }
    }
    return nullptr;
}

Semestre* chercherSemestre(string codeDiplome, int numeroSem) {
    Diplome* dip = chercherDiplome(codeDiplome);
    if (!dip) return nullptr;

    const auto& sems = dip->getSemestres();
    for (auto s : sems) {
        if (s && s->getNumero() == numeroSem) return s;
    }
    return nullptr;
}

void lireLignesExistantes(string nomFichier, set<string>& out) {
    out.clear();
    ifstream f(nomFichier.c_str());
    if (!f) return;

    string ligne;
    while (getline(f, ligne)) {
        ligne = trimCopy(ligne);
        if (!ligne.empty()) out.insert(ligne);
    }
}

bool ecrireLignesUnion(string nomFichier, set<string>& lignes) {
    string tmp = nomFichier + ".tmp";
    ofstream f(tmp.c_str());
    if (!f) return false;

    for (auto& l : lignes) f << l << "\n";
    f.close();

    remove(nomFichier.c_str());
    rename(tmp.c_str(), nomFichier.c_str());
    return true;
}

// Sauvegarde des données
void sauvegarderDepartements(string fichier) {
    set<string> uni;
    lireLignesExistantes(fichier, uni);

    for (auto d : g_departements) {
        if (!d) continue;
        uni.insert(d->getCode() + ";" + d->getNom());
    }
    ecrireLignesUnion(fichier, uni);
}

void sauvegarderEnseignants(string fichier) {
    set<string> uni;
    lireLignesExistantes(fichier, uni);

    for (auto dep : g_departements) {
        if (!dep) continue;
        for (auto e : dep->getEnseignants()) {
            if (!e) continue;
            string ligne = e->getId() + ";" + e->getNom() + ";" + e->getPrenom()
                         + ";" + e->getAdresse() + ";" + e->getEmail() + ";"
                         + statutToStr(e->getStatut()) + ";" + dep->getCode();

            uni.insert(ligne);
        }
    }
    ecrireLignesUnion(fichier, uni);
}

void sauvegarderDiplomes(string fichier) {
    set<string> uni;
    lireLignesExistantes(fichier, uni);

    for (auto d : g_diplomes) {
        if (!d || !d->getDepartement()) continue;

        string ligne = d->getCode() + ";" +
                       d->getNom() + ";" +
                       d->getDepartement()->getCode();

        uni.insert(ligne);
    }

    ecrireLignesUnion(fichier, uni);
}
void sauvegarderSemestres(string fichier) {
    set<string> uni;
    lireLignesExistantes(fichier, uni);

    for (auto dip : g_diplomes) {
        if (!dip) continue;
        for (auto s : dip->getSemestres()) {
            if (!s) continue;
            uni.insert(to_string(s->getNumero()) + ";" + dip->getCode());
        }
    }
    ecrireLignesUnion(fichier, uni);
}

void sauvegarderUEs(string fichier) {
    set<string> uni;
    lireLignesExistantes(fichier, uni);

    for (auto dep : g_departements) {
        if (!dep) continue;
        for (auto ue : dep->getUEs()) {
            if (!ue) continue;
            string ligne = ue->getCode() + ";" + ue->getLibelle() + ";"
                         + dbl(ue->getHeuresCours(), 2) + ";" + dbl(ue->getHeuresTD(), 2) + ";" + dbl(ue->getHeuresTP(), 2) + ";"
                         + to_string(ue->getNbGroupesCours()) + ";" + to_string(ue->getNbGroupesTD()) + ";" + to_string(ue->getNbGroupesTP()) + ";"
                         + dep->getCode() + ";"
                         + (ue->getResponsable() ? ue->getResponsable()->getId() : "");

            uni.insert(ligne);
        }
    }
    ecrireLignesUnion(fichier, uni);
}

void sauvegarderInscriptions(string fichier) {
    set<string> uni;
    lireLignesExistantes(fichier, uni);
    for (auto dip : g_diplomes) {
        if (!dip) continue;
        for (auto sem : dip->getSemestres()) {
            if (!sem) continue;
            for (auto ins : sem->getInscriptions()) {
                if (!ins || !ins->getUE()) continue;

                string ligne = ins->getUE()->getCode() + ";"
                             + to_string(sem->getNumero()) + ";"
                             + dip->getCode() + ";"
                             + to_string(ins->getNbInscrits());

                uni.insert(ligne);
            }
        }
    }
    ecrireLignesUnion(fichier, uni);
}

void sauvegarderInterventions(string fichier) {
    set<string> uni;
    lireLignesExistantes(fichier, uni);
    for (auto dep : g_departements) {
        if (!dep) continue;
        for (auto e : dep->getEnseignants()) {
            if (!e) continue;
            for (auto inter : e->getInterventions()) {
                if (!inter || !inter->getUE()) continue;

                string ligne = e->getId() + ";"
                             + inter->getUE()->getCode() + ";"
                             + dbl(inter->getHeuresCours(), 2) + ";"
                             + dbl(inter->getHeuresTD(), 2) + ";"
                             + dbl(inter->getHeuresTP(), 2);

                uni.insert(ligne);
            }
        }
    }
    ecrireLignesUnion(fichier, uni);
}

//Chargement des données depuis les fichiers textes

void chargerDepartements(string fichier) {
    ifstream f(fichier.c_str());
    if (!f) { cout << "Erreur ouverture: " << fichier << "\n"; return; }

    string ligne;
    while (getline(f, ligne)) {
        ligne = trimCopy(ligne);
        if (ligne.empty()) continue;

        stringstream ss(ligne);
        string code, nom;
        getline(ss, code, ';');
        getline(ss, nom, ';');

        code = trimCopy(code); nom = trimCopy(nom);
        if (code.empty()) continue;

        if (chercherDepartement(code)) continue;

        Departement* d = new Departement(code, nom);
        g_departements.push_back(d);
    }
}

void chargerEnseignants(string fichier) {
    ifstream f(fichier.c_str());
    if (!f) { cout << "Erreur ouverture: " << fichier << "\n"; return; }

    string ligne;
    while (getline(f, ligne)) {
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

        id = trimCopy(id);
        if (id.empty()) continue;
        if (chercherEnseignant(id)) continue;

        Departement* dep = chercherDepartement(trimCopy(codeDep));
        if (!dep) continue;

        StatutEnseignant st = strToStatut(trimCopy(statutStr));

        Enseignant* e = new Enseignant(
            trimCopy(id), trimCopy(nom), trimCopy(prenom),
            trimCopy(adresse), trimCopy(email),
            st, dep
        );
        dep->ajouterEnseignant(e);
    }
}

void chargerDiplomes(string fichier) {
    ifstream f(fichier.c_str());
    if (!f) { cout << "Erreur ouverture: " << fichier << "\n"; return; }

    string ligne;
    while (getline(f, ligne)) {
        ligne = trimCopy(ligne);
        if (ligne.empty()) continue;

        stringstream ss(ligne);
        string code, nom, codeDep;
        getline(ss, code, ';');
        getline(ss, nom, ';');
        getline(ss, codeDep, ';');

        code = trimCopy(code);
        if (code.empty()) continue;
        if (chercherDiplome(code)) continue;

        Departement* dep = chercherDepartement(trimCopy(codeDep));
        if (!dep) continue;
        Diplome* dip = new Diplome(code, trimCopy(nom),dep);
        dep->ajouterDiplome(dip);
        g_diplomes.push_back(dip);
    }
}

void chargerSemestres(string fichier) {
    ifstream f(fichier.c_str());
    if (!f) { cout << "Erreur ouverture: " << fichier << "\n"; return; }

    string ligne;
    while (getline(f, ligne)) {
        ligne = trimCopy(ligne);
        if (ligne.empty()) continue;

        stringstream ss(ligne);
        string numeroStr, codeDip;
        getline(ss, numeroStr, ';');
        getline(ss, codeDip, ';');

        int numero = stoi(trimCopy(numeroStr));
        Diplome* dip = chercherDiplome(trimCopy(codeDip));
        if (!dip) continue;

        bool existe = false;
        for (auto s : dip->getSemestres()) {
            if (s && s->getNumero() == numero) { existe = true; break; }
        }
        if (existe) continue;

        dip->ajouterSemestre(new Semestre(numero, dip));
    }
}

void chargerUEs(string fichier) {
    ifstream f(fichier.c_str());
    if (!f) { cout << "Erreur ouverture: " << fichier << "\n"; return; }

    string ligne;
    while (getline(f, ligne)) {
        ligne = trimCopy(ligne);
        if (ligne.empty()) continue;

        stringstream ss(ligne);

        string code, libelle, hCStr, hTDStr, hTPStr, gCStr, gTDStr, gTPStr, codeDep, idResp;

        getline(ss, code, ';');
        getline(ss, libelle, ';');
        getline(ss, hCStr, ';');
        getline(ss, hTDStr, ';');
        getline(ss, hTPStr, ';');
        getline(ss, gCStr, ';');
        getline(ss, gTDStr, ';');
        getline(ss, gTPStr, ';');
        getline(ss, codeDep, ';');
        getline(ss, idResp, ';');

        code = trimCopy(code);
        if (code.empty()) continue;
        if (chercherUE(code)) continue;

        Departement* dep = chercherDepartement(trimCopy(codeDep));
        Enseignant* resp = chercherEnseignant(trimCopy(idResp));
        if (!dep || !resp) continue;

        double hC = stod(trimCopy(hCStr));
        double hTD = stod(trimCopy(hTDStr));
        double hTP = stod(trimCopy(hTPStr));
        int gC = stoi(trimCopy(gCStr));
        int gTD = stoi(trimCopy(gTDStr));
        int gTP = stoi(trimCopy(gTPStr));

        UniteEnseignement* ue = new UniteEnseignement(
            code, trimCopy(libelle),
            hC, hTD, hTP,
            gC, gTD, gTP,
            dep, resp
        );
        dep->ajouterUE(ue);
    }
}

void chargerInscriptions(string fichier) {
    ifstream f(fichier.c_str());
    if (!f) { cout << "Erreur ouverture: " << fichier << "\n"; return; }

    string ligne;
    while (getline(f, ligne)) {
        ligne = trimCopy(ligne);
        if (ligne.empty()) continue;

        stringstream ss(ligne);
        string codeUE, numSemStr, codeDip, nbStr;
        getline(ss, codeUE, ';');
        getline(ss, numSemStr, ';');
        getline(ss, codeDip, ';');
        getline(ss, nbStr, ';');

        UniteEnseignement* ue = chercherUE(trimCopy(codeUE));
        Semestre* sem = chercherSemestre(trimCopy(codeDip), stoi(trimCopy(numSemStr)));
        if (!ue || !sem) continue;

        bool existe = false;
        for (auto ins : ue->getInscriptions()) {
            if (ins && ins->getSemestre() == sem) { existe = true; break; }
        }
        if (existe) continue;

        int nb = stoi(trimCopy(nbStr));
        InscriptionUE* ins = new InscriptionUE(ue, sem, nb);

        ue->ajouterInscription(ins);
        sem->ajouterInscription(ins);
    }
}

void chargerInterventions(string fichier) {
    ifstream f(fichier.c_str());
    if (!f) { cout << "Erreur ouverture: " << fichier << "\n"; return; }

    string ligne;
    while (getline(f, ligne)) {
        ligne = trimCopy(ligne);
        if (ligne.empty()) continue;

        stringstream ss(ligne);
        string idEns, codeUE, hCStr, hTDStr, hTPStr;

        getline(ss, idEns, ';');
        getline(ss, codeUE, ';');
        getline(ss, hCStr, ';');
        getline(ss, hTDStr, ';');
        getline(ss, hTPStr, ';');

        Enseignant* e = chercherEnseignant(trimCopy(idEns));
        UniteEnseignement* ue = chercherUE(trimCopy(codeUE));
        if (!e || !ue) continue;

        double hC = stod(trimCopy(hCStr));
        double hTD = stod(trimCopy(hTDStr));
        double hTP = stod(trimCopy(hTPStr));

        bool existe = false;
        for (auto inter : e->getInterventions()) {
            if (inter && inter->getUE() == ue &&
                inter->getHeuresCours() == hC &&
                inter->getHeuresTD() == hTD &&
                inter->getHeuresTP() == hTP) {
                existe = true;
                break;
            }
        }
        if (existe) continue;

        Intervention* inter = new Intervention(e, ue, hC, hTD, hTP);
        e->ajouterIntervention(inter);
        ue->ajouterIntervention(inter);
    }
}

// Editions (affichage)
void editerDepartement(Departement* d) {
    if (!d) return;

    separateur('-');
    cout << "DEPARTEMENT : " << d->getNom() << " (" << d->getCode() << ")\n";
    separateur('-');

    cout << "Charge totale ETD   : " << dbl(d->getChargeETD(), 2) << "\n";
    cout << "Potentiel total ETD : " << dbl(d->getPotentielETD(), 2) << "\n";
    cout << "Taux encadrement    : " << dbl(d->getTauxEncadrement(), 2) << "\n";
    cout << "Nb enseignants      : " << d->getEnseignants().size() << "\n";
    cout << "Nb UE               : " << d->getUEs().size() << "\n";
    cout << "Nb Diplomes         : " << d->getDiplomes().size() << "\n";
    cout << "\n";
}

void editerEnseignantsTriesParCharge(Departement* d) {
    if (!d) return;

    vector<Enseignant*> ens = d->getEnseignants();
    sort(ens.begin(), ens.end(), [](Enseignant* a, Enseignant* b) {
        return a->getChargeReelleETD() > b->getChargeReelleETD();
    });

    separateur('-');
    cout << "ENSEIGNANTS - " << d->getNom() << " (" << d->getCode() << ")  (tri ETD desc)\n";
    separateur('-');

    cout << left
         << setw(8)  << "ID"
         << setw(14) << "Nom"
         << setw(14) << "Prenom"
         << setw(18) << "Adresse"
         << setw(22) << "Email"
         << setw(8)  << "Statut"
         << setw(8)  << "ETD"
         << setw(8)  << "Interventions"
         << "\n";

    for (auto e : ens) {
        if (!e) continue;
        cout << left
             << setw(8)  << e->getId()
             << setw(14) << e->getNom()
             << setw(14) << e->getPrenom()
             << setw(18) << tronquer(e->getAdresse(),17)
             << setw(22) << tronquer(e->getEmail(),17)
             << setw(8)  << statutToStr(e->getStatut())
             << setw(8)  << dbl(e->getChargeReelleETD(), 2)
             << setw(8)  << e->getInterventions().size()
             << "\n";
    }
    cout << "\n";
}

void editerUEsTriesParCout(Departement* d) {
    if (!d) return;

    vector<UniteEnseignement*> ues = d->getUEs();
    sort(ues.begin(), ues.end(), [](UniteEnseignement* a, UniteEnseignement* b) {
        return a->getCoutBrutETD() > b->getCoutBrutETD();
    });

    separateur('-');
    cout << "UE - " << d->getNom() << " (" << d->getCode() << ")  (tri Cout desc)\n";
    separateur('-');

    cout << left
         << setw(8)  << "Code"
         << setw(22) << "Libelle"
         << setw(8)  << "Cout"
         << setw(8)  << "hC"
         << setw(8)  << "hTD"
         << setw(8)  << "hTP"
         << setw(6)  << "gC"
         << setw(6)  << "gTD"
         << setw(6)  << "gTP"
         << setw(18) << "Responsable"
         << "\n";

    for (auto ue : ues) {
        if (!ue) continue;
        string resp = (ue->getResponsable())
                        ? (ue->getResponsable()->getNom() + " " + ue->getResponsable()->getPrenom())
                        : "N/A";

        cout << left
             << setw(8)  << ue->getCode()
             << setw(22) << tronquer(ue->getLibelle(),17)
             << setw(8)  << dbl(ue->getCoutBrutETD(), 2)
             << setw(8)  << dbl(ue->getHeuresCours(), 2)
             << setw(8)  << dbl(ue->getHeuresTD(), 2)
             << setw(8)  << dbl(ue->getHeuresTP(), 2)
             << setw(6)  << ue->getNbGroupesCours()
             << setw(6)  << ue->getNbGroupesTD()
             << setw(6)  << ue->getNbGroupesTP()
             << setw(18) << resp
             << "\n";
    }
    cout << "\n";
}

void editerEnseignant(Enseignant* e) {
    if (!e) return;

    separateur('-');
    cout << "ENSEIGNANT : " << e->getNom() << " " << e->getPrenom()
         << " (ID=" << e->getId() << ")\n";
    separateur('-');

    cout << "Adresse : " << e->getAdresse() << "\n";
    cout << "Email   : " << e->getEmail() << "\n";
    cout << "Statut  : " << statutToStr(e->getStatut()) << "\n";
    cout << "Charge ETD : " << dbl(e->getChargeReelleETD(), 2) << "\n";

    // UE dont il est responsable (recherche globale)
    cout << "\nUE responsables :\n";
    bool ok = false;
    for (auto dep : g_departements) {
        if (!dep) continue;
        for (auto ue : dep->getUEs()) {
            if (ue && ue->getResponsable() == e) {
                cout << " - " << ue->getCode() << " : " << ue->getLibelle() << "\n";
                ok = true;
            }
        }
    }
    if (!ok) cout << " (Aucune)\n";

    // Interventions
    cout << "\nInterventions :\n";
    const auto& inters = e->getInterventions();
    if (inters.empty()) {
        cout << " (Aucune)\n";
    } else {
        cout << left << setw(8) << "UE" << setw(22) << "Libelle"
             << setw(8) << "hC" << setw(8) << "hTD" << setw(8) << "hTP"
             << setw(8) << "ETD" << "\n";

        for (auto inter : inters) {
            if (!inter || !inter->getUE()) continue;
            auto ue = inter->getUE();

            cout << left
                 << setw(8)  << ue->getCode()
                 << setw(22) << ue->getLibelle()
                 << setw(8)  << dbl(inter->getHeuresCours(), 2)
                 << setw(8)  << dbl(inter->getHeuresTD(), 2)
                 << setw(8)  << dbl(inter->getHeuresTP(), 2)
                 << setw(8)  << dbl(inter->getETD(), 2)
                 << "\n";
        }
    }
    cout << "\n";
}

void editerUE(UniteEnseignement* ue) {
    if (!ue) return;

    separateur('-');
    cout << "UE : " << ue->getLibelle() << " (" << ue->getCode() << ")\n";
    separateur('-');

    cout << "Volumes horaires : hC=" << dbl(ue->getHeuresCours(),2)
         << "  hTD=" << dbl(ue->getHeuresTD(),2)
         << "  hTP=" << dbl(ue->getHeuresTP(),2) << "\n";
    cout << "Groupes : gC=" << ue->getNbGroupesCours()
         << "  gTD=" << ue->getNbGroupesTD()
         << "  gTP=" << ue->getNbGroupesTP() << "\n";
    cout << "Cout ETD : " << dbl(ue->getCoutBrutETD(),2) << "\n";

    cout << "Responsable : ";
    if (ue->getResponsable()) cout << ue->getResponsable()->getNom() << " " << ue->getResponsable()->getPrenom();
    else cout << "N/A";
    cout << "\n";

    // Interventions
    cout << "\nInterventions :\n";
    const auto& inters = ue->getInterventions();
    if (inters.empty()) cout << " (Aucune)\n";
    else {
        cout << left << setw(18) << "Enseignant"
             << setw(8) << "hC" << setw(8) << "hTD" << setw(8) << "hTP"
             << setw(8) << "ETD" << "\n";

        for (auto inter : inters) {
            if (!inter) continue;
            Enseignant* e = inter->getEnseignant();
            string nom = e ? (e->getNom() + " " + e->getPrenom()) : "??";

            cout << left << setw(18) << nom
                 << setw(8) << dbl(inter->getHeuresCours(),2)
                 << setw(8) << dbl(inter->getHeuresTD(),2)
                 << setw(8) << dbl(inter->getHeuresTP(),2)
                 << setw(8) << dbl(inter->getETD(),2)
                 << "\n";
        }
    }

    // Inscriptions (UE peut être dans plusieurs diplômes/semestres)
    cout << "\nInscriptions (par diplome/semestre) :\n";
    const auto& ins = ue->getInscriptions();
    if (ins.empty()) cout << " (Aucune)\n";
    else {
        cout << left << setw(10) << "Diplome" << setw(10) << "Semestre" << setw(10) << "Inscrits" << "\n";
        for (auto i : ins) {
            if (!i || !i->getSemestre()) continue;
            Semestre* s = i->getSemestre();
            Diplome* d = s->getDiplome();
            cout << left
                 << setw(10) << (d ? d->getCode() : "??")
                 << setw(10) << s->getNumero()
                 << setw(10) << i->getNbInscrits()
                 << "\n";
        }
    }
    cout << "\n";
}

void editerDiplome(Diplome* d) {
    if (!d) return;

    separateur('-');
    cout << "DIPLOME : " << d->getNom() << " (" << d->getCode() << ")\n";
    separateur('-');
     if (d->getDepartement()) {
        cout << "Departement : "
             << d->getDepartement()->getNom()
             << " (" << d->getDepartement()->getCode() << ")\n";
    }
    cout << "Cout horaire total (ETD) : " << dbl(d->getCoutHoraireETD(),2) << "\n";
    cout << "Semestres : ";
    const auto& sems = d->getSemestres();
    for (size_t i=0;i<sems.size();i++){
        cout << sems[i]->getNumero();
        if (i+1<sems.size()) cout << ", ";
    }
    if (sems.empty()) cout << "(aucun)";
    cout << "\n\n";
}

//Ajouts d'elements
bool ajouterDepartement(string code, string nom,
                              string fichierDepartements) {
    if (code.empty()) return false;
    if (chercherDepartement(code)) return false;

    g_departements.push_back(new Departement(code, nom));
    sauvegarderDepartements(fichierDepartements);
    return true;
}

bool ajouterEnseignant(string id, string nom, string prenom,
                             string adresse, string email, StatutEnseignant st,
                             string codeDep,
                             string fichierEnseignants) {
    if (id.empty()) return false;
    if (chercherEnseignant(id)) return false;

    Departement* dep = chercherDepartement(codeDep);
    if (!dep) return false;

    Enseignant* e = new Enseignant(id, nom, prenom, adresse, email, st, dep);
    dep->ajouterEnseignant(e);

    sauvegarderEnseignants(fichierEnseignants);
    return true;
}

bool ajouterUE(string code, string libelle,
                     double hC, double hTD, double hTP,
                     int gC, int gTD, int gTP,
                     string codeDep, string idResp,
                     string fichierUEs) {
    if (code.empty()) return false;
    if (chercherUE(code)) return false;

    Departement* dep = chercherDepartement(codeDep);
    Enseignant* resp = chercherEnseignant(idResp);
    if (!dep || !resp) return false;

    UniteEnseignement* ue = new UniteEnseignement(code, libelle, hC, hTD, hTP, gC, gTD, gTP, dep, resp);
    dep->ajouterUE(ue);

    sauvegarderUEs(fichierUEs);
    return true;
}

bool ajouterInscription(string codeUE, string codeDiplome,
                              int numeroSem, int nbInscrits,
                              string fichierInscriptions) {
    UniteEnseignement* ue = chercherUE(codeUE);
    Semestre* sem = chercherSemestre(codeDiplome, numeroSem);
    if (!ue || !sem) return false;

    for (auto ins : ue->getInscriptions()) {
        if (ins && ins->getSemestre() == sem) return false;
    }

    InscriptionUE* ins = new InscriptionUE(ue, sem, nbInscrits);
    ue->ajouterInscription(ins);
    sem->ajouterInscription(ins);

    sauvegarderInscriptions(fichierInscriptions);
    return true;
}

bool ajouterIntervention(string idEns, string codeUE,
                               double hC, double hTD, double hTP,
                               string fichierInterventions) {
    Enseignant* e = chercherEnseignant(idEns);
    UniteEnseignement* ue = chercherUE(codeUE);
    if (!e || !ue) return false;

    for (auto inter : e->getInterventions()) {
        if (inter && inter->getUE() == ue &&
            inter->getHeuresCours() == hC &&
            inter->getHeuresTD() == hTD &&
            inter->getHeuresTP() == hTP) {
            return false;
        }
    }

    Intervention* inter = new Intervention(e, ue, hC, hTD, hTP);
    e->ajouterIntervention(inter);
    ue->ajouterIntervention(inter);

    sauvegarderInterventions(fichierInterventions);
    return true;
}

bool ajouterDiplome(string code, string nom,
                    string codeDepartement,
                    string fichierDiplomes) {
    if (code.empty()) return false;
    if (chercherDiplome(code)) return false;

    Departement* dep = chercherDepartement(codeDepartement);
    if (!dep) return false;

    Diplome* d = new Diplome(code, nom, dep);
    g_diplomes.push_back(d);

    sauvegarderDiplomes(fichierDiplomes);
    return true;
}

bool ajouterSemestre(string codeDiplome, int numero,
                     string fichierSemestres) {
    Diplome* dip = chercherDiplome(codeDiplome);
    if (!dip) return false;

    for (auto s : dip->getSemestres()) {
        if (s && s->getNumero() == numero) return false;
    }

    dip->ajouterSemestre(new Semestre(numero, dip));
    sauvegarderSemestres(fichierSemestres);
    return true;
}

//Affichage global des données
void afficherEtatGlobal() {
    cout << "------------------ETAT GLOBAL (donnees chargees)------------------\n";

    cout << "\nDEPARTEMENTS:\n";
    for (auto d : g_departements) {
        editerDepartement(d);
        editerEnseignantsTriesParCharge(d);
        editerUEsTriesParCout(d);
    }

    cout << "\nDIPLOMES:\n";
    for (auto dip : g_diplomes) {
        editerDiplome(dip);
    }
}

// Menu
void afficherMenu() {
    cout << "\n              MENU - GESTION FST ENSEIGNANTS\n\n";

    cout << " 1 - Afficher infos departement\t"
         << " 2 - Enseignants (tri ETD) \t"
         << " 3 - UEs (tri Cout)\n";

    cout << " 4 - Infos d'une UE\t\t"
         << " 5 - Infos d'un enseignant\t"
         << " 6 - Cout diplome\n";

    cout << "--------------------------------------------------------------\n";

    cout << " 7 - Ajouter departement\t"
         << " 8 - Ajouter enseignant\t\t"
         << " 9 - Ajouter UE\n";

    cout << " 10 - Ajouter inscription\t"
         << " 11 - Ajouter intervention\t"
         << " 12 - Ajouter diplome\t\t\n";

    cout << " 13 - Ajouter semestre\t\t"
         << " 14 - Reafficher etat global\n";

    cout << "--------------------------------------------------------------\n";
    cout << " 0 - Quitter\n\n";
    cout << "Votre choix : ";
}
