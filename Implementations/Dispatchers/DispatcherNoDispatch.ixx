export module DispatcherNoDispatch;

import Dispatcher;

namespace Geneticxx {
    /**
     * @class DispatcherNoDispatch
     * @brief A dispatcher that performs evaluations sequentially without parallelization.
     *
     * The `DispatcherNoDispatch` class is a concrete implementation of the `Dispatcher` interface.
     * It processes each individual in a population sequentially by applying all evaluation functions
     * to their phenomes and storing the computed objective scores.
     */
    export class DispatcherNoDispatch : public Dispatcher {
    public:
        /**
         * @brief Default constructor for DispatcherNoDispatch.
         *
         * Initializes an instance of `DispatcherNoDispatch`, which applies evaluations sequentially.
         */
        DispatcherNoDispatch();

        /**
         * @brief Destructor for DispatcherNoDispatch.
         *
         * Ensures proper cleanup when an instance of `DispatcherNoDispatch` is destroyed.
         */
        ~DispatcherNoDispatch() override;

        /**
         * @brief Dispatches the evaluations for each individual in the population.
         *
         * This method iterates through all individuals in the given population, applies
         * all evaluation functions from the provided evaluation list, and stores the
         * computed objective scores.
         *
         * @param population Pointer to the Population object containing individuals to be evaluated.
         * @param evaluation Vector of unique pointers to Evaluation objects, each representing an evaluation function.
         */
        void dispatch(Population* population, std::vector<std::unique_ptr<Evaluation>>* evaluation) override;
    };
}
