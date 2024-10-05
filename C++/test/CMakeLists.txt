enable_testing()

add_executable(TestUnit TestVect.cpp
        TestParticle.cpp
        TestCellule.cpp)
#lier la bibliothèque gtest_main à mon exécutable

target_link_libraries(TestUnit  gtest_main Src)

include(GoogleTest)
gtest_discover_tests(TestUnit)