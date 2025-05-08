#include "../doctest.h"

// --- Dummy Population Implementation ---
import StoppingCriterionMaxGenerations;
import Population;
import Individual;
import std;

using namespace Geneticxx;

namespace StoppingCriterionMaxGenerationsTest {
    class DummyPopulation : public Population {
    public:
        // Track the current iteration count.
        size_t iteration;

        DummyPopulation(size_t iter = 0) : iteration(iter) {}

        // Create a new instance with default iteration.
        [[nodiscard]] std::unique_ptr<Population> createNew() const override {
            return std::make_unique<DummyPopulation>();
        }

        // Create a deep copy.
        [[nodiscard]] std::unique_ptr<Population> clone() const override {
            return std::make_unique<DummyPopulation>(iteration);
        }

        // Return an individual (dummy stub).
        Individual* getIndividual(size_t i) override {
            return nullptr;
        }

        // Set an individual (dummy stub).
        void setIndividual(size_t i, Individual* individual) override {
            // No-op.
        }

        // Return size (dummy stub).
        size_t getSize() const override {
            return 0;
        }

        // Return current iteration count.
        size_t getIteration() const override {
            return iteration;
        }

        // Increase iteration by one.
        void increaseIteration() override {
            ++iteration;
        }

        // Resize population (dummy stub).
        void resize(size_t size) override {
            // No-op.
        }

        // Clear population (dummy stub).
        void clear() override {
            // No-op.
        }
    };


    // --- Tests for StoppingCriterionMaxGenerations ---


    TEST_SUITE("StoppingCriterionMaxGenerations") {

        TEST_CASE("Constructor and getMaxGenerations: Returns the initialized value") {
            // Arrange
            size_t maxGen = 100;
            StoppingCriterionMaxGenerations stoppingCriterion(maxGen);
            // Act & Assert
            CHECK(stoppingCriterion.getMaxGenerations() == maxGen);
        }

        TEST_CASE("check: Returns false when current iteration is less than maxGenerations") {
            // Arrange
            size_t maxGen = 50;
            StoppingCriterionMaxGenerations stoppingCriterion(maxGen);
            DummyPopulation population(25);  // iteration less than maxGen.
            // Act
            bool shouldStop = stoppingCriterion.check(&population);
            // Assert
            CHECK(shouldStop == false);
        }

        TEST_CASE("check: Returns true when current iteration equals maxGenerations") {
            // Arrange
            size_t maxGen = 30;
            StoppingCriterionMaxGenerations stoppingCriterion(maxGen);
            DummyPopulation population(30);  // iteration equal to maxGen.
            // Act
            bool shouldStop = stoppingCriterion.check(&population);
            // Assert
            CHECK(shouldStop == true);
        }

        TEST_CASE("check: Returns true when current iteration is greater than maxGenerations") {
            // Arrange
            size_t maxGen = 20;
            StoppingCriterionMaxGenerations stoppingCriterion(maxGen);
            DummyPopulation population(25);  // iteration greater than maxGen.
            // Act
            bool shouldStop = stoppingCriterion.check(&population);
            // Assert
            CHECK(shouldStop == true);
        }

        TEST_CASE("Integration with population: Iteration increases and eventually triggers stopping") {
            // Arrange
            size_t maxGen = 5;
            StoppingCriterionMaxGenerations stoppingCriterion(maxGen);
            DummyPopulation population(0);
            // Act & Assert: Increase iterations one by one until reaching threshold.
            for (size_t i = 0; i < maxGen; ++i) {
                CHECK(stoppingCriterion.check(&population) == false);
                population.increaseIteration();
            }
            // At this point, iteration == maxGen.
            CHECK(stoppingCriterion.check(&population) == true);
        }
    }
}