#include "/home/ensimag/C++/include/Particle.h"
#include <cmath>
#include<iostream>
#include <tuple>
#include "/home/ensimag/C++/include/Vecteur.h"
#include "/home/ensimag/C++/include/Cellules.h"

#include <iterator>
#include <random>

template<int dim>
Particle<dim>::Particle(const Vecteur<dim>& position_,
                        const Vecteur<dim>& vitesse_,
                        const double m_,
                        const double id_,
                        const std::string& category_,
                        const Vecteur<dim>& force_,
                        const Vecteur<dim>& forceOld_){
    position =  Vecteur(position_);
    vitesse = Vecteur(vitesse_);
    force = Vecteur(force_);
    m = m_ ;
    id = id_ ;
    category = category_;
    old_force = Vecteur(forceOld_);
}


//le destructeur n'as pas besoin de faire f=grand chose le destructeur par defaut fait le boulot
template <int dim>
Particle<dim>::~Particle(){

}

// Getters
template <int dim>
Vecteur<dim> Particle<dim>::getPosition() const { return position; }

template <int dim>
Vecteur<dim> Particle<dim>::getVitesse() const { return vitesse; }

template <int dim>
double Particle<dim>::getMass() const { return m; }


template <int dim>
std::string Particle<dim>::getCategory() const { return category; }

template <int dim>
Vecteur<dim> Particle<dim>::getForce() const { return force; }




template<int dim>
void Particle<dim>::setForce(const Vecteur<dim>& force_) { force = Vecteur(force_); }

template<int dim>
void Particle<dim>::setForceOld(const Vecteur<dim>& oldForce_){old_force = Vecteur(oldForce_);}


template<int dim>
bool Particle<dim>::position_maj(double dt, std::array<double, dim> longCaract, double rayonCoupe) {
    std::array<int, dim> cell_old={};
    std::array<int, dim> cell_new={};
    std::array<double,dim> value={};
    for (int i = 0; i < dim; i++) {
        cell_old[i] = position.getValue()[i] / Cellules<dim>::cellLenght + 1;
    }

    Vecteur<dim> parenthese = (force.multCoeff(0.5 * dt / m)).sum(vitesse);
    Vecteur<dim> res = position.sum(parenthese.multCoeff(dt));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribH(0, rayonCoupe);

    std::vector<std::uniform_real_distribution<double>> distribB(dim);
    for (int i = 0; i < dim; i++) {
        distribB[i] = std::uniform_real_distribution<double>(longCaract[i] - rayonCoupe, longCaract[i]);
    }

    for (int i = 0; i < dim; i++) {
        if (res.getValue()[i] > longCaract[i]) {
            value[i] = distribH(gen);
        }
        else if (res.getValue()[i] < 0) {
            value[i] =  distribB[i](gen);
        } else{
            value[i] = res.getValue()[i];
        }

    }
    res.setValue(value);

    for (int i = 0; i < dim; i++) {
        cell_new[i] = res.getValue()[i] / Cellules<dim>::cellLenght + 1;
    }

    position = res;

    for (int i = 0; i < dim; i++) {
        if (cell_new[i] != cell_old[i]) {
            return true;
        }
    }
    return false;
}



template<int dim>
void Particle<dim>::vitesse_maj(double dt) {
    Vecteur<dim> par = force.sum(old_force);
    Vecteur<dim> par2 = par.multCoeff(dt * 0.5 / m);
    Vecteur<dim> res = vitesse.sum(par2);
    vitesse = res;
}


template<int dim>
void Particle<dim>::maj_forceIJPot(Particle<dim>& other, double sigma, double epsilon, double rayonCoupe) {
    double distance = position.dist(other.position);
    if (distance > rayonCoupe*rayonCoupe || distance == 0) {
        return;
    } else {
        Vecteur<dim> rij = other.position.diff(position);
        double coeff1 = pow(sigma, 6) / pow(distance, 6);
        double coeff2 = 1 - 2 * pow(sigma, 6) / pow(distance, 3);
        Vecteur<dim> res = rij.multCoeff(24 * epsilon * coeff1 * coeff2);
        force = force.sum(res);
        std::array<double,dim> val = {};
        for (int i =0 ; i<dim ; i++){
            if (force.getValue()[i] >1000){
                val[i]= 1000;
            }
            else if( force.getValue()[i] < -1000){
                val[i]= -1000;
            }
            else{
                val[i]= force.getValue()[i];
            }
        }
        force.setValue(val);
    }
}

template <int dim>
std::array<int,dim> Particle<dim>::ParticleCell(const std::array<double,dim>& longCaract) {
    std::array<int,dim> cellId={};

    for (int i = 0; i < dim; ++i) {
        double position_i = position.getValue()[i];
        cellId[i] = static_cast<int>(position_i / Cellules<dim>::cellLenght) + 1;

        if (position_i == longCaract[i]) {
            cellId[i] -= 1;
        }
    }

    return cellId;
}
/*
 *
template <int dim>
Particle<dim>::Particle(Particle<dim>&& other) noexcept
        : position(std::move(other.position)),
          vitesse(std::move(other.vitesse)),
          force(std::move(other.force)),
          old_force(std::move(other.old_force)),
          m(other.m),  // m et id sont double , leur constructeur deplacement memeoire est prédefinie ,, mm chose pour catégorie
          id(other.id),
          category(std::move(other.category)) {

}

template <int dim>
Particle<dim>& Particle<dim>::operator=(Particle<dim>&& other) noexcept {
    if (this != &other) {
        position = std::move(other.position); //recopie par deplacement mémoire est déja définie pour Vecteur
        vitesse = std::move(other.vitesse);
        force = std::move(other.force);
        old_force = std::move(other.old_force);
        m = other.m;  //prédefinie pour double et string
        id = other.id;
        category = std::move(other.category);
    }
    return *this;
}

template <int dim>
Particle<dim>& Particle<dim>::operator=(const Particle<dim>& other) {
    if (this != &other) {
        position = other.position; // l'operateur = est définie pour la classe Vecteur
        vitesse = other.vitesse;
        force = other.force;
        old_force = other.old_force;
        m = other.m;
        id = other.id;
        category = other.category;
    }
    return *this;
} */


template class Particle<1>;
template class Particle<2>;
template class Particle<3>;



