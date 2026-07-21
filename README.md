# 🎓 Gestion des Enseignements FST 

> **Projet - UE Analyse et Programmation Orientées Objets / C++**
 
Logiciel de gestion et de calcul de charges horaires et de coûts d'enseignements pour la Faculté des Sciences et Techniques (FST). Ce projet couvre l'ensemble du cycle de conception POO, de l'analyse UML jusqu'à l'implémentation robuste en **C++17 / C++20**.

---

## 📌 Contexte & Objectifs

L'objectif principal est de concevoir un système d'information permettant d'effectuer la modélisation, le calcul et le suivi administratif des enseignements au sein de la faculté :

* **Calculs des charges et coûts d'heures ETD** (Équivalent TD).
* **Gestion des structures pédagogiques** (Départements, Diplômes, Semestres, UE).
* **Gestion du personnel enseignant** et suivi des services statutaires.
* **Suivi de la répartition budgétaire** des UE multi-diplômes/multi-semestres.

---

## ⚙️ Règles de Gestion & Calculs Métier

### 1. Ratios d'Équivalence TD (ETD)
Les heures d'enseignement sont pondérées selon les coefficients réglementaires universitaires :
* **Cours (CM) :** $1.5 \times \text{heures}$
* **Travaux Dirigés (TD) :** $1.0 \times \text{heures}$
* **Travaux Pratiques (TP) :** $\frac{2}{3} \times \text{heures}$

$$\text{Coût ETD UE} = (N_{CM} \times H_{CM} \times 1.5) + (N_{TD} \times H_{TD} \times 1.0) + \left(N_{TP} \times H_{TP} \times \frac{2}{3}\right)$$

*(où $N$ correspond au nombre de groupes ouverts et $H$ au nombre d'heures par groupe)*.

### 2. Répartition par Diplôme / Semestre
Lorsqu'une UE est partagée entre plusieurs diplômes/semestres, le coût ETD est proratisé en fonction du nombre d'inscrits par formation.

### 3. Statuts Enseignants & Charges Statutaires
* **PR / MC** (Enseignants-Chercheurs) : Service dû de **192h ETD / an**.
* **Autres** (Enseignants du secondaire / PRAG / Non-titulaires) : Service dû de **384h ETD / an**.

### 4. Taux d'Encadrement par Département
Ratio exprimé par le rapport entre les heures assurables par les enseignants rattachés au département et les heures totales sous la responsabilité de ce dernier.

---

## 🚀 Fonctionnalités Principales

*  **Saisie et Gestion :** Ajout et édition des départements, enseignants, diplômes, semestres, UE et affectations d'interventions.
*  **Éditions et Reporting :**
  * Calcul de la charge horaire d'un enseignant spécifique (par ID/Matricule).
  * Coût horaire global d'un diplôme.
  * Charge horaire totale d'un département.
  * Taux d'encadrement par département.
*  **Persistance des données:** Sauvegarde et chargement automatique des états via fichiers textes.
---

## 🛠️ Stack Technique & Bonnes Pratiques

* **Langage :** C++ (standard C++17 / C++20)
* **Conception :** Diagramme de classes UML & Design Patterns POO
* **Bibliothèque Standard (STL) :** Utilisation avancée des conteneurs (`std::vector`, `std::map`, `std::unordered_map`) et algorithmes STL (`<algorithm>`, `<numeric>`).

---

## 💻 Compilation et Exécution

### Prérequis
* Un compilateur C++ compatible (GCC ≥ 10, Clang ≥ 11, ou MSVC)

### Étapes de compilation

```bash
# 1. Cloner le dépôt
git clone [https://github.com/prcx-mg23/Gestion_universitaire.git](https://github.com/prcx-mg23/Gestion_universitaire.git)
cd Gestion_universitaire


# 2. Lancer le programme
./main.cpp
