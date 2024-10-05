#include "gtest/gtest.h"
#include "Vecteur.h"
#include "Particle.h"

TEST(TestParticle, DefaultConstructeur){
    Particle<1> particle=Particle<1>();

    EXPECT_EQ(particle.getPosition().getValue()[0],0);
    EXPECT_EQ(particle.getMass(),0);
}

TEST(TestParticle, Constructeur){
    std::array<double,1> val_pos={1};
    Vecteur<1> pos=Vecteur<1>(val_pos);
    std::array<double,1> val_vit={1};
    Vecteur<1> vitesse=Vecteur<1>(val_vit);
    std::array<double,1> val_force={1};
    Vecteur<1> force=Vecteur<1>(val_force);
    std::array<double,1> val_oldf={1};
    Vecteur<1> old_force=Vecteur<1>(val_oldf);
    Particle<1> particle=Particle<1>(pos,vitesse,1,1,"cat",force,old_force);

    EXPECT_EQ(particle.getPosition().getValue()[0],1);
    EXPECT_EQ(particle.getVitesse().getValue()[0],1);
    EXPECT_EQ(particle.getForce().getValue()[0],1);
    EXPECT_EQ(particle.getOldForce().getValue()[0],1);
    EXPECT_EQ(particle.getID(),1);
    EXPECT_EQ(particle.getCategory(),"cat");
}

TEST(TestParticle, MajPosition){
    std::array<double,1> longCaract={100};

    std::array<double,1> val_pos={1};
    Vecteur<1> pos=Vecteur<1>(val_pos);
    std::array<double,1> val_vit={1};
    Vecteur<1> vitesse=Vecteur<1>(val_vit);
    std::array<double,1> val_force={1};
    Vecteur<1> force=Vecteur<1>(val_force);
    std::array<double,1> val_oldf={1};
    Vecteur<1> old_force=Vecteur<1>(val_oldf);
    Particle<1> particle=Particle<1>(pos,vitesse,1,1,"cat",force,old_force);

    particle.position_maj(1,longCaract,1);

    EXPECT_EQ(particle.getPosition().getValue()[0],2.5);
}

TEST(TestParticle, MajVitesse){
    std::array<double,1> longCaract={100};

    std::array<double,1> val_pos={1};
    Vecteur<1> pos=Vecteur<1>(val_pos);
    std::array<double,1> val_vit={1};
    Vecteur<1> vitesse=Vecteur<1>(val_vit);
    std::array<double,1> val_force={1};
    Vecteur<1> force=Vecteur<1>(val_force);
    std::array<double,1> val_oldf={1};
    Vecteur<1> old_force=Vecteur<1>(val_oldf);
    Particle<1> particle=Particle<1>(pos,vitesse,1,1,"cat",force,old_force);

    particle.vitesse_maj(1);

    EXPECT_EQ(particle.getVitesse().getValue()[0],2);
}

TEST(TestParticle, MajForce){
    std::array<double,1> longCaract={1};

    std::array<double,1> val_pos1={2};
    Vecteur<1> pos1=Vecteur<1>(val_pos1);
    std::array<double,1> val_vit1={2};
    Vecteur<1> vitesse1=Vecteur<1>(val_vit1);
    std::array<double,1> val_force1={2};
    Vecteur<1> force1=Vecteur<1>(val_force1);
    std::array<double,1> val_oldf1={2};
    Vecteur<1> old_force1=Vecteur<1>(val_oldf1);

    std::array<double,1> val_pos={1};
    Vecteur<1> pos=Vecteur<1>(val_pos);
    std::array<double,1> val_vit={1};
    Vecteur<1> vitesse=Vecteur<1>(val_vit);
    std::array<double,1> val_force={1};
    Vecteur<1> force=Vecteur<1>(val_force);
    std::array<double,1> val_oldf={1};
    Vecteur<1> old_force=Vecteur<1>(val_oldf);
    Particle<1> particle=Particle<1>(pos,vitesse,1,1,"cat",force,old_force);

    Particle<1> other=Particle<1>(pos1,vitesse1,1,1,"cat",force1,old_force1);

    particle.maj_forceIJPot(other,1,1,2);

    EXPECT_EQ(particle.getForce().getValue()[0],-23);
}
