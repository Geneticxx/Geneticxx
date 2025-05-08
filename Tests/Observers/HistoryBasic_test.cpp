#include "../doctest.h"

// --- Dummy Individual Implementation ---

import Individual;
import Phenome;
import Statistics;
// import Genome;
import std;
import HistoryBasic;
import Population;

using namespace Geneticxx;

namespace HistoryBasicTest {
    class DummyIndividual : public Individual {
        double fitness;
        std::vector<double> objScore;
    public:
        // Constructor takes fitness and a single objective score.
        DummyIndividual(double f, double obj = 0.0) : fitness(f), objScore({obj}) { }

        ~DummyIndividual() override {}

        // Returns a new dummy individual with the same fitness and objective score.
        Individual* createNew() const override {
            return new DummyIndividual(0.0, 0.0);
        }

        Individual* clone() const override {
            return new DummyIndividual(fitness, objScore.empty() ? 0.0 : objScore[0]);
        }

        double getFitness() const override {
            return fitness;
        }

        void setFitness(double f) override {
            fitness = f;
        }

        std::vector<double> getObjectiveScore() const override {
            return objScore;
        }

        void setObjectiveScore(std::vector<double> *score) override {
            objScore = *score;
        }

        void updatePhenome() override {
            // No-op for dummy.
        }

        const Genome* getGenome() const override { return nullptr; }
        Genome* getGenome() override { return nullptr; }
        void setGenome(Genome* /*genome*/) override { }

        const Phenome* getPhenome() const override { return nullptr; }
        void setPhenome(Phenome* /*phenome*/) override { }
    };


    // --- Dummy Statistics Implementation ---

    class DummyStatistics : public Statistics {
        // Store clones of individuals from a population.
        std::vector<std::unique_ptr<Individual>> individuals;
        size_t size;
    public:
        DummyStatistics() : size(0) { }

        ~DummyStatistics() override {}

        // Update by cloning individuals from the provided population.
        void update(Population* population) override {
            individuals.clear();
            if (population) {
                size_t s = population->getSize();
                for (size_t i = 0; i < s; i++) {
                    // Clone each individual from the population.
                    individuals.push_back(std::unique_ptr<Individual>(population->getIndividual(i)->clone()));
                }
                size = s;
            }
        }

        void clear() override {
            individuals.clear();
            size = 0;
        }

        // Create a new DummyStatistics object that clones current individuals.
        DummyStatistics* createNew() override {
            DummyStatistics* ds = new DummyStatistics();
            ds->size = this->size;
            for (size_t i = 0; i < individuals.size(); i++) {
                ds->individuals.push_back(std::unique_ptr<Individual>(individuals[i]->clone()));
            }
            return ds;
        }

        size_t getSize() override {
            return size;
        }

        void setSize(size_t s) override {
            size = s;
        }

        // Return the individual at the given index.
        Individual* getIndividual(int index) override {
            if (index < 0 || index >= static_cast<int>(individuals.size()))
                return nullptr;
            return individuals[index].get();
        }

        // For dummy, best fitness is simply the individual's fitness.
        double getBestFitness(int index) override {
            Individual* ind = getIndividual(index);
            return ind ? ind->getFitness() : 0.0;
        }

        double getMeanFitness(int) override {return 0;}
        double getMedianFitness(int) override {return 0;}
        double getVarianceFitness(int) override {return 0;}
    };

    // --- Dummy Population Implementation ---

    class DummyPopulation : public Population {
    public:
        std::vector<std::unique_ptr<Individual>> individuals;
        // For simplicity, iteration is stored as a simple counter.
        size_t iteration;

        DummyPopulation() : iteration(0) { }

        // Add an individual to the population.
        void addIndividual(Individual* ind) {
            individuals.push_back(std::unique_ptr<Individual>(ind));
        }

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

