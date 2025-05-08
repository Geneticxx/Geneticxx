#include "../doctest.h"

import Genome1D;
import Phenome1D;
import IndividualSimple;
import std;

using namespace Geneticxx;

// --- Dummy Implementations for Genome and Phenome ---

// Minimal dummy Genome implementation.
namespace IndividualSimpleTest {
    class DummyGenomeIndividualSimple : public Genome1D {
    public:
        int data;

        DummyGenomeIndividualSimple(int d = 0) : data(d) {}

        std::unique_ptr<Genome> createNew() const override {
            return std::make_unique<DummyGenomeIndividualSimple>();
        }

        std::unique_ptr<Genome> clone() const override {
            return std::make_unique<DummyGenomeIndividualSimple>(data);
        }

        double distance(Genome *other) const override {
            // For simplicity, cast to DummyGenomeIndividualSimple and compute absolute difference.
            DummyGenomeIndividualSimple* otherGenome = dynamic_cast<DummyGenomeIndividualSimple*>(other);
            if(otherGenome)
                return std::abs(data - otherGenome->data);
            return 0.0;
        }

        std::any getValue(size_t position) const override {
            // Only one value at position 0.
            if (position == 0)
                return data;
            return {};
        }

        void setValue(size_t position, std::any value) override {
            if (position == 0 && value.has_value())
                data = std::any_cast<int>(value);
        }

        size_t getSize() const override {
            return 1;
        }

        bool operator==(Genome *other) const override {
            DummyGenomeIndividualSimple* otherGenome = dynamic_cast<DummyGenomeIndividualSimple*>(other);
            return otherGenome && (data == otherGenome->data);
        }
    };

    // Minimal dummy Phenome implementation.
    class DummyPhenomeIndividualSimple : public Phenome1D {
    public:
        int trait;
        // A flag to indicate update was called.
        bool updated;

        DummyPhenomeIndividualSimple(int t = 0) : trait(t), updated(false) {}

        void updatePhenome(const Genome* genome) override {
            // For testing, if genome is DummyGenomeIndividualSimple, set trait equal to genome's data.
            if (genome) {
                const DummyGenomeIndividualSimple* dg = dynamic_cast<const DummyGenomeIndividualSimple*>(genome);
                if(dg) {
                    trait = dg->data;
                    updated = true;
                }
            }
        }

        Phenome* createNew() const override {
            return new DummyPhenomeIndividualSimple();
        }

        Phenome* clone() const override {
            auto* copy = new DummyPhenomeIndividualSimple(trait);
            copy->updated = updated;
            return copy;
        }

        std::any getValue(size_t position) const override {
            if (position == 0)
                return trait;
            return {};
        }

        void setValue(size_t position, std::any value) override {
            if (position == 0 && value.has_value())
                trait = std::any_cast<int>(value);
        }

        int getSize() const override {
            return 1;
        }

        bool operator==(const Phenome *other) const override {
            const DummyPhenomeIndividualSimple* otherPhenome = dynamic_cast<const DummyPhenomeIndividualSimple*>(other);
            return otherPhenome && (trait == otherPhenome->trait);
        }
    };

    // --- Include the IndividualSimple module ---
    // (Assuming the module interface is available and the implementation is linked)
    // For testing, we can simulate it with an include if necessary.

