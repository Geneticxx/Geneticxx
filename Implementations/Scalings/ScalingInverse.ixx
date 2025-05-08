export module ScalingInverse;

export import ScalingSchema;
import Individual;
import Population;

namespace Geneticxx {
    /**
     * @class ScalingInverse
     * @brief A scaling schema that applies inverse scaling to the fitness of individuals.
     *
     * This class implements the `ScalingSchema` interface and applies inverse scaling to the fitness of individuals
     * in a population. The fitness is calculated as the sum of the inverse of each objective score of an individual.
     */
    export class ScalingInverse : public ScalingSchema {
    public:
        /**
         * @brief Default constructor for `ScalingInverse` class.
         *
         * This constructor initializes a new instance of the `ScalingInverse` class, which will apply inverse scaling
         * to the fitness scores of individuals.
         */
        ScalingInverse();

        /**
         * @brief Destructor for `ScalingInverse` class.
         *
         * The destructor is virtual to ensure proper cleanup when derived class objects are destroyed.
         */
        ~ScalingInverse() override;

        /**
         * @brief Scales the population using inverse scaling.
         *
         * This method iterates over all individuals in the population and calls the `scale` method on each individual.
         * The fitness of each individual is updated by applying inverse scaling to their objective scores.
         *
         * @param population The population to be scaled.
         * @return A pointer to the modified population where each individual's fitness has been updated.
         */
        Population* scale(Population* population) override;

        /**
         * @brief Scales the individual using inverse scaling.
         *
         * This method applies inverse scaling to an individual's objective scores by summing the inverses of each
         * objective score and setting this sum as the individual's fitness. A higher objective score results in a
         * lower fitness value.
         *
         * @param individual The individual to be scaled.
         * @return A pointer to the modified individual with the updated fitness score.
         */
        Individual* scale(Individual* individual) override;
    };
}
