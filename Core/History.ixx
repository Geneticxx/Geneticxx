export module History;

export import Statistics;
export import Population;
import Observers;

namespace Geneticxx {/**
 * @class History
 * @brief Class responsible for storing statistics of past populations (and optionally the populations themselves),
 *        and also stores information on which generation had the best individual.
 *
 * The `History` class tracks statistics for populations across generations, including
 * details about the best individual in each generation. It provides methods for accessing
 * historical data related to fitness, objective scores, and phenomes of individuals.
 */
export class History : public AlgorithmObserver {
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived class objects.
     *
     * This virtual destructor ensures that the destructors of derived classes are called
     * when deleting an object through a base class pointer.
     */
    virtual ~History() {}

    /**
     * @brief Updates the statistics of the current population.
     *
     * This method is called to update statistics based on the current population, such as
     * fitness values, objective scores, and other relevant metrics.
     *
     * @param population Pointer to the Population object whose statistics will be updated.
     */
    virtual void updateCurrentStatistics(Population *population, int index) = 0;

    /**
     * @brief Saves or pushes the computed statistics for future reference.
     *
     * This method saves or stores the computed statistics so that they can be retrieved later.
     * It is typically called after updating the current statistics.
     */
    virtual void pushStatistics() = 0;

    virtual void clear() = 0;

    /**
     * @brief Retrieves the best fitness value from a specific generation.
     *
     * This method returns the highest fitness value observed in a given generation.
     *
     * @param index Index of the generation.
     * @return The best fitness value as a double.
     */
    virtual double getBestFitness(int index) const = 0;

    /**
     * @brief Retrieves the best objective scores from a specific generation.
     *
     * This method returns the best objective scores associated with the most fit individual
     * in the specified generation.
     *
     * @param index Index of the generation.
     * @return A vector of objective scores.
     */
    virtual std::vector<double> getBestObjectiveScores(int index) const = 0;

    /**
     * @brief Retrieves the generation index where the best individual was found.
     *
     * This method returns the index of the generation where the best individual (based
     * on fitness or other criteria) was located.
     *
     * @return The generation index.
     */
    virtual int getBestGeneration() const = 0;
    virtual int getBestPopulationIndex() const = 0;

    /**
     * @brief Retrieves the phenome of a specific individual from a given generation.
     *
     * This method allows access to the phenome of a specific individual from a specified
     * generation.
     *
     * @param generation Index of the generation.
     * @param index Index of the individual in the population.
     * @return Pointer to the Phenome object.
     */
    virtual const Individual* getBestIndividual(int generation, int populationIndex, int index) const = 0;

    /**
         * @brief Retrieves the phenome of an individual at a given generation and index.
         *
         * This method is currently not implemented, but it is intended to return the phenome of the individual
         * at the specified generation and index.
         *
         * @param index The index of the individual in the population.
         * @return A pointer to the phenome of the individual.
         */
    virtual const Individual* getBestIndividual(int index) const = 0;

    /**
     * @brief Retrieves the objective score of a specific individual from a given generation.
     *
     * This method returns the objective score associated with a specific individual in a
     * given generation.
     *
     * @param generation Index of the generation.
     * @param index Index of the individual in the population.
     * @return The objective score as a double.
     */
    virtual std::vector<double> getObjectiveScore(int generation, int populationIndex, int index) const = 0;

    /**
     * @brief Retrieves the fitness value of a specific individual from a given generation.
     *
     * This method returns the fitness value of a specific individual from a given generation.
     *
     * @param generation Index of the generation.
     * @param index Index of the individual in the population.
     * @return The fitness value as a double.
     */
    virtual double getFitness(int generation, int populationIndex, int index) const = 0;

    // virtual int generationDone(Population* population) = 0; // This is inherited as pure virtual, no need to redefine it here.
};

}
