project(Genetic_Tests LANGUAGES CXX)

enable_testing()

add_executable(Genetic_Tests
        test_main.cpp
#        Crossovers/CrossoverSinglePoint_test.cpp
#        Evaluations/EvaluationTravellingSalesman_test.cpp
        Individuals/IndividualSimple_test.cpp
#        StoppingCriteria/StoppingCriterionMaxGenerations_test.cpp
#        Selectors/SelectorRoulette_test.cpp
#        Replacements/ReplacementFull_test.cpp
#        Publishers/PublisherPopulation_test.cpp
#        Observers/HistoryBasic_test.cpp
)
#target_include_directories(Genetic_Tests PRIVATE ${CMAKE_SOURCE_DIR})


target_link_libraries(Genetic_Tests PRIVATE GeneticLib)

add_test(NAME GeneticTests COMMAND Genetic_Tests)
