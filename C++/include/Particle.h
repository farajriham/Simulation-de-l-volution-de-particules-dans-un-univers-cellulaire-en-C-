/**
 * @file Particle.h
 * @brief Définition de la classe Particle
 *
 * Ce fichier contient la définition de la classe Particle,
 * qui représente une particule dans un système de simulation.
 */

#ifndef PARTICLE_H
#define PARTICLE_H
#include <vector>
#include<string>
#include "Vecteur.h"
#include "Cellules.h"

/**
 * @brief Déclaration anticipée de la classe Cellules
 *
 * Permet d'éviter les dépendances cycliques.
 */
template< int dim>
class Cellules;

/**
 * @brief Classe représentant une particule dans un système de simulation.
 * @tparam dim Dimension de l'espace dans lequel la particule évolue.
 */
template< int dim>
class Particle{
private:
    Vecteur<dim> position; /**< Position de la particule */
    Vecteur<dim> vitesse; /**< Vitesse de la particule */
    Vecteur<dim> force; /**< Force agissant sur la particule */
    Vecteur<dim> old_force;/**< Ancienne force agissant sur la particule */
    double m; /**< Masse de la particule */
    double id; /**< Identifiant unique de la particule */
    std::string category; /**< Catégorie de la particule */


public:
    /**
     * @brief Constructeur de la classe Particle.
     * @param position_ Position initiale de la particule.
     * @param vitesse_ Vitesse initiale de la particule.
     * @param m_ Masse de la particule.
     * @param id_ Identifiant unique de la particule.
     * @param category_ Catégorie de la particule.
     * @param force_ Force initiale agissant sur la particule.
     * @param forceOld_ Ancienne force agissant sur la particule.
     */
    Particle(const Vecteur<dim>& position_,
             const Vecteur<dim>& vitesse_,
             const double m_,
             const double id_,
             const std::string& category_,
             const Vecteur<dim>& force_,
             const Vecteur<dim>& forceOld_);

    /**
     * @brief Constructeur par défaut.
     */
    Particle () = default;

    //destructeur
    ~Particle();

    // Getters
    Vecteur<dim> getPosition() const;
    Vecteur<dim> getVitesse() const;
    double getMass() const;
    std::string getCategory() const;
    Vecteur<dim> getForce() const;

    // Setters
    void setForce(const Vecteur<dim>& force_) ;
    void setForceOld(const Vecteur<dim>& oldForce_);


    /**
 * @brief Met à jour la position de la particule en fonction du temps.
 * @param dt Intervalle de temps.
 * @param longCaract Longueur caractéristique du système.
 * @param rayonCoupe Rayon de coupure pour les interactions.
 * @return true si la position a été mise à jour avec succès, sinon false.
 */
    bool position_maj(double dt,std::array<double,dim> longCaract , double rayonCoupe);
    /**
 * @brief Met à jour la vitesse de la particule en fonction du temps.
 * @param dt Intervalle de temps.
 */
    void vitesse_maj(double dt);

    /**
     * @brief Met à jour la force entre cette particule et une autre particule en fonction de la distance.
     * @param other L'autre particule.
     * @param sigma Paramètre sigma pour le potentiel de Lennard-Jones.
     * @param epsilon Paramètre epsilon pour le potentiel de Lennard-Jones.
     * @param rayonCoupe Rayon de coupure pour le potentiel de Lennard-Jones.
     */
    void maj_forceIJPot (Particle<dim>& other,double sigma,double epsilon,double rayonCoupe);

    /**
 * @brief Calcule la cellule dans laquelle se trouve la particule.
 * @param longCaract Longueur caractéristique du système.
 * @return Les indices de la cellule dans laquelle se trouve la particule.
 */
    std::array<int,dim> ParticleCell(const std::array<double,dim>& longCaract);

};

extern template class Particle<1>;
extern template class Particle<2>;
extern template class Particle<3>;

#endif
