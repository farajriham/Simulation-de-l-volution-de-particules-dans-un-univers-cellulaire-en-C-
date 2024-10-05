//
// Created by ensimag on 3/12/24.
//

#include "/home/ensimag/C++/include/Vecteur.h"
#include <cmath>
#include <iostream>
#include <cstring>


template < int dim>
Vecteur<dim>::Vecteur(std::array<double,dim> value_) {
    for(int i =0; i < dim; i++){
        value[i]=value_[i];
    }
}


template < int dim>
Vecteur<dim>::Vecteur(const Vecteur<dim> &other) {
    for(int i =0; i < dim; i++){
        value[i]=other.getValue()[i];
    }
}

template <int dim>
Vecteur<dim>::~Vecteur() {}

template < int dim>
std::array<double,dim> Vecteur<dim>::getValue() const{
    return value;
}

template <int dim>
void Vecteur<dim>::setValue(std::array<double,dim> value_){
    for(int i =0; i < dim; i++){
        value[i]=value_[i];
    }
}

template <int dim>
double Vecteur<dim>::dist(Vecteur<dim> other) {
    double dist=0;
    for(int i =0; i < dim; i++){
        dist+=(other.value[i]-value[i])*(other.value[i]-value[i]);
    }
    return dist;
}

template <int dim>
Vecteur<dim> Vecteur<dim>::sum(Vecteur<dim> vect) {
    Vecteur<dim> res={};
    for(int i =0; i < dim; i++){
        res.value[i]=value[i]+vect.value[i];
    }
    return res;
}

template <int dim>
Vecteur<dim> Vecteur<dim>::diff(Vecteur<dim> vect) {
    Vecteur<dim> res={};
    for(int i =0; i < dim; i++){
        res.value[i]=value[i]-vect.value[i];
    }
    return res;
}

template < int dim>
Vecteur<dim> Vecteur<dim>::multCoeff(double coeff) {
    Vecteur<dim> res={};
    for(int i =0; i < dim; i++){
        res.value[i]=value[i]*coeff;
    }
    return res;
}

template<int dim>
void Vecteur<dim>::print() {
    std::cout << "les coordonnées sont ( ";
    for(int i =0; i < dim; i++){
        std::cout<<value[i]<<" ";
    }
    std::cout<<" "<<std::endl;
}


template<int dim>
Vecteur<dim>& Vecteur<dim>::operator=(const Vecteur<dim>& other) {
    if (this != &other) {
        value = other.value;
    }
    return *this;
}

template <int dim>
Vecteur<dim>::Vecteur(Vecteur<dim>&& other) noexcept{
    value = std::move(other.value);
}


template <int dim>
Vecteur<dim>& Vecteur<dim>::operator=(Vecteur<dim>&& other) noexcept {
    if (this != &other) {
        value = std::move(other.value);
    }
    return *this;
}

template <int dim>
Vecteur<dim> Vecteur<dim>::operator+(const Vecteur<dim>& other) const {
    Vecteur<dim> result;
    for (int i = 0; i < dim; ++i) {
        result.value[i] = this->value[i] + other.value[i];
    }
    return result;
}

template <int dim>
Vecteur<dim> Vecteur<dim>::operator-(const Vecteur<dim>& other) const {
    Vecteur<dim> result;
    for (int i = 0; i < dim; ++i) {
        result.value[i] = this->value[i] - other.value[i];
    }
    return result;
}

template <int dim>
bool Vecteur<dim>::operator==(const Vecteur<dim>& other) const {
    for (int i = 0; i < dim; ++i) {
        if (this->value[i] != other.value[i]) {
            return false;
        }
    }
    return true;
}

template <int dim>
Vecteur<dim> Vecteur<dim>::operator*(double scalar) const {
    Vecteur<dim> result;
    for (int i = 0; i < dim; ++i) {
        result.value[i] = this->value[i] * scalar;
    }
    return result;
}
template class Vecteur<1>;
template class Vecteur<2>;
template class Vecteur<3>;
