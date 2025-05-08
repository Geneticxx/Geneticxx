export module CrossoverUniform;

import CrossoverSchema;
import RandomIntFromRange;
import Genome1D;
import std;

namespace Geneticxx {
    /**
     * @class CrossoverUniform
     * @brief Class responsible for performing uniform crossover between two parent genomes.
     *
     * The `CrossoverUniform` class implements a uniform crossover schema for genetic algorithms.
     * It creates two offspring genomes by randomly exchanging genetic material at each gene position between
     * two parent genomes. This class uses a random number generator to decide whether to copy a gene from the first
     * parent or the second parent at each position.
     */
    export class CrossoverUniform : public CrossoverSchema {
    private:
        RandomIntFromRange* m_RandomNumbersGeneratorInt; /**< Utility for generating random numbers */

    public:
        /**
         * @brief Constructor for the CrossoverUniform class.
         *
         * Initializes the random number generator used for determining gene exchanges between parents.
         *
         * @param genInt A pointer to the `RandomIntFromRange` instance used for generating random integers.
         */
        CrossoverUniform(RandomIntFromRange* genInt);

        /**
         * @brief Destructor for the CrossoverUniform class.
         *
         * Cleans up any dynamically allocated memory (if applicable).
         */
        ~CrossoverUniform() override;

        /**
         * @brief Performs uniform crossover on two parent genomes.
         *
         * This method generates two child genomes by performing a uniform crossover operation.
         * For each gene position, a random choice is made to decide whether the gene should come from
         * the first parent or the second parent. This results in genetic material being exchanged uniformly
         * across all gene positions.
         *
         * @param parent1 Pointer to the first parent genome.
         * @param parent2 Pointer to the second parent genome.
         *
         * @return A vector containing two unique pointers to the child genomes.
         *
         * @throws std::invalid_argument If the parent genomes have different sizes.
         */
        std::vector<std::unique_ptr<Genome>> crossover(Genome* parent1, Genome* parent2) override;
    };
}
