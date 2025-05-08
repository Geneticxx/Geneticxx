export module StatisticsBasic;

import Statistics;
import Phenome;
import Genome;
import std;
import std.compat;

namespace Geneticxx {
    /**
     * @class StatisticsBasic
     * @brief A class for tracking and storing statistics of a population in a genetic algorithm.
     *
     * This class keeps track of the best individuals in the population and stores counts for various genetic
     * algorithm operations such as mutation, crossover, selection, and replacement. It provides methods for
     * updating the statistics, clearing stored data, and retrieving information about the best individuals.
     *
     * @todo This class will be reworked to retrieve statistical measures from each generation.
     */
    export class StatisticsBasic : public Statistics {
    private:
        /**
         * @brief Stores the best individuals of the population.
         *
         * This vector holds the individuals with the highest fitness values from the population.
         */
        std::vector<std::unique_ptr<Individual>> m_Individuals;

        /**
         * @brief Counters for genetic algorithm operations.
         *
         * These counters track the number of times specific operations (mutation, crossover, selection, and replacement)
         * occur during the algorithm's execution.
         */
        int mutationCount, crossoverCount, selectionCount, replacementCount;

        /**
         * @brief The size of the statistics (number of best individuals to track).
         */
        size_t m_size;

        /**
         * @brief The actual number of best individuals in the population.
         */
        size_t m_realSize;
        double m_meanFitness, m_medianFitness, m_varianceFitness;
    public:
        /**
         * @brief Destructor for `StatisticsBasic` class.
         *
         * Ensures proper cleanup of resources used by the `StatisticsBasic` object.
         */
        ~StatisticsBasic() override;

        /**
         * @brief Default constructor for `StatisticsBasic` class.
         *
         * Initializes counters for genetic algorithm operations and sets the size of the statistics.
         */
        StatisticsBasic();

        /**
         * @brief Updates the statistics based on the current population.
         *
         * This method stores a clone of the best individuals from the population and updates the statistics.
         * The number of best individuals stored is determined by `m_size`.
         *
         * @param population The population whose statistics need to be updated.
         */
        void update(Population* population) override;

        /**
         * @brief Clears the stored statistics.
         *
         * This method clears the list of stored best individuals and resets the statistics counters.
         */
        void clear() override;

        /**
         * @brief Creates a new instance of the `StatisticsBasic` class.
         *
         * This method returns a new instance of `StatisticsBasic`, allowing for the creation of fresh statistic objects.
         *
         * @return A pointer to a newly created `StatisticsBasic` object.
         */
        StatisticsBasic* createNew() override;

        /**
         * @brief Gets the size of the statistics (number of best individuals tracked).
         *
         * This method returns the number of best individuals currently tracked in the statistics.
         *
         * @return The size of the statistics.
         */
        size_t getSize() override;

        /**
         * @brief Sets the size of the statistics.
         *
         * This method sets the number of best individuals to be tracked in the statistics.
         *
         * @param size The new size of the statistics.
         */
        void setSize(size_t size) override;

        /**
         * @brief Retrieves a specific individual from the statistics.
         *
         * This method returns a clone of the individual at the specified index in the statistics.
         * If the index is out of range, an exception is thrown.
         *
         * @param index The index of the individual to retrieve.
         * @return A clone of the individual at the specified index.
         * @throws std::runtime_error if the index is out of range.
         */
        Individual* getBestIndividual(int index) override;

        /**
         * @brief Retrieves the fitness value of the best individual at the specified index.
         *
         * This method returns the fitness value of the individual at the given index in the statistics.
         * If the index is out of range, an exception is thrown.
         *
         * @param index The index of the individual whose fitness is to be retrieved.
         * @return The fitness value of the individual at the specified index.
         * @throws std::runtime_error if the index is out of range.
         */
        double getBestFitness(int index) override;
        double getMeanFitness(int index) override;
        double getMedianFitness(int index) override;
        double getVarianceFitness(int index) override;
    };
}
