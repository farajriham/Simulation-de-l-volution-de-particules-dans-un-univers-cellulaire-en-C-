#include <random>
#include <iostream>
#include "/home/ensimag/C++/include/Particle.h"
#include <chrono>
#include "/home/ensimag/C++/include/Vecteur.h"
#include "/home/ensimag/C++/include/Univers.h"
#include <cmath>
#include <vector>


using namespace std;

void expensive_function() {
    for (int i = 0; i < 10000000; ++i) {
        // Effectue un calcul coûteux
        double result = std::sin(i) * std::cos(i);
        result = std::log(result + 1.0);
    }
}

double lennardJonesPotential(double r) {
    double epsilon = 1.0; // Profondeur du potentiel
    double sigma = 1.0; // Interaction avec l'axe nul du potentiel

    double term1 = 4/pow( r, 6);
    double term2 = 1/pow(r, 6) - 1;
    return term1 * term2;
}

int main(){

    //Univers monUnivers = Univers(3);
    std::array<double,2> longCaract_ = {250.,40.};


    std::vector<Particle<2>> particles;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribxCarre(123,127);
    std::uniform_real_distribution<double> distribyCarre(10,14);

    std::uniform_real_distribution<double> distribyRect(14+pow(2,1/6),18+pow(2,1/6));
    std::uniform_real_distribution<double> distribxRect(115,135);

    auto start = std::chrono::high_resolution_clock::now();
    std::array<double,2> vitCar={0.,10.};
    std::array<double,2> zero={0.,0.};
    for (int i = 0; i<40*40 ; i++){

        double x = distribxCarre(gen);
        double y = distribyCarre(gen);
        std::array<double,2> vect={x,y};
        //std::cout<<"(x,y,z,i )" << x << y << z << i << std::endl;
        particles.push_back(Particle(Vecteur<2>(vect),Vecteur<2>(vitCar),1,i,"cat",Vecteur<2>(zero),Vecteur<2>(zero)));
        // meme vitesse, meme masse , old force et force sont initialement nuls , id = i et categorie ="category"
    }
    for (int i = 0; i<160*40 ; i++){

        double x = distribxRect(gen);
        double y = distribyRect(gen);
        std::array<double,2> vect={x,y};

        //std::cout<<"(x,y,z,i )" << x << y << z << i << std::endl;
        particles.push_back(Particle<2>(Vecteur<2>(vect),Vecteur<2>(zero),1,i,"cat",Vecteur<2>(zero),Vecteur<2>(zero)));
        // meme vitesse, meme masse , old force et force sont initialement nuls , id = i et categorie ="category"
    }
    Univers<2> monUnivers = Univers<2>(particles,8000, 5,1,longCaract_, 2.5);


    std::cout<< "Univers created succesfully , now time for stromer verlet  "<<std::endl;

    /*monUnivers.Evolution(1,1);*/
    monUnivers.stromer_verlet(0.5,0.005);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Temps d'insertion pour " << 8000 << " particules : " << elapsed_seconds.count() << " secondes" << std::endl;




    std::cout << "Fin du programme" << std::endl;

}

/*int main() {
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> dist_position(-10.0, 10.0); // Plage de valeurs pour les positions
std::uniform_real_distribution<double> dist_vitesse(-1.0, 1.0); // Plage de valeurs pour les vitesses
std::uniform_real_distribution<double> dist_masse(0.1, 10.0); // Plage de valeurs pour les masses
std::uniform_real_distribution<double> dist_force(-5.0, 5.0); // Plage de valeurs pour les composantes de la force
std::uniform_int_distribution<int> dist_id(1, 100); // Plage de valeurs pour les identifiants
std::vector<std::string> categories = {"Type1", "Type2", "Type3", "Type4"}; // Catégories de particules possibles


    //Analyse d eperformances
    for (int size = 64; size <= 2048; size *= 2) {
        std::vector<Particle> particles;

        auto start = std::chrono::high_resolution_clock::now();

        // Insertion des particules dans le vecteur
        for (int i=0; i<16; ++i){
            std::vector<double> positions={dist_position(mt),dist_position(mt), dist_position(mt)};
            std::vector<double> vitesses = {dist_vitesse(mt), dist_vitesse(mt), dist_vitesse(mt)};
            std::vector<double> forces = {dist_force(mt), dist_force(mt), dist_force(mt)};
            double masses = dist_masse(mt);
            int ids = dist_id(mt);
            std::string category = categories[mt() % categories.size()];
            particles.emplace_back(positions, vitesses, masses,ids,category,forces);
        }   
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Temps d'insertion pour " << size << " particules : " << elapsed_seconds.count() << " secondes" << std::endl;
    }
    


    return 0;
}*/

