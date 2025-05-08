#include "../doctest.h"

import RandomIntFromRange;
import CrossoverSinglePoint;
import GenomeIntVector;
import DefaultUniformIntRandomGenerator;
import std;

using namespace Geneticxx;

namespace CrossoverSinglePointTest {
    TEST_CASE(
        "CrossoverSinglePoint basic functionality"
    ) {
        auto *rng = new DefaultUniformIntRandomGenerator(42); // Fixed seed for reproducibility
        CrossoverSinglePoint crossoverOperator(rng);
        std::vector<int> parent1_data(1);
        std::vector<int> parent2_data(1);
        parent1_data.push_back(1);
        parent2_data.push_back(1);
        auto *parent11 = new GenomeIntVector(parent1_data);
        auto *parent22 = new GenomeIntVector(parent2_data);
        Genome *parent1 = parent11;
        Genome *parent2 = parent22;

        std::vector<std::unique_ptr<Genome> > offspring = crossoverOperator.crossover(parent1, parent2);

        REQUIRE(offspring.size() == 2);
        REQUIRE(offspring[0]->getSize() == parent1->getSize());
        REQUIRE(offspring[1]->getSize() == parent2->getSize());
    }

    TEST_CASE(
        "CrossoverSinglePoint correctness"
    ) {
        class MockRandomGenerator : public RandomIntFromRange {
        public:
            explicit MockRandomGenerator() : RandomIntFromRange(0) {
            }

            int generate(int min, int max) override {
                return (min + max) / 2; // Always return middle index
            }
        };

        MockRandomGenerator rng;
        CrossoverSinglePoint crossoverOperator(&rng);

        std::vector<int> parent1_data = {10, 20, 30, 40, 50};
        std::vector<int> parent2_data = {50, 40, 30, 20, 10};
        GenomeIntVector parent1(parent1_data);
        GenomeIntVector parent2(parent2_data);

        auto offspring = (crossoverOperator.crossover(&parent1, &parent2));

        REQUIRE(offspring.size() == 2);
        REQUIRE(offspring[0]->getSize() == 5);
        REQUIRE(offspring[1]->getSize() == 5);

        CHECK(std::any_cast<int>(dynamic_cast<Genome1D*>(offspring[0].get())->getValue(0)) == 50);
        CHECK(std::any_cast<int>(dynamic_cast<Genome1D*>(offspring[0].get())->getValue(1)) == 40);
        CHECK(std::any_cast<int>(dynamic_cast<Genome1D*>(offspring[0].get())->getValue(2)) == 30);
        CHECK(std::any_cast<int>(dynamic_cast<Genome1D*>(offspring[0].get())->getValue(3)) == 40);
        CHECK(std::any_cast<int>(dynamic_cast<Genome1D*>(offspring[0].get())->getValue(4)) == 50);
    }
}