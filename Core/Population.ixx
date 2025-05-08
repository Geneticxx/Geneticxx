export module Population;

export import Individual;
import std;
import std.compat;

namespace Geneticxx {
    /**
     * @class Population
     * @brief Class responsible for holding individuals within a population.
     *
     * The `Population` class represents a collection of individuals, typically used in evolutionary algorithms.
     * It provides methods to manage the individuals, track the population's size, and handle iterations for the algorithm's progression.
     */
    export class Population {
    public:
        /**
         * @brief Virtual destructor to ensure proper cleanup of derived class objects.
         *
         * This virtual destructor ensures that the destructors of derived classes are called
         * when deleting an object through a base class pointer.
         */
        virtual ~Population() {
        }

        /**
         * @brief Creates a new instance of a Population with default properties.
         *
         * This method creates a new `Population` object with default properties and returns a unique pointer to it.
         *
         * @return A unique pointer to a new `Population` instance.
         */
        [[nodiscard]] virtual std::unique_ptr<Population> createNew() const = 0;

        /**
         * @brief Creates a deep copy of the current Population.
         *
         * This method creates a deep copy of the current `Population` object and returns a unique pointer to the copy.
         *
         * @return A unique pointer to a copy of the current `Population`.
         */
        [[nodiscard]] virtual std::unique_ptr<Population> clone() const = 0;

        /**
         * @brief Retrieves a pointer to the Individual at the specified index.
         *
         * This method retrieves the `Individual` object located at the specified index in the population.
         * The index should be within the bounds of the population's current size.
         *
         * @param i The index of the `Individual` to retrieve.
         * @return A pointer to the `Individual` at the specified index.
         *
         * @note Consider making this function `const` if the `Individual` is not modified.
         */
        virtual Individual* getIndividual(size_t i) = 0; // TODO: Should this be const?

        /**
         * @brief Sets the Individual at the specified index.
         *
         * This method sets the `Individual` at the specified index in the population.
         *
         * @param i The index where the `Individual` will be set.
         * @param individual A pointer to the `Individual` to be set.
         */
        virtual void setIndividual(size_t i, Individual *individual) = 0;

        /**
         * @brief Returns the current occupied size of the Population.
         *
         * This method returns the current number of `Individual` objects in the population.
         *
         * @return The current size of the Population.
         */
        virtual size_t getSize() const = 0;

        /**
         * @brief Returns the number of elements that can be held in currently allocated storage.
         *
         * This method returns the capacity of the population, i.e., how many individuals it can hold before
         * needing reallocation.
         *
         * @return The capacity of the Population.
         *
         * @note This function is currently commented out. Consider implementing it if needed.
         */
        //virtual size_t getCapacity() const = 0;

        /**
         * @brief Returns the current iteration count of the Population.
         *
         * This method returns the current iteration count of the population, which tracks the number of generations
         * or cycles the population has undergone in the evolutionary algorithm.
         *
         * @return The current iteration count.
         */
        virtual size_t getIteration() const = 0;

        /**
         * @brief Increments the iteration count of the Population.
         *
         * This method increases the iteration count by one, typically used to track the passage of time
         * through generations in an evolutionary algorithm.
         */
        virtual void increaseIteration() = 0;

        /**
         * @brief Resizes the Population to the given size.
         *
         * This method resizes the population to the specified size. If the size is larger than the current size,
         * new individuals are created; if smaller, individuals may be removed.
         *
         * @param size The new size of the Population.
         */
        virtual void resize(size_t size) = 0;

        /**
         * @brief Clears all Individuals in the Population.
         *
         * This method removes all individuals from the population, effectively resetting it to an empty state.
         */
        virtual void clear() = 0;
    };
}
