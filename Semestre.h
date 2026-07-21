#ifndef SEMESTRE_H_INCLUDED
#define SEMESTRE_H_INCLUDED

#include <vector>

class Diplome;
class InscriptionUE;

/*
 * Classe représentant un semestre d’un diplôme.
 */
class Semestre {
   private:
    int numero;        // Numéro du semestre
    Diplome* diplome;  // Diplôme auquel appartient le semestre
    std::vector<InscriptionUE*> inscriptions;  // Inscriptions aux UE

   public:
    Semestre(int numero, Diplome* diplome);

    /*
     * Ajoute une inscription UE au semestre.
     */
    void ajouterInscription(InscriptionUE* insc);

    /*
     * Calcule le coût total du semestre en ETD.
     */
    double getCoutETD() const;

    void afficher() const;

    /*
     * Getters
     */
    int getNumero() const;
    Diplome* getDiplome() const;

    std::vector<InscriptionUE*> getInscriptions() const;
};

#endif  // SEMESTRE_H_INCLUDED
