export module GeneticAlgorithmSimple;

export import GeneticAlgorithm;
export import PublisherPopulation;
import std;
import std.compat;

namespace Geneticxx {
    /**
     * @class GeneticAlgorithmSimple
     * @brief A basic genetic algorithm implementation.
     *
     * This class implements a simple genetic algorithm that evolves a population using selection, crossover,
     * mutation, and replacement operators. The evolution process continues until a stopping criterion is met.
     */
    export class GeneticAlgorithmSimple : public GeneticAlgorithm, public PublisherPopulation {
    private:
        /**
         * @enum event
         * @brief Represents different stages of the genetic algorithm.
         */
        enum event { genDone, genStart, evalDone };

        double m_mutationChance = 0.1;

        /// A vector of unique pointers to Population objects representing the evolving populations.
        std::vector<std::unique_ptr<Population>> m_populations;

        /// A vector of unique pointers to Evaluation objects responsible for evaluating individuals' fitness.
        std::vector<std::unique_ptr<Evaluation>> m_evaluation;

        /// A unique pointer to the ReplacementSchema object defining the population replacement strategy.
        std::unique_ptr<ReplacementSchema> m_replacementSchema;

        /// A unique pointer to the StoppingCriterionSchema object specifying when the algorithm should terminate.
        std::unique_ptr<StoppingCriterionSchema> m_stoppingCriterionSchema;

        /// A unique pointer to the SelectionSchema object defining the individual selection method.
        std::unique_ptr<SelectionSchema> m_selectionSchema;

        /// A unique pointer to the InitializationSchema object defining how the initial population is created.
        std::unique_ptr<InitializationSchema> m_initializationSchema;

        /// A unique pointer to the CrossoverSchema object defining crossover operations.
        std::unique_ptr<CrossoverSchema> m_crossoverSchema;

        /// A unique pointer to the MutationSchema object defining mutation operations.
        std::unique_ptr<MutationSchema> m_mutationSchema;

        /// A unique pointer to the ScalingSchema object responsible for scaling fitness values.
        std::unique_ptr<ScalingSchema> m_scalingSchema;

        /// A pointer to the Dispatcher object managing task execution.
        Dispatcher* m_dispatcher;

        /// A pointer to a random number generator for real numbers.
        RandomRealFromRange* m_randomNumbersGeneratorReal;

    public:
        /**
         * @brief Constructs a GeneticAlgorithmSimple instance.
         *
         * Initializes all required components of the genetic algorithm.
         *
         * @param populations The initial set of populations.
         * @param evaluation The evaluation strategy for fitness measurement.
         * @param replacement The population replacement strategy.
         * @param crossover The crossover operation strategy.
         * @param mutation The mutation operation strategy.
         * @param scaling The scaling strategy for fitness values.
         * @param selection The selection method for choosing parents.
         * @param initialization The initialization strategy for the population.
         * @param stoppingCriterion The stopping condition for evolution.
         * @param dispatcher Task manager for execution control.
         * @param genReal Random number generator.
         */
        GeneticAlgorithmSimple(
            std::vector<std::unique_ptr<Population>>* populations,
            Evaluation* evaluation,
            ReplacementSchema* replacement,
            CrossoverSchema* crossover,
            MutationSchema* mutation,
            ScalingSchema* scaling,
            SelectionSchema* selection,
            InitializationSchema* initialization,
            StoppingCriterionSchema* stoppingCriterion,
            Dispatcher* dispatcher,
            RandomRealFromRange* genReal
        );

        /// Destructor for GeneticAlgorithmSimple.
        ~GeneticAlgorithmSimple() override;

        /// Executes one step of the genetic algorithm.
        void step() override;

        /// Executes a given number of steps in the genetic algorithm.
        /// @param steps The number of steps to execute.
        void step(int steps) override;

        /// Runs the evolution process until the stopping criterion is met.
        void evolve() override;

        /// Initializes the genetic algorithm by setting up populations and evaluating the initial state.
        void initialize() override;

        /// Adds a population to the algorithm.
        /// @param population The population to add.
        void addPopulation(Population* population) override;

        /// Adds an evaluation function to the algorithm.
        /// @param evaluation The evaluation function to add.
        void addEvaluation(Evaluation* evaluation) override;

        /// Sets the replacement schema.
        /// @param replacementSchema The replacement schema to use.
        void setReplacementSchema(ReplacementSchema* replacementSchema) override;

        /// Sets the stopping criterion schema.
        /// @param stoppingCriterionSchema The stopping criterion schema to use.
        void setStoppingCriterionSchema(StoppingCriterionSchema* stoppingCriterionSchema) override;

        /// Sets the selection schema.
        /// @param selectionSchema The selection schema to use.
        void setSelectionSchema(SelectionSchema* selectionSchema) override;

        /// Sets the initialization schema.
        /// @param initializationSchema The initialization schema to use.
        void setInitializationSchema(InitializationSchema* initializationSchema) override;

        /// Sets the crossover schema.
        /// @param crossoverSchema The crossover schema to use.
        void setCrossoverSchema(CrossoverSchema* crossoverSchema) override;

        /// Sets the mutation schema.
        /// @param mutationSchema The mutation schema to use.
        void setMutationSchema(MutationSchema* mutationSchema) override;

        /// Sets the scaling schema.
        /// @param scalingSchema The scaling schema to use.
        void setScalingSchema(ScalingSchema* scalingSchema) override;

        /// Sets the dispatcher responsible for task execution.
        /// @param dispatcher The dispatcher to use.
        void setDispatcher(Dispatcher* dispatcher) override;

        /// Sets the random number generator for real numbers.
        /// @param genReal The random number generator to use.
        void setRandomNumbersGenerator(RandomRealFromRange* genReal) override;

        /// Attempts to mutate a given genome based on a predefined mutation probability.
        /// @param object The genome to mutate.
        void tryToMutate(Genome* object);
    };
}
