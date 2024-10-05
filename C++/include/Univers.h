/**
 * @file Univers.h
 * @brief Définition de la classe Univers
 *
 * Ce fichier contient la définition de la classe Univers,
 * qui représente un univers de particules dans une simulation.
 */
#ifndef UNIVERS_H
#define UNIVERS_H


#include <vector>
#include "Particle.h"
#include "Cellules.h"


#include <iterator>
#include <iostream>
#include <fstream>
#include <filesystem>

/**
 * @class Univers
 * @brief Classe représentant un univers de particules.
 * @tparam dim Dimension de l'univers.
 */
template< int dim>
class Univers {
private:
    std::map<std::array<int,dim>,Cellules<dim>> Cells ;/**< Grille de cellules contenant les particules */
    std::vector<Particle<dim>>& Particles;/**< Liste des particules de l'univers */
    int nbParticles;/**< Nombre total de particules */
    double epsylon;/**< Paramètre epsilon pour le potentiel de Lennard-Jones */
    double sigma;/**< Paramètre sigma pour le potentiel de Lennard-Jones */
    std::array<double,dim> longCaract;/**< Longueur caractéristique de l'univers */
    double rayonCoupe;/**< Rayon de coupure pour les interactions */
    std::array<double,dim> nb_cellule;/**< Nombres de cellules totales de cet univers */

public:
    /**
  * @brief Constructeur de la classe Univers.
  * @param particles Liste des particules de l'univers.
  * @param nb_Particles Nombre total de particules.
  * @param epsilon_ Paramètre epsilon pour le potentiel de Lennard-Jones.
  * @param sigma_ Paramètre sigma pour le potentiel de Lennard-Jones.
  * @param longCaract_ Longueur caractéristique de l'univers.
  * @param rayonCoup Rayon de coupure pour les interactions.
  */
    Univers(std::vector<Particle<dim>>& particles,
            int nb_Particles, double epsilon_,
            double sigma_, std::array<double,dim> longCaract_,double rayonCoup);
    Univers()= default;
    ~Univers();

    //getters
    /**
 * @brief Obtient la grille de cellules de l'univers.
 * @return La grille de cellules.
 */
    std::map<std::array<int,dim>,Cellules<dim> >  getUnivers ();

    /**
   * @brief Obtient les cellules voisines d'une cellule donnée dans la grille.
   * @param cell La cellule dont on veut obtenir les voisins.
   * @return Un vecteur contenant les indices des cellules voisines.
   */
    std::vector<std::array<int,dim>> getNeighbour(Cellules<dim> cell);

    /**
   * @brief Met à jour les forces des particules .
   */
    void evolution();

    /**
 * @brief Exécute l'algorithme de Störmer-Verlet pour une durée donnée avec un pas de temps donné.
 * @param t_end Durée totale de la simulation.
 * @param dt Pas de temps de la simulation.
 */
    void stromer_verlet(double t_end,double dt);

    /**
 * @brief Affiche les données du haut de l'univers dans un fichier au format VTK.
 * @param t Instant de la simulation.
 * @param i Indice du fichier.
 *
 * Cette méthode génère un fichier au format VTK contenant l'entête du fichier .vtu
 */
    void printHaut(double t, int i );

    /**
 * @brief Affiche les données du bas de l'univers dans un fichier au format VTK.
 * @param t Instant de la simulation.
 * @param i Indice du fichier.
 *
 * Cette méthode génère un fichier au format VTK contenant les données du bas du fichier ( masse...)
 */
    void printBas(double t, int i );



/**
 * @brief Affiche les données du milieu c'est à dire le texte décrivant les vitesses des particules de l'univers dans un fichier au format VTK.
 * @param t Instant de la simulation.
 * @param i Indice du fichier.
 *
 * Cette méthode génère un fichier au format VTK contenant les données du milieu du fichier(masse...)
 */
    void printMilieu1(double t ,int i);

