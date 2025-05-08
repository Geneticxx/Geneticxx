export module ScalingWithout;

export import ScalingSchema;
import Individual;
import Population;

namespace Geneticxx {
    /**
     * @class ScalingWithout
     * @brief A scaling schema that does not apply any scaling to the population or individuals.
     *
     * This class implements the `ScalingSchema` interface and provides a "no scaling" strategy where
     * neither the population nor individual fitness scores are scaled. It simply returns the population
     * or individual as-is.
     */
    export class ScalingWithout : public ScalingSchema {
    public:
        /**
         * @brief Default constructor for `ScalingWithout` class.
         *
         * This constructor initializes a new instance of the `ScalingWithout` class. It does not perform any
         * specific setup as this class represents a no-scaling behavior.
         */
        ScalingWithout();

        /**
         * @brief Destructor for `ScalingWithout` class.
         *
         * The destructor is virtual to ensure proper cleanup when derived class objects are destroyed.
         */
        ~ScalingWithout() override;

        /**
         * @brief Scales the population (no actual scaling is applied).
         *
         * This method iterates over all individuals in the population and calls the `scale` method on each individual.
         * As part of the "no scaling" schema, the population is returned without any modifications.
         *
         * @param population The population to be scaled.
         * @return A pointer to the unmodified population.
         */
        Population* scale(Population* population) override;

        /**
         * @brief Scales the individual (no actual scaling is applied).
         *
         * This method calculates the sum of all objective scores of the individual and sets this sum as the individual's
         * fitness score. No scaling is applied; the individual's fitness is simply the sum of its objective scores.
         *
         * @param individual The individual to be scaled.
         * @return A pointer to the unmodified individual with updated fitness score.
         */
        Individual* scale(Individual* individual) override;
    };
}
