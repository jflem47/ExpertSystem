/**
 * \file ListeCirculaire.hpp
 * \brief Le code des opérateurs de ListeCirculaire.
 * \author IFT-2008
 * \version 0.5
 * \date mai 2020
 *
 * Implémentation de la classe générique ListeCirculaire dans une liste simplement chainée circulaire.
 *
 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

/**
 * \namespace tp1
 * \brief Namespace du tp1 contenant la classe ListeCirculaire.
 */
namespace tp1 {

/**
 *  \brief Constructeur par défaut
 *
 *  \post Une instance de la classe ListeCirculaire est initialisée
 */
template<typename T>
ListeCirculaire<T>::ListeCirculaire() :
		m_dernier(0), m_cardinalite(0) {
}

/**
 *  \brief Destructeur
 *  \post L'instance de ListeCirculaire est détruite.
 */
template<typename T>
ListeCirculaire<T>::~ListeCirculaire() {
	_detruire();
}

/**
 *  \brief Constructeur de copie.
 *
 * \pre Il faut qu'il y ait suffisamment de mémoire
 * \post La liste passée en paramètre est copiée
 * \param[in] p_source La liste à copier
 * \exception bad_alloc s'il n'y a pas assez de mémoire
 */
template<typename T>
ListeCirculaire<T>::ListeCirculaire(const ListeCirculaire & p_source) :
        m_dernier(p_source.m_dernier), m_cardinalite(p_source.m_cardinalite){
	if (!p_source.estVide()) {
		_copier(p_source.m_dernier);
	}
}

/**
 * \brief Surcharge de l'opérateur =
 *
 * \pre Il y a assez de mémoire pour l'opération
 * \post La liste passée en paramètre est copiée
 * \param[in] p_source La liste à copier
 * \exception bad_alloc si la précondition n'est pas respectée
 */
template<typename T>
const ListeCirculaire<T>& ListeCirculaire<T>::operator =(const ListeCirculaire<T>& p_source) {
	if (this != &p_source) {
		_detruire();
		if (!p_source.estVide()) {
			_copier(p_source.m_dernier);
		}
	}

	return *this;
}

/**
 *  \brief Ajouter un nouvel élément dans la liste
 *
 * \pre Il y a assez de Mémoire pour ajouter l'élément x
 * \pre La position d'ajout, pos, est comprise entre 1 et |L|+1
 * \post La liste comprend un élément de plus
 * \post La liste est inchangée sinon
 * \param[in] p_element L'élément à ajouter
 * \param[in] p_position La position de l'élément à ajouter
 * \exception bad_alloc si pas assez de mémoire
 */
template<typename T>
void ListeCirculaire<T>::ajouter(const T & p_element, const int & p_position) {
	if (!(p_position > 0 && p_position <= m_cardinalite + 1))
		throw std::logic_error("ListeCirculaire::ajouter: Erreur de préconditions !");

	// liste vide
	if (m_dernier == 0) {
		m_dernier = new Noeud(p_element);
		m_dernier->m_suivant = m_dernier;
	}
	// première position
	else if (p_position == 1) {
		m_dernier->m_suivant = new Noeud(p_element, m_dernier->m_suivant);
	}
	// dernière position
	else if (p_position == m_cardinalite + 1) {
		m_dernier->m_suivant = new Noeud(p_element, m_dernier->m_suivant);
		m_dernier = m_dernier->m_suivant;
		// position quelconque
	} else {
		elem sentinelle = _pointeurSurNoeud(p_position - 1);
		sentinelle->m_suivant = new Noeud(p_element, sentinelle->m_suivant);
	}

	int cardinaliteCourante = m_cardinalite;
	m_cardinalite++;
}

/**
 *  \brief Enlever la première occurence d'un élément
 *
 * \pre L'élément doit être présent dans la liste
 * \post La liste comprend un élément de moins
 * \post La liste est inchangée sinon
 * \param[in] p_elementARetirer L'élément à retirer
 */
template<typename T>
void ListeCirculaire<T>::enleverEl(const T & p_elementARetirer) {
	if (!(appartient(p_elementARetirer)))
        throw std::logic_error("ListeCirculaire::enleverEl: Erreur de préconditions !");

	elem sentinelle = m_dernier->m_suivant;
	while (sentinelle != m_dernier
			&& sentinelle->m_suivant->m_el != p_elementARetirer) {
		sentinelle = sentinelle->m_suivant;
	}
	_enlever(sentinelle);

	int cardinaliteCourante = m_cardinalite;
	m_cardinalite--;
}

/**
 *  \brief Enlever un élément à une certaine position
 *
 * \pre La position doit être comprise entre 1 et |L|
 * \post La liste comprend un élément de moins
 * \post La liste est inchangée sinon
 * \param[in] p_position La position à effacer
 */
template<typename T>
void ListeCirculaire<T>::enleverPos(const int & p_position) {
	if (!(p_position >= 1 && p_position <= m_cardinalite))
        throw std::logic_error("ListeCirculaire::enleverPos: Erreur de préconditions !");

	elem sentinelle(0);
	if (p_position == 1) {
		sentinelle = m_dernier;
	} else {
		sentinelle = _pointeurSurNoeud(p_position - 1);
	}
	_enlever(sentinelle);

	int cardinaliteCourante = m_cardinalite;
	m_cardinalite--;
}

/**
 * \brief Retourne la cardinalité de la liste
 *
 * \post La liste est inchangée
 * \return La cardinalité de la liste est retournée
 */
template<typename T>
int ListeCirculaire<T>::taille() const {
	return m_cardinalite;
}

/**
 * \brief Vérifier si la liste est vide
 *
 * \post La liste est inchangée
 * \return Bool indiquant si la liste est vide ou non
 */
template<typename T>
bool ListeCirculaire<T>::estVide() const {
	return m_cardinalite == 0;
}

/**
 * \brief Recherche d'un élément dans la liste
 *
 * \post La liste est inchangée
 * \param[in] p_elementATrouver L'élément à tester
 * \return Bool indiquand si l'élément est dans la liste
 */
template<typename T>
bool ListeCirculaire<T>::appartient(const T & p_elementATrouver) const {
	if (m_dernier == 0) {
		return false;
	}
	elem sentinelle = m_dernier->m_suivant;
	while (sentinelle != m_dernier) {
		if (sentinelle->m_el == p_elementATrouver) {
			return true;
		}
		sentinelle = sentinelle->m_suivant;
	}
	if (m_dernier->m_el == p_elementATrouver) {
		return true;
	}
	return false;
}

/**
 * \brief Retourner l'élément à une certaine position
 *
 * \pre La position est comprise entre 1 et |L|
 * \post La liste est inchangée dans tous les cas
 * \param[in] p_position La position où trouver l'élément
 * \return L'élément à la position demandée est retourné
 */
template<typename T>
T & ListeCirculaire<T>::element(const int & p_position) const {
	if (!(p_position >= 1 && p_position <= m_cardinalite))
        throw std::logic_error("ListeCirculaire::element: Erreur de préconditions !");
	return _pointeurSurNoeud(p_position)->m_el;
}

/**
 * \brief Retourner la position d'un élément
 *
 * \pre L'élément doit être présent dans la liste
 * \post La liste est inchangée dans tous les cas
 * \param[in] p_elementATrouver L'élément à trouver
 * \return La position de l'élément est retournée
 */
template<typename T>
int ListeCirculaire<T>::position(const T & p_elementATrouver) const {
	elem sentinelle = m_dernier->m_suivant;
	int position = 1;
	while (sentinelle != m_dernier) {
		if (sentinelle->m_el == p_elementATrouver) {
			return position;
		}
		sentinelle = sentinelle->m_suivant;
		position++;
	}
	if (m_dernier->m_el == p_elementATrouver) {
		return m_cardinalite;
	}
}

/**
 * \brief Affiche la liste
 * \param[in, out] p_out Le flux de sortie
 * \param[in] p_liste Une liste
 * \post La liste est inchangée
 * \return Une référence sur le flux de sortie
 */
template<typename T>
std::ostream& operator <<(std::ostream& p_out, const ListeCirculaire<T> & p_liste) {
	if (p_liste.m_dernier == 0)
		p_out << "La liste est vide" << std::endl;
	else
	{
		int nb = 1;
		typename ListeCirculaire<T>::elem courant = p_liste.m_dernier->m_suivant;
		while (courant != p_liste.m_dernier)
		{
			p_out << "Element numero " << nb << ": " << std::endl;
			p_out << courant->m_el;
			courant = courant->m_suivant;
			nb++;
		}
		p_out << "Element numero " << nb << ": " << std::endl;
		p_out << p_liste.m_dernier->m_el;
	}
	return p_out;
}

/**
 * \brief Retourne un pointeur sur le noeud à la position demandé
 * \param[in] p_position La position demandée
 * \return Pointeur sur le noeud à la position demandé
 */
template<typename T>
typename ListeCirculaire<T>::elem ListeCirculaire<T>::_pointeurSurNoeud(
		const int & p_position) const {
	elem sentinelle = m_dernier->m_suivant;
	for (int i = 1; i < p_position; i++) {
		sentinelle = sentinelle->m_suivant;
	}
	return sentinelle;
}

/*
 * \brief Copie profonde d'une liste source
 * \post La liste est copiée
 */
template<typename T>
void ListeCirculaire<T>::_copier(const elem p_source) {
	try {
		m_dernier = new Noeud(p_source->m_el);
		m_dernier->m_suivant = m_dernier;
		m_cardinalite = 1;
		elem sentinelleSurThis = m_dernier;
		for (elem sentinelleSurSource = p_source->m_suivant;
				sentinelleSurSource != p_source; sentinelleSurSource =
						sentinelleSurSource->m_suivant) {
			sentinelleSurThis->m_suivant = new Noeud(sentinelleSurSource->m_el,
					m_dernier);
			m_cardinalite++;
			sentinelleSurThis = sentinelleSurThis->m_suivant;
		}
	} catch (const std::exception & e) {
		_detruire();
		throw;
	}
}
/*
 * \brief Destruction profonde de la liste
 * \post La liste est détruite
 */
template<typename T>
void ListeCirculaire<T>::_detruire() {
	if (m_dernier != 0) {
		elem sentinelle = m_dernier->m_suivant;
		elem remover = sentinelle;
		while (sentinelle != m_dernier) {
			sentinelle = sentinelle->m_suivant;
			remover->m_suivant = 0;
			delete remover;
			remover = sentinelle;
		}
		m_dernier->m_suivant = 0;
		delete m_dernier;
	}
	m_dernier = NULL;
	m_cardinalite = 0;
}

/*
 * \brief Enleve un noeud et gère les liaisons
 * \param[in] Un pointeur sur le noeud AVANT celui à enlever.
 * \post Le noeud est enlevé
 * \post La liste est correctement liée
 */
template<typename T>
void ListeCirculaire<T>::_enlever(elem p_precedentSentinelle) {
	elem sentinelle = p_precedentSentinelle->m_suivant;
// 1 seul element
	if (taille() == 1) {
		m_dernier = 0;
	}
// premier élément
	else if (m_dernier->m_suivant == sentinelle) {
		m_dernier->m_suivant = m_dernier->m_suivant->m_suivant;
	}
// dernier élément
	else if (m_dernier == sentinelle) {
		p_precedentSentinelle->m_suivant = m_dernier->m_suivant;
		m_dernier = p_precedentSentinelle;
		// position quelconque
	} else {
		p_precedentSentinelle->m_suivant = sentinelle->m_suivant;
	}

	sentinelle->m_suivant = 0;
	delete sentinelle;
}
} // fin namespace
