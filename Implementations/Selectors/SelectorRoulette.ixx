export module SelectorRoulette;

import SelectionSchema;
import RandomRealFromRange;
import std;
import std.compat;

namespace Geneticxx {
    /**
     * @class SelectorRoulette
     * @brief A selection schema that uses the roulette wheel method to select individuals from a population.
     *
     * This class implements the `SelectionSchema` interface and selects individuals based on their cumulative fitness.
     * The selection process uses the roulette wheel mechanism, where individuals with higher fitness have a higher
     * chance of being selected.
     */
    export class SelectorRoulette : public SelectionSchema {
    private:
        /**
         * @brief Pointer to a random number generator for generating random integers.
         *
         * This utility is used to generate random integer values for cutoff.
         */
        RandomRealFromRange *m_RandomNumbersGeneratorReal{};

        /**
         * @brief A vector that stores cumulative fitness values for the roulette wheel selection.
         *
         * The vector holds partial sums of individual fitness values. The cumulative sum allows for fast selection
         * of individuals using the roulette wheel method.
         */
        std::vector<double> m_PartialSums;

        /**
         * @brief The current size of the `m_PartialSums` vector.
         *
         * This value represents the number of individuals in the population, which is used to determine if the
         * `m_PartialSums` vector needs to be resized.
         */
        size_t m_PartialSums_Size;

    public:
        /**
         * @brief Default constructor for `SelectorRoulette` class.
         *
         * Initializes the selector by accepting random number generators for real and sets the size
         * of the partial sums vector to zero.
         *
         * @param genReal Pointer to the random real generator.
         */
        SelectorRoulette(RandomRealFromRange* genReal);

        /**
         * @brief Destructor for `SelectorRoulette` class.
         *
         * The destructor ensures proper cleanup of resources when the `SelectorRoulette` object is destroyed.
         */
        ~SelectorRoulette() override;

        /**
         * @brief Selects a subset of individuals from the population using the roulette wheel method.
         *
         * This method selects `size` individuals based on their fitness, with higher fitness individuals having
         * a higher chance of being selected. The roulette wheel mechanism is implemented using the cumulative
         * fitness stored in `m_PartialSums`.
         *
         * @param population The population from which to select individuals.
         * @param size The number of individuals to select.
         * @return A vector containing the selected individuals as unique pointers.
         */
        std::vector<std::unique_ptr<Individual>> select(Population* population, size_t size) override;

        /**
         * @brief Updates the cumulative fitness values (partial sums) for the population.
         *
         * This method calculates the partial sums of the fitness values of the individuals in the population and
         * stores them in the `m_PartialSums` vector. The cumulative sum is used for fast selection in the roulette
         * wheel method.
         *
         * @param population The population whose fitness values are used to update the partial sums.
         */
        void updatePartialSums(Population* population);
    };
}
