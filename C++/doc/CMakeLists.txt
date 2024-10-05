# Configuration de Doxygen
set(DOXYGEN_INPUT_DIR ${CMAKE_SOURCE_DIR}/src)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc/html)
set(DOXYGEN_CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

# Commande d'exécution de Doxygen
add_custom_command(
        OUTPUT ${DOXYGEN_OUTPUT_DIR}
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG}
        COMMENT "Generating documentation with Doxygen"
        VERBATIM
)

# Option de génération de la cible de documentation
add_custom_target(
        documentation
        DEPENDS ${DOXYGEN_OUTPUT_DIR}
)
