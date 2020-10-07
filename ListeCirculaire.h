/**
 * \file ListeCirculaire.h
 * \brief Classe définissant le type abstrait Liste.
 * \author IFT-2008
 * \version 0.5
 * \date mai 2020
 *
 * Implémentation dans une liste simplement chaînée circulaire.
 */

#ifndef _LISTECIRCULAIRE__H
#define _LISTECIRCULAIRE__H

namespace tp1 {
/**
 * \class ListeCirculaire
 *
 * \brief classe générique représentant une liste ordonnée
 *
 *  La classe gére une liste ordonnée générique. L'implémentation
 *  se fait dans une liste simplement chainée.
 */
template<typename T>
class ListeCirculaire {
public:
	ListeCirculaire();
	ListeCirculaire(const ListeCirculaire &);
	~ListeCirculaire();

	const ListeCirculaire<T> & operator =(const ListeCirculaire<T> &);

	void ajouter(const T &, const int &);
	void enleverEl(const T &);
	void enleverPos(const int &);

	int taille() const;
	bool estVide() const;
	bool appartient(const T &) const;
	T & element(const int &) const;
	int position(const T &) const;

	template<class U> friend std::ostream& operator <<(std::ostream &,
			const ListeCirculaire<U> &);
private:

	/**
	 * \class Noeud
	 *
	 * \brief Classe interne représentant un noeud (une position) dans la liste.
	 */
	class Noeud {
	public:
		T m_el; /*!<L'élément de base de la liste*/
		Noeud * m_suivant; /*!<Un pointeur vers le noeud suivant*/

		explicit Noeud(const T& data_item, Noeud * next_ptr = 0) :
				m_el(data_item), m_suivant(next_ptr) {
		}
	};

	/**
	 * \typedef typedef Noeud *elem
	 * \brief Définition d'un pointeur sur un Noeud
	 *
	 *  Pour abréger les écritures
	 */
	typedef Noeud * elem;
	elem m_dernier; /*!<Pointeur vers le dernier noeud de la liste*/
	int m_cardinalite; /*!< Cardinalité de la liste*/

	// Méthodes privées
	elem _pointeurSurNoeud(const int &) const;
	void _copier(elem);
	void _detruire();
	void _enlever(elem);
};
}

#include "ListeCirculaire.hpp"

#endif
