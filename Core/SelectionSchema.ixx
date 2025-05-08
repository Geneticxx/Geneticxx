export module SelectionSchema;

export import Individual;
export import Population;
import std;
import std.compat;

namespace Geneticxx {
    /**
     * @class SelectionSchema
     * @brief Class responsible for selecting individuals from a population based on a selection strategy.
     *
     * The `SelectionSchema` class defines an interface for selecting individuals from a population.
     * Different selection strategies (e.g. roulette wheel, tournament) can be implemented by
     * deriving from this class and overriding the selection methods.
     */
    export class SelectionSchema {
    public:
        /**
         * @brief Virtual destructor to ensure proper cleanup of derived class objects.
         *
         * This virtual destructor ensures that the destructors of derived classes are called
         * when deleting an object through a base class pointer.
         */
        virtual ~SelectionSchema() {
        }

        /**
         * @brief Selects individuals from the given population based on the selection strategy.
         *
         * This method selects a specified number of individuals from the population following
         * the selection strategy defined by the derived class. The exact selection process
         * (e.g., random, fitness-based) depends on the implementation of the derived class.
         *
         * @param population Pointer to the population from which individuals will be selected.
         * @param size The number of individuals to select from the population.
         *
         * @return A vector of unique pointers to the selected individuals.
         */
        virtual std::vector<std::unique_ptr<Individual>> select(Population *population, size_t size) = 0;

        /**
         * @note The population should ideally be `const` to prevent modifications. However, this would require
         * the `getIndividual` method to be a `const` function as well, which would prevent modification of individuals.
         * Therefore, selection might be better handled as a method within the `Population` class itself.
         */
    };
}
