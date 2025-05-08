#include "../doctest.h"

import Individual;
import Population;
import ReplacementFull;
import std;

using namespace Geneticxx;

// --- Dummy Implementation for Individual ---

namespace ReplacementFullTest {
    class DummyIndividual : public Individual {
    private:
        double fitness;
    public:
        explicit DummyIndividual(double f) : fitness(f) { }
        ~DummyIndividual() override { }

        // Create a new default dummy individual.
        Individual* createNew() const override {
            return new DummyIndividual(0.0);
        }

        // Clone returns a new DummyIndividual with the same fitness.
        Individual* clone() const override {
            return new DummyIndividual(fitness);
        }

        double getFitness() const override {
            return fitness;
        }

        void setFitness(double f) override {
            fitness = f;
        }

        std::vector<double> getObjectiveScore() const override {
            return {};
        }
        void setObjectiveScore(std::vector<double> *score) override { }

        void updatePhenome() override { }

        const Genome* getGenome() const override { return nullptr; }
        Genome* getGenome() override { return nullptr; }
        void setGenome(Genome* /*genome*/) override { }

        const Phenome* getPhenome() const override { return nullptr; }
        void setPhenome(Phenome* /*phenome*/) override { }
    };


    // --- DummyPopulation Implementation ---
    // This custom DummyPopulation supports dynamic sizing through setIndividual.


    class DummyPopulation : public Population {
    public:
        std::vector<std::unique_ptr<Individual>> individuals;
        size_t iteration;

        DummyPopulation() : iteration(0) { }

        // Adds an individual to the end of the population.
        void addIndividual(Individual* ind) {
            individuals.push_back(std::unique_ptr<Individual>(ind));
        }

        // Population interface implementations:
        [[nodiscard]] std::unique_ptr<Population> createNew() const override {
            return std::make_unique<DummyPopulation>();
        }

        [[nodiscard]] std::unique_ptr<Population> clone() const override {
            auto clonePop = std::make_unique<DummyPopulation>();
            for (const auto& ind : individuals) {
                clonePop->addIndividual(ind->clone());
            }
            clonePop->iteration = iteration;
            return clonePop;
        }

        Individual* getIndividual(size_t i) override {
            return individuals[i].get();
        }

        // This version of setIndividual resizes the vector if needed.
        void setIndividual(size_t i, Individual* individual) override {
            if (i < individuals.size()) {
                individuals[i] = std::unique_ptr<Individual>(individual);
            } else if (i == individuals.size()) {
                individuals.push_back(std::unique_ptr<Individual>(individual));
            } else {
                // If i is greater than the current size, resize and add.
                individuals.resize(i + 1);
                individuals[i] = std::unique_ptr<Individual>(individual);
            }
        }

        size_t getSize() const override {
            return individuals.size();
        }

        size_t getIteration() const override {
            return iteration;
        }

        void increaseIteration() override {
            ++iteration;
        }

        // For replacement, clear simply erases all individuals.
        void clear() override {
            individuals.clear();
        }

        void resize(size_t size) override {
            individuals.resize(size);
        }
    };


    // --- Tests for ReplacementFull ---


    TEST_SUITE("ReplacementFull") {

        TEST_CASE("replace: When populations have the same size, original population is fully replaced") {
            // Arrange: Create an original population with 3 individuals.
            auto original = std::make_unique<DummyPopulation>();
            original->addIndividual(new DummyIndividual(1.0));
            original->addIndividual(new DummyIndividual(2.0));
            original->addIndividual(new DummyIndividual(3.0));
            size_t originalIteration = original->getIteration();

            // Create a replacing population with 3 individuals (different fitness values).
            auto replacing = std::make_unique<DummyPopulation>();
            replacing->addIndividual(new DummyIndividual(4.0));
            replacing->addIndividual(new DummyIndividual(5.0));
            replacing->addIndividual(new DummyIndividual(6.0));

            ReplacementFull replacer;
            // Act: Perform replacement.
            Population* result = replacer.replace(original.get(), replacing.get());

            // Assert: The original population should now have the replacing individuals.
            CHECK(result->getSize() == 3);
            CHECK(result->getIteration() == originalIteration + 1);
            for (size_t i = 0; i < result->getSize(); i++) {
                // The fitness value of each individual should match the replacing population.
                double replacedFitness = result->getIndividual(i)->getFitness();
                double expectedFitness = replacing->getIndividual(i)->getFitness();
                CHECK(replacedFitness == expectedFitness);

                // Also ensure that the individual is a clone (a distinct object).
                CHECK(result->getIndividual(i) != replacing->getIndividual(i));
            }
        }

        TEST_CASE("replace: When populations have different sizes, original is cleared and replaced") {
            // Arrange: Create an original population with 2 individuals.
            auto original = std::make_unique<DummyPopulation>();
            original->addIndividual(new DummyIndividual(10.0));
            original->addIndividual(new DummyIndividual(20.0));
            size_t originalIteration = original->getIteration();

            // Create a replacing population with 3 individuals.
            auto replacing = std::make_unique<DummyPopulation>();
            replacing->addIndividual(new DummyIndividual(30.0));
            replacing->addIndividual(new DummyIndividual(40.0));
            replacing->addIndividual(new DummyIndividual(50.0));

            ReplacementFull replacer;
            // Act: Perform replacement.
            Population* result = replacer.replace(original.get(), replacing.get());

            // Assert: Original population should now have exactly 3 individuals.
            CHECK(result->getSize() == 3);
            CHECK(result->getIteration() == originalIteration + 1);
            for (size_t i = 0; i < result->getSize(); i++) {
                double replacedFitness = result->getIndividual(i)->getFitness();
                double expectedFitness = replacing->getIndividual(i)->getFitness();
                CHECK(replacedFitness == expectedFitness);
                CHECK(result->getIndividual(i) != replacing->getIndividual(i));
            }
        }
    }
}