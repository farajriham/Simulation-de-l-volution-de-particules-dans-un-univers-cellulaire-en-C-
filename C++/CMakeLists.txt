cmake_minimum_required (VERSION 3.16.3)
project(Demo CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-pg -Wall")


#indiquer à CMake où trouver les fichiers d'en-tête .h utilisés
include_directories(${CMAKE_SOURCE_DIR}/include)

#CMake cherchera un fichier CMakeLists.txt dans le répertoire src et exécutera les instructions qu'il contient pour construire ce sous-projet
add_subdirectory(src)

# Inclure la gestion de la documentation avec Doxygen
include(FindDoxygen)
find_package(Doxygen)

# Vérifier si Doxygen est trouvé
if (DOXYGEN_FOUND)
    # Ajouter une cible pour générer la documentation
    add_custom_target(
            documentation
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc
            COMMENT "Generating documentation with Doxygen"
            VERBATIM
    )
endif()

#GOOGlE TESSSSSSSSSSSSSSSSSST
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.8.0
)

set(gtest_force_shared_crt ON CACHE BOOL ”” FORCE)
    FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(test)
