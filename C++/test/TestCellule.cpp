#include "gtest/gtest.h"
#include "Vecteur.h"
#include "Particle.h"
#include "Cellules.h"

TEST(TestCellule, DefaultConstructeur){
    Cellules<1> cell=Cellules<1>();

    EXPECT_EQ(cell.getParSet().size(),0);

}

TEST(TestCellule, Constructeur){
    std::set<int> parSet={2};
    std::array<int,1> cellId={1};

    Cellules<1> cell=Cellules<1>(cellId);

    EXPECT_EQ(cell.getcellId(),cellId);
}

TEST(TestCellule, AddParticle){
    std::set<int> parSet={2};
    std::array<int,1> cellId={1};

    Cellules<1> cell=Cellules<1>(cellId);
    int indice_par=2;
    cell.addParticle(indice_par);

    EXPECT_EQ(cell.getParSet().size(),1);
}

