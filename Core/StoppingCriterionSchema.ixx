export module StoppingCriterionSchema;

export import Population;

namespace Geneticxx {
    /**
     * @class StoppingCriterionSchema
     * @brief Class responsible for defining and checking stopping criteria in evolutionary algorithms.
     *
     * The `StoppingCriterionSchema` class provides an interface for checking whether the stopping
     * criterion for an evolutionary algorithm has been met. Derived classes should implement specific
     * criteria (e.g., a maximum number of generations, a target fitness value).
     */
    export class StoppingCriterionSchema {
    public:
        /**
         * @brief Virtual destructor for proper cleanup in derived classes.
         *
         * The destructor ensures that derived class objects are correctly destroyed when
         * deleted through a base class pointer.
         */
        virtual ~StoppingCriterionSchema() {}

        /**
         * @brief Checks if the stopping criterion is met for a given population.
         *
         * This method evaluates the population against the stopping condition defined by
         * the derived class. The specific stopping criterion (e.g., maximum number of generations
         * or fitness threshold) will depend on the implementation in the derived class.
         *
         * @param population The Population instance to evaluate against the stopping criterion.
         *
         * @return `true` if the stopping condition is satisfied, `false` otherwise.
         */
        virtual bool check(Population *population) = 0;
    };

}
