export module InitializeWithCopies;

export import InitializationSchema;
import std;

namespace Geneticxx {
    /**
     * @class InitializeWithCopies
     * @brief A class for initializing a population with multiple copies of a given individual.
     *
     * This class defines a schema for initializing a population by creating a specified number of copies
     * of a provided individual. It supports the initialization of multiple populations based on this schema.
     */
    export class InitializeWithCopies : public InitializationSchema {
    private:
        /**
         * @brief Pointer to an individual instance, managed with unique ownership.
         *
         * This individual is used as a template to generate copies for the population.
         */
        std::unique_ptr<Individual> individual;

        /**
         * @brief The number of copies to create in the population.
         *
         * This specifies how many identical individuals should be added to the population during initialization.
         */
        int size;

    public:
        /**
         * @brief Constructor to initialize the schema with a specified number of copies and an example individual.
         *
         * This constructor initializes the schema by setting the number of copies (size) and providing an example
         * individual that will be cloned to create the population members.
         *
         * @param size The number of copies to create in the population.
         * @param individual Pointer to the individual that will be cloned to populate the population.
         */
        InitializeWithCopies(int size, Individual* individual);

        /**
         * @brief Destructor.
         *
         * Cleans up the resources used by the object. Since the individual is managed by a unique_ptr,
         * it will be automatically cleaned up.
         */
        ~InitializeWithCopies() override;

        /**
         * @brief Initializes the population with the specified number of individual copies.
         *
         * This method fills each population in the provided vector with the specified number of copies of the individual.
         *
         * @param populations Pointer to a vector of populations to be initialized.
         *
         * @note If the size is less than or equal to zero, no individuals will be added to the population.
         */
        void initialize(std::vector<std::unique_ptr<Population>>* populations) override;

        /**
         * @brief Sets the individual to be copied for population initialization.
         *
         * This method allows updating the individual to be cloned for initializing the population.
         *
         * @param individual Pointer to the new individual that will be cloned.
         */
        void setIndividual(Individual* individual);
    };
}
