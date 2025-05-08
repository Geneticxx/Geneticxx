export module ReplacementFull;

export import  ReplacementSchema;

namespace Geneticxx {
    /**
     * @class ReplacementFull
     * @brief A replacement schema that replaces the entire population with a new one.
     *
     * This class implements the `ReplacementSchema` interface and defines the behavior for a full
     * replacement strategy. The `replace` method replaces all individuals in the original population
     * with the individuals from the new (replacing) population.
     */
    export class ReplacementFull : public ReplacementSchema {
    public:
        /**
         * @brief Default constructor for `ReplacementFull` class.
         *
         * This constructor initializes a new instance of the `ReplacementFull` class. The constructor
         * doesn't take any parameters and doesn't perform any specific setup as this class directly
         * implements the replacement strategy.
         */
        ReplacementFull();

        /**
         * @brief Destructor for `ReplacementFull` class.
         *
         * The destructor is virtual to ensure proper cleanup when derived class objects are destroyed.
         */
        ~ReplacementFull() override;

        /**
         * @brief Replaces the original population with the replacing population.
         *
         * This method performs a full replacement of the original population with the new population.
         * It ensures that both populations have the same size. If the sizes differ, the original population
         * is cleared before the replacement.
         *
         * @param originalPopulation The population to be replaced.
         * @param replacingPopulation The new population that will replace the original.
         * @return A pointer to the modified `originalPopulation` after replacement.
         *
         * This method also increases the iteration count of the original population.
         */
        Population* replace(Population* originalPopulation, Population* replacingPopulation) override;
    };
}
