//
// Created by ensimag on 3/23/24.
//

#include "/home/ensimag/C++/include/Cellules.h"
#include <iterator>
#include <iostream>
#include <functional>
template <int dim>
double Cellules<dim>::cellLenght=1;

template <int dim>
Cellules<dim>::Cellules(std::array<int,dim>& cellId_){
    cellId=cellId_;
}

template <int dim>
Cellules<dim>::~Cellules(){
}

template <int dim>
void Cellules<dim>::deleteParticle(int& indicePar){
    myParticles.erase(indicePar);
}

template <int dim>
Cellules<dim>::Cellules(const Cellules & other){
    cellLenght = other.cellLenght;
    cellId = other.cellId; //copie du tuple
    myParticles = other.myParticles;
    //index = other.index;
}

//Cellules& operator=(const Cellules& other){ return other};

template <int dim>
void Cellules<dim>::addParticle(int& indicePar) {

    myParticles.insert(indicePar);
}

template <int dim>
Vecteur<dim> Cellules<dim>::centre() {
    std::array<double, dim> coords={};

    for (int i = 0; i < dim; i++) {
        coords[i] = cellLenght * (cellId[i] - 0.5);
    }

    return Vecteur<dim>(coords);
}


template <int dim>
std::set<int> Cellules<dim>::getParSet(){
    return myParticles;
}

template <int dim>
std::array<int,dim> Cellules<dim>::getcellId(){
    return cellId;
}

template <int dim>
Cellules<dim>::Cellules(Cellules<dim>&& other) noexcept
        : myParticles(std::move(other.myParticles)), // deja definie pour la classe Particle
          cellId(std::move(other.cellId)) {
}

template <int dim>
Cellules<dim>& Cellules<dim>::operator=(Cellules<dim>&& other) noexcept {
    if (this != &other) {
        myParticles = std::move(other.myParticles);
        cellId = std::move(other.cellId);
    }
    return *this;
}

template <int dim>
Cellules<dim>& Cellules<dim>::operator=(const Cellules<dim>& other) {
    if (this != &other) {
        myParticles = other.myParticles;
        cellId = other.cellId;
    }
    return *this;
}

template class Cellules<1>;
template class Cellules<2>;
template class Cellules<3>;
