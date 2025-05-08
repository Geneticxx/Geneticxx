export module ReplacementSchema;

export import Population;
export import Individual;
import std.compat;

namespace Geneticxx {
    /**
     * @class ReplacementSchema
     * @brief Class responsible for handling the replacement of individuals in a population.
     *
     * The `ReplacementSchema` class provides an interface for replacing individuals in an existing population
     * with individuals from a new population, typically used in evolutionary algorithms to simulate generational replacement.
     */
    export class ReplacementSchema {
    public:
        /**
         * @brief Virtual destructor to ensure proper cleanup of derived class objects.
         *
         * This virtual destructor ensures that the destructors of derived classes are called
         * when deleting an object through a base class pointer.
         */
        virtual ~ReplacementSchema() {
        }

        /**
         * @brief Replaces individuals in the original population with those from the replacing population.
         *
         * This method replaces the individuals in the original population with those from the replacing population.
         * The replacement strategy depends on the specific implementation of the `ReplacementSchema`.
         *
         * @param originalPopulation Pointer to the original population to be updated.
         * @param replacingPopulation Pointer to the new population used for replacement.
         *
         * @return A pointer to the updated population after the replacement.
         */
        virtual Population* replace(Population *originalPopulation, Population *replacingPopulation) = 0;
    };
}
