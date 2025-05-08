export module Individual; // interface for individual implementations

export import Genome;
export import Phenome;
import std;

namespace Geneticxx {
    /**
     * @class Individual
     * @brief Class representing an individual who consists of a genome and a phenome.
     *
     * The `Individual` class represents a single entity in the population of the genetic algorithm,
     * consisting of both a genome and a phenome. It provides methods for retrieving and setting the
     * fitness and objective scores, as well as for manipulating the genome and phenome.
     */
    export class Individual {
    public:
        /**
         * @brief Virtual destructor to ensure proper cleanup of derived class objects.
         *
         * This virtual destructor ensures that the destructors of derived classes are called
         * when deleting an object through a base class pointer.
         */
        virtual ~Individual() {
        }

        /**
         * @brief Creates a new instance of the individual with default properties.
         *
         * This method creates a new instance of the `Individual` class with default properties,
         * typically used for creating fresh individuals.
         *
         * @return Pointer to a newly created Individual.
         */
        virtual Individual* createNew() const = 0;

        /**
         * @brief Creates a deep copy of the current individual.
         *
         * This method creates a new instance of the `Individual` class that is a deep copy
         * of the current individual. It can be used for cloning individuals in the population.
         *
         * @return Pointer to the cloned Individual.
         */
        virtual Individual* clone() const = 0;

        /**
         * @brief Retrieves the fitness value of the individual.
         *
         * This method returns the fitness value of the individual, which is used to evaluate
         * the suitability or performance of the individual in the genetic algorithm.
         *
         * @return The fitness value as a double.
         */
        virtual double getFitness() const = 0;

        /**
         * @brief Sets the fitness value of the individual.
         *
         * This method sets the fitness value of the individual, which will be used to determine
         * its suitability in the evolutionary process.
         *
         * @param fitness The new fitness value.
         */
        virtual void setFitness(double fitness) = 0;

        /**
         * @brief Retrieves the objective score of the individual.
         *
         * This method returns a vector of objective scores for the individual, which are used
         * to assess the quality of the individual based on multiple criteria.
         *
         * @return A vector containing the objective scores.
         */
        virtual std::vector<double> getObjectiveScore() const = 0;

        /**
         * @brief Sets the objective score of the individual.
         *
         * This method sets the objective score of the individual, which are used to measure the
         * individual’s performance with respect to various objectives.
         *
         * @param objectiveScore A vector of objective scores.
         */
        virtual void setObjectiveScore(std::vector<double> *objectiveScore) = 0;

        /**
         * @brief Updates the phenome based on the current genome.
         *
         * This method is called to update the phenome of the individual based on the current
         * genome. The phenome is a representation of the individual that can be observed or
         * measured in the environment.
         */
        virtual void updatePhenome() = 0;

        /**
         * @brief Returns a pointer to the genome of the individual.
         *
         * This method provides access to the genome of the individual, which encodes the genetic
         * information and determines the individual’s characteristics.
         *
         * @return Pointer to the Genome object (const version).
         */
        virtual const Genome* getGenome() const = 0;

        /**
         * @brief Returns a pointer to the genome of the individual.
         *
         * This method provides access to the genome of the individual. It can be used for modifying
         * the genome directly.
         *
         * @return Pointer to the Genome object.
         */
        virtual Genome* getGenome() = 0;

        /**
         * @brief Sets the genome of the individual.
         *
         * This method sets the genome of the individual, which will influence its phenome and
         * fitness in the genetic algorithm.
         *
         * @param genome Pointer to the new Genome object.
         */
        virtual void setGenome(Genome *genome) = 0;

        /**
         * @brief Returns a pointer to the phenome of the individual.
         *
         * This method provides access to the phenome of the individual, which is the observable
         * expression of the individual's genome.
         *
         * @return Pointer to the Phenome object (const version).
         */
        virtual const Phenome* getPhenome() const = 0;

        /**
         * @brief Sets the phenome of the individual.
         *
         * This method sets the phenome of the individual, which represents the individual’s
         * traits in the environment, as determined by its genome.
         *
         * @param phenome Pointer to the new Phenome object.
         */
        virtual void setPhenome(Phenome *phenome) = 0;
    };
}
