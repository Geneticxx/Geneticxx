export module PopulationSimple;

import Population;
import std;
import std.compat;

namespace Geneticxx {
    /**
     * @class PopulationSimple
     * @brief A class representing a simple population for a genetic algorithm.
     *
     * This class models a population of individuals for a genetic algorithm, where the population consists of unique pointers
     * to `Individual` objects. It provides methods for managing and manipulating the population, including cloning,
     * retrieving and setting individuals, and managing iterations.
     */
    export class PopulationSimple : public Population {
    protected:
        /**
         * @brief The current iteration count of the genetic algorithm.
         *
         * This variable keeps track of the number of iterations the algorithm has gone through.
         */
        size_t m_Iteration;

        /**
         * @brief A vector containing unique pointers to individuals in the population.
         *
         * This vector holds the population of `Individual` objects, represented by unique pointers.
         */
        std::vector<std::unique_ptr<Individual>> m_PopulationVector;

    public:
        /**
         * @brief Default constructor.
         *
         * Initializes an empty population with zero iterations.
         */
        PopulationSimple();

        /**
         * @brief Destructor.
         *
         * Cleans up the resources used by the `PopulationSimple` object.
         */
        ~PopulationSimple() override;

        /**
         * @brief Copy constructor.
         *
         * Creates a new `PopulationSimple` by copying the data from another `PopulationSimple` object.
         * The population vector is cloned, and iteration count is copied.
         *
         * @param other The `PopulationSimple` object to copy from.
         */
        PopulationSimple(const PopulationSimple& other);

        /**
         * @brief Move constructor.
         *
         * Creates a new `PopulationSimple` by moving the data from another `PopulationSimple` object.
         *
         * @param other The `PopulationSimple` object to move from.
         */
        PopulationSimple(PopulationSimple&& other);

        /**
         * @brief Copy assignment operator.
         *
         * Copies the data from another `PopulationSimple` object to the current instance, including
         * cloning individuals and copying the iteration count.
         *
         * @param other The `PopulationSimple` object to copy from.
         * @return A reference to the current `PopulationSimple` object.
         */
        PopulationSimple& operator=(const PopulationSimple& other);

        /**
         * @brief Move assignment operator.
         *
         * Moves the data from another `PopulationSimple` object to the current instance, transferring
         * ownership of the population vector and iteration count.
         *
         * @param other The `PopulationSimple` object to move from.
         * @return A reference to the current `PopulationSimple` object.
         */
        PopulationSimple& operator=(PopulationSimple&& other);

        /**
         * @brief Creates a new instance of `PopulationSimple`.
         *
         * This method creates and returns a new `PopulationSimple` object, typically used for creating
         * a new population.
         *
         * @return A unique pointer to a newly created `PopulationSimple` object.
         */
        [[nodiscard]] std::unique_ptr<Population> createNew() const override;

        /**
         * @brief Clones the current population.
         *
         * This method creates a new `PopulationSimple` that is a copy of the current one, including
         * the same individuals and iteration count.
         *
         * @return A unique pointer to the cloned `PopulationSimple` object.
         */
        [[nodiscard]] std::unique_ptr<Population> clone() const override;

        /**
         * @brief Retrieves an individual from the population.
         *
         * This method returns a pointer to the `Individual` at the specified index in the population.
         *
         * @param i The index of the individual to retrieve.
         * @return A pointer to the `Individual` at the specified index.
         */
        Individual* getIndividual(size_t i) override;

        /**
         * @brief Sets an individual at a specific index in the population.
         *
         * This method updates the individual at the given index with a new `Individual` object.
         *
         * @param i The index at which to set the individual.
         * @param individual A pointer to the new `Individual` to set at the specified index.
         */
        void setIndividual(size_t i, Individual* individual) override;

        /**
         * @brief Retrieves the size of the population.
         *
         * This method returns the number of individuals currently in the population.
         *
         * @return The size of the population.
         */
        size_t getSize() const override;

        /**
         * @brief Retrieves the current iteration count.
         *
         * This method returns the number of iterations that have passed in the genetic algorithm.
         *
         * @return The current iteration count.
         */
        size_t getIteration() const override;

        /**
         * @brief Increases the iteration count.
         *
         * This method increments the iteration count by one, typically called after a generation has been processed.
         */
        void increaseIteration() override;

        /**
         * @brief Resizes the population.
         *
         * This method adjusts the size of the population, adding or removing individuals as needed.
         *
         * @param size The new size for the population.
         */
        void resize(size_t size) override;

        /**
         * @brief Clears the population.
         *
         * This method removes all individuals from the population, resetting it to an empty state.
         */
        void clear() override;
    };
}
