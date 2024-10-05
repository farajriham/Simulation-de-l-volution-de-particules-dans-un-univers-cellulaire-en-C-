/**
 * @file Vecteur.h
 * @brief Définition de la classe Vecteur
 *
 * Ce fichier contient la définition de la classe Vecteur,
 * qui représente un vecteur de dimension N.
 */
#ifndef VECTEUR_H
#define VECTEUR_H

#include <array>
/**
 * @brief Classe représentant un vecteur de dimension N.
 * @tparam dim Dimension du vecteur.
 */

template <int dim>
class Vecteur {
private:
    std::array<double,dim> value; /**< Tableau de valeurs représentant le vecteur */
public:
    /**
   * @brief Constructeur par valeur.
   * @param value_ Les valeurs initiales du vecteur.
   */
    Vecteur(std::array<double,dim> value_);

    /**
 * @brief Constructeur par copie.
 * @param other Le vecteur à copier.
 */
    Vecteur(const Vecteur<dim> &other);

    Vecteur() = default;

    ~Vecteur();

    //Getters
    std::array<double,dim> getValue() const;

    //Setters
    void setValue(std::array<double,dim> value_);

    /**
 * @brief Calcule la distance entre ce vecteur et un autre vecteur.
 * @param other L'autre vecteur.
 * @return La distance entre les deux vecteurs.
 */
    double dist(Vecteur<dim> other);

    /**
 * @brief Calcule la somme de ce vecteur avec un autre vecteur.
 * @param vect L'autre vecteur.
 * @return Le résultat de l'addition.
 */
    Vecteur<dim> sum(Vecteur<dim> vect);

    /**
 * @brief Calcule la différence entre ce vecteur et un autre vecteur.
 * @param vect L'autre vecteur.
 * @return Le résultat de la soustraction.
 */
    Vecteur<dim> diff(Vecteur<dim> vect);

    /**
 * @brief Multiplie ce vecteur par un coefficient.
 * @param coeff Le coefficient de multiplication.
 * @return Le résultat de la multiplication.
 */
    Vecteur<dim> multCoeff(double coeff);

    void print();

    /**
 * @brief Opérateur d'affectation par recopie.
 * @param vect Le vecteur à copier.
 * @return Une référence vers ce vecteur après l'affectation.
 */
    Vecteur<dim> &operator=(const Vecteur<dim> &vect); //operateur de recopie

    /**
 * @brief Constructeur par déplacement (move).
 * @param other Le vecteur source à déplacer.
 */
    Vecteur(Vecteur<dim>&& other) noexcept; // constructeur par move

    /**
     * @brief Opérateur d'affectation par déplacement (move assignment).
     * @param other Le vecteur source à déplacer.
     * @return Une référence vers ce vecteur après l'affectation.
     */
    Vecteur<dim>& operator=(Vecteur<dim>&& other) noexcept; // Move assignment operator



    Vecteur<dim> operator+(const Vecteur<dim>& other) const; // operateur plus

    Vecteur<dim> operator-(const Vecteur<dim>& other) const; // operateur -

    bool operator==(const Vecteur<dim>& other) const; // operateur ==

    Vecteur<dim> operator*(double scalar) const; // operateur multiplication


};
extern template class Vecteur<1>;
extern template class Vecteur<2>;
extern template class Vecteur<3>;

#endif //VECTEUR_H