    Univers(Univers<dim>&& other) noexcept;
    Univers<dim>& operator=(const Univers<dim>& other);
    Univers<dim>& operator=(Univers<dim>&& other) noexcept;

};



template <int dim>
Univers<dim>::Univers(std::vector<Particle<dim>>& particles,
                      int nb_Particles, double epsilon_,
                      double sigma_,std::array<double,dim> longCaract_,double rayonCoup)
        :Particles(particles),
         nbParticles(nb_Particles),
         epsylon(epsilon_),
         sigma(sigma_),
         longCaract(longCaract_),
         rayonCoupe(rayonCoup)
{


    //creation des cellules de l univers une fois pour tt
    Cellules<dim>::cellLenght=rayonCoup;
    switch (dim) {
        case 1:{

            std::array<int,dim>  cooor;
            nb_cellule={longCaract_[0]/rayonCoup};
            int nbr_cellules=nb_cellule[0];
            for(int i=0 ; i<nbr_cellules;i++){
                cooor[0] = i+1;
                Cellules<dim> cell= Cellules<dim>(cooor);
                Cells.insert(std::make_pair(cooor,cell));
            }
            break;
        }

        case 2:{
            nb_cellule = {longCaract_[0]/rayonCoup, longCaract_[1]/rayonCoup};
            int nbr_cellules_x=nb_cellule[0];
            int nbr_cellules_y=nb_cellule[1];
            std::array<int,dim>  cooor;

            for(int i=0 ; i<nbr_cellules_x;i++) {
                for (int j = 0; j < nbr_cellules_y; j++) {
                    cooor[0]= i+1; cooor[1]=j+1;
                    Cellules<dim> cell = Cellules<dim>(cooor);
                    Cells.insert(std::make_pair(cooor,cell));
                }
            }
            break;
        }

        case 3:{
            /*nb_cellule={longCaract_[0]/rayonCoup,longCaract_[1]/rayonCoup,longCaract_[2]/rayonCoup};
            std::array<int,dim>  cooor;
            int nb_cellules_x=nb_cellule[0];
            int nb_cellules_y=nb_cellule[1];
            int nb_cellules_z=nb_cellule[2];*/
            std::array<int,dim>  cooor;

            for(int i=0 ; i<=longCaract_[0]/rayonCoup;i++) {
                for (int j = 0; j <= longCaract_[1]/rayonCoup; j++) {
                    for(int k = 0; k <=longCaract_[2]/rayonCoup; k++){
                        cooor[0]= i+1; cooor[1]=j+1; cooor[2]=k+1;
                        Cellules<dim> cell = Cellules<dim>(cooor);
                        Cells.insert(std::make_pair(cooor,cell));
                    }
                }
            }
            break;
        }


        default :{
            std::cout << "Dimension invalid"<<std::endl;
            break;

        }

    }

    for(int i=0;i<particles.size();i++){
        Particle<dim> parCr = particles[i];
        std::array<int,dim> coor = parCr.ParticleCell(longCaract);
        auto it = Cells.find(coor);
        if(it!=Cells.end()){
            it->second.addParticle(i);
        }
        else{
            std::cout<<"cellule not found :/// , particule was not added to the right cell"<<std::endl;
        }
    }

}

template <int dim>
Univers<dim>::~Univers(){}

//getters
template <int dim>
std::map<std::array<int,dim>,Cellules<dim>>  Univers<dim>::getUnivers (){return Cells;}

