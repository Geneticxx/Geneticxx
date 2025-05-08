#include "../doctest.h"

// --- Dummy Implementation for Individual ---

import SelectorRoulette;
import Individual;
import Population;
import DefaultUniformIntRandomGenerator;
import DefaultUniformRealRandomGenerator;
import std;
using namespace Geneticxx;
namespace SelectorRouletteTest {
    class DummyIndividual : public Individual {
    private:
        double fitness;
    public:
        explicit DummyIndividual(double f) : fitness(f) {}
        ~DummyIndividual() override {}

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

        void setObjectiveScore(std::vector<double> *score) override {
            // No-op.
        }

        void updatePhenome() override {
            // No-op.
        }

        const Genome* getGenome() const override {
            return nullptr;
        }

        Genome* getGenome() override {
            return nullptr;
        }

        void setGenome(Genome* /*genome*/) override {
            // No-op.
        }

        const Phenome* getPhenome() const override {
            return nullptr;
        }

        void setPhenome(Phenome* /*phenome*/) override {
            // No-op.
        }
    };

    // namespace Geneticxx

    // --- Dummy Implementation for Population ---
    // This dummy population stores individuals in a vector.



    class DummyPopulation : public Population {
    private:
        std::vector<std::unique_ptr<Individual>> individuals;
        size_t iteration;
    public:
        DummyPopulation() : iteration(0) {}

        // Add an individual to the population.
        void addIndividual(Individual* ind) {
            individuals.push_back(std::unique_ptr<Individual>(ind));
        }

        [[nodiscard]] std::unique_ptr<Population> createNew() const override {
            return std::make_unique<DummyPopulation>();
        }

        [[nodiscard]] std::unique_ptr<Population> clone() const override {
            auto clonePop = std::make_unique<DummyPopulation>();
            for (const auto& ind : individuals)
                clonePop->addIndividual(ind->clone());
            clonePop->iteration = iteration;
            return clonePop;
        }

        Individual* getIndividual(size_t i) override {
            return individuals[i].get();
        }

        void setIndividual(size_t i, Individual* individual) override {
            individuals[i] = std::unique_ptr<Individual>(individual);
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

        void resize(size_t size) override {
            individuals.resize(size);
        }

        void clear() override {
            individuals.clear();
        }
    };



    // --- Tests for SelectorRoulette ---





    TEST_SUITE("SelectorRoulette") {

        // Seed the random number generator with a fixed value for reproducibility.
        // struct RNGInitializer {
        //     RNGInitializer() { std::srand(42); }
        // } rngInitializer;

        TEST_CASE("select: Returns empty vector when population is empty") {
            // Arrange
            auto *genReal = new DefaultUniformRealRandomGenerator(42);
            DummyPopulation population;
            SelectorRoulette selector(genReal);
            // Act
            auto selected = selector.select(&population, 5);
            // Assert
            CHECK(selected.size() == 0);
        }

        TEST_CASE("updatePartialSums & select: Selected individuals are clones with correct fitness values") {
            // Arrange: Create a dummy population with individuals of known fitness values.
            auto *genReal = new DefaultUniformRealRandomGenerator(42);
            DummyPopulation population;
            std::vector<double> fitnessValues = {10.0, 20.0, 30.0, 40.0};
            for (double f : fitnessValues) {
                population.addIndividual(new DummyIndividual(f));
            }
            // Total fitness = 100.0 and partial sums should be [10, 30, 60, 100].
            SelectorRoulette selector(genReal);
            // Act: Request selection of 10 individuals.
            auto selected = selector.select(&population, 10);
            // Assert:
            // The number of selected individuals must match the requested size.
            CHECK(selected.size() == 10);

            // Collect original fitness values in a set for easy lookup.
            std::set<double> originalFitness(fitnessValues.begin(), fitnessValues.end());

            // For each selected individual, check:
            // - Its fitness value is one of the original fitness values.
            // - It is a clone (i.e. its pointer differs from the original stored individual).
            for (size_t i = 0; i < selected.size(); i++) {
                double selFitness = selected[i]->getFitness();
                CHECK(originalFitness.find(selFitness) != originalFitness.end());

                // Additionally, verify that the clone is distinct from the original.
                // We obtain one candidate from the population with the same fitness.
                bool isDistinct = true;
                for (size_t j = 0; j < population.getSize(); j++) {
                    if (population.getIndividual(j)->getFitness() == selFitness) {
                        if (population.getIndividual(j) == selected[i].get()) {
                            isDistinct = false;
                            break;
                        }
                    }
                }
                CHECK(isDistinct);
            }
        }

        TEST_CASE("select: Returns clones that are independent copies") {
            // Arrange: Create a population with a single individual.
            auto *genReal = new DefaultUniformRealRandomGenerator(42);
            DummyPopulation population;
            population.addIndividual(new DummyIndividual(55.5));
            SelectorRoulette selector(genReal);
            // Act: Select multiple copies of the same individual.
            auto selected = selector.select(&population, 5);
            // Assert: All selected clones must have the same fitness as the original.
            for (const auto& indPtr : selected) {
                CHECK(indPtr->getFitness() == 55.5);
            }
            // Additionally, check that each clone is a distinct object.
            for (size_t i = 0; i < selected.size(); i++) {
                for (size_t j = i + 1; j < selected.size(); j++) {
                    CHECK(selected[i].get() != selected[j].get());
                }
            }
        }
    }
}