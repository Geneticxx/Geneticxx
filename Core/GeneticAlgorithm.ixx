export module GeneticAlgorithm;

export import Dispatcher;
export import Population;
export import ReplacementSchema;
export import StoppingCriterionSchema;
export import SelectionSchema;
export import InitializationSchema;
export import Evaluation;
export import CrossoverSchema;
export import MutationSchema;
export import ScalingSchema;
export import Observers;
export import RandomRealFromRange;
export import Publisher;

namespace Geneticxx {
   /**
 * @class GeneticAlgorithm
 * @brief Class responsible for configuring and managing the parameters of the genetic algorithm and executing it.
 *
 * This class provides the structure for running a genetic algorithm, managing the population,
 * evaluation, selection, crossover, mutation, and stopping criteria. Derived classes should implement
 * the necessary logic to perform each step of the algorithm.
 */
export class GeneticAlgorithm {


public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived class objects.
     *
     * The virtual destructor ensures that derived class destructors are called
     * when deleting an object through a base class pointer.
     */
    virtual ~GeneticAlgorithm() {
    }

    /**
     * @brief Perform a single step in the genetic algorithm process.
     *
     * This method should be implemented in derived classes to define the logic
     * for a single step of the genetic algorithm.
     */
    virtual void step() = 0;

    /**
     * @brief Perform a specified number of steps in the genetic algorithm process.
     *
     * This method executes multiple steps of the genetic algorithm as specified.
     *
     * @param steps Number of steps to perform.
     */
    virtual void step(int steps) = 0;

    /**
     * @brief Run the genetic algorithm until a stopping criterion is met.
     *
     * This method runs the entire genetic algorithm process, continuously evolving the population
     * until the stopping criterion is satisfied.
     */
    virtual void evolve() = 0;

    /**
     * @brief Initialize the genetic algorithm components.
     *
     * This method initializes all relevant components of the genetic algorithm, including
     * InitializationSchema, Evaluation, and ScalingSchema to ensure the algorithm starts
     * in a properly initialized state.
     *
     * @note Failure to execute the relevant functions during initialization may result
     *       in unexpected behavior during the first iteration.
     */
    virtual void initialize() = 0;

    /**
     * @brief Set the population component of the genetic algorithm.
     *
     * This method sets the population for the genetic algorithm.
     *
     * @param population Pointer to the Population object.
     */
    virtual void addPopulation(Population *population) = 0;

    /**
     * @brief Set the evaluation schema used to evaluate individuals in the population.
     *
     * This method sets the evaluation schema that will be used to evaluate the fitness of
     * individuals within the population.
     *
     * @param evaluation Pointer to the Evaluation object.
     */
    virtual void addEvaluation(Evaluation *evaluation) = 0;

        // Set the replacement schema used to replace individuals in the population
        virtual void setReplacementSchema(ReplacementSchema *replacementSchema) = 0;

    /**
     * @brief Set the stopping criterion schema used to determine when to stop the algorithm.
     *
     * This method sets the criteria that will determine when the genetic algorithm should stop.
     *
     * @param stoppingCriterionSchema Pointer to the StoppingCriterionSchema object.
     */
    virtual void setStoppingCriterionSchema(StoppingCriterionSchema *stoppingCriterionSchema) = 0;

    /**
     * @brief Set the selection schema used to select individuals for reproduction.
     *
     * This method sets the selection process that will be used to choose individuals for reproduction.
     *
     * @param selectionSchema Pointer to the SelectionSchema object.
     */
    virtual void setSelectionSchema(SelectionSchema *selectionSchema) = 0;

    /**
     * @brief Set the initialization schema used to set up the initial population.
     *
     * This method sets the schema used for initializing the first population in the genetic algorithm.
     *
     * @param initializationSchema Pointer to the InitializationSchema object.
     */
    virtual void setInitializationSchema(InitializationSchema *initializationSchema) = 0;

    /**
     * @brief Set the crossover schema used for combining individuals to create offspring.
     *
     * This method sets the crossover schema that defines how individuals are combined to produce offspring.
     *
     * @param crossoverSchema Pointer to the CrossoverSchema object.
     */
    virtual void setCrossoverSchema(CrossoverSchema *crossoverSchema) = 0;

    /**
     * @brief Set the mutation schema used to introduce variability in individuals.
     *
     * This method sets the mutation schema that will be used to introduce random changes in individuals.
     *
     * @param mutationSchema Pointer to the MutationSchema object.
     */
    virtual void setMutationSchema(MutationSchema *mutationSchema) = 0;

    /**
     * @brief Set the scaling schema used for rescaling or modifying values during the algorithm.
     *
     * This method sets the scaling schema that will modify the values of individuals during the algorithm.
     *
     * @param scalingSchema Pointer to the ScalingSchema object.
     */
    virtual void setScalingSchema(ScalingSchema *scalingSchema) = 0;

    /**
     * @brief Set the dispatcher to handle parallel or distributed computation.
     *
     * This method sets the dispatcher responsible for parallel or distributed computation during
     * the algorithm execution.
     *
     * @param dispatcher Pointer to the Dispatcher object.
     */
    virtual void setDispatcher(Dispatcher *dispatcher) = 0;

    /**
     * @brief Set the random numbers generator for handling random real numbers generated in a certain range.
     *
     * This method sets the random number generator used to generate random real numbers within
     * a specified range during the algorithm execution.
     *
     * @param genReal Pointer to the RandomRealFromRange object.
     */
    virtual void setRandomNumbersGenerator(RandomRealFromRange *genReal) = 0;
};

}
