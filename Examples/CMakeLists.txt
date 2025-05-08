project(Genetic_Examples LANGUAGES CXX)


add_executable(Genetic_TravellingSalesman
        TravellingSalesman.ixx
)
target_link_libraries(Genetic_TravellingSalesman PRIVATE GeneticLib)

add_executable(Genetic_Knapsack
        Knapsack.ixx
)
target_link_libraries(Genetic_Knapsack PRIVATE GeneticLib)

add_executable(Genetic_LinearModelOptimization
        LinearModelOptimization.ixx
)
target_link_libraries(Genetic_LinearModelOptimization PRIVATE GeneticLib)
#target_include_directories(Genetic_Tests PRIVATE ${CMAKE_SOURCE_DIR})




