#include <iostream>
#include <string>
#include "Utils.cpp"

using namespace std;

int main()
{


    // Chargement des données
    chargerDepartements(F_DEP);
    chargerEnseignants(F_ENS);
    chargerDiplomes(F_DIP);
    chargerSemestres(F_SEM);
    chargerUEs(F_UE);
    chargerInscriptions(F_INS);
    chargerInterventions(F_INT);

    afficherEtatGlobal();

    int choix = -1;

    while (choix != 0)
    {

        afficherMenu();
        cin >> choix;
        cin.ignore();

        //AFFICHAGES

        if (choix == 1)
        {
            string code;
            cout << "Code departement : ";
            getline(cin, code);

            Departement* d = chercherDepartement(trimCopy(code));
            if (d) editerDepartement(d);
            else cout << "Departement introuvable.\n";
        }

        else if (choix == 2)
        {
            string code;
            cout << "Code departement : ";
            getline(cin, code);

            Departement* d = chercherDepartement(trimCopy(code));
            if (d) editerEnseignantsTriesParCharge(d);
            else cout << "Departement introuvable.\n";
        }

        else if (choix == 3)
        {
            string code;
            cout << "Code departement : ";
            getline(cin, code);

            Departement* d = chercherDepartement(trimCopy(code));
            if (d) editerUEsTriesParCout(d);
            else cout << "Departement introuvable.\n";
        }

        else if (choix == 4)
        {
            string codeUE;
            cout << "Code UE : ";
            getline(cin, codeUE);

            UniteEnseignement* ue = chercherUE(trimCopy(codeUE));
            if (ue) editerUE(ue);
            else cout << "UE introuvable.\n";
        }

        else if (choix == 5)
        {
            string id;
            cout << "ID enseignant : ";
            getline(cin, id);

            Enseignant* e = chercherEnseignant(trimCopy(id));
            if (e) editerEnseignant(e);
            else cout << "Enseignant introuvable.\n";
        }

        else if (choix == 6)
        {
            string code;
            cout << "Code diplome : ";
            getline(cin, code);

            Diplome* d = chercherDiplome(trimCopy(code));
            if (d) editerDiplome(d);
            else cout << "Diplome introuvable.\n";
        }

        // AJOUTS

        else if (choix == 7)
        {
            string code, nom;
            cout << "Code departement : ";
            getline(cin, code);
            cout << "Nom departement : ";
            getline(cin, nom);

            if (ajouterDepartement(trimCopy(code), trimCopy(nom), F_DEP))
                cout << "Departement ajoute.\n";
            else
                cout << "Echec ajout (code existant ou invalide).\n";
        }

        else if (choix == 8)
        {
            string id, nom, prenom, adr, mail, stat, dep;

            cout << "ID : ";
            getline(cin, id);
            cout << "Nom : ";
            getline(cin, nom);
            cout << "Prenom : ";
            getline(cin, prenom);
            cout << "Adresse : ";
            getline(cin, adr);
            cout << "Email : ";
            getline(cin, mail);
            cout << "Statut (MC_PR / AUTRE) : ";
            getline(cin, stat);
            cout << "Code departement : ";
            getline(cin, dep);

            if (ajouterEnseignant(trimCopy(id), trimCopy(nom), trimCopy(prenom),
                                  trimCopy(adr), trimCopy(mail),
                                  strToStatut(trimCopy(stat)),
                                  trimCopy(dep), F_ENS))
                cout << "Enseignant ajoute.\n";
            else
                cout << "Echec ajout.\n";
        }

        else if (choix == 9)
        {
            string code, lib, dep, resp;
            double hC, hTD, hTP;
            int gC, gTD, gTP;

            cout << "Code UE : ";
            getline(cin, code);
            cout << "Libelle : ";
            getline(cin, lib);
            cout << "h Cours : ";
            cin >> hC;
            cout << "h TD : ";
            cin >> hTD;
            cout << "h TP : ";
            cin >> hTP;
            cout << "Groupes Cours : ";
            cin >> gC;
            cout << "Groupes TD : ";
            cin >> gTD;
            cout << "Groupes TP : ";
            cin >> gTP;
            cin.ignore();

            cout << "Code departement : ";
            getline(cin, dep);
            cout << "ID responsable : ";
            getline(cin, resp);

            if (ajouterUE(trimCopy(code), trimCopy(lib),
                          hC, hTD, hTP,
                          gC, gTD, gTP,
                          trimCopy(dep), trimCopy(resp), F_UE))
                cout << "UE ajoutee.\n";
            else
                cout << "Echec ajout UE.\n";
        }

        else if (choix == 10)
        {
            string codeUE, codeDip;
            int sem, nb;

            cout << "Code UE : ";
            getline(cin, codeUE);
            cout << "Code diplome : ";
            getline(cin, codeDip);
            cout << "Numero semestre : ";
            cin >> sem;
            cout << "Nb inscrits : ";
            cin >> nb;
            cin.ignore();

            if (ajouterInscription(trimCopy(codeUE), trimCopy(codeDip),
                                   sem, nb, F_INS))
                cout << "Inscription ajoutee.\n";
            else
                cout << "Echec ajout inscription.\n";
        }

        else if (choix == 11)
        {
            string id, codeUE;
            double hC, hTD, hTP;

            cout << "ID enseignant : ";
            getline(cin, id);
            cout << "Code UE : ";
            getline(cin, codeUE);
            cout << "h Cours : ";
            cin >> hC;
            cout << "h TD : ";
            cin >> hTD;
            cout << "h TP : ";
            cin >> hTP;
            cin.ignore();

            if (ajouterIntervention(trimCopy(id), trimCopy(codeUE),
                                    hC, hTD, hTP, F_INT))
                cout << "Intervention ajoutee.\n";
            else
                cout << "Echec ajout intervention.\n";
        }

        else if (choix == 12)
        {
            string code, nom, codeDep;
            cout << "Code diplome : ";
            getline(cin, code);
            cout << "Nom diplome : ";
            getline(cin, nom);
            cout << "Code departement : ";
            getline(cin, codeDep);

            if (ajouterDiplome(trimCopy(code), trimCopy(nom), codeDep, F_DIP))
                cout << "Diplome ajoute\n";
            else
                cout << "Echec ajout (code vide ou deja existant).\n";
        }
        else if (choix == 13)
        {
            string codeDip;
            int numero;

            cout << "Code diplome : ";
            getline(cin, codeDip);
            cout << "Numero semestre : ";
            cin >> numero;
            cin.ignore();

            if (ajouterSemestre(trimCopy(codeDip), numero, F_SEM))
                cout << "Semestre ajoute.\n";
            else
                cout << "Echec ajout (diplome introuvable ou semestre deja existant).\n";
        }


        else if (choix == 14)
        {
            afficherEtatGlobal();
        }

        else if (choix == 0)
        {
            cout << "Fin du programme.\n";
        }

        else
        {
            cout << "Choix invalide.\n";
        }
    }

    return 0;
}
