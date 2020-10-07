/**
 * \file SystemeExpert.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe SystemeExpert
 * \author Jean-Francois Lemieux
 * \version 0.5
 * \date 1 juin 2020
 *
 */

#include "SystemeExpert.h"

namespace tp1 {
    /**
     * \brief Constructeur par défaut
     * \return Une instance d'un objet SystemeExpert
     */
    SystemeExpert::SystemeExpert()
            : baseFaits(), baseRegles() {}

    /**
     * \brief Constructeur de copie de la classe SystemeExpert
     * @param se Un objet SystemeExpert
     * \pre se doit être un objet SystemeExpert valide.
     * \return Une instance d'un objet SystemeExpert
     */
    SystemeExpert::SystemeExpert(const SystemeExpert &se)
            : baseRegles(se.baseRegles), baseFaits(se.baseFaits) {}

    /**
     * \brief Destructeur de la classe SystemeExpert
     */
    SystemeExpert::~SystemeExpert() {}

    /**
     * \brief Surcharge de l'operateur =
     * @param se Un objet SystemeExpert
     * \pre se doit être un objet SystemeExpert valide.
     * \post baseFaits == se.baseFaits
     * \post baseRegles == se.baseRegles
     * @return Un objet SystemeExpert
     */
    SystemeExpert &SystemeExpert::operator=(const SystemeExpert &se) {
        baseFaits = se.baseFaits;
        baseRegles = se.baseRegles;
    }

    /**
     * \brief Cette fonction permet d'ajouter une regle au SE
     * @param tr Une instance d'un objet regle
     * \pre tr doit êtreun objet Regle valide.
     * \post tr doit faire partie de baseRegles.
     */
    void SystemeExpert::ajouterRegleSE(const Regle &tr) {
        if (baseRegles.appartient(tr)) {
            std::cout << "Cette règle est déjà présente dans le Systeme Expert." << std::endl;
        } else { baseRegles.ajouter(tr, baseRegles.taille() + 1); }
    }

    /**
     * \brief Fonction pour ajouter un fait au SE
     * @param tf Un fait (string)
     * \pre le fait doit être une chaine de caractères.
     * \post tf doit faire partie de baseFaits.
     */
    void SystemeExpert::ajouterFaitSE(const TypeFait &tf) {
        bool present = false;
        for (const auto &fait : baseFaits) {
            if (fait == tf) { // Vérification de la présence du fait dans la base de faits.
                present = true;
            }
        }
        if (present == true) {
            std::cout << "Le fait est déjà présent dans le Systeme Expert." << std::endl;
        } else { baseFaits.push_back(tf); }
    }

    /**
     * \brief Cette fonction charge un SE à partir d'un fichier txt.
     * @param EntreeFichier Un fichier txt.
     * \pre EntreeFichier doit être ouvert.
     * \post baseRegles et baseFaits doivent être chargés avec le contenu du fichier EntreeFichier.
     */
    void SystemeExpert::chargerSE(std::ifstream &EntreeFichier) {
        if (EntreeFichier.is_open()) {
            std::string FaitLu;
            tp1::Regle regle;
            int cas = 1; // Initialisation d'une variable qui changera selon les balises du fichier .txt
            for (FaitLu; getline(EntreeFichier, FaitLu);) {
                if (FaitLu == "!>") cas = 2; // Cette balise indique que ce qui suit sera des conclusions
                else if (FaitLu == "!%") { // Cette balise indique que ce qui suit sera à nouveau des prémisses
                    ajouterRegleSE(regle);
                    regle.GetConclusions().clear();
                    regle.GetPremisses().clear();
                    cas = 1;
                } else if (FaitLu == "!!") { // Cette balise indique que ce qui suit sera un ensemble de faits
                    ajouterRegleSE(regle);
                    regle.GetPremisses().clear();
                    regle.GetConclusions().clear();
                    cas = 3;
                } else {
                    switch (cas) {
                        case 1: // Cas d'un ensemble de prémisses (et création d'une nouvelle règle)
                            regle.GetPremisses().push_back(FaitLu);
                            break;
                        case 2: // Cas d'un ensemble de conclusions
                            regle.GetConclusions().push_back(FaitLu);
                            break;
                        case 3: // Cas d'un ensemble de faits
                            ajouterFaitSE(FaitLu);
                            break;
                    }
                }
            }
        } else { throw std::logic_error("Le fichier doit être ouvert."); }
    }

