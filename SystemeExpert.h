/////////////////////////////////////////////////////////////////////////////
//Fichier SystemeExpert.h
/////////////////////////////////////////////////////////////////////////////
/**
 * \file SystemeExpert.h
 * \brief Ce fichier contient une définition de la classe SystemeExpert
 * \author IFT-2008
 * \version 0.5
 * \date mai 2020
 *
 * Ce fichier contient l'inteface d'un systeme expert permettant
 *	à partir de premisses de trouver des conclusions qui permettent
 *	finalement d'affirmer ou d'infirmer des reponses.
 *	Le systeme expert emploie les definitions de l'ensemble de regles et
 *	de l'ensemble de faits.
 *	A partir d'une comparaison systematique des faits aux regles connues,
 *	nous serons à meme de déduire des faits nouveaux.
 */

#ifndef _SYSTEMEEXPERT_H
#define _SYSTEMEEXPERT_H

#include <iostream>
#include <fstream>
#include "Regle.h"
#include <list>
#include "ListeCirculaire.h"
#include <algorithm>

namespace tp1
{

class SystemeExpert{

  public:

	SystemeExpert(); //constructeur
	~SystemeExpert(); //destructeur
	SystemeExpert(const SystemeExpert & se); //constructeur de copie
	SystemeExpert & operator = (const SystemeExpert & se); // surcharge de l’opérateur =

	// Surcharge de l’opérateur <<
	// Ne pas toucher à cette méthode
	friend std::ostream & operator << (std::ostream & os, const SystemeExpert & se)
	{
		os << "Base de regles:" << std::endl << se.baseRegles;

		os << "Base de fait:" << std::endl;

		if(se.baseFaits.empty())
			os << "La liste est vide" << std::endl;
		else
		{
			for (std::list<TypeFait>::const_iterator itr = se.baseFaits.begin(); itr!= se.baseFaits.end(); ++itr)
					os << *itr << std::endl;
		}

		return os;
	}

	// Permet d'ajouter la règle tr (déjà créée et initialisée) au système expert
	// Ne rien faire si la règle existe déjà !
	void ajouterRegleSE(const Regle & tr);

	// Permet d'ajouter le fait tf (déjà créé et initialisé) au système expert
	// Ne rien faire si le fait existe déjà !
	void ajouterFaitSE(const TypeFait & tf);

	void chargerSE(std::ifstream & EntreeFichier);
	/*	La méthode chargerSE permet de charger un système expert à partir d'un fichier texte reçu en paramètre.
		Le fichier EntreeFichier a déjà été ouvert à l'aide de la méthode "open", préalablement à l'appel de la fonction "chargerSE"
		(donc vous ne devez PAS ouvrir le fichier dans cette fonction, il sera déjà ouvert).
		De plus, la fonction "chargerSE" ne devra pas fermer ce fichier, ce sera à "l'appelant" de le faire.
		Réfléchissez aux exceptions qu'il faut lancer par cette méthode.

		Voici le format du fichier texte:

		Regle_1_Premisse_1		|
		Regle_1_Premisse_2		|
		...						|
		Regle_1_Premisse_N		| PREMIÈRE
		!>						| RÈGLE
		Regle_1_Conclusion_1	|
		Regle_1_Conclusion_2	|
		...						|
		Regle_1_Conclusion_N	|
		!%
		Regle_2_Premisse_1		|
		...						|
		Regle_2_Premisse_N		| DEUXIÈME
		!>						| RÈGLE
		Regle_2_Conclusion_1	|
		...						|
		Regle_2_Conclusion_N	|
		!%
		...						   ...
		!%
		Regle_N_Premisse_1		|
		...						|
		Regle_N_Premisse_N		| N ième
		!>						| RÈGLE
		Regle_N_Conclusion_1	|
		...						|
		Regle_N_Conclusion_N	|
		!!
		Fait_1					|
		Fait_2					| BASE DE
		...						| FAITS
		Fait_3					|
	*/


	void sauvegarderSE(std::ofstream & SortieFichier) const;

    [[noreturn]] /* La méthode sauvegarderSE permet de sauvegarder le système expert dans le fichier SortieFichier.
		Le format du fichier est le même que pour le chargement d’un système expert.
		Le fichier reçu est déjà ouvert, et votre fonction ne doit pas le fermer non plus.
		Réfléchissez aux exceptions qu'il faut lancer par cette méthode.
	*/

	void chainageAvant(ListeCirculaire<Regle> & er);
	/*	La méthode chainageAvant permet de saturer la base de faits du système expert se en retrouvant
		les faits qui peuvent être déduits de la base de faits du système expert en question
		et en se basant sur les règles de celui-ci. Cette fonction retourne (par référence) l’ensemble de règles qui ont
		permis à déduire de nouveaux faits.
		Réfléchissez aux exceptions qu'il faut lancer par cette méthode.
	*/

	//Accesseurs
	ListeCirculaire<Regle> & getBaseRegles () {return baseRegles;}
	std::list<TypeFait> & getBaseFaits () {return baseFaits;}

  private:

	ListeCirculaire<Regle> baseRegles;	//Contient toutes les règles connues du système expert (utilise la liste circulaire des TDs, mais modifiée)
    std::list<TypeFait> baseFaits;		//Contient tous les faits connus du système expert (utilise la liste STL)

   //Ajouter ici des fonctions utilitaires si nécessaire.

};

}

#endif
