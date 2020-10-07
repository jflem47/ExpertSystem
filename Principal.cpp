/////////////////////////////////////////////////////////////////////////////
//Fichier Principal.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file Principal.cpp
 * \brief Ce fichier contient un main permettant de tester le système
 * \author Jean-Francois Lemieux 111 156 490
 * \version 0.5
 * \date 29 mai 2020
 *
 * Ce fichier contient un main permettant de tester le système
 * expert en utilisant un menu contenant des choix proposés à l'utilisateur.
 */

#include <iostream>
#include <fstream>
using namespace std;

#include "SystemeExpert.h"

int main()
{
	int nb = 1;					//Choix de l'utilisateur dans le menu initialisé à 1.
	tp1::SystemeExpert se1;		//Le système expert utilisé pour les tests de base.
	tp1::SystemeExpert se2;		//Le système expert utilisé principalement pour le chaînage avant.
	tp1::Regle re;				//Une règle.
	tp1::TypeFait fait;			//Un fait.
	ifstream EntreeFichier;		//Flux d'entrée
	ofstream SortieFichier;		//Flux de sortie
	tp1::ListeCirculaire<tp1::Regle> er;	//Une liste de règles pour le retour du chaînage avant.

	//Affichage du menu
	cout << "------------------ Menu --------------------------------" << endl;
	cout << "1 - Ajouter une regle au systeme expert." << endl;
	cout << "2 - Ajouter un fait a analyser au systeme expert." << endl;
	cout << "3 - Supprimer une regle du systeme expert." << endl;
	cout << "4 - Supprimer un fait du systeme expert." << endl;
	cout << "5 - Charger un systeme expert depuis un fichier texte." << endl;
	cout << "6 - Tirer des conclusions a partir de la base de faits." << endl;
	cout << "7 - Copier un systeme expert dans un autre" << endl;
	cout << "8-  Sauvegarder un systeme expert dans un fichier texte" << endl;
	cout << "0 - Quitter." << endl;
	cout << "--------------------------------------------------------" << endl;

	while (nb != 0)
	{
		do
		{
			cout << endl;
			cout << "Entrer s.v.p. votre choix (0 a 8):? ";
			cin >> nb;
			if(nb <0 || nb>8)
			{
				cout << "***Option invalide!***\n";
			}
		}while(nb <0 || nb>8);

		try
		{
			switch (nb)
			{
				case 1:
					//Ajouter une regle au systeme expert.
                    if (find(re.GetPremisses().begin(), re.GetPremisses().end(), "a des poils") == re.GetPremisses().end())
					    re.GetPremisses().push_back("a des poils");
                    if (find(re.GetConclusions().begin(), re.GetConclusions().end(), "est un mammifere") == re.GetConclusions().end())
					    re.GetConclusions().push_back("est un mammifere");
					se1.ajouterRegleSE(re);
					cout << "La regle suivante a ete ajoutee:" << endl;
					cout << "Si Animal << a des poils>>, alors Animal <<est un mammifere>>" << endl;
					cout << "Nombre de premisses de cette regle: " << re.GetPremisses().size() << endl;;
					cout << "Nombre de conclusions de cette regle: " << re.GetConclusions().size() << endl;
					cout << "Affichage du systeme expert:" << endl << se1 << endl;
					break;

				case 2:
					//Ajouter un fait a analyser au systeme expert.
					fait = "a des poils";
					se1.ajouterFaitSE(fait);
					cout <<"Le fait suivant a ete ajoute: " << fait << endl;
					cout << "Nombre de faits dans la base de faits: " << se1.getBaseFaits().size() << endl;
					cout << "Affichage du systeme expert:" << endl << se1 << endl;
					break;

				case 3:
					//Supprimer une regle du systeme expert.
					se1.getBaseRegles().enleverPos(1);
					cout << "La regle suivante a ete supprimee:" << endl;
					cout << "Si Animal <<a des poils>>, alors Animal <<est un mammifere>>" << endl;
					cout << "Affichage du systeme expert:" << endl << se1 << endl;
					break;

				case 4:
					//Supprimer un fait du systeme expert.
					se1.getBaseFaits().pop_back();
					cout <<"Le fait suivant a ete supprime: " << fait << endl;
					cout << "Affichage du systeme expert:" << endl << se1 << endl;
					break;

				case 5:
					//Charger un systeme expert depuis un fichier texte.
					EntreeFichier.open("Animaux.txt", ios::in);
					if(EntreeFichier.is_open())
					{
						se2.chargerSE(EntreeFichier);
						cout << "Le systeme expert a ete charge, voici son contenu:" << endl << se2 << endl;
						cout << "Nombre de regles dans la base de regles: " << se2.getBaseRegles().taille() << endl;
						cout << "Nombre de faits dans la base de faits: " << se2.getBaseFaits().size() << endl;
					}
					else
						cout << "ERREUR: Fichier introuvable!" << endl;
					EntreeFichier.close();

					break;

				case 6:
					//Tirer des conclusions a partir de la base de faits.
					se2.chainageAvant(er);
					cout << "Le systeme expert a ete sature" << endl;
				    cout << "Voici la nouvelle base de faits: " << endl;
					for (std::list<tp1::TypeFait>::iterator itr = se2.getBaseFaits().begin(); itr!= se2.getBaseFaits().end(); ++itr)
							cout << *itr << std::endl;
					cout << "Voici la liste des regles utilises: " << endl << er << endl;
					cout << "Nombre de regles utilises: " << er.taille() << endl;

					break;

				case 7:
					//Copier un systeme expert dans un autre.
					cout << "Affichage du systeme expert avant la copie:" << endl << se1 << endl;
					se1 = se2;
					cout << "Affichage du systeme expert apres la copie:" << endl << se1 << endl;

					break;

				case 8:
					//Sauvegarder le systeme expert dans un fichier texte.
					SortieFichier.open("SystemeExpert.txt", ios::out);
					if(SortieFichier.is_open())
					{
						se2.sauvegarderSE(SortieFichier);
						cout << "Le systeme expert a ete sauvegarde dans le fichier: SystemeExpert.txt" << endl;
					}
					SortieFichier.close();

					break;
			}

		}
		catch(exception & e)
		{
			std::cerr << "ERREUR: " << e.what() << std::endl;
		}
	}

	cout << "***Merci et au revoir !***" << endl;

	return 0;
}