    /**
     * \brief Cette fonction permet de sauvegarder un SE dans un fichier .txt
     * @param SortieFichier Un fichier .txt
     * \pre Le SortieFichier doit être ouvert
     * \post Le SortieFichier doit contenir le SE avec le bon format
     */
    void SystemeExpert::sauvegarderSE(std::ofstream &SortieFichier) const {
        if (SortieFichier.is_open()) {
            for (int i = 1; i <= baseRegles.taille(); i++) {
                for (const auto &premisse : baseRegles.element(i).GetPremisses()) {
                    SortieFichier << premisse << std::endl; // Ajout des prémisses de la règle courante
                }
                SortieFichier << "!>" << std::endl; // Ajout de la balise
                for (const auto &conclusion : baseRegles.element(i).GetConclusions()) {
                    SortieFichier << conclusion << std::endl; // Ajout des ocnclusions de la règle courante
                }
                if (i == baseRegles.taille()) SortieFichier << "!!" << std::endl; // Si c'était la dernière règle, ajouter la balise de Faits
                else (SortieFichier << "!%" << std::endl); // S'il y a d'autres règles, ajouter la balise de nouvelle règle (Ensemble de prémisses)
            }
            for (const auto &fait : baseFaits) {
                SortieFichier << fait << std::endl; // Ajout de l'ensemble des faits.
            }
        } else { throw std::logic_error("Le fichier doit être ouvert."); }
    }

    /**
    * \brief Cette fonction permet de saturer le SE afin d'en déduire de nouveaux faits à partir des règles et de leur
    *         conclusions.
    * @param er Une liste de règles vide afin d'y insérer les règles utilisées par la méthode.
    * \pre La liste doit être vide.
    * \pre Les bases de faits et de règles doivent contenir des faits et des règles.
    * \post La liste doit contenir les règles utilisées.
    */
    void SystemeExpert::chainageAvant(ListeCirculaire<Regle> &er) {
        if (!er.estVide()) { throw std::logic_error("La liste en entrée doit être vide."); }
        else if (baseRegles.estVide() || baseFaits.empty()) {
            throw std::logic_error(
                    "Les bases doivent contenir des règles ou des faits afin de pouvoir en tirer des conclusions.");
        } else {
            for (int i = 1; i <= baseRegles.taille(); i++) { // Pour toutes les règles:
                bool resultat = true;
                for (const auto &premisse : baseRegles.element(i).GetPremisses()) { // Valider que toutes les prémisses sont respectées.
                    if (std::find(baseFaits.begin(), baseFaits.end(), premisse) == baseFaits.end()) {
                        resultat = false; // S'il manque une ou plusieurs prémisses dans la base de faits, la règle n'est pas respectée.
                    } else { continue; } // Si la prémisse est présente dans la base de fait, on passe à la suivante.
                }
                if (resultat) { // Ssi la règle est respectée:
                    if (!er.appartient(baseRegles.element(i))) { // Si la règle n'est pas déjà présente dans la liste: l'ajouter
                        er.ajouter(baseRegles.element(i), er.taille() + 1);
                    }
                    for (const auto &conclusion : baseRegles.element(i).GetConclusions()) {
                        if (std::find(baseFaits.begin(), baseFaits.end(), conclusion) == baseFaits.end()) {
                            baseFaits.push_back(conclusion); // Si la conclusion n'est pas déjà présente dans la base de faits: l'ajouter
                            i = 1; // On réinitialise le compteur à 1 afin de repasser sur toutes les règles.
                        } else { continue; } // Ssi la conclusion est déjà présente, on passe à la suivante.
                    }
                }
            }
        }
    }
}