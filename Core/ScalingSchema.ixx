export module ScalingSchema;

export import Individual;
export import Population;

namespace Geneticxx {
    /**
     * @class ScalingSchema
     * @brief Class responsible for transforming objective scores into fitness values.
     *
     * The `ScalingSchema` class provides an interface for scaling the objective scores of individuals
     * to fitness values. This transformation is typically used in evolutionary algorithms, where the fitness
     * of individuals determines their probability of selection.
     */
    export class ScalingSchema {
    public:
        /**
         * @brief Virtual destructor to ensure proper cleanup of derived class objects.
         *
         * This virtual destructor ensures that the destructors of derived classes are called
         * when deleting an object through a base class pointer.
         */
        virtual ~ScalingSchema() {
        }

        /**
         * @brief Scales the objective scores to fitness values for all individuals in a population.
         *
         * This method transforms the objective scores of all individuals in the provided population
         * into their respective fitness values. This scaling is often necessary for selecting individuals
         * based on their performance in an evolutionary algorithm.
         *
         * @param population Pointer to the population whose individuals' objective scores will be scaled.
         *
         * @return A pointer to the updated population where each individual's fitness has been scaled.
         */
        virtual Population* scale(Population *population) = 0;

        /**
         * @brief Scales the objective score to a fitness value for a single individual.
         *
         * This method transforms the objective score of a single individual into a fitness value.
         * Selection algorithms might ignore individuals with negative fitness values, so it's important
         * that the fitness value accurately reflects the individual's performance.
         *
         * @param individual Pointer to the individual whose objective score will be scaled.
         *
         * @return A pointer to the updated individual with the scaled fitness value.
         */
        virtual Individual* scale(Individual *individual) = 0;
    };
}