        void setIndividual(size_t i, Individual* individual) override {
            if (i < individuals.size()) {
                individuals[i] = std::unique_ptr<Individual>(individual);
            } else if (i == individuals.size()) {
                individuals.push_back(std::unique_ptr<Individual>(individual));
            } else {
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

        void resize(size_t size) override {
            individuals.resize(size);
        }

        void clear() override {
            individuals.clear();
        }
    };


    // --- Test Suite for HistoryBasic ---

    TEST_SUITE("HistoryBasic") {
        /// TODO: add checking handling passed nullptr as an argument to generationDone, generationStart and evaluationDone methods
        TEST_CASE("Initial HistoryBasic: Stores initial statistics and default values") {
            // Arrange: Create an initial DummyStatistics with one individual.
            auto initialStats = new DummyStatistics();
            // Create a dummy population with one individual (fitness 5, objective score 0.5).
            auto pop = std::make_unique<DummyPopulation>();
            pop->addIndividual(new DummyIndividual(5.0, 0.5));
            // Update initial statistics from the population.
            initialStats->update(pop.get());
            // Create HistoryBasic with the initial statistics.
            HistoryBasic history(initialStats);

            // Act: Check initial best generation (should be 0) and best fitness via HistoryBasic.
            int bestGen = history.getBestGeneration();
            double bestFitness = history.getBestFitness(0);

            // Assert: Since we have one individual with fitness 5.
            CHECK(bestGen == 0);
            CHECK(bestFitness == 5.0);
        }

        TEST_CASE("generationDone: Updates statistics and best values correctly") {
            // Arrange:
            // Create a dummy population with two individuals.
            auto population = std::make_unique<DummyPopulation>();
            // First individual: fitness 10, objective score 1.0.
            population->addIndividual(new DummyIndividual(10.0, 1.0));
            // Second individual: fitness 20, objective score 2.0.
            population->addIndividual(new DummyIndividual(20.0, 2.0));

            // Create initial statistics and update it with the population.
            auto initialStats = new DummyStatistics();
            initialStats->update(population.get());
            // Create HistoryBasic with the initial statistics.
            HistoryBasic history(initialStats);

            // Prepare a vector of populations (only one population in this test).
            std::vector<std::unique_ptr<Population>> popVec;
            popVec.push_back(std::move(population));

            // Act: Simulate generationDone event.
            int status = history.generationDone(&popVec);

            // Assert:
            CHECK(status == 0);
            // The best fitness should now be 20 (from second individual).
            double bestFitness = history.getBestFitness(1);
            CHECK(bestFitness == 20.0);

            // getBestObjectiveScores(1) should return objective score vector with value 2.0.
            std::vector<double> bestObj = history.getBestObjectiveScores(1);
            REQUIRE(!bestObj.empty());
            CHECK(bestObj[0] == 2.0);

            // getFitness(generation, index) should return same as best fitness for generation 0, index 1.
            double fitnessVal = history.getFitness(0, 1);
            CHECK(fitnessVal == 20.0);

            // getBestGeneration should return the generation index where the best was found.
            int bestGen = history.getBestGeneration();
            CHECK(bestGen == 0);
        }

        TEST_CASE("Notification methods evaluationDone and generationStart return 0") {
            // Arrange: Create a dummy vector of populations.
            std::vector<std::unique_ptr<Population>> popVec;
            popVec.push_back(std::make_unique<DummyPopulation>());

            // Create a HistoryBasic with an initial dummy statistics.
            auto initialStats = new DummyStatistics();
            initialStats->update(popVec[0].get());
            HistoryBasic history(initialStats);

            // Act & Assert:
            CHECK(history.evaluationDone(&popVec) == 0);
            CHECK(history.generationStart(&popVec) == 0);
        }

        TEST_CASE("Multiple generations: Best generation is updated when improvement occurs") {
            // Arrange:
            // Generation 0: Population with one individual, fitness 15.
            auto popGen0 = std::make_unique<DummyPopulation>();
            popGen0->addIndividual(new DummyIndividual(15.0, 1.5));
            auto stats0 = new DummyStatistics();
            stats0->update(popGen0.get());
            HistoryBasic history(stats0);

            // Prepare vector for generation 0.
            std::vector<std::unique_ptr<Population>> popVec0;
            popVec0.push_back(std::move(popGen0));

            // Act: Process generation 0.
            history.generationDone(&popVec0);

            // Generation 1: New population with one individual, fitness 10 (lower than 15).
            auto popGen1 = std::make_unique<DummyPopulation>();
            popGen1->addIndividual(new DummyIndividual(10.0, 1.0));
            auto stats1 = new DummyStatistics();
            stats1->update(popGen1.get());
            // Prepare vector for generation 1.
            std::vector<std::unique_ptr<Population>> popVec1;
            popVec1.push_back(std::move(popGen1));

            // Act: Process generation 1.
            history.generationDone(&popVec1);

            // Assert: Since generation 1 did not improve on best fitness, best generation should remain 0.
            int bestGen = history.getBestGeneration();
            CHECK(bestGen == 0);

            // Generation 2: New population with one individual, fitness 25 (improvement).
            auto popGen2 = std::make_unique<DummyPopulation>();
            popGen2->addIndividual(new DummyIndividual(25.0, 2.5));
            auto stats2 = new DummyStatistics();
            stats2->update(popGen2.get());
            // Prepare vector for generation 2.
            std::vector<std::unique_ptr<Population>> popVec2;
            popVec2.push_back(std::move(popGen2));

            // Act: Process generation 2.
            history.generationDone(&popVec2);

            // Assert: Now the best generation should be updated to generation 2.
            bestGen = history.getBestGeneration();
            CHECK(bestGen == 2);
            // And the best fitness should be 25.
            double bestFitness = history.getBestFitness(0);
            CHECK(bestFitness == 25.0);
        }

        TEST_CASE("Default unimplemented methods return default values") {
            // Arrange: Create an initial dummy statistics and HistoryBasic.
            auto initialStats = new DummyStatistics();
            // Create a dummy population with one individual.
            auto pop = std::make_unique<DummyPopulation>();
            pop->addIndividual(new DummyIndividual(8.0, 0.8));
            initialStats->update(pop.get());
            HistoryBasic history(initialStats);

            // Act & Assert:
            // getBestPhenome should return nullptr.
            CHECK(history.getBestPhenome() == nullptr);
            // getGenome and getPhenome should return nullptr.
            CHECK(history.getGenome(0, 0) == nullptr);
            CHECK(history.getPhenome(0, 0) == nullptr);
            // getObjectiveScore for a generation/index should return 0.
            CHECK(history.getObjectiveScore(0, 0) == 0);
        }
    }
}