template <int dim>
std::vector< std::array<int,dim> > Univers<dim>::getNeighbour(Cellules<dim> cell){
    std::vector<std::array<int,dim>> ret;
    std::array<int, dim> cor;
    std::vector<int> offsets={-1,0,1};

    switch(dim){
        case 1:{

            int nb_cellules_x=nb_cellule[0];
            for(int xOffset : offsets){
                int x=cell.getcellId()[0]+xOffset;
                cor[0] = {x};
                if (x>0 && x<=nb_cellules_x){
                    ret.push_back(cor);
                }
            }
        }
        case 2:{
            int nb_cellules_x=nb_cellule[0];
            int nb_cellules_y=nb_cellule[1];
            for(int xOffset : offsets) {
                for (int yOffset: offsets) {
                    int x=cell.getcellId()[0]+xOffset;
                    int y=cell.getcellId()[1]+yOffset;
                    cor[0]=x; cor[1]=y;
                    if (x>0 && x<=nb_cellules_x && y>0 && y<=nb_cellules_y){
                        ret.push_back(cor);
                    }
                }
            }
        }
        case 3:{
            int nb_cellules_x=nb_cellule[0];
            int nb_cellules_y=nb_cellule[1];
            int nb_cellules_z=nb_cellule[2];
            for(int xOffset : offsets) {
                for (int yOffset: offsets) {
                    for (int zOffset: offsets) {
                        int x = cell.getcellId()[0] + xOffset;
                        int y = cell.getcellId()[1] + yOffset;
                        int z = cell.getcellId()[2] + zOffset;
                        cor[0]=x; cor[1]=y; cor[2] =z;
                        if (x > 0 && x <= nb_cellules_x && y > 0 && y <= nb_cellules_y && z > 0 && z <= nb_cellules_z) {
                            ret.push_back(cor);
                        }
                    }
                }
            }
        }
            break;
    }
    return ret ;
}
template <int dim>
void Univers<dim>::evolution() {
    //parcours des cellules de l'univers
    for(auto it=Cells.begin();it != Cells.end(); ++it){
        //recuperation des voisins de la cellule courante (map)
        std::vector< std::array<int,dim> > voisins= this->getNeighbour(it->second);
        // pour les particules de la cellule courante , elle interagit avec la collection des voisins de la cell courante
        auto parSet = (it->second).getParSet(); // vecteur des indices des  particules stocké dans la cellule courantes
        for(int i:parSet){
            for (auto vois_it=voisins.begin();vois_it!=voisins.end();++vois_it){
                auto cellula = Cells.find(*vois_it);
                Vecteur centre_cell = (cellula->second).centre();
                Vecteur pos=Particles[i].getPosition();
                if(centre_cell.dist(pos)<rayonCoupe*rayonCoupe){
                    for (int j : (cellula->second).getParSet()){
                        Particles[i].maj_forceIJPot(Particles[j],sigma,epsylon,rayonCoupe);
                    }
                }
            }
        }
    }
}
template <int dim>
void Univers<dim>::stromer_verlet(double t_end,double dt) {
    double t = 0;

    namespace fs = std::filesystem;
    std::ostringstream fileNameStream;
    // Nom du répertoire
    std::string directory = "/home/ensimag/C++/demo";

    // Vérifie si le répertoire existe, sinon le crée
    if (!fs::exists(directory)) {
        if (!fs::create_directory(directory)) {
            std::cerr << "Erreur: impossible de créer le répertoire " << directory << std::endl;
            return;
        }
    }

    int compteur = 0;
    /*this->printHaut(t, compteur);
    for (Particle<dim> parti : Particles){
        creer le fichier pour l'instant 0
    }*/

    // calcul des forces pour chaque particules
    std::cout << "started stromer verlet , now time for evolution for first time " << std::endl;
    this->evolution();

    while (t < t_end) {
        t += dt;
        compteur++;
        this->printHaut(t, compteur);
        std::ostringstream fileNameS;

        fileNameS << "data_" << compteur << ".vtu";
        std::string fileName = fileNameS.str();

        // Chemin complet du fichier
        std::string filePath = directory + "/" + fileName;

        std::ofstream outFile(filePath, std::ios_base::app); // Open file in append mode
        if (!outFile) {
            std::cerr << "Erreur: impossible de créer ou d'ouvrir le fichier " << filePath << std::endl;
            return;
        }

        for (auto it = Cells.begin(); it != Cells.end(); ++it) {

            //Parcours des cellules
            auto parVect = (it->second).getParSet(); // map des particules de la cellule courante
            for (int indicePar:parVect) { // parcours des indices des particules stocké dans la cellule courante
                //parcours des particules des cellules
                if (Particles[indicePar].position_maj(dt,longCaract,rayonCoupe)) { // mise à jour de la position et return boolean si la particule a changé de cellule
                    //si la particule a changé de cellule
                    //ajoute la particule dans la cellule convenable
                    (it->second).deleteParticle(indicePar);
                    std::array<int,dim> coor = Particles[indicePar].ParticleCell(longCaract);
                    auto it = Cells.find(coor);
                    if(it!=Cells.end()){
                        (it->second).addParticle(indicePar);
                    }
                    else{
                        std::cout<<"cellule not found :/// , particule was not added to the right cell"<<std::endl;
                    }
                }
                Vecteur var = Particles[indicePar].getPosition();
                //outFile <<"Helloooooooo"<<std::endl;
                for (int i = 0; i < dim; ++i) {
                    outFile << var.getValue()[i] << " ";
                }
                for (int i = dim ; i<3 ; i++){
                    outFile << 0 << " ";
                }
                //outFile << 0 << " ";
                outFile << std::endl;

                Particles[indicePar].setForceOld(Particles[indicePar].getForce());

                Particles[indicePar].setForce(Vecteur<dim>(std::array<double,dim> {}));
                // lorsque initialisé par accolades , il est remplie par des 0
            }

        }
        this->printMilieu1(t, compteur);

        this->evolution();

        for (auto it = Cells.begin(); it != Cells.end(); ++it) { // parcours des ceulles de l'univers
            auto parSet = (it->second).getParSet(); // Stockez la carte de particules localement
            for (int indicePart : parSet) {
                Particles[indicePart].vitesse_maj(dt); // mise à jour des vitesses
                Vecteur vitesse = Particles[indicePart].getVitesse();

                for (int i = 0; i < dim; ++i) {
                    outFile << vitesse.getValue()[i] << " ";
                    //outFile << 0 << " ";
                }
                for (int i = dim ; i<3 ; i++){
                    outFile << 0 << " ";
                }
                //outFile << 0 << " ";
                outFile << std::endl;

                std::cout << "Pour la particle d'id =  " << Particles[indicePart].getCategory() << ", ";
                std::cout << "t = " << t << "\n";
                (Particles[indicePart].getPosition()).print();
            }
        }

        outFile.close();

        this->printBas(t, compteur);



    }

}


