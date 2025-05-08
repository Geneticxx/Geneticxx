export module DispatcherMultiThreaded;

export import Dispatcher;

namespace Geneticxx {
    /**
     * @class DispatcherMultiThreaded
     * @brief A dispatcher that performs evaluations in parallel on 4 threads
     *
     * The `DispatcherMultiThreaded` class is a concrete implementation of the `Dispatcher` interface.
     * It processes each individual in a population in parallel on 4 threads by applying all evaluation functions
     * to their phenomes and storing the computed objective scores.
     * It shouldn't be used when evaluation needs data beyond a single individual
     * or if the evaluation function has low computational cost.
     * This is a very simple, inefficient implementation to showcase the possibility of multithreading.
     */
    export class DispatcherMultiThreaded : public Dispatcher {
    public:
        /**
         * @brief Default constructor for DispatcherMultiThreaded.
         *
         * Initializes an instance of `DispatcherMultiThreaded`, which applies evaluations concurrently
         */
        DispatcherMultiThreaded();

        /**
         * @brief Destructor for DispatcherMultiThreaded.
         *
         * Ensures proper cleanup when an instance of `DispatcherMultiThreaded` is destroyed.
         */
        ~DispatcherMultiThreaded() override;

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

        static void dispatched(Individual* individual, std::vector<std::unique_ptr<Evaluation>>* evaluation);
    };
}
