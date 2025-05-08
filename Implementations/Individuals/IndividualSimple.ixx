export module IndividualSimple; // implementation of Individual.ixx interface

export import Individual;
import std;

namespace Geneticxx {
    /**
     * @class IndividualSimple
     * @brief Represents an individual in a genetic algorithm with genome and phenome.
     *
     * This class provides functionality to handle the individual's genome, phenome, fitness, and objective score.
     * It supports cloning, copying, moving, and managing the genome and phenome.
     */
    export class IndividualSimple : public Individual {
    private:
        /**
         * @brief Fitness value of the individual, indicating how well it performs.
         *
         * The fitness is a key metric used in genetic algorithms to evaluate the quality of an individual.
         */
        double m_Fitness;

        /**
         * @brief Objective score of the individual, a secondary metric for evaluation.
         *
         * The objective score provides additional evaluation criteria, often used in multi-objective optimization.
         */
        std::vector<double> m_ObjectiveScore = {0};

        /**
         * @brief Pointer to the genome of the individual, defining its genetic makeup.
         *
         * The genome is responsible for the genetic representation of the individual, which can be mutated and evolved.
         */
        std::unique_ptr<Genome> m_Genome{};

        /**
         * @brief Pointer to the phenome of the individual, representing its traits or behaviour.
         *
         * The phenome is a manifestation of the genome and defines how the individual behaves or performs in its environment.
         */
        std::unique_ptr<Phenome> m_Phenome{};

    public:
        /**
         * @brief Default constructor.
         *
         * Initializes an individual with default values: fitness is set to 0.0, and the genome and phenome are nullptr.
         */
        IndividualSimple();

        /**
         * @brief Constructor to initialize IndividualSimple with a Phenome and a Genome.
         *
         * Initializes the individual with a given phenome and genome.
         *
         * @param phenome Pointer to the phenome of the individual.
         * @param genome Pointer to the genome of the individual.
         */
        IndividualSimple(Phenome* phenome, Genome* genome);

        /**
         * @brief Copy constructor.
         *
         * Initializes a new individual by copying data from another individual. This includes cloning the genome and phenome.
         *
         * @param individual The individual to copy.
         */
        IndividualSimple(const IndividualSimple& individual);

        /**
         * @brief Move constructor.
         *
         * Initializes a new individual by transferring ownership of the genome and phenome from another individual.
         *
         * @param individual The individual to move.
         */
        IndividualSimple(IndividualSimple&& individual);

        /**
         * @brief Copy assignment operator.
         *
         * Assigns the data of another individual to the current individual. This includes cloning the genome and phenome.
         *
         * @param individual The individual to copy.
         * @return Reference to the current individual.
         */
        IndividualSimple& operator=(const IndividualSimple& individual);

        /**
         * @brief Move assignment operator.
         *
         * Transfers ownership of the genome and phenome from another individual to the current individual.
         *
         * @param individual The individual to move.
         * @return Reference to the current individual.
         */
        IndividualSimple& operator=(IndividualSimple&& individual);

        /**
         * @brief Destructor.
         *
         * Destroys the individual, cleaning up the resources associated with the genome and phenome.
         */
        ~IndividualSimple() override;

        /**
         * @brief Creates a new individual.
         *
         * This method creates and returns a new instance of IndividualSimple.
         *
         * @return A new individual.
         */
        Individual* createNew() const override;

        /**
         * @brief Clones the individual (deep copy).
         *
         * This method creates a new individual that is a copy of the current individual, including cloned genome and phenome.
         *
         * @return A new cloned individual.
         */
        Individual* clone() const override;

        /**
         * @brief Gets the fitness value of the individual.
         *
         * This method retrieves the fitness value, which represents how well the individual performs in the context of the problem.
         *
         * @return The fitness value of the individual.
         */
        double getFitness() const override;

        /**
         * @brief Sets the fitness value of the individual.
         *
         * This method assigns a new fitness value to the individual.
         *
         * @param fitness The new fitness value to set.
         */
        void setFitness(double fitness) override;

        /**
         * @brief Gets the objective score of the individual.
         *
         * This method retrieves the objective score, which provides additional evaluation criteria for the individual.
         *
         * @return The objective score as a vector of doubles.
         */
        std::vector<double> getObjectiveScore() const override;

        /**
         * @brief Sets the objective score of the individual.
         *
         * This method assigns a new objective score to the individual.
         *
         * @param objectiveScore The new objective score to set.
         */
        void setObjectiveScore(std::vector<double> *objectiveScore) override;

        /**
         * @brief Updates the phenome of the individual based on its genome.
         *
         * This method synchronizes the phenome with the current state of the genome.
         */
        void updatePhenome() override;

        /**
         * @brief Gets the genome of the individual.
         *
         * This method retrieves the genome of the individual, which is used for genetic operations.
         *
         * @return A pointer to the genome of the individual.
         */
        const Genome* getGenome() const override;

        /**
         * @brief Gets the genome of the individual.
         *
         * This method retrieves the genome of the individual, which is used for genetic operations.
         *
         * @return A pointer to the genome of the individual.
         */
        Genome* getGenome() override;

        /**
         * @brief Sets the genome of the individual.
         *
         * This method assigns a new genome to the individual. Ownership of the genome is transferred.
         *
         * @param genome Pointer to the new genome to set.
         */
        void setGenome(Genome* genome) override;

        /**
         * @brief Gets the phenome of the individual.
         *
         * This method retrieves the phenome of the individual, which represents its behavior or traits.
         *
         * @return A pointer to the phenome of the individual.
         */
        Phenome* getPhenome() const override;

        /**
         * @brief Sets the phenome of the individual.
         *
         * This method assigns a new phenome to the individual. Ownership of the phenome is transferred.
         *
         * @param phenome Pointer to the new phenome to set.
         */
        void setPhenome(Phenome* phenome) override;
    };
}
