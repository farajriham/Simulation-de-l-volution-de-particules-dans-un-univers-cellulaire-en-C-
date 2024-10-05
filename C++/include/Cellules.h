/**
 * @file Cellules.h
 * @brief Définition de la classe Cellules
 *
 * Ce fichier contient la définition de la classe Cellules,
 * qui représente une cellule dans une grille pour une simulation.
 */
#ifndef CELLULES_H
#define CELLULES_H

#include <map>
#include <unordered_map>
#include <set>
#include "Particle.h"
/**
 * @brief Déclaration anticipée de la classe Particle
 *
 * Permet d'éviter les dépendances cycliques.
 */
template< int dim>
class Particle;

/**
 * @brief Classe représentant une cellule dans une grille pour une simulation.
 * @tparam dim Dimension de l'espace dans lequel la simulation a lieu.
 */
template< int dim>
class Cellules {
    std::set<int> myParticles; /**< Liste des indices des particules contenues dans cette cellule */
    std::array<int,dim> cellId={};/**< Identifiant unique de la cellule */
public :
    static double cellLenght;/**< Longueur de la cellule */


public:
    /**
  * @brief Constructeur de la classe Cellules.
  * @param cellId_ Identifiant de la cellule.
  */
    Cellules(std::array<int,dim>&  cellId_);
    Cellules()=default;
    Cellules(const Cellules & other);
    ~Cellules(); // destructor


    /**
 * @brief Supprime une particule de la cellule.
 * @param indicePar Indice de la particule à supprimer.
 */
    void deleteParticle(int& indicePar);

    /**
 * @brief Ajoute une particule à la cellule.
 * @param indicePar Indice de la particule à ajouter.
 */
    void addParticle(int& indicePar);

    /**
 * @brief Calcule le centre géométrique de la cellule.
 * @return Le vecteur représentant le centre géométrique de la cellule.
 */
    Vecteur<dim> centre();

    /**
 * @brief Obtient l'ensemble des indices des particules contenues dans la cellule.
 * @return Un ensemble contenant les indices des particules.
 */
    std::set<int> getParSet();

    /**
 * @brief Obtient l'identifiant de la cellule.
 * @return L'identifiant de la cellule.
 */
    std::array<int,dim> getcellId();


    /**
  * @brief Constructeur par déplacement (move).
  * @param other La cellule source à déplacer.
  */
    Cellules(Cellules<dim>&& other) noexcept; //  déplacement mémoire

    /**
     * @brief Opérateur d'affectation par déplacement (move assignment).
     * @param other La cellule source à déplacer.
     * @return Une référence vers cette cellule après l'affectation.
     */
    Cellules<dim>& operator=(Cellules<dim>&& other) noexcept; // Recopie par déplacement mémoire

    /**
     * @brief Opérateur d'affectation par copie.
     * @param other La cellule source à copier.
     * @return Une référence vers cette cellule après l'affectation.
     */
    Cellules<dim>& operator=(const Cellules<dim>& other); // Opérateur  recopie

};

extern template class Cellules<1>;
extern template class Cellules<2>;
extern template class Cellules<3>;
#endif //CELLULES_H
