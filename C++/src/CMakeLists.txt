# Déclarer les fichiers source de votre bibliothèque ou exécutable
set(SOURCES
        Cellules.cpp
        Particle.cpp
        Vecteur.cpp
        main.cpp
)

# Ajouter l'exécutable principal ou la bibliothèque à construire
add_library(Src ${SOURCES})

# Indiquer à CMake où trouver les fichiers d'en-tête
target_include_directories(Src PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