// Constructeur de déplacement
template<int dim>
Univers<dim>::Univers(Univers<dim>&& other) noexcept
        : Cells(std::move(other.Cells)),
          Particles(std::move(other.Particles)),
          nbParticles(other.nbParticles),
          epsylon(other.epsylon),
          sigma(other.sigma),
          longCaract(std::move(other.longCaract)),
          rayonCoupe(other.rayonCoupe),
          nb_cellule(std::move(other.nb_cellule)) {}


// Opérateur d'affectation par copie
template<int dim>
Univers<dim>& Univers<dim>::operator=(const Univers<dim>& other) {
    if (this != &other) {
        Cells = other.Cells;
        Particles = other.Particles;
        nbParticles = other.nbParticles;
        epsylon = other.epsylon;
        sigma = other.sigma;
        longCaract = other.longCaract;
        rayonCoupe = other.rayonCoupe;
        nb_cellule = other.nb_cellule;
    }
    return *this;
}

// Opérateur d'affectation par déplacement
template<int dim>
Univers<dim>& Univers<dim>::operator=(Univers<dim>&& other) noexcept {
    if (this != &other) {
        Cells = std::move(other.Cells);
        Particles = std::move(other.Particles);
        nbParticles = other.nbParticles;
        epsylon = other.epsylon;
        sigma = other.sigma;
        longCaract = std::move(other.longCaract);
        rayonCoupe = other.rayonCoupe;
        nb_cellule = std::move(other.nb_cellule);
    }
    return *this;
}

