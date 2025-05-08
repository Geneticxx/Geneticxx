export module InitializationSchema;

export import Individual;
export import Genome;
export import Population;

import std;

namespace Geneticxx {
    /**
 * @class InitializationSchema
 * @brief Class responsible for initializing populations.
 *
 * The `InitializationSchema` class defines an interface for initializing populations in a genetic algorithm.
 * It provides the method to populate a vector of populations with individuals, ensuring that the populations
 * are properly initialized for the algorithm's evolution process.
 */
    export class InitializationSchema {
    public:
        /**
         * @brief Virtual destructor to ensure proper cleanup of derived class objects.
         *
         * This virtual destructor ensures that the destructors of derived classes are called
         * when deleting an object through a base class pointer.
         */
        virtual ~InitializationSchema() {}

        /**
         * @brief Initializes the given population with specific individuals.
         *
         * This method initializes the populations with individuals. The exact method of initialization
         * depends on the implementation, but it typically involves creating individuals and assigning them
         * to the given population(s).
         *
         * @param populations Pointer to a vector of unique pointers to populations (min. 1).
         *
         * This method must ensure that the populations are properly populated with valid individuals
         * before the genetic algorithm proceeds with its evolutionary steps.
         */
        virtual void initialize(std::vector<std::unique_ptr<Population> > *populations) = 0;
    };

}
