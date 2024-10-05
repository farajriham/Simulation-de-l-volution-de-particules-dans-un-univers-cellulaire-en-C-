#include "gtest/gtest.h"
#include "Vecteur.h"

//Test de notre constructeur
TEST(TestVecteur, DefaultConstructeur){
    Vecteur<2> vect=Vecteur<2>();

    EXPECT_EQ(vect.getValue()[0],0);
    EXPECT_EQ(vect.getValue()[1],0);
}

TEST(TestVecteur, Constructeur){
    std::array<double,2> val={1,2};
    Vecteur<2> vect(val);
    EXPECT_EQ(vect.getValue()[0],1);
    EXPECT_EQ(vect.getValue()[1],2);
}

TEST(TestVecteur,ConstructeurCopie){
    std::array<double,2> val={1,2};
    Vecteur<2> vectSrc(val);
    Vecteur<2> VectDest(vectSrc);

    EXPECT_EQ(VectDest.getValue()[0],1);
    EXPECT_EQ(VectDest.getValue()[1],2);
}

TEST(TestVecteur,Distance){
    std::array<double,2> val1={4,3};
    std::array<double,2> val2={0,0};
    Vecteur<2> vect1(val1);
    Vecteur<2> vect2(val2);
    double dist=vect1.dist(vect2);

    EXPECT_EQ(dist,25);
}

TEST(TestVecteur,Somme){
    std::array<double,2> val1={1,1};
    std::array<double,2> val2={1,1};
    Vecteur<2> vect1(val1);
    Vecteur<2> vect2(val2);
    Vecteur somme=vect1.sum(vect2);

    EXPECT_EQ(somme.getValue()[0],2);
    EXPECT_EQ(somme.getValue()[1],2);

}

TEST(TestVecteur,Difference){
    std::array<double,2> val1={2,2};
    std::array<double,2> val2={1,1};
    Vecteur<2> vect1(val1);
    Vecteur<2> vect2(val2);

    Vecteur diff=vect1.diff(vect2);

    EXPECT_EQ(diff.getValue()[0],1);
    EXPECT_EQ(diff.getValue()[1],1);
}

TEST(TestVecteur,MultScal){
    std::array<double,2> val={2,2};
    Vecteur<2> vect(val);
    Vecteur mult=vect.multCoeff(3);

    EXPECT_EQ(mult.getValue()[0],6);
    EXPECT_EQ(mult.getValue()[1],6);
}


TEST(TestVecteur,opAffectCopy){
    std::array<double,2> val={1,1};
    Vecteur<2> vect1(val);
    Vecteur vect2=vect1;
    EXPECT_EQ(vect2.getValue()[0],vect1.getValue()[0]);
}
