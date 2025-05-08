export module CrossoverSinglePoint;

import CrossoverSchema;
import Genome1D;
import RandomIntFromRange;
import std;

namespace Geneticxx {
    /**
     * @class CrossoverSinglePoint
     * @brief Class responsible for performing single-point crossover between two parent genomes.
     *
     * The `CrossoverSinglePoint` class implements a single-point crossover schema for genetic algorithms.
     * It creates two offspring genomes by exchanging genetic material between two parent genomes at a randomly
     * selected crossover point. This class uses a random number generator to determine the crossover point.
     */
    export class CrossoverSinglePoint : public CrossoverSchema {
    private:
        RandomIntFromRange* m_RandomNumbersGeneratorInt; /**< Utility for generating random numbers */

    public:
        /**
         * @brief Constructor for the CrossoverSinglePoint class.
         *
         * Initializes the random number generator used for selecting the crossover point.
         *
         * @param genInt A pointer to the `RandomIntFromRange` instance used for generating random integers.
         */
        CrossoverSinglePoint(RandomIntFromRange* genInt);

        /**
         * @brief Destructor for the CrossoverSinglePoint class.
         *
         * Cleans up any dynamically allocated memory (if applicable).
         */
        ~CrossoverSinglePoint() override;

        /**
         * @brief Performs single-point crossover on two parent genomes.
         *
         * This method generates two child genomes by performing a single-point crossover operation.
         * It selects a random crossover point and exchanges genetic material between the parents at that point.
         *
         * @param parent1 Pointer to the first parent genome.
         * @param parent2 Pointer to the second parent genome.
         *
         * @return A vector containing two unique pointers to the child genomes.
         */
        std::vector<std::unique_ptr<Genome>> crossover(Genome* parent1, Genome* parent2) override;
    };
}