    /// TODO: add checking handling passed nullptr as an argument to setObjectiveScore method
    TEST_SUITE("IndividualSimple") {

        // Helper functions to create dummy objects.
        DummyGenomeIndividualSimple* createDummyGenomeIndividualSimple(int data = 42) {
            return new DummyGenomeIndividualSimple(data);
        }

        DummyPhenomeIndividualSimple* createDummyPhenomeIndividualSimple(int trait = 0) {
            return new DummyPhenomeIndividualSimple(trait);
        }

        TEST_CASE("Default Constructor: Initializes to default values") {
            // Arrange & Act
            IndividualSimple individual;
            // Assert
            CHECK(individual.getFitness() == 0.0);
            CHECK(individual.getObjectiveScore() == std::vector<double>{0});
            CHECK(individual.getGenome() == nullptr);
            CHECK(individual.getPhenome() == nullptr);
        }

        TEST_CASE("Parameterized Constructor: Takes ownership of provided genome and phenome") {
            // Arrange
            DummyGenomeIndividualSimple* genome = createDummyGenomeIndividualSimple(10);
            DummyPhenomeIndividualSimple* phenome = createDummyPhenomeIndividualSimple(5);
            // Act
            IndividualSimple individual(phenome, genome);
            // Assert: ownership is transferred so pointers must not be null.
            CHECK(individual.getGenome() != nullptr);
            CHECK(individual.getPhenome() != nullptr);
            // Validate dummy values
            auto* dg = dynamic_cast<DummyGenomeIndividualSimple*>(individual.getGenome());
            auto* dp = dynamic_cast<DummyPhenomeIndividualSimple*>(individual.getPhenome());
            REQUIRE(dg != nullptr);
            REQUIRE(dp != nullptr);
            CHECK(dg->data == 10);
            CHECK(dp->trait == 5);
        }

        TEST_CASE("Copy Constructor: Deep copies genome and phenome") {
            // Arrange
            DummyGenomeIndividualSimple* genome = createDummyGenomeIndividualSimple(20);
            DummyPhenomeIndividualSimple* phenome = createDummyPhenomeIndividualSimple(15);
            IndividualSimple original(phenome, genome);
            original.setFitness(3.14);
            std::vector<double> scores1 = {1.0, 2.0};
            original.setObjectiveScore(&scores1);
            // Act
            IndividualSimple copy(original);
            // Assert: Fitness and objective score are the same.
            CHECK(copy.getFitness() == original.getFitness());
            CHECK(copy.getObjectiveScore() == original.getObjectiveScore());
            // Assert: Genome and phenome are deep-copied (different addresses).
            CHECK(copy.getGenome() != original.getGenome());
            CHECK(copy.getPhenome() != original.getPhenome());
            // Check that internal values are the same.
            auto* origGenome = dynamic_cast<DummyGenomeIndividualSimple*>(original.getGenome());
            auto* copyGenome = dynamic_cast<DummyGenomeIndividualSimple*>(copy.getGenome());
            auto* origPhenome = dynamic_cast<DummyPhenomeIndividualSimple*>(original.getPhenome());
            auto* copyPhenome = dynamic_cast<DummyPhenomeIndividualSimple*>(copy.getPhenome());
            REQUIRE(origGenome != nullptr);
            REQUIRE(copyGenome != nullptr);
            REQUIRE(origPhenome != nullptr);
            REQUIRE(copyPhenome != nullptr);
            CHECK(origGenome->data == copyGenome->data);
            CHECK(origPhenome->trait == copyPhenome->trait);
        }

        TEST_CASE("Move Constructor: Transfers ownership and resets moved-from individual") {
            // Arrange
            DummyGenomeIndividualSimple* genome = createDummyGenomeIndividualSimple(30);
            DummyPhenomeIndividualSimple* phenome = createDummyPhenomeIndividualSimple(25);
            IndividualSimple original(phenome, genome);
            original.setFitness(2.71);
            std::vector<double> scores1 = {3.0, 4.0};
            original.setObjectiveScore(&scores1);
            // Act
            IndividualSimple moved(std::move(original));
            // Assert: Moved-to object has the original's data.
            CHECK(moved.getFitness() == 2.71);
            CHECK(moved.getObjectiveScore() == std::vector<double>{3.0, 4.0});
            CHECK(moved.getGenome() != nullptr);
            CHECK(moved.getPhenome() != nullptr);
            // The moved-from individual should have its unique_ptrs transferred (i.e. become null).
            CHECK(original.getGenome() == nullptr);
            CHECK(original.getPhenome() == nullptr);
            // And fitness and objective score are reset.
            CHECK(original.getFitness() == 0.0);
            CHECK(original.getObjectiveScore() == std::vector<double>{0});
        }

        TEST_CASE("Copy Assignment Operator: Deep copies data") {
            // Arrange
            DummyGenomeIndividualSimple* genome1 = createDummyGenomeIndividualSimple(50);
            DummyPhenomeIndividualSimple* phenome1 = createDummyPhenomeIndividualSimple(45);
            IndividualSimple individual1(phenome1, genome1);
            individual1.setFitness(5.55);
            std::vector<double> scores1 = {7.0};
            individual1.setObjectiveScore(&scores1);

            DummyGenomeIndividualSimple* genome2 = createDummyGenomeIndividualSimple(100);
            DummyPhenomeIndividualSimple* phenome2 = createDummyPhenomeIndividualSimple(90);
            IndividualSimple individual2(phenome2, genome2);
            individual2.setFitness(9.99);
            std::vector<double> scores2 = {8.0, 9.0};
            individual2.setObjectiveScore(&scores2);

            // Act: Copy assign individual1 to individual2
            individual2 = individual1;
            // Assert: Check deep copy
            CHECK(individual2.getFitness() == 5.55);
            CHECK(individual2.getObjectiveScore() == std::vector<double>{7.0});
            CHECK(individual2.getGenome() != individual1.getGenome());
            CHECK(individual2.getPhenome() != individual1.getPhenome());
            auto* dg1 = dynamic_cast<DummyGenomeIndividualSimple*>(individual1.getGenome());
            auto* dg2 = dynamic_cast<DummyGenomeIndividualSimple*>(individual2.getGenome());
            auto* dp1 = dynamic_cast<DummyPhenomeIndividualSimple*>(individual1.getPhenome());
            auto* dp2 = dynamic_cast<DummyPhenomeIndividualSimple*>(individual2.getPhenome());
            REQUIRE(dg1 != nullptr);
            REQUIRE(dg2 != nullptr);
            REQUIRE(dp1 != nullptr);
            REQUIRE(dp2 != nullptr);
            CHECK(dg1->data == dg2->data);
            CHECK(dp1->trait == dp2->trait);
        }

        TEST_CASE("Move Assignment Operator: Transfers ownership and resets moved-from individual") {
            // Arrange
            DummyGenomeIndividualSimple* genome1 = createDummyGenomeIndividualSimple(60);
            DummyPhenomeIndividualSimple* phenome1 = createDummyPhenomeIndividualSimple(55);
            IndividualSimple individual1(phenome1, genome1);
            individual1.setFitness(11.11);
            std::vector<double> scores1 = {10.0};
            individual1.setObjectiveScore(&scores1);

            DummyGenomeIndividualSimple* genome2 = createDummyGenomeIndividualSimple(200);
            DummyPhenomeIndividualSimple* phenome2 = createDummyPhenomeIndividualSimple(180);
            IndividualSimple individual2(phenome2, genome2);
            individual2.setFitness(22.22);
            std::vector<double> scores2 = {20.0, 30.0};
            individual2.setObjectiveScore(&scores2);

            // Act: Move assign individual1 to individual2
            individual2 = std::move(individual1);
            // Assert: individual2 now holds individual1's data.
            CHECK(individual2.getFitness() == 11.11);
            CHECK(individual2.getObjectiveScore() == std::vector<double>{10.0});
            CHECK(individual2.getGenome() != nullptr);
            CHECK(individual2.getPhenome() != nullptr);
            // Moved-from individual1 should have null genome/phenome and reset fitness/objectiveScore.
            CHECK(individual1.getGenome() == nullptr);
            CHECK(individual1.getPhenome() == nullptr);
            CHECK(individual1.getFitness() == 0.0);
            CHECK(individual1.getObjectiveScore() == std::vector<double>{0});
        }

        TEST_CASE("Fitness and Objective Score: Set and get work as expected") {
            // Arrange
            IndividualSimple individual;
            // Act & Assert for fitness
            individual.setFitness(99.9);
            CHECK(individual.getFitness() == 99.9);
            // Act & Assert for objective score
            std::vector<double> scores1 = {3.14, 2.718};
            individual.setObjectiveScore(&scores1);
            CHECK(individual.getObjectiveScore() == scores1);
        }

        TEST_CASE("updatePhenome: Calls phenome update when both genome and phenome exist") {
            // Arrange
            DummyGenomeIndividualSimple* genome = createDummyGenomeIndividualSimple(77);
            DummyPhenomeIndividualSimple* phenome = createDummyPhenomeIndividualSimple(0);
            IndividualSimple individual(phenome, genome);
            // Initially, the dummy phenome has not been updated.
            auto* dp = dynamic_cast<DummyPhenomeIndividualSimple*>(individual.getPhenome());
            REQUIRE(dp != nullptr);
            CHECK(dp->updated == false);
            // Act
            individual.updatePhenome();
            // Assert: The dummy phenome's updatePhenome should have been called,
            // setting its trait equal to the genome's data and marking it as updated.
            CHECK(dp->trait == 77);
            CHECK(dp->updated == true);
        }

        TEST_CASE("updatePhenome: Does nothing when genome or phenome is nullptr") {
            // Arrange: default constructed individual (both pointers are nullptr)
            IndividualSimple individual;
            // Act & Assert: Calling updatePhenome should not crash
            CHECK_NOTHROW(individual.updatePhenome());
        }

        TEST_CASE("getGenome and setGenome: Allow replacing genome") {
            // Arrange
            DummyGenomeIndividualSimple* genome1 = createDummyGenomeIndividualSimple(15);
            IndividualSimple individual;
            // Initially, genome is nullptr.
            CHECK(individual.getGenome() == nullptr);
            // Act: Set genome to genome1.
            individual.setGenome(genome1);
            // Assert
            auto* dg = dynamic_cast<DummyGenomeIndividualSimple*>(individual.getGenome());
            REQUIRE(dg != nullptr);
            CHECK(dg->data == 15);
        }

        TEST_CASE("getPhenome and setPhenome: Allow replacing phenome") {
            // Arrange
            DummyPhenomeIndividualSimple* phenome1 = createDummyPhenomeIndividualSimple(25);
            IndividualSimple individual;
            // Initially, phenome is nullptr.
            CHECK(individual.getPhenome() == nullptr);
            // Act: Set phenome.
            individual.setPhenome(phenome1);
            // Assert
            auto* dp = dynamic_cast<DummyPhenomeIndividualSimple*>(individual.getPhenome());
            REQUIRE(dp != nullptr);
            CHECK(dp->trait == 25);
        }

        TEST_CASE("createNew and clone: Produce independent individuals") {
            // Arrange
            DummyGenomeIndividualSimple* genome = createDummyGenomeIndividualSimple(88);
            DummyPhenomeIndividualSimple* phenome = createDummyPhenomeIndividualSimple(77);
            IndividualSimple original(phenome, genome);
            original.setFitness(3.33);
            std::vector<double> scores1 = {5.55};
            original.setObjectiveScore(&scores1);
            // Act: createNew
            Individual* newIndividual = original.createNew();
            // Assert: New individual should be default constructed.
            auto* newInd = dynamic_cast<IndividualSimple*>(newIndividual);
            REQUIRE(newInd != nullptr);
            CHECK(newInd->getFitness() == 0.0);
            CHECK(newInd->getObjectiveScore() == std::vector<double>{0});
            // Act: clone
            Individual* clonedIndividual = original.clone();
            auto* cloneInd = dynamic_cast<IndividualSimple*>(clonedIndividual);
            REQUIRE(cloneInd != nullptr);
            // Assert: Clone should be deep equal to original.
            CHECK(cloneInd->getFitness() == original.getFitness());
            CHECK(cloneInd->getObjectiveScore() == original.getObjectiveScore());
            // Genome and phenome should be deep-copied.
            CHECK(cloneInd->getGenome() != original.getGenome());
            CHECK(cloneInd->getPhenome() != original.getPhenome());
            // Clean up dynamically allocated individuals from createNew/clone.
            delete newInd;
            delete cloneInd;
        }
        TEST_CASE("setObjectiveScore with nullptr resets to default") {
            IndividualSimple individual;
            CHECK_NOTHROW(individual.setObjectiveScore(nullptr));
            CHECK(individual.getObjectiveScore() == std::vector<double>{0});
        }


        TEST_CASE("Overwriting genome and phenome with setGenome/setPhenome") {
            auto g1 = std::make_unique<DummyGenomeIndividualSimple>(5);
            auto g2 = std::make_unique<DummyGenomeIndividualSimple>(10);
            IndividualSimple individual;
            individual.setGenome(g1.release());
            auto* oldGenome = individual.getGenome();
            individual.setGenome(g2.release());
            auto* newGenome = individual.getGenome();
            CHECK(newGenome != nullptr);
            CHECK(newGenome != oldGenome);
            CHECK(dynamic_cast<DummyGenomeIndividualSimple*>(newGenome)->data == 10);

            auto p1 = std::make_unique<DummyPhenomeIndividualSimple>(3);
            auto p2 = std::make_unique<DummyPhenomeIndividualSimple>(8);
            individual.setPhenome(p1.release());
            auto* oldPhenome = individual.getPhenome();
            individual.setPhenome(p2.release());
            auto* newPhenome = individual.getPhenome();
            CHECK(newPhenome != nullptr);
            CHECK(newPhenome != oldPhenome);
            CHECK(dynamic_cast<DummyPhenomeIndividualSimple*>(newPhenome)->trait == 8);
        }

        TEST_CASE("ObjectiveScore vector independence after setObjectiveScore") {
            IndividualSimple individual;
            std::vector<double> scores = {1.1, 2.2, 3.3};
            individual.setObjectiveScore(&scores);
            scores[0] = 9.9;
            auto stored = individual.getObjectiveScore();
            CHECK(stored[0] == doctest::Approx(1.1));
        }

        TEST_CASE("Polymorphic clone and createNew via base pointer") {
            auto genome = std::make_unique<DummyGenomeIndividualSimple>(7);
            auto phenome = std::make_unique<DummyPhenomeIndividualSimple>(14);
            IndividualSimple original(phenome.release(), genome.release());
            original.setFitness(0.42);
            std::vector<double> sc = {4.2};
            original.setObjectiveScore(&sc);

            Individual* basePtr = &original;

            SUBCASE("createNew produces fresh IndividualSimple") {
                std::unique_ptr<Individual> newInd{ basePtr->createNew() };
                auto* newSimple = dynamic_cast<IndividualSimple*>(newInd.get());
                REQUIRE(newSimple);
                CHECK(newSimple->getFitness() == doctest::Approx(0.0));
                // default objective score should be empty
                CHECK(newSimple->getObjectiveScore() == std::vector<double>{0});
            }

            SUBCASE("clone preserves fitness and scores") {
                std::unique_ptr<Individual> cloned{ basePtr->clone() };
                auto* cloneSimple = dynamic_cast<IndividualSimple*>(cloned.get());
                REQUIRE(cloneSimple);
                CHECK(cloneSimple->getFitness() == doctest::Approx(original.getFitness()));
                CHECK(cloneSimple->getObjectiveScore() == original.getObjectiveScore());
            }
        }
        /// TODO: If Genome::clone() or Phenome::clone() throws, does IndividualSimple remain in a valid state? (This one is a bit more advanced.)
    }
}