template <int dim>
void Univers<dim>::printHaut(double t, int i){
    namespace fs = std::filesystem;
    std::ostringstream fileNameStream;
    /*int total = 1;
    for (int i = 0 ; i<dim ; i++){
        total+= nb_cellule[i];
    }*/

    // Nom du répertoire
    std::string directory = "/home/ensimag/C++/demo";

    // Vérifie si le répertoire existe, sinon le crée
    if (!fs::exists(directory)) {
        if (!fs::create_directory(directory)) {
            std::cerr << "Erreur: impossible de créer le répertoire " << directory << std::endl;
            return ;
        }
    }
    fileNameStream << "data_" << i << ".vtu";
    std::string fileName = fileNameStream.str();

    // Chemin complet du fichier
    std::string filePath = directory + "/" + fileName;


    // Crée et ouvre le fichier en écriture
    std::ofstream outFile(filePath);

    if (!outFile) {
        std::cerr << "Erreur: impossible de créer ou d'ouvrir le fichier " << filePath << std::endl;
        return ;
    }

    // Écrit le contenu dans le fichier
    outFile << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"BigEndian\">\n"
            << "  <UnstructuredGrid>\n"
            << "        <Piece NumberOfPoints=\"" << nbParticles << "\" NumberOfCells=\"" << 0 << "\" Time= \"" << t << "\">"
            << "      <Points>\n"
            << "        <DataArray name=\"Position\" type=\"Float32\"  NumberOfComponents= \"" << 3 << "\"  format=\"ascii\">\n" << std::endl;
    // Ferme le fichier
    outFile.close();

}
template <int dim>
void Univers<dim>::printBas(double t , int i){
    namespace fs = std::filesystem;
    std::ostringstream fileNameStream;

    // Nom du répertoire
    std::string directory = "/home/ensimag/C++/demo";

    fileNameStream << "data_" << i << ".vtu";
    std::string fileName = fileNameStream.str();

    // Chemin complet du fichier
    std::string filePath = directory + "/" + fileName;


    // Crée et ouvre le fichier en écriture
    std::ofstream outFile(filePath, std::ios_base::app);

    // Écrit le contenu dans le fichier
    outFile << "        </DataArray>\n"
            << "        <DataArray type=\"Float32\" Name=\"Masse\" format=\"ascii\">\n" << std::endl;

    for (auto it = Cells.begin(); it != Cells.end(); ++it) {
        auto parVect = (it->second).getParSet(); // map des particules de la cellule courante
        for (int indicePar : parVect) {
            outFile << Particles[indicePar].getMass() << "\n" ;
        }
    }
    outFile << "        </DataArray>\n" //juste après print des masses
            << "      </PointData>\n"
            << "      <Cells>\n"
            << "        <DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\n"
            << "        </DataArray>\n"
            << "        <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\n"
            << "        </DataArray>\n"
            << "        <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n"
            << "        </DataArray>\n"
            << "      </Cells>\n"
            << "    </Piece>\n"
            << "  </UnstructuredGrid>\n"
            << "</VTKFile>\n";
    outFile.close();
}
template <int dim>
void Univers<dim>::printMilieu1(double t , int i){
    namespace fs = std::filesystem;
    std::ostringstream fileNameStream;

    // Nom du répertoire
    std::string directory = "/home/ensimag/C++/demo";

    // Vérifie si le répertoire existe, sinon le crée
    fileNameStream << "data_" << i << ".vtu";
    std::string fileName = fileNameStream.str();

    // Chemin complet du fichier
    std::string filePath = directory + "/" + fileName;

    // Crée et ouvre le fichier en écriture
    std::ofstream outFile(filePath, std::ios_base::app);

    outFile << "        </DataArray>\n"
            << "      </Points>\n"
            << "      <PointData Vectors=\"vector\">\n"
            << "        <DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\""  << 3 << "\" format=\"ascii\">\n" << std::endl;
    outFile.close();
}

#endif //UNIVERS_H
