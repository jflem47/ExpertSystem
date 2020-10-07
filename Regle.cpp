/////////////////////////////////////////////////////////////////////////////
//Fichier Regle.cpp
/////////////////////////////////////////////////////////////////////////////
/**
 * \file Regle.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Regle
 * \author Jean-Francois Lemieux 111 156 490
 * \version 0.5
 * \date juin 2020
 *
 */

#include "Regle.h"

namespace tp1
{
    /**
     * \brief Constructeur par défaut de la classe Regle.
     * \return Une instance d'un objet Regle.
     */
     Regle::Regle()
     : premisses(), conclusions()
     {};

     /**
      * \brief Constructeur de copie de la classe Regle.
      * \param[in] r Un objet Regle
      * \pre r doit être un objet Regle valide.
      * \post premisses == r.premisse et conclusions == r.conclusions.
      * \return Une instance d'un objet Regle.
      */
     Regle::Regle(const Regle& r)
     :  premisses(r.premisses), conclusions(r.conclusions)
     {};

     /**
      * \brief Destructeur de la classe Regle.
      */
     Regle::~Regle()
     {};

     /**
      * \brief Surcharge de l'opérateur =
      * @param r Une instance d'un objet Regle
      * \pre r doit être un objet Regle valide.
      * \post conclusions == r.conclusions et premisses == r.premisses.
      * @return L'objet de base modifié avec les attributs de l'objet passé en paramètre.
      */
     Regle & Regle::operator=(const Regle &r) {
         conclusions = r.conclusions;
         premisses = r.premisses;
     }

     /**
      * \brief Surcharge de l'opérateur ==
      * @param r Une instance d'un objet Regle
      * \pre r doit être un objet Regle valide.
      * \post Les deux instances doivent être inchangées.
      * @return Un boooléen signifiant si l'objet de base est identique ou non à l'objet Regle passé en paramètre.
      */
     bool Regle::operator==(const Regle &r) const {
         return (conclusions == r.conclusions && premisses == r.premisses);
     }

     /**
      * \brief Surcharge de l'opérateur !=
      * @param r Une instance d'un objet Regle
      * \pre r doit être un objet Regle valide.
      * \post Les deux instances doivent être inchangées.
      * @return un booléen signifiant si l'objet de base est différent ou non de l'objet Regle passé en paramètre.
      */
     bool Regle::operator!=(const Regle &r) const {
         return (premisses != r.premisses && conclusions != r.conclusions);
     }

